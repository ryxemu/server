#ifndef COMMON_WEBINTUTIL_H
#define COMMON_WEBINTUTIL_H

#include "../common/global_define.h"
// #include "rapidjson/writer.h"
// #include "rapidjson/stringbuffer.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>

std::vector<std::string> explode_string(std::string const& s, char delim);
std::string MakeJSON(std::string json);

#endif
