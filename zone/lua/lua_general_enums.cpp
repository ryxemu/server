#ifdef LUA_EQEMU
#include <sol/sol.hpp>

#include "common.h"
#include "event_codes.h"
#include "../common/faction.h"
#include "../common/emu_constants.h"
#include "../common/textures.h"
#include "../common/classes.h"

void lua_register_events(sol::state_view &sv) {
	sv.new_enum("Event",
	            "say", static_cast<int>(EVENT_SAY),
	            "trade", static_cast<int>(EVENT_TRADE),
	            "death", static_cast<int>(EVENT_DEATH),
	            "spawn", static_cast<int>(EVENT_SPAWN),
	            "combat", static_cast<int>(EVENT_COMBAT),
	            "slay", static_cast<int>(EVENT_SLAY),
	            "waypoint_arrive", static_cast<int>(EVENT_WAYPOINT_ARRIVE),
	            "waypoint_depart", static_cast<int>(EVENT_WAYPOINT_DEPART),
	            "timer", static_cast<int>(EVENT_TIMER),
	            "signal", static_cast<int>(EVENT_SIGNAL),
	            "hp", static_cast<int>(EVENT_HP),
	            "enter", static_cast<int>(EVENT_ENTER),
	            "exit", static_cast<int>(EVENT_EXIT),
	            "enter_zone", static_cast<int>(EVENT_ENTER_ZONE),
	            "click_door", static_cast<int>(EVENT_CLICK_DOOR),
	            "loot", static_cast<int>(EVENT_LOOT),
	            "zone", static_cast<int>(EVENT_ZONE),
	            "level_up", static_cast<int>(EVENT_LEVEL_UP),
	            "killed_merit", static_cast<int>(EVENT_KILLED_MERIT),
	            "cast_on", static_cast<int>(EVENT_CAST_ON),
	            "task_accepted", static_cast<int>(EVENT_TASK_ACCEPTED),
	            "task_stage_complete", static_cast<int>(EVENT_TASK_STAGE_COMPLETE),
	            "environmental_damage", static_cast<int>(EVENT_ENVIRONMENTAL_DAMAGE),
	            "task_update", static_cast<int>(EVENT_TASK_UPDATE),
	            "task_complete", static_cast<int>(EVENT_TASK_COMPLETE),
	            "task_fail", static_cast<int>(EVENT_TASK_FAIL),
	            "aggro_say", static_cast<int>(EVENT_AGGRO_SAY),
	            "player_pickup", static_cast<int>(EVENT_PLAYER_PICKUP),
	            "popup_response", static_cast<int>(EVENT_POPUP_RESPONSE),
	            "proximity_say", static_cast<int>(EVENT_PROXIMITY_SAY),
	            "cast", static_cast<int>(EVENT_CAST),
	            "cast_begin", static_cast<int>(EVENT_CAST_BEGIN),
	            "scale_calc", static_cast<int>(EVENT_SCALE_CALC),
	            "item_enter_zone", static_cast<int>(EVENT_ITEM_ENTER_ZONE),
	            "target_change", static_cast<int>(EVENT_TARGET_CHANGE),
	            "hate_list", static_cast<int>(EVENT_HATE_LIST),
	            "spell_effect", static_cast<int>(EVENT_SPELL_EFFECT_CLIENT),
	            "spell_buff_tic", static_cast<int>(EVENT_SPELL_EFFECT_BUFF_TIC_CLIENT),
	            "spell_fade", static_cast<int>(EVENT_SPELL_FADE),
	            "spell_effect_translocate_complete", static_cast<int>(EVENT_SPELL_EFFECT_TRANSLOCATE_COMPLETE),
	            "combine_success ", static_cast<int>(EVENT_COMBINE_SUCCESS),
	            "combine_failure ", static_cast<int>(EVENT_COMBINE_FAILURE),
	            "item_click", static_cast<int>(EVENT_ITEM_CLICK),
	            "item_click_cast", static_cast<int>(EVENT_ITEM_CLICK_CAST),
	            "group_change", static_cast<int>(EVENT_GROUP_CHANGE),
	            "forage_success", static_cast<int>(EVENT_FORAGE_SUCCESS),
	            "forage_failure", static_cast<int>(EVENT_FORAGE_FAILURE),
	            "fish_start", static_cast<int>(EVENT_FISH_START),
	            "fish_success", static_cast<int>(EVENT_FISH_SUCCESS),
	            "fish_failure", static_cast<int>(EVENT_FISH_FAILURE),
	            "click_object", static_cast<int>(EVENT_CLICK_OBJECT),
	            "discover_item", static_cast<int>(EVENT_DISCOVER_ITEM),
	            "disconnect", static_cast<int>(EVENT_DISCONNECT),
	            "connect", static_cast<int>(EVENT_CONNECT),
	            "item_tick", static_cast<int>(EVENT_ITEM_TICK),
	            "duel_win", static_cast<int>(EVENT_DUEL_WIN),
	            "duel_lose", static_cast<int>(EVENT_DUEL_LOSE),
	            "encounter_load", static_cast<int>(EVENT_ENCOUNTER_LOAD),
	            "encounter_unload", static_cast<int>(EVENT_ENCOUNTER_UNLOAD),
	            "command", static_cast<int>(EVENT_COMMAND),
	            "drop_item", static_cast<int>(EVENT_DROP_ITEM),
	            "destroy_item", static_cast<int>(EVENT_DESTROY_ITEM),
	            "feign_death", static_cast<int>(EVENT_FEIGN_DEATH),
	            "weapon_proc", static_cast<int>(EVENT_WEAPON_PROC),
	            "equip_item", static_cast<int>(EVENT_EQUIP_ITEM),
	            "unequip_item", static_cast<int>(EVENT_UNEQUIP_ITEM),
	            "augment_item", static_cast<int>(EVENT_AUGMENT_ITEM),
	            "unaugment_item", static_cast<int>(EVENT_UNAUGMENT_ITEM),
	            "augment_insert", static_cast<int>(EVENT_AUGMENT_INSERT),
	            "augment_remove", static_cast<int>(EVENT_AUGMENT_REMOVE),
	            "enter_area", static_cast<int>(EVENT_ENTER_AREA),
	            "leave_area", static_cast<int>(EVENT_LEAVE_AREA),
	            "death_complete", static_cast<int>(EVENT_DEATH_COMPLETE),
	            "unhandled_opcode", static_cast<int>(EVENT_UNHANDLED_OPCODE),
	            "tick", static_cast<int>(EVENT_TICK),
	            "spawn_zone", static_cast<int>(EVENT_SPAWN_ZONE),
	            "death_zone", static_cast<int>(EVENT_DEATH_ZONE),
	            "use_skill", static_cast<int>(EVENT_USE_SKILL),
	            "warp", static_cast<int>(EVENT_WARP),
	            "test_buff", static_cast<int>(EVENT_TEST_BUFF),
	            "consider", static_cast<int>(EVENT_CONSIDER),
	            "consider_corpse", static_cast<int>(EVENT_CONSIDER_CORPSE),
	            "loot_zone", static_cast<int>(EVENT_LOOT_ZONE),
	            "equip_item_client", static_cast<int>(EVENT_EQUIP_ITEM_CLIENT),
	            "unequip_item_client", static_cast<int>(EVENT_UNEQUIP_ITEM_CLIENT),
	            "skill_up", static_cast<int>(EVENT_SKILL_UP),
	            "language_skill_up", static_cast<int>(EVENT_LANGUAGE_SKILL_UP),
	            "alt_currency_merchant_buy", static_cast<int>(EVENT_ALT_CURRENCY_MERCHANT_BUY),
	            "alt_currency_merchant_sell", static_cast<int>(EVENT_ALT_CURRENCY_MERCHANT_SELL),
	            "merchant_buy", static_cast<int>(EVENT_MERCHANT_BUY),
	            "merchant_sell", static_cast<int>(EVENT_MERCHANT_SELL));
}

