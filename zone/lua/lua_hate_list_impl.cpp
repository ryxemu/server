#ifdef LUA_EQEMU
#include "masterentity.h"
#include "hate_list.h"
#include "lua_mob.h"
#include "lua_hate_list.h"

Lua_Mob Lua_HateEntry::GetEnt() {
	Lua_Safe_Call_Class(Lua_Mob);
	return Lua_Mob(self->entity_on_hatelist);
}

void Lua_HateEntry::SetEnt(Lua_Mob e) {
	Lua_Safe_Call_Void();
	self->entity_on_hatelist = e;
}

int64 Lua_HateEntry::GetDamage() {
	Lua_Safe_Call_Int();
	return self->hatelist_damage;
}

void Lua_HateEntry::SetDamage(int64 value) {
	Lua_Safe_Call_Void();
	self->hatelist_damage = value;
}

int64 Lua_HateEntry::GetHate() {
	Lua_Safe_Call_Int();
	return self->stored_hate_amount;
}

void Lua_HateEntry::SetHate(int64 value) {
	Lua_Safe_Call_Void();
	self->stored_hate_amount = value;
}

int Lua_HateEntry::GetFrenzy() {
	Lua_Safe_Call_Int();
	return self->is_entity_frenzy;
}

void Lua_HateEntry::SetFrenzy(bool value) {
	Lua_Safe_Call_Void();
	self->is_entity_frenzy = value;
}
#endif