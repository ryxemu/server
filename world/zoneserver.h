/*	EQEMu: Everquest Server Emulator
    Copyright (C) 2001-2002 EQEMu Development Team (http://eqemu.org)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; version 2 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY except by those people which sell it, which
    are required to give you total support for your newly bought product;
    without even the implied warranty of MERCHANTABILITY or FITNESS FOR
    A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/
#ifndef ZONESERVER_H
#define ZONESERVER_H

#include "world_tcp_connection.h"
#include "../common/emu_tcp_connection.h"
#include <string>
#include <array>

class Client;
class ServerPacket;

class ZoneServer : public WorldTCPConnection {
public:
    ZoneServer(EmuTCPConnection* itcpc);
    ~ZoneServer();

    virtual bool IsZoneServer() const override { return true; }

    bool Process();
    bool SendPacket(ServerPacket* pack) { return tcpc->SendPacket(pack); }
    void SendEmoteMessage(const char* to, uint32 to_guilddbid, int16 to_minstatus, uint32 type, const char* message, ...);
    void SendEmoteMessageRaw(const char* to, uint32 to_guilddbid, int16 to_minstatus, uint32 type, const char* message);
    void TriggerBootup(uint32 iZoneID = 0, const char* iAdminName = nullptr, bool iMakeStatic = false);
    void Disconnect() { tcpc->Disconnect(); }
    void IncomingClient(Client* client);
    void LSBootUpdate(uint32 zoneid, bool startup = false);
    void LSSleepUpdate(uint32 zoneid);
    void LSShutDownUpdate(uint32 zoneid);

    const char* GetZoneName() const { return zone_name.c_str(); }
    const char* GetZoneLongName() const { return long_name.c_str(); }
    const char* GetCompileTime() const { return compiled.data(); }
    uint32 GetPrevZoneID() const { return zone_server_previous_zone_id; }
    uint32 GetZoneID() const { return zone_server_zone_id; }
    uint32 GetIP() const { return tcpc->GetrIP(); }
    uint16 GetPort() const { return tcpc->GetrPort(); }
    const char* GetCAddress() const { return client_address.data(); }
    const char* GetCLocalAddress() const { return client_local_address.data(); }
    uint16 GetCPort() const { return client_port; }
    uint32 GetID() const { return zone_server_id; }
    bool IsBootingUp() const { return is_booting_up; }
    bool IsStaticZone() const { return is_static_zone; }
    uint32 NumPlayers() const { return zone_player_count; }
    const char* GetLaunchName() const { return launcher_name.c_str(); }
    const char* GetLaunchedName() const { return launched_name.c_str(); }
    uint32 GetZoneOSProcessID() const { return zone_os_process_id; }

    void SetCompile(const char* in_compile);

    void ChangeWID(uint32 iCharID, uint32 iWID);
    void SendGroupIDs();
    bool SetZone(uint32 iZoneID, bool iStaticZone = false);
    void AddPlayer() { ++zone_player_count; }
    void RemovePlayer() { --zone_player_count; }

private:
    EmuTCPConnection* const tcpc;

    uint32 zone_server_id;
    std::array<char, 250> client_address;
    std::array<char, 250> client_local_address;
    uint16 client_port;
    bool is_booting_up;
    bool is_static_zone;
    bool is_authenticated;
    bool ucs_connected;
    uint32 zone_player_count;
    std::array<char, 25> compiled;
    std::string zone_name;
    std::string long_name;
    uint32 zone_server_zone_id;
    uint32 zone_server_previous_zone_id;
    Timer zone_boot_timer;
    uint32 zone_os_process_id;
    std::string launcher_name;
    std::string launched_name;
};

#endif
