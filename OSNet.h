/***************************************************************************************************************:')

OSNet.h

Network includes, typedefs, defines, initialization and some useful functions.
You must call InitNet() before using any low-level network function.

Fabrice Le Bars

Created : 2007

***************************************************************************************************************:)*/

// Prevent Visual Studio Intellisense from defining _WIN32 and _MSC_VER when we use 
// Visual Studio to edit Linux or Borland C++ code.
#ifdef __linux__
#	undef _WIN32
#endif // __linux__
#if defined(__GNUC__) || defined(__BORLANDC__)
#	undef _MSC_VER
#endif // defined(__GNUC__) || defined(__BORLANDC__)

#ifndef OSNET_H
#define OSNET_H

#include "OSTime.h"
#ifndef DISABLE_THREADS_OSNET
#include "OSThread.h"
#endif // !DISABLE_THREADS_OSNET

/*
Debug macros specific to OSNet.
*/
#ifdef _DEBUG_MESSAGES_OSUTILS
#	define _DEBUG_MESSAGES_OSNET
#endif // _DEBUG_MESSAGES_OSUTILS

#ifdef _DEBUG_WARNINGS_OSUTILS
#	define _DEBUG_WARNINGS_OSNET
#endif // _DEBUG_WARNINGS_OSUTILS

#ifdef _DEBUG_ERRORS_OSUTILS
#	define _DEBUG_ERRORS_OSNET
#endif // _DEBUG_ERRORS_OSUTILS

#ifdef _DEBUG_MESSAGES_OSNET
#	define PRINT_DEBUG_MESSAGE_OSNET(params) PRINT_DEBUG_MESSAGE(params)
#else
#	define PRINT_DEBUG_MESSAGE_OSNET(params)
#endif // _DEBUG_MESSAGES_OSNET

#ifdef _DEBUG_WARNINGS_OSNET
#	define PRINT_DEBUG_WARNING_OSNET(params) PRINT_DEBUG_WARNING(params)
#else
#	define PRINT_DEBUG_WARNING_OSNET(params)
#endif // _DEBUG_WARNINGS_OSNET

#ifdef _DEBUG_ERRORS_OSNET
#	define PRINT_DEBUG_ERROR_OSNET(params) PRINT_DEBUG_ERROR(params)
#else
#	define PRINT_DEBUG_ERROR_OSNET(params)
#endif // _DEBUG_ERRORS_OSNET

#ifdef _WIN32
// The maximum number of sockets that an application can actually use is independent of 
// the number of sockets supported by a particular implementation. The maximum number of 
// sockets that a Windows Sockets application can use is determined at compile time by the
// manifest constant FD_SETSIZE. This value is used in constructing the FD_SET structures 
// used in select. The default value in Winsock2.h is 64.
//#define FD_SETSIZE 64
#else
//#define FD_SETSIZE 64
#endif // _WIN32

#ifdef _WIN32
#ifdef __BORLANDC__
// Disable some Borland C++ Builder warnings that happen in ws2tcpip.h.
#pragma warn -8004
#endif // __BORLANDC__
#include <winsock2.h>
#if (_WIN32_WINNT <= 0x0500)
#include <ws2tcpip.h>
#include <Wspiapi.h>
#else
#include <ws2tcpip.h>
#endif // (_WIN32_WINNT <= 0x0500)
//#include <iphlpapi.h>
#ifdef __BORLANDC__
// Restore the Borland C++ Builder warnings previously disabled for ws2tcpip.h.
#pragma warn .8004
#endif // __BORLANDC__
#else 
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#ifndef DISABLE_IOCTLSOCKET
#include <sys/ioctl.h>
#endif // !DISABLE_IOCTLSOCKET
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif // _WIN32

#ifndef DEFAULT_SOCK_TIMEOUT
#define DEFAULT_SOCK_TIMEOUT 10000
#endif // !DEFAULT_SOCK_TIMEOUT

#ifdef _WIN32
/*
Format a message corresponding to the last error in a system call related 
to network with Winsock (thread-safe).

char* buf : (INOUT) Valid pointer to a buffer that will receive the message.
int buflen : (IN) Size of the buffer in bytes.

Return : buf.
*/
inline char* WSAFormatLastErrorMsg(char* buf, int buflen)
{
	TCHAR* tstr = (TCHAR*)calloc((size_t)buflen, sizeof(TCHAR));

	memset(buf, 0, (size_t)buflen);

	if (tstr == NULL)
	{
		sprintf(buf, "calloc failed. ");
		buf[buflen-1] = 0;
		return buf;
	}

	memset(tstr, 0, (size_t)(buflen*sizeof(TCHAR)));

	if (!FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS | 
		FORMAT_MESSAGE_MAX_WIDTH_MASK, // Remove the line break at the end. 
		// Note that there is still a dot and a space at the end.
		NULL,
		WSAGetLastError(),
		0,
		tstr,
		(DWORD)buflen,
		NULL
		))
	{
		sprintf(buf, "FormatMessage failed. ");
		buf[buflen-1] = 0;
		free(tstr); tstr = NULL;
		return buf;
	}

#ifdef UNICODE
	wcstombs(buf, tstr, buflen);
#else
	memcpy(buf, tstr, buflen);
#endif // UNICODE
	buf[buflen-1] = 0;
	free(tstr); tstr = NULL;

	return buf;
}
#else
typedef int SOCKET;

#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)

#define SD_RECEIVE SHUT_RD
#define SD_SEND SHUT_WR
#define SD_BOTH SHUT_RDWR

#ifndef DISABLE_IOCTLSOCKET
#define ioctlsocket ioctl
#endif // !DISABLE_IOCTLSOCKET
#define closesocket(sock) close((sock))
#endif // _WIN32

// Specific macro used with PRINT_DEBUG_MESSAGE, PRINT_DEBUG_WARNING 
// or PRINT_DEBUG_ERROR to return the message corresponding to the last error 
// in a system call related to network (with Winsock for Windows) in the 
// current thread.
#ifdef _WIN32
#define WSAGetLastErrorMsg() WSAFormatLastErrorMsg(szLastErrMsg, LAST_ERROR_MSG_SIZE)
#else 
#define WSAGetLastErrorMsg GetLastErrorMsg
#endif // _WIN32

/*
Initialize the network. Must be called once before the use of any network function. 
Use ReleaseNet() to release the network at the end.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int InitNet(void)
{
#ifdef _WIN32
	WSADATA wsaData;

	// Initiate use of the Winsock 2 DLL (WS2_32.dll) by a process.
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	switch (iResult)
	{
	case EXIT_SUCCESS: 
		break;
#ifdef _DEBUG_ERRORS_OSNET
	case WSASYSNOTREADY: 
		PRINT_DEBUG_ERROR_OSNET(("InitNet error (%s) : %s"
			"\n", 
			strtime_m(), 
			"The underlying network subsystem is not ready for network communication. "));
		return EXIT_FAILURE;
	case WSAVERNOTSUPPORTED: 
		PRINT_DEBUG_ERROR_OSNET(("InitNet error (%s) : %s"
			"\n", 
			strtime_m(), 
			"The version of Windows Sockets support requested is not provided by this particular Windows Sockets implementation. "));
		return EXIT_FAILURE;
	case WSAEINPROGRESS: 
		PRINT_DEBUG_ERROR_OSNET(("InitNet error (%s) : %s"
			"\n", 
			strtime_m(), 
			"A blocking Windows Sockets 1.1 operation is in progress. "));
		return EXIT_FAILURE;
	case WSAEPROCLIM: 
		PRINT_DEBUG_ERROR_OSNET(("InitNet error (%s) : %s"
			"\n", 
			strtime_m(), 
			"A limit on the number of tasks supported by the Windows Sockets implementation has been reached. "));
		return EXIT_FAILURE;
	case WSAEFAULT: 
		PRINT_DEBUG_ERROR_OSNET(("InitNet error (%s) : %s"
			"\n", 
			strtime_m(), 
			"The lpWSAData parameter is not a valid pointer. "));
		return EXIT_FAILURE;
#endif // _DEBUG_ERRORS_OSNET
	default:
		PRINT_DEBUG_ERROR_OSNET(("InitNet error (%s) : %s"
			"\n", 
			strtime_m(), 
			"WSAStartup failed. "));
		return EXIT_FAILURE;
	}
#else
#ifndef DISABLE_IGNORE_SIGPIPE
	// See https://stackoverflow.com/questions/17332646/server-dies-on-send-if-client-was-closed-with-ctrlc...
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
	{
		PRINT_DEBUG_WARNING_OSNET(("InitNet warning (%s) : %s"
			"\n",
			strtime_m(),
			"signal failed. "));
	}
#endif // DISABLE_IGNORE_SIGPIPE
#endif // _WIN32

	return EXIT_SUCCESS;
}

/*
Release the network (previously initialized by InitNet()).

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int ReleaseNet(void)
{
#ifdef _WIN32
	// Terminate use of the Winsock 2 DLL (WS2_32.dll).
	int iResult = WSACleanup();
	switch (iResult)
	{
	case EXIT_SUCCESS: 
		break;
#ifdef _DEBUG_ERRORS_OSNET
	case WSANOTINITIALISED: 
		PRINT_DEBUG_ERROR_OSNET(("ReleaseNet error (%s) : %s"
			"\n", 
			strtime_m(), 
			"A successful WSAStartup call must occur before using this function. "));
		return EXIT_FAILURE;
	case WSAENETDOWN: 
		PRINT_DEBUG_ERROR_OSNET(("ReleaseNet error (%s) : %s"
			"\n", 
			strtime_m(), 
			"The network subsystem has failed. "));
		return EXIT_FAILURE;
	case WSAEINPROGRESS: 
		PRINT_DEBUG_ERROR_OSNET(("ReleaseNet error (%s) : %s"
			"\n", 
			strtime_m(), 
			"A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function. "));
		return EXIT_FAILURE;
#endif // _DEBUG_ERRORS_OSNET
	default:
		PRINT_DEBUG_ERROR_OSNET(("ReleaseNet error (%s) : %s"
			"\n", 
			strtime_m(), 
			"WSACleanup failed. "));
		return EXIT_FAILURE;
	}
#endif

	return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Portable functions that can be directly used.
//////////////////////////////////////////////////////////////////////////////////////////

// Note that struct sockaddr variables should be defined as struct sockaddr_storage (to be protocol independant) and then 
// cast to struct sockaddr when called in functions that need this type (especially when it is a pointer).

// If a send or receive operation times out on a socket, the socket state is indeterminate, and should not be used.

// If the pNodeName parameter points to a computer name, all permanent addresses for the computer that can be used as a source address are returned. 
// If the pNodeName parameter points to a string equal to "localhost", all loopback addresses on the local computer are returned. 
// If the pNodeName parameter contains an empty string, all registered addresses on the local computer are returned. 
// ppResult is a linked list.
// Do not set errno, use gai_strerror() for Linux (thread-safe?) or WSAGetLastErrorMsg() for Windows.
//int getaddrinfo(char* pNodeName, char* pServiceName, struct addrinfo* pHints, struct addrinfo** ppResult);

// Free the linked-list returned by getaddrinfo()
//void freeaddrinfo(struct addrinfo* pAi);

// Convert a socket address to a corresponding host/address and service/port.
// Use NI_MAXHOST and NI_MAXSERV for the size of host and serv.
// flags can be a combination of NI_NAMEREQD (a host name that cannot be resolved by DNS results in an error),
// NI_NOFQDN (return only the hostname part of the fully qualified domain name for local hosts)
// NI_NUMERICHOST (returns the numeric form of the host name instead of its name) 
// NI_NUMERICSERV (returns the port number of the service instead of its name)
// NI_DGRAM (indicates that the service is an UDP service rather than TCP)
// Do not set errno, use gai_strerror() for Linux (thread-safe?) or WSAGetLastErrorMsg() for Windows.
//int getnameinfo(const struct sockaddr* sa, socklen_t salen, char* host, size_t hostlen, char* serv, size_t servlen, int flags);

// Translate the error codes of getaddrinfo() and getnameinfo() to a string for Linux.
//const char* gai_strerror(int errcode);

/*
Create a socket for a specific protocol (TCP/IPv4, UDP/IPv4, TCP/IPv6 or UDP/IPv6 are the 
most common).
Used at the beginning to create a server or client application.
Often use the addrinfo results of a call to getaddrinfo().
InitNet() must be called before using any network function.

int af : (IN) Address family : AF_INET for IPv4, AF_INET6 for IPv6. Often set to the ai_family 
field of an addrinfo element of the linked list returned by getaddrinfo().
int type : (IN) Socket type : SOCK_STREAM for TCP, SOCK_DGRAM for UDP. Often set to the ai_socktype 
field of an addrinfo element of the linked list returned by getaddrinfo().
int protocol : (IN) Protocol to be used : IPPROTO_TCP for TCP, IPPROTO_UDP for UDP. Often set to the ai_protocol 
field of an addrinfo element of the linked list returned by getaddrinfo().

Return : The socket created or INVALID_SOCKET if there is an error.
*/
//SOCKET socket(int af, int type, int protocol);

