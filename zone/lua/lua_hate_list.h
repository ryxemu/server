#ifndef EQEMU_LUA_HATE_LIST_H
#define EQEMU_LUA_HATE_LIST_H

#include <sol/sol.hpp>
#include "lua_ptr.h"

class Lua_Mob;
struct struct_HateList;

class Lua_HateEntry : public Lua_Ptr<struct_HateList> {
	typedef struct_HateList NativeType;

   public:
	Lua_HateEntry() : Lua_Ptr(nullptr) {}
	Lua_HateEntry(struct_HateList *d) : Lua_Ptr(d) {}
	virtual ~Lua_HateEntry() {}

	Lua_Mob GetEnt();
	void SetEnt(Lua_Mob e);
	// int64 GetDamage();
	// void SetDamage(int64 value);
	// int64 GetHate();
	// void SetHate(int64 value);
	// int GetFrenzy();
	// void SetFrenzy(bool value);
};

struct Lua_HateList {
	std::vector<Lua_HateEntry> entries;
	sol::as_table_t<std::vector<Lua_HateEntry>> get_entries() { return sol::as_table(entries); }
};
#endif