void lua_register_faction(sol::state_view &sv) {
	sv.new_enum("Faction",
	            "Ally", static_cast<int>(FACTION_ALLY),
	            "Warmly", static_cast<int>(FACTION_WARMLY),
	            "Kindly", static_cast<int>(FACTION_KINDLY),
	            "Amiable", static_cast<int>(FACTION_AMIABLY),
	            "Indifferent", static_cast<int>(FACTION_INDIFFERENTLY),
	            "Apprehensive", static_cast<int>(FACTION_APPREHENSIVELY),
	            "Dubious", static_cast<int>(FACTION_DUBIOUSLY),
	            "Threatenly", static_cast<int>(FACTION_THREATENINGLY),
	            "Scowls", static_cast<int>(FACTION_SCOWLS));
}

void lua_register_slot(sol::state_view &sv) {
	sv.new_enum("Slot",
	            "Charm", static_cast<int>(EQ::invslot::slotCharm),
	            "Ear1", static_cast<int>(EQ::invslot::slotEar1),
	            "Head", static_cast<int>(EQ::invslot::slotHead),
	            "Face", static_cast<int>(EQ::invslot::slotFace),
	            "Ear2", static_cast<int>(EQ::invslot::slotEar2),
	            "Neck", static_cast<int>(EQ::invslot::slotNeck),
	            "Shoulders", static_cast<int>(EQ::invslot::slotShoulders),
	            "Arms", static_cast<int>(EQ::invslot::slotArms),
	            "Back", static_cast<int>(EQ::invslot::slotBack),
	            "Wrist1", static_cast<int>(EQ::invslot::slotWrist1),
	            "Wrist2", static_cast<int>(EQ::invslot::slotWrist2),
	            "Range", static_cast<int>(EQ::invslot::slotRange),
	            "Hands", static_cast<int>(EQ::invslot::slotHands),
	            "Primary", static_cast<int>(EQ::invslot::slotPrimary),
	            "Secondary", static_cast<int>(EQ::invslot::slotSecondary),
	            "Finger1", static_cast<int>(EQ::invslot::slotFinger1),
	            "Finger2", static_cast<int>(EQ::invslot::slotFinger2),
	            "Chest", static_cast<int>(EQ::invslot::slotChest),
	            "Legs", static_cast<int>(EQ::invslot::slotLegs),
	            "Feet", static_cast<int>(EQ::invslot::slotFeet),
	            "Waist", static_cast<int>(EQ::invslot::slotWaist),
	            "PowerSource", static_cast<int>(EQ::invslot::slotPowerSource),
	            "Ammo", static_cast<int>(EQ::invslot::slotAmmo),
	            "General1", static_cast<int>(EQ::invslot::slotGeneral1),
	            "General2", static_cast<int>(EQ::invslot::slotGeneral2),
	            "General3", static_cast<int>(EQ::invslot::slotGeneral3),
	            "General4", static_cast<int>(EQ::invslot::slotGeneral4),
	            "General5", static_cast<int>(EQ::invslot::slotGeneral5),
	            "General6", static_cast<int>(EQ::invslot::slotGeneral6),
	            "General7", static_cast<int>(EQ::invslot::slotGeneral7),
	            "General8", static_cast<int>(EQ::invslot::slotGeneral8),
	            "General9", static_cast<int>(EQ::invslot::slotGeneral9),
	            "General10", static_cast<int>(EQ::invslot::slotGeneral10),
	            "Cursor", static_cast<int>(EQ::invslot::slotCursor),
	            "PossessionsBegin", static_cast<int>(EQ::invslot::POSSESSIONS_BEGIN),
	            "PossessionsEnd", static_cast<int>(EQ::invslot::POSSESSIONS_END),
	            "EquipmentBegin", static_cast<int>(EQ::invslot::EQUIPMENT_BEGIN),
	            "EquipmentEnd", static_cast<int>(EQ::invslot::EQUIPMENT_END),
	            "GeneralBegin", static_cast<int>(EQ::invslot::GENERAL_BEGIN),
	            "GeneralEnd", static_cast<int>(EQ::invslot::GENERAL_END),
	            "PossessionsBagsBegin", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN),
	            "PossessionsBagsEnd", static_cast<int>(EQ::invbag::CURSOR_BAG_END),
	            "GeneralBagsBegin", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN),
	            "GeneralBagsEnd", static_cast<int>(EQ::invbag::GENERAL_BAGS_END),
	            "General1BagBegin", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN),
	            "General1BagEnd", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 9,
	            "General2BagBegin", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 10,
	            "General2BagEnd", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 19,
	            "General3BagBegin", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 20,
	            "General3BagEnd", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 29,
	            "General4BagBegin", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 30,
	            "General4BagEnd", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 39,
	            "General5BagBegin", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 40,
	            "General5BagEnd", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 49,
	            "General6BagBegin", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 50,
	            "General6BagEnd", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 59,
	            "General7BagBegin", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 60,
	            "General7BagEnd", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 69,
	            "General8BagBegin", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 70,
	            "General8BagEnd", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 79,
	            "General9BagBegin", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 80,
	            "General9BagEnd", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 89,
	            "General10BagBegin", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 90,
	            "General10BagEnd", static_cast<int>(EQ::invbag::GENERAL_BAGS_BEGIN) + 99,
	            "CursorBagBegin", static_cast<int>(EQ::invbag::CURSOR_BAG_BEGIN),
	            "CursorBagEnd", static_cast<int>(EQ::invbag::CURSOR_BAG_END),
	            "Tradeskill", static_cast<int>(EQ::invslot::SLOT_TRADESKILL_EXPERIMENT_COMBINE),
	            "Augment", static_cast<int>(EQ::invslot::SLOT_AUGMENT_GENERIC_RETURN),
	            "BankBegin", static_cast<int>(EQ::invslot::BANK_BEGIN),
	            "BankEnd", static_cast<int>(EQ::invslot::BANK_END),
	            "BankBagsBegin", static_cast<int>(EQ::invbag::BANK_BAGS_BEGIN),
	            "BankBagsEnd", static_cast<int>(EQ::invbag::BANK_BAGS_END),
	            "SharedBankBegin", static_cast<int>(EQ::invslot::SHARED_BANK_BEGIN),
	            "SharedBankEnd", static_cast<int>(EQ::invslot::SHARED_BANK_END),
	            "SharedBankBagsBegin", static_cast<int>(EQ::invbag::SHARED_BANK_BAGS_BEGIN),
	            "SharedBankBagsEnd", static_cast<int>(EQ::invbag::SHARED_BANK_BAGS_END),
	            "BagSlotBegin", static_cast<int>(EQ::invbag::SLOT_BEGIN),
	            "BagSlotEnd", static_cast<int>(EQ::invbag::SLOT_END),
	            "AugSocketBegin", static_cast<int>(EQ::invaug::SOCKET_BEGIN),
	            "AugSocketEnd", static_cast<int>(EQ::invaug::SOCKET_END),
	            "Invalid", static_cast<int>(EQ::invslot::SLOT_INVALID),

	            "Shoulder", static_cast<int>(EQ::invslot::slotShoulders),       // deprecated
	            "Bracer1", static_cast<int>(EQ::invslot::slotWrist1),           // deprecated
	            "Bracer2", static_cast<int>(EQ::invslot::slotWrist2),           // deprecated
	            "Ring1", static_cast<int>(EQ::invslot::slotFinger1),            // deprecated
	            "Ring2", static_cast<int>(EQ::invslot::slotFinger2),            // deprecated
	            "PersonalBegin", static_cast<int>(EQ::invslot::GENERAL_BEGIN),  // deprecated
	            "PersonalEnd", static_cast<int>(EQ::invslot::GENERAL_END),      // deprecated
	            "CursorEnd", 0xFFFE                                             // deprecated (not in use..and never valid vis-a-vis client behavior
	);
}