/*
Close an existing socket. 
InitNet() must be called before using any network function.

SOCKET s : (IN) Socket to close.

Return : EXIT_SUCCESS or SOCKET_ERROR if there is an error.
*/
//int closesocket(SOCKET s);

/*
Associate a local address and port with a server socket.
InitNet() must be called before using any network function.

SOCKET s : (IN) Unbound server socket.
struct sockaddr* name : (IN) Address family, host address and port to assign to the socket as a sockaddr structure. 
Can be obtained from getaddrinfo() (ai_addr field of the resulting addrinfo structures) or built using its 
fields sin_family, sin_addr.s_addr (using the conversion function inet_addr()) and sin_port (using the 
conversion function htons()). There are several special addresses : INADDR_LOOPBACK ("127.0.0.1") always 
refers to the local host via the loopback device, INADDR_ANY ("0.0.0.0") means any address for binding. 
When INADDR_ANY is specified, the socket will be bound to all local interfaces.
int namelen : (IN) Length of the value in the name parameter in bytes.

Return : EXIT_SUCCESS or SOCKET_ERROR if there is an error.
*/
//int bind(SOCKET s, struct sockaddr* name, int namelen);

/* 
Place a socket in a state in which it is listening for an incoming connection. The socket is put into 
passive mode where incoming connection requests are acknowledged and queued pending acceptance by the 
process. If a connection request arrives and the queue is full, the client will receive an error.
Should be used only with TCP sockets.
InitNet() must be called before using any network function.

SOCKET s : (IN) Bound and unconnected server socket.
int backlog : (IN) Maximum length of the queue of pending connections. Set to 1 if there 
should be only 1 simultaneous client or to SOMAXCONN for a default maximum reasonable value.

Return : EXIT_SUCCESS or SOCKET_ERROR if there is an error.
*/
//int listen(SOCKET s, int backlog);

/*
Determine the status of the sockets in the different fd_set structures, waiting if necessary until 
at least one socket meets the specified criteria depending on timeout. Upon return, the fd_set structures 
are updated to reflect the subset of the sockets that meet the specified condition. 
Macros to manipulate and check fd_set contents :

FD_ZERO(*set) 
Initialize the set to the null set.

FD_SET(s, *set) 
Add socket s to set.

FD_ISSET(s, *set) 
Nonzero if s is a member of the set. Otherwise, 0.

FD_CLR(s, *set) 
Remove the socket s from set.

Structure to define the timeout :

struct timeval {
long tv_sec; // Seconds.
long tv_usec; // Microseconds.
};

InitNet() must be called before using any network function.

int nfds : (IN) Highest-numbered file descriptor in any of the three sets, plus 1.
fd_set* pReadfds : (INOUT) Valid pointer to a set of sockets to be checked for readability 
(data is available i.e. a recv(), recvfrom() is guaranteed not to block, a connect request has been received 
by a listening socket such that an accept() is guaranteed to complete without blocking, or a request to 
close the socket has been received). NULL to ignore.
fd_set* pWritefds : (INOUT) Valid pointer to a set of sockets to be checked for writability (data can be 
sent i.e. a send(), sendto() is guaranteed to succeed). NULL to ignore.
fd_set* pExceptfds : (INOUT) Valid pointer to a set of sockets to be checked for errors/exceptions (do not use). 
NULL to ignore.
struct timeval* pTimeout : (INOUT) Valid pointer to a timeval structure specifying the maximum time to wait, 
NULL for infinite. Return immediately if the structure is initialized to {0,0}. The structure may be modified 
after the call.

Return : The total number of sockets contained in the updated fd_set structures, 0 if the time limit expired 
or SOCKET_ERROR if there is an error.
*/
//int select(int nfds, fd_set* pReadfds, fd_set* pWritefds, fd_set* pExceptfds, struct timeval* pTimeout);

/*
Extract the first connection request on the queue of pending connections for a listening socket.
Can block the caller until a connection is present.
Should be used only with TCP sockets.
InitNet() must be called before using any network function.

SOCKET s : (IN) Bound and listening server socket.
struct sockaddr* addr : (INOUT) Address family, host address and port of the accepted client socket as a 
sockaddr structure (fields sin_family, sin_addr.s_addr (using the conversion function inet_addr()) and 
sin_port (using the conversion function htons()). NULL to ignore.
int* addrlen : (INOUT) Valid pointer to the length of the addr parameter in bytes. 
On return it will contain the actual length in bytes of the address returned. NULL to ignore.

Return : The client socket or INVALID_SOCKET if there is an error.
*/
//SOCKET accept(SOCKET s, struct sockaddr* addr, int* addrlen);

/*
Establish a connection to a server.
Usually used with TCP sockets.
InitNet() must be called before using any network function.

SOCKET s : (IN) Unconnected client socket.
struct sockaddr* name : (IN) Address family, host address and port of the server socket as a sockaddr 
structure (fields sin_family, sin_addr.s_addr (using the conversion function inet_addr()) and sin_port 
(using the conversion function htons()).
int namelen : (IN) Length of the value in the name parameter in bytes.

Return : EXIT_SUCCESS or SOCKET_ERROR if there is an error.
*/
//int connect(SOCKET s, struct sockaddr* name, int namelen);

//int send(SOCKET s);

//int recv(SOCKET s);

/*
Usually used with UDP sockets.
InitNet() must be called before using any network function.

struct sockaddr* to : (IN) Address family, host address and port of the target socket as a sockaddr 
structure (fields sin_family, sin_addr.s_addr (using the conversion function inet_addr()) and sin_port 
(using the conversion function htons()).
int tolen : (IN) Length of the value in the to parameter in bytes.

*/
//int sendto(SOCKET s, char* buf, int len, int flags, struct sockaddr* to, int tolen);

/*
Usually used with UDP sockets.
InitNet() must be called before using any network function.

struct sockaddr* from : (INOUT) Address family, host address and port of the source socket as a 
sockaddr structure (fields sin_family, sin_addr.s_addr (using the conversion function inet_addr()) and 
sin_port (using the conversion function htons()). NULL to ignore.
socklen_t* fromlen : (INOUT) Valid pointer to the length of the from parameter in bytes. 
On return it will contain the actual length in bytes of the address returned. NULL to ignore.

*/
//int recvfrom(SOCKET s, char* buf, int len, int flags, struct sockaddr* from, socklen_t* fromlen);

//int shutdown(SOCKET s);

//int setsockopt(SOCKET s, int level, int optname, char *optval, int optlen);

