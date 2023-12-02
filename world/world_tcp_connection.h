#ifndef WorldTCPCONNECTION_H
#define WorldTCPCONNECTION_H

#include "../common/types.h"

class WorldTCPConnection {
   public:
	WorldTCPConnection() {}
	virtual ~WorldTCPConnection() {}
	virtual void SendEmoteMessage(const char* to, uint32 to_guilddbid, int16 to_minstatus, uint32 type, const char* message, ...) {}
	virtual void SendEmoteMessageRaw(const char* to, uint32 to_guilddbid, int16 to_minstatus, uint32 type, const char* message) {}

	virtual inline bool IsConsole() { return false; }
	virtual inline bool IsZoneServer() { return false; }
};

#endif
