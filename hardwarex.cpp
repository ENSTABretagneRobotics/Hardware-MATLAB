#include "hardwarex.h"

THREAD_IDENTIFIER MTThreadId;
CRITICAL_SECTION MTCS;
MTDATA mtdataMT;
BOOL bExitMT = FALSE;

THREAD_IDENTIFIER RazorAHRSThreadId;
CRITICAL_SECTION RazorAHRSCS;
RAZORAHRSDATA razorahrsdataRazorAHRS;
BOOL bExitRazorAHRS = FALSE;

THREAD_IDENTIFIER NMEADeviceThreadId;
CRITICAL_SECTION NMEADeviceCS;
NMEADATA nmeadataNMEADevice;
BOOL bExitNMEADevice = FALSE;

THREAD_IDENTIFIER SSC32ThreadId;
CRITICAL_SECTION SSC32CS;
int selectedchannelsSSC32[NB_CHANNELS_PWM_SSC32];
int pwsSSC32[NB_CHANNELS_PWM_SSC32];
BOOL bExitSSC32 = FALSE;

THREAD_IDENTIFIER MaestroThreadId;
CRITICAL_SECTION MaestroCS;
int selectedchannelsMaestro[NB_CHANNELS_PWM_MAESTRO];
int pwsMaestro[NB_CHANNELS_PWM_MAESTRO];
int valueMaestro = 0;
BOOL bExitMaestro = FALSE;

THREAD_IDENTIFIER HokuyoThreadId;
CRITICAL_SECTION HokuyoCS;
double anglesHokuyo[MAX_SLITDIVISION_HOKUYO];
double distancesHokuyo[MAX_SLITDIVISION_HOKUYO];
BOOL bExitHokuyo = FALSE;

#pragma region MT
HARDWAREX_API MT* CreateMTx(void)
{
	return (MT*)calloc(1, sizeof(MT));
}

HARDWAREX_API void DestroyMTx(MT* pMT)
{
	return free(pMT);
}

HARDWAREX_API MTDATA* CreateMTDatax(void)
{
	return (MTDATA*)calloc(1, sizeof(MTDATA));
}

HARDWAREX_API void DestroyMTDatax(MTDATA* pMTData)
{
	return free(pMTData);
}

HARDWAREX_API int GetLatestDataMTx(MT* pMT, MTDATA* pMTData)
{
	return GetLatestDataMT(pMT, pMTData);
}

HARDWAREX_API int ConnectMTx(MT* pMT, char* szCfgFilePath)
{
	return ConnectMT(pMT, szCfgFilePath);
}

HARDWAREX_API int DisconnectMTx(MT* pMT)
{
	return DisconnectMT(pMT);
}

THREAD_PROC_RETURN_VALUE MTThread(void* pParam)
{
	MT* pMT = (MT*)pParam;
	MTDATA mtdata;

	for (;;)
	{
		mSleep(100);
		memset(&mtdata, 0, sizeof(MTDATA));
		GetLatestDataMT(pMT, &mtdata);
		EnterCriticalSection(&MTCS);
		mtdataMT = mtdata;
		LeaveCriticalSection(&MTCS);
		if (bExitMT) break;
	}

	return 0;
}

HARDWAREX_API int GetLatestDataFromThreadMTx(MT* pMT, MTDATA* pMTData)
{
	UNREFERENCED_PARAMETER(pMT);

	// id[pMT->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&MTCS);
	*pMTData = mtdataMT;
	LeaveCriticalSection(&MTCS);

	return EXIT_SUCCESS;
}

HARDWAREX_API int StartThreadMTx(MT* pMT)
{
	bExitMT = FALSE;
	InitCriticalSection(&MTCS);
	return CreateDefaultThread(MTThread, (void*)pMT, &MTThreadId);
}

HARDWAREX_API int StopThreadMTx(MT* pMT)
{
	UNREFERENCED_PARAMETER(pMT);

	bExitMT = TRUE;
	WaitForThread(MTThreadId);
	DeleteCriticalSection(&MTCS);
	return EXIT_SUCCESS;
}
#pragma endregion

#pragma region RazorAHRS
HARDWAREX_API RAZORAHRS* CreateRazorAHRSx(void)
{
	return (RAZORAHRS*)calloc(1, sizeof(RAZORAHRS));
}

HARDWAREX_API void DestroyRazorAHRSx(RAZORAHRS* pRazorAHRS)
{
	return free(pRazorAHRS);
}

HARDWAREX_API RAZORAHRSDATA* CreateRazorAHRSDatax(void)
{
	return (RAZORAHRSDATA*)calloc(1, sizeof(RAZORAHRSDATA));
}

HARDWAREX_API void DestroyRazorAHRSDatax(RAZORAHRSDATA* pRazorAHRSData)
{
	return free(pRazorAHRSData);
}

HARDWAREX_API int GetLatestDataRazorAHRSx(RAZORAHRS* pRazorAHRS, RAZORAHRSDATA* pRazorAHRSData)
{
	return GetLatestDataRazorAHRS(pRazorAHRS, pRazorAHRSData);
}

HARDWAREX_API int ConnectRazorAHRSx(RAZORAHRS* pRazorAHRS, char* szCfgFilePath)
{
	return ConnectRazorAHRS(pRazorAHRS, szCfgFilePath);
}

HARDWAREX_API int DisconnectRazorAHRSx(RAZORAHRS* pRazorAHRS)
{
	return DisconnectRazorAHRS(pRazorAHRS);
}

THREAD_PROC_RETURN_VALUE RazorAHRSThread(void* pParam)
{
	RAZORAHRS* pRazorAHRS = (RAZORAHRS*)pParam;
	RAZORAHRSDATA razorahrsdata;

	for (;;)
	{
		mSleep(100);
		memset(&razorahrsdata, 0, sizeof(RAZORAHRSDATA));
		GetLatestDataRazorAHRS(pRazorAHRS, &razorahrsdata);
		EnterCriticalSection(&RazorAHRSCS);
		razorahrsdataRazorAHRS = razorahrsdata;
		LeaveCriticalSection(&RazorAHRSCS);
		if (bExitRazorAHRS) break;
	}

	return 0;
}

HARDWAREX_API int GetLatestDataFromThreadRazorAHRSx(RAZORAHRS* pRazorAHRS, RAZORAHRSDATA* pRazorAHRSData)
{
	UNREFERENCED_PARAMETER(pRazorAHRS);

	// id[pRazorAHRS->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&RazorAHRSCS);
	*pRazorAHRSData = razorahrsdataRazorAHRS;
	LeaveCriticalSection(&RazorAHRSCS);

	return EXIT_SUCCESS;
}

HARDWAREX_API int StartThreadRazorAHRSx(RAZORAHRS* pRazorAHRS)
{
	bExitRazorAHRS = FALSE;
	InitCriticalSection(&RazorAHRSCS);
	return CreateDefaultThread(RazorAHRSThread, (void*)pRazorAHRS, &RazorAHRSThreadId);
}

HARDWAREX_API int StopThreadRazorAHRSx(RAZORAHRS* pRazorAHRS)
{
	UNREFERENCED_PARAMETER(pRazorAHRS);

	bExitRazorAHRS = TRUE;
	WaitForThread(RazorAHRSThreadId);
	DeleteCriticalSection(&RazorAHRSCS);
	return EXIT_SUCCESS;
}
#pragma endregion

#pragma region NMEADevice
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
	NMEADEVICE* pNMEADevice = (NMEADEVICE*)pParam;
	NMEADATA nmeadata;

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

	return EXIT_SUCCESS;
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
	return EXIT_SUCCESS;
}
#pragma endregion

#pragma region SSC32
HARDWAREX_API SSC32* CreateSSC32x(void)
{
	return (SSC32*)calloc(1, sizeof(SSC32));
}

HARDWAREX_API void DestroySSC32x(SSC32* pSSC32)
{
	return free(pSSC32);
}

HARDWAREX_API int SetPWMSSC32x(SSC32* pSSC32, int channel, int pw)
{
	return SetPWMSSC32(pSSC32, channel, pw);
}

HARDWAREX_API int SetAllPWMsSSC32x(SSC32* pSSC32, int* selectedchannels, int* pws)
{
	return SetAllPWMsSSC32(pSSC32, selectedchannels, pws);
}

HARDWAREX_API int ConnectSSC32x(SSC32* pSSC32, char* szCfgFilePath)
{
	return ConnectSSC32(pSSC32, szCfgFilePath);
}

HARDWAREX_API int DisconnectSSC32x(SSC32* pSSC32)
{
	return DisconnectSSC32(pSSC32);
}

THREAD_PROC_RETURN_VALUE SSC32Thread(void* pParam)
{
	SSC32* pSSC32 = (SSC32*)pParam;
	int selectedchannels[NB_CHANNELS_PWM_SSC32];
	int pws[NB_CHANNELS_PWM_SSC32];

	for (;;)
	{
		mSleep(50);
		EnterCriticalSection(&SSC32CS);
		memcpy(selectedchannels, selectedchannelsSSC32, NB_CHANNELS_PWM_SSC32*sizeof(int));
		memcpy(pws, pwsSSC32, NB_CHANNELS_PWM_SSC32*sizeof(int));
		LeaveCriticalSection(&SSC32CS);
		SetAllPWMsSSC32(pSSC32, selectedchannels, pws);
		if (bExitSSC32) break;
	}

	return 0;
}

HARDWAREX_API int SetAllPWMsFromThreadSSC32x(SSC32* pSSC32, int* selectedchannels, int* pws)
{
	UNREFERENCED_PARAMETER(pSSC32);

	// id[pSSC32->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&SSC32CS);
	memcpy(selectedchannelsSSC32, selectedchannels, NB_CHANNELS_PWM_SSC32*sizeof(int));
	memcpy(pwsSSC32, pws, NB_CHANNELS_PWM_SSC32*sizeof(int));
	LeaveCriticalSection(&SSC32CS);

	return EXIT_SUCCESS;
}

HARDWAREX_API int StartThreadSSC32x(SSC32* pSSC32)
{
	bExitSSC32 = FALSE;
	InitCriticalSection(&SSC32CS);
	return CreateDefaultThread(SSC32Thread, (void*)pSSC32, &SSC32ThreadId);
}

HARDWAREX_API int StopThreadSSC32x(SSC32* pSSC32)
{
	UNREFERENCED_PARAMETER(pSSC32);

	bExitSSC32 = TRUE;
	WaitForThread(SSC32ThreadId);
	DeleteCriticalSection(&SSC32CS);
	return EXIT_SUCCESS;
}
#pragma endregion

#pragma region Maestro
HARDWAREX_API MAESTRO* CreateMaestrox(void)
{
	return (MAESTRO*)calloc(1, sizeof(MAESTRO));
}

HARDWAREX_API void DestroyMaestrox(MAESTRO* pMaestro)
{
	return free(pMaestro);
}

HARDWAREX_API int GetValueMaestrox(MAESTRO* pMaestro, int channel, int* pValue)
{
	return GetValueMaestro(pMaestro, channel, pValue);
}

HARDWAREX_API int SetPWMMaestrox(MAESTRO* pMaestro, int channel, int pw)
{
	return SetPWMMaestro(pMaestro, channel, pw);
}

HARDWAREX_API int SetAllPWMsMaestrox(MAESTRO* pMaestro, int* selectedchannels, int* pws)
{
	return SetAllPWMsMaestro(pMaestro, selectedchannels, pws);
}

HARDWAREX_API int ConnectMaestrox(MAESTRO* pMaestro, char* szCfgFilePath)
{
	return ConnectMaestro(pMaestro, szCfgFilePath);
}

HARDWAREX_API int DisconnectMaestrox(MAESTRO* pMaestro)
{
	return DisconnectMaestro(pMaestro);
}

THREAD_PROC_RETURN_VALUE MaestroThread(void* pParam)
{
	MAESTRO* pMaestro = (MAESTRO*)pParam;
	int selectedchannels[NB_CHANNELS_PWM_MAESTRO];
	int pws[NB_CHANNELS_PWM_MAESTRO];
	int value = 0;

	for (;;)
	{
		mSleep(25);
		EnterCriticalSection(&MaestroCS);
		memcpy(selectedchannels, selectedchannelsMaestro, NB_CHANNELS_PWM_MAESTRO*sizeof(int));
		memcpy(pws, pwsMaestro, NB_CHANNELS_PWM_MAESTRO*sizeof(int));
		LeaveCriticalSection(&MaestroCS);
		SetAllPWMsMaestro(pMaestro, selectedchannels, pws);
		mSleep(25);
		// Channel 11...
		value = 0;
		GetValueMaestro(pMaestro, 11, &value);
		EnterCriticalSection(&MaestroCS);
		valueMaestro = value;
		LeaveCriticalSection(&MaestroCS);
		if (bExitMaestro) break;
	}

	return 0;
}

HARDWAREX_API int SetAllPWMsFromThreadMaestrox(MAESTRO* pMaestro, int* selectedchannels, int* pws)
{
	UNREFERENCED_PARAMETER(pMaestro);

	// id[pMaestro->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&MaestroCS);
	memcpy(selectedchannelsMaestro, selectedchannels, NB_CHANNELS_PWM_MAESTRO*sizeof(int));
	memcpy(pwsMaestro, pws, NB_CHANNELS_PWM_MAESTRO*sizeof(int));
	LeaveCriticalSection(&MaestroCS);

	return EXIT_SUCCESS;
}

HARDWAREX_API int GetValueFromThreadMaestrox(MAESTRO* pMaestro, int channel, int* pValue)
{
	UNREFERENCED_PARAMETER(pMaestro);
	UNREFERENCED_PARAMETER(channel);

	// id[pMaestro->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&MaestroCS);
	*pValue = valueMaestro;
	LeaveCriticalSection(&MaestroCS);

	return EXIT_SUCCESS;
}

HARDWAREX_API int StartThreadMaestrox(MAESTRO* pMaestro)
{
	bExitMaestro = FALSE;
	InitCriticalSection(&MaestroCS);
	return CreateDefaultThread(MaestroThread, (void*)pMaestro, &MaestroThreadId);
}

HARDWAREX_API int StopThreadMaestrox(MAESTRO* pMaestro)
{
	UNREFERENCED_PARAMETER(pMaestro);

	bExitMaestro = TRUE;
	WaitForThread(MaestroThreadId);
	DeleteCriticalSection(&MaestroCS);
	return EXIT_SUCCESS;
}
#pragma endregion

#pragma region Hokuyo
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
	HOKUYO* pHokuyo = (HOKUYO*)pParam;
	double angles[MAX_SLITDIVISION_HOKUYO];
	double distances[MAX_SLITDIVISION_HOKUYO];

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

	return EXIT_SUCCESS;
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
	return EXIT_SUCCESS;
}
#pragma endregion
