#ifndef EQEMU_LUA_SPELL_H
#define EQEMU_LUA_SPELL_H
#ifdef LUA_EQEMU

#include "lua_ptr.h"

struct SPDat_Spell_Struct;

luabind::scope lua_register_spell();

class Lua_Spell : public Lua_Ptr<const SPDat_Spell_Struct> {
	typedef const SPDat_Spell_Struct NativeType;

   public:
	Lua_Spell(int id);
	Lua_Spell() : Lua_Ptr(nullptr) {}
	Lua_Spell(const SPDat_Spell_Struct *d) : Lua_Ptr(d) {}
	virtual ~Lua_Spell() {}

	operator const SPDat_Spell_Struct *() {
		return reinterpret_cast<const SPDat_Spell_Struct *>(GetLuaPtrData());
	}

	int GetID();
	const char *GetName();
	const char *GetPlayer1();
	const char *GetTeleportZone();
	const char *GetYouCast();
	const char *GetOtherCasts();
	const char *GetCastOnYou();
	const char *GetCastOnOther();
	const char *GetSpellFades();
	float GetRange();
	float GetAoeRange();
	float GetPushBack();
	float GetPushUp();
	uint32 GetCastTime();
	uint32 GetRecoveryTime();
	uint32 GetRecastTime();
	uint32 GetBuffdurationFormula();
	uint32 GetBuffDuration();
	uint32 GetAEDuration();
	int GetMana();
	int GetBase(int i);
	int GetBase2(int i);
	int GetMax(int i);
	int GetComponents(int i);
	int GetComponentCounts(int i);
	int GetNoexpendReagent(int i);
	int GetFormula(int i);
	int GetGoodEffect();
	int GetActivated();
	int GetResistType();
	int GetEffectID(int i);
	int GetTargetType();
	int GetBaseDiff();
	int GetSkill();
	int GetZoneType();
	int GetEnvironmentType();
	int GetTimeOfDay();
	int GetClasses(int i);
	int GetCastingAnim();
	int GetSpellAffectIndex();
	int GetDisallowSit();
	int GetDeities(int i);
	int GetUninterruptable();
	int GetResistDiff();
	int GetRecourseLink();
	int GetShortBuffBox();
	int GetDescNum();
	int GetEffectDescNum();
	int GetEndurCost();
	int GetEndurTimerIndex();
	int GetHateAdded();
	int GetEndurUpkeep();
	int GetPVPResistBase();
	int GetPVPResistCalc();
	int GetPVPResistCap();
	int GetSpellCategory();
	int GetCanMGB();
	int GetDispelFlag();
	int GetSpellGroup();
	bool GetAllowRest();
	int GetDamageShieldType();
};

#endif
#endif
