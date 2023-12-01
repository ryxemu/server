#ifndef __EQEMU_SHARED_MEMORY_LOOT_H
#define __EQEMU_SHARED_MEMORY_LOOT_H

#include <string>
#include "../common/eqemu_config.h"

class SharedDatabase;
void LoadLoot(SharedDatabase *database, const std::string &prefix);

#endif
