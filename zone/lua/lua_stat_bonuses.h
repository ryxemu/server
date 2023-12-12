#pragma once

#include "lua_ptr.h"
#include "../common.h"

struct StatBonuses;

class Lua_StatBonuses : public Lua_Ptr<StatBonuses> {
	typedef StatBonuses NativeType;

   public:
	Lua_StatBonuses() : Lua_Ptr(nullptr) {}
	Lua_StatBonuses(StatBonuses *d) : Lua_Ptr(d) {}
	virtual ~Lua_StatBonuses() {}

	operator StatBonuses *() {
		return reinterpret_cast<StatBonuses *>(GetLuaPtrData());
	}

	int32 GetAC() const;
	// int64 GetHP() const;
	// int64 GetHPRegen() const;
	// int64 GetMaxHP() const;
	// int64 GetManaRegen() const;
	// int64 GetEnduranceRegen() const;
	// int64 GetMana() const;
	// int64 GetEndurance() const;
	// int32 GetATK() const;
	// int32 GetSTR() const;
	// int32 GetSTRCapMod() const;
	// int32 GetHeroicSTR() const;
	// int32 GetSTA() const;
	// int32 GetSTACapMod() const;
	// int32 GetHeroicSTA() const;
	// int32 GetDEX() const;
	// int32 GetDEXCapMod() const;
	// int32 GetHeroicDEX() const;
	// int32 GetAGI() const;
	// int32 GetAGICapMod() const;
	// int32 GetHeroicAGI() const;
	// int32 GetINT() const;
	// int32 GetINTCapMod() const;
	// int32 GetHeroicINT() const;
	// int32 GetWIS() const;
	// int32 GetWISCapMod() const;
	// int32 GetHeroicWIS() const;
	// int32 GetCHA() const;
	// int32 GetCHACapMod() const;
	// int32 GetHeroicCHA() const;
	// int32 GetMR() const;
	// int32 GetMRCapMod() const;
	// int32 GetHeroicMR() const;
	// int32 GetFR() const;
	// int32 GetFRCapMod() const;
	// int32 GetHeroicFR() const;
	// int32 GetCR() const;
	// int32 GetCRCapMod() const;
	// int32 GetHeroicCR() const;
	// int32 GetPR() const;
	// int32 GetPRCapMod() const;
	// int32 GetHeroicPR() const;
	// int32 GetDR() const;
	// int32 GetDRCapMod() const;
	// int32 GetHeroicDR() const;
	// int32 GetCorrup() const;
	// int32 GetCorrupCapMod() const;
	// int32 GetHeroicCorrup() const;
	// uint16 GetDamageShieldSpellID() const;
	// int GetDamageShield() const;
	// int GetDamageShieldType() const;
	// int GetSpellDamageShield() const;
	// int GetSpellShield() const;
	// int GetReverseDamageShield() const;
	// uint16 GetReverseDamageShieldSpellID() const;
	// int GetReverseDamageShieldType() const;
	// int Getmovementspeed() const;
	// int32 Gethaste() const;
	// int32 Gethastetype2() const;
	// int32 Gethastetype3() const;
	// int32 Getinhibitmelee() const;
	// float GetAggroRange() const;
	// float GetAssistRange() const;
	// int32 Getskillmod(int idx) const;
	// int32 Getskillmodmax(int idx) const;
	// int Geteffective_casting_level() const;
	// int Getadjusted_casting_skill() const;
	// int Getreflect_chance() const;
	// uint32 GetsingingMod() const;
	// uint32 GetAmplification() const;
	// uint32 GetbrassMod() const;
	// uint32 GetpercussionMod() const;
	// uint32 GetwindMod() const;
	// uint32 GetstringedMod() const;
	// uint32 GetsongModCap() const;
	// int32 Gethatemod() const;
	// int64 GetEnduranceReduction() const;
	// int32 GetStrikeThrough() const;
	// int32 GetMeleeMitigation() const;
	// int32 GetMeleeMitigationEffect() const;
	// int32 GetCriticalHitChance(int idx) const;
	// int32 GetCriticalSpellChance() const;
	// int32 GetSpellCritDmgIncrease() const;
	// int32 GetSpellCritDmgIncNoStack() const;
	// int32 GetDotCritDmgIncrease() const;
	// int32 GetCriticalHealChance() const;
	// int32 GetCriticalHealOverTime() const;
	// int32 GetCriticalDoTChance() const;
	// int32 GetCrippBlowChance() const;
	// int32 GetAvoidMeleeChance() const;
	// int32 GetAvoidMeleeChanceEffect() const;
	// int32 GetRiposteChance() const;
	// int32 GetDodgeChance() const;
	// int32 GetParryChance() const;
	// int32 GetDualWieldChance() const;
	// int32 GetDoubleAttackChance() const;
	// int32 GetTripleAttackChance() const;
	// int32 GetDoubleRangedAttack() const;
	// int32 GetResistSpellChance() const;
	// int32 GetResistFearChance() const;
	// bool GetFearless() const;
	// bool GetIsFeared() const;
	// bool GetIsBlind() const;
	// int32 GetStunResist() const;
	// int32 GetMeleeSkillCheck() const;
	// uint8 GetMeleeSkillCheckSkill() const;
	// int32 GetHitChance() const;
	// int32 GetHitChanceEffect(int idx) const;
	// int32 GetDamageModifier(int idx) const;
	// int32 GetDamageModifier2(int idx) const;
	// int32 GetMinDamageModifier(int idx) const;
	// int32 GetProcChance() const;
	// int32 GetProcChanceSPA() const;
	// int32 GetExtraAttackChance() const;
	// int32 GetDoTShielding() const;
	// int32 GetFlurryChance() const;
	// int32 GetHundredHands() const;
	// int32 GetMeleeLifetap() const;
	// int32 GetVampirism() const;
	// int32 GetHealRate() const;
	// int32 GetMaxHPChange() const;
	// int32 GetHealAmt() const;
	// int32 GetSpellDmg() const;
	// int32 GetClairvoyance() const;
	// int32 GetDSMitigation() const;
	// int32 GetDSMitigationOffHand() const;
	// int32 GetTwoHandBluntBlock() const;
	// uint32 GetItemManaRegenCap() const;
	// int32 GetGravityEffect() const;
	// bool GetAntiGate() const;
	// bool GetMagicWeapon() const;
	// int32 GetIncreaseBlockChance() const;
	// uint32 GetPersistantCasting() const;
	// int GetXPRateMod() const;
	// bool GetBlockNextSpell() const;
	// bool GetImmuneToFlee() const;
	// uint32 GetVoiceGraft() const;
	// int32 GetSpellProcChance() const;
	// int32 GetCharmBreakChance() const;
	// int32 GetSongRange() const;
	// uint32 GetHPToManaConvert() const;
	// bool GetNegateEffects() const;
	// bool GetTriggerMeleeThreshold() const;
	// bool GetTriggerSpellThreshold() const;
	// int32 GetShieldBlock() const;
	// int32 GetBlockBehind() const;
	// bool GetCriticalRegenDecay() const;
	// bool GetCriticalHealDecay() const;
	// bool GetCriticalDotDecay() const;
	// bool GetDivineAura() const;
	// bool GetDistanceRemoval() const;
	// int32 GetFrenziedDevastation() const;
	// bool GetNegateIfCombat() const;
	// int8 GetScreech() const;
	// int32 GetAlterNPCLevel() const;
	// bool GetBerserkSPA() const;
	// int32 GetMetabolism() const;
	// bool GetSanctuary() const;
	// int32 GetFactionModPct() const;
	// uint32 GetPC_Pet_Flurry() const;
	// int8 GetPackrat() const;
	// uint8 GetBuffSlotIncrease() const;
	// uint32 GetDelayDeath() const;
	// int8 GetBaseMovementSpeed() const;
	// uint8 GetIncreaseRunSpeedCap() const;
	// int32 GetDoubleSpecialAttack() const;
	// uint8 GetFrontalStunResist() const;
	// int32 GetBindWound() const;
	// int32 GetMaxBindWound() const;
	// int32 GetChannelChanceSpells() const;
	// int32 GetChannelChanceItems() const;
	// uint8 GetSeeInvis() const;
	// uint8 GetTripleBackstab() const;
	// bool GetFrontalBackstabMinDmg() const;
	// uint8 GetFrontalBackstabChance() const;
	// uint8 GetConsumeProjectile() const;
	// uint8 GetForageAdditionalItems() const;
	// uint8 GetSalvageChance() const;
	// uint32 GetArcheryDamageModifier() const;
	// bool GetSecondaryDmgInc() const;
	// uint32 GetGiveDoubleAttack() const;
	// int32 GetPetCriticalHit() const;
	// int32 GetPetAvoidance() const;
	// int32 GetCombatStability() const;
	// int32 GetDoubleRiposte() const;
	// int32 GetAmbidexterity() const;
	// int32 GetPetMaxHP() const;
	// int32 GetPetFlurry() const;
	// uint8 GetMasteryofPast() const;
	// bool GetGivePetGroupTarget() const;
	// int32 GetRootBreakChance() const;
	// int32 GetUnfailingDivinity() const;
	// int32 GetItemHPRegenCap() const;
	// int32 GetOffhandRiposteFail() const;
	// int32 GetItemATKCap() const;
	// int32 GetShieldEquipDmgMod() const;
	// bool GetTriggerOnValueAmount() const;
	// int8 GetStunBashChance() const;
	// int8 GetIncreaseChanceMemwipe() const;
	// int8 GetCriticalMend() const;
	// int32 GetImprovedReclaimEnergy() const;
	// int32 GetPetMeleeMitigation() const;
	// bool GetIllusionPersistence() const;
	// uint16 Getextra_xtargets() const;
	// bool GetShroudofStealth() const;
	// uint16 GetReduceFallDamage() const;
	// uint8 GetTradeSkillMastery() const;
	// int16 GetNoBreakAESneak() const;
	// int16 GetFeignedCastOnChance() const;
	// int32 GetDivineSaveChance(int idx) const;
	// uint32 GetDeathSave(int idx) const;
	// int32 GetAccuracy(int idx) const;
	// int16 GetSkillDmgTaken(int idx) const;
	// uint32 GetSpellTriggers(int idx) const;
	// uint32 GetSpellOnKill(int idx) const;
	// uint32 GetSpellOnDeath(int idx) const;
	// int32 GetCritDmgMod(int idx) const;
	// int32 GetSkillReuseTime(int idx) const;
	// int32 GetSkillDamageAmount(int idx) const;
	// int GetHPPercCap(int idx) const;
	// int GetManaPercCap(int idx) const;
	// int GetEndPercCap(int idx) const;
	// uint8 GetFocusEffects(int idx) const;
	// int16 GetFocusEffectsWorn(int idx) const;
	// int32 GetSkillDamageAmount2(int idx) const;
	// uint32 GetNegateAttacks(int idx) const;
	// uint32 GetMitigateMeleeRune(int idx) const;
	// uint32 GetMeleeThresholdGuard(int idx) const;
	// uint32 GetSpellThresholdGuard(int idx) const;
	// uint32 GetMitigateSpellRune(int idx) const;
	// uint32 GetMitigateDotRune(int idx) const;
	// uint32 GetManaAbsorbPercentDamage(int idx) const;
	// int32 GetImprovedTaunt(int idx) const;
	// int8 GetRoot(int idx) const;
	// uint32 GetAbsorbMagicAtt(int idx) const;
	// uint32 GetMeleeRune(int idx) const;
	// int32 GetAStacker(int idx) const;
	// int32 GetBStacker(int idx) const;
	// int32 GetCStacker(int idx) const;
	// int32 GetDStacker(int idx) const;
	// bool GetLimitToSkill(int idx) const;
	// uint32 GetSkillProc(int idx) const;
	// uint32 GetSkillProcSuccess(int idx) const;
	// uint32 GetPC_Pet_Rampage(int idx) const;
	// int32 GetSkillAttackProc(int idx) const;
	// int32 GetSlayUndead(int idx) const;
	// int32 GetGiveDoubleRiposte(int idx) const;
	// uint32 GetRaiseSkillCap(int idx) const;
	// int32 GetSEResist(int idx) const;
	// int32 GetFinishingBlow(int idx) const;
	// uint32 GetFinishingBlowLvl(int idx) const;
	// uint32 GetHeadShot(int idx) const;
	// uint8 GetHSLevel(int idx) const;
	// uint32 GetAssassinate(int idx) const;
	// uint8 GetAssassinateLevel(int idx) const;
	// int32 GetReduceTradeskillFail(int idx) const;
};