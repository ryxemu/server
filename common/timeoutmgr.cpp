#include "../common/global_define.h"

// #define TIMEOUT_DEBUG

#include "timeoutmgr.h"

Timeoutable::Timeoutable(uint32 check_frequency)
    : next_check(check_frequency) {
	timeout_manager.AddMember(this);
}

Timeoutable::~Timeoutable() {
	timeout_manager.DeleteMember(this);
}

TimeoutManager::TimeoutManager() {
}

void TimeoutManager::CheckTimeouts() {
	std::vector<Timeoutable *>::iterator cur, end;
	cur = members.begin();
	end = members.end();
	for (; cur != end; ++cur) {
		Timeoutable *it = *cur;
		if (it->next_check.Check()) {
#ifdef TIMEOUT_DEBUG
			Log(Logs::General, Logs::None, , "Checking timeout on 0x%x\n", it);
#endif
			it->CheckTimeout();
		}
	}
}

// methods called by Timeoutable objects:
void TimeoutManager::AddMember(Timeoutable *who) {
	if (who == nullptr)
		return;

	DeleteMember(who);  // just in case... prolly not needed.
	members.push_back(who);
#ifdef TIMEOUT_DEBUG
	Log(Logs::General, Logs::None, , "Adding timeoutable 0x%x\n", who);
#endif
}

void TimeoutManager::DeleteMember(Timeoutable *who) {
#ifdef TIMEOUT_DEBUG
	Log(Logs::General, Logs::None, , "Removing timeoutable 0x%x\n", who);
#endif
	std::vector<Timeoutable *>::iterator cur, end;
	cur = members.begin();
	end = members.end();
	for (; cur != end; ++cur) {
		if (*cur == who) {
			members.erase(cur);
			return;
		}
	}
}
