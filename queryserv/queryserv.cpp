#include "../common/global_define.h"
#include "../common/eqemu_logsys.h"
#include "../common/opcodemgr.h"
#include "../common/eq_stream_factory.h"
#include "../common/rulesys.h"
#include "../common/servertalk.h"
#include "../common/platform.h"
#include "../common/crash.h"
#include "../common/strings.h"
#include "../common/event/timer.h"
#include "database.h"
#include "queryservconfig.h"
#include "worldserver.h"
#include <list>
#include <signal.h>

volatile bool RunLoops = true;

TimeoutManager timeout_manager;
Database database;
std::string WorldShortName;
const queryservconfig* Config;
WorldServer* worldserver = 0;
EQEmuLogSys LogSys;

void CatchSignal(int sig_num) {
	RunLoops = false;
	if (worldserver)
		worldserver->Disconnect();
}

int main() {
	RegisterExecutablePlatform(ExePlatformQueryServ);
	LogSys.LoadLogSettingsDefaults();
	set_exception_handler();
	Timer InterserverTimer(INTERSERVER_TIMER);  // does auto-reconnect

	LogInfo("Starting EQMacEmu QueryServ.");
	if (!queryservconfig::LoadConfig()) {
		LogInfo("Loading server configuration failed.");
		return 1;
	}

	Config = queryservconfig::get();
	WorldShortName = Config->ShortName;

	LogInfo("Connecting to MySQL...");

	/* MySQL Connection */
	if (!database.Connect(
	        Config->QSDatabaseHost.c_str(),
	        Config->QSDatabaseUsername.c_str(),
	        Config->QSDatabasePassword.c_str(),
	        Config->QSDatabaseDB.c_str(),
	        Config->QSDatabasePort)) {
		LogInfo("Cannot continue without a database connection.");
		return 1;
	}

	/* Bootstrap Database updates */
	if (!database.DBSetup()) {
		return 1;
	}

	LogSys.SetDatabase(&database)
	    ->LoadLogDatabaseSettings()
	    ->StartFileLogs();

	if (signal(SIGINT, CatchSignal) == SIG_ERR) {
		LogInfo("Could not set signal handler");
		return 1;
	}
	if (signal(SIGTERM, CatchSignal) == SIG_ERR) {
		LogInfo("Could not set signal handler");
		return 1;
	}

	/* Initial Connection to Worldserver */
	worldserver = new WorldServer;
	worldserver->Connect();

	bool worldwasconnected = worldserver->Connected();
	/* Load Looking For Guild Manager */
	auto loop_fn = [&](EQ::Timer* t) {
		Timer::SetCurrentTime();

		if (!RunLoops) {
			EQ::EventLoop::Get().Shutdown();
			return;
		}

		if (worldserver->Connected()) {
			worldwasconnected = true;
		} else {
			worldwasconnected = false;
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

	LogSys.CloseFileLogs();
}

void UpdateWindowTitle(char* iNewTitle) {
#ifdef _WINDOWS
	std::string title;
	if (iNewTitle) {
		title = StringFormat("QueryServ: %s", iNewTitle);
	} else {
		title = "QueryServ";
	}
	SetConsoleTitle(title.c_str());
#endif
}
