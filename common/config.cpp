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

	if (_root["world"]["short_name"].IsNull()) {
		throw std::runtime_error("Missing world.short_name in config.yaml");
	}
	if (_root["world"]["short_name"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("world.short_name must be a string");
	}
	ShortName = _root["world"]["short_name"].as<std::string>();

	if (_root["world"]["long_name"].IsNull()) {
		throw std::runtime_error("Missing world.long_name in config.yaml");
	}
	if (_root["world"]["long_name"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("world.long_name must be a string");
	}
	LongName = _root["world"]["long_name"].as<std::string>();

	if (_root["world"]["wan_address"].IsNull()) {
		throw std::runtime_error("Missing world.wan_address in config.yaml");
	}
	if (_root["world"]["wan_address"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("world.wan_address must be a string");
	}
	WorldAddress = _root["world"]["wan_address"].as<std::string>();

	if (_root["world"]["lan_address"].IsNull()) {
		throw std::runtime_error("Missing world.lan_address in config.yaml");
	}
	if (_root["world"]["lan_address"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("world.lan_address must be a string");
	}
	LocalAddress = _root["world"]["lan_address"].as<std::string>();

	if (!_root["world"]["max_clients"].IsNull()) {
		if (_root["world"]["max_clients"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.max_clients must be an integer");
		}
		MaxClients = _root["world"]["max_clients"].as<int32_t>();
	}

	if (_root["world"]["shared_key"].IsNull()) {
		throw std::runtime_error("Missing world.shared_key in config.yaml");
	}
	if (_root["world"]["shared_key"].Type() != YAML::NodeType::Scalar) {
		throw std::runtime_error("world.shared_key must be a string");
	}
	SharedKey = _root["world"]["shared_key"].as<std::string>();

	if (!_root["world"]["is_locked"].IsNull()) {
		if (_root["world"]["is_locked"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.is_locked must be a boolean");
		}
		IsLocked = _root["world"]["is_locked"].as<bool>();
	} else {
		IsLocked = false;
	}

	if (!_root["world"]["intranet_ip"].IsNull()) {
		if (_root["world"]["intranet_ip"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.intranet_ip must be a string");
		}
		WorldIP = _root["world"]["intranet_ip"].as<std::string>();
	} else {
		WorldIP = "0.0.0.0";
	}

	if (!_root["world"]["intranet_port"].IsNull()) {
		if (_root["world"]["intranet_port"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("world.intranet_port must be a number");
		}
		WorldTCPPort = _root["world"]["intranet_port"].as<uint16_t>();
	} else {
		WorldTCPPort = 0;
	}

	LoginCount = 0;

	loginlist.Clear();
	for (std::size_t i = 0; i < _root["login_server"].size(); i++) {
		auto loginconfig = new LoginConfig;
		if (_root["login_server"][i]["host"].IsNull()) {
			throw std::runtime_error("Missing login_server.host in config.yaml");
		}
		if (_root["login_server"][i]["host"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login_server.host must be a string");
		}
		loginconfig->LoginHost = _root["login_server"][i]["host"].as<std::string>();
		if (_root["login_server"][i]["port"].IsNull()) {
			throw std::runtime_error("Missing login_server.port in config.yaml");
		}
		if (_root["login_server"][i]["port"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("login_server.port must be a number");
		}
		loginconfig->LoginPort = _root["login_server"][i]["port"].as<uint16>();
		if (!_root["login_server"][i]["account"].IsNull()) {
			if (_root["login_server"][i]["account"].Type() != YAML::NodeType::Scalar) {
				throw std::runtime_error("login_server.account must be a string");
			}
			loginconfig->LoginAccount = _root["login_server"][i]["account"].as<std::string>();
		}
		if (!_root["login_server"][i]["password"].IsNull()) {
			if (_root["login_server"][i]["password"].Type() != YAML::NodeType::Scalar) {
				throw std::runtime_error("login_server.password must be a string");
			}
			loginconfig->LoginPassword = _root["login_server"][i]["password"].as<std::string>();
		}
		if (!_root["login_server"][i]["type"].IsNull()) {
			if (_root["login_server"][i]["type"].Type() != YAML::NodeType::Scalar) {
				throw std::runtime_error("login_server.type must be a number");
			}
			loginconfig->LoginType = _root["login_server"][i]["type"].as<uint8>();
		}
		loginlist.Insert(loginconfig);
	}

	if (!_root["world"]["telnet_is_enabled"].IsNull()) {
		if (_root["world"]["telnet_is_enabled"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("telnet.is_enabled must be a boolean");
		}
		TelnetEnabled = _root["world"]["telnet_is_enabled"].as<bool>();
	} else {
		TelnetEnabled = false;
	}

	if (!_root["ucs"]["host"].IsNull()) {
		if (_root["ucs"]["host"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("ucs.host must be a string");
		}

		ChatHost = _root["ucs"]["host"].as<std::string>();
	}

	if (!_root["ucs"]["port"].IsNull()) {
		if (_root["ucs"]["port"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("ucs.port must be a number");
		}
		ChatPort = _root["ucs"]["port"].as<uint16_t>();
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
			throw std::runtime_error("database.port must be a number");
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
			throw std::runtime_error("query_serv.port must be a number");
		}
		QSDatabasePort = _root["query_serv"]["port"].as<uint16_t>();
	} else {
		throw std::runtime_error("Missing query_serv.port in config.yaml");
	}

	if (!_root["zone"]["default_status"].IsNull()) {
		if (_root["zone"]["default_status"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("zone.default_status must be a number");
		}
		DefaultStatus = _root["zone"]["default_status"].as<uint8_t>();
	} else {
		DefaultStatus = 0;
	}

	if (!_root["zone"]["port_min"].IsNull()) {
		if (_root["zone"]["port_min"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("zone.port_min must be a number");
		}
		ZonePortLow = _root["zone"]["port_min"].as<uint16_t>();
	} else {
		ZonePortLow = 7000;
	}

	if (!_root["zone"]["port_max"].IsNull()) {
		if (_root["zone"]["port_max"].Type() != YAML::NodeType::Scalar) {
			throw std::runtime_error("zone.port_max must be a number");
		}
		ZonePortHigh = _root["zone"]["port_max"].as<uint16_t>();
	} else {
		ZonePortHigh = 7400;
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