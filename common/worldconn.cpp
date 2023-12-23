#include "../common/global_define.h"
#include "../common/eqemu_logsys.h"
#include <iomanip>

#include "worldconn.h"
#include "config.h"
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
	const Config *Config = Config::get();
	Log(Logs::General, Logs::Netcode, "[WORLD] Connected to World: %s:%d", Config::get()->WorldWANIP.c_str(), Config::get()->WorldWANPort);

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
	const Config *Config = Config::get();
	tcpc.AsyncConnect(Config::get()->WorldLANIP.c_str(), Config::get()->WorldLANPort);
}

std::string WorldConnection::Connect() {
	char errbuf[TCPConnection_ErrorBufferSize];
	if (!tcpc.Connect(Config::get()->ZoneWorldIP.c_str(), Config::get()->ZoneWorldPort, errbuf)) {
		return fmt::format("TCP {}:{}: {}", Config::get()->ZoneWorldIP, Config::get()->ZoneWorldPort, errbuf);
	}
	LogInfo("Connected to world server on TCP {}:{}", Config::get()->ZoneWorldIP, Config::get()->ZoneWorldPort);
	return "";
}

void WorldConnection::Disconnect() {
	tcpc.Disconnect();
}
