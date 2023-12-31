#include "../masterentity.h"
#include "lua_item.h"

Lua_Item::Lua_Item(uint32 item_id) {
	const EQ::ItemData *t = database.GetItem(item_id);
	SetLuaPtrData(t);
}

int Lua_Item::GetMinStatus() {
	Lua_Safe_Call_Int();
	return self->MinStatus;
}

int Lua_Item::GetItemClass() {
	Lua_Safe_Call_Int();
	return self->ItemClass;
}

const char *Lua_Item::GetName() {
	Lua_Safe_Call_String();
	return self->Name;
}

const char *Lua_Item::GetLore() {
	Lua_Safe_Call_String();
	return self->Lore;
}

const char *Lua_Item::GetIDFile() {
	Lua_Safe_Call_String();
	return self->IDFile;
}

uint32 Lua_Item::GetID() {
	Lua_Safe_Call_Int();
	return self->ID;
}

int Lua_Item::GetWeight() {
	Lua_Safe_Call_Int();
	return self->Weight;
}

int Lua_Item::GetNoRent() {
	Lua_Safe_Call_Int();
	return self->NoRent;
}

int Lua_Item::GetNoDrop() {
	Lua_Safe_Call_Int();
	return self->NoDrop;
}

int Lua_Item::GetSize() {
	Lua_Safe_Call_Int();
	return self->Size;
}

uint32 Lua_Item::GetSlots() {
	Lua_Safe_Call_Int();
	return self->Slots;
}

uint32 Lua_Item::GetPrice() {
	Lua_Safe_Call_Int();
	return self->Price;
}

uint32 Lua_Item::GetIcon() {
	Lua_Safe_Call_Int();
	return self->Icon;
}

int32 Lua_Item::GetLoreGroup() {
	Lua_Safe_Call_Int();
	return self->LoreGroup;
}

bool Lua_Item::GetLoreFlag() {
	Lua_Safe_Call_Bool();
	return self->LoreFlag;
}

bool Lua_Item::GetPendingLoreFlag() {
	Lua_Safe_Call_Bool();
	return self->PendingLoreFlag;
}

bool Lua_Item::GetArtifactFlag() {
	Lua_Safe_Call_Bool();
	return self->ArtifactFlag;
}

bool Lua_Item::GetSummonedFlag() {
	Lua_Safe_Call_Bool();
	return self->SummonedFlag;
}

int Lua_Item::GetFVNoDrop() {
	Lua_Safe_Call_Int();
	return self->FVNoDrop;
}

uint32 Lua_Item::GetFavor() {
	Lua_Safe_Call_Int();
	return self->Favor;
}

uint32 Lua_Item::GetGuildFavor() {
	Lua_Safe_Call_Int();
	return self->GuildFavor;
}

uint32 Lua_Item::GetPointType() {
	Lua_Safe_Call_Int();
	return self->PointType;
}

int Lua_Item::GetBagType() {
	Lua_Safe_Call_Int();
	return self->BagType;
}

int Lua_Item::GetBagSlots() {
	Lua_Safe_Call_Int();
	return self->BagSlots;
}

int Lua_Item::GetBagSize() {
	Lua_Safe_Call_Int();
	return self->BagSize;
}

int Lua_Item::GetBagWR() {
	Lua_Safe_Call_Int();
	return self->BagWR;
}

bool Lua_Item::GetBenefitFlag() {
	Lua_Safe_Call_Bool();
	return self->BenefitFlag;
}

bool Lua_Item::GetTradeskills() {
	Lua_Safe_Call_Bool();
	return self->Tradeskills;
}

int Lua_Item::GetCR() {
	Lua_Safe_Call_Int();
	return self->CR;
}

int Lua_Item::GetDR() {
	Lua_Safe_Call_Int();
	return self->DR;
}

int Lua_Item::GetPR() {
	Lua_Safe_Call_Int();
	return self->PR;
}

int Lua_Item::GetMR() {
	Lua_Safe_Call_Int();
	return self->MR;
}

int Lua_Item::GetFR() {
	Lua_Safe_Call_Int();
	return self->FR;
}

int Lua_Item::GetAStr() {
	Lua_Safe_Call_Int();
	return self->AStr;
}

int Lua_Item::GetASta() {
	Lua_Safe_Call_Int();
	return self->ASta;
}

