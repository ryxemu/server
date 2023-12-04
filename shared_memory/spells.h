#ifndef __EQEMU_SHARED_MEMORY_SPELLS_H
#define __EQEMU_SHARED_MEMORY_SPELLS_H

#include <string>
#include "../common/config.h"

class SharedDatabase;
void LoadSpells(SharedDatabase *database, const std::string &prefix);

#endif
