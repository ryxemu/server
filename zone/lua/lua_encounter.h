#ifndef EQEMU_LUA_ENCOUNTER_H
#define EQEMU_LUA_ENCOUNTER_H

#include "lua_ptr.h"

class Encounter;

class Lua_Encounter : public Lua_Ptr<Encounter> {
	typedef Encounter NativeType;

   public:
	Lua_Encounter() { SetLuaPtrData(nullptr); }
	Lua_Encounter(Encounter *d) { SetLuaPtrData(reinterpret_cast<Encounter *>(d)); }
	virtual ~Lua_Encounter() {}

	operator Encounter *() {
		return reinterpret_cast<Encounter *>(GetLuaPtrData());
	}
};
#endif