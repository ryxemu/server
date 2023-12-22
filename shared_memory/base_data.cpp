#include "base_data.h"
#include "../common/global_define.h"
#include "../common/shareddb.h"
#include "../common/ipc_mutex.h"
#include "../common/memory_mapped_file.h"
#include "../common/eqemu_exception.h"

void LoadBaseData(SharedDatabase *database, const std::string &prefix) {
	EQ::IPCMutex mutex("base_data");
	mutex.Lock();
	int records = (database->GetMaxBaseDataLevel() + 1);
	if (records == 0) {
		EQ_EXCEPT("Shared Memory", "Unable to get base data from the database.");
	}

	uint32 size = records * 16 * sizeof(BaseDataStruct);

	auto Config = Config::get();
	std::string file_name = Config::get()->DirSharedMem + prefix + std::string("base_data");
	EQ::MemoryMappedFile mmf(file_name, size);
	mmf.ZeroFile();

	void *ptr = mmf.Get();
	database->LoadBaseData(ptr, records);
	mutex.Unlock();
}
