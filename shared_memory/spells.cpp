#include "spells.h"
#include "../common/global_define.h"
#include "../common/shareddb.h"
#include "../common/ipc_mutex.h"
#include "../common/memory_mapped_file.h"
#include "../common/eqemu_exception.h"
#include "../common/spdat.h"

void LoadSpells(SharedDatabase *database, const std::string &prefix) {
	EQ::IPCMutex mutex("spells");
	mutex.Lock();
	int records = database->GetMaxSpellID() + 1;
	if (records == 0) {
		EQ_EXCEPT("Shared Memory", "Unable to get any spells from the database.");
	}

	uint32 size = records * sizeof(SPDat_Spell_Struct) + sizeof(uint32);

	auto Config = Config::get();
	std::string file_name = Config::get()->DirSharedMem + prefix + std::string("spells");
	EQ::MemoryMappedFile mmf(file_name, size);
	mmf.ZeroFile();

	void *ptr = mmf.Get();
	database->LoadSpells(ptr, records);
	mutex.Unlock();
}