int Lua_Item::GetAAgi() {
	Lua_Safe_Call_Int();
	return self->AAgi;
}

int Lua_Item::GetADex() {
	Lua_Safe_Call_Int();
	return self->ADex;
}

int Lua_Item::GetACha() {
	Lua_Safe_Call_Int();
	return self->ACha;
}

int Lua_Item::GetAInt() {
	Lua_Safe_Call_Int();
	return self->AInt;
}

int Lua_Item::GetAWis() {
	Lua_Safe_Call_Int();
	return self->AWis;
}

int Lua_Item::GetHP() {
	Lua_Safe_Call_Int();
	return self->HP;
}

int Lua_Item::GetMana() {
	Lua_Safe_Call_Int();
	return self->Mana;
}

int Lua_Item::GetAC() {
	Lua_Safe_Call_Int();
	return self->AC;
}

uint32 Lua_Item::GetDeity() {
	Lua_Safe_Call_Int();
	return self->Deity;
}

int Lua_Item::GetSkillModValue() {
	Lua_Safe_Call_Int();
	return self->SkillModValue;
}

uint32 Lua_Item::GetSkillModType() {
	Lua_Safe_Call_Int();
	return self->SkillModType;
}

uint32 Lua_Item::GetBaneDmgRace() {
	Lua_Safe_Call_Int();
	return self->BaneDmgRace;
}

int Lua_Item::GetBaneDmgAmt() {
	Lua_Safe_Call_Int();
	return self->BaneDmgAmt;
}

uint32 Lua_Item::GetBaneDmgBody() {
	Lua_Safe_Call_Int();
	return self->BaneDmgBody;
}

bool Lua_Item::GetMagic() {
	Lua_Safe_Call_Bool();
	return self->Magic;
}

int Lua_Item::GetCastTime_() {
	Lua_Safe_Call_Int();
	return self->CastTime_;
}

int Lua_Item::GetReqLevel() {
	Lua_Safe_Call_Int();
	return self->ReqLevel;
}

uint32 Lua_Item::GetBardType() {
	Lua_Safe_Call_Int();
	return self->BardType;
}

int Lua_Item::GetBardValue() {
	Lua_Safe_Call_Int();
	return self->BardValue;
}

int Lua_Item::GetLight() {
	Lua_Safe_Call_Int();
	return self->Light;
}

int Lua_Item::GetDelay() {
	Lua_Safe_Call_Int();
	return self->Delay;
}

int Lua_Item::GetRecLevel() {
	Lua_Safe_Call_Int();
	return self->RecLevel;
}

int Lua_Item::GetRecSkill() {
	Lua_Safe_Call_Int();
	return self->RecSkill;
}

int Lua_Item::GetElemDmgType() {
	Lua_Safe_Call_Int();
	return self->ElemDmgType;
}

int Lua_Item::GetElemDmgAmt() {
	Lua_Safe_Call_Int();
	return self->ElemDmgAmt;
}

int Lua_Item::GetRange() {
	Lua_Safe_Call_Int();
	return self->Range;
}

uint32 Lua_Item::GetDamage() {
	Lua_Safe_Call_Int();
	return self->Damage;
}

uint32 Lua_Item::GetColor() {
	Lua_Safe_Call_Int();
	return self->Color;
}

uint32 Lua_Item::GetClasses() {
	Lua_Safe_Call_Int();
	return self->Classes;
}

uint32 Lua_Item::GetRaces() {
	Lua_Safe_Call_Int();
	return self->Races;
}

int Lua_Item::GetMaxCharges() {
	Lua_Safe_Call_Int();
	return self->MaxCharges;
}

int Lua_Item::GetItemType() {
	Lua_Safe_Call_Int();
	return self->ItemType;
}

int Lua_Item::GetMaterial() {
	Lua_Safe_Call_Int();
	return self->Material;
}

double Lua_Item::GetSellRate() {
	Lua_Safe_Call_Real();
	return self->SellRate;
}

uint32 Lua_Item::GetFulfilment() {
	Lua_Safe_Call_Int();
	return self->Fulfilment;
}

int Lua_Item::GetCastTime() {
	Lua_Safe_Call_Int();
	return self->CastTime;
}

uint32 Lua_Item::GetEliteMaterial() {
	Lua_Safe_Call_Int();
	return self->EliteMaterial;
}

int Lua_Item::GetProcRate() {
	Lua_Safe_Call_Int();
	return self->ProcRate;
}

