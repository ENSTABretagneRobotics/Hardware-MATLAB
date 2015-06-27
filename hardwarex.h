#ifndef HARDWAREX_H
#define HARDWAREX_H

#ifdef _WIN32
#ifdef HARDWAREX_EXPORTS
#define HARDWAREX_API __declspec(dllexport) 
#else
#define HARDWAREX_API __declspec(dllimport) 
#endif // HARDWAREX_EXPORTS
#else
#define HARDWAREX_API 
#endif // _WIN32

//#ifndef DISABLE_THREADS_OSNET
//#define DISABLE_THREADS_OSNET
//#endif // DISABLE_THREADS_OSNET

#include "OSCriticalSection.h"
#include "Hokuyo.h"

#ifdef __cplusplus
extern "C" {
#endif

	HARDWAREX_API HOKUYO* CreateHokuyox(void);
	HARDWAREX_API void DestroyHokuyox(HOKUYO* pHokuyo);
	HARDWAREX_API double k2angleHokuyox(HOKUYO* pHokuyo, int k);
	HARDWAREX_API int angle2kHokuyox(HOKUYO* pHokuyo, double angle);
	HARDWAREX_API int GetLatestDataHokuyox(HOKUYO* pHokuyo, double* pDistances, double* pAngles);
	HARDWAREX_API int ConnectHokuyox(HOKUYO* pHokuyo, char* szCfgFilePath);
	HARDWAREX_API int DisconnectHokuyox(HOKUYO* pHokuyo);
	HARDWAREX_API int GetLatestDataFromThreadHokuyox(HOKUYO* pHokuyo, double* pDistances, double* pAngles);
	HARDWAREX_API int StartThreadHokuyox(HOKUYO* pHokuyo);
	HARDWAREX_API int StopThreadHokuyox(HOKUYO* pHokuyo);

#ifdef __cplusplus
}
#endif

#endif // HARDWAREX_H
