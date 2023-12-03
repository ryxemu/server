#include "items.h"
#include "../common/global_define.h"
#include "../common/shareddb.h"
#include "../common/ipc_mutex.h"
#include "../common/memory_mapped_file.h"
#include "../common/eqemu_exception.h"
#include "../common/item_data.h"

void LoadItems(SharedDatabase *database, const std::string &prefix) {
	EQ::IPCMutex mutex("items");
	mutex.Lock();

	int32 items = -1;
	uint32 max_item = 0;
	database->GetItemsCount(items, max_item);
	if (items == -1) {
		EQ_EXCEPT("Shared Memory", "Unable to get any items from the database.");
	}

	uint32 size = static_cast<uint32>(EQ::FixedMemoryHashSet<EQ::ItemData>::estimated_size(items, max_item));

	auto Config = Config::get();
	std::string file_name = Config->SharedMemDir + prefix + std::string("items");
	EQ::MemoryMappedFile mmf(file_name, size);
	mmf.ZeroFile();

	void *ptr = mmf.Get();
	database->LoadItems(ptr, size, items, max_item);
	mutex.Unlock();
}