int Lua_Item::GetCombatEffects() {
	Lua_Safe_Call_Int();
	return self->CombatEffects;
}

int Lua_Item::GetShielding() {
	Lua_Safe_Call_Int();
	return self->Shielding;
}

int Lua_Item::GetStunResist() {
	Lua_Safe_Call_Int();
	return self->StunResist;
}

int Lua_Item::GetStrikeThrough() {
	Lua_Safe_Call_Int();
	return self->StrikeThrough;
}

uint32 Lua_Item::GetExtraDmgSkill() {
	Lua_Safe_Call_Int();
	return self->ExtraDmgSkill;
}

uint32 Lua_Item::GetExtraDmgAmt() {
	Lua_Safe_Call_Int();
	return self->ExtraDmgAmt;
}

int Lua_Item::GetSpellShield() {
	Lua_Safe_Call_Int();
	return self->SpellShield;
}

int Lua_Item::GetAvoidance() {
	Lua_Safe_Call_Int();
	return self->Avoidance;
}

int Lua_Item::GetAccuracy() {
	Lua_Safe_Call_Int();
	return self->Accuracy;
}

uint32 Lua_Item::GetCharmFileID() {
	Lua_Safe_Call_Int();
	return self->CharmFileID;
}

int Lua_Item::GetFactionMod1() {
	Lua_Safe_Call_Int();
	return self->FactionMod1;
}

int Lua_Item::GetFactionMod2() {
	Lua_Safe_Call_Int();
	return self->FactionMod2;
}

int Lua_Item::GetFactionMod3() {
	Lua_Safe_Call_Int();
	return self->FactionMod3;
}

int Lua_Item::GetFactionMod4() {
	Lua_Safe_Call_Int();
	return self->FactionMod4;
}

int Lua_Item::GetFactionAmt1() {
	Lua_Safe_Call_Int();
	return self->FactionAmt1;
}

int Lua_Item::GetFactionAmt2() {
	Lua_Safe_Call_Int();
	return self->FactionAmt2;
}

int Lua_Item::GetFactionAmt3() {
	Lua_Safe_Call_Int();
	return self->FactionAmt3;
}

int Lua_Item::GetFactionAmt4() {
	Lua_Safe_Call_Int();
	return self->FactionAmt4;
}

const char *Lua_Item::GetCharmFile() {
	Lua_Safe_Call_String();
	return self->CharmFile;
}

uint32 Lua_Item::GetAugType() {
	Lua_Safe_Call_Int();
	return self->AugType;
}

int Lua_Item::GetAugSlotType(int i) {
	Lua_Safe_Call_Int();

	if(i >= 5 || i < 0) {
		return 0;
	}

	return self->AugSlotType[i];
}

int Lua_Item::GetAugSlotVisible(int i) {
	Lua_Safe_Call_Int();

	if(i >= 5 || i < 0) {
		return 0;
	}

	return self->AugSlotVisible[i];
}

int Lua_Item::GetAugSlotUnk2(int i) {
	Lua_Safe_Call_Int();

	if(i >= 5 || i < 0) {
		return 0;
	}

	return self->AugSlotUnk2[i];
}

uint32 Lua_Item::GetLDoNTheme() {
	Lua_Safe_Call_Int();
	return self->LDoNTheme;
}

uint32 Lua_Item::GetLDoNPrice() {
	Lua_Safe_Call_Int();
	return self->LDoNPrice;
}

uint32 Lua_Item::GetLDoNSold() {
	Lua_Safe_Call_Int();
	return self->LDoNSold;
}

uint32 Lua_Item::GetBaneDmgRaceAmt() {
	Lua_Safe_Call_Int();
	return self->BaneDmgRaceAmt;
}

uint32 Lua_Item::GetAugRestrict() {
	Lua_Safe_Call_Int();
	return self->AugRestrict;
}

int32 Lua_Item::GetEndur() {
	Lua_Safe_Call_Int();
	return self->Endur;
}

int32 Lua_Item::GetDotShielding() {
	Lua_Safe_Call_Int();
	return self->DotShielding;
}

int32 Lua_Item::GetAttack() {
	Lua_Safe_Call_Int();
	return self->Attack;
}

int32 Lua_Item::GetRegen() {
	Lua_Safe_Call_Int();
	return self->Regen;
}

