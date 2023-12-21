#define DONT_SHARED_OPCODES
#define PLATFORM_ZONE 1

#include "../common/global_define.h"
#include "../common/features.h"
#include "../common/queue.h"
#include "../common/timer.h"
#include "../common/eq_stream.h"
#include "../common/eq_stream_factory.h"
#include "../common/eq_packet_structs.h"
#include "../common/mutex.h"
#include "../common/version.h"
#include "../common/packet_dump_file.h"
#include "../common/opcodemgr.h"
#include "../common/guilds.h"
#include "../common/eq_stream_ident.h"
#include "../common/patches/patches.h"
#include "../common/rulesys.h"
#include "../common/misc_functions.h"
#include "../common/strings.h"
#include "../common/platform.h"
#include "../common/crash.h"
#include "../common/ipc_mutex.h"
#include "../common/memory_mapped_file.h"
#include "../common/eqemu_exception.h"
#include "../common/spdat.h"
#include "../common/eqemu_logsys.h"
#include "../common/event/timer.h"
#include "../common/config.h"

#include "masterentity.h"
#include "worldserver.h"
#include "zone.h"
#include "queryserv.h"
#include "command.h"
#include "titles.h"
#include "guild_mgr.h"
#include "quest_parser_collection.h"
#include "lua/lua_parser.h"
#include "questmgr.h"

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <ctime>
#include <chrono>
#include <memory>

#ifdef _CRTDBG_MAP_ALLOC
#undef new
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#ifdef _WINDOWS
#include <conio.h>
#include <process.h>
#else
#include <pthread.h>
#include "../common/unix.h"
#endif

volatile bool RunLoops = true;
extern volatile bool is_zone_loaded;

TimeoutManager timeout_manager;
EntityList entity_list;
WorldServer worldserver;
uint32 numclients = 0;
char errorname[32];
extern Zone* zone;
EQStreamFactory eqsf(ZoneStream);
TitleManager title_manager;
QueryServ* QServ = 0;
QuestParserCollection* parse = 0;
EQEmuLogSys LogSys;
const SPDat_Spell_Struct* spells;
int32 SPDAT_RECORDS = -1;
double frame_time = 0.0;

void Shutdown();
void UpdateWindowTitle(char* iNewTitle);
void CatchSignal(int sig_num);

extern void MapOpcodes();

int main(int argc, char** argv) {
	RegisterExecutablePlatform(ExePlatformZone);
	LogSys.LoadLogSettingsDefaults();
	set_exception_handler();
	QServ = new QueryServ;

	LogInfo("Starting Zone v{}", VERSION);
	auto load_result = Config::LoadConfig();
	if (!load_result.empty()) {
		LogError("{}", load_result);
		return 1;
	}

	const char* zone_name;
	std::string z_name;
	if (argc == 4) {
		worldserver.SetLauncherName(argv[2]);
		auto zone_port = Strings::Split(argv[1], ':');

		if (!zone_port.empty()) {
			z_name = zone_port[0];
		}

		if (zone_port.size() > 1) {
			std::string p_name = zone_port[1];
			Config::get()->SetZonePort(atoi(p_name.c_str()));
		}

		worldserver.SetLaunchedName(z_name.c_str());
		if (strncmp(z_name.c_str(), "dynamic_", 8) == 0) {
			zone_name = ".";
		} else {
			zone_name = z_name.c_str();
		}
	} else if (argc == 3) {
		worldserver.SetLauncherName(argv[2]);
		auto zone_port = Strings::Split(argv[1], ':');

		if (!zone_port.empty()) {
			z_name = zone_port[0];
		}

		if (zone_port.size() > 1) {
			std::string p_name = zone_port[1];
			Config::get()->SetZonePort(atoi(p_name.c_str()));
		}

		worldserver.SetLaunchedName(z_name.c_str());
		if (strncmp(z_name.c_str(), "dynamic_", 8) == 0) {
			zone_name = ".";
		} else {
			zone_name = z_name.c_str();
		}
	} else if (argc == 2) {
		worldserver.SetLauncherName("NONE");
		auto zone_port = Strings::Split(argv[1], ':');

		if (!zone_port.empty()) {
			z_name = zone_port[0];
		}

		if (zone_port.size() > 1) {
			std::string p_name = zone_port[1];
			Config::get()->SetZonePort(atoi(p_name.c_str()));
		}

		worldserver.SetLaunchedName(z_name.c_str());
		if (strncmp(z_name.c_str(), "dynamic_", 8) == 0) {
			zone_name = ".";
		} else {
			zone_name = z_name.c_str();
		}
	} else {
		zone_name = ".";
		worldserver.SetLaunchedName(".");
		worldserver.SetLauncherName("NONE");
	}

	worldserver.SetPassword(Config::get()->WorldSharedKey.c_str());

	LogInfo("Connecting to MySQL...");
	if (!database.Connect(
	        Config::get()->DatabaseHost.c_str(),
	        Config::get()->DatabaseUsername.c_str(),
	        Config::get()->DatabasePassword.c_str(),
	        Config::get()->DatabaseDB.c_str(),
	        Config::get()->DatabasePort)) {
		LogError("Cannot continue without a database connection.");
		return 1;
	}

	LogSys.SetDatabase(&database)
	    ->LoadLogDatabaseSettings()
	    ->SetGMSayHandler(&Zone::GMSayHookCallBackProcess)
	    ->StartFileLogs();

	/* Guilds */
	guild_mgr.SetDatabase(&database);

#ifdef _EQDEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	LogInfo("VERSION: {} ", VERSION);

	/*
	 * Setup nice signal handlers
	 */
	if (signal(SIGINT, CatchSignal) == SIG_ERR) {
		LogError("Could not set signal handler");
		return 1;
	}
	if (signal(SIGTERM, CatchSignal) == SIG_ERR) {
		LogError("Could not set signal handler");
		return 1;
	}
#ifndef WIN32
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
		LogError("Could not set signal handler");
		return 1;
	}
