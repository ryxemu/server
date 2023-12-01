#ifndef COMMON_EMU_VERSIONS_H
#define COMMON_EMU_VERSIONS_H

#include "types.h"

#include <stdlib.h>

namespace EQ {
namespace versions {
enum ClientVersion {
	Unknown = 0,
	Unused,
	MacPC,
	MacIntel,
	MacPPC,
	Mac
};

enum ClientVersionBit : uint32 {
	bit_Unknown = 0,
	bit_Unused = 0x00000001,
	bit_MacPC = 0x00000002,
	bit_MacIntel = 0x00000004,
	bit_MacPPC = 0x00000008,
	bit_Mac = 0x0000000E,
	bit_AllClients = 0xFFFFFFFF
};

const ClientVersion LastClientVersion = ClientVersion::Mac;
const size_t ClientVersionCount = (static_cast<size_t>(LastClientVersion) + 1);

bool IsValidClientVersion(ClientVersion client_version);
ClientVersion ValidateClientVersion(ClientVersion client_version);
const char* ClientVersionName(ClientVersion client_version);
uint32 ConvertClientVersionToClientVersionBit(ClientVersion client_version);
ClientVersion ConvertClientVersionBitToClientVersion(uint32 client_version_bit);

enum class MobVersion {
	Unknown = 0,
	Unused,
	Mac,
	NPC,
	NPCMerchant,
	ClientPet,
	NPCPet,
	OfflineMac
};

const MobVersion LastMobVersion = MobVersion::OfflineMac;
const MobVersion LastPCMobVersion = MobVersion::Mac;
const MobVersion LastNonPCMobVersion = MobVersion::NPCPet;
const MobVersion LastOfflinePCMobVersion = MobVersion::OfflineMac;
const size_t MobVersionCount = (static_cast<size_t>(LastMobVersion) + 1);

bool IsValidMobVersion(MobVersion Mob_version);
bool IsValidPCMobVersion(MobVersion Mob_version);
bool IsValidNonPCMobVersion(MobVersion Mob_version);
bool IsValidOfflinePCMobVersion(MobVersion Mob_version);

MobVersion ValidateMobVersion(MobVersion Mob_version);
MobVersion ValidatePCMobVersion(MobVersion Mob_version);
MobVersion ValidateNonPCMobVersion(MobVersion Mob_version);
MobVersion ValidateOfflinePCMobVersion(MobVersion Mob_version);

const char* MobVersionName(MobVersion Mob_version);
ClientVersion ConvertMobVersionToClientVersion(MobVersion Mob_version);
MobVersion ConvertClientVersionToMobVersion(ClientVersion client_version);
MobVersion ConvertPCMobVersionToOfflinePCMobVersion(MobVersion Mob_version);
MobVersion ConvertOfflinePCMobVersionToPCMobVersion(MobVersion Mob_version);
ClientVersion ConvertOfflinePCMobVersionToClientVersion(MobVersion Mob_version);
MobVersion ConvertClientVersionToOfflinePCMobVersion(ClientVersion client_version);

}  // namespace versions
}  // namespace EQ

#endif /* COMMON_EMU_VERSIONS_H */