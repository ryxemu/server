#ifndef ZONE_MAP_H
#define ZONE_MAP_H

#include "position.h"
#include <stdio.h>
#include "../common/types.h"

#define BEST_Z_INVALID -99999

uint32 InflateData(const char *buffer, uint32 len, char *out_buffer, uint32 out_len_max);

class Map {
   public:
	Map();
	~Map();

	float FindBestZ(glm::vec3 &start, glm::vec3 *result) const;
	float FindBestZ(glm::vec3 &start, glm::vec3 *result, float limit, float offset = 0.0f) const;
	float FindClosestZ(glm::vec3 &start, glm::vec3 *result, float z_offset) const;
	float FindCeiling(glm::vec3 &start, glm::vec3 *result) const;
	float FindGround(glm::vec3 &start, glm::vec3 *result) const;
	bool LineIntersectsZone(glm::vec3 start, glm::vec3 end, float step, glm::vec3 *hitLocation, glm::vec3 *hitNormal = nullptr, float *hitDistance = nullptr) const;
	bool LineIntersectsZoneCeiling(glm::vec3 start, glm::vec3 end, float step, glm::vec3 *hitLocation, glm::vec3 *hitNormal = nullptr, float *hitDistance = nullptr) const;
	bool LineIntersectsZoneNoZLeaps(glm::vec3 start, glm::vec3 end, float step_mag, glm::vec3 *result) const;
	bool CheckLoS(glm::vec3 myloc, glm::vec3 oloc) const;
	bool DoCollisionCheck(glm::vec3 myloc, glm::vec3 oloc, glm::vec3 &outnorm, float &distance) const;
	bool Load(const std::string &filename);
	static Map *LoadMapFile(std::string file);
	bool NoHazardsAccurate(glm::vec3 From, glm::vec3 To, float size = 6.0f, int max_steps = 20, float interval = 5.0f);

   private:
	void RotateVertex(glm::vec3 &v, float rx, float ry, float rz);
	void ScaleVertex(glm::vec3 &v, float sx, float sy, float sz);
	void TranslateVertex(glm::vec3 &v, float tx, float ty, float tz);
	bool LoadV1(FILE *f);
	bool LoadV2(FILE *f);

	struct impl;
	impl *imp;
};

#endif
