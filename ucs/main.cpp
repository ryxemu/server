#include "../common/eqemu_logsys.h"
#include "../common/global_define.h"
#include "clientlist.h"
#include "../common/opcodemgr.h"
#include "../common/eq_stream_factory.h"
#include "../common/rulesys.h"
#include "../common/servertalk.h"
#include "../common/platform.h"
#include "../common/crash.h"
#include "../common/strings.h"
#include "../common/event/timer.h"
#include "../common/config.h"
#include "database.h"
#include "chatchannel.h"
#include "worldserver.h"
#include <list>
#include <signal.h>

ChatChannelList *ChannelList;
Clientlist *g_Clientlist;
EQEmuLogSys LogSys;
TimeoutManager timeout_manager;
Database database;
WorldServer *worldserver = nullptr;

std::string WorldShortName;

uint32 ChatMessagesSent = 0;

volatile bool RunLoops = true;

void CatchSignal(int sig_num) {
	RunLoops = false;

	if (worldserver)
		worldserver->Disconnect();
}

int main() {
	RegisterExecutablePlatform(ExePlatformUCS);
	LogSys.LoadLogSettingsDefaults();
	set_exception_handler();

	// Check every minute for unused channels we can delete
	//
	Timer ChannelListProcessTimer(60000);
	Timer ClientConnectionPruneTimer(60000);

	Timer InterserverTimer(INTERSERVER_TIMER);  // does auto-reconnect

	LogInfo("Starting UCS v{}", VERSION);

	auto load_result = Config::LoadConfig();
	if (!load_result.empty()) {
		LogError("{}", load_result);
		return 1;
	}

	WorldShortName = Config::get()->WorldShortName;

	LogInfo(
	    "Connecting to DB {0}@{1}:{2}",
	    Config::get()->DatabaseUsername.c_str(),
	    Config::get()->DatabaseHost.c_str(),
	    Config::get()->DatabasePort);
	if (!database.Connect(
	        Config::get()->DatabaseHost.c_str(),
	        Config::get()->DatabaseUsername.c_str(),
	        Config::get()->DatabasePassword.c_str(),
	        Config::get()->DatabaseDB.c_str(),
	        Config::get()->DatabasePort)) {
		LogInfo("Cannot continue without a database connection.");
		return 1;
	}

	LogSys.SetDatabase(&database)
	    ->LoadLogDatabaseSettings()
	    ->StartFileLogs();

	char tmp[64];

	if (database.GetVariable("RuleSet", tmp, sizeof(tmp) - 1)) {
		LogInfo("Loading rule set '[{0}]'", tmp);
		if (!RuleManager::Instance()->LoadRules(&database, tmp)) {
			LogInfo("Failed to load ruleset '[{0}]', falling back to defaults.", tmp);
		}
	} else {
		if (!RuleManager::Instance()->LoadRules(&database, "default")) {
			LogInfo("No rule set configured, using default rules");
		}
	}

	g_Clientlist = new Clientlist();

	ChannelList = new ChatChannelList();

	database.LoadChatChannels();

	if (signal(SIGINT, CatchSignal) == SIG_ERR) {
		LogInfo("Could not set signal handler");
		return 1;
	}
	if (signal(SIGTERM, CatchSignal) == SIG_ERR) {
		LogInfo("Could not set signal handler");
		return 1;
	}

	worldserver = new WorldServer;

	worldserver->Connect();

	auto loop_fn = [&](EQ::Timer *t) {
		Timer::SetCurrentTime();

		if (!RunLoops) {
			EQ::EventLoop::Get().Shutdown();
			return;
		}

		g_Clientlist->Process();

		if (ChannelListProcessTimer.Check()) {
			ChannelList->Process();
		}

		if (ClientConnectionPruneTimer.Check()) {
			g_Clientlist->CheckForStaleConnectionsAll();
		}

		if (InterserverTimer.Check()) {
			if (worldserver->TryReconnect() && (!worldserver->Connected()))
				worldserver->AsyncConnect();
		}
		worldserver->Process();

		timeout_manager.CheckTimeouts();
	};

	EQ::Timer process_timer(loop_fn);
	process_timer.Start(32, true);

	EQ::EventLoop::Get().Run();

	ChannelList->RemoveAllChannels();

	g_Clientlist->CloseAllConnections();

	LogSys.CloseFileLogs();
}

void UpdateWindowTitle(char *iNewTitle) {
#ifdef _WINDOWS
	std::string title;
	if (iNewTitle) {
		title = StringFormat("UCS: %s", iNewTitle);
	} else {
		title = "UCS";
	}
	SetConsoleTitle(title.c_str());
#endif
}
