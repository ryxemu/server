#include "emu_constants.h"
#include "emu_limits.h"

static const EQ::inventory::LookupEntry inventory_lookup_entries[EQ::versions::MobVersionCount] =
    {
        {// ClientUnknown
         ClientUnknown::INULL,
         ClientUnknown::INULL,
         ClientUnknown::INULL,
         ClientUnknown::INULL,
         ClientUnknown::INULL,
         ClientUnknown::INULL,
         ClientUnknown::INULL,
         ClientUnknown::INULL,
         ClientUnknown::INULL,

         ClientUnknown::INULL,
         ClientUnknown::INULL,
         ClientUnknown::INULL,

         false,
         false,
         false,
         false},
        {// ClientUnused
         ClientUnused::INULL,
         ClientUnused::INULL,
         ClientUnused::INULL,
         ClientUnused::INULL,
         ClientUnused::INULL,
         ClientUnused::INULL,
         ClientUnused::INULL,
         ClientUnused::INULL,
         ClientUnused::INULL,

         ClientUnused::INULL,
         ClientUnused::INULL,
         ClientUnused::INULL,

         false,
         false,
         false,
         false},
        {// Mac
         EQ::invtype::POSSESSIONS_SIZE,
         Mac::invtype::BANK_SIZE,
         Mac::invtype::TRADE_SIZE,
         Mac::invtype::WORLD_SIZE,
         Mac::invtype::LIMBO_SIZE,
         Mac::invtype::MERCHANT_SIZE,
         Mac::invtype::CORPSE_SIZE,
         Mac::invtype::BAZAAR_SIZE,
         Mac::invtype::INSPECT_SIZE,

         Mac::invslot::POSSESSIONS_BITMASK,
         Mac::invslot::CORPSE_BITMASK,
         Mac::invbag::SLOT_COUNT,

         Mac::inventory::AllowEmptyBagInBag,
         Mac::inventory::AllowClickCastFromBag,
         Mac::inventory::ConcatenateInvTypeLimbo,
         Mac::inventory::AllowOverLevelEquipment},
        {// NPC
         EQ::invtype::POSSESSIONS_SIZE,
         EntityLimits::NPC::INULL,
         EntityLimits::NPC::invtype::TRADE_SIZE,
         EntityLimits::NPC::INULL,
         EntityLimits::NPC::INULL,
         EntityLimits::NPC::INULL,
         EntityLimits::NPC::INULL,
         EntityLimits::NPC::INULL,
         EntityLimits::NPC::INULL,

         EntityLimits::NPC::INULL,
         EntityLimits::NPC::INULL,
         0,

         false,
         false,
         false,
         false},
        {// NPCMerchant
         EQ::invtype::POSSESSIONS_SIZE,
         EntityLimits::NPCMerchant::INULL,
         EntityLimits::NPCMerchant::invtype::TRADE_SIZE,
         EntityLimits::NPCMerchant::INULL,
         EntityLimits::NPCMerchant::INULL,
         EntityLimits::NPCMerchant::INULL,
         EntityLimits::NPCMerchant::INULL,
         EntityLimits::NPCMerchant::INULL,
         EntityLimits::NPCMerchant::INULL,

         EntityLimits::NPCMerchant::INULL,
         EntityLimits::NPCMerchant::INULL,
         0,

         false,
         false,
         false,
         false},
        {// ClientPet
         EQ::invtype::POSSESSIONS_SIZE,
         EntityLimits::ClientPet::INULL,
         EntityLimits::ClientPet::invtype::TRADE_SIZE,
         EntityLimits::ClientPet::INULL,
         EntityLimits::ClientPet::INULL,
         EntityLimits::ClientPet::INULL,
         EntityLimits::ClientPet::INULL,
         EntityLimits::ClientPet::INULL,
         EntityLimits::ClientPet::INULL,

         EntityLimits::ClientPet::INULL,
         EntityLimits::ClientPet::INULL,
         0,

         false,
         false,
         false,
         false},
        {// NPCPet
         EQ::invtype::POSSESSIONS_SIZE,
         EntityLimits::NPCPet::INULL,
         EntityLimits::NPCPet::invtype::TRADE_SIZE,
         EntityLimits::NPCPet::INULL,
         EntityLimits::NPCPet::INULL,
         EntityLimits::NPCPet::INULL,
         EntityLimits::NPCPet::INULL,
         EntityLimits::NPCPet::INULL,
         EntityLimits::NPCPet::INULL,

         EntityLimits::NPCPet::INULL,
         EntityLimits::NPCPet::INULL,
         0,

         false,
         false,
         false,
         false},
        {// OfflineMac
         Mac::INULL,
         Mac::INULL,
         Mac::invtype::TRADE_SIZE,
         Mac::INULL,
         Mac::INULL,
         Mac::invtype::MERCHANT_SIZE,
         Mac::INULL,
         Mac::invtype::BAZAAR_SIZE,
         Mac::invtype::INSPECT_SIZE,

         Mac::INULL,
         Mac::INULL,
         EQ::invbag::SLOT_COUNT,

         false,
         false,
         false,
         false},
};

const EQ::inventory::LookupEntry* EQ::inventory::Lookup(versions::MobVersion Mob_version) {
	return &inventory_lookup_entries[static_cast<int>(versions::ValidateMobVersion(Mob_version))];
}

static const EQ::behavior::LookupEntry behavior_lookup_entries[EQ::versions::MobVersionCount] =
    {
        {// Unknown
         true},
        {// ClientUnused
         true},
        {// Mac
         Mac::behavior::CoinHasWeight},
        {
            // NPC
            EQ::behavior::CoinHasWeight /*CoinHasWeight*/
        },
        {
            // NPCMerchant
            EQ::behavior::CoinHasWeight /*CoinHasWeight*/
        },
        {
            // ClientPet
            EQ::behavior::CoinHasWeight /*CoinHasWeight*/
        },
        {
            // NPCPet
            EQ::behavior::CoinHasWeight /*CoinHasWeight*/
        },
        {// OfflineMac
         Mac::behavior::CoinHasWeight}};

const EQ::behavior::LookupEntry* EQ::behavior::Lookup(versions::MobVersion Mob_version) {
	return &behavior_lookup_entries[static_cast<int>(versions::ValidateMobVersion(Mob_version))];
}