#endif

	LogInfo("Mapping Incoming Opcodes");
	MapOpcodes();

	LogInfo("Loading Variables");
	database.LoadVariables();

	std::string hotfix_name;
	if (database.GetVariable("hotfix_name", hotfix_name)) {
		if (!hotfix_name.empty()) {
			LogInfo("Current hotfix in use: [{}]", hotfix_name.c_str());
		}
	}

	LogInfo("Loading zone names");
	database.LoadZoneNames();

	LogInfo("Loading items");
	if (!database.LoadItems(hotfix_name)) {
		LogError("Loading items FAILED!");
		LogError("Failed. But ignoring error and going on...");
	}

	LogInfo("Loading npc faction lists");
	if (!database.LoadNPCFactionLists(hotfix_name)) {
		LogError("Loading npcs faction lists FAILED!");
		return 1;
	}
	LogInfo("Loading loot tables");
	if (!database.LoadLoot(hotfix_name)) {
		LogError("Loading loot FAILED!");
		return 1;
	}
	LogInfo("Loading skill caps");
	if (!database.LoadSkillCaps(std::string(hotfix_name))) {
		LogError("Loading skill caps FAILED!");
		return 1;
	}

	LogInfo("Loading spells");
	if (!database.LoadSpells(hotfix_name, &SPDAT_RECORDS, &spells)) {
		LogError("Loading spells FAILED!");
		return 1;
	}

	// load these here for now
	database.SetSharedItemsCount(database.GetItemsCount());
	database.SetSharedSpellsCount(database.GetSpellsCount());

	LogInfo("Loading base data");
	if (!database.LoadBaseData(hotfix_name)) {
		LogError("Loading base data FAILED!");
		return 1;
	}

	LogInfo("Loading guilds");
	guild_mgr.LoadGuilds();

	LogInfo("Loading factions");
	database.LoadFactionData();

	LogInfo("Loading titles");
	title_manager.LoadTitles();

	LogInfo("Loading AA actions");
	database.LoadAAActions();

	LogInfo("Loading commands");
	int retval = command_init();
	if (retval < 0) {
		LogError("Command loading FAILED");
	} else {
		LogInfo("{} commands loaded", retval);
	}

	// rules:
	{
		std::string tmp;
		if (database.GetVariable("RuleSet", tmp)) {
			LogInfo("Loading rule set '{}'", tmp.c_str());
			if (!RuleManager::Instance()->LoadRules(&database, tmp.c_str())) {
				LogError("Failed to load ruleset '{}', falling back to defaults.", tmp.c_str());
			}
		} else {
			if (!RuleManager::Instance()->LoadRules(&database, "default")) {
				LogInfo("No rule set configured, using default rules");
			} else {
				LogInfo("Loaded default rule set 'Default'");
			}
		}
	}

	parse = new QuestParserCollection();
	auto lua = std::make_unique<LuaParser>();
	parse->RegisterQuestInterface(lua.get(), "lua");

	// now we have our parser, load the quests
	LogInfo("Loading quests");
	parse->ReloadQuests();

	if (!worldserver.Connect()) {
		LogError("Worldserver Connection Failed :: worldserver.Connect()");
	}

	Timer InterserverTimer(INTERSERVER_TIMER);  // does MySQL pings and auto-reconnect
	Timer RemoteCallProcessTimer(5000);