/*
Set timeout options for a socket.

SOCKET sock : (IN) Socket.
int timeout : (IN) Timeout in ms for send and recv (0 to disable timeouts).

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int setsockettimeouts(SOCKET sock, int timeout)
{
#ifdef _WIN32
	int iOptVal = 0;
#else
	struct timeval tv;
#endif // _WIN32
	int iOptLen = 0;

#ifdef _WIN32
	iOptVal = timeout; // In ms.
	iOptLen = sizeof(int);
	if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&iOptVal, iOptLen) == SOCKET_ERROR) 
	{
		PRINT_DEBUG_WARNING_OSNET(("setsockettimeouts warning (%s) : %s(sock=%d, timeout=%d)\n", 
			strtime_m(), 
			"setsockopt failed. ", 
			(int)sock, timeout));
		//return EXIT_FAILURE;
	}
	if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&iOptVal, iOptLen) == SOCKET_ERROR) 
	{
		PRINT_DEBUG_WARNING_OSNET(("setsockettimeouts warning (%s) : %s(sock=%d, timeout=%d)\n", 
			strtime_m(), 
			"setsockopt failed. ", 
			(int)sock, timeout));
		//return EXIT_FAILURE;
	}
#else
	tv.tv_sec = (long)(timeout/1000);
	tv.tv_usec = (long)((timeout%1000)*1000);
	iOptLen = sizeof(struct timeval);
	if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, iOptLen) == SOCKET_ERROR)
	{
		PRINT_DEBUG_WARNING_OSNET(("setsockettimeouts warning (%s) : %s(sock=%d, timeout=%d)\n", 
			strtime_m(), 
			"setsockopt failed. ", 
			(int)sock, timeout));
		//return EXIT_FAILURE;
	}
	if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, iOptLen) == SOCKET_ERROR)
	{
		PRINT_DEBUG_WARNING_OSNET(("setsockettimeouts warning (%s) : %s(sock=%d, timeout=%d)\n", 
			strtime_m(), 
			"setsockopt failed. ", 
			(int)sock, timeout));
		//return EXIT_FAILURE;
	}
#endif // _WIN32

	return EXIT_SUCCESS;
}

/*
Set SO_REUSEADDR option for a socket.

SOCKET sock : (IN) Socket.
BOOL reuseaddr : (IN) 1 to enable SO_REUSEADDR, 0 to disable.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int setsocketreuseaddr(SOCKET sock, BOOL reuseaddr)
{
	int iOptVal = 0;
	int iOptLen = 0;

	iOptVal = (int)reuseaddr;
	iOptLen = sizeof(int);
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&iOptVal, iOptLen) == SOCKET_ERROR) 
	{
		PRINT_DEBUG_WARNING_OSNET(("setsocketreuseaddr warning (%s) : %s(sock=%d, reuseaddr=%d)\n", 
			strtime_m(), 
			"setsockopt failed. ", 
			(int)sock, (int)reuseaddr));
		//return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/*
Connect to an IPv4 TCP server.

SOCKET* pSock : (INOUT) Valid pointer to a socket that will be used to communicate with the server.
char* address : (IN) IPv4 address of the server.
char* port : (IN) TCP port of the server.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int inittcpcli(SOCKET* pSock, char* address, char* port)
{
	struct sockaddr_in sa;

#ifdef _WIN32
	WSADATA wsaData;
#endif // _WIN32

#ifdef _WIN32
	// Initiate use of the Winsock 2 DLL (WS2_32.dll) by a process.
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("inittcpcli error (%s) : %s(address=%s, port=%s)\n", 
			strtime_m(), 
			"WSAStartup failed. ", 
			address, port));
		return EXIT_FAILURE;
	}
#endif // _WIN32

	// Create a TCP IPv4 socket.
	*pSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*pSock == INVALID_SOCKET)
	{
		PRINT_DEBUG_ERROR_OSNET(("inittcpcli error (%s) : %s(address=%s, port=%s)\n", 
			strtime_m(), 
			"socket failed. ", 
			address, port));
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32
		return EXIT_FAILURE;
	}

	// Configure timeouts for send and recv.
	if (setsockettimeouts(*pSock, DEFAULT_SOCK_TIMEOUT) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("inittcpcli error (%s) : %s(address=%s, port=%s)\n", 
			strtime_m(), 
			"setsockettimeouts failed. ", 
			address, port));
		closesocket(*pSock);
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32
		return EXIT_FAILURE;
	}

	memset(&sa, 0, sizeof(sa));

	// The sockaddr_in structure specifies the address family,
	// IP address, and port of the server to be connected to.
	sa.sin_family = AF_INET;
	sa.sin_port = htons((unsigned short)atoi(port));
	sa.sin_addr.s_addr = inet_addr(address);

	// Connect to server.
	if (connect(*pSock, (struct sockaddr*)&sa, sizeof(sa)) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("inittcpcli error (%s) : %s(address=%s, port=%s)\n", 
			strtime_m(), 
			"connect failed. ", 
			address, port));
		closesocket(*pSock);
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/*
Disconnect from an IPv4 TCP server.

SOCKET sock : (IN) Socket used to communicate with the server.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int releasetcpcli(SOCKET sock)
{
	// Shutdown the connection.
	if (shutdown(sock, SD_BOTH) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_WARNING_OSNET(("releasetcpcli warning (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			"shutdown failed. ", 
			(int)sock));
		//return EXIT_FAILURE;
	}

	// Destroy the socket created by socket().
	if (closesocket(sock) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("releasetcpcli error (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			"closesocket failed. ", 
			(int)sock));
		return EXIT_FAILURE;
	}

#ifdef _WIN32
	// Terminate use of the Winsock 2 DLL (WS2_32.dll).
	if (WSACleanup() != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("releasetcpcli error (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			"WSACleanup failed. ", 
			(int)sock));
		return EXIT_FAILURE;
	}
#endif // _WIN32

	return EXIT_SUCCESS;
}

/*
Connect to an IPv4 UDP server.

SOCKET* pSock : (INOUT) Valid pointer to a socket that will be used to communicate with the server.
char* address : (IN) IPv4 address of the server.
char* port : (IN) UDP port of the server.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int initudpcli(SOCKET* pSock, char* address, char* port)
{
	struct sockaddr_in sa;

#ifdef _WIN32
	WSADATA wsaData;
#endif // _WIN32

#ifdef _WIN32
	// Initiate use of the Winsock 2 DLL (WS2_32.dll) by a process.
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("initudpcli error (%s) : %s(address=%s, port=%s)\n", 
			strtime_m(), 
			"WSAStartup failed. ", 
			address, port));
		return EXIT_FAILURE;
	}
#endif // _WIN32

	// Create a UDP IPv4 socket.
	*pSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (*pSock == INVALID_SOCKET)
	{
		PRINT_DEBUG_ERROR_OSNET(("initudpcli error (%s) : %s(address=%s, port=%s)\n", 
			strtime_m(), 
			"socket failed. ", 
			address, port));
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32
		return EXIT_FAILURE;
	}

	// Configure timeouts for send and recv.
	if (setsockettimeouts(*pSock, DEFAULT_SOCK_TIMEOUT) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("initudpcli error (%s) : %s(address=%s, port=%s)\n", 
			strtime_m(), 
			"setsockettimeouts failed. ", 
			address, port));
		closesocket(*pSock);
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32
		return EXIT_FAILURE;
	}

	memset(&sa, 0, sizeof(sa));

	// The sockaddr_in structure specifies the address family,
	// IP address, and port of the server to be connected to.
	sa.sin_family = AF_INET;
	sa.sin_port = htons((unsigned short)atoi(port));
	sa.sin_addr.s_addr = inet_addr(address);

//	// Associate the client to the desired address and port.
//	if (bind(*pSock, (struct sockaddr*)&sa, sizeof(sa)) != EXIT_SUCCESS)
//	{
//		PRINT_DEBUG_ERROR_OSNET(("initudpcli error (%s) : %s(address=%s, port=%s)\n", 
//			strtime_m(), 
//			"bind failed. ", 
//			address, port));
//		closesocket(*pSock);
//#ifdef _WIN32
//		WSACleanup();
//#endif // _WIN32
//		return EXIT_FAILURE;
//	}

	// Connect to server.
	if (connect(*pSock, (struct sockaddr*)&sa, sizeof(sa)) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("initudpcli error (%s) : %s(address=%s, port=%s)\n", 
			strtime_m(), 
			"connect failed. ", 
			address, port));
		closesocket(*pSock);
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/*
Disconnect from an IPv4 UDP server.

SOCKET sock : (IN) Socket used to communicate with the server.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int releaseudpcli(SOCKET sock)
{
	// Shutdown the connection.
	if (shutdown(sock, SD_BOTH) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_WARNING_OSNET(("releaseudpcli warning (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			"shutdown failed. ", 
			(int)sock));
		//return EXIT_FAILURE;
	}

	// Destroy the socket created by socket().
	if (closesocket(sock) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("releaseudpcli error (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			"closesocket failed. ", 
			(int)sock));
		return EXIT_FAILURE;
	}

#ifdef _WIN32
	// Terminate use of the Winsock 2 DLL (WS2_32.dll).
	if (WSACleanup() != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("releaseudpcli error (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			"WSACleanup failed. ", 
			(int)sock));
		return EXIT_FAILURE;
	}
#endif // _WIN32

	return EXIT_SUCCESS;
}

/*
Create an IPv4 TCP server.

SOCKET* pSock : (INOUT) Valid pointer to a server socket.
char* address : (IN) IPv4 address of the server. Set to "0.0.0.0" to use all local 
network interfaces.
char* port : (IN) TCP port of the server.
int maxnbcli : (IN) Maximum number of simultaneous client connections. Set to 1 if there 
should be only 1 simultaneous client or to SOMAXCONN for a default maximum reasonable value.
int timeout : (IN) Timeout in ms for send and recv (0 to disable timeouts).

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int inittcpsrv(SOCKET* pSock, char* address, char* port, int maxnbcli, int timeout)
{
	struct sockaddr_in sa;

#ifdef _WIN32
	WSADATA wsaData;
#endif // _WIN32

#ifdef _WIN32
	// Initiate use of the Winsock 2 DLL (WS2_32.dll) by a process.
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("inittcpsrv error (%s) : %s(address=%s, port=%s, maxnbcli=%d, timeout=%d)\n", 
			strtime_m(), 
			"WSAStartup failed. ", 
			address, port, maxnbcli, timeout));
		return EXIT_FAILURE;
	}
#endif // _WIN32

	// Create a TCP IPv4 socket.
	*pSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*pSock == INVALID_SOCKET)
	{
		PRINT_DEBUG_ERROR_OSNET(("inittcpsrv error (%s) : %s(address=%s, port=%s, maxnbcli=%d, timeout=%d)\n", 
			strtime_m(), 
			"socket failed. ", 
			address, port, maxnbcli, timeout));
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32
		return EXIT_FAILURE;
	}

	// Configure timeouts for send and recv.
	if (setsockettimeouts(*pSock, timeout) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("inittcpsrv error (%s) : %s(address=%s, port=%s, maxnbcli=%d, timeout=%d)\n", 
			strtime_m(), 
			"setsockettimeouts failed. ", 
			address, port, maxnbcli, timeout));
		closesocket(*pSock);
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32
		return EXIT_FAILURE;
	}

#ifndef DISABLE_TCPSERVER_SO_REUSEADDR
	// Enable immediate reuse of the address and port.
	if (setsocketreuseaddr(*pSock, TRUE) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("inittcpsrv error (%s) : %s(address=%s, port=%s, maxnbcli=%d, timeout=%d)\n",
			strtime_m(),
			"setsocketreuseaddr failed. ",
			address, port, maxnbcli, timeout));
		closesocket(*pSock);
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32
		return EXIT_FAILURE;
	}
#endif // DISABLE_TCPSERVER_SO_REUSEADDR

	memset(&sa, 0, sizeof(sa));

	// The sockaddr_in structure specifies the address family,
	// IP address, and port of the server.
	sa.sin_family = AF_INET;
	sa.sin_port = htons((unsigned short)atoi(port));
	sa.sin_addr.s_addr = inet_addr(address);

	// Associate the server to the desired address and port.
	if (bind(*pSock, (struct sockaddr*)&sa, sizeof(sa)) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("inittcpsrv error (%s) : %s(address=%s, port=%s, maxnbcli=%d, timeout=%d)\n", 
			strtime_m(), 
			"bind failed. ", 
			address, port, maxnbcli, timeout));
		closesocket(*pSock);
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32
		return EXIT_FAILURE;
	}

	// Set the number of simultaneous client connections that can be accepted by the server.
	if (listen(*pSock, maxnbcli) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("inittcpsrv error (%s) : %s(address=%s, port=%s, maxnbcli=%d, timeout=%d)\n", 
			strtime_m(), 
			"listen failed. ", 
			address, port, maxnbcli, timeout));
		closesocket(*pSock);
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/*
Stop an IPv4 TCP server.

SOCKET sock : (IN) Server socket.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int releasetcpsrv(SOCKET sock)
{
	// Shutdown the connection.
	if (shutdown(sock, SD_BOTH) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_WARNING_OSNET(("releasetcpsrv warning (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			"shutdown failed. ", 
			(int)sock));
		//return EXIT_FAILURE;
	}

	// Destroy the socket created by socket().
	if (closesocket(sock) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("releasetcpsrv error (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			"closesocket failed. ", 
			(int)sock));
		return EXIT_FAILURE;
	}

#ifdef _WIN32
	// Terminate use of the Winsock 2 DLL (WS2_32.dll).
	if (WSACleanup() != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("releasetcpsrv error (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			"WSACleanup failed. ", 
			(int)sock));
		return EXIT_FAILURE;
	}
#endif // _WIN32

	return EXIT_SUCCESS;
}

/*
Create an IPv4 UDP server.

SOCKET* pSock : (INOUT) Valid pointer to a server socket.
char* address : (IN) IPv4 address of the server. Set to "0.0.0.0" to use all local 
network interfaces.
char* port : (IN) UDP port of the server.
int timeout : (IN) Timeout in ms for send and recv (0 to disable timeouts).

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int initudpsrv(SOCKET* pSock, char* address, char* port, int timeout)
{
	struct sockaddr_in sa;

#ifdef _WIN32
	WSADATA wsaData;
#endif // _WIN32

#ifdef _WIN32
	// Initiate use of the Winsock 2 DLL (WS2_32.dll) by a process.
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("initudpsrv error (%s) : %s(address=%s, port=%s, timeout=%d)\n", 
			strtime_m(), 
			"WSAStartup failed. ", 
			address, port, timeout));
		return EXIT_FAILURE;
	}
#endif // _WIN32

	// Create a UDP IPv4 socket.
	*pSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (*pSock == INVALID_SOCKET)
	{
		PRINT_DEBUG_ERROR_OSNET(("initudpsrv error (%s) : %s(address=%s, port=%s, timeout=%d)\n", 
			strtime_m(), 
			"socket failed. ", 
			address, port, timeout));
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32
		return EXIT_FAILURE;
	}

	// Configure timeouts for send and recv.
	if (setsockettimeouts(*pSock, timeout) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("initudpsrv error (%s) : %s(address=%s, port=%s, timeout=%d)\n", 
			strtime_m(), 
			"setsockettimeouts failed. ", 
			address, port, timeout));
		closesocket(*pSock);
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32
		return EXIT_FAILURE;
	}

#ifndef DISABLE_UDPSERVER_SO_REUSEADDR
	// Enable immediate reuse of the address and port.
	if (setsocketreuseaddr(*pSock, TRUE) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("initudpsrv error (%s) : %s(address=%s, port=%s, timeout=%d)\n", 
			strtime_m(), 
			"setsocketreuseaddr failed. ", 
			address, port, timeout));
		closesocket(*pSock);
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32
		return EXIT_FAILURE;
	}
#endif // DISABLE_UDPSERVER_SO_REUSEADDR

	memset(&sa, 0, sizeof(sa));

	// The sockaddr_in structure specifies the address family,
	// IP address, and port of the server.
	sa.sin_family = AF_INET;
	sa.sin_port = htons((unsigned short)atoi(port));
	sa.sin_addr.s_addr = inet_addr(address);

	// Associate the server to the desired address and port.
	if (bind(*pSock, (struct sockaddr*)&sa, sizeof(sa)) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("initudpsrv error (%s) : %s(address=%s, port=%s, timeout=%d)\n", 
			strtime_m(), 
			"bind failed. ", 
			address, port, timeout));
		closesocket(*pSock);
#ifdef _WIN32
		WSACleanup();
#endif // _WIN32
		return EXIT_FAILURE;
	}

//	// Set defaults for recv()... and send()...
//	if (connect(*pSock, (struct sockaddr*)&sa, sizeof(sa)) != EXIT_SUCCESS)
//	{
//		PRINT_DEBUG_ERROR_OSNET(("initudpsrv error (%s) : %s(address=%s, port=%s, timeout=%d)\n", 
//			strtime_m(), 
//			WSAGetLastErrorMsg(), 
//			address, port, timeout));
//		closesocket(*pSock);
//#ifdef _WIN32
//		WSACleanup();
//#endif // _WIN32
//		return EXIT_FAILURE;
//	}

	return EXIT_SUCCESS;
}

/*
Stop an IPv4 UDP server.

SOCKET sock : (IN) Server socket.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int releaseudpsrv(SOCKET sock)
{
	// Shutdown the connection.
	if (shutdown(sock, SD_BOTH) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_WARNING_OSNET(("releaseudpsrv warning (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			"shutdown failed. ", 
			(int)sock));
		//return EXIT_FAILURE;
	}

	// Destroy the socket created by socket().
	if (closesocket(sock) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("releaseudpsrv error (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			"closesocket failed. ", 
			(int)sock));
		return EXIT_FAILURE;
	}

#ifdef _WIN32
	// Terminate use of the Winsock 2 DLL (WS2_32.dll).
	if (WSACleanup() != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("releaseudpsrv error (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			"WSACleanup failed. ", 
			(int)sock));
		return EXIT_FAILURE;
	}
#endif // _WIN32

	return EXIT_SUCCESS;
}

#ifdef _MSC_VER
// Disable some Visual Studio warnings.
#pragma warning(disable : 4127) 
#endif // _MSC_VER
/*
Wait for a client for an IPv4 TCP server.

SOCKET socksrv : (IN) Server socket.
SOCKET* pSockCli : (INOUT) Valid pointer that will receive the client socket.
int timeout : (IN) Max time to wait in ms (0 to disable timeout).

Return : EXIT_SUCCESS if there is a client, EXIT_TIMEOUT if there is no client 
after the timeout elapses or EXIT_FAILURE if there is an error.
*/
inline int waitforclifortcpsrv(SOCKET socksrv, SOCKET* pSockCli, int timeout)
{
	fd_set sock_set;
	int iResult = SOCKET_ERROR;
	struct timeval tv;
	struct sockaddr_storage addr;
	socklen_t addrlen = sizeof(struct sockaddr_storage);
	char hostname[NI_MAXHOST];
	char service[NI_MAXSERV];

	tv.tv_sec = (long)(timeout/1000);
	tv.tv_usec = (long)((timeout%1000)*1000);

	*pSockCli = INVALID_SOCKET;

	// Initialize a fd_set and add the server socket to it.
	FD_ZERO(&sock_set); 
	FD_SET(socksrv, &sock_set);

	// Wait for the readability of the socket in the fd_set, with a timeout.
	if (timeout != 0)
	{
		iResult = select((int)socksrv+1, &sock_set, NULL, NULL, &tv);
	}
	else
	{
		iResult = select((int)socksrv+1, &sock_set, NULL, NULL, NULL);
	}

	// Remove the server socket from the set.
	// No need to use FD_ISSET() here, as we only have one socket the return value of select() is 
	// sufficient to know what happened.
	FD_CLR(socksrv, &sock_set); 

	if (iResult == SOCKET_ERROR)
	{
		PRINT_DEBUG_ERROR_OSNET(("waitforclifortcpsrv error (%s) : %s(socksrv=%d, timeout=%d)\n", 
			strtime_m(), 
			"select failed. ", 
			(int)socksrv, timeout));
		return EXIT_FAILURE;
	}

	if (iResult == 0)
	{ 
		PRINT_DEBUG_MESSAGE_OSNET(("waitforclifortcpsrv message (%s) : %s(socksrv=%d, timeout=%d)\n", 
			strtime_m(), 
			"select timed out. ", 
			(int)socksrv, timeout));
		return EXIT_TIMEOUT;
	}

	memset(&addr, 0, sizeof(addr));
	addrlen = sizeof(addr);
	*pSockCli = accept(socksrv, (struct sockaddr*)&addr, &addrlen);
	if (*pSockCli == INVALID_SOCKET)
	{
		PRINT_DEBUG_ERROR_OSNET(("waitforclifortcpsrv error (%s) : %s(socksrv=%d, timeout=%d)\n", 
			strtime_m(), 
			"accept failed. ", 
			(int)socksrv, timeout));
		return EXIT_FAILURE;
	}

	// Display hostname and service.
	if (getnameinfo((struct sockaddr*)&addr, addrlen, hostname, NI_MAXHOST, service,
		NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("waitforclifortcpsrv error (%s) : %s(socksrv=%d, timeout=%d)\n", 
			strtime_m(), 
			"getnameinfo failed. ", 
			(int)socksrv, timeout));
		closesocket(*pSockCli);
		return EXIT_FAILURE;
	}

	PRINT_DEBUG_MESSAGE_OSNET(("Accepted connection from host %s and port %s\n", hostname, service));

	return EXIT_SUCCESS;
}

/*
Wait for a client for an IPv4 UDP server.

SOCKET socksrv : (IN) Server socket.
SOCKET* pSockCli : (INOUT) Valid pointer that will receive the client socket.
int timeout : (IN) Max time to wait in ms (0 to disable timeout).

Return : EXIT_SUCCESS if there is a client, EXIT_TIMEOUT if there is no client 
after the timeout elapses or EXIT_FAILURE if there is an error.
*/
//inline int waitforcliforudpsrv(SOCKET socksrv, SOCKET* pSockCli, int timeout, char* firstdgram, int firstdgramlen)
inline int waitforcliforudpsrv(SOCKET socksrv, SOCKET* pSockCli, int timeout)
{
	fd_set sock_set;
	int iResult = SOCKET_ERROR;
	struct timeval tv;
	struct sockaddr_storage addr;
	socklen_t addrlen = sizeof(struct sockaddr_storage);
	char hostname[NI_MAXHOST];
	char service[NI_MAXSERV];
	char buf[65535];

	tv.tv_sec = (long)(timeout/1000);
	tv.tv_usec = (long)((timeout%1000)*1000);

	*pSockCli = INVALID_SOCKET;

	// Initialize a fd_set and add the server socket to it.
	FD_ZERO(&sock_set); 
	FD_SET(socksrv, &sock_set);

	// Wait for the readability of the socket in the fd_set, with a timeout.
	if (timeout != 0)
	{
		iResult = select((int)socksrv+1, &sock_set, NULL, NULL, &tv);
	}
	else
	{
		iResult = select((int)socksrv+1, &sock_set, NULL, NULL, NULL);
	}

	// Remove the server socket from the set.
	// No need to use FD_ISSET() here, as we only have one socket the return value of select() is 
	// sufficient to know what happened.
	FD_CLR(socksrv, &sock_set); 

	if (iResult == SOCKET_ERROR)
	{
		PRINT_DEBUG_ERROR_OSNET(("waitforcliforudpsrv error (%s) : %s(socksrv=%d, timeout=%d)\n", 
			strtime_m(), 
			"select failed. ", 
			(int)socksrv, timeout));
		return EXIT_FAILURE;
	}

	if (iResult == 0)
	{ 
		PRINT_DEBUG_MESSAGE_OSNET(("waitforcliforudpsrv message (%s) : %s(socksrv=%d, timeout=%d)\n", 
			strtime_m(), 
			"select timed out. ", 
			(int)socksrv, timeout));
		return EXIT_TIMEOUT;
	}

	// First datagram will be lost...
	memset(&addr, 0, sizeof(addr));
	addrlen = sizeof(addr);
	if (recvfrom(socksrv, buf, sizeof(buf), 0, (struct sockaddr*)&addr, (socklen_t*)&addrlen) < 0)
	{
		PRINT_DEBUG_ERROR_OSNET(("waitforcliforudpsrv error (%s) : %s(socksrv=%d, timeout=%d)\n", 
			strtime_m(), 
			WSAGetLastErrorMsg(), 
			(int)socksrv, timeout));
		return EXIT_FAILURE;
	}

	// Should create a new socket connected to that client...?

	//// Create a UDP IPv4 socket.
	//*pSockCli = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//if (*pSockCli == INVALID_SOCKET)
	//{
	//	PRINT_DEBUG_ERROR_OSNET(("waitforcliforudpsrv error (%s) : %s(socksrv=%d, timeout=%d)\n", 
	//		strtime_m(), 
	//		WSAGetLastErrorMsg(), 
	//		(int)socksrv, timeout));
	//	return EXIT_FAILURE;
	//}

	//// Configure timeouts for send and recv.
	//if (setsockettimeouts(*pSockCli, DEFAULT_SOCK_TIMEOUT) != EXIT_SUCCESS)
	//{
	//	PRINT_DEBUG_ERROR_OSNET(("waitforcliforudpsrv error (%s) : %s(socksrv=%d, timeout=%d)\n", 
	//		strtime_m(), 
	//		WSAGetLastErrorMsg(), 
	//		(int)socksrv, timeout));
	//	closesocket(*pSockCli);
	//	return EXIT_FAILURE;
	//}
	
	// Set defaults for recv()... and send()...
	//if (connect(*pSockCli, (struct sockaddr*)&addr, addrlen) != EXIT_SUCCESS)
	if (connect(socksrv, (struct sockaddr*)&addr, addrlen) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("waitforcliforudpsrv error (%s) : %s(socksrv=%d, timeout=%d)\n", 
			strtime_m(), 
			WSAGetLastErrorMsg(), 
			(int)socksrv, timeout));
		//closesocket(*pSockCli);
		return EXIT_FAILURE;
	}

	// Display hostname and service.
	if (getnameinfo((struct sockaddr*)&addr, addrlen, hostname, NI_MAXHOST, service,
		NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("waitforcliforudpsrv error (%s) : %s(socksrv=%d, timeout=%d)\n", 
			strtime_m(), 
			"getnameinfo failed. ", 
			(int)socksrv, timeout));
		//closesocket(*pSockCli);
		return EXIT_FAILURE;
	}

	PRINT_DEBUG_MESSAGE_OSNET(("Accepted connection from host %s and port %s\n", hostname, service));

	*pSockCli = socksrv;

	return EXIT_SUCCESS;
}
#ifdef _MSC_VER
// Restore the Visual Studio warnings previously disabled.
#pragma warning(default : 4127) 
#endif // _MSC_VER

