#ifndef CONSOLE_H
#define CONSOLE_H

enum {
	consoleLoginStatus = 50,   // ability to log in, basic commands.
	httpLoginStatus = 100,     // can log into the HTTP interface
	consoleFlagStatus = 200,   // flag
	consoleKickStatus = 150,   // kick
	consoleLockStatus = 150,   // world lock/unlock
	consoleZoneStatus = 150,   // zone up/down/lock
	consolePassStatus = 200,   // change password
	consoleWorldStatus = 200,  // world shutdown
	consoleOpcodesStatus = 250
};

#define CONSOLE_STATE_USERNAME 0
#define CONSOLE_STATE_PASSWORD 1
#define CONSOLE_STATE_CONNECTED 2
#define CONSOLE_STATE_CLOSED 3

#include "../common/linked_list.h"
#include "../common/timer.h"
#include "../common/queue.h"
#include "../common/emu_tcp_connection.h"
#include "world_tcp_connection.h"
#include "../common/mutex.h"

struct ServerChannelMessage_Struct;

class Console : public WorldTCPConnection {
   public:
	Console(EmuTCPConnection* itcpc);
	virtual ~Console();
	virtual inline bool IsConsole() { return true; }

	bool Process();
	void Send(const char* message);
	int16 Admin() { return admin; }
	uint32 GetIP() { return tcpc->GetrIP(); }
	uint16 GetPort() { return tcpc->GetrPort(); }
	void ProcessCommand(const char* command);
	void Die();

	bool SendChannelMessage(const ServerChannelMessage_Struct* scm);
	bool SendEmoteMessage(uint32 type, const char* message, ...);
	bool SendEmoteMessageRaw(uint32 type, const char* message);
	void SendEmoteMessage(const char* to, uint32 to_guilddbid, int16 to_minstatus, uint32 type, const char* message, ...);
	void SendEmoteMessageRaw(const char* to, uint32 to_guilddbid, int16 to_minstatus, uint32 type, const char* message);
	void SendMessage(uint8 newline, const char* message, ...);

	const char* GetName() { return paccountname; }
	const char* AccountName() { return paccountname; }
	uint32 AccountID() { return paccountid; }
	void SetAccountID(uint32 new_id) { paccountid = new_id; }

   private:
	EmuTCPConnection* tcpc;

	Timer timeout_timer;
	Timer prompt_timer;

	void SendPrompt();

	uint32 paccountid;
	char paccountname[30];
	bool pAcceptMessages;

	uint8 state;

	int16 admin;
	uchar textbuf[1024];
	int bufindex;
};

class ConsoleList {
   public:
	ConsoleList() {}
	~ConsoleList() {}

	void Add(Console* con);
	void Process();
	void KillAll();

	void SendChannelMessage(const ServerChannelMessage_Struct* scm);
	void SendConsoleWho(WorldTCPConnection* connection, const char* to, int16 admin);
	void SendEmoteMessage(uint32 type, const char* message, ...);
	void SendEmoteMessageRaw(uint32 type, const char* message);
	Console* FindByAccountName(const char* accname);

   private:
	LinkedList<Console*> list;
};
#endif
