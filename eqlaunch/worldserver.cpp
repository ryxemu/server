#include "../common/global_define.h"
#include "../common/eqemu_logsys.h"
#include "../common/servertalk.h"
#include "../common/eqemu_config.h"
#include "../common/strings.h"
#include "worldserver.h"
#include "zone_launch.h"

WorldServer::WorldServer(std::map<std::string, ZoneLaunch *> &zones, const char *name, const EQEmuConfig *config)
    : WorldConnection(EmuTCPConnection::packetModeLauncher, config->SharedKey.c_str()),
      m_name(name),
      m_config(config),
      m_zones(zones) {
}

WorldServer::~WorldServer() {
}

void WorldServer::OnConnected() {
	WorldConnection::OnConnected();

	auto pack = new ServerPacket(ServerOP_LauncherConnectInfo, sizeof(LauncherConnectInfo));
	LauncherConnectInfo *sci = (LauncherConnectInfo *)pack->pBuffer;
	strn0cpy(sci->name, m_name, sizeof(sci->name));
	//	sci->port = net.GetZonePort();
	//	strcpy(sci->address, net.GetZoneAddress());
	SendPacket(pack);
	safe_delete(pack);

	// send status for all zones...
	std::map<std::string, ZoneLaunch *>::iterator cur, end;
	cur = m_zones.begin();
	end = m_zones.end();
	for (; cur != end; ++cur) {
		cur->second->SendStatus();
	}
}

void WorldServer::Process() {
	WorldConnection::Process();

	if (!Connected())
		return;

	ServerPacket *pack = 0;
	while ((pack = tcpc.PopPacket())) {
		switch (pack->opcode) {
			case 0: {
				break;
			}
			case ServerOP_EmoteMessage:
			case ServerOP_KeepAlive: {
				// ignore this
				break;
			}
			case ServerOP_ZAAuthFailed: {
				Log(Logs::Detail, Logs::Launcher, "World server responded 'Not Authorized', disabling reconnect");
				pTryReconnect = false;
				Disconnect();
				break;
			}
			case ServerOP_LauncherZoneRequest: {
				if (pack->size != sizeof(LauncherZoneRequest)) {
					Log(Logs::Detail, Logs::Launcher, "Invalid size of LauncherZoneRequest: %d", pack->size);
					break;
				}
				const LauncherZoneRequest *lzr = (const LauncherZoneRequest *)pack->pBuffer;

				switch (ZoneRequestCommands(lzr->command)) {
					case ZR_Start: {
						if (m_zones.find(lzr->short_name) != m_zones.end()) {
							Log(Logs::Detail, Logs::Launcher, "World told us to start zone %s, but it is already running.", lzr->short_name);
						} else {
							Log(Logs::Detail, Logs::Launcher, "World told us to start zone %s.", lzr->short_name);
							auto l = new ZoneLaunch(this, m_name, lzr->short_name, lzr->port, m_config);
							m_zones[lzr->short_name] = l;
						}
						break;
					}
					case ZR_Restart: {
						auto res = m_zones.find(lzr->short_name);
						if (res == m_zones.end()) {
							Log(Logs::Detail, Logs::Launcher, "World told us to restart zone %s, but it is not running.", lzr->short_name);
						} else {
							Log(Logs::Detail, Logs::Launcher, "World told us to restart zone %s.", lzr->short_name);
							res->second->Restart();
						}
						break;
					}
					case ZR_Stop: {
						auto res = m_zones.find(lzr->short_name);
						if (res == m_zones.end()) {
							Log(Logs::Detail, Logs::Launcher, "World told us to stop zone %s, but it is not running.", lzr->short_name);
						} else {
							Log(Logs::Detail, Logs::Launcher, "World told us to stop zone %s.", lzr->short_name);
							res->second->Stop();
						}
						break;
					}
				}
				break;
			}
			case ServerOP_GroupIDReply: {
				// ignore this, world is still being dumb
				break;
			}

			default: {
				Log(Logs::Detail, Logs::Launcher, "Unknown opcode 0x%x from World of len %d", pack->opcode, pack->size);
				break;
			}
		}
		safe_delete(pack);
	}
}

void WorldServer::SendStatus(const char *short_name, uint32 start_count, bool running) {
	auto pack = new ServerPacket(ServerOP_LauncherZoneStatus, sizeof(LauncherZoneStatus));
	LauncherZoneStatus *it = (LauncherZoneStatus *)pack->pBuffer;

	strn0cpy(it->short_name, short_name, 32);
	it->start_count = start_count;
	it->running = running ? 1 : 0;

	SendPacket(pack);
	safe_delete(pack);
}
