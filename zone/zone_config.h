#ifndef __ZoneConfig_H
#define __ZoneConfig_H

#include "../common/config.h"

class ZoneConfig : public Config {
   public:
	uint16 ZonePort;
	std::string ZoneAddress;

   private:
	static ZoneConfig *_zone_config;

	ZoneConfig() : Config() {
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
	static std::string LoadConfig() {
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
