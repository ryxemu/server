#ifndef WORLDSERVER_H
#define WORLDSERVER_H

#include "../common/worldconn.h"
#include <string>
#include <queue>
#include <map>

class ZoneLaunch;
class EQEmuConfig;

class WorldServer : public WorldConnection {
   public:
	WorldServer(std::map<std::string, ZoneLaunch *> &zones, const char *name, const EQEmuConfig *config);
	virtual ~WorldServer();

	virtual void Process();

	void SendStatus(const char *short_name, uint32 start_count, bool running);

   private:
	virtual void OnConnected();

	const char *const m_name;
	const EQEmuConfig *const m_config;
	std::map<std::string, ZoneLaunch *> &m_zones;
};
#endif