void lua_register_material(sol::state_view &sv) {
	sv.new_enum("Material",
	            "Head", static_cast<int>(EQ::textures::armorHead),
	            "Chest", static_cast<int>(EQ::textures::armorChest),
	            "Arms", static_cast<int>(EQ::textures::armorArms),
	            "Wrist", static_cast<int>(EQ::textures::armorWrist),
	            "Hands", static_cast<int>(EQ::textures::armorHands),
	            "Legs", static_cast<int>(EQ::textures::armorLegs),
	            "Feet", static_cast<int>(EQ::textures::armorFeet),
	            "Primary", static_cast<int>(EQ::textures::weaponPrimary),
	            "Secondary", static_cast<int>(EQ::textures::weaponSecondary),
	            "Count", static_cast<int>(EQ::textures::materialCount),
	            "Invalid", static_cast<int>(EQ::textures::materialInvalid),

	            "Bracer", static_cast<int>(EQ::textures::armorWrist),  // deprecated
	            "Max", static_cast<int>(EQ::textures::materialCount)   // deprecated
	);
}

void lua_register_client_version(sol::state_view &sv) {
	sv.new_enum("ClientVersion",
	            "Unknown", static_cast<int>(EQ::versions::ClientVersion::Unknown),
	            "Titanium", static_cast<int>(EQ::versions::ClientVersion::Titanium),
	            "SoF", static_cast<int>(EQ::versions::ClientVersion::SoF),
	            "SoD", static_cast<int>(EQ::versions::ClientVersion::SoD),
	            "Underfoot", static_cast<int>(EQ::versions::ClientVersion::UF),  // deprecated
	            "UF", static_cast<int>(EQ::versions::ClientVersion::UF),
	            "RoF", static_cast<int>(EQ::versions::ClientVersion::RoF),
	            "RoF2", static_cast<int>(EQ::versions::ClientVersion::RoF2));
}

