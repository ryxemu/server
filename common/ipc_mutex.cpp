#include "ipc_mutex.h"
#ifdef _WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif
#include "types.h"
#include "eqemu_exception.h"
#include "config.h"

namespace EQ {
struct IPCMutex::Implementation {
#ifdef _WINDOWS
	HANDLE mut_;
#else
	int fd_;
#endif
};

IPCMutex::IPCMutex(std::string name) : locked_(false) {
	imp_ = new Implementation;
#ifdef _WINDOWS
	auto Config = Config::get();
	std::string final_name = Config->SharedMemDir + "EQEmuMutex_";
	final_name += name;

	imp_->mut_ = CreateMutex(nullptr,
	                         FALSE,
	                         final_name.c_str());

	if (!imp_->mut_) {
		EQ_EXCEPT("IPC Mutex", "Could not create mutex.");
	}
#else
	auto Config = Config::get();
	std::string final_name = Config->SharedMemDir + name;
	final_name += ".lock";

#ifdef __DARWIN
#if __DARWIN_C_LEVEL < 200809L
	imp_->fd_ = open(final_name.c_str(),
	                 O_RDWR | O_CREAT,
	                 S_IRUSR | S_IWUSR);
#else
	imp_->fd_ = open(final_name.c_str(),
	                 O_RDWR | O_CREAT | O_CLOEXEC,
	                 S_IRUSR | S_IWUSR);
#endif
#else
	imp_->fd_ = open(final_name.c_str(),
	                 O_RDWR | O_CREAT | O_CLOEXEC,
	                 S_IRUSR | S_IWUSR);
#endif

	if (imp_->fd_ == -1) {
		EQ_EXCEPT("IPC Mutex", "Could not create mutex.");
	}
#endif
}

IPCMutex::~IPCMutex() {
#ifdef _WINDOWS
	if (locked_) {
		ReleaseMutex(imp_->mut_);
	}
	CloseHandle(imp_->mut_);

#else
	if (locked_) {
		lockf(imp_->fd_, F_ULOCK, 0);
	}
	close(imp_->fd_);

#endif
	delete imp_;
}

bool IPCMutex::Lock() {
	if (locked_) {
		return false;
	}

#ifdef _WINDOWS
	DWORD wait_result = WaitForSingleObject(imp_->mut_, INFINITE);
	if (wait_result != WAIT_OBJECT_0) {
		return false;
	}
#else
	if (lockf(imp_->fd_, F_LOCK, 0) != 0) {
		return false;
	}
#endif
	locked_ = true;
	return true;
}

bool IPCMutex::Unlock() {
	if (!locked_) {
		return false;
	}
#ifdef _WINDOWS
	if (!ReleaseMutex(imp_->mut_)) {
		return false;
	}
#else
	if (lockf(imp_->fd_, F_ULOCK, 0) != 0) {
		return false;
	}
#endif
	locked_ = false;
	return true;
}
}  // namespace EQ
