#ifndef PROCLAUNCHER_H_
#define PROCLAUNCHER_H_

#include "global_define.h"

#include <string>
#include <vector>
#include <map>

// I forced this object to become a singleton because it registers its
// signal handler for UNIX
class ProcLauncher {
	ProcLauncher();

   public:
	// Singleton method
	static ProcLauncher *get() { return (&s_launcher); }
	static void ProcessInThisThread();

#ifdef WIN32
	typedef DWORD ProcRef;
	static const ProcRef ProcError;
#else
	typedef pid_t ProcRef;
	static const ProcRef ProcError;
#endif
	class EventHandler;
	class Spec {
		friend class ProcLauncher;  // for visual c++
	   public:
		Spec();
		Spec(const Spec &other);
		Spec &operator=(const Spec &other);

		std::string program;
		std::vector<std::string> args;
		// std::map<std::string,std::string> environment;
		EventHandler *handler;  // optional, we do not own this pointer
		std::string logFile;    // empty = do not redirect output.
	   protected:
		// None of these fields get copied around
#ifdef WIN32
		PROCESS_INFORMATION proc_info;
#endif
	};
	class EventHandler {
	   public:
		virtual ~EventHandler() {}
		virtual void OnTerminate(const ProcRef &ref, const Spec *spec) = 0;
	};

	/* The main launch method, call to start a new background process. */
	ProcRef Launch(Spec *&to_launch);  // takes ownership of the pointer

	/* The terminate method */
	bool Terminate(const ProcRef &proc, bool graceful = true);
	void TerminateAll(bool final = true);

	/* The main processing method. Call regularly to check for terminated background processes. */
	void Process();

   protected:
	// std::vector<Spec *> m_specs;
	std::map<ProcRef, Spec *> m_running;  // we own the pointers in this map

	void ProcessTerminated(std::map<ProcRef, Spec *>::iterator &it);

   private:
	static ProcLauncher s_launcher;
#ifndef WIN32
	uint8 m_signalCount;
	static void HandleSigChild(int signum);
#endif
};

#endif /*PROCLAUNCHER_H_*/
