#ifndef __queryservconfig_H
#define __queryservconfig_H

#include "../common/config.h"

class queryservconfig : public Config {
   private:
	static queryservconfig *_chat_config;

   public:
	// Produce a const singleton
	static const queryservconfig *get() {
		if (_chat_config == nullptr)
			LoadConfig();
		return (_chat_config);
	}

	// Load the config
	static std::string LoadConfig() {
		if (_chat_config != nullptr)
			delete _chat_config;
		_chat_config = new queryservconfig;
		_config = _chat_config;

		return _config->parseFile();
	}
};

#endif
