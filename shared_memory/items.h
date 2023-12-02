#ifndef __EQEMU_SHARED_MEMORY_ITEMS_H
#define __EQEMU_SHARED_MEMORY_ITEMS_H

#include <string>
#include "../common/eqemu_config.h"

class SharedDatabase;
void LoadItems(SharedDatabase *database, const std::string &prefix);

#endif
