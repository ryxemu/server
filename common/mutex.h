#ifndef MYMUTEX_H
#define MYMUTEX_H
#ifdef _WINDOWS
#include <winsock2.h>
#include <windows.h>
#else
#include <pthread.h>
#include "../common/unix.h"
#endif
#include "../common/types.h"

class Mutex {
   public:
	Mutex();
	~Mutex();

	void lock();
	void unlock();
	bool trylock();

   protected:
   private:
#if defined WIN32 || defined WIN64
	CRITICAL_SECTION CSMutex;
#else
	pthread_mutex_t CSMutex;
#endif
};

class LockMutex {
   public:
	LockMutex(Mutex* in_mut, bool iLock = true);
	~LockMutex();
	void unlock();
	void lock();

   private:
	bool locked;
	Mutex* mut;
};

// Somewhat untested...
// Multi-read, single write mutex -Quagmire
class MRMutex {
   public:
	MRMutex();
	~MRMutex();

	void ReadLock();
	bool TryReadLock();
	void UnReadLock();

	void WriteLock();
	bool TryWriteLock();
	void UnWriteLock();

	int32 ReadLockCount();
	int32 WriteLockCount();

   private:
	int32 rl;  // read locks in effect
	int32 wr;  // write lock requests pending
	int32 wl;  // write locks in effect (should never be more than 1)
	Mutex MCounters;
};

#endif
