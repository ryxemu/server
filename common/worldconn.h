#ifndef WORLDCONNECTION_H
#define WORLDCONNECTION_H

#include "../common/emu_tcp_connection.h"
#include <string>

class ServerPacket;

/*
 * This object is an arbitrary connection to world.
 */
class WorldConnection {
   public:
	WorldConnection(EmuTCPConnection::ePacketMode mode, const char *password = "");
	virtual ~WorldConnection();

	virtual void Process();
	bool SendPacket(ServerPacket *pack);

	uint32 GetIP() const { return tcpc.GetrIP(); }
	uint16 GetPort() const { return tcpc.GetrPort(); }
	bool Connected() const { return (pConnected && tcpc.Connected()); }

	void SetPassword(const char *password) { m_password = password; }
	bool Connect();
	void AsyncConnect();
	void Disconnect();
	inline bool TryReconnect() const { return pTryReconnect; }

   protected:
	virtual void OnConnected();

	std::string m_password;
	EmuTCPConnection tcpc;
	bool pTryReconnect;
	bool pConnected;
};

#endif
