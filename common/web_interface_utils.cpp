#include "../common/global_define.h"
#include "web_interface_utils.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>

using namespace rapidjson;
using namespace std;

std::vector<std::string> explode_string(std::string const& s, char delim) {
	std::vector<std::string> result;
	std::istringstream iss(s);

	for (std::string token; std::getline(iss, token, delim);) {
		result.push_back(std::move(token));
	}

	return result;
}

std::string MakeJSON(std::string json) {
	StringBuffer s;
	Writer<StringBuffer> writer(s);
	writer.StartObject();

	auto arg_c = explode_string(json, ',');
	if (arg_c.size() == 0) {
		auto arg_v = explode_string(json, ':');
		if (arg_v.size() > 0) {
			for (int j = 0; j < arg_v.size(); j++) {
				writer.String(arg_v[j].c_str());
			}
		}
	} else {
		for (int i = 0; i < arg_c.size(); i++) {
			auto arg_v = explode_string(arg_c[i], ':');
			for (int j = 0; j < arg_v.size(); j++) {
				writer.String(arg_v[j].c_str());
			}
		}
	}

	writer.EndObject();
	return s.GetString();
}