#ifdef _WINDOWS
#if (!defined(_MSC_VER) || (defined(_MSC_VER) && _MSC_VER < 1900))
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#endif
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif

#include "../common/races.h"
#include "encounter.h"
#include "entity.h"
#include "mob.h"

class Zone;

Encounter::Encounter(const char* enc_name)
    : Mob(
          nullptr, nullptr, 0, 0, 0, INVISIBLE_MAN, 0, BT_NoTarget, 0, 0, 0, 0, 0, glm::vec4(0, 0, 0, 0), 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, EQ::TintProfile(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) {
	encounter_name[0] = 0;
	strn0cpy(encounter_name, enc_name, 64);
	remove_me = false;
}

Encounter::~Encounter() {
}

bool Encounter::Process() {
	if (remove_me) return false;
	return true;
}
