/***************************************************************************************************************:')

OSNet.c

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

#include "OSNet.h"

#ifndef DISABLE_THREADS_OSNET
THREAD_PROC_RETURN_VALUE handlecliThreadProc(void* pHandlecliThreadParam)
{
	int (*handlecli)(SOCKET, void*) = ((HANDLECLITHREADPARAM*)pHandlecliThreadParam)->handlecli;
	SOCKET sockcli = ((HANDLECLITHREADPARAM*)pHandlecliThreadParam)->sockcli;
	void* pParam = ((HANDLECLITHREADPARAM*)pHandlecliThreadParam)->pParam;

	if (handlecli(sockcli, pParam) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_WARNING_OSNET(("handlecliThreadProc warning (%s) : %s\n", 
			strtime_m(), 
			"Error while communicating with a client. "));
	}

	free(pHandlecliThreadParam);
	if (disconnectclifromtcpsrv(sockcli) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_WARNING_OSNET(("handlecliThreadProc warning (%s) : %s\n", 
			strtime_m(), 
			"Error disconnecting a client. "));
	}

	return 0;
}
#endif // !DISABLE_THREADS_OSNET