void lua_register_appearance(sol::state_view &sv) {
	sv.new_enum("Appearance",
	            "Standing", static_cast<int>(eaStanding),
	            "Sitting", static_cast<int>(eaSitting),
	            "Crouching", static_cast<int>(eaCrouching),
	            "Dead", static_cast<int>(eaDead),
	            "Looting", static_cast<int>(eaLooting));
}

void lua_register_classes(sol::state_view &sv) {
	sv.new_enum("Class",
	            "WARRIOR", WARRIOR,
	            "CLERIC", CLERIC,
	            "PALADIN", PALADIN,
	            "RANGER", RANGER,
	            "SHADOWKNIGHT", SHADOWKNIGHT,
	            "DRUID", DRUID,
	            "MONK", MONK,
	            "BARD", BARD,
	            "ROGUE", ROGUE,
	            "SHAMAN", SHAMAN,
	            "NECROMANCER", NECROMANCER,
	            "WIZARD", WIZARD,
	            "MAGICIAN", MAGICIAN,
	            "ENCHANTER", ENCHANTER,
	            "BEASTLORD", BEASTLORD,
	            "BERSERKER", BERSERKER,
	            "WARRIORGM", WARRIORGM,
	            "CLERICGM", CLERICGM,
	            "PALADINGM", PALADINGM,
	            "RANGERGM", RANGERGM,
	            "SHADOWKNIGHTGM", SHADOWKNIGHTGM,
	            "DRUIDGM", DRUIDGM,
	            "MONKGM", MONKGM,
	            "BARDGM", BARDGM,
	            "ROGUEGM", ROGUEGM,
	            "SHAMANGM", SHAMANGM,
	            "NECROMANCERGM", NECROMANCERGM,
	            "WIZARDGM", WIZARDGM,
	            "MAGICIANGM", MAGICIANGM,
	            "ENCHANTERGM", ENCHANTERGM,
	            "BEASTLORDGM", BEASTLORDGM,
	            "BERSERKERGM", BERSERKERGM,
	            "BANKER", BANKER,
	            "MERCHANT", MERCHANT,
	            "DISCORD_MERCHANT", DISCORD_MERCHANT,
	            "ADVENTURE_RECRUITER", ADVENTURE_RECRUITER,
	            "ADVENTURE_MERCHANT", ADVENTURE_MERCHANT,
	            "LDON_TREASURE", LDON_TREASURE,
	            "TRIBUTE_MASTER", TRIBUTE_MASTER,
	            "GUILD_TRIBUTE_MASTER", GUILD_TRIBUTE_MASTER,
	            "NORRATHS_KEEPERS_MERCHANT", NORRATHS_KEEPERS_MERCHANT,
	            "DARK_REIGN_MERCHANT", DARK_REIGN_MERCHANT,
	            "FELLOWSHIP_MASTER", FELLOWSHIP_MASTER,
	            "ALT_CURRENCY_MERCHANT", ALT_CURRENCY_MERCHANT,
	            "MERCENARY_MASTER", MERCENARY_MASTER);
}

