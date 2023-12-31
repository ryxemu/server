#ifndef EQEMU_LUA_GROUP_H
#define EQEMU_LUA_GROUP_H

#include "lua_ptr.h"

class Group;
class Lua_Mob;
class Lua_Client;

class Lua_Group : public Lua_Ptr<Group> {
	typedef Group NativeType;

   public:
	Lua_Group() : Lua_Ptr(nullptr) {}
	Lua_Group(Group *d) : Lua_Ptr(d) {}
	virtual ~Lua_Group() {}

	operator Group *() {
		return reinterpret_cast<Group *>(GetLuaPtrData());
	}

	int GetID();
	// void DisbandGroup();
	// bool IsGroupMember(Lua_Mob mob);
	// void CastGroupSpell(Lua_Mob caster, int spell_id);
	// void SplitExp(uint32 exp, Lua_Mob other);
	// void GroupMessage(Lua_Mob sender, int language, const char *message);
	// uint32 GetTotalGroupDamage(Lua_Mob other);
	// void SplitMoney(uint32 copper, uint32 silver, uint32 gold, uint32 platinum);
	// void SplitMoney(uint32 copper, uint32 silver, uint32 gold, uint32 platinum, Lua_Client splitter);
	// void SetLeader(Lua_Mob leader);
	// Lua_Mob GetLeader();
	// const char *GetLeaderName();
	// bool IsLeader(Lua_Mob leader);
	// int GroupCount();
	// int GetHighestLevel();
	// int GetLowestLevel();
	// void TeleportGroup(Lua_Mob sender, uint32 zone_id, uint32 instance_id, float x, float y, float z, float h);
	// Lua_Mob GetMember(int index);
	// bool DoesAnyMemberHaveExpeditionLockout(std::string expedition_name, std::string event_name);
	// bool DoesAnyMemberHaveExpeditionLockout(std::string expedition_name, std::string event_name, int max_check_count);
};

#endif