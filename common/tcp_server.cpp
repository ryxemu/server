#include "global_define.h"
#include "tcp_server.h"
#include "../common/eqemu_logsys.h"

#include <stdio.h>
#include <cstdlib>
#include <cstring>

#ifdef _WINDOWS
#include <process.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif

#define SERVER_LOOP_GRANULARITY 3  // # of ms between checking our socket/queues

BaseTCPServer::BaseTCPServer(uint16 in_port) {
	NextID = 1;
	pPort = in_port;
	sock = 0;
	pRunLoop = true;
#ifdef _WINDOWS
	_beginthread(BaseTCPServer::TCPServerLoop, 0, this);
#else
	pthread_t thread;
	pthread_create(&thread, nullptr, &BaseTCPServer::TCPServerLoop, this);
#endif
}

BaseTCPServer::~BaseTCPServer() {
	StopLoopAndWait();
}

void BaseTCPServer::StopLoopAndWait() {
	MRunLoop.lock();
	if (pRunLoop) {
		pRunLoop = false;
		MRunLoop.unlock();
		// wait for loop to stop.
		MLoopRunning.lock();
		MLoopRunning.unlock();
	} else {
		MRunLoop.unlock();
	}
}

bool BaseTCPServer::RunLoop() {
	bool ret;
	MRunLoop.lock();
	ret = pRunLoop;
	MRunLoop.unlock();
	return ret;
}

ThreadReturnType BaseTCPServer::TCPServerLoop(void *tmp) {
#ifdef _WINDOWS
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
#endif
	if (tmp == 0) {
		THREAD_RETURN(nullptr);
	}
	BaseTCPServer *tcps = (BaseTCPServer *)tmp;

#ifndef WIN32
	Log(Logs::Detail, Logs::None, "Starting TCPServerLoop with thread ID %d", pthread_self());
#endif

	tcps->MLoopRunning.lock();
	while (tcps->RunLoop()) {
		Sleep(SERVER_LOOP_GRANULARITY);
		tcps->Process();
	}
	tcps->MLoopRunning.unlock();

#ifndef WIN32
	Log(Logs::Detail, Logs::None, "Ending TCPServerLoop with thread ID %d", pthread_self());
#endif

	THREAD_RETURN(nullptr);
}

void BaseTCPServer::Process() {
	ListenNewConnections();
}

void BaseTCPServer::ListenNewConnections() {
	SOCKET tmpsock;
	struct sockaddr_in from;
	struct in_addr in;
	unsigned int fromlen;
	unsigned short port;

	from.sin_family = AF_INET;
	fromlen = sizeof(from);
	LockMutex lock(&MSock);
#ifndef DARWIN  // Corysia - On OSX, 0 is a valid fd.
	if (!sock)
		return;
#else
	if (sock == -1) return;
#endif

		// Check for pending connects
#ifdef _WINDOWS
	unsigned long nonblocking = 1;
	while ((tmpsock = accept(sock, (struct sockaddr *)&from, (int *)&fromlen)) != INVALID_SOCKET) {
		ioctlsocket(tmpsock, FIONBIO, &nonblocking);
#else
#ifdef __CYGWIN__
	while ((tmpsock = accept(sock, (struct sockaddr *)&from, (int *)&fromlen)) != INVALID_SOCKET) {
#else
	while ((tmpsock = accept(sock, (struct sockaddr *)&from, &fromlen)) != INVALID_SOCKET) {
#endif
		fcntl(tmpsock, F_SETFL, O_NONBLOCK);
#endif
		int bufsize = 64 * 1024;  // 64kbyte recieve buffer, up from default of 8k
		setsockopt(tmpsock, SOL_SOCKET, SO_RCVBUF, (char *)&bufsize, sizeof(bufsize));
		port = from.sin_port;
		in.s_addr = from.sin_addr.s_addr;

		// New TCP connection, this must consume the socket.
		CreateNewConnection(GetNextID(), tmpsock, in.s_addr, ntohs(from.sin_port));
	}
}

// Listen to a new TCP socket connection
std::string BaseTCPServer::Open(std::string bind_address, uint16 bind_port) {
	LockMutex lock(&MSock);
	if (sock != 0) {
		return "Listening socket already open";
	}
	if (bind_port != 0) {
		pPort = bind_port;
	}

#ifdef _WINDOWS
	SOCKADDR_IN address;
	unsigned long nonblocking = 1;
#else
	struct sockaddr_in address;
#endif
	int reuse_addr = 1;

	//	Setup internet address information.
	//	This is used with the bind() call
	memset((char *)&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(pPort);
	address.sin_addr.s_addr = htonl(INADDR_ANY);

	//	Setting up TCP port for new TCP connections
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		return fmt::format("socket: {}", strerror(errno));
	}

	// Quag: dont think following is good stuff for TCP, good for UDP
	// Mis: SO_REUSEADDR shouldn't be a problem for tcp--allows you to restart
	// without waiting for conns in TIME_WAIT to die
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse_addr, sizeof(reuse_addr));

	if (bind(sock, (struct sockaddr *)&address, sizeof(address)) < 0) {
#ifdef _WINDOWS
		closesocket(sock);
#else
		close(sock);
#endif
		sock = 0;
		return fmt::format("bind: {}", strerror(errno));
	}

	int bufsize = 64 * 1024;  // 64kbyte recieve buffer, up from default of 8k
	setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char *)&bufsize, sizeof(bufsize));
#ifdef _WINDOWS
	ioctlsocket(sock, FIONBIO, &nonblocking);
#else
	fcntl(sock, F_SETFL, O_NONBLOCK);
#endif

	if (listen(sock, SOMAXCONN) == SOCKET_ERROR) {
#ifdef _WINDOWS
		closesocket(sock);
#else
		close(sock);
#endif
		sock = 0;
		return fmt::format("listen: {}", strerror(errno));
	}

	return "";
}

void BaseTCPServer::Close() {
	StopLoopAndWait();

	LockMutex lock(&MSock);
	if (sock) {
#ifdef _WINDOWS
		closesocket(sock);
#else
		close(sock);
#endif
	}
	sock = 0;
}

bool BaseTCPServer::IsOpen() {
	MSock.lock();
	bool ret = (bool)(sock != 0);
	MSock.unlock();
	return ret;
}
