#ifndef __EQEMU_TESTS_IPC_MUTEX_H
#define __EQEMU_TESTS_IPC_MUTEX_H

#include "cppunit/cpptest.h"
#include "../common/ipc_mutex.h"

class IPCMutexTest : public Test::Suite {
	typedef void (IPCMutexTest::*TestFunction)(void);

   public:
	IPCMutexTest() {
		TEST_ADD(IPCMutexTest::LockMutexTest);
		TEST_ADD(IPCMutexTest::UnlockMutexTest);
		TEST_ADD(IPCMutexTest::DoubleLockMutexTest);
		TEST_ADD(IPCMutexTest::DoubleUnlockMutexTest);
	}

	~IPCMutexTest() {
	}

   private:
	void LockMutexTest() {
		EQ::IPCMutex mutex("TestMutex1");
		TEST_ASSERT(mutex.Lock());
		TEST_ASSERT(mutex.Unlock());
	}

	void UnlockMutexTest() {
		EQ::IPCMutex mutex("TestMutex2");
		TEST_ASSERT(!mutex.Unlock());
	}

	void DoubleLockMutexTest() {
		EQ::IPCMutex mutex("TestMutex3");
		TEST_ASSERT(mutex.Lock());
		TEST_ASSERT(!mutex.Lock());
	}

	void DoubleUnlockMutexTest() {
		EQ::IPCMutex mutex("TestMutex4");
		TEST_ASSERT(mutex.Lock());
		TEST_ASSERT(mutex.Unlock());
		TEST_ASSERT(!mutex.Unlock());
	}
};

#endif
