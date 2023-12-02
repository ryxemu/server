#ifndef TIMEOUT_MANAGER_H
#define TIMEOUT_MANAGER_H

// ms between checking all timeouts
// timeouts are generally somewhat large, so its safe to use a
// value on the order of seconds here.
#define TIMEOUT_GRANULARITY 1000

#include "types.h"
#include "timer.h"

#include <vector>

// timeoutable objects automatically register themselves
// with the global TimeoutManager object
class TimeoutManager;
class Timeoutable {
	friend class TimeoutManager;

   public:
	// this frequency should generally be a multiple of TIMEOUT_GRANULARITY
	Timeoutable(uint32 check_frequency);
	virtual ~Timeoutable();

	virtual void CheckTimeout() = 0;

   private:
	// accessed directly by TimeoutManager
	Timer next_check;
};

class TimeoutManager {
	friend class Timeoutable;

   public:
	TimeoutManager();

	void CheckTimeouts();

   protected:
	// methods called by Timeoutable objects:
	void AddMember(Timeoutable *who);
	void DeleteMember(Timeoutable *who);

	std::vector<Timeoutable *> members;
};

extern TimeoutManager timeout_manager;

#endif
