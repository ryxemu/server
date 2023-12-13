#ifndef EQEMU_LUA_EXPEDITION_H
#define EQEMU_LUA_EXPEDITION_H
#include <string>
#include <sol/forward.hpp>
#include "lua_ptr.h"
#include "../../common/types.h"

class Expedition;
class Lua_Client;

class Lua_Expedition : public Lua_Ptr<Expedition> {
	typedef Expedition NativeType;

   public:
	Lua_Expedition() : Lua_Ptr(nullptr) {}
	Lua_Expedition(Expedition *d) : Lua_Ptr(d) {}
	virtual ~Lua_Expedition() {}

	operator Expedition *() {
		return reinterpret_cast<Expedition *>(GetLuaPtrData());
	}

	// void AddLockout(std::string event_name, uint32_t seconds);
	// void AddLockoutDuration(std::string event_name, int seconds);
	// void AddLockoutDuration(std::string event_name, int seconds, bool members_only);
	// void AddReplayLockout(uint32_t seconds);
	// void AddReplayLockoutDuration(int seconds);
	// void AddReplayLockoutDuration(int seconds, bool members_only);
	// uint32_t GetDynamicZoneID();
	// uint32_t GetID();
	// int GetInstanceID();
	// std::string GetLeaderName();
	// sol::table GetLockouts(sol::this_state s);
	// std::string GetLootEventByNPCTypeID(uint32_t npc_type_id);
	// std::string GetLootEventBySpawnID(uint32_t spawn_id);
	// uint32_t GetMemberCount();
	// sol::table GetMembers(sol::this_state s);
	// std::string GetName();
	// int GetSecondsRemaining();
	// std::string GetUUID();
	// int GetZoneID();
	// std::string GetZoneName();
	// int GetZoneVersion();
	// bool HasLockout(std::string event_name);
	// bool HasReplayLockout();
	// bool IsLocked();
	// void RemoveCompass();
	// void RemoveLockout(std::string event_name);
	// void SetCompass(uint32_t zone_id, float x, float y, float z);
	// void SetCompass(std::string zone_name, float x, float y, float z);
	// void SetLocked(bool lock_expedition);
	// void SetLocked(bool lock_expedition, int lock_msg);
	// void SetLocked(bool lock_expedition, int lock_msg, uint32_t color);
	// void SetLootEventByNPCTypeID(uint32_t npc_type_id, std::string event_name);
	// void SetLootEventBySpawnID(uint32_t spawn_id, std::string event_name);
	// void SetReplayLockoutOnMemberJoin(bool enable);
	// void SetSafeReturn(uint32_t zone_id, float x, float y, float z, float heading);
	// void SetSafeReturn(std::string zone_name, float x, float y, float z, float heading);
	// void SetSecondsRemaining(uint32_t seconds_remaining);
	// void SetSwitchID(int dz_switch_id);
	// void SetZoneInLocation(float x, float y, float z, float heading);
	// void UpdateLockoutDuration(std::string event_name, uint32_t duration);
	// void UpdateLockoutDuration(std::string event_name, uint32_t duration, bool members_only);
};
#endif  // EQEMU_LUA_EXPEDITION_H