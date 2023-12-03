#ifndef __EQEMU_SHARED_MEMORY_SKILL_CAPS_H
#define __EQEMU_SHARED_MEMORY_SKILL_CAPS_H

#include <string>
#include "../common/config.h"

class SharedDatabase;
void LoadSkillCaps(SharedDatabase *database, const std::string &prefix);

#endif
