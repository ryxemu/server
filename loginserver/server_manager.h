#ifndef EQEMU_SERVERMANAGER_H
#define EQEMU_SERVERMANAGER_H

#include "../common/global_define.h"
#include "../common/eq_stream_factory.h"
#include "../common/emu_tcp_connection.h"
#include "../common/emu_tcp_server.h"
#include "../common/servertalk.h"
#include "../common/packet_dump.h"
#include "world_server.h"
#include "client.h"
#include <list>

/**
* Server manager class, deals with management of the world servers.
*/
class ServerManager
{
public:
	/**
	* Constructor, sets up the TCP server and starts listening.
	*/
	ServerManager();

	/**
	* Destructor, shuts down the TCP server.
	*/
	~ServerManager();

	/**
	* Does basic processing for all the servers.
	*/
	void Process();

	/**
	* Sends a request to world to see if the client is banned or suspended.
	*/
	void SendOldUserToWorldRequest(const char* ServerIP, unsigned int client_account_id, uint32 ip);

	/**
	* Creates a server list packet for the older client.
	*/
	EQApplicationPacket* CreateOldServerListPacket(Client* c);

	/**
	* Checks to see if there is a server exists with this name, ignoring option.
	*/
	bool ServerExists(std::string l_name, std::string s_name, WorldServer *ignore = nullptr);

	/**
	* Destroys a server with this name, ignoring option.
	*/
	void DestroyServerByName(std::string l_name, std::string s_name, WorldServer *ignore = nullptr);

private:
	/**
	* Processes all the disconnected connections in Process(), not used outside.
	*/
	void ProcessDisconnect();

	/**
	* Retrieves a server(if exists) by ip address
	* Useful utility for the reconnect process.
	*/
	WorldServer* GetServerByAddress(unsigned int address);

	EmuTCPServer* tcps;
	std::list<WorldServer*> world_servers;
};

#endif

