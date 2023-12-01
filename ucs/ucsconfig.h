#ifndef __ucsconfig_H
#define __ucsconfig_H

#include "../common/eqemu_config.h"

class ucsconfig : public EQEmuConfig {
   public:
	virtual std::string GetByName(const std::string &var_name) const;

   private:
	static ucsconfig *_chat_config;

   public:
	// Produce a const singleton
	static const ucsconfig *get() {
		if (_chat_config == nullptr)
			LoadConfig();
		return (_chat_config);
	}

	// Load the config
	static bool LoadConfig() {
		if (_chat_config != nullptr)
			delete _chat_config;
		_chat_config = new ucsconfig;
		_config = _chat_config;

		return _config->parseFile();
	}
};

#endif
