#include "client_manager.h"
#include "login_server.h"
#include "../common/config.h"

extern LoginServer server;
extern bool run_server;

#include "../common/eqemu_logsys.h"
extern EQEmuLogSys Log;

ClientManager::ClientManager() {
	stream = new EQStreamFactory(NewLSStream);
	ops = new RegularOpcodeManager;

	std::string opfile = Config::get()->PatchDir;
	opfile += "patch_";
	opfile += "Ls20231211";
	opfile += ".conf";

	run_server = false;
	if (!ops->LoadOpcodes(opfile.c_str())) {
		LogError("Failed to load opcodes from {}", opfile.c_str());
		return;
	}
	auto result = stream->Open(Config::get()->LoginPlayerIP, Config::get()->LoginPlayerPort);
	if (!result.empty()) {
		LogError("Failed to listen for client connections on UDP {}:{}: {}", Config::get()->LoginPlayerIP, Config::get()->LoginPlayerPort, result);
		exit(1);
	}
	LogInfo("Listening for client connections on UDP {}:{}", Config::get()->LoginPlayerIP, Config::get()->LoginPlayerPort);
	run_server = true;
}

ClientManager::~ClientManager() {
	if (stream) {
		stream->Close();
		delete stream;
	}

	if (ops) {
		delete ops;
	}
}

void ClientManager::Process() {
	ProcessDisconnect();
	EQOldStream *oldcur = stream->PopOld();
	if (stream) {
		while (oldcur) {
			struct in_addr in;
			in.s_addr = oldcur->GetRemoteIP();
			LogInfo("New client connection from {0}:{1}", inet_ntoa(in), ntohs(oldcur->GetRemotePort()));

			oldcur->SetOpcodeManager(&ops);
			Client *c = new Client(oldcur, cv_old);
			clients.push_back(c);
			oldcur = stream->PopOld();
		}
	}

	list<Client *>::iterator iter = clients.begin();
	while (iter != clients.end()) {
		if ((*iter)->Process() == false) {
			Log(Logs::General, Logs::LoginServer, "Client had a fatal error and had to be removed from the login");
			delete (*iter);
			iter = clients.erase(iter);
		} else {
			++iter;
		}
	}
}

void ClientManager::ProcessDisconnect() {
	list<Client *>::iterator iter = clients.begin();
	while (iter != clients.end()) {
		EQStreamInterface *c = (*iter)->GetConnection();
		if (c->CheckState(CLOSED)) {
			c->ReleaseFromUse();
			LogInfo("Client disconnected from the server, removing client");
			delete (*iter);
			iter = clients.erase(iter);
		} else {
			++iter;
		}
	}
}

void ClientManager::RemoveExistingClient(unsigned int account_id) {
	list<Client *>::iterator iter = clients.begin();
	while (iter != clients.end()) {
		if ((*iter)->GetAccountID() == account_id) {
			Log(Logs::General, Logs::LoginServer, "Client attempting to log in and existing client already logged in, removing existing client");
			delete (*iter);
			iter = clients.erase(iter);
		} else {
			++iter;
		}
	}
}

void ClientManager::UpdateServerList() {
	list<Client *>::iterator iter = clients.begin();
	while (iter != clients.end()) {
		(*iter)->SendServerListPacket();
		++iter;
	}
}

Client *ClientManager::GetClient(unsigned int account_id) {
	Client *cur = nullptr;
	int count = 0;
	list<Client *>::iterator iter = clients.begin();
	while (iter != clients.end()) {
		if ((*iter)->GetAccountID() == account_id) {
			cur = (*iter);
			count++;
		}
		++iter;
	}

	if (count > 1) {
		Log(Logs::General, Logs::Error, "More than one client with a given account_id existed in the client list");
	}
	return cur;
}
