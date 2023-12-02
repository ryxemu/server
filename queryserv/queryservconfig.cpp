#include "../common/global_define.h"
#include "queryservconfig.h"

queryservconfig *queryservconfig::_chat_config = nullptr;

std::string queryservconfig::GetByName(const std::string &var_name) const {
	return (EQEmuConfig::GetByName(var_name));
}
