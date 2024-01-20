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
	LogInfo("Starting Login v{}", VERSION);

	auto load_result = Config::LoadConfig();
	if (!load_result.empty()) {
		LogError("{}", load_result);
		return 1;
	}

	LogSys.log_settings[Logs::Error].log_to_console = Logs::General;

	LogInfo(
	    "Connecting to DB {0}@{1}:{2}",
	    Config::get()->DatabaseUsername.c_str(),
	    Config::get()->DatabaseHost.c_str(),
	    Config::get()->DatabasePort);
	server.db = (Database*)new Database(
	    Config::get()->DatabaseUsername,
	    Config::get()->DatabasePassword,
	    Config::get()->DatabaseHost,
	    Config::get()->DatabasePort,
	    Config::get()->DatabaseDB);
	LogSys.SetDatabase(server.db);
	LogSys.LoadLogDatabaseSettings();
	LogSys.StartFileLogs(fmt::format("login_{}.log", getpid()));

	if (Config::get()->IsLoginPacketDumpEnabled) {
		LogSys.log_settings[Logs::Netcode].log_to_console = Logs::General;
		LogSys.log_settings[Logs::Netcode].is_category_enabled = true;
		LogSys.log_settings[Logs::PacketServerClientWithDump].log_to_console = Logs::General;
		LogSys.log_settings[Logs::PacketServerClientWithDump].is_category_enabled = true;
	}

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
	SetConsoleTitle(L"RyxEmu Login Server");
#else
	SetConsoleTitle("RyxEmu Login Server");
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
