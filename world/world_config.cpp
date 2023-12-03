#include "../common/global_define.h"
#include "world_config.h"

WorldConfig *WorldConfig::_world_config = nullptr;

std::string WorldConfig::GetByName(const std::string &var_name) const {
	if (var_name == "UpdateStats")
		return (UpdateStats ? "true" : "false");
	if (var_name == "LoginDisabled")
		return (LoginDisabled ? "true" : "false");
	return (Config::GetByName(var_name));
}
