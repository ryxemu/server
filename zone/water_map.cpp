#include "../common/config.h"

#include "water_map.h"
#include "water_map_v1.h"
#include "water_map_v2.h"

#include <algorithm>
#include <cctype>
#include <stdio.h>
#include <string.h>

/**
 * @param name
 * @return
 */
inline bool file_exists(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

/**
 * @param zone_name
 * @return
 */
WaterMap* WaterMap::LoadWaterMapfile(std::string zone_name) {
	std::transform(zone_name.begin(), zone_name.end(), zone_name.begin(), ::tolower);

	std::string filename;
	if (file_exists("maps")) {
		filename = "maps";
	} else if (file_exists("Maps")) {
		filename = "Maps";
	} else {
		filename = Config::get()->MapDir;
	}

	std::string file_path = filename + "/" + zone_name + std::string(".wtr");
	FILE* f = fopen(file_path.c_str(), "rb");
	if (f) {
		char magic[10];
		uint32 version;
		if (fread(magic, 10, 1, f) != 1) {
			fclose(f);
			return nullptr;
		}

		if (strncmp(magic, "EQEMUWATER", 10)) {
			fclose(f);
			return nullptr;
		}

		if (fread(&version, sizeof(version), 1, f) != 1) {
			fclose(f);
			return nullptr;
		}

		if (version == 1) {
			auto wm = new WaterMapV1();
			if (!wm->Load(f)) {
				delete wm;
				wm = nullptr;
			}

			fclose(f);
			return wm;
		} else if (version == 2) {
			auto wm = new WaterMapV2();
			if (!wm->Load(f)) {
				delete wm;
				wm = nullptr;
			}

			fclose(f);
			return wm;
		} else {
			fclose(f);
			return nullptr;
		}
	}

	return nullptr;
}
