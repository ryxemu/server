#ifndef CHATSERVER_DATABASE_H
#define CHATSERVER_DATABASE_H

#define AUTHENTICATION_TIMEOUT 60
#define INVALID_ID 0xFFFFFFFF

#include "../common/global_define.h"
#include "../common/types.h"
#include "../common/dbcore.h"
#include "../common/linked_list.h"
#include "clientlist.h"
#include <string>
#include <vector>
#include <map>

// atoi is not uint32 or uint32 safe!!!!
#define atoul(str) strtoul(str, nullptr, 10)

class Database : public DBcore {
   public:
	Database();
	Database(const char* host, const char* user, const char* passwd, const char* database, uint32 port);
	bool Connect(const char* host, const char* user, const char* passwd, const char* database, uint32 port);
	~Database();

	int FindAccount(const char* CharacterName, Client* c);
	int FindCharacter(const char* CharacterName);
	bool GetVariable(const char* varname, char* varvalue, uint16 varvalue_len);
	bool LoadChatChannels();
	void GetAccountStatus(Client* c);
	void SetChannelPassword(std::string ChannelName, std::string Password);
	void SetChannelOwner(std::string ChannelName, std::string Owner);
	void SetMessageStatus(int MessageNumber, int Status);
	void AddFriendOrIgnore(int CharID, int Type, std::string Name);
	void RemoveFriendOrIgnore(int CharID, int Type, std::string Name);
	void GetFriendsAndIgnore(int CharID, std::vector<std::string>& Friends, std::vector<std::string>& Ignorees);

   protected:
	void HandleMysqlError(uint32 errnum);

   private:
	void DBInitVars();
};

#endif
