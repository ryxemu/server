#ifndef __EQEMU_SHARED_MEMORY_BASE_DATA_H
#define __EQEMU_SHARED_MEMORY_BASE_DATA_H

#include <string>
#include "../common/config.h"

class SharedDatabase;
void LoadBaseData(SharedDatabase *database, const std::string &prefix);

#endif
