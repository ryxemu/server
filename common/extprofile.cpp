#include "global_define.h"
#include "extprofile.h"

// Set defaults in the extended profile...
void InitExtendedProfile(ExtendedProfile_Struct *p) {
	memset(p, 0, sizeof(ExtendedProfile_Struct));
	// set any special values here...
}

bool SetExtendedProfile(ExtendedProfile_Struct *to, char *old, unsigned int len) {
	if (len == 0 || old == nullptr) {
		// handle old chars without an extended profile...
		InitExtendedProfile(to);
		return (true);
	}
	if (len == sizeof(ExtendedProfile_Struct)) {
		memcpy(to, old, sizeof(ExtendedProfile_Struct));
		return (true);
	}

	// convert an old block of memory of size old to the new struct
	// and store the new results in 'to'

	// generic converter that will work as long as the structre
	// only grows, and nothign gets re-arranged
	if (len < sizeof(ExtendedProfile_Struct)) {
		InitExtendedProfile(to);
		memcpy(to, old, len);
		return (true);
	}

	return (false);
}