#ifdef EQPROFILE
#ifdef PROFILE_DUMP_TIME
	Timer profile_dump_timer(PROFILE_DUMP_TIME * 1000);
	profile_dump_timer.Start();
#endif
#endif
	if (!strlen(zone_name) || !strcmp(zone_name, ".")) {
		LogInfo("Entering sleep mode");
	} else if (!Zone::Bootup(database.GetZoneID(zone_name), true)) {
		LogError("Zone Bootup failed :: Zone::Bootup");
		zone = 0;
	}

	// register all the patches we have avaliable with the stream identifier.
	EQStreamIdentifier stream_identifier;
	RegisterAllPatches(stream_identifier);

#ifndef WIN32
	Log(Logs::Detail, Logs::None, "Main thread running with thread id %d", pthread_self());
#endif

	Timer quest_timers(100);
	UpdateWindowTitle(nullptr);
	bool worldwasconnected = worldserver.Connected();
	EQStream* eqss;
	EQOldStream* eqoss;
	EQStreamInterface* eqsi;
	std::chrono::time_point<std::chrono::steady_clock> frame_prev = std::chrono::steady_clock::now();

	auto loop_fn = [&](EQ::Timer* t) {
		{  // profiler block to omit the sleep from times

			/**
			 * Calculate frame time
			 */
			std::chrono::time_point<std::chrono::steady_clock> frame_now = std::chrono::steady_clock::now();
			frame_time = std::chrono::duration<double>(frame_now - frame_prev).count();
			frame_prev = frame_now;
			// Advance the timer to our current point in time
			Timer::SetCurrentTime();

			worldserver.Process();

			if (!eqsf.IsOpen() && Config::get()->ZonePortCurrent != 0) {
				LogInfo("Starting EQ Network server on port {} ", Config::get()->ZonePortCurrent);
				if (!eqsf.Open(Config::get()->ZonePortCurrent)) {
					LogError("Failed to open port {} ", Config::get()->ZonePortCurrent);
					Config::get()->SetZonePort(0);
					worldserver.Disconnect();
					worldwasconnected = false;
				}
			}

			// check the factory for any new incoming streams.
			while ((eqss = eqsf.Pop())) {
				// pull the stream out of the factory and give it to the stream identifier
				// which will figure out what patch they are running, and set up the dynamic
				// structures and opcodes for that patch.
				struct in_addr in;
				in.s_addr = eqss->GetRemoteIP();
				Log(Logs::Detail, Logs::WorldServer, "New connection from %s:%d", inet_ntoa(in), ntohs(eqss->GetRemotePort()));
				stream_identifier.AddStream(eqss);  // takes the stream
			}

			// check the factory for any new incoming streams.
			while ((eqoss = eqsf.PopOld())) {
				// pull the stream out of the factory and give it to the stream identifier
				// which will figure out what patch they are running, and set up the dynamic
				// structures and opcodes for that patch.
				struct in_addr in;
				in.s_addr = eqoss->GetRemoteIP();
				Log(Logs::Detail, Logs::WorldServer, "New connection from %s:%d", inet_ntoa(in), ntohs(eqoss->GetRemotePort()));
				stream_identifier.AddOldStream(eqoss);  // takes the stream
			}

			// give the stream identifier a chance to do its work....
			stream_identifier.Process();

			// check the stream identifier for any now-identified streams
			while ((eqsi = stream_identifier.PopIdentified())) {
				// now that we know what patch they are running, start up their client object
				struct in_addr in;
				in.s_addr = eqsi->GetRemoteIP();
				Log(Logs::Detail, Logs::WorldServer, "New client from %s:%d", inet_ntoa(in), ntohs(eqsi->GetRemotePort()));
				auto client = new Client(eqsi);
				entity_list.AddClient(client);
			}

			// check for timeouts in other threads
			timeout_manager.CheckTimeouts();

			if (worldserver.Connected()) {
				worldwasconnected = true;
			} else {
				if (worldwasconnected && is_zone_loaded)
					entity_list.ChannelMessageFromWorld(0, 0, ChatChannel_Broadcast, 0, 0, 100, "WARNING: World server connection lost");
				worldwasconnected = false;
			}

			if (is_zone_loaded) {
				entity_list.GroupProcess();
				entity_list.DoorProcess();
				entity_list.ObjectProcess();
				entity_list.CorpseProcess();
				entity_list.CorpseDepopProcess();
				entity_list.TrapProcess();
				entity_list.RaidProcess();

				entity_list.Process();
				entity_list.MobProcess();
				entity_list.BeaconProcess();
				entity_list.EncounterProcess();

				if (zone) {
					if (!zone->Process()) {
						Zone::Shutdown();
					}
				}

				if (quest_timers.Check())
					quest_manager.Process();
			}
			if (InterserverTimer.Check()) {
				InterserverTimer.Start();
				database.ping();
				// AsyncLoadVariables(dbasync, &database);
				entity_list.UpdateWho();
				if (worldserver.TryReconnect() && (!worldserver.Connected()))
					worldserver.AsyncConnect();
			}

			if (!RunLoops) {
				EQ::EventLoop::Get().Shutdown();
				Zone::Shutdown(true);
			}

#ifdef EQPROFILE
#ifdef PROFILE_DUMP_TIME
			if (profile_dump_timer.Check()) {
				DumpZoneProfile();
			}
#endif
#endif
		}  // end extra profiler block
	};

	EQ::Timer process_timer(loop_fn);
	process_timer.Start(32, true);

	EQ::EventLoop::Get().Run();

	entity_list.Clear();
	entity_list.RemoveAllEncounters();  // gotta do it manually or rewrite lots of shit :P

	parse->ClearInterfaces();

	title_manager.ClearTitles();
	if (zone != 0)
		Zone::Shutdown(true);
	// Fix for Linux world server problem.
	eqsf.Close();
	worldserver.Disconnect();
	command_deinit();
	safe_delete(parse);
	LogInfo("Proper zone shutdown complete.");
	LogSys.CloseFileLogs();
	return 0;
}

