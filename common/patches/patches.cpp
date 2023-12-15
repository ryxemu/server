
#include "../global_define.h"
#include "patches.h"

#include "mac.h"
#include "ls20231211.h"

void RegisterAllPatches(EQStreamIdentifier &into) {
	Mac::Register(into);
	Ls20231211::Register(into);
}

void ReloadAllPatches() {
	Mac::Reload();
	Ls20231211::Reload();
}
