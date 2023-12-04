#ifndef LOGINSERVER_H
#define LOGINSERVER_H

#include "../common/servertalk.h"
#include "../common/linked_list.h"
#include "../common/timer.h"
#include "../common/queue.h"
#include "../common/eq_packet_structs.h"
#include "../common/mutex.h"
#include "../common/emu_tcp_connection.h"

class LoginServer {
   public:
	LoginServer(const char*, uint16, const char*, const char*, uint8);
	~LoginServer();

	bool InitLoginServer();

	bool Process();
	bool Connect();

	void SendInfo();
	void SendNewInfo();
	void SendStatus();

	void SendPacket(ServerPacket* pack) { tcpc->SendPacket(pack); }
	void SendAccountUpdate(ServerPacket* pack);
	bool ConnectReady() { return tcpc->ConnectReady(); }
	bool Connected() { return tcpc->Connected(); }
	bool CanUpdate() { return CanAccountUpdate; }

   private:
	EmuTCPConnection* tcpc;
	char LoginServerAddress[256];
	uint32 LoginServerIP;
	uint16 LoginServerPort;
	char LoginAccount[32];
	char LoginPassword[32];
	uint8 LoginServerType;
	bool CanAccountUpdate;

	Timer statusupdate_timer;
};
#endif