void CatchSignal(int sig_num) {
#ifdef _WINDOWS
	LogInfo("Recieved signal: {} ", sig_num);
#endif
	Shutdown();
}

void Shutdown() {
	RunLoops = false;
	LogInfo("Shutting down...");
}

/* Update Window Title with relevant information */
void UpdateWindowTitle(char* iNewTitle) {
#ifdef _WINDOWS
	char tmp[500];
	if (iNewTitle) {
		snprintf(tmp, sizeof(tmp), "%i: %s", Config::get()->ZonePort, iNewTitle);
	} else {
		if (zone) {
#if defined(GOTFRAGS) || defined(_EQDEBUG)
			snprintf(tmp, sizeof(tmp), "%i: %s, %i clients, %i", Config::get()->ZonePort, zone->GetShortName(), numclients, getpid());
#else
			snprintf(tmp, sizeof(tmp), "%s :: clients: %i :: port: %i", zone->GetShortName(), numclients, Config::get()->ZonePort);
#endif
		} else {
#if defined(GOTFRAGS) || defined(_EQDEBUG)
			snprintf(tmp, sizeof(tmp), "%i: sleeping, %i", Config::get()->ZonePort, getpid());
#else
			snprintf(tmp, sizeof(tmp), "%i: sleeping", Config::get()->ZonePort);
#endif
		}
	}
	SetConsoleTitle(tmp);
#endif
}
