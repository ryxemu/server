#ifndef __ZoneConfig_H
#define __ZoneConfig_H

#include "../common/eqemu_config.h"

class ZoneConfig : public EQEmuConfig {
   public:
	uint16 ZonePort;
	std::string ZoneAddress;

   private:
	static ZoneConfig *_zone_config;

	ZoneConfig() : EQEmuConfig() {
		ZonePort = 0;
	}

   public:
	// Produce a const singleton
	static const ZoneConfig *get() {
		if (_zone_config == nullptr)
			LoadConfig();
		return (_zone_config);
	}

	// Load the config
	static bool LoadConfig() {
		if (_zone_config != nullptr)
			delete _zone_config;
		_zone_config = new ZoneConfig;
		_config = _zone_config;

		return _config->parseFile();
	}

	// Accessors for the static private object
	static void SetZonePort(uint16 port) {
		if (_zone_config) _zone_config->ZonePort = port;
	}

	void Dump() const;
};

#endif