void lua_register_skills(sol::state_view &sv) {
	sv.new_enum("Skill",
	            "1HBlunt", EQ::skills::Skill1HBlunt,
	            "Blunt1H", EQ::skills::Skill1HBlunt,
	            "1HSlashing", EQ::skills::Skill1HSlashing,
	            "Slashing1H", EQ::skills::Skill1HSlashing,
	            "2HBlunt", EQ::skills::Skill2HBlunt,
	            "Blunt2H", EQ::skills::Skill2HBlunt,
	            "2HSlashing", EQ::skills::Skill2HSlashing,
	            "Slashing2H", EQ::skills::Skill2HSlashing,
	            "Abjuration", EQ::skills::SkillAbjuration,
	            "Alteration", EQ::skills::SkillAlteration,
	            "ApplyPoison", EQ::skills::SkillApplyPoison,
	            "Archery", EQ::skills::SkillArchery,
	            "Backstab", EQ::skills::SkillBackstab,
	            "BindWound", EQ::skills::SkillBindWound,
	            "Bash", EQ::skills::SkillBash,
	            "Block", EQ::skills::SkillBlock,
	            "BrassInstruments", EQ::skills::SkillBrassInstruments,
	            "Channeling", EQ::skills::SkillChanneling,
	            "Conjuration", EQ::skills::SkillConjuration,
	            "Defense", EQ::skills::SkillDefense,
	            "Disarm", EQ::skills::SkillDisarm,
	            "DisarmTraps", EQ::skills::SkillDisarmTraps,
	            "Divination", EQ::skills::SkillDivination,
	            "Dodge", EQ::skills::SkillDodge,
	            "DoubleAttack", EQ::skills::SkillDoubleAttack,
	            "DragonPunch", EQ::skills::SkillDragonPunch,
	            "TailRake", EQ::skills::SkillTailRake,
	            "DualWield", EQ::skills::SkillDualWield,
	            "EagleStrike", EQ::skills::SkillEagleStrike,
	            "Evocation", EQ::skills::SkillEvocation,
	            "FeignDeath", EQ::skills::SkillFeignDeath,
	            "FlyingKick", EQ::skills::SkillFlyingKick,
	            "Forage", EQ::skills::SkillForage,
	            "HandtoHand", EQ::skills::SkillHandtoHand,
	            "Hide", EQ::skills::SkillHide,
	            "Kick", EQ::skills::SkillKick,
	            "Meditate", EQ::skills::SkillMeditate,
	            "Mend", EQ::skills::SkillMend,
	            "Offense", EQ::skills::SkillOffense,
	            "Parry", EQ::skills::SkillParry,
	            "PickLock", EQ::skills::SkillPickLock,
	            "1HPiercing", EQ::skills::Skill1HPiercing,
	            "Piercing1H", EQ::skills::Skill1HPiercing,
	            "Riposte", EQ::skills::SkillRiposte,
	            "RoundKick", EQ::skills::SkillRoundKick,
	            "SafeFall", EQ::skills::SkillSafeFall,
	            "SenseHeading", EQ::skills::SkillSenseHeading,
	            "Singing", EQ::skills::SkillSinging,
	            "Sneak", EQ::skills::SkillSneak,
	            "SpecializeAbjure", EQ::skills::SkillSpecializeAbjure,
	            "SpecializeAlteration", EQ::skills::SkillSpecializeAlteration,
	            "SpecializeConjuration", EQ::skills::SkillSpecializeConjuration,
	            "SpecializeDivination", EQ::skills::SkillSpecializeDivination,
	            "SpecializeEvocation", EQ::skills::SkillSpecializeEvocation,
	            "PickPockets", EQ::skills::SkillPickPockets,
	            "StringedInstruments", EQ::skills::SkillStringedInstruments,
	            "Swimming", EQ::skills::SkillSwimming,
	            "Throwing", EQ::skills::SkillThrowing,
	            "TigerClaw", EQ::skills::SkillTigerClaw,
	            "Tracking", EQ::skills::SkillTracking,
	            "WindInstruments", EQ::skills::SkillWindInstruments,
	            "Fishing", EQ::skills::SkillFishing,
	            "MakePoison", EQ::skills::SkillMakePoison,
	            "Tinkering", EQ::skills::SkillTinkering,
	            "Research", EQ::skills::SkillResearch,
	            "Alchemy", EQ::skills::SkillAlchemy,
	            "Baking", EQ::skills::SkillBaking,
	            "Tailoring", EQ::skills::SkillTailoring,
	            "SenseTraps", EQ::skills::SkillSenseTraps,
	            "Blacksmithing", EQ::skills::SkillBlacksmithing,
	            "Fletching", EQ::skills::SkillFletching,
	            "Brewing", EQ::skills::SkillBrewing,
	            "AlcoholTolerance", EQ::skills::SkillAlcoholTolerance,
	            "Begging", EQ::skills::SkillBegging,
	            "JewelryMaking", EQ::skills::SkillJewelryMaking,
	            "Pottery", EQ::skills::SkillPottery,
	            "PercussionInstruments", EQ::skills::SkillPercussionInstruments,
	            "Intimidation", EQ::skills::SkillIntimidation,
	            "Berserking", EQ::skills::SkillBerserking,
	            "Taunt", EQ::skills::SkillTaunt,
	            "Frenzy", EQ::skills::SkillFrenzy,
	            "RemoveTraps", EQ::skills::SkillRemoveTraps,
	            "TripleAttack", EQ::skills::SkillTripleAttack,
	            "2HPiercing", EQ::skills::Skill2HPiercing,
	            "Piercing2H", EQ::skills::Skill2HPiercing,
	            "HIGHEST_SKILL", EQ::skills::HIGHEST_SKILL);
}

