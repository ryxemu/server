#ifndef TIMER_H
#define TIMER_H

#include "types.h"

// Disgrace: for windows compile
#ifdef _WINDOWS
#include "global_define.h"
int gettimeofday(timeval *tp, ...);
#endif

class Timer {
   public:
	Timer();
	Timer(uint32 duration);
	~Timer() {}
	bool Check(bool iReset = true);
	bool CheckKeepSynchronized(int tolerance = 200);
	void Enable();
	void Disable();
	void Start(uint32 duration = 0, bool ChangeResetTimer = true);
	uint32 GetRemainingTime();
	void Trigger();
	void Reset();
	void Stop();
	void Pause();
	void Resume();
	bool Paused();

	inline bool Enabled() { return enabled; }
	inline uint32 GetDuration() { return (Duration); }
	void SetDuration(uint32 duration, bool update_current_interval = false);

	static const uint32 SetCurrentTime();
	static const uint32 GetCurrentTime();
	static const uint32 GetTimeSeconds();  // returns a unix timestamp, not used by Timer class

   private:
	uint32 TriggerTime;
	uint32 TriggerEra;
	uint32 Duration;
	uint32 pause_time;
	bool enabled;

	static uint32 current_era;
	static uint32 current_time;
};

#endif
