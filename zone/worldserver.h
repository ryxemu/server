#ifndef WORLDSERVER_H
#define WORLDSERVER_H

#include "../common/worldconn.h"
#include "../common/eq_packet_structs.h"

class ServerPacket;
class EQApplicationPacket;
class Client;

class WorldServer : public WorldConnection {
   public:
	WorldServer();
	virtual ~WorldServer();

	virtual void Process();

	bool SendChannelMessage(Client* from, const char* to, uint8 chan_num, uint32 guilddbid, uint8 language, uint8 lang_skill, const char* message, ...);
	bool SendEmoteMessage(const char* to, uint32 to_guilddbid, uint32 type, const char* message, ...);
	bool SendEmoteMessage(const char* to, uint32 to_guilddbid, int16 to_minstatus, uint32 type, const char* message, ...);
	void SetZoneData(uint32 iZoneID);
	bool RezzPlayer(EQApplicationPacket* rpack, uint32 rezzexp, uint32 dbid, uint16 opcode);
	bool IsOOCMuted() const { return (oocmuted); }

	uint32 NextGroupID();

	void SetLaunchedName(const char* n) { m_launchedName = n; }
	void SetLauncherName(const char* n) { m_launcherName = n; }

	void RequestTellQueue(const char* who);

   private:
	virtual void OnConnected();

	std::string m_launchedName;
	std::string m_launcherName;

	bool oocmuted;

	uint32 cur_groupid;
	uint32 last_groupid;
};
#endif
