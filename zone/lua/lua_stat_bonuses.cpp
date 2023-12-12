#include <sol/sol.hpp>

#include "lua_stat_bonuses.h"

void lua_register_stat_bonuses(sol::state_view &sv)
{
	auto bonuses = sv.new_usertype<Lua_StatBonuses>("StatBonuses", sol::constructors<Lua_StatBonuses()>());
	bonuses["AC"] = &Lua_StatBonuses::GetAC;
	// bonuses["AbsorbMagicAtt"] = &Lua_StatBonuses::GetAbsorbMagicAtt;
	// bonuses["Accuracy"] = &Lua_StatBonuses::GetAccuracy;
	// bonuses["adjusted_casting_skill"] = &Lua_StatBonuses::Getadjusted_casting_skill;
	// bonuses["AggroRange"] = &Lua_StatBonuses::GetAggroRange;
	// bonuses["AGI"] = &Lua_StatBonuses::GetAGI;
	// bonuses["AGICapMod"] = &Lua_StatBonuses::GetAGICapMod;
	// bonuses["AlterNPCLevel"] = &Lua_StatBonuses::GetAlterNPCLevel;
	// bonuses["Ambidexterity"] = &Lua_StatBonuses::GetAmbidexterity;
	// bonuses["Amplification"] = &Lua_StatBonuses::GetAmplification;
	// bonuses["AntiGate"] = &Lua_StatBonuses::GetAntiGate;
	// bonuses["ArcheryDamageModifier"] = &Lua_StatBonuses::GetArcheryDamageModifier;
	// bonuses["Assassinate"] = &Lua_StatBonuses::GetAssassinate;
	// bonuses["AssassinateLevel"] = &Lua_StatBonuses::GetAssassinateLevel;
	// bonuses["AssistRange"] = &Lua_StatBonuses::GetAssistRange;
	// bonuses["AStacker"] = &Lua_StatBonuses::GetAStacker;
	// bonuses["ATK"] = &Lua_StatBonuses::GetATK;
	// bonuses["AvoidMeleeChance"] = &Lua_StatBonuses::GetAvoidMeleeChance;
	// bonuses["AvoidMeleeChanceEffect"] = &Lua_StatBonuses::GetAvoidMeleeChanceEffect;
	// bonuses["BaseMovementSpeed"] = &Lua_StatBonuses::GetBaseMovementSpeed;
	// bonuses["BerserkSPA"] = &Lua_StatBonuses::GetBerserkSPA;
	// bonuses["BindWound"] = &Lua_StatBonuses::GetBindWound;
	// bonuses["BlockBehind"] = &Lua_StatBonuses::GetBlockBehind;
	// bonuses["BlockNextSpell"] = &Lua_StatBonuses::GetBlockNextSpell;
	// bonuses["brassMod"] = &Lua_StatBonuses::GetbrassMod;
	// bonuses["BStacker"] = &Lua_StatBonuses::GetBStacker;
	// bonuses["BuffSlotIncrease"] = &Lua_StatBonuses::GetBuffSlotIncrease;
	// bonuses["CHA"] = &Lua_StatBonuses::GetCHA;
	// bonuses["CHACapMod"] = &Lua_StatBonuses::GetCHACapMod;
	// bonuses["ChannelChanceItems"] = &Lua_StatBonuses::GetChannelChanceItems;
	// bonuses["ChannelChanceSpells"] = &Lua_StatBonuses::GetChannelChanceSpells;
	// bonuses["CharmBreakChance"] = &Lua_StatBonuses::GetCharmBreakChance;
	// bonuses["Clairvoyance"] = &Lua_StatBonuses::GetClairvoyance;
	// bonuses["CombatStability"] = &Lua_StatBonuses::GetCombatStability;
	// bonuses["ConsumeProjectile"] = &Lua_StatBonuses::GetConsumeProjectile;
	// bonuses["Corrup"] = &Lua_StatBonuses::GetCorrup;
	// bonuses["CorrupCapMod"] = &Lua_StatBonuses::GetCorrupCapMod;
	// bonuses["CR"] = &Lua_StatBonuses::GetCR;
	// bonuses["CRCapMod"] = &Lua_StatBonuses::GetCRCapMod;
	// bonuses["CrippBlowChance"] = &Lua_StatBonuses::GetCrippBlowChance;
	// bonuses["CritDmgMod"] = &Lua_StatBonuses::GetCritDmgMod;
	// bonuses["CriticalDoTChance"] = &Lua_StatBonuses::GetCriticalDoTChance;
	// bonuses["CriticalDotDecay"] = &Lua_StatBonuses::GetCriticalDotDecay;
	// bonuses["CriticalHealChance"] = &Lua_StatBonuses::GetCriticalHealChance;
	// bonuses["CriticalHealDecay"] = &Lua_StatBonuses::GetCriticalHealDecay;
	// bonuses["CriticalHealOverTime"] = &Lua_StatBonuses::GetCriticalHealOverTime;
	// bonuses["CriticalHitChance"] = &Lua_StatBonuses::GetCriticalHitChance;
	// bonuses["CriticalMend"] = &Lua_StatBonuses::GetCriticalMend;
	// bonuses["CriticalRegenDecay"] = &Lua_StatBonuses::GetCriticalRegenDecay;
	// bonuses["CriticalSpellChance"] = &Lua_StatBonuses::GetCriticalSpellChance;
	// bonuses["CStacker"] = &Lua_StatBonuses::GetCStacker;
	// bonuses["DamageModifier"] = &Lua_StatBonuses::GetDamageModifier;
	// bonuses["DamageModifier2"] = &Lua_StatBonuses::GetDamageModifier2;
	// bonuses["DamageShield"] = &Lua_StatBonuses::GetDamageShield;
	// bonuses["DamageShieldSpellID"] = &Lua_StatBonuses::GetDamageShieldSpellID;
	// bonuses["DamageShieldType"] = &Lua_StatBonuses::GetDamageShieldType;
	// bonuses["DeathSave"] = &Lua_StatBonuses::GetDeathSave;
	// bonuses["DelayDeath"] = &Lua_StatBonuses::GetDelayDeath;
	// bonuses["DEX"] = &Lua_StatBonuses::GetDEX;
	// bonuses["DEXCapMod"] = &Lua_StatBonuses::GetDEXCapMod;
	// bonuses["DistanceRemoval"] = &Lua_StatBonuses::GetDistanceRemoval;
	// bonuses["DivineAura"] = &Lua_StatBonuses::GetDivineAura;
	// bonuses["DivineSaveChance"] = &Lua_StatBonuses::GetDivineSaveChance;
	// bonuses["DodgeChance"] = &Lua_StatBonuses::GetDodgeChance;
	// bonuses["DotCritDmgIncrease"] = &Lua_StatBonuses::GetDotCritDmgIncrease;
	// bonuses["DoTShielding"] = &Lua_StatBonuses::GetDoTShielding;
	// bonuses["DoubleAttackChance"] = &Lua_StatBonuses::GetDoubleAttackChance;
	// bonuses["DoubleRangedAttack"] = &Lua_StatBonuses::GetDoubleRangedAttack;
	// bonuses["DoubleRiposte"] = &Lua_StatBonuses::GetDoubleRiposte;
	// bonuses["DoubleSpecialAttack"] = &Lua_StatBonuses::GetDoubleSpecialAttack;
	// bonuses["DR"] = &Lua_StatBonuses::GetDR;
	// bonuses["DRCapMod"] = &Lua_StatBonuses::GetDRCapMod;
	// bonuses["DSMitigation"] = &Lua_StatBonuses::GetDSMitigation;
	// bonuses["DSMitigationOffHand"] = &Lua_StatBonuses::GetDSMitigationOffHand;
	// bonuses["DStacker"] = &Lua_StatBonuses::GetDStacker;
	// bonuses["DualWieldChance"] = &Lua_StatBonuses::GetDualWieldChance;
	// bonuses["effective_casting_level"] = &Lua_StatBonuses::Geteffective_casting_level;
	// bonuses["EndPercCap"] = &Lua_StatBonuses::GetEndPercCap;
	// bonuses["Endurance"] = &Lua_StatBonuses::GetEndurance;
	// bonuses["EnduranceReduction"] = &Lua_StatBonuses::GetEnduranceReduction;
	// bonuses["EnduranceRegen"] = &Lua_StatBonuses::GetEnduranceRegen;
	// bonuses["extra_xtargets"] = &Lua_StatBonuses::Getextra_xtargets;
	// bonuses["ExtraAttackChance"] = &Lua_StatBonuses::GetExtraAttackChance;
	// bonuses["FactionModPct"] = &Lua_StatBonuses::GetFactionModPct;
	// bonuses["Fearless"] = &Lua_StatBonuses::GetFearless;
	// bonuses["FeignedCastOnChance"] = &Lua_StatBonuses::GetFeignedCastOnChance;
	// bonuses["FinishingBlow"] = &Lua_StatBonuses::GetFinishingBlow;
	// bonuses["FinishingBlowLvl"] = &Lua_StatBonuses::GetFinishingBlowLvl;
	// bonuses["FlurryChance"] = &Lua_StatBonuses::GetFlurryChance;
	// bonuses["FocusEffects"] = &Lua_StatBonuses::GetFocusEffects;
	// bonuses["FocusEffectsWorn"] = &Lua_StatBonuses::GetFocusEffectsWorn;
	// bonuses["ForageAdditionalItems"] = &Lua_StatBonuses::GetForageAdditionalItems;
	// bonuses["FR"] = &Lua_StatBonuses::GetFR;
	// bonuses["FRCapMod"] = &Lua_StatBonuses::GetFRCapMod;
	// bonuses["FrenziedDevastation"] = &Lua_StatBonuses::GetFrenziedDevastation;
	// bonuses["FrontalBackstabChance"] = &Lua_StatBonuses::GetFrontalBackstabChance;
	// bonuses["FrontalBackstabMinDmg"] = &Lua_StatBonuses::GetFrontalBackstabMinDmg;
	// bonuses["FrontalStunResist"] = &Lua_StatBonuses::GetFrontalStunResist;
	// bonuses["GiveDoubleAttack"] = &Lua_StatBonuses::GetGiveDoubleAttack;
	// bonuses["GiveDoubleRiposte"] = &Lua_StatBonuses::GetGiveDoubleRiposte;
	// bonuses["GivePetGroupTarget"] = &Lua_StatBonuses::GetGivePetGroupTarget;
	// bonuses["GravityEffect"] = &Lua_StatBonuses::GetGravityEffect;
	// bonuses["haste"] = &Lua_StatBonuses::Gethaste;
	// bonuses["hastetype2"] = &Lua_StatBonuses::Gethastetype2;
	// bonuses["hastetype3"] = &Lua_StatBonuses::Gethastetype3;
	// bonuses["hatemod"] = &Lua_StatBonuses::Gethatemod;
	// bonuses["HeadShot"] = &Lua_StatBonuses::GetHeadShot;
	// bonuses["HealAmt"] = &Lua_StatBonuses::GetHealAmt;
	// bonuses["HealRate"] = &Lua_StatBonuses::GetHealRate;
	// bonuses["HeroicAGI"] = &Lua_StatBonuses::GetHeroicAGI;
	// bonuses["HeroicCHA"] = &Lua_StatBonuses::GetHeroicCHA;
	// bonuses["HeroicCorrup"] = &Lua_StatBonuses::GetHeroicCorrup;
	// bonuses["HeroicCR"] = &Lua_StatBonuses::GetHeroicCR;
	// bonuses["HeroicDEX"] = &Lua_StatBonuses::GetHeroicDEX;
	// bonuses["HeroicDR"] = &Lua_StatBonuses::GetHeroicDR;
	// bonuses["HeroicFR"] = &Lua_StatBonuses::GetHeroicFR;
	// bonuses["HeroicINT"] = &Lua_StatBonuses::GetHeroicINT;
	// bonuses["HeroicMR"] = &Lua_StatBonuses::GetHeroicMR;
	// bonuses["HeroicPR"] = &Lua_StatBonuses::GetHeroicPR;
	// bonuses["HeroicSTA"] = &Lua_StatBonuses::GetHeroicSTA;
	// bonuses["HeroicSTR"] = &Lua_StatBonuses::GetHeroicSTR;
	// bonuses["HeroicWIS"] = &Lua_StatBonuses::GetHeroicWIS;
	// bonuses["HitChance"] = &Lua_StatBonuses::GetHitChance;
	// bonuses["HitChanceEffect"] = &Lua_StatBonuses::GetHitChanceEffect;
	// bonuses["HP"] = &Lua_StatBonuses::GetHP;
	// bonuses["HPPercCap"] = &Lua_StatBonuses::GetHPPercCap;
	// bonuses["HPRegen"] = &Lua_StatBonuses::GetHPRegen;
	// bonuses["HPToManaConvert"] = &Lua_StatBonuses::GetHPToManaConvert;
	// bonuses["HSLevel"] = &Lua_StatBonuses::GetHSLevel;
	// bonuses["HundredHands"] = &Lua_StatBonuses::GetHundredHands;
	// bonuses["IllusionPersistence"] = &Lua_StatBonuses::GetIllusionPersistence;
	// bonuses["ImmuneToFlee"] = &Lua_StatBonuses::GetImmuneToFlee;
	// bonuses["ImprovedReclaimEnergy"] = &Lua_StatBonuses::GetImprovedReclaimEnergy;
	// bonuses["ImprovedTaunt"] = &Lua_StatBonuses::GetImprovedTaunt;
	// bonuses["IncreaseBlockChance"] = &Lua_StatBonuses::GetIncreaseBlockChance;
	// bonuses["IncreaseChanceMemwipe"] = &Lua_StatBonuses::GetIncreaseChanceMemwipe;
	// bonuses["IncreaseRunSpeedCap"] = &Lua_StatBonuses::GetIncreaseRunSpeedCap;
	// bonuses["inhibitmelee"] = &Lua_StatBonuses::Getinhibitmelee;
	// bonuses["INT"] = &Lua_StatBonuses::GetINT;
	// bonuses["INTCapMod"] = &Lua_StatBonuses::GetINTCapMod;
	// bonuses["IsBlind"] = &Lua_StatBonuses::GetIsBlind;
	// bonuses["IsFeared"] = &Lua_StatBonuses::GetIsFeared;
	// bonuses["ItemATKCap"] = &Lua_StatBonuses::GetItemATKCap;
	// bonuses["ItemHPRegenCap"] = &Lua_StatBonuses::GetItemHPRegenCap;
	// bonuses["ItemManaRegenCap"] = &Lua_StatBonuses::GetItemManaRegenCap;
	// bonuses["LimitToSkill"] = &Lua_StatBonuses::GetLimitToSkill;
	// bonuses["MagicWeapon"] = &Lua_StatBonuses::GetMagicWeapon;
	// bonuses["Mana"] = &Lua_StatBonuses::GetMana;
	// bonuses["ManaAbsorbPercentDamage"] = &Lua_StatBonuses::GetManaAbsorbPercentDamage;
	// bonuses["ManaPercCap"] = &Lua_StatBonuses::GetManaPercCap;
	// bonuses["ManaRegen"] = &Lua_StatBonuses::GetManaRegen;
	// bonuses["MasteryofPast"] = &Lua_StatBonuses::GetMasteryofPast;
	// bonuses["MaxBindWound"] = &Lua_StatBonuses::GetMaxBindWound;
	// bonuses["MaxHP"] = &Lua_StatBonuses::GetMaxHP;
	// bonuses["MaxHPChange"] = &Lua_StatBonuses::GetMaxHPChange;
	// bonuses["MeleeLifetap"] = &Lua_StatBonuses::GetMeleeLifetap;
	// bonuses["MeleeMitigation"] = &Lua_StatBonuses::GetMeleeMitigation;
	// bonuses["MeleeMitigationEffect"] = &Lua_StatBonuses::GetMeleeMitigationEffect;
	// bonuses["MeleeRune"] = &Lua_StatBonuses::GetMeleeRune;
	// bonuses["MeleeSkillCheck"] = &Lua_StatBonuses::GetMeleeSkillCheck;
	// bonuses["MeleeSkillCheckSkill"] = &Lua_StatBonuses::GetMeleeSkillCheckSkill;
	// bonuses["MeleeThresholdGuard"] = &Lua_StatBonuses::GetMeleeThresholdGuard;
	// bonuses["Metabolism"] = &Lua_StatBonuses::GetMetabolism;
	// bonuses["MinDamageModifier"] = &Lua_StatBonuses::GetMinDamageModifier;
	// bonuses["MitigateDotRune"] = &Lua_StatBonuses::GetMitigateDotRune;
	// bonuses["MitigateMeleeRune"] = &Lua_StatBonuses::GetMitigateMeleeRune;
	// bonuses["MitigateSpellRune"] = &Lua_StatBonuses::GetMitigateSpellRune;
	// bonuses["movementspeed"] = &Lua_StatBonuses::Getmovementspeed;
	// bonuses["MR"] = &Lua_StatBonuses::GetMR;
	// bonuses["MRCapMod"] = &Lua_StatBonuses::GetMRCapMod;
	// bonuses["NegateAttacks"] = &Lua_StatBonuses::GetNegateAttacks;
	// bonuses["NegateEffects"] = &Lua_StatBonuses::GetNegateEffects;
	// bonuses["NegateIfCombat"] = &Lua_StatBonuses::GetNegateIfCombat;
	// bonuses["NoBreakAESneak"] = &Lua_StatBonuses::GetNoBreakAESneak;
	// bonuses["OffhandRiposteFail"] = &Lua_StatBonuses::GetOffhandRiposteFail;
	// bonuses["Packrat"] = &Lua_StatBonuses::GetPackrat;
	// bonuses["ParryChance"] = &Lua_StatBonuses::GetParryChance;
	// bonuses["PC_Pet_Flurry"] = &Lua_StatBonuses::GetPC_Pet_Flurry;
	// bonuses["PC_Pet_Rampage"] = &Lua_StatBonuses::GetPC_Pet_Rampage;
	// bonuses["percussionMod"] = &Lua_StatBonuses::GetpercussionMod;
	// bonuses["PersistantCasting"] = &Lua_StatBonuses::GetPersistantCasting;
	// bonuses["PetAvoidance"] = &Lua_StatBonuses::GetPetAvoidance;
	// bonuses["PetCriticalHit"] = &Lua_StatBonuses::GetPetCriticalHit;
	// bonuses["PetFlurry"] = &Lua_StatBonuses::GetPetFlurry;
	// bonuses["PetMaxHP"] = &Lua_StatBonuses::GetPetMaxHP;
	// bonuses["PetMeleeMitigation"] = &Lua_StatBonuses::GetPetMeleeMitigation;
	// bonuses["PR"] = &Lua_StatBonuses::GetPR;
	// bonuses["PRCapMod"] = &Lua_StatBonuses::GetPRCapMod;
	// bonuses["ProcChance"] = &Lua_StatBonuses::GetProcChance;
	// bonuses["ProcChanceSPA"] = &Lua_StatBonuses::GetProcChanceSPA;
	// bonuses["RaiseSkillCap"] = &Lua_StatBonuses::GetRaiseSkillCap;
	// bonuses["ReduceFallDamage"] = &Lua_StatBonuses::GetReduceFallDamage;
	// bonuses["ReduceTradeskillFail"] = &Lua_StatBonuses::GetReduceTradeskillFail;
	// bonuses["reflect_chance"] = &Lua_StatBonuses::Getreflect_chance;
	// bonuses["ResistFearChance"] = &Lua_StatBonuses::GetResistFearChance;
	// bonuses["ResistSpellChance"] = &Lua_StatBonuses::GetResistSpellChance;
	// bonuses["ReverseDamageShield"] = &Lua_StatBonuses::GetReverseDamageShield;
	// bonuses["ReverseDamageShieldSpellID"] = &Lua_StatBonuses::GetReverseDamageShieldSpellID;
	// bonuses["ReverseDamageShieldType"] = &Lua_StatBonuses::GetReverseDamageShieldType;
	// bonuses["RiposteChance"] = &Lua_StatBonuses::GetRiposteChance;
	// bonuses["Root"] = &Lua_StatBonuses::GetRoot;
	// bonuses["RootBreakChance"] = &Lua_StatBonuses::GetRootBreakChance;
	// bonuses["SalvageChance"] = &Lua_StatBonuses::GetSalvageChance;
	// bonuses["Sanctuary"] = &Lua_StatBonuses::GetSanctuary;
	// bonuses["Screech"] = &Lua_StatBonuses::GetScreech;
	// bonuses["SecondaryDmgInc"] = &Lua_StatBonuses::GetSecondaryDmgInc;
	// bonuses["SeeInvis"] = &Lua_StatBonuses::GetSeeInvis;
	// bonuses["SEResist"] = &Lua_StatBonuses::GetSEResist;
	// bonuses["ShieldBlock"] = &Lua_StatBonuses::GetShieldBlock;
	// bonuses["ShieldEquipDmgMod"] = &Lua_StatBonuses::GetShieldEquipDmgMod;
	// bonuses["ShroudofStealth"] = &Lua_StatBonuses::GetShroudofStealth;
	// bonuses["singingMod"] = &Lua_StatBonuses::GetsingingMod;
	// bonuses["SkillAttackProc"] = &Lua_StatBonuses::GetSkillAttackProc;
	// bonuses["SkillDamageAmount"] = &Lua_StatBonuses::GetSkillDamageAmount;
	// bonuses["SkillDamageAmount2"] = &Lua_StatBonuses::GetSkillDamageAmount2;
	// bonuses["SkillDmgTaken"] = &Lua_StatBonuses::GetSkillDmgTaken;
	// bonuses["skillmod"] = &Lua_StatBonuses::Getskillmod;
	// bonuses["skillmodmax"] = &Lua_StatBonuses::Getskillmodmax;
	// bonuses["SkillProc"] = &Lua_StatBonuses::GetSkillProc;
	// bonuses["SkillProcSuccess"] = &Lua_StatBonuses::GetSkillProcSuccess;
	// bonuses["SkillReuseTime"] = &Lua_StatBonuses::GetSkillReuseTime;
	// bonuses["SlayUndead"] = &Lua_StatBonuses::GetSlayUndead;
	// bonuses["songModCap"] = &Lua_StatBonuses::GetsongModCap;
	// bonuses["SongRange"] = &Lua_StatBonuses::GetSongRange;
	// bonuses["SpellCritDmgIncNoStack"] = &Lua_StatBonuses::GetSpellCritDmgIncNoStack;
	// bonuses["SpellCritDmgIncrease"] = &Lua_StatBonuses::GetSpellCritDmgIncrease;
	// bonuses["SpellDamageShield"] = &Lua_StatBonuses::GetSpellDamageShield;
	// bonuses["SpellDmg"] = &Lua_StatBonuses::GetSpellDmg;
	// bonuses["SpellOnDeath"] = &Lua_StatBonuses::GetSpellOnDeath;
	// bonuses["SpellOnKill"] = &Lua_StatBonuses::GetSpellOnKill;
	// bonuses["SpellProcChance"] = &Lua_StatBonuses::GetSpellProcChance;
	// bonuses["SpellShield"] = &Lua_StatBonuses::GetSpellShield;
	// bonuses["SpellThresholdGuard"] = &Lua_StatBonuses::GetSpellThresholdGuard;
	// bonuses["SpellTriggers"] = &Lua_StatBonuses::GetSpellTriggers;
	// bonuses["STA"] = &Lua_StatBonuses::GetSTA;
	// bonuses["STACapMod"] = &Lua_StatBonuses::GetSTACapMod;
	// bonuses["STR"] = &Lua_StatBonuses::GetSTR;
	// bonuses["STRCapMod"] = &Lua_StatBonuses::GetSTRCapMod;
	// bonuses["StrikeThrough"] = &Lua_StatBonuses::GetStrikeThrough;
	// bonuses["stringedMod"] = &Lua_StatBonuses::GetstringedMod;
	// bonuses["StunBashChance"] = &Lua_StatBonuses::GetStunBashChance;
	// bonuses["StunResist"] = &Lua_StatBonuses::GetStunResist;
	// bonuses["TradeSkillMastery"] = &Lua_StatBonuses::GetTradeSkillMastery;
	// bonuses["TriggerMeleeThreshold"] = &Lua_StatBonuses::GetTriggerMeleeThreshold;
	// bonuses["TriggerOnValueAmount"] = &Lua_StatBonuses::GetTriggerOnValueAmount;
	// bonuses["TriggerSpellThreshold"] = &Lua_StatBonuses::GetTriggerSpellThreshold;
	// bonuses["TripleAttackChance"] = &Lua_StatBonuses::GetTripleAttackChance;
	// bonuses["TripleBackstab"] = &Lua_StatBonuses::GetTripleBackstab;
	// bonuses["TwoHandBluntBlock"] = &Lua_StatBonuses::GetTwoHandBluntBlock;
	// bonuses["UnfailingDivinity"] = &Lua_StatBonuses::GetUnfailingDivinity;
	// bonuses["Vampirism"] = &Lua_StatBonuses::GetVampirism;
	// bonuses["VoiceGraft"] = &Lua_StatBonuses::GetVoiceGraft;
	// bonuses["windMod"] = &Lua_StatBonuses::GetwindMod;
	// bonuses["WIS"] = &Lua_StatBonuses::GetWIS;
	// bonuses["WISCapMod"] = &Lua_StatBonuses::GetWISCapMod;
	// bonuses["XPRateMod"] = &Lua_StatBonuses::GetXPRateMod;
}