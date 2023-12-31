#include "../masterentity.h"
#include "lua_raid.h"
#include "lua_entity.h"
#include "lua_mob.h"
#include "lua_client.h"
#include "lua_npc.h"

int Lua_Raid::GetID() {
	Lua_Safe_Call_Int();
	return self->GetID();
}
/*
bool Lua_Raid::IsRaidMember(const char *name) {
	Lua_Safe_Call_Bool();
	return self->IsRaidMember(name);
}

void Lua_Raid::CastGroupSpell(Lua_Mob caster, int spell_id, uint32 group_id) {
	Lua_Safe_Call_Void();
	self->CastGroupSpell(caster, spell_id, group_id);
}

int Lua_Raid::GroupCount(uint32 group_id) {
	Lua_Safe_Call_Int();
	return self->GroupCount(group_id);
}

int Lua_Raid::RaidCount() {
	Lua_Safe_Call_Int();
	return self->RaidCount();
}

int Lua_Raid::GetGroup(const char *c) {
	Lua_Safe_Call_Int();
	return self->GetGroup(c);
}

int Lua_Raid::GetGroup(Lua_Client c) {
	Lua_Safe_Call_Int();
	return self->GetGroup(c);
}

void Lua_Raid::SplitExp(uint32 exp, Lua_Mob other) {
	Lua_Safe_Call_Void();
	self->SplitExp(exp, other);
}

uint32 Lua_Raid::GetTotalRaidDamage(Lua_Mob other) {
	Lua_Safe_Call_Int();
	return self->GetTotalRaidDamage(other);
}

void Lua_Raid::SplitMoney(uint32 gid, uint32 copper, uint32 silver, uint32 gold, uint32 platinum) {
	Lua_Safe_Call_Void();
	self->SplitMoney(gid, copper, silver, gold, platinum);
}

void Lua_Raid::SplitMoney(uint32 gid, uint32 copper, uint32 silver, uint32 gold, uint32 platinum, Lua_Client splitter) {
	Lua_Safe_Call_Void();
	self->SplitMoney(gid, copper, silver, gold, platinum, splitter);
}

void Lua_Raid::BalanceHP(int penalty, uint32 group_id) {
	Lua_Safe_Call_Void();
	self->BalanceHP(penalty, group_id);
}

bool Lua_Raid::IsLeader(const char *c) {
	Lua_Safe_Call_Bool();
	return self->IsLeader(c);
}

bool Lua_Raid::IsLeader(Lua_Client c) {
	Lua_Safe_Call_Bool();
	return self->IsLeader(c);
}

bool Lua_Raid::IsGroupLeader(const char *name) {
	Lua_Safe_Call_Bool();
	return self->IsGroupLeader(name);
}

int Lua_Raid::GetHighestLevel() {
	Lua_Safe_Call_Int();
	return self->GetHighestLevel();
}

int Lua_Raid::GetLowestLevel() {
	Lua_Safe_Call_Int();
	return self->GetLowestLevel();
}

Lua_Client Lua_Raid::GetClientByIndex(int index) {
	Lua_Safe_Call_Class(Lua_Client);
	return self->GetClientByIndex(index);
}

void Lua_Raid::TeleportGroup(Lua_Mob sender, uint32 zone_id, uint32 instance_id, float x, float y, float z, float h, uint32 group_id) {
	Lua_Safe_Call_Void();
	self->TeleportGroup(sender, zone_id, instance_id, x, y, z, h, group_id);
}

void Lua_Raid::TeleportRaid(Lua_Mob sender, uint32 zone_id, uint32 instance_id, float x, float y, float z, float h) {
	Lua_Safe_Call_Void();
	self->TeleportRaid(sender, zone_id, instance_id, x, y, z, h);
}



Lua_Client Lua_Raid::GetMember(int index) {
	Lua_Safe_Call_Class(Lua_Client);

	if (index >= 72 || index < 0) {
		return Lua_Client();
	}

	return self->members[index].member;
}

int Lua_Raid::GetGroupNumber(int index) {
	Lua_Safe_Call_Int();

	if (index >= 72 || index < 0 || self->members[index].GroupNumber == RAID_GROUPLESS) {
		return -1;
	}

	return self->members[index].GroupNumber;
}

bool Lua_Raid::DoesAnyMemberHaveExpeditionLockout(std::string expedition_name, std::string event_name) {
	Lua_Safe_Call_Bool();
	return self->DoesAnyMemberHaveExpeditionLockout(expedition_name, event_name);
}

bool Lua_Raid::DoesAnyMemberHaveExpeditionLockout(std::string expedition_name, std::string event_name, int max_check_count) {
	Lua_Safe_Call_Bool();
	return self->DoesAnyMemberHaveExpeditionLockout(expedition_name, event_name, max_check_count);
} */