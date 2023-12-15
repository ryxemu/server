#ifndef COMMON_EMU_CONSTANTS_H
#define COMMON_EMU_CONSTANTS_H

#include "eq_limits.h"
#include "emu_versions.h"
#include "bodytypes.h"

#include <string.h>

namespace EQ {
using Ls20231211::IINVALID;
using Ls20231211::INULL;

namespace inventory {

}  // namespace inventory

namespace invtype {
using namespace Ls20231211::invtype::enum_;

using Ls20231211::invtype::BANK_SIZE;
using Ls20231211::invtype::BAZAAR_SIZE;
using Ls20231211::invtype::CORPSE_SIZE;
using Ls20231211::invtype::INSPECT_SIZE;
using Ls20231211::invtype::LIMBO_SIZE;
using Ls20231211::invtype::MERCHANT_SIZE;
using Ls20231211::invtype::POSSESSIONS_SIZE;
using Ls20231211::invtype::TRADE_SIZE;
using Ls20231211::invtype::WORLD_SIZE;

using Ls20231211::invtype::TRADE_NPC_SIZE;

using Ls20231211::invtype::TYPE_BEGIN;
using Ls20231211::invtype::TYPE_COUNT;
using Ls20231211::invtype::TYPE_END;
using Ls20231211::invtype::TYPE_INVALID;

int16 GetInvTypeSize(int16 inv_type);
using Ls20231211::invtype::GetInvTypeName;

}  // namespace invtype

namespace invslot {
using namespace Ls20231211::invslot::enum_;

using Ls20231211::invslot::SLOT_BEGIN;
using Ls20231211::invslot::SLOT_INVALID;

using Ls20231211::invslot::POSSESSIONS_BEGIN;
using Ls20231211::invslot::POSSESSIONS_COUNT;
using Ls20231211::invslot::POSSESSIONS_END;

using Ls20231211::invslot::EQUIPMENT_BEGIN;
using Ls20231211::invslot::EQUIPMENT_COUNT;
using Ls20231211::invslot::EQUIPMENT_END;

using Ls20231211::invslot::GENERAL_BEGIN;
using Ls20231211::invslot::GENERAL_COUNT;
using Ls20231211::invslot::GENERAL_END;

using Ls20231211::invslot::BONUS_BEGIN;
using Ls20231211::invslot::BONUS_SKILL_END;
using Ls20231211::invslot::BONUS_STAT_END;

using Ls20231211::invslot::BANK_BEGIN;
using Ls20231211::invslot::BANK_END;

using Ls20231211::invslot::TRADE_BEGIN;
using Ls20231211::invslot::TRADE_END;

using Ls20231211::invslot::TRADE_NPC_END;

using Ls20231211::invslot::WORLD_BEGIN;
using Ls20231211::invslot::WORLD_END;

const int16 CORPSE_BEGIN = invslot::slotGeneral1;
const int16 CORPSE_END = CORPSE_BEGIN + invslot::slotGeneral8;

const int16 CURSOR_QUEUE_BEGIN = 8000;
const int16 CURSOR_QUEUE_END = 8999;

using Ls20231211::invslot::CORPSE_BITMASK;
using Ls20231211::invslot::POSSESSIONS_BITMASK;

using Ls20231211::invslot::GetInvPossessionsSlotName;
using Ls20231211::invslot::GetInvSlotName;

}  // namespace invslot

namespace invbag {
using Ls20231211::invbag::SLOT_BEGIN;
using Ls20231211::invbag::SLOT_COUNT;
using Ls20231211::invbag::SLOT_END;
using Ls20231211::invbag::SLOT_INVALID;

using Ls20231211::invbag::GENERAL_BAGS_BEGIN;
const int16 GENERAL_BAGS_COUNT = invslot::GENERAL_COUNT * SLOT_COUNT;
const int16 GENERAL_BAGS_END = (GENERAL_BAGS_BEGIN + GENERAL_BAGS_COUNT) - 1;

const int16 GENERAL_BAGS_8_COUNT = 8 * SLOT_COUNT;
const int16 GENERAL_BAGS_8_END = (GENERAL_BAGS_BEGIN + GENERAL_BAGS_8_COUNT) - 1;

const int16 CURSOR_BAG_BEGIN = 330;
const int16 CURSOR_BAG_COUNT = SLOT_COUNT;
const int16 CURSOR_BAG_END = (CURSOR_BAG_BEGIN + CURSOR_BAG_COUNT) - 1;

using Ls20231211::invbag::BANK_BAGS_BEGIN;
const int16 BANK_BAGS_COUNT = (invtype::BANK_SIZE * SLOT_COUNT);
const int16 BANK_BAGS_END = (BANK_BAGS_BEGIN + BANK_BAGS_COUNT) - 1;

const int16 BANK_BAGS_8_COUNT = 8 * SLOT_COUNT;
const int16 BANK_BAGS_8_END = (BANK_BAGS_BEGIN + BANK_BAGS_8_COUNT) - 1;

using Ls20231211::invbag::TRADE_BAGS_BEGIN;
const int16 TRADE_BAGS_COUNT = invtype::TRADE_SIZE * SLOT_COUNT;
const int16 TRADE_BAGS_END = (TRADE_BAGS_BEGIN + TRADE_BAGS_COUNT) - 1;

using Ls20231211::invbag::GetInvBagIndexName;

}  // namespace invbag

namespace constants {
// database
static const EQ::versions::ClientVersion CharacterCreationClient = EQ::versions::ClientVersion::Ls20231211;  // adjust according to starting item placement and target client
using Ls20231211::constants::CHARACTER_CREATION_LIMIT;

const size_t SAY_LINK_OPENER_SIZE = 1;
using Ls20231211::constants::SAY_LINK_BODY_SIZE;
const size_t SAY_LINK_TEXT_SIZE = 200;
const size_t SAY_LINK_CLOSER_SIZE = 1;
const size_t SAY_LINK_MAXIMUM_SIZE = (SAY_LINK_OPENER_SIZE + SAY_LINK_BODY_SIZE + SAY_LINK_TEXT_SIZE + SAY_LINK_CLOSER_SIZE);

enum GravityBehavior : int8 {
	Ground,
	Flying,
	Levitating,
	Water
};

enum SpawnAnimations : uint8 {
	Standing,
	Sitting,
	Crouching,
	Laying,
	Looting
};

extern const std::map<int, std::string>& GetLanguageMap();
std::string GetLanguageName(int language_id);

extern const std::map<int8, std::string>& GetFlyModeMap();
std::string GetFlyModeName(int8 flymode_id);

extern const std::map<bodyType, std::string>& GetBodyTypeMap();
std::string GetBodyTypeName(bodyType bodytype_id);

extern const std::map<uint8, std::string>& GetAccountStatusMap();
std::string GetAccountStatusName(uint8 account_status);

extern const std::map<uint8, std::string>& GetConsiderLevelMap();
std::string GetConsiderLevelName(uint8 consider_level);

extern const std::map<uint8, std::string>& GetStuckBehaviorMap();
std::string GetStuckBehaviorName(uint8 behavior_id);

extern const std::map<uint8, std::string>& GetSpawnAnimationMap();
std::string GetSpawnAnimationName(uint8 animation_id);

}  // namespace constants

namespace spells {
enum class CastingSlot : int32 {
	Invalid = -1,
	Gem1 = 0,
	Gem2 = 1,
	Gem3 = 2,
	Gem4 = 3,
	Gem5 = 4,
	Gem6 = 5,
	Gem7 = 6,
	Gem8 = 7,
	MaxGems = 8,
	Ability = 9,
	Item = 10,
	AltAbility = 0xFF
};

using Ls20231211::spells::SPELL_GEM_COUNT;
using Ls20231211::spells::SPELL_ID_MAX;
using Ls20231211::spells::SPELLBOOK_SIZE;

}  // namespace spells

namespace profile {

using Ls20231211::profile::SKILL_ARRAY_SIZE;

}  // namespace profile

namespace behavior {
using Ls20231211::behavior::CoinHasWeight;

}  // namespace behavior

namespace bug {
enum CategoryID : uint32 {
	catOther = 0,
	catVideo,
	catAudio,
	catPathing,
	catQuest,
	catTradeskills,
	catSpellStacking,
	catDoorsPortals,
	catItems,
	catNPC,
	catDialogs,
};

enum OptionalInfoFlag : uint32 {
	infoNoOptionalInfo = 0x0,
	infoCanDuplicate = 0x1,
	infoCrashBug = 0x2,
	infoTargetInfo = 0x4,
	infoCharacterFlags = 0x8,
	infoUnknownValue = 0xFFFFFFF0
};

const char* CategoryIDToCategoryName(CategoryID category_id);
CategoryID CategoryNameToCategoryID(const char* category_name);

}  // namespace bug

enum WaypointStatus : int {
	QuestControlNoGrid = -2,
	QuestControlGrid = -1
};
}  // namespace EQ

enum ServerLockType : int {
	List,
	Lock,
	Unlock
};

enum AccountStatus : uint8 {
	Player = 0,
	Steward = 10,
	ApprenticeGuide = 20,
	Guide = 50,
	QuestTroupe = 80,
	SeniorGuide = 81,
	GMTester = 85,
	EQSupport = 90,
	GMStaff = 95,
	GMAdmin = 100,
	GMLeadAdmin = 150,
	QuestMaster = 160,
	GMAreas = 170,
	GMCoder = 180,
	GMMgmt = 200,
	GMImpossible = 250,
	Max = 255
};

enum ConsiderLevel : uint8 {
	Ally = 1,
	Warmly,
	Kindly,
	Amiably,
	Indifferently,
	Apprehensively,
	Dubiously,
	Threateningly,
	Scowls
};

#endif /*COMMON_EMU_CONSTANTS_H*/