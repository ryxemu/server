#ifndef _EQEMU_LOOTTABLE_H
#define _EQEMU_LOOTTABLE_H

#include "types.h"

#pragma pack(1)
struct LootTableEntries_Struct {
	uint32 lootdrop_id;
	uint8 droplimit;
	uint8 mindrop;
	uint8 multiplier;
	float probability;
	uint8 multiplier_min;
};

struct LootTable_Struct {
	uint32 mincash;
	uint32 maxcash;
	uint32 avgcoin;
	uint32 NumEntries;
	LootTableEntries_Struct Entries[0];
};

struct LootDropEntries_Struct {
	uint32 item_id;
	int8 item_charges;
	uint8 equip_item;
	float chance;
	uint8 minlevel;
	uint8 maxlevel;
	uint8 multiplier;
};

struct LootDrop_Struct {
	uint32 NumEntries;
	LootDropEntries_Struct Entries[0];
};
#pragma pack()

#endif
