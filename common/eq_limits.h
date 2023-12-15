#ifndef COMMON_EQ_LIMITS_H
#define COMMON_EQ_LIMITS_H

#include "types.h"
#include "eq_constants.h"
#include "emu_versions.h"
#include "../common/patches/mac_limits.h"
#include "../common/patches/ls20231211_limits.h"

namespace EQ {
namespace inventory {
class LookupEntry {
   public:
	int16 InventoryTypeSize[9];

	uint64 PossessionsBitmask;
	uint64 CorpseBitmask;
	int16 BagSlotCount;

	bool AllowEmptyBagInBag;
	bool AllowClickCastFromBag;
	bool ConcatenateInvTypeLimbo;
	bool AllowOverLevelEquipment;
};

const LookupEntry* Lookup(versions::MobVersion Mob_version);

}  // namespace inventory

namespace behavior {
class LookupEntry {
   public:
	bool CoinHasWeight;
};

const LookupEntry* Lookup(versions::MobVersion Mob_version);

}  // namespace behavior

}  // namespace EQ

namespace ClientUnknown {
const int16 IINVALID = -1;
const int16 INULL = 0;

}  // namespace ClientUnknown

namespace ClientUnused {
const int16 IINVALID = -1;
const int16 INULL = 0;

}  // namespace ClientUnused

#endif /*COMMON_EQ_LIMITS_H*/