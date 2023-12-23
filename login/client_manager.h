#ifndef EQEMU_CLIENTMANAGER_H
#define EQEMU_CLIENTMANAGER_H

#include "../common/global_define.h"
#include "../common/opcodemgr.h"
#include "../common/eq_stream_type.h"
#include "../common/eq_stream_factory.h"
#include "client.h"
#include <list>

using namespace std;

/**
 * Client manager class, holds all the client objects and does basic processing.
 */
class ClientManager {
   public:
	/**
	 * Constructor, sets up the stream factories and opcode managers.
	 */
	ClientManager();

	/**
	 * Destructor, shuts down the streams and opcode managers.
	 */
	~ClientManager();

	/**
	 * Processes every client in the internal list, removes them if necessary.
	 */
	void Process();

	/**
	 * Sends a new server list to every client.
	 */
	void UpdateServerList();

	/**
	 * Removes a client with a certain account id.
	 */
	void RemoveExistingClient(unsigned int account_id);

	/**
	 * Gets a client (if exists) by their account id.
	 */
	Client* GetClient(unsigned int account_id);

   private:
	/**
	 * Processes disconnected clients, removes them if necessary.
	 */
	void ProcessDisconnect();

	list<Client*> clients;
	OpcodeManager* ops;
	EQStreamFactory* stream;
};

#endif