void lua_register_bodytypes(sol::state_view &sv) {
	sv.new_enum("BT",
	            "Humanoid", 1,
	            "Lycanthrope", 2,
	            "Undead", 3,
	            "Giant", 4,
	            "Construct", 5,
	            "Extraplanar", 6,
	            "Magical", 7,
	            "SummonedUndead", 8,
	            "RaidGiant", 9,
	            "NoTarget", 11,
	            "Vampire", 12,
	            "Atenha_Ra", 13,
	            "Greater_Akheva", 14,
	            "Khati_Sha", 15,
	            "Seru", 16,
	            "Draz_Nurakk", 18,
	            "Zek", 19,
	            "Luggald", 20,
	            "Animal", 21,
	            "Insect", 22,
	            "Monster", 23,
	            "Summoned", 24,
	            "Plant", 25,
	            "Dragon", 26,
	            "Summoned2", 27,
	            "Summoned3", 28,
	            "VeliousDragon", 30,
	            "Dragon3", 32,
	            "Boxes", 33,
	            "Muramite", 34,
	            "NoTarget2", 60,
	            "SwarmPet", 63,
	            "InvisMan", 66,
	            "Special", 67);
}

void lua_register_filters(sol::state_view &sv) {
	sv.new_enum("Filter",
	            "None", FilterNone,
	            "GuildChat", FilterGuildChat,
	            "Socials", FilterSocials,
	            "GroupChat", FilterGroupChat,
	            "Shouts", FilterShouts,
	            "Auctions", FilterAuctions,
	            "OOC", FilterOOC,
	            "BadWords", FilterBadWords,
	            "PCSpells", FilterPCSpells,
	            "NPCSpells", FilterNPCSpells,
	            "BardSongs", FilterBardSongs,
	            "SpellCrits", FilterSpellCrits,
	            "MeleeCrits", FilterMeleeCrits,
	            "SpellDamage", FilterSpellDamage,
	            "MyMisses", FilterMyMisses,
	            "OthersMiss", FilterOthersMiss,
	            "OthersHit", FilterOthersHit,
	            "MissedMe", FilterMissedMe,
	            "DamageShields", FilterDamageShields,
	            "DOT", FilterDOT,
	            "PetHits", FilterPetHits,
	            "PetMisses", FilterPetMisses,
	            "FocusEffects", FilterFocusEffects,
	            "PetSpells", FilterPetSpells,
	            "HealOverTime", FilterHealOverTime,
	            "Unknown25", FilterUnknown25,
	            "Unknown26", FilterUnknown26,
	            "Unknown27", FilterUnknown27,
	            "Unknown28", FilterUnknown28);
}

