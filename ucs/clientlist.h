#ifndef CHATSERVER_CLIENTLIST_H
#define CHATSERVER_CLIENTLIST_H

#include "../common/opcodemgr.h"
#include "../common/eq_stream_type.h"
#include "../common/eq_stream_factory.h"
#include "../common/rulesys.h"
#include "chatchannel.h"
#include <list>
#include <vector>

#define MAX_JOINED_CHANNELS 10

enum {
	CommandJoin = 0,
	CommandLeaveAll,
	CommandLeave,
	CommandListAll,
	CommandList,
	CommandSet,
	CommandAnnounce,
	CommandSetOwner,
	CommandOPList,
	CommandInvite,
	CommandGrant,
	CommandModerate,
	CommandVoice,
	CommandKick,
	CommandPassword,
	CommandToggleInvites,
	CommandAFK,
	CommandUptime,
	CommandGetHeaders,
	CommandGetBody,
	CommandMailTo,
	CommandSetMessageStatus,
	CommandSelectMailBox,
	CommandSetMailForwarding,
	CommandBuddy,
	CommandIgnorePlayer,
	CommandEndOfList
};

struct CommandEntry {
	const char *CommandString;
	int CommandCode;
};

typedef enum { ConnectionTypeUnknown,
	           ConnectionTypeCombined,
	           ConnectionTypeMail,
	           ConnectionTypeChat } ConnectionType;

static const CommandEntry Commands[] = {
    {"join", CommandJoin},
    {"leaveall", CommandLeaveAll},
    {"leave", CommandLeave},
    {"listall", CommandListAll},
    {"list", CommandList},
    {"set", CommandSet},
    {"announce", CommandAnnounce},
    {"setowner", CommandSetOwner},
    {"oplist", CommandOPList},
    {"invite", CommandInvite},
    {"grant", CommandGrant},
    {"moderate", CommandModerate},
    {"voice", CommandVoice},
    {"kick", CommandKick},
    {"password", CommandPassword},
    {"toggleinvites", CommandToggleInvites},
    {"afk", CommandAFK},
    {"uptime", CommandUptime},
    {"getheaders", CommandGetHeaders},
    {"getbody", CommandGetBody},
    {"mailto", CommandMailTo},
    {"setmessagestatus", CommandSetMessageStatus},
    {"selectmailbox", CommandSelectMailBox},
    {"setmailforwarding", CommandSetMailForwarding},
    {"buddy", CommandBuddy},
    {"ignoreplayer", CommandIgnorePlayer},
    {"", CommandEndOfList}};

struct CharacterEntry {
	int CharID;
	int Level;
	int Race;
	int Class;
	std::string Name;
};

class Client {
   public:
	Client(EQStream *eqs);
	~Client();

	EQStream *ClientStream;
	void AddCharacter(int CharID, const char *CharacterName, int Level, int Race, int Class);
	void ClearCharacters() { Characters.clear(); }
	void SendChatlist();
	inline void QueuePacket(const EQApplicationPacket *p, bool ack_req = true) {
		if (ClientStream && ClientStream->CheckActive()) ClientStream->QueuePacket(p, ack_req);
	}
	std::string GetName() {
		if (Characters.size())
			return Characters[0].Name;
		else
			return "";
	}
	int GetLevel() {
		if (Characters.size())
			return Characters[0].Level;
		else
			return 0;
	}
	int GetRace() {
		if (Characters.size())
			return Characters[0].Race;
		else
			return 999;
	}
	int GetClass() {
		if (Characters.size())
			return Characters[0].Class;
		else
			return 999;
	}
	void JoinChannels(std::string ChannelList);
	void LeaveChannels(std::string ChannelList);
	void LeaveAllChannels(bool SendUpdatedChannelList = true);
	void AddToChannelList(ChatChannel *JoinedChannel);
	void RemoveFromChannelList(ChatChannel *JoinedChannel);
	void SendChannelMessage(std::string Message);
	void SendChannelMessage(std::string ChannelName, std::string Message, Client *Sender);
	void SendChannelMessageByNumber(std::string Message);
	void SendChannelList();
	void CloseConnection();
	void ToggleAnnounce(std::string State);
	bool IsAnnounceOn() { return (Announce == true); }
	void AnnounceJoin(ChatChannel *Channel, Client *c);
	void AnnounceLeave(ChatChannel *Channel, Client *c);
	void GeneralChannelMessage(std::string Message);
	void GeneralChannelMessage(const char *Characters);
	void SetChannelPassword(std::string ChannelPassword);
	void ProcessChannelList(std::string CommandString);
	void AccountUpdate();
	int ChannelCount();
	inline void SetAccountID(int inAccountID) { AccountID = inAccountID; }
	inline int GetAccountID() { return AccountID; }
	inline void SetAccountStatus(int inStatus) { Status = inStatus; }
	inline void SetHideMe(bool inHideMe) { HideMe = inHideMe; }
	inline void SetKarma(uint32 inKarma) { TotalKarma = inKarma; }
	inline int GetAccountStatus() { return Status; }
	inline bool GetHideMe() { return HideMe; }
	inline uint32 GetKarma() { return TotalKarma; }
	void SetChannelOwner(std::string CommandString);
	void OPList(std::string CommandString);
	void ChannelInvite(std::string CommandString);
	void ChannelGrantModerator(std::string CommandString);
	void ChannelGrantVoice(std::string CommandString);
	void ChannelKick(std::string CommandString);
	void ChannelModerate(std::string CommandString);
	std::string ChannelSlotName(int ChannelNumber);
	void ToggleInvites();
	bool InvitesAllowed() { return AllowInvites; }
	bool IsRevoked() { return Revoked; }
	void SetRevoked(bool r) { Revoked = r; }
	inline bool IsChannelAdmin() { return (Status >= RuleI(Channels, RequiredStatusAdmin)); }
	inline bool CanListAllChannels() { return (Status >= RuleI(Channels, RequiredStatusListAll)); }
	void SendHelp();
	inline bool GetForceDisconnect() { return ForceDisconnect; }
	void SetConnectionType(char c);
	ConnectionType GetConnectionType() { return TypeOfConnection; }
	bool GetStale() { return stale; }
	void SetStale() { stale = true; }
	void SendFriends();
	int GetCharID();
	void SendUptime();
	void SendKeepAlive();

   private:
	std::vector<CharacterEntry> Characters;
	ChatChannel *JoinedChannels[MAX_JOINED_CHANNELS];
	bool Announce;
	int AccountID;
	int Status;
	bool HideMe;
	bool AllowInvites;
	bool Revoked;
	bool stale;

	// Anti Spam Stuff
	Timer *AccountGrabUpdateTimer;
	uint32 TotalKarma;

	Timer *GlobalChatLimiterTimer;  // 60 seconds
	int AttemptedMessages;
	bool ForceDisconnect;
	ConnectionType TypeOfConnection;
};

class Clientlist {
   public:
	Clientlist();
	void Process();
	void CloseAllConnections();
	Client *FindCharacter(std::string CharacterName);
	void CheckForStaleConnectionsAll();
	void CheckForStaleConnections(Client *c);
	void CLClearStaleConnections();
	Client *IsCharacterOnline(std::string CharacterName);
	void ProcessOPChatCommand(Client *c, std::string CommandString);

   private:
	EQStreamFactory *chatsf;

	std::deque<Client *> ClientChatConnections;
	Mutex MClientChatConnections;

	OpcodeManager *ChatOpMgr;
};

#endif
