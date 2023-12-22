#include "loot.h"
#include "../common/global_define.h"
#include "../common/shareddb.h"
#include "../common/ipc_mutex.h"
#include "../common/memory_mapped_file.h"
#include "../common/eqemu_exception.h"
#include "../common/fixed_memory_variable_hash_set.h"
#include "../common/loottable.h"

void LoadLoot(SharedDatabase *database, const std::string &prefix) {
	EQ::IPCMutex mutex("loot");
	mutex.Lock();

	uint32 loot_table_count, loot_table_max, loot_table_entries_count;
	uint32 loot_drop_count, loot_drop_max, loot_drop_entries_count;
	database->GetLootTableInfo(loot_table_count, loot_table_max, loot_table_entries_count);
	database->GetLootDropInfo(loot_drop_count, loot_drop_max, loot_drop_entries_count);

	uint32 loot_table_size = (3 * sizeof(uint32)) +                                         // header
	                         ((loot_table_max + 1) * sizeof(uint32)) +                      // offset list
	                         (loot_table_count * sizeof(LootTable_Struct)) +                // loot table headers
	                         (loot_table_entries_count * sizeof(LootTableEntries_Struct));  // number of loot table entries

	uint32 loot_drop_size = (3 * sizeof(uint32)) +                                       // header
	                        ((loot_drop_max + 1) * sizeof(uint32)) +                     // offset list
	                        (loot_drop_count * sizeof(LootDrop_Struct)) +                // loot table headers
	                        (loot_drop_entries_count * sizeof(LootDropEntries_Struct));  // number of loot table entries

	auto Config = Config::get();
	std::string file_name_lt = Config::get()->DirSharedMem + prefix + std::string("loot_table");
	std::string file_name_ld = Config::get()->DirSharedMem + prefix + std::string("loot_drop");

	EQ::MemoryMappedFile mmf_loot_table(file_name_lt, loot_table_size);
	EQ::MemoryMappedFile mmf_loot_drop(file_name_ld, loot_drop_size);
	mmf_loot_table.ZeroFile();
	mmf_loot_drop.ZeroFile();

	EQ::FixedMemoryVariableHashSet<LootTable_Struct> loot_table_hash(reinterpret_cast<byte *>(mmf_loot_table.Get()),
	                                                                 loot_table_size, loot_table_max);

	EQ::FixedMemoryVariableHashSet<LootDrop_Struct> loot_drop_hash(reinterpret_cast<byte *>(mmf_loot_drop.Get()),
	                                                               loot_drop_size, loot_drop_max);

	database->LoadLootTables(mmf_loot_table.Get(), loot_table_max);
	database->LoadLootDrops(mmf_loot_drop.Get(), loot_drop_max);
	mutex.Unlock();
}