/*
Disconnect a client from an IPv4 TCP server.

SOCKET sock : (IN) Client socket to disconnect from the server.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int disconnectclifromtcpsrv(SOCKET sock)
{
	// Shutdown the connection.
	if (shutdown(sock, SD_BOTH) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_WARNING_OSNET(("disconnectclifromtcpsrv warning (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			"shutdown failed. ", 
			(int)sock));
		//return EXIT_FAILURE;
	}

	// Destroy the socket created by socket().
	if (closesocket(sock) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("disconnectclifromtcpsrv error (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			"closesocket failed. ", 
			(int)sock));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/*
Disconnect a client from an IPv4 UDP server.

SOCKET sock : (IN) Client socket to disconnect from the server.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int disconnectclifromudpsrv(SOCKET sock)
{

	// Should create another socket correctly bound in waitforcliudpsrv()...?

	UNREFERENCED_PARAMETER(sock);

	//// Shutdown the connection.
	//if (shutdown(sock, SD_BOTH) != EXIT_SUCCESS)
	//{
	//	PRINT_DEBUG_WARNING_OSNET(("disconnectclifromudpsrv warning (%s) : %s(sock=%d)\n",
	//		strtime_m(),
	//		"shutdown failed. ",
	//		(int)sock));
	//	//return EXIT_FAILURE;
	//}

	//// Destroy the socket created by socket().
	//if (closesocket(sock) != EXIT_SUCCESS)
	//{
	//	PRINT_DEBUG_ERROR_OSNET(("disconnectclifromudpsrv error (%s) : %s(sock=%d)\n",
	//		strtime_m(),
	//		"closesocket failed. ",
	//		(int)sock));
	//	return EXIT_FAILURE;
	//}

	return EXIT_SUCCESS;
}

#ifdef _MSC_VER
// Disable some Visual Studio warnings.
//#pragma warning(disable : 4127) 
#pragma warning(disable : 4702) 
#endif // _MSC_VER
inline int LaunchUDPSrv(char* port, int (*handlecli)(SOCKET, void*), void* pParam)
{
	int iResult = EXIT_FAILURE;
	SOCKET socksrv = INVALID_SOCKET;
	SOCKET sockcli = INVALID_SOCKET;

	if (initudpsrv(&socksrv, "0.0.0.0", port, DEFAULT_SOCK_TIMEOUT) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	for (;;)
	{
		iResult = waitforcliforudpsrv(socksrv, &sockcli, DEFAULT_SOCK_TIMEOUT);
		switch (iResult)
		{
		case EXIT_SUCCESS:
			if (handlecli(sockcli, pParam) != EXIT_SUCCESS)
			{
				PRINT_DEBUG_WARNING_OSNET(("LaunchUDPSrv warning (%s) : %s\n", 
					strtime_m(), 
					"Error while communicating with a client. "));
			}
			if (disconnectclifromudpsrv(sockcli) != EXIT_SUCCESS)
			{
				PRINT_DEBUG_WARNING_OSNET(("LaunchUDPSrv warning (%s) : %s\n", 
					strtime_m(), 
					"Error disconnecting a client. "));
			}
			break;
		case EXIT_TIMEOUT:
			break;
		default:
			releaseudpsrv(socksrv);
			return EXIT_FAILURE;
		}
	}

	if (releaseudpsrv(socksrv) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

inline int LaunchSingleCliTCPSrv(char* port, int (*handlecli)(SOCKET, void*), void* pParam)
{
	int iResult = EXIT_FAILURE;
	SOCKET socksrv = INVALID_SOCKET;
	SOCKET sockcli = INVALID_SOCKET;

	if (inittcpsrv(&socksrv, "0.0.0.0", port, 1, DEFAULT_SOCK_TIMEOUT) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	for (;;)
	{
		iResult = waitforclifortcpsrv(socksrv, &sockcli, DEFAULT_SOCK_TIMEOUT);
		switch (iResult)
		{
		case EXIT_SUCCESS:
			if (handlecli(sockcli, pParam) != EXIT_SUCCESS)
			{
				PRINT_DEBUG_WARNING_OSNET(("LaunchSingleCliTCPSrv warning (%s) : %s\n", 
					strtime_m(), 
					"Error while communicating with a client. "));
			}
			if (disconnectclifromtcpsrv(sockcli) != EXIT_SUCCESS)
			{
				PRINT_DEBUG_WARNING_OSNET(("LaunchSingleCliTCPSrv warning (%s) : %s\n", 
					strtime_m(), 
					"Error disconnecting a client. "));
			}
			break;
		case EXIT_TIMEOUT:
			break;
		default:
			releasetcpsrv(socksrv);
			return EXIT_FAILURE;
		}
	}

	if (releasetcpsrv(socksrv) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

#ifndef DISABLE_THREADS_OSNET
struct HANDLECLITHREADPARAM
{
	int (*handlecli)(SOCKET, void*);
	SOCKET sockcli;
	void* pParam;
};
typedef struct HANDLECLITHREADPARAM HANDLECLITHREADPARAM;

EXTERN_C THREAD_PROC_RETURN_VALUE handlecliThreadProc(void* pParam);

inline int LaunchMultiCliTCPSrv(char* port, int (*handlecli)(SOCKET, void*), void* pParam)
{
	int iResult = EXIT_FAILURE;
	SOCKET socksrv = INVALID_SOCKET;
	SOCKET sockcli = INVALID_SOCKET;
	THREAD_IDENTIFIER handlecliThreadId;
	HANDLECLITHREADPARAM* pHandlecliThreadParam = NULL;

	if (inittcpsrv(&socksrv, "0.0.0.0", port, SOMAXCONN, DEFAULT_SOCK_TIMEOUT) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	for (;;)
	{
		iResult = waitforclifortcpsrv(socksrv, &sockcli, DEFAULT_SOCK_TIMEOUT);
		switch (iResult)
		{
		case EXIT_SUCCESS:		
			pHandlecliThreadParam = (HANDLECLITHREADPARAM*)calloc(1, sizeof(HANDLECLITHREADPARAM));
			if (!pHandlecliThreadParam)	
			{
				PRINT_DEBUG_WARNING_OSNET(("LaunchMultiCliTCPSrv warning (%s) : %s\n", 
					strtime_m(), 
					"Unable to handle new client. "));
				if (disconnectclifromtcpsrv(sockcli) != EXIT_SUCCESS)
				{
					PRINT_DEBUG_WARNING_OSNET(("LaunchMultiCliTCPSrv warning (%s) : %s\n", 
						strtime_m(), 
						"Error disconnecting a client. "));
				}
				break;
			}
			pHandlecliThreadParam->handlecli = handlecli;
			pHandlecliThreadParam->sockcli = sockcli;
			pHandlecliThreadParam->pParam = pParam;
			if (CreateDefaultThread(handlecliThreadProc, pHandlecliThreadParam, &handlecliThreadId) != EXIT_SUCCESS)
			{
				PRINT_DEBUG_WARNING_OSNET(("LaunchMultiCliTCPSrv warning (%s) : %s\n", 
					strtime_m(), 
					"Unable to handle new client. "));
				free(pHandlecliThreadParam);
				if (disconnectclifromtcpsrv(sockcli) != EXIT_SUCCESS)
				{
					PRINT_DEBUG_WARNING_OSNET(("LaunchMultiCliTCPSrv warning (%s) : %s\n", 
						strtime_m(), 
						"Error disconnecting a client. "));
				}
				break;
			}
			if (DetachThread(handlecliThreadId) != EXIT_SUCCESS)
			{
				PRINT_DEBUG_WARNING_OSNET(("LaunchMultiCliTCPSrv warning (%s) : %s\n", 
					strtime_m(), 
					"Error processing new client. "));
			}
			break;
		case EXIT_TIMEOUT:
			break;
		default:
			releasetcpsrv(socksrv);
			return EXIT_FAILURE;
		}
	}

	if (releasetcpsrv(socksrv) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
#endif // !DISABLE_THREADS_OSNET
#ifdef _MSC_VER
// Restore the Visual Studio warnings previously disabled.
#pragma warning(default : 4702) 
//#pragma warning(default : 4127) 
#endif // _MSC_VER

#ifndef DISABLE_IOCTLSOCKET
/*
Check for any data available to read on a socket.

SOCKET sock : (IN) Socket.

Return : EXIT_SUCCESS if there is data to read from the socket, EXIT_TIMEOUT if a timeout occurs or 
EXIT_FAILURE if there is an error.
*/
inline int checkavailablebytessocket(SOCKET sock)
{
//#ifdef _WIN32
	unsigned long bytes_avail = 0;
//#else
//	int bytes_avail = 0;
//#endif // _WIN32

	if (ioctlsocket(sock, FIONREAD, &bytes_avail) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSNET(("checkavailablebytessocket error (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			WSAGetLastErrorMsg(), 
			(int)sock));
		return EXIT_FAILURE;
	}
	if (bytes_avail <= 0) return EXIT_TIMEOUT;

	return EXIT_SUCCESS;
}
#endif // !DISABLE_IOCTLSOCKET

// The 2 following functions should be used with caution...

#ifdef _MSC_VER
// Disable some Visual Studio warnings.
#pragma warning(disable : 4127) 
#endif // _MSC_VER
/*
Wait for data to read on a socket.

SOCKET sock : (IN) Socket.
timeval timeout : (IN) Max time to wait before returning.

Return : EXIT_SUCCESS if there is data to read from the socket, EXIT_TIMEOUT if a timeout occurs or 
EXIT_FAILURE if there is an error.
*/
inline int waitforsocket(SOCKET sock, struct timeval timeout)
{
	fd_set sock_set;
	int iResult = SOCKET_ERROR;

	// Initialize a fd_set and add the socket to it.
	FD_ZERO(&sock_set); 
	FD_SET(sock, &sock_set);

	// Wait for the readability of the socket in the fd_set, with a timeout.
	iResult = select((int)sock+1, &sock_set, NULL, NULL, &timeout);

	// Remove the socket from the set.
	FD_CLR(sock, &sock_set); 

	if (iResult == SOCKET_ERROR)
	{
		PRINT_DEBUG_ERROR_OSNET(("waitforsocket error (%s) : %s(sock=%d, timeout=%d)\n", 
			strtime_m(), 
			"select failed. ", 
			(int)sock, timeout));
		return EXIT_FAILURE;
	}

	if (iResult == 0)
	{ 
		// The timeout on select() occured.
		return EXIT_TIMEOUT;
	}

	return EXIT_SUCCESS;
}

/*
Eliminate all the data coming from a socket (if any).

SOCKET sock : (IN) Socket.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int flushsocket(SOCKET sock)
{
	fd_set sock_set;
	struct timeval timeout = {0, 0}; // Timeout of 0 s for select().
	int iResult = SOCKET_ERROR;
	char recvbuf[1024];

	// Initialize a fd_set and add the socket to it.
	FD_ZERO(&sock_set); 
	FD_SET(sock, &sock_set);

	// Check the readability of the socket in the fd_set.
	iResult = select((int)sock+1, &sock_set, NULL, NULL, &timeout);

	while (iResult > 0)
	{
		// There is some data on the socket.
		if (recv(sock, recvbuf, 1024*sizeof(char), 0) <= 0)
		{
			PRINT_DEBUG_ERROR_OSNET(("flushsocket error (%s) : %s(sock=%d)\n", 
				strtime_m(), 
				"recv failed or timed out. ", 
				(int)sock));
			FD_CLR(sock, &sock_set); 
			return EXIT_FAILURE;
		}
		// Reset timeout (because a previous call to select may have modified it).
		timeout.tv_sec = 0;
		timeout.tv_usec = 0;
		// Check the readability of the socket in the fd_set.
		iResult = select((int)sock+1, &sock_set, NULL, NULL, &timeout);
	}

	// Remove the socket from the set.
	FD_CLR(sock, &sock_set); 

	if (iResult == SOCKET_ERROR)
	{
		PRINT_DEBUG_ERROR_OSNET(("flushsocket error (%s) : %s(sock=%d)\n", 
			strtime_m(), 
			"select failed. ", 
			(int)sock));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
#ifdef _MSC_VER
// Restore the Visual Studio warnings previously disabled.
#pragma warning(default : 4127) 
#endif // _MSC_VER

/*
Send data to a socket. Retry automatically if all the bytes were not sent.
Fail when a timeout occurs if it is enabled on the socket.

SOCKET sock : (IN) Socket.
char* sendbuf : (IN) Valid pointer to the data to send.
int sendbuflen : (IN) Number of bytes to send.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int sendall(SOCKET sock, char* sendbuf, int sendbuflen)
{
#ifdef _DEBUG_MESSAGES_OSNET
	int i = 0;
#endif // _DEBUG_MESSAGES_OSNET
	int BytesSent = 0;
	int Bytes = 0;

	while (BytesSent < sendbuflen)
	{
		Bytes = send(sock, sendbuf + BytesSent, sendbuflen - BytesSent, 0);
		if (Bytes >= 0)
		{
			if (Bytes == 0)
			{
				PRINT_DEBUG_WARNING_OSNET(("sendall warning (%s) : %s(sock=%d, sendbuf=%#x, sendbuflen=%d)\n", 
					strtime_m(), 
					szOSUtilsErrMsgs[EXIT_TIMEOUT], 
					(int)sock, sendbuf, sendbuflen));
#ifdef _DEBUG_MESSAGES_OSNET
				for (i = 0; i < BytesSent; i++)
				{
					PRINT_DEBUG_MESSAGE_OSNET(("%.2x ", (int)(unsigned char)sendbuf[i]));
				}
				PRINT_DEBUG_MESSAGE_OSNET(("\n"));
#endif // _DEBUG_MESSAGES_OSNET
				PRINT_DEBUG_MESSAGE_OSNET(("Total bytes sent : %d\n", BytesSent));
				return EXIT_TIMEOUT;
			}
			else
			{
				PRINT_DEBUG_MESSAGE_OSNET(("Bytes sent : %d\n", Bytes));
			}
		}
		else
		{
			PRINT_DEBUG_ERROR_OSNET(("sendall error (%s) : %s(sock=%d, sendbuf=%#x, sendbuflen=%d)\n", 
				strtime_m(), 
				WSAGetLastErrorMsg(), 
				(int)sock, sendbuf, sendbuflen));
#ifdef _DEBUG_MESSAGES_OSNET
			for (i = 0; i < BytesSent; i++)
			{
				PRINT_DEBUG_MESSAGE_OSNET(("%.2x ", (int)(unsigned char)sendbuf[i]));
			}
			PRINT_DEBUG_MESSAGE_OSNET(("\n"));
#endif // _DEBUG_MESSAGES_OSNET
			PRINT_DEBUG_MESSAGE_OSNET(("Total bytes sent : %d\n", BytesSent));
			return EXIT_FAILURE;
		}

		BytesSent += Bytes;
	}

#ifdef _DEBUG_MESSAGES_OSNET
	for (i = 0; i < BytesSent; i++)
	{
		PRINT_DEBUG_MESSAGE_OSNET(("%.2x ", (int)(unsigned char)sendbuf[i]));
	}
	PRINT_DEBUG_MESSAGE_OSNET(("\n"));
#endif // _DEBUG_MESSAGES_OSNET
	PRINT_DEBUG_MESSAGE_OSNET(("Total bytes sent : %d\n", BytesSent));

	return EXIT_SUCCESS;
}

/*
Receive data at a socket. Retry automatically if all the bytes were not received.
Fail when a timeout occurs if it is enabled on the socket.

SOCKET sock : (IN) Socket.
char* recvbuf : (INOUT) Valid pointer that will receive the data received.
int recvbuflen : (IN) Number of bytes to receive.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int recvall(SOCKET sock, char* recvbuf, int recvbuflen)
{
#ifdef _DEBUG_MESSAGES_OSNET
	int i = 0;
#endif // _DEBUG_MESSAGES_OSNET
	int BytesReceived = 0;
	int Bytes = 0;

	while (BytesReceived < recvbuflen)
	{
		Bytes = recv(sock, recvbuf + BytesReceived, recvbuflen - BytesReceived, 0);
		if (Bytes >= 0)
		{
			if (Bytes == 0)
			{
				PRINT_DEBUG_WARNING_OSNET(("recvall warning (%s) : %s(sock=%d, recvbuf=%#x, recvbuflen=%d)\n", 
					strtime_m(), 
					szOSUtilsErrMsgs[EXIT_TIMEOUT], 
					(int)sock, recvbuf, recvbuflen));
#ifdef _DEBUG_MESSAGES_OSNET
				for (i = 0; i < BytesReceived; i++)
				{
					PRINT_DEBUG_MESSAGE_OSNET(("%.2x ", (int)(unsigned char)recvbuf[i]));
				}
				PRINT_DEBUG_MESSAGE_OSNET(("\n"));
#endif // _DEBUG_MESSAGES_OSNET
				PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
				return EXIT_TIMEOUT;
			}
			else
			{
				PRINT_DEBUG_MESSAGE_OSNET(("Bytes received : %d\n", Bytes));
			}
		}
		else
		{
			PRINT_DEBUG_ERROR_OSNET(("recvall error (%s) : %s(sock=%d, recvbuf=%#x, recvbuflen=%d)\n", 
				strtime_m(), 
				WSAGetLastErrorMsg(), 
				(int)sock, recvbuf, recvbuflen));
#ifdef _DEBUG_MESSAGES_OSNET
			for (i = 0; i < BytesReceived; i++)
			{
				PRINT_DEBUG_MESSAGE_OSNET(("%.2x ", (int)(unsigned char)recvbuf[i]));
			}
			PRINT_DEBUG_MESSAGE_OSNET(("\n"));
#endif // _DEBUG_MESSAGES_OSNET
			PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
			return EXIT_FAILURE;
		}

		BytesReceived += Bytes;
	}

#ifdef _DEBUG_MESSAGES_OSNET
	for (i = 0; i < BytesReceived; i++)
	{
		PRINT_DEBUG_MESSAGE_OSNET(("%.2x ", (int)(unsigned char)recvbuf[i]));
	}
	PRINT_DEBUG_MESSAGE_OSNET(("\n"));
#endif // _DEBUG_MESSAGES_OSNET
	PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));

	return EXIT_SUCCESS;
}

inline int sendtoall(SOCKET sock, char* sendbuf, int sendbuflen, struct sockaddr* sa, int salen)
{
#ifdef _DEBUG_MESSAGES_OSNET
	int i = 0;
#endif // _DEBUG_MESSAGES_OSNET
	int BytesSent = 0;
	int Bytes = 0;

	while (BytesSent < sendbuflen)
	{
		Bytes = sendto(sock, sendbuf + BytesSent, sendbuflen - BytesSent, 0, sa, salen);
		if (Bytes >= 0)
		{
			if (Bytes == 0)
			{
				PRINT_DEBUG_WARNING_OSNET(("sendtoall warning (%s) : %s(sock=%d, sendbuf=%#x, sendbuflen=%d, sa=%#x, salen=%d)\n", 
					strtime_m(), 
					szOSUtilsErrMsgs[EXIT_TIMEOUT], 
					(int)sock, sendbuf, sendbuflen, sa, salen));
#ifdef _DEBUG_MESSAGES_OSNET
				for (i = 0; i < BytesSent; i++)
				{
					PRINT_DEBUG_MESSAGE_OSNET(("%.2x ", (int)(unsigned char)sendbuf[i]));
				}
				PRINT_DEBUG_MESSAGE_OSNET(("\n"));
#endif // _DEBUG_MESSAGES_OSNET
				PRINT_DEBUG_MESSAGE_OSNET(("Total bytes sent : %d\n", BytesSent));
				return EXIT_TIMEOUT;
			}
			else
			{
				PRINT_DEBUG_MESSAGE_OSNET(("Bytes sent : %d\n", Bytes));
			}
		}
		else
		{
			PRINT_DEBUG_ERROR_OSNET(("sendtoall error (%s) : %s(sock=%d, sendbuf=%#x, sendbuflen=%d, sa=%#x, salen=%d)\n", 
				strtime_m(), 
				WSAGetLastErrorMsg(), 
				(int)sock, sendbuf, sendbuflen, sa, salen));
#ifdef _DEBUG_MESSAGES_OSNET
			for (i = 0; i < BytesSent; i++)
			{
				PRINT_DEBUG_MESSAGE_OSNET(("%.2x ", (int)(unsigned char)sendbuf[i]));
			}
			PRINT_DEBUG_MESSAGE_OSNET(("\n"));
#endif // _DEBUG_MESSAGES_OSNET
			PRINT_DEBUG_MESSAGE_OSNET(("Total bytes sent : %d\n", BytesSent));
			return EXIT_FAILURE;
		}

		BytesSent += Bytes;
	}

#ifdef _DEBUG_MESSAGES_OSNET
	for (i = 0; i < BytesSent; i++)
	{
		PRINT_DEBUG_MESSAGE_OSNET(("%.2x ", (int)(unsigned char)sendbuf[i]));
	}
	PRINT_DEBUG_MESSAGE_OSNET(("\n"));
#endif // _DEBUG_MESSAGES_OSNET
	PRINT_DEBUG_MESSAGE_OSNET(("Total bytes sent : %d\n", BytesSent));

	return EXIT_SUCCESS;
}

inline int recvfromall(SOCKET sock, char* recvbuf, int recvbuflen, struct sockaddr* sa, int* pSalen)
{
#ifdef _DEBUG_MESSAGES_OSNET
	int i = 0;
#endif // _DEBUG_MESSAGES_OSNET
	int BytesReceived = 0;
	int Bytes = 0;

	while (BytesReceived < recvbuflen)
	{
		Bytes = recvfrom(sock, recvbuf + BytesReceived, recvbuflen - BytesReceived, 0, sa, (socklen_t*)pSalen);
		if (Bytes >= 0)
		{
			if (Bytes == 0)
			{
				PRINT_DEBUG_WARNING_OSNET(("recvfromall warning (%s) : %s(sock=%d, recvbuf=%#x, recvbuflen=%d)\n", 
					strtime_m(), 
					szOSUtilsErrMsgs[EXIT_TIMEOUT], 
					(int)sock, recvbuf, recvbuflen));
#ifdef _DEBUG_MESSAGES_OSNET
				for (i = 0; i < BytesReceived; i++)
				{
					PRINT_DEBUG_MESSAGE_OSNET(("%.2x ", (int)(unsigned char)recvbuf[i]));
				}
				PRINT_DEBUG_MESSAGE_OSNET(("\n"));
#endif // _DEBUG_MESSAGES_OSNET
				PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
				return EXIT_TIMEOUT;
			}
			else
			{
				PRINT_DEBUG_MESSAGE_OSNET(("Bytes received : %d\n", Bytes));
			}
		}
		else
		{
			PRINT_DEBUG_ERROR_OSNET(("recvfromall error (%s) : %s(sock=%d, recvbuf=%#x, recvbuflen=%d)\n", 
				strtime_m(), 
				WSAGetLastErrorMsg(), 
				(int)sock, recvbuf, recvbuflen));
#ifdef _DEBUG_MESSAGES_OSNET
			for (i = 0; i < BytesReceived; i++)
			{
				PRINT_DEBUG_MESSAGE_OSNET(("%.2x ", (int)(unsigned char)recvbuf[i]));
			}
			PRINT_DEBUG_MESSAGE_OSNET(("\n"));
#endif // _DEBUG_MESSAGES_OSNET
			PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
			return EXIT_FAILURE;
		}

		BytesReceived += Bytes;
	}

#ifdef _DEBUG_MESSAGES_OSNET
	for (i = 0; i < BytesReceived; i++)
	{
		PRINT_DEBUG_MESSAGE_OSNET(("%.2x ", (int)(unsigned char)recvbuf[i]));
	}
	PRINT_DEBUG_MESSAGE_OSNET(("\n"));
#endif // _DEBUG_MESSAGES_OSNET
	PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));

	return EXIT_SUCCESS;
}

inline int recvlatest(SOCKET sock, char* recvbuf, int recvbuflen)
{
	int BytesReceived = 0;
	int Bytes = 0;
	char* savebuf = NULL;

	savebuf = (char*)calloc(recvbuflen, sizeof(char));

	if (savebuf == NULL)
	{
		PRINT_DEBUG_ERROR_OSNET(("recvlatest error (%s) : %s(sock=%d, recvbuf=%#x, recvbuflen=%d)\n", 
			strtime_m(), 
			szOSUtilsErrMsgs[EXIT_OUT_OF_MEMORY], 
			(int)sock, recvbuf, recvbuflen));
		return EXIT_OUT_OF_MEMORY;
	}

	Bytes = recv(sock, recvbuf, recvbuflen, 0);
	if (Bytes >= 0)
	{
		if (Bytes == 0)
		{
			PRINT_DEBUG_WARNING_OSNET(("recvlatest warning (%s) : %s(sock=%d, recvbuf=%#x, recvbuflen=%d)\n", 
				strtime_m(), 
				szOSUtilsErrMsgs[EXIT_TIMEOUT], 
				(int)sock, recvbuf, recvbuflen));
			free(savebuf);
			return EXIT_TIMEOUT;
		}
		else
		{

		}
	}
	else
	{
		PRINT_DEBUG_ERROR_OSNET(("recvlatest error (%s) : %s(sock=%d, recvbuf=%#x, recvbuflen=%d)\n", 
			strtime_m(), 
			WSAGetLastErrorMsg(), 
			(int)sock, recvbuf, recvbuflen));
		free(savebuf);
		return EXIT_FAILURE;
	}

	BytesReceived += Bytes;

	while (Bytes == recvbuflen)
	{
		memcpy(savebuf, recvbuf, Bytes);
		Bytes = recv(sock, recvbuf, recvbuflen, 0);
		if (Bytes >= 0)
		{
			if (Bytes == 0)
			{
				PRINT_DEBUG_WARNING_OSNET(("recvlatest warning (%s) : %s(sock=%d, recvbuf=%#x, recvbuflen=%d)\n", 
					strtime_m(), 
					szOSUtilsErrMsgs[EXIT_TIMEOUT], 
					(int)sock, recvbuf, recvbuflen));
				free(savebuf);
				return EXIT_TIMEOUT;
			}
			else
			{

			}
		}
		else
		{
			PRINT_DEBUG_ERROR_OSNET(("recvlatest error (%s) : %s(sock=%d, recvbuf=%#x, recvbuflen=%d)\n", 
				strtime_m(), 
				WSAGetLastErrorMsg(), 
				(int)sock, recvbuf, recvbuflen));
			free(savebuf);
			return EXIT_FAILURE;
		}

		BytesReceived += Bytes;
	}

	if (BytesReceived < recvbuflen)
	{
		int iResult = recvall(sock, recvbuf+BytesReceived, recvbuflen-BytesReceived);
		if (iResult != EXIT_SUCCESS)
		{
			free(savebuf);
			return iResult;
		}
	}
	else
	{
		memmove(recvbuf+recvbuflen-Bytes, recvbuf, Bytes);
		memcpy(recvbuf, savebuf+Bytes, recvbuflen-Bytes);
	}

	free(savebuf);

	return EXIT_SUCCESS;
}

/*
Receive data at a socket until a specific end string is received.
If this string is found (and the maximum number of bytes to receive has not 
been reached), it is not necessarily the last received bytes in the buffer 
(other bytes might have been received after).
Fail when a timeout occurs if it is enabled on the socket.

SOCKET sock : (IN) Socket.
char* recvbuf : (INOUT) Valid pointer that will receive the data received 
(should be null-terminated, but the search does not include terminating null characters).
char* endstr : (IN) End string to wait for (should be null-terminated, but 
the search does not include terminating null characters).
int maxrecvbuflen : (IN) Maximum number of bytes to receive.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int recvatleastuntilstr(SOCKET sock, char* recvbuf, char* endstr, int maxrecvbuflen)
{
	int BytesReceived = 0;
	int Bytes = 0;

	for (;;)
	{
		if (BytesReceived >= maxrecvbuflen)
		{
			PRINT_DEBUG_ERROR_OSNET(("recvatleastuntil error (%s) : %s(sock=%d, recvbuf=%#x, endstr=%s, maxrecvbuflen=%d)\n", 
				strtime_m(), 
				"recvbuf full. ", 
				(int)sock, recvbuf, endstr, maxrecvbuflen));
			PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
			return EXIT_OUT_OF_MEMORY;
		}

		Bytes = recv(sock, recvbuf + BytesReceived, maxrecvbuflen - BytesReceived, 0);
		if (Bytes >= 0)
		{
			if (Bytes == 0)
			{
				PRINT_DEBUG_WARNING_OSNET(("recvatleastuntil warning (%s) : %s(sock=%d, recvbuf=%#x, endstr=%s, maxrecvbuflen=%d)\n", 
					strtime_m(), 
					szOSUtilsErrMsgs[EXIT_TIMEOUT], 
					(int)sock, recvbuf, endstr, maxrecvbuflen));
				PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
				return EXIT_TIMEOUT;
			}
			else
			{
				PRINT_DEBUG_MESSAGE_OSNET(("Bytes received : %d\n", Bytes));

				// Look for endstr in the bytes received.
				if (strstr(recvbuf, endstr))
				{
					break;
				}
			}
		}
		else
		{
			PRINT_DEBUG_ERROR_OSNET(("recvatleastuntil error (%s) : %s(sock=%d, recvbuf=%#x, endstr=%s, maxrecvbuflen=%d)\n", 
				strtime_m(), 
				WSAGetLastErrorMsg(), 
				(int)sock, recvbuf, endstr, maxrecvbuflen));
			PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
			return EXIT_FAILURE;
		}

		BytesReceived += Bytes;
	}

	PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));

	return EXIT_SUCCESS;
}

/*
Receive data at a socket until a specific end character is received.
If this character is found (and the maximum number of bytes to receive has not 
been reached), it is not necessarily the last received byte in the buffer 
(other bytes might have been received after).
Fail when a timeout occurs if it is enabled on the socket.

SOCKET sock : (IN) Socket.
char* recvbuf : (INOUT) Valid pointer that will receive the data received.
char endchar : (IN) End character to wait for.
int maxrecvbuflen : (IN) Maximum number of bytes to receive.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int recvatleastuntil(SOCKET sock, char* recvbuf, char endchar, int maxrecvbuflen)
{
	int BytesReceived = 0;
	int Bytes = 0;
	int bStop = 0;

	for (;;)
	{
		if (BytesReceived >= maxrecvbuflen)
		{
			PRINT_DEBUG_ERROR_OSNET(("recvatleastuntil error (%s) : %s(sock=%d, recvbuf=%#x, endchar=%.2x, maxrecvbuflen=%d)\n", 
				strtime_m(), 
				"recvbuf full. ", 
				(int)sock, recvbuf, (int)(unsigned char)endchar, maxrecvbuflen));
			PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
			return EXIT_OUT_OF_MEMORY;
		}

		Bytes = recv(sock, recvbuf + BytesReceived, maxrecvbuflen - BytesReceived, 0);
		if (Bytes >= 0)
		{
			if (Bytes == 0)
			{
				PRINT_DEBUG_WARNING_OSNET(("recvatleastuntil warning (%s) : %s(sock=%d, recvbuf=%#x, endchar=%.2x, maxrecvbuflen=%d)\n", 
					strtime_m(), 
					szOSUtilsErrMsgs[EXIT_TIMEOUT], 
					(int)sock, recvbuf, (int)(unsigned char)endchar, maxrecvbuflen));
				PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
				return EXIT_TIMEOUT;
			}
			else
			{
				int i = 0;

				PRINT_DEBUG_MESSAGE_OSNET(("Bytes received : %d\n", Bytes));

				// Look for endchar in the bytes just received.
				for (i = BytesReceived; i < BytesReceived+Bytes; i++)
				{
					if (recvbuf[i] == endchar)
					{
						bStop = 1;
						break;
					}
				}

				if (bStop)
				{
					break;
				}
			}
		}
		else
		{
			PRINT_DEBUG_ERROR_OSNET(("recvatleastuntil error (%s) : %s(sock=%d, recvbuf=%#x, endchar=%.2x, maxrecvbuflen=%d)\n", 
				strtime_m(), 
				WSAGetLastErrorMsg(), 
				(int)sock, recvbuf, (int)(unsigned char)endchar, maxrecvbuflen));
			PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
			return EXIT_FAILURE;
		}

		BytesReceived += Bytes;
	}

	PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));

	return EXIT_SUCCESS;
}

/*
Receive data at a socket until a specific end character is received.
If this character is found (and the maximum number of bytes to receive has not 
been reached), it is the last received byte in the buffer.
This function might take more network load than recvatleastuntil() but guarantees
that no bytes are received after the end character (the bytes that might be between 
the end character and the maximum number of bytes to receive are left unchanged).
Fail when a timeout occurs if it is enabled on the socket.

SOCKET sock : (IN) Socket.
char* recvbuf : (INOUT) Valid pointer that will receive the data received.
char endchar : (IN) End character to wait for.
int maxrecvbuflen : (IN) Maximum number of bytes to receive.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int recvuntil(SOCKET sock, char* recvbuf, char endchar, int maxrecvbuflen)
{
	int BytesReceived = 0;
	int Bytes = 0;

	// Receive byte per byte.
	while ((BytesReceived <= 0)||(recvbuf[BytesReceived-1] != endchar))
	{
		if (BytesReceived >= maxrecvbuflen)
		{
			PRINT_DEBUG_ERROR_OSNET(("recvuntil error (%s) : %s(sock=%d, recvbuf=%#x, endchar=%.2x, maxrecvbuflen=%d)\n", 
				strtime_m(), 
				"recvbuf full. ", 
				(int)sock, recvbuf, (int)(unsigned char)endchar, maxrecvbuflen));
			PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
			return EXIT_OUT_OF_MEMORY;
		}

		// Receive 1 byte.
		Bytes = recv(sock, recvbuf + BytesReceived, 1, 0);
		if (Bytes >= 0)
		{
			if (Bytes == 0)
			{
				PRINT_DEBUG_WARNING_OSNET(("recvuntil warning (%s) : %s(sock=%d, recvbuf=%#x, endchar=%.2x, maxrecvbuflen=%d)\n", 
					strtime_m(), 
					szOSUtilsErrMsgs[EXIT_TIMEOUT], 
					(int)sock, recvbuf, (int)(unsigned char)endchar, maxrecvbuflen));
				PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
				return EXIT_TIMEOUT;
			}
			else
			{
				PRINT_DEBUG_MESSAGE_OSNET(("Bytes received : %d\n", Bytes));
			}
		}
		else
		{
			PRINT_DEBUG_ERROR_OSNET(("recvuntil error (%s) : %s(sock=%d, recvbuf=%#x, endchar=%.2x, maxrecvbuflen=%d)\n", 
				strtime_m(), 
				WSAGetLastErrorMsg(), 
				(int)sock, recvbuf, (int)(unsigned char)endchar, maxrecvbuflen));
			PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
			return EXIT_FAILURE;
		}

		BytesReceived += Bytes;
	}

	PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));

	//*pBytesReceived = BytesReceived;

	return EXIT_SUCCESS;
}

inline int recvuntilstr(SOCKET sock, char* recvbuf, char* endstr, int maxrecvbuflen, int* pBytesReceived)
{
	int BytesReceived = 0;
	int Bytes = 0;

	// Receive byte per byte.
	while ((BytesReceived <= 0)||(strstr(recvbuf, endstr) == NULL))
	{
		if (BytesReceived >= maxrecvbuflen)
		{
			PRINT_DEBUG_ERROR_OSNET(("recvuntilstr error (%s) : %s(sock=%d, recvbuf=%#x, endstr=%s, maxrecvbuflen=%d)\n", 
				strtime_m(), 
				"recvbuf full. ", 
				(int)sock, recvbuf, endstr, maxrecvbuflen));
			PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
			*pBytesReceived = BytesReceived;
			return EXIT_OUT_OF_MEMORY;
		}

		// Receive 1 byte.
		Bytes = recv(sock, recvbuf + BytesReceived, 1, 0);
		if (Bytes >= 0)
		{
			if (Bytes == 0)
			{
				PRINT_DEBUG_WARNING_OSNET(("recvuntilstr warning (%s) : %s(sock=%d, recvbuf=%#x, endstr=%s, maxrecvbuflen=%d)\n", 
					strtime_m(), 
					szOSUtilsErrMsgs[EXIT_TIMEOUT], 
					(int)sock, recvbuf, endstr, maxrecvbuflen));
				PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
				*pBytesReceived = BytesReceived;
				return EXIT_TIMEOUT;
			}
			else
			{
				PRINT_DEBUG_MESSAGE_OSNET(("Bytes received : %d\n", Bytes));
			}
		}
		else
		{
			PRINT_DEBUG_ERROR_OSNET(("recvuntilstr error (%s) : %s(sock=%d, recvbuf=%#x, endstr=%s, maxrecvbuflen=%d)\n", 
				strtime_m(), 
				WSAGetLastErrorMsg(), 
				(int)sock, recvbuf, endstr, maxrecvbuflen));
			PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));
			*pBytesReceived = BytesReceived;
			return EXIT_FAILURE;
		}

		BytesReceived += Bytes;
	}

	PRINT_DEBUG_MESSAGE_OSNET(("Total bytes received : %d\n", BytesReceived));

	*pBytesReceived = BytesReceived;

	return EXIT_SUCCESS;
}

#endif // !OSNET_H
