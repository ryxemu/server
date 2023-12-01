#include "skill_caps.h"
#include "../common/global_define.h"
#include "../common/shareddb.h"
#include "../common/ipc_mutex.h"
#include "../common/memory_mapped_file.h"
#include "../common/eqemu_exception.h"
#include "../common/classes.h"
#include "../common/features.h"

void LoadSkillCaps(SharedDatabase *database, const std::string &prefix) {
	EQ::IPCMutex mutex("skill_caps");
	mutex.Lock();

	uint32 class_count = PLAYER_CLASS_COUNT;
	uint32 skill_count = EQ::skills::HIGHEST_SKILL + 1;
	uint32 level_count = HARD_LEVEL_CAP + 1;
	uint32 size = (class_count * skill_count * level_count * sizeof(uint16));

	auto Config = EQEmuConfig::get();
	std::string file_name = Config->SharedMemDir + prefix + std::string("skill_caps");
	EQ::MemoryMappedFile mmf(file_name, size);
	mmf.ZeroFile();

	void *ptr = mmf.Get();
	database->LoadSkillCaps(ptr);
	mutex.Unlock();
}
