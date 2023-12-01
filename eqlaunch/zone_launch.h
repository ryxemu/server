#ifndef ZONELAUNCH_H_
#define ZONELAUNCH_H_

#include "../common/proc_launcher.h"
#include "../common/timer.h"
#include <string>

class WorldServer;
class EQEmuConfig;

class ZoneLaunch : protected ProcLauncher::EventHandler {
   public:
	ZoneLaunch(WorldServer *world, const char *launcher_name,
	           const char *zone_name, uint16 port, const EQEmuConfig *config);
	virtual ~ZoneLaunch();

	void Stop(bool graceful = true);
	void Restart();

	bool Process();

	void SendStatus() const;

	const char *GetZone() const { return (m_zone.c_str()); }
	uint32 GetStartCount() const { return (m_startCount); }

	// should only be called during process init to setup the start timer.
	static void InitStartTimer();

   protected:
	bool IsRunning() const { return (m_state == StateStarted || m_state == StateStopPending || m_state == StateRestartPending); }

	void Start();

	void OnTerminate(const ProcLauncher::ProcRef &ref, const ProcLauncher::Spec *spec);

	enum {
		StateStartPending,
		StateStarted,
		StateRestartPending,
		StateStopPending,
		StateStopped
	} m_state;

	WorldServer *const m_world;
	const std::string m_zone;
	const char *const m_launcherName;
	const EQEmuConfig *const m_config;
	const uint16 m_port;

	Timer m_timer;
	ProcLauncher::ProcRef m_ref;
	uint32 m_startCount;

	uint32 m_killFails;

   private:
	static int s_running;
	static Timer s_startTimer;
};

#endif /*ZONELAUNCH_H_*/
