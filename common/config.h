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

struct LoginConfig {
	std::string LoginHost;
	std::string LoginAccount;
	std::string LoginPassword;
	uint16 LoginPort;
	uint8 LoginType;
};

class Config {
   public:
	virtual std::string GetByName(const std::string &var_name) const;

	// From <world/>
	std::string ShortName;
	std::string LongName;
	std::string WorldAddress;
	std::string LocalAddress;
	std::string LoginHost;
	std::string LoginAccount;
	std::string LoginPassword;
	uint8 LoginType;
	uint16 LoginPort;
	uint32 LoginCount;
	LinkedList<LoginConfig *> loginlist;
	bool Locked;
	uint16 WorldTCPPort;
	std::string WorldIP;
	bool TelnetEnabled;
	int32 MaxClients;
	std::string SharedKey;

	// From <chatserver/>
	std::string ChatHost;
	uint16 ChatPort;

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
	std::string MapDir;
	std::string QuestDir;
	std::string LuaModuleDir;
	std::string PatchDir;
	std::string SharedMemDir;
	std::string LogDir;

	// From <zones/>
	uint16 ZonePortLow;
	uint16 ZonePortHigh;
	uint8 DefaultStatus;
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
	// Allow the use to set the conf file to be used.
	static void SetConfigFile(std::string file) {
		Config::ConfigFile = file;
	}
	// Load the config
	static std::string LoadConfig() {
		if (_config != nullptr) return "";

		_config = new Config;

		return parseFile();
	}

	// Load config file and parse data
	static std::string parseFile() {
		if (_config == nullptr) {
			return LoadConfig();
		}

		try {
			_config->_root = YAML::LoadFile(Config::ConfigFile);
			_config->parse_config();
		} catch (YAML::BadFile &e) {
			return fmt::format("Failed opening {}:{}:{}: {}", Config::ConfigFile, e.mark.line, e.mark.column, e.msg);
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

	void Dump() const;
};

#endif