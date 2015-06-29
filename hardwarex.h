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
#include "MT.h"
#include "RazorAHRS.h"
#include "NMEADevice.h"
#include "SSC32.h"
#include "Maestro.h"
#include "Hokuyo.h"

#ifdef __cplusplus
extern "C" {
#endif

	HARDWAREX_API MT* CreateMTx(void);
	HARDWAREX_API void DestroyMTx(MT* pMT);
	HARDWAREX_API MTDATA* CreateMTDatax(void);
	HARDWAREX_API void DestroyMTDatax(MTDATA* pMTData);
	HARDWAREX_API int GetLatestDataMTx(MT* pMT, MTDATA* pMTData);
	HARDWAREX_API int ConnectMTx(MT* pMT, char* szCfgFilePath);
	HARDWAREX_API int DisconnectMTx(MT* pMT);
	HARDWAREX_API int GetLatestDataFromThreadMTx(MT* pMT, MTDATA* pMTData);
	HARDWAREX_API int StartThreadMTx(MT* pMT);
	HARDWAREX_API int StopThreadMTx(MT* pMT);

	HARDWAREX_API RAZORAHRS* CreateRazorAHRSx(void);
	HARDWAREX_API void DestroyRazorAHRSx(RAZORAHRS* pRazorAHRS);
	HARDWAREX_API RAZORAHRSDATA* CreateRazorAHRSDatax(void);
	HARDWAREX_API void DestroyRazorAHRSDatax(RAZORAHRSDATA* pRazorAHRSData);
	HARDWAREX_API int GetLatestDataRazorAHRSx(RAZORAHRS* pRazorAHRS, RAZORAHRSDATA* pRazorAHRSData);
	HARDWAREX_API int ConnectRazorAHRSx(RAZORAHRS* pRazorAHRS, char* szCfgFilePath);
	HARDWAREX_API int DisconnectRazorAHRSx(RAZORAHRS* pRazorAHRS);
	HARDWAREX_API int GetLatestDataFromThreadRazorAHRSx(RAZORAHRS* pRazorAHRS, RAZORAHRSDATA* pRazorAHRSData);
	HARDWAREX_API int StartThreadRazorAHRSx(RAZORAHRS* pRazorAHRS);
	HARDWAREX_API int StopThreadRazorAHRSx(RAZORAHRS* pRazorAHRS);

	HARDWAREX_API NMEADEVICE* CreateNMEADevicex(void);
	HARDWAREX_API void DestroyNMEADevicex(NMEADEVICE* pNMEADevice);
	HARDWAREX_API NMEADATA* CreateNMEADatax(void);
	HARDWAREX_API void DestroyNMEADatax(NMEADATA* pNMEAData);
	HARDWAREX_API int GetLatestDataNMEADevicex(NMEADEVICE* pNMEADevice, NMEADATA* pNMEAData);
	HARDWAREX_API int ConnectNMEADevicex(NMEADEVICE* pNMEADevice, char* szCfgFilePath);
	HARDWAREX_API int DisconnectNMEADevicex(NMEADEVICE* pNMEADevice);
	HARDWAREX_API int GetLatestDataFromThreadNMEADevicex(NMEADEVICE* pNMEADevice, NMEADATA* pNMEAData);
	HARDWAREX_API int StartThreadNMEADevicex(NMEADEVICE* pNMEADevice);
	HARDWAREX_API int StopThreadNMEADevicex(NMEADEVICE* pNMEADevice);

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
