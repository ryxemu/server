#ifndef __EQEmuConfig_H
#define __EQEmuConfig_H

#include "json/json.h"
#include "linked_list.h"
#include <fstream>

struct LoginConfig {
	std::string LoginHost;
	std::string LoginAccount;
	std::string LoginPassword;
	uint16 LoginPort;
	uint8 LoginType;
};

class EQEmuConfig {
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

	// From <files/>
	std::string SpellsFile;
	std::string OpCodesFile;

	// From <directories/>
	std::string MapDir;
	std::string QuestDir;
	std::string LuaModuleDir;
	std::string PatchDir;
	std::string SharedMemDir;
	std::string LogDir;

	// From <launcher/>
	std::string LogPrefix;
	std::string LogSuffix;
	std::string ZoneExe;
	uint32 RestartWait;
	uint32 TerminateWait;
	uint32 InitialBootWait;
	uint32 ZoneBootInterval;

	// From <zones/>
	uint16 ZonePortLow;
	uint16 ZonePortHigh;
	uint8 DefaultStatus;
	//	uint16 DynamicCount;
	//	map<string,uint16> StaticZones;
   protected:
	static EQEmuConfig *_config;
	Json::Value _root;
	static std::string ConfigFile;

	void parse_config();

	EQEmuConfig() {
	}
	virtual ~EQEmuConfig() {}

   public:
	// Produce a const singleton
	static const EQEmuConfig *get() {
		LoadConfig();
		return (_config);
	}
	// Allow the use to set the conf file to be used.
	static void SetConfigFile(std::string file) { EQEmuConfig::ConfigFile = file; }
	// Load the config
	static bool LoadConfig() {
		if (_config != nullptr)
			return true;

		_config = new EQEmuConfig;

		return parseFile();
	}

	// Load config file and parse data
	static bool parseFile() {
		if (_config == nullptr) {
			return LoadConfig();
		}

		std::ifstream fconfig(EQEmuConfig::ConfigFile, std::ifstream::binary);
		try {
			fconfig >> _config->_root;
			_config->parse_config();
		} catch (std::exception) {
			return false;
		}
		return true;
	}

	void Dump() const;
};

#endif
