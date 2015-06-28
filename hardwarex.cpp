#include "hardwarex.h"

THREAD_IDENTIFIER NMEADeviceThreadId;
CRITICAL_SECTION NMEADeviceCS;
NMEADATA nmeadataNMEADevice;
BOOL bExitNMEADevice = FALSE;

THREAD_IDENTIFIER HokuyoThreadId;
CRITICAL_SECTION HokuyoCS;
double anglesHokuyo[MAX_SLITDIVISION_HOKUYO];
double distancesHokuyo[MAX_SLITDIVISION_HOKUYO];
BOOL bExitHokuyo = FALSE;

HARDWAREX_API NMEADEVICE* CreateNMEADevicex(void)
{
	return (NMEADEVICE*)calloc(1, sizeof(NMEADEVICE));
}

HARDWAREX_API void DestroyNMEADevicex(NMEADEVICE* pNMEADevice)
{
	return free(pNMEADevice);
}

HARDWAREX_API NMEADATA* CreateNMEADatax(void)
{
	return (NMEADATA*)calloc(1, sizeof(NMEADATA));
}

HARDWAREX_API void DestroyNMEADatax(NMEADATA* pNMEAData)
{
	return free(pNMEAData);
}

HARDWAREX_API int GetLatestDataNMEADevicex(NMEADEVICE* pNMEADevice, NMEADATA* pNMEAData)
{
	return GetLatestDataNMEADevice(pNMEADevice, pNMEAData);
}

HARDWAREX_API int ConnectNMEADevicex(NMEADEVICE* pNMEADevice, char* szCfgFilePath)
{
	return ConnectNMEADevice(pNMEADevice, szCfgFilePath);
}

HARDWAREX_API int DisconnectNMEADevicex(NMEADEVICE* pNMEADevice)
{
	return DisconnectNMEADevice(pNMEADevice);
}

THREAD_PROC_RETURN_VALUE NMEADeviceThread(void* pParam)
{
	NMEADATA nmeadata;
	NMEADEVICE* pNMEADevice = (NMEADEVICE*)pParam;

	for (;;)
	{
		mSleep(100);
		memset(&nmeadata, 0, sizeof(NMEADATA));
		GetLatestDataNMEADevice(pNMEADevice, &nmeadata);
		EnterCriticalSection(&NMEADeviceCS);
		nmeadataNMEADevice = nmeadata;
		LeaveCriticalSection(&NMEADeviceCS);
		if (bExitNMEADevice) break;
	}

	return 0;
}

HARDWAREX_API int GetLatestDataFromThreadNMEADevicex(NMEADEVICE* pNMEADevice, NMEADATA* pNMEAData)
{
	UNREFERENCED_PARAMETER(pNMEADevice);

	// id[pNMEADevice->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&NMEADeviceCS);
	*pNMEAData = nmeadataNMEADevice;
	LeaveCriticalSection(&NMEADeviceCS);

	return 0;
}

HARDWAREX_API int StartThreadNMEADevicex(NMEADEVICE* pNMEADevice)
{
	bExitNMEADevice = FALSE;
	InitCriticalSection(&NMEADeviceCS);
	return CreateDefaultThread(NMEADeviceThread, (void*)pNMEADevice, &NMEADeviceThreadId);
}

HARDWAREX_API int StopThreadNMEADevicex(NMEADEVICE* pNMEADevice)
{
	UNREFERENCED_PARAMETER(pNMEADevice);

	bExitNMEADevice = TRUE;
	WaitForThread(NMEADeviceThreadId);
	DeleteCriticalSection(&NMEADeviceCS);
	return 0;
}

HARDWAREX_API HOKUYO* CreateHokuyox(void)
{
	return (HOKUYO*)calloc(1, sizeof(HOKUYO));
}

HARDWAREX_API void DestroyHokuyox(HOKUYO* pHokuyo)
{
	return free(pHokuyo);
}

HARDWAREX_API double k2angleHokuyox(HOKUYO* pHokuyo, int k)
{
	return k2angleHokuyo(pHokuyo, k);
}

HARDWAREX_API int angle2kHokuyox(HOKUYO* pHokuyo, double angle)
{
	return angle2kHokuyo(pHokuyo, angle);
}

HARDWAREX_API int GetLatestDataHokuyox(HOKUYO* pHokuyo, double* pDistances, double* pAngles)
{
	return GetLatestDataHokuyo(pHokuyo, pDistances, pAngles);
}

HARDWAREX_API int ConnectHokuyox(HOKUYO* pHokuyo, char* szCfgFilePath)
{
	return ConnectHokuyo(pHokuyo, szCfgFilePath);
}

HARDWAREX_API int DisconnectHokuyox(HOKUYO* pHokuyo)
{
	return DisconnectHokuyo(pHokuyo);
}

THREAD_PROC_RETURN_VALUE HokuyoThread(void* pParam)
{
	double angles[MAX_SLITDIVISION_HOKUYO];
	double distances[MAX_SLITDIVISION_HOKUYO];
	HOKUYO* pHokuyo = (HOKUYO*)pParam;

	for (;;)
	{
		mSleep(50);
		memset(distances, 0, MAX_SLITDIVISION_HOKUYO*sizeof(double));
		memset(angles, 0, MAX_SLITDIVISION_HOKUYO*sizeof(double));
		GetLatestDataHokuyo(pHokuyo, distances, angles);
		EnterCriticalSection(&HokuyoCS);
		memcpy(distancesHokuyo, distances, MAX_SLITDIVISION_HOKUYO*sizeof(double));
		memcpy(anglesHokuyo, angles, MAX_SLITDIVISION_HOKUYO*sizeof(double));
		LeaveCriticalSection(&HokuyoCS);
		if (bExitHokuyo) break;
	}

	return 0;
}

HARDWAREX_API int GetLatestDataFromThreadHokuyox(HOKUYO* pHokuyo, double* pDistances, double* pAngles)
{
	UNREFERENCED_PARAMETER(pHokuyo);

	// id[pHokuyo->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&HokuyoCS);
	memcpy(pDistances, distancesHokuyo, MAX_SLITDIVISION_HOKUYO*sizeof(double));
	memcpy(pAngles, anglesHokuyo, MAX_SLITDIVISION_HOKUYO*sizeof(double));
	LeaveCriticalSection(&HokuyoCS);

	return 0;
}

HARDWAREX_API int StartThreadHokuyox(HOKUYO* pHokuyo)
{
	bExitHokuyo = FALSE;
	InitCriticalSection(&HokuyoCS);
	return CreateDefaultThread(HokuyoThread, (void*)pHokuyo, &HokuyoThreadId);
}

HARDWAREX_API int StopThreadHokuyox(HOKUYO* pHokuyo)
{
	UNREFERENCED_PARAMETER(pHokuyo);

	bExitHokuyo = TRUE;
	WaitForThread(HokuyoThreadId);
	DeleteCriticalSection(&HokuyoCS);
	return 0;
}