int32 Lua_Item::GetManaRegen() {
	Lua_Safe_Call_Int();
	return self->ManaRegen;
}

int32 Lua_Item::GetEnduranceRegen() {
	Lua_Safe_Call_Int();
	return self->EnduranceRegen;
}

int32 Lua_Item::GetHaste() {
	Lua_Safe_Call_Int();
	return self->Haste;
}

int32 Lua_Item::GetDamageShield() {
	Lua_Safe_Call_Int();
	return self->DamageShield;
}

uint32 Lua_Item::GetRecastDelay() {
	Lua_Safe_Call_Int();
	return self->RecastDelay;
}

uint32 Lua_Item::GetRecastType() {
	Lua_Safe_Call_Int();
	return self->RecastType;
}

uint32 Lua_Item::GetAugDistiller() {
	Lua_Safe_Call_Int();
	return self->AugDistiller;
}

bool Lua_Item::GetAttuneable() {
	Lua_Safe_Call_Bool();
	return self->Attuneable;
}

bool Lua_Item::GetNoPet() {
	Lua_Safe_Call_Bool();
	return self->NoPet;
}

bool Lua_Item::GetPotionBelt() {
	Lua_Safe_Call_Bool();
	return self->PotionBelt;
}

bool Lua_Item::GetStackable() {
	Lua_Safe_Call_Bool();
	return self->Stackable;
}

bool Lua_Item::GetNoTransfer() {
	Lua_Safe_Call_Bool();
	return self->NoTransfer;
}

bool Lua_Item::GetQuestItemFlag() {
	Lua_Safe_Call_Bool();
	return self->QuestItemFlag;
}

int Lua_Item::GetStackSize() {
	Lua_Safe_Call_Int();
	return self->StackSize;
}

int Lua_Item::GetPotionBeltSlots() {
	Lua_Safe_Call_Int();
	return self->PotionBeltSlots;
}

int Lua_Item::GetClick_Effect() {
	Lua_Safe_Call_Int();
	return self->Click.Effect;
}

int Lua_Item::GetClick_Type() {
	Lua_Safe_Call_Int();
	return self->Click.Type;
}

int Lua_Item::GetClick_Level() {
	Lua_Safe_Call_Int();
	return self->Click.Level;
}

int Lua_Item::GetClick_Level2() {
	Lua_Safe_Call_Int();
	return self->Click.Level2;
}

int Lua_Item::GetProc_Effect() {
	Lua_Safe_Call_Int();
	return self->Proc.Effect;
}

int Lua_Item::GetProc_Type() {
	Lua_Safe_Call_Int();
	return self->Proc.Type;
}

int Lua_Item::GetProc_Level() {
	Lua_Safe_Call_Int();
	return self->Proc.Level;
}

int Lua_Item::GetProc_Level2() {
	Lua_Safe_Call_Int();
	return self->Proc.Level2;
}

int Lua_Item::GetWorn_Effect() {
	Lua_Safe_Call_Int();
	return self->Worn.Effect;
}

int Lua_Item::GetWorn_Type() {
	Lua_Safe_Call_Int();
	return self->Worn.Type;
}

int Lua_Item::GetWorn_Level() {
	Lua_Safe_Call_Int();
	return self->Worn.Level;
}

int Lua_Item::GetWorn_Level2() {
	Lua_Safe_Call_Int();
	return self->Worn.Level2;
}

int Lua_Item::GetFocus_Effect() {
	Lua_Safe_Call_Int();
	return self->Focus.Effect;
}

int Lua_Item::GetFocus_Type() {
	Lua_Safe_Call_Int();
	return self->Focus.Type;
}

int Lua_Item::GetFocus_Level() {
	Lua_Safe_Call_Int();
	return self->Focus.Level;
}

int Lua_Item::GetFocus_Level2() {
	Lua_Safe_Call_Int();
	return self->Focus.Level2;
}

int Lua_Item::GetScroll_Effect() {
	Lua_Safe_Call_Int();
	return self->Scroll.Effect;
}

int Lua_Item::GetScroll_Type() {
	Lua_Safe_Call_Int();
	return self->Scroll.Type;
}

int Lua_Item::GetScroll_Level() {
	Lua_Safe_Call_Int();
	return self->Scroll.Level;
}

int Lua_Item::GetScroll_Level2() {
	Lua_Safe_Call_Int();
	return self->Scroll.Level2;
}

