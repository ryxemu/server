#ifndef __CONDITION_H
#define __CONDITION_H

#include "global_define.h"
#include "mutex.h"
#ifndef WIN32
#include <pthread.h>
#endif

// Sombody, someday needs to figure out how to implement a condition
// system on windows...

class Condition {
   private:
#ifdef WIN32
	enum {
		SignalEvent = 0,
		BroadcastEvent,
		_eventCount
	};

	HANDLE m_events[_eventCount];
	uint32 m_waiters;
	CRITICAL_SECTION CSMutex;
#else
	pthread_cond_t cond;
	pthread_mutex_t mutex;
#endif
   public:
	Condition();
	void Signal();
	void SignalAll();
	void Wait();
	//		bool TimedWait(unsigned long usec);
	~Condition();
};

#endif
