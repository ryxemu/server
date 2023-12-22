#ifndef __EQEmuConfig_H
#define __EQEmuConfig_H

#include "linked_list.h"
#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>
#ifndef _WIN32
// this doesn't appear to affect linux-based systems..need feedback for _WIN64
#include <fmt/format.h>
#endif
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

struct LoginConfig {
	std::string LoginIP;
	std::string LoginUsername;
	std::string LoginPassword;
	uint16 LoginPort;
	uint8 LoginType;
};

class Config {
   public:
	bool WorldUpdateStats;                     // world temporary variable (not loaded from config) // TODO: add to a proper state system
	bool IsWorldLocked;                        // world.is_locked, Is the world locked, not allowing new players to log in
	std::string WorldShortName;                // world.short_name
	std::string WorldLongName;                 // world.long_name
	std::string WorldWANIP;                    // world.wan_ip
	uint16 WorldWANPort;                       // world.wan_port
	std::string WorldLANIP;                    // world.lan_ip
	uint16 WorldLANPort;                       // world.lan_port
	int32 WorldMaxClients;                     // world.max_players, maximum number of players allowed to log in
	LinkedList<LoginConfig *> WorldLoginList;  // world.login_list, list of login servers to connect to
	bool IsWorldTelnetEnabled;                 // world.telnet_enabled, is telnet enabled
	std::string WorldTelnetIP;                 // world.telnet_ip
	uint16 WorldTelnetPort;                    // world.telnet_port
	std::string WorldSharedKey;                // world.shared_key
	uint16 WorldZonePortMin;                   // world.zone_port_min
	uint16 WorldZonePortMax;                   // world.zone_port_max
	uint16 WorldDefaultStatus;                 // world.default_status

	std::string LoginPlayerIP;                     // login.player_ip
	uint16 LoginPlayerPort;                        // login.lan_port
	std::string LoginWorldIP;                      // login.world_ip
	uint16 LoginWorldPort;                         // login.world_port
	std::string LoginUsername;                     // login.username
	std::string LoginPassword;                     // login.password
	bool IsLoginAutoCreateAccountsEnabled;         // login.is_auto_create_accounts_enabled
	bool IsLoginAutoAccountActivated;              // login.is_auto_account_activated
	bool IsLoginFailureLogged;                     // login.is_login_failure_logged
	bool IsLoginIPLogged;                          // login.is_login_ip_logged
	bool IsLoginUnregisteredAllowed;               // login.is_unregistered_allowed
	bool IsLoginDuplicateServerRejected;           // login.is_duplicate_server_rejected
	bool IsLoginTraceEnabled;                      // login.is_trace_enabled
	bool IsLoginTraceWorldEnabled;                 // login.is_trace_world_enabled
	bool IsLoginPacketInLoggingEnabled;            // login.is_packet_in_logging_enabled
	bool IsLoginPacketOutLoggingEnabled;           // login.is_packet_out_logging_enabled
	std::string LoginSalt;                         // login.salt
	std::string LoginSecurityPlugin;               // login.security.plugin
	int32 LoginSecurityMode;                       // login.security.mode
	std::string LoginAccessLogTable;               // login.schema.access_log_table
	std::string LoginAccountTable;                 // login.schema.account_table
	std::string LoginWorldRegistrationTable;       // login.schema.world_registration_table
	std::string LoginWorldAdminRegistrationTable;  // login.schema.world_admin_registration_table
	std::string LoginWorldServerTypeTable;         // login.schema.world_server_type_table
	std::string LoginLoginServerSettingTable;      // login.schema.loginserver_setting_table

	std::string UCSIP;
	uint16 UCSPort;

	// From <database/>
	std::string DatabaseHost;
	std::string DatabaseUsername;
	std::string DatabasePassword;
	std::string DatabaseDB;
	uint16 DatabasePort;

	// From <qsdatabase> // QueryServ
	std::string QSDatabaseHost;
	std::string QSDatabaseUsername;
	std::string QSDatabasePassword;
	std::string QSDatabaseDB;
	uint16 QSDatabasePort;

	// From dir
	std::string DirMap;
	std::string DirQuest;
	std::string DirLuaModule;
	std::string DirPatch;
	std::string DirSharedMem;
	std::string DirLog;

	std::string ZoneIP;
	uint16 ZonePort;  // temporary variable (not loaded from config) of what port zone is using // TODO: add to a proper state system
	std::string ZoneWorldIP;
	uint16 ZoneWorldPort;

	//	uint16 DynamicCount;
	//	map<string,uint16> StaticZones;
   protected:
	static Config *_config;
	YAML::Node _root;
	static std::string ConfigFile;

	void parse_config();

	Config() {}
	virtual ~Config() {}

   public:
	// Produce a const singleton
	static const Config *get() {
		LoadConfig();
		return (_config);
	}

	// Load the config
	static std::string LoadConfig() {
		if (_config != nullptr) return "";

		_config = new Config;
		return parseFile();
	}

	// Load config file and parse data
	static std::string parseFile() {
		try {
			_config->_root = YAML::LoadFile(Config::ConfigFile);
			_config->parse_config();
		} catch (YAML::BadFile &e) {
			if (e.mark.line == -1) {
				return fmt::format("Failed opening config: {}. This likely means the file was not found at {}/config.yaml", e.msg, CurrentWorkingDirectory());
			}
			return fmt::format("Failed opening config: {}:{}: {}", e.mark.line, e.mark.column, e.msg);
		} catch (YAML::RepresentationException &e) {
			return fmt::format("Failed with {}:{}:{}: {}", Config::ConfigFile, e.mark.line, e.mark.column, e.msg);
		} catch (YAML::ParserException &e) {
			return fmt::format("Failed parsing {}:{}:{}: {}", Config::ConfigFile, e.mark.line, e.mark.column, e.msg);
		} catch (YAML::Exception &e) {
			return fmt::format("Failed loading {}: {}", Config::ConfigFile, e.msg);
		} catch (std::exception &e) {
			return "Failed during " + Config::ConfigFile + ": " + e.what();
		}
		return "";
	}

	// SetIsLocked is used to set the world lock status
	static void SetIsLocked(bool value) {
		if (_config == nullptr) {
			return;
		}
		_config->IsWorldLocked = value;
		return;
	}

	static void SetZonePort(uint16 value) {
		if (_config == nullptr) {
			return;
		}
		_config->ZonePort = value;
		return;
	}

	static void SetWorldWANIP(std::string value) {
		if (_config == nullptr) {
			return;
		}
		_config->WorldWANIP = value;
		return;
	}

	static void SetWorldLANIP(std::string value) {
		if (_config == nullptr) {
			return;
		}
		_config->WorldLANIP = value;
		return;
	}

	// Returns the Current Working Directory that the program was started from
	static std::string CurrentWorkingDirectory() {
		char buff[FILENAME_MAX];
		GetCurrentDir(buff, FILENAME_MAX);
		std::string current_working_dir(buff);
		return current_working_dir;
	}
};

#endif