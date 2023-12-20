#ifndef EQEMU_LOGINSERVER_H
#define EQEMU_LOGINSERVER_H

#include "config.h"
#include "database.h"
#include "options.h"
#include "server_manager.h"
#include "client_manager.h"

/**
 * Login server struct, contains every variable for the server that needs to exist
 * outside the scope of main().
 */
struct LoginServer {
   public:
	/**
	 * I don't really like how this looks with all the ifdefs...
	 * but it's the most trivial way to do this.
	 */
	LoginServer() : config(nullptr), db(nullptr), server_manager(nullptr) {}

	Config *config;
	Database *db;
	Options options;
	ServerManager *server_manager;
	ClientManager *client_manager;
};

#endif
