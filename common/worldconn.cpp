#include "../common/global_define.h"
#include "../common/eqemu_logsys.h"
#include <iomanip>

#include "worldconn.h"
#include "eqemu_config.h"
#include "md5.h"
#include "servertalk.h"

WorldConnection::WorldConnection(EmuTCPConnection::ePacketMode mode, const char *password)
    : m_password(password) {
	tcpc.SetPacketMode(mode);
	pTryReconnect = true;
	pConnected = false;
}

WorldConnection::~WorldConnection() {
}

bool WorldConnection::SendPacket(ServerPacket *pack) {
	if (!Connected())
		return false;
	return tcpc.SendPacket(pack);
}

void WorldConnection::OnConnected() {
	const EQEmuConfig *Config = EQEmuConfig::get();
	Log(Logs::General, Logs::Netcode, "[WORLD] Connected to World: %s:%d", Config->WorldIP.c_str(), Config->WorldTCPPort);

	auto pack = new ServerPacket(ServerOP_ZAAuth, 16);
	MD5::Generate((const uchar *)m_password.c_str(), m_password.length(), pack->pBuffer);
	SendPacket(pack);
	safe_delete(pack);
}

void WorldConnection::Process() {
	// persistent connection....
	if (!Connected()) {
		pConnected = tcpc.Connected();
		if (pConnected) {
			OnConnected();
		} else
			return;
	}
}

void WorldConnection::AsyncConnect() {
	const EQEmuConfig *Config = EQEmuConfig::get();
	tcpc.AsyncConnect(Config->WorldIP.c_str(), Config->WorldTCPPort);
}

bool WorldConnection::Connect() {
	const EQEmuConfig *Config = EQEmuConfig::get();
	char errbuf[TCPConnection_ErrorBufferSize];
	if (tcpc.Connect(Config->WorldIP.c_str(), Config->WorldTCPPort, errbuf)) {
		return true;
	} else {
		Log(Logs::General, Logs::Netcode, "[WORLD] WorldConnection connect: Connecting to the server %s:%d failed: %s", Config->WorldIP.c_str(), Config->WorldTCPPort, errbuf);
	}
	return false;
}

void WorldConnection::Disconnect() {
	tcpc.Disconnect();
}
