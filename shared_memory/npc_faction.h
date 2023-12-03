#ifndef __EQEMU_SHARED_MEMORY_NPC_FACTION_H
#define __EQEMU_SHARED_MEMORY_NPC_FACTION_H

#include <string>
#include "../common/config.h"

class SharedDatabase;
void LoadFactions(SharedDatabase *database, const std::string &prefix);

#endif
