#include "condition.h"

#ifdef _WINDOWS

Condition::Condition() {
	m_events[SignalEvent] = CreateEvent(nullptr,      // security
	                                    FALSE,        // is auto-reset event?
	                                    FALSE,        // is signaled initially?
	                                    nullptr);     // name
	m_events[BroadcastEvent] = CreateEvent(nullptr,   // security
	                                       TRUE,      // is auto-reset event?
	                                       FALSE,     // is signaled initially?
	                                       nullptr);  // name
	m_waiters = 0;
	InitializeCriticalSection(&CSMutex);
}

Condition::~Condition() {
	DeleteCriticalSection(&CSMutex);
	CloseHandle(m_events[SignalEvent]);
	CloseHandle(m_events[BroadcastEvent]);
}

void Condition::Signal() {
	EnterCriticalSection(&CSMutex);
	if (m_waiters > 0)
		SetEvent(m_events[SignalEvent]);
	LeaveCriticalSection(&CSMutex);
}

void Condition::SignalAll() {
	EnterCriticalSection(&CSMutex);
	if (m_waiters > 0)
		SetEvent(m_events[BroadcastEvent]);
	LeaveCriticalSection(&CSMutex);
}

void Condition::Wait() {
	EnterCriticalSection(&CSMutex);

	m_waiters++;

	LeaveCriticalSection(&CSMutex);
	int result = WaitForMultipleObjects(_eventCount, m_events, FALSE, INFINITE);
	EnterCriticalSection(&CSMutex);

	m_waiters--;

	// see if we are the last person waiting on the condition, and there was a broadcast
	// if so, we need to reset the broadcast event.
	if (m_waiters == 0 && result == (WAIT_OBJECT_0 + BroadcastEvent))
		ResetEvent(m_events[BroadcastEvent]);

	LeaveCriticalSection(&CSMutex);
}

#else
#include <pthread.h>
#include <sys/time.h>
#include <errno.h>

Condition::Condition() {
	pthread_cond_init(&cond, nullptr);
	pthread_mutex_init(&mutex, nullptr);
}

void Condition::Signal() {
	pthread_mutex_lock(&mutex);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
}

void Condition::SignalAll() {
	pthread_mutex_lock(&mutex);
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
}

void Condition::Wait() {
	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&cond, &mutex);
	pthread_mutex_unlock(&mutex);
}

/*
I commented this specifically because I think it might be very
difficult to write a windows counterpart to it, so I would like
to discourage its use until we can confirm that it can be reasonably
implemented on windows.

bool Condition::TimedWait(unsigned long usec)
{
struct timeval now;
struct timespec timeout;
int retcode=0;
    pthread_mutex_lock(&mutex);
    gettimeofday(&now,nullptr);
    now.tv_usec+=usec;
    timeout.tv_sec = now.tv_sec + (now.tv_usec/1000000);
    timeout.tv_nsec = (now.tv_usec%1000000) *1000;
    //cout << "now=" << now.tv_sec << "."<<now.tv_usec << endl;
    //cout << "timeout=" << timeout.tv_sec << "."<<timeout.tv_nsec << endl;
    retcode=pthread_cond_timedwait(&cond,&mutex,&timeout);
    pthread_mutex_unlock(&mutex);

    return retcode!=ETIMEDOUT;
}
*/

Condition::~Condition() {
	pthread_mutex_lock(&mutex);
	pthread_cond_destroy(&cond);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
}

#endif