int Lua_Item::GetBard_Effect() {
	Lua_Safe_Call_Int();
	return self->Bard.Effect;
}

int Lua_Item::GetBard_Type() {
	Lua_Safe_Call_Int();
	return self->Bard.Type;
}

int Lua_Item::GetBard_Level() {
	Lua_Safe_Call_Int();
	return self->Bard.Level;
}

int Lua_Item::GetBard_Level2() {
	Lua_Safe_Call_Int();
	return self->Bard.Level2;
}

int Lua_Item::GetBook() {
	Lua_Safe_Call_Int();
	return self->Book;
}

uint32 Lua_Item::GetBookType() {
	Lua_Safe_Call_Int();
	return self->BookType;
}

const char *Lua_Item::GetFilename() {
	Lua_Safe_Call_String();
	return self->Filename;
}

int Lua_Item::GetSVCorruption() {
	Lua_Safe_Call_Int();
	return self->SVCorruption;
}

uint32 Lua_Item::GetPurity() {
	Lua_Safe_Call_Int();
	return self->Purity;
}

uint32 Lua_Item::GetBackstabDmg() {
	Lua_Safe_Call_Int();
	return self->BackstabDmg;
}

uint32 Lua_Item::GetDSMitigation() {
	Lua_Safe_Call_Int();
	return self->DSMitigation;
}

int Lua_Item::GetHeroicStr() {
	Lua_Safe_Call_Int();
	return self->HeroicStr;
}

int Lua_Item::GetHeroicInt() {
	Lua_Safe_Call_Int();
	return self->HeroicInt;
}

int Lua_Item::GetHeroicWis() {
	Lua_Safe_Call_Int();
	return self->HeroicWis;
}

int Lua_Item::GetHeroicAgi() {
	Lua_Safe_Call_Int();
	return self->HeroicAgi;
}

int Lua_Item::GetHeroicDex() {
	Lua_Safe_Call_Int();
	return self->HeroicDex;
}

int Lua_Item::GetHeroicSta() {
	Lua_Safe_Call_Int();
	return self->HeroicSta;
}

int Lua_Item::GetHeroicCha() {
	Lua_Safe_Call_Int();
	return self->HeroicCha;
}

int Lua_Item::GetHeroicMR() {
	Lua_Safe_Call_Int();
	return self->HeroicMR;
}

int Lua_Item::GetHeroicFR() {
	Lua_Safe_Call_Int();
	return self->HeroicFR;
}

int Lua_Item::GetHeroicCR() {
	Lua_Safe_Call_Int();
	return self->HeroicCR;
}

int Lua_Item::GetHeroicDR() {
	Lua_Safe_Call_Int();
	return self->HeroicDR;
}

int Lua_Item::GetHeroicPR() {
	Lua_Safe_Call_Int();
	return self->HeroicPR;
}

int Lua_Item::GetHeroicSVCorrup() {
	Lua_Safe_Call_Int();
	return self->HeroicSVCorrup;
}

int Lua_Item::GetHealAmt() {
	Lua_Safe_Call_Int();
	return self->HealAmt;
}

int Lua_Item::GetSpellDmg() {
	Lua_Safe_Call_Int();
	return self->SpellDmg;
}

uint32 Lua_Item::GetLDoNSellBackRate() {
	Lua_Safe_Call_Int();
	return self->LDoNSellBackRate;
}

uint32 Lua_Item::GetScriptFileID() {
	Lua_Safe_Call_Int();
	return self->ScriptFileID;
}

int Lua_Item::GetExpendableArrow() {
	Lua_Safe_Call_Int();
	return self->ExpendableArrow;
}

uint32 Lua_Item::GetClairvoyance() {
	Lua_Safe_Call_Int();
	return self->Clairvoyance;
}

const char *Lua_Item::GetClickName() {
	Lua_Safe_Call_String();
	return self->ClickName;
}

const char *Lua_Item::GetProcName() {
	Lua_Safe_Call_String();
	return self->ProcName;
}

const char *Lua_Item::GetWornName() {
	Lua_Safe_Call_String();
	return self->WornName;
}

const char *Lua_Item::GetFocusName() {
	Lua_Safe_Call_String();
	return self->FocusName;
}

const char *Lua_Item::GetScrollName() {
	Lua_Safe_Call_String();
	return self->ScrollName;
}