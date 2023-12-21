#define RYML_SINGLE_HDR_DEFINE_NOW
#define RYML_USE_ASSERT
#include <yaml-cpp/yaml.h>

#include "../common/global_define.h"
#include "config.h"
#include "misc_functions.h"

#include <iostream>
#include <sstream>

std::string Config::ConfigFile = "config.yaml";
Config *Config::_config = nullptr;

void Config::parse_config() {
	if (_root["world"].IsNull()) {
		throw std::runtime_error("Missing world section in config.ymaml");
	}
	std::string value;

	IsWorldLocked = false;
	if (!_root["world"]["is_locked"].IsNull()) {
		if (_root["world"]["is_locked"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.is_locked must be a boolean");
		}
		IsWorldLocked = _root["world"]["is_locked"].as<bool>();
	}

	if (_root["world"]["short_name"].IsNull()) {
		throw std::runtime_error("Missing world.short_name in config.yaml");
	}
	if (_root["world"]["short_name"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("world.short_name must be a string");
	}
	WorldShortName = _root["world"]["short_name"].as<std::string>();

	if (_root["world"]["long_name"].IsNull()) {
		throw std::runtime_error("Missing world.long_name in config.yaml");
	}
	if (_root["world"]["long_name"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("world.long_name must be a string");
	}
	WorldLongName = _root["world"]["long_name"].as<std::string>();

	WorldWANIP = "127.0.0.1";
	if (!_root["world"]["wan_ip"].IsNull()) {
		if (_root["world"]["wan_ip"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.wan_ip must be a string");
		}
		WorldWANIP = _root["world"]["wan_ip"].as<std::string>();
	}

	WorldWANPort = 9000;
	if (!_root["world"]["wan_port"].IsNull()) {
		if (_root["world"]["wan_port"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.wan_port must be an integer");
		}
		WorldWANPort = _root["world"]["wan_port"].as<uint16_t>();
	}

	WorldLANIP = "127.0.0.1";
	if (!_root["world"]["lan_ip"].IsNull()) {
		if (_root["world"]["lan_ip"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.lan_ip must be a string");
		}
		WorldLANIP = _root["world"]["lan_ip"].as<std::string>();
	}

	WorldLANPort = 9000;
	if (!_root["world"]["lan_port"].IsNull()) {
		if (_root["world"]["lan_port"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.lan_port must be an integer");
		}
		WorldWANPort = _root["world"]["lan_port"].as<uint16_t>();
	}

	WorldMaxClients = -1;
	if (!_root["world"]["max_clients"].IsNull()) {
		if (_root["world"]["max_clients"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.max_clients must be an integer");
		}
		WorldMaxClients = _root["world"]["max_clients"].as<int32_t>();
	}

	WorldSharedKey = "pleasegenerateakey";
	if (!_root["world"]["shared_key"].IsNull()) {
		if (_root["world"]["shared_key"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.shared_key must be a string");
		}
		WorldSharedKey = _root["world"]["shared_key"].as<std::string>();
	}

	WorldZonePortMin = 7000;
	if (!_root["world"]["zone_port_min"].IsNull()) {
		if (_root["world"]["zone_port_min"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.zone_port_min must be an integer");
		}
		WorldZonePortMin = _root["world"]["zone_port_min"].as<uint16_t>();
	}

	WorldZonePortMax = 7400;
	if (!_root["world"]["zone_port_max"].IsNull()) {
		if (_root["world"]["zone_port_max"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.zone_port_max must be an integer");
		}
		WorldZonePortMax = _root["world"]["zone_port_max"].as<uint16_t>();
	}

	WorldDefaultStatus = 0;
	if (!_root["world"]["default_status"].IsNull()) {
		if (_root["world"]["default_status"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.default_status must be an integer");
		}
		WorldDefaultStatus = _root["world"]["default_status"].as<uint16_t>();
	}

	if (_root["world"]["login"].IsNull()) {
		throw std::runtime_error("Missing world.login elements in config.yaml");
	}

	WorldLoginList.Clear();
	for (std::size_t i = 0; i < _root["world"]["login"].size(); i++) {
		auto login_config = new LoginConfig;

		auto node = _root["world"]["login"][i];
		if (node.IsNull()) {
			throw std::runtime_error("Missing world.login element in config.yaml");
		}
		if (node["ip"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("Invalid world.login.ip must be a string");
		}
		login_config->LoginIP = node["ip"].as<std::string>();
		if (node["port"].IsNull()) {
			throw std::runtime_error("Missing world.login.port in config.yaml");
		}
		if (node["port"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("Invalid world.login.port must be an integer");
		}
		login_config->LoginPort = node["port"].as<uint16>();

		if (node["username"].IsNull()) {
			throw std::runtime_error("Missing world.login.username in config.yaml");
		}
		if (node["username"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("Invalid world.login.username must be a string");
		}
		login_config->LoginUsername = node["username"].as<std::string>();

		if (node["password"].IsNull()) {
			throw std::runtime_error("Missing world.login.password in config.yaml");
		}
		if (node["password"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("Invalid world.login.password must be a string");
		}
		login_config->LoginPassword = node["password"].as<std::string>();

		if (node["type"].IsNull()) {
			throw std::runtime_error("Missing world.login.type in config.yaml");
		}
		if (node["type"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("Invalid world.login.type must be an integer");
		}
		login_config->LoginType = node["type"].as<uint8>();

		WorldLoginList.Insert(login_config);
	}

	if (_root["world"]["telnet"].IsNull()) {
		throw std::runtime_error("Missing world.telnet in config.yaml");
	}

	IsWorldTelnetEnabled = false;
	if (!_root["world"]["telnet"]["is_enabled"].IsNull()) {
		if (_root["world"]["telnet"]["is_enabled"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.telnet.is_enabled must be a boolean");
		}
		IsWorldTelnetEnabled = _root["world"]["telnet"]["is_enabled"].as<bool>();
	}

	WorldTelnetIP = "127.0.0.1";
	if (!_root["world"]["telnet"]["ip"].IsNull()) {
		if (_root["world"]["telnet"]["ip"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.telnet.ip must be a string");
		}
		WorldTelnetIP = _root["world"]["telnet"]["ip"].as<std::string>();
	}

	WorldTelnetPort = 9000;
	if (!_root["world"]["telnet"]["port"].IsNull()) {
		if (_root["world"]["telnet"]["port"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.telnet.port must be an integer");
		}
		WorldTelnetPort = _root["world"]["telnet"]["port"].as<uint16_t>();
	}

	LoginPlayerIP = "127.0.0.1";
	if (!_root["login"]["player_ip"].IsNull()) {
		if (_root["login"]["player_ip"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login.player_ip must be a string");
		}
		LoginPlayerIP = _root["login"]["player_ip"].as<std::string>();
	}

	LoginPlayerPort = 5998;
	if (!_root["login"]["player_port"].IsNull()) {
		if (_root["login"]["player_port"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login.player_port must be an integer");
		}
		LoginPlayerPort = _root["login"]["player_port"].as<uint16_t>();
	}

	LoginWorldIP = "127.0.0.1";
	if (!_root["login"]["world_ip"].IsNull()) {
		if (_root["login"]["world_ip"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login.world_ip must be a string");
		}
		LoginWorldIP = _root["login"]["world_ip"].as<std::string>();
	}

	LoginWorldPort = 5998;
	if (!_root["login"]["world_port"].IsNull()) {
		if (_root["login"]["world_port"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login.world_port must be an integer");
		}
		LoginWorldPort = _root["login"]["world_port"].as<uint16_t>();
	}

	if (_root["login"]["username"].IsNull()) {
		throw std::runtime_error("Missing login.username in config.yaml");
	}
	if (_root["login"]["username"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("login.username must be a string");
	}
	LoginUsername = _root["login"]["username"].as<std::string>();

	if (_root["login"]["password"].IsNull()) {
		throw std::runtime_error("Missing login.password in config.yaml");
	}
	if (_root["login"]["password"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("login.password must be a string");
	}
	LoginPassword = _root["login"]["password"].as<std::string>();

	IsLoginAutoCreateAccountsEnabled = false;
	if (!_root["login"]["is_auto_create_accounts_enabled"].IsNull()) {
		if (_root["login"]["is_auto_create_accounts_enabled"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login.is_auto_create_accounts_enabled must be a boolean");
		}
		IsLoginAutoCreateAccountsEnabled = _root["login"]["is_auto_create_accounts_enabled"].as<bool>();
	}

	IsLoginAutoAccountActivated = false;
	if (!_root["login"]["is_auto_account_activated"].IsNull()) {
		if (_root["login"]["is_auto_account_activated"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login.is_auto_account_activated must be a boolean");
		}
		IsLoginAutoAccountActivated = _root["login"]["is_auto_account_activated"].as<bool>();
	}

	IsLoginFailureLogged = false;
	if (!_root["login"]["is_login_failure_logged"].IsNull()) {
		if (_root["login"]["is_login_failure_logged"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login.is_login_failure_logged must be a boolean");
		}
		IsLoginFailureLogged = _root["login"]["is_login_failure_logged"].as<bool>();
	}

	IsLoginIPLogged = false;
	if (!_root["login"]["is_login_ip_logged"].IsNull()) {
		if (_root["login"]["is_login_ip_logged"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login.is_login_ip_logged must be a boolean");
		}
		IsLoginIPLogged = _root["login"]["is_login_ip_logged"].as<bool>();
	}

	IsLoginUnregisteredAllowed = false;
	if (!_root["login"]["is_unregistered_allowed"].IsNull()) {
		if (_root["login"]["is_unregistered_allowed"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login.is_unregistered_allowed must be a boolean");
		}
		IsLoginUnregisteredAllowed = _root["login"]["is_unregistered_allowed"].as<bool>();
	}

	IsLoginDuplicateServerRejected = false;
	if (!_root["login"]["is_duplicate_server_rejected"].IsNull()) {
		if (_root["login"]["is_duplicate_server_rejected"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login.is_duplicate_server_rejected must be a boolean");
		}
		IsLoginDuplicateServerRejected = _root["login"]["is_duplicate_server_rejected"].as<bool>();
	}

	IsLoginTraceEnabled = false;
	if (!_root["login"]["is_trace_enabled"].IsNull()) {
		if (_root["login"]["is_trace_enabled"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login.is_trace_enabled must be a boolean");
		}
		IsLoginTraceEnabled = _root["login"]["is_trace_enabled"].as<bool>();
	}

	IsLoginTraceWorldEnabled = false;
	if (!_root["login"]["is_trace_world_enabled"].IsNull()) {
		if (_root["login"]["is_trace_world_enabled"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login.is_trace_world_enabled must be a boolean");
		}
		IsLoginTraceWorldEnabled = _root["login"]["is_trace_world_enabled"].as<bool>();
	}

	IsLoginPacketInLoggingEnabled = false;
	if (!_root["login"]["is_packet_in_logging_enabled"].IsNull()) {
		if (_root["login"]["is_packet_in_logging_enabled"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login.is_packet_in_logging_enabled must be a boolean");
		}
		IsLoginPacketInLoggingEnabled = _root["login"]["is_packet_in_logging_enabled"].as<bool>();
	}

	IsLoginPacketOutLoggingEnabled = false;
	if (!_root["login"]["is_packet_out_logging_enabled"].IsNull()) {
		if (_root["login"]["is_packet_out_logging_enabled"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login.is_packet_out_logging_enabled must be a boolean");
		}
		IsLoginPacketOutLoggingEnabled = _root["login"]["is_packet_out_logging_enabled"].as<bool>();
	}

	if (_root["login"]["salt"].IsNull()) {
		throw std::runtime_error("Missing login.salt in config.yaml");
	}
	if (_root["login"]["salt"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("login.salt must be a string");
	}

	LoginSalt = _root["login"]["salt"].as<std::string>();

	if (_root["login"]["security"]["plugin"].IsNull()) {
		throw std::runtime_error("Missing login.security.plugin in config.yaml");
	}
	if (_root["login"]["security"]["plugin"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("login.security.plugin must be a string");
	}
	LoginSecurityPlugin = _root["login"]["security"]["plugin"].as<std::string>();

	if (_root["login"]["security"]["mode"].IsNull()) {
		throw std::runtime_error("Missing login.security.mode in config.yaml");
	}
	if (_root["login"]["security"]["mode"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("login.security.mode must be an integer");
	}
	LoginSecurityMode = _root["login"]["security"]["mode"].as<int32_t>();

	if (_root["login"]["schema"]["access_log_table"].IsNull()) {
		throw std::runtime_error("Missing login.schema.access_log_table in config.yaml");
	}
	if (_root["login"]["schema"]["access_log_table"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("login.schema.access_log_table must be a string");
	}
	LoginAccessLogTable = _root["login"]["schema"]["access_log_table"].as<std::string>();

	if (_root["login"]["schema"]["account_table"].IsNull()) {
		throw std::runtime_error("Missing login.schema.account_table in config.yaml");
	}
	if (_root["login"]["schema"]["account_table"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("login.schema.account_table must be a string");
	}
	LoginAccountTable = _root["login"]["schema"]["account_table"].as<std::string>();

	if (_root["login"]["schema"]["world_registration_table"].IsNull()) {
		throw std::runtime_error("Missing login.schema.world_registration_table in config.yaml");
	}
	if (_root["login"]["schema"]["world_registration_table"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("login.schema.world_registration_table must be a string");
	}
	LoginWorldRegistrationTable = _root["login"]["schema"]["world_registration_table"].as<std::string>();

	if (_root["login"]["schema"]["world_admin_registration_table"].IsNull()) {
		throw std::runtime_error("Missing login.schema.world_admin_registration_table in config.yaml");
	}
	if (_root["login"]["schema"]["world_admin_registration_table"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("login.schema.world_admin_registration_table must be a string");
	}
	LoginWorldAdminRegistrationTable = _root["login"]["schema"]["world_admin_registration_table"].as<std::string>();

	if (_root["login"]["schema"]["world_server_type_table"].IsNull()) {
		throw std::runtime_error("Missing login.schema.world_server_type_table in config.yaml");
	}
	if (_root["login"]["schema"]["world_server_type_table"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("login.schema.world_server_type_table must be a string");
	}
	LoginWorldServerTypeTable = _root["login"]["schema"]["world_server_type_table"].as<std::string>();

	if (_root["login"]["schema"]["loginserver_setting_table"].IsNull()) {
		throw std::runtime_error("Missing login.schema.loginserver_setting_table in config.yaml");
	}
	if (_root["login"]["schema"]["loginserver_setting_table"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("login.schema.loginserver_setting_table must be a string");
	}
	LoginLoginServerSettingTable = _root["login"]["schema"]["loginserver_setting_table"].as<std::string>();

	UCSIP = "0.0.0.0";
	if (!_root["ucs"]["ip"].IsNull()) {
		if (_root["ucs"]["ip"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("ucs.ip must be a string");
		}

		UCSIP = _root["ucs"]["ip"].as<std::string>();
	}

	UCSPort = 7778;
	if (!_root["ucs"]["port"].IsNull()) {
		if (_root["ucs"]["port"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("ucs.port must be an integer");
		}
		UCSPort = _root["ucs"]["port"].as<uint16_t>();
	}

	if (!_root["database"]["host"].IsNull()) {
		if (_root["database"]["host"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("database.host must be a string");
		}
		DatabaseHost = _root["database"]["host"].as<std::string>();
	} else {
		throw std::runtime_error("Missing database.host in config.yaml");
	}

	if (!_root["database"]["username"].IsNull()) {
		if (_root["database"]["username"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("database.username must be a string");
		}
		DatabaseUsername = _root["database"]["username"].as<std::string>();
	} else {
		throw std::runtime_error("Missing database.username in config.yaml");
	}

	if (!_root["database"]["password"].IsNull()) {
		if (_root["database"]["password"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("database.password must be a string");
		}
		DatabasePassword = _root["database"]["password"].as<std::string>();
	} else {
		throw std::runtime_error("Missing database.password in config.yaml");
	}

	if (!_root["database"]["db"].IsNull()) {
		if (_root["database"]["db"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("database.db must be a string");
		}
		DatabaseDB = _root["database"]["db"].as<std::string>();
	} else {
		throw std::runtime_error("Missing database.db in config.yaml");
	}

	if (!_root["database"]["port"].IsNull()) {
		if (_root["database"]["port"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("database.port must be an integer");
		}
		DatabasePort = _root["database"]["port"].as<uint16_t>();
	} else {
		throw std::runtime_error("Missing database.port in config.yaml");
	}

	if (!_root["query_serv"]["host"].IsNull()) {
		if (_root["query_serv"]["host"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("query_serv.host must be a string");
		}
		QSDatabaseHost = _root["query_serv"]["host"].as<std::string>();
	} else {
		throw std::runtime_error("Missing query_serv.host in config.yaml");
	}

	if (!_root["query_serv"]["username"].IsNull()) {
		if (_root["query_serv"]["username"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("query_serv.username must be a string");
		}
		QSDatabaseUsername = _root["query_serv"]["username"].as<std::string>();
	} else {
		throw std::runtime_error("Missing query_serv.username in config.yaml");
	}

	if (!_root["query_serv"]["password"].IsNull()) {
		if (_root["query_serv"]["password"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("query_serv.password must be a string");
		}
		QSDatabasePassword = _root["query_serv"]["password"].as<std::string>();
	} else {
		throw std::runtime_error("Missing query_serv.password in config.yaml");
	}

	if (!_root["query_serv"]["db"].IsNull()) {
		if (_root["query_serv"]["db"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("query_serv.db must be a string");
		}
		QSDatabaseDB = _root["query_serv"]["db"].as<std::string>();
	} else {
		throw std::runtime_error("Missing query_serv.db in config.yaml");
	}

	if (!_root["query_serv"]["port"].IsNull()) {
		if (_root["query_serv"]["port"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("query_serv.port must be an integer");
		}
		QSDatabasePort = _root["query_serv"]["port"].as<uint16_t>();
	} else {
		throw std::runtime_error("Missing query_serv.port in config.yaml");
	}

	ZoneIP = "0.0.0.0";
	if (!_root["zone"]["ip"].IsNull()) {
		if (_root["zone"]["ip"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("zone.ip must be a string");
		}
		ZoneIP = _root["zone"]["ip"].as<std::string>();
	}

	ZoneWorldIP = "127.0.0.1";
	if (!_root["zone"]["world_ip"].IsNull()) {
		if (_root["zone"]["world_ip"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("zone.world_ip must be a string");
		}
		ZoneWorldIP = _root["zone"]["world_ip"].as<std::string>();
	}
	ZoneWorldPort = 9000;
	if (!_root["zone"]["world_port"].IsNull()) {
		if (_root["zone"]["world_port"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("zone.world_port must be an integer");
		}
		ZoneWorldPort = _root["zone"]["world_port"].as<uint16_t>();
	}

	if (!_root["dir"]["maps"].IsNull()) {
		if (_root["dir"]["maps"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("dir.maps must be a string");
		}
		MapDir = _root["dir"]["maps"].as<std::string>();
	} else {
		MapDir = "maps/";
	}

	if (!_root["dir"]["logs"].IsNull()) {
		if (_root["dir"]["logs"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("dir.logs must be a string");
		}
		LogDir = _root["dir"]["logs"].as<std::string>();
	} else {
		LogDir = "logs/";
	}

	if (!_root["dir"]["lua_modules"].IsNull()) {
		if (_root["dir"]["lua_modules"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("dir.lua_modules must be a string");
		}
		LuaModuleDir = _root["dir"]["lua_modules"].as<std::string>();
	} else {
		LuaModuleDir = "quests/lua_modules/";
	}

	if (!_root["dir"]["quests"].IsNull()) {
		if (_root["dir"]["quests"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("dir.quests must be a string");
		}
		QuestDir = _root["dir"]["quests"].as<std::string>();
	} else {
		QuestDir = "quests/";
	}

	if (!_root["dir"]["patches"].IsNull()) {
		if (_root["dir"]["patches"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("dir.patches must be a string");
		}
		PatchDir = _root["dir"]["patches"].as<std::string>();
	} else {
		PatchDir = "assets/patches/";
	}

	if (!_root["dir"]["shared_memory"].IsNull()) {
		if (_root["dir"]["shared_memory"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("dir.shared_memory must be a string");
		}
		SharedMemDir = _root["dir"]["shared_memory"].as<std::string>();
	} else {
		SharedMemDir = "shared/";
	}
}