#include "../common/global_define.h"
#include "../common/types.h"
#include "../common/opcodemgr.h"
#include "../common/eq_stream_factory.h"
#include "../common/timer.h"
#include "../common/platform.h"
#include "../common/crash.h"
#include "../common/eqemu_logsys.h"
#include "../common/event/timer.h"
#include "../common/config.h"

#include "eq_crypto.h"
#include "login_server.h"
#include <time.h>
#include <stdlib.h>
#include <string>
#include <sstream>

TimeoutManager timeout_manager;
LoginServer server;
EQEmuLogSys LogSys;
EQCrypto eq_crypto;
bool run_server = true;

void CatchSignal(int sig_num) {
}

int main() {
	RegisterExecutablePlatform(ExePlatformLogin);
	LogSys.LoadLogSettingsDefaults();
	set_exception_handler();
	LogInfo("Starting LoginServer v{}", VERSION);

	auto load_result = Config::LoadConfig();
	if (!load_result.empty()) {
		LogError("{}", load_result);
		return 1;
	}

	LogSys.log_settings[Logs::Error].log_to_console = Logs::General;

	server.db = (Database*)new Database(
	    Config::get()->DatabaseUsername,
	    Config::get()->DatabasePassword,
	    Config::get()->DatabaseHost,
	    Config::get()->DatabasePort,
	    Config::get()->DatabaseDB);

	// create our server manager.
	server.server_manager = new ServerManager();
	if (!server.server_manager) {
		// We can't run without a server manager, cleanup and exit.
		LogError("Server Manager Failed to Start");

		LogInfo("Database System Shutdown");
		delete server.db;
		return 1;
	}

	// create our client manager.
	server.client_manager = new ClientManager();
	if (!server.client_manager) {
		// We can't run without a client manager, cleanup and exit.
		LogError("Client Manager Failed to Start");
		LogInfo("Server Manager Shutdown");
		delete server.server_manager;

		LogInfo("Database System Shutdown");
		delete server.db;
		return 1;
	}

#ifdef WIN32
#ifdef UNICODE
	SetConsoleTitle(L"EQEmu Login Server");
#else
	SetConsoleTitle("EQEmu Login Server");
#endif
#endif

	auto loop_fun = [&](EQ::Timer* t) {
		Timer::SetCurrentTime();

		if (!run_server) {
			EQ::EventLoop::Get().Shutdown();
			return;
		}

		server.client_manager->Process();
		server.server_manager->Process();
		timeout_manager.CheckTimeouts();
	};

	EQ::Timer proccess_timer(loop_fun);
	proccess_timer.Start(32, true);

	EQ::EventLoop::Get().Run();

	LogInfo("Server Shutdown");

	LogInfo("Client Manager Shutdown");
	delete server.client_manager;

	LogInfo("Server Manager Shutdown");
	delete server.server_manager;

	LogInfo("Database System Shutdown");
	delete server.db;

	LogSys.CloseFileLogs();

	return 0;
}
