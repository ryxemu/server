#ifndef __WorldConfig_H
#define __WorldConfig_H

#include "../common/eqemu_config.h"

class WorldConfig : public EQEmuConfig {
   public:
	virtual std::string GetByName(const std::string &var_name) const;

	bool UpdateStats;
	bool LoginDisabled;

   private:
	static WorldConfig *_world_config;

	WorldConfig() : EQEmuConfig() {
		LoginDisabled = false;
		UpdateStats = true;
	}

   public:
	// Produce a const singleton
	static const WorldConfig *get() {
		if (_world_config == nullptr)
			LoadConfig();
		return (_world_config);
	}

	// Load the config
	static bool LoadConfig() {
		if (_world_config != nullptr)
			delete _world_config;
		_world_config = new WorldConfig;
		_config = _world_config;

		return _config->parseFile();
	}

	// Accessors for the static private object
	static void LockWorld() {
		if (_world_config) _world_config->Locked = true;
	}
	static void UnlockWorld() {
		if (_world_config) _world_config->Locked = false;
	}

	static void DisableStats() {
		if (_world_config) _world_config->UpdateStats = false;
	}
	static void EnableStats() {
		if (_world_config) _world_config->UpdateStats = true;
	}

	static void DisableLoginserver() {
		if (_world_config) _world_config->LoginDisabled = true;
	}
	static void EnableLoginserver() {
		if (_world_config) _world_config->LoginDisabled = false;
	}

	static void SetWorldAddress(std::string addr) {
		if (_world_config) _world_config->WorldAddress = addr;
	}
	static void SetLocalAddress(std::string addr) {
		if (_world_config) _world_config->LocalAddress = addr;
	}

	void Dump() const;
};

#endif
