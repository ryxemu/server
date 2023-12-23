#ifndef _EQSTREAMFACTORY_H

#define _EQSTREAMFACTORY_H

#include <queue>
#include <map>

#include "../common/eq_stream.h"
#include "../common/condition.h"
#include "../common/timeoutmgr.h"

class EQStream;
class Timer;

// EQStreamFactory is a UDP connection wrapper
class EQStreamFactory : private Timeoutable {
   private:
	int sock;

	bool ReaderRunning;
	Mutex MReaderRunning;
	bool WriterRunning;
	Mutex MWriterRunning;

	Condition WriterWork;

	EQStreamType StreamType;

	std::queue<EQStream *> NewStreams;
	Mutex MNewStreams;

	std::map<std::pair<uint32, uint16>, EQStream *> Streams;
	Mutex MStreams;

	Mutex MWritingStreams;

	virtual void CheckTimeout();

	Timer *DecayTimer;

	uint32 stream_timeout;

   public:
	EQStreamFactory(EQStreamType type, uint32 timeout = 61000) : Timeoutable(5000), stream_timeout(timeout) {
		ReaderRunning = false;
		WriterRunning = false;
		StreamType = type;
		sock = -1;
	}

	EQStream *Pop();
	void Push(EQStream *s);

	std::string Open(const std::string &address, int bind_port);
	bool IsOpen() { return sock != -1; }
	void Close();
	void ReaderLoop();
	void WriterLoop();
	void Stop() {
		StopReader();
		StopWriter();
	}
	void StopReader() {
		MReaderRunning.lock();
		ReaderRunning = false;
		MReaderRunning.unlock();
	}
	void StopWriter() {
		MWriterRunning.lock();
		WriterRunning = false;
		MWriterRunning.unlock();
		WriterWork.Signal();
	}
	void SignalWriter() { WriterWork.Signal(); }
};

#endif
