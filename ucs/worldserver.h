#ifndef WORLDSERVER_H
#define WORLDSERVER_H

#include "../common/worldconn.h"
#include "../common/eq_packet_structs.h"

class EQApplicationPacket;

class WorldServer : public WorldConnection {
   public:
	WorldServer();
	virtual ~WorldServer();
	virtual void Process();

   private:
	virtual void OnConnected();
};
#endif