void lua_register_message_types(sol::state_view &sv) {
	sv.new_enum("MT",
	            "White", Chat::White,
	            "DimGray", Chat::DimGray,
	            "Default", Chat::Default,
	            "Green", Chat::Green,
	            "BrightBlue", Chat::BrightBlue,
	            "LightBlue", Chat::LightBlue,
	            "Magenta", Chat::Magenta,
	            "Gray", Chat::Gray,
	            "LightGray", Chat::LightGray,
	            "NPCQuestSay", Chat::NPCQuestSay,
	            "DarkGray", Chat::DarkGray,
	            "Red", Chat::Red,
	            "Lime", Chat::Lime,
	            "Yellow", Chat::Yellow,
	            "Blue", Chat::Blue,
	            "LightNavy", Chat::LightNavy,
	            "Cyan", Chat::Cyan,
	            "Black", Chat::Black,
	            "Say", Chat::Say,
	            "Tell", Chat::Tell,
	            "Group", Chat::Group,
	            "Guild", Chat::Guild,
	            "OOC", Chat::OOC,
	            "Auction", Chat::Auction,
	            "Shout", Chat::Shout,
	            "Emote", Chat::Emote,
	            "Spells", Chat::Spells,
	            "YouHitOther", Chat::YouHitOther,
	            "OtherHitsYou", Chat::OtherHitYou,
	            "YouMissOther", Chat::YouMissOther,
	            "OtherMissesYou", Chat::OtherMissYou,
	            "Broadcasts", Chat::Broadcasts,
	            "Skills", Chat::Skills,
	            "Disciplines", Chat::Disciplines,
	            "Unused1", Chat::Unused1,
	            "DefaultText", Chat::DefaultText,
	            "Unused2", Chat::Unused2,
	            "MerchantOffer", Chat::MerchantOffer,
	            "MerchantBuySell", Chat::MerchantExchange,
	            "YourDeath", Chat::YourDeath,
	            "OtherDeath", Chat::OtherDeath,
	            "OtherHits", Chat::OtherHitOther,
	            "OtherMisses", Chat::OtherMissOther,
	            "Who", Chat::Who,
	            "YellForHelp", Chat::YellForHelp,
	            "NonMelee", Chat::NonMelee,
	            "WornOff", Chat::SpellWornOff,
	            "MoneySplit", Chat::MoneySplit,
	            "LootMessages", Chat::Loot,
	            "DiceRoll", Chat::DiceRoll,
	            "OtherSpells", Chat::OtherSpells,
	            "SpellFailure", Chat::SpellFailure,
	            "Chat", Chat::ChatChannel,
	            "Channel1", Chat::Chat1,
	            "Channel2", Chat::Chat2,
	            "Channel3", Chat::Chat3,
	            "Channel4", Chat::Chat4,
	            "Channel5", Chat::Chat5,
	            "Channel6", Chat::Chat6,
	            "Channel7", Chat::Chat7,
	            "Channel8", Chat::Chat8,
	            "Channel9", Chat::Chat9,
	            "Channel10", Chat::Chat10,
	            "CritMelee", Chat::MeleeCrit,
	            "SpellCrits", Chat::SpellCrit,
	            "TooFarAway", Chat::TooFarAway,
	            "NPCRampage", Chat::NPCRampage,
	            "NPCFlurry", Chat::NPCFlurry,
	            "NPCEnrage", Chat::NPCEnrage,
	            "SayEcho", Chat::EchoSay,
	            "TellEcho", Chat::EchoTell,
	            "GroupEcho", Chat::EchoGroup,
	            "GuildEcho", Chat::EchoGuild,
	            "OOCEcho", Chat::EchoOOC,
	            "AuctionEcho", Chat::EchoAuction,
	            "ShoutECho", Chat::EchoShout,
	            "EmoteEcho", Chat::EchoEmote,
	            "Chat1Echo", Chat::EchoChat1,
	            "Chat2Echo", Chat::EchoChat2,
	            "Chat3Echo", Chat::EchoChat3,
	            "Chat4Echo", Chat::EchoChat4,
	            "Chat5Echo", Chat::EchoChat5,
	            "Chat6Echo", Chat::EchoChat6,
	            "Chat7Echo", Chat::EchoChat7,
	            "Chat8Echo", Chat::EchoChat8,
	            "Chat9Echo", Chat::EchoChat9,
	            "Chat10Echo", Chat::EchoChat10,
	            "DoTDamage", Chat::DotDamage,
	            "ItemLink", Chat::ItemLink,
	            "RaidSay", Chat::RaidSay,
	            "MyPet", Chat::MyPet,
	            "DS", Chat::DamageShield,
	            "Leadership", Chat::LeaderShip,
	            "PetFlurry", Chat::PetFlurry,
	            "PetCrit", Chat::PetCritical,
	            "FocusEffect", Chat::FocusEffect,
	            "Experience", Chat::Experience,
	            "System", Chat::System,
	            "PetSpell", Chat::PetSpell,
	            "PetResponse", Chat::PetResponse,
	            "ItemSpeech", Chat::ItemSpeech,
	            "StrikeThrough", Chat::StrikeThrough,
	            "Stun", Chat::Stun);
}

void lua_register_journal_speakmode(sol::state_view &sv) {
	sv.new_enum("SpeakMode",
	            "Raw", static_cast<int>(Journal::SpeakMode::Raw),
	            "Say", static_cast<int>(Journal::SpeakMode::Say),
	            "Shout", static_cast<int>(Journal::SpeakMode::Shout),
	            "EmoteAlt", static_cast<int>(Journal::SpeakMode::EmoteAlt),
	            "Emote", static_cast<int>(Journal::SpeakMode::Emote),
	            "Group", static_cast<int>(Journal::SpeakMode::Group));
}

void lua_register_journal_mode(sol::state_view &sv) {
	sv.new_enum("JournalMode",
	            "None", static_cast<int>(Journal::Mode::None),
	            "Log1", static_cast<int>(Journal::Mode::Log1),
	            "Log2", static_cast<int>(Journal::Mode::Log2));
}

#endif