#include "hardwarex.h"

#ifdef ENABLE_SBG_SUPPORT
THREAD_IDENTIFIER SBGThreadId;
CRITICAL_SECTION SBGCS;
SBGDATA sbgdataSBG;
BOOL bExitSBG = FALSE;
#endif // ENABLE_SBG_SUPPORT

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

THREAD_IDENTIFIER ubloxNMEAThreadId;
THREAD_IDENTIFIER ubloxUBXThreadId;
CRITICAL_SECTION ubloxCS;
NMEADATA nmeadataublox;
UBXDATA ubxdataublox;
BOOL bExitNMEAublox = FALSE;
BOOL bExitUBXublox = FALSE;

THREAD_IDENTIFIER SSC32ThreadId;
CRITICAL_SECTION SSC32CS;
int selectedchannelsSSC32[NB_CHANNELS_PWM_SSC32];
int pwsSSC32[NB_CHANNELS_PWM_SSC32];
BOOL bExitSSC32 = FALSE;

THREAD_IDENTIFIER PololuThreadId;
CRITICAL_SECTION PololuCS;
int selectedchannelsPololu[NB_CHANNELS_PWM_POLOLU];
int pwsPololu[NB_CHANNELS_PWM_POLOLU];
int valuePololu = 0;
BOOL bExitPololu = FALSE;

THREAD_IDENTIFIER HokuyoThreadId;
CRITICAL_SECTION HokuyoCS;
double anglesHokuyo[MAX_SLITDIVISION_HOKUYO];
double distancesHokuyo[MAX_SLITDIVISION_HOKUYO];
BOOL bExitHokuyo = FALSE;

THREAD_IDENTIFIER RPLIDARScanThreadId;
THREAD_IDENTIFIER RPLIDARExpressScanThreadId;
CRITICAL_SECTION RPLIDARCS;
double angleRPLIDAR = 0;
double distanceRPLIDAR = 0;
double anglesRPLIDAR[NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR];
double distancesRPLIDAR[NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR];
BOOL bNewScanRPLIDAR = FALSE;
int qualityRPLIDAR = FALSE;
BOOL bExitScanRPLIDAR = FALSE;
BOOL bExitExpressScanRPLIDAR = FALSE;

#ifdef ENABLE_MAVLINK_SUPPORT
THREAD_IDENTIFIER MAVLinkDeviceThreadId;
CRITICAL_SECTION MAVLinkDeviceCS;
int selectedchannelsMAVLinkDevice[NB_CHANNELS_PWM_MAVLINKDEVICE];
int pwsMAVLinkDevice[NB_CHANNELS_PWM_MAVLINKDEVICE];
MAVLINKDATA mavlinkdataMAVLinkDevice;
BOOL bExitMAVLinkDevice = FALSE;
#endif // ENABLE_MAVLINK_SUPPORT

#ifdef ENABLE_SBG_SUPPORT
#pragma region SBG
HARDWAREX_API SBG* CreateSBGx(void)
{
	return (SBG*)calloc(1, sizeof(SBG));
}

HARDWAREX_API void DestroySBGx(SBG* pSBG)
{
	return free(pSBG);
}

HARDWAREX_API SBGDATA* CreateSBGDatax(void)
{
	return (SBGDATA*)calloc(1, sizeof(SBGDATA));
}

HARDWAREX_API void DestroySBGDatax(SBGDATA* pSBGData)
{
	return free(pSBGData);
}

HARDWAREX_API int GetLatestDataSBGx(SBG* pSBG, SBGDATA* pSBGData)
{
	return GetLatestDataSBG(pSBG, pSBGData);
}

HARDWAREX_API int ConnectSBGx(SBG* pSBG, char* szCfgFilePath)
{
	return ConnectSBG(pSBG, szCfgFilePath);
}

HARDWAREX_API int DisconnectSBGx(SBG* pSBG)
{
	return DisconnectSBG(pSBG);
}

THREAD_PROC_RETURN_VALUE SBGThread(void* pParam)
{
	SBG* pSBG = (SBG*)pParam;
	SBGDATA sbgdata;

	for (;;)
	{
		mSleep(100);
		memset(&sbgdata, 0, sizeof(SBGDATA));
		GetLatestDataSBG(pSBG, &sbgdata);
		EnterCriticalSection(&SBGCS);
		sbgdataSBG = sbgdata;
		LeaveCriticalSection(&SBGCS);
		if (bExitSBG) break;
	}

	return 0;
}

HARDWAREX_API int GetLatestDataFromThreadSBGx(SBG* pSBG, SBGDATA* pSBGData)
{
	UNREFERENCED_PARAMETER(pSBG);

	// id[pSBG->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&SBGCS);
	*pSBGData = sbgdataSBG;
	LeaveCriticalSection(&SBGCS);

	return EXIT_SUCCESS;
}

HARDWAREX_API int StartThreadSBGx(SBG* pSBG)
{
	bExitSBG = FALSE;
	InitCriticalSection(&SBGCS);
	return CreateDefaultThread(SBGThread, (void*)pSBG, &SBGThreadId);
}

HARDWAREX_API int StopThreadSBGx(SBG* pSBG)
{
	UNREFERENCED_PARAMETER(pSBG);

	bExitSBG = TRUE;
	WaitForThread(SBGThreadId);
	DeleteCriticalSection(&SBGCS);
	return EXIT_SUCCESS;
}
#pragma endregion
#endif // ENABLE_SBG_SUPPORT

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

#pragma region ublox
HARDWAREX_API UBLOX* Createubloxx(void)
{
	return (UBLOX*)calloc(1, sizeof(UBLOX));
}

HARDWAREX_API void Destroyubloxx(UBLOX* publox)
{
	return free(publox);
}

HARDWAREX_API UBXDATA* CreateUBXDatax(void)
{
	return (UBXDATA*)calloc(1, sizeof(UBXDATA));
}

HARDWAREX_API void DestroyUBXDatax(UBXDATA* pUBXData)
{
	return free(pUBXData);
}

HARDWAREX_API int GetNMEASentenceubloxx(UBLOX* publox, NMEADATA* pNMEAData)
{
	return GetNMEASentenceublox(publox, pNMEAData);
}

HARDWAREX_API int GetUBXPacketubloxx(UBLOX* publox, UBXDATA* pUBXData)
{
	return GetUBXPacketublox(publox, pUBXData);
}

HARDWAREX_API int Connectubloxx(UBLOX* publox, char* szCfgFilePath)
{
	return Connectublox(publox, szCfgFilePath);
}

HARDWAREX_API int Disconnectubloxx(UBLOX* publox)
{
	return Disconnectublox(publox);
}

THREAD_PROC_RETURN_VALUE ubloxNMEAThread(void* pParam)
{
	UBLOX* publox = (UBLOX*)pParam;
	NMEADATA nmeadata;

	for (;;)
	{
		mSleep(100);
		memset(&nmeadata, 0, sizeof(NMEADATA));
		GetNMEASentenceublox(publox, &nmeadata);
		EnterCriticalSection(&ubloxCS);
		nmeadataublox = nmeadata;
		LeaveCriticalSection(&ubloxCS);
		if (bExitNMEAublox) break;
	}

	return 0;
}

THREAD_PROC_RETURN_VALUE ubloxUBXThread(void* pParam)
{
	UBLOX* publox = (UBLOX*)pParam;
	UBXDATA ubxdata;

	for (;;)
	{
		mSleep(100);
		memset(&ubxdata, 0, sizeof(UBXDATA));
		GetUBXPacketublox(publox, &ubxdata);
		EnterCriticalSection(&ubloxCS);
		ubxdataublox = ubxdata;
		LeaveCriticalSection(&ubloxCS);
		if (bExitUBXublox) break;
	}

	return 0;
}

HARDWAREX_API int GetNMEASentenceFromThreadubloxx(UBLOX* publox, NMEADATA* pNMEAData)
{
	UNREFERENCED_PARAMETER(publox);

	// id[publox->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&ubloxCS);
	*pNMEAData = nmeadataublox;
	LeaveCriticalSection(&ubloxCS);

	return EXIT_SUCCESS;
}

HARDWAREX_API int GetUBXPacketFromThreadubloxx(UBLOX* publox, UBXDATA* pUBXData)
{
	UNREFERENCED_PARAMETER(publox);

	// id[publox->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&ubloxCS);
	*pUBXData = ubxdataublox;
	LeaveCriticalSection(&ubloxCS);

	return EXIT_SUCCESS;
}

HARDWAREX_API int StartNMEAThreadubloxx(UBLOX* publox)
{
	bExitNMEAublox = FALSE;
	InitCriticalSection(&ubloxCS);
	return CreateDefaultThread(ubloxNMEAThread, (void*)publox, &ubloxNMEAThreadId);
}

HARDWAREX_API int StopNMEAThreadubloxx(UBLOX* publox)
{
	UNREFERENCED_PARAMETER(publox);

	bExitNMEAublox = TRUE;
	WaitForThread(ubloxNMEAThreadId);
	DeleteCriticalSection(&ubloxCS);
	return EXIT_SUCCESS;
}

HARDWAREX_API int StartUBXThreadubloxx(UBLOX* publox)
{
	bExitUBXublox = FALSE;
	InitCriticalSection(&ubloxCS);
	return CreateDefaultThread(ubloxUBXThread, (void*)publox, &ubloxUBXThreadId);
}

HARDWAREX_API int StopUBXThreadubloxx(UBLOX* publox)
{
	UNREFERENCED_PARAMETER(publox);

	bExitUBXublox = TRUE;
	WaitForThread(ubloxUBXThreadId);
	DeleteCriticalSection(&ubloxCS);
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

#pragma region Pololu
HARDWAREX_API POLOLU* CreatePololux(void)
{
	return (POLOLU*)calloc(1, sizeof(POLOLU));
}

HARDWAREX_API void DestroyPololux(POLOLU* pPololu)
{
	return free(pPololu);
}

HARDWAREX_API int GetValuePololux(POLOLU* pPololu, int channel, int* pValue)
{
	return GetValuePololu(pPololu, channel, pValue);
}

HARDWAREX_API int SetPWMPololux(POLOLU* pPololu, int channel, int pw)
{
	return SetPWMPololu(pPololu, channel, pw);
}

HARDWAREX_API int SetAllPWMsPololux(POLOLU* pPololu, int* selectedchannels, int* pws)
{
	return SetAllPWMsPololu(pPololu, selectedchannels, pws);
}

HARDWAREX_API int ConnectPololux(POLOLU* pPololu, char* szCfgFilePath)
{
	return ConnectPololu(pPololu, szCfgFilePath);
}

HARDWAREX_API int DisconnectPololux(POLOLU* pPololu)
{
	return DisconnectPololu(pPololu);
}

THREAD_PROC_RETURN_VALUE PololuThread(void* pParam)
{
	POLOLU* pPololu = (POLOLU*)pParam;
	int selectedchannels[NB_CHANNELS_PWM_POLOLU];
	int pws[NB_CHANNELS_PWM_POLOLU];
	int value = 0;

	for (;;)
	{
		mSleep(25);
		EnterCriticalSection(&PololuCS);
		memcpy(selectedchannels, selectedchannelsPololu, NB_CHANNELS_PWM_POLOLU*sizeof(int));
		memcpy(pws, pwsPololu, NB_CHANNELS_PWM_POLOLU*sizeof(int));
		LeaveCriticalSection(&PololuCS);
		SetAllPWMsPololu(pPololu, selectedchannels, pws);
		mSleep(25);
		// Channel 11...
		value = 0;
		GetValuePololu(pPololu, 11, &value);
		EnterCriticalSection(&PololuCS);
		valuePololu = value;
		LeaveCriticalSection(&PololuCS);
		if (bExitPololu) break;
	}

	return 0;
}

HARDWAREX_API int SetAllPWMsFromThreadPololux(POLOLU* pPololu, int* selectedchannels, int* pws)
{
	UNREFERENCED_PARAMETER(pPololu);

	// id[pPololu->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&PololuCS);
	memcpy(selectedchannelsPololu, selectedchannels, NB_CHANNELS_PWM_POLOLU*sizeof(int));
	memcpy(pwsPololu, pws, NB_CHANNELS_PWM_POLOLU*sizeof(int));
	LeaveCriticalSection(&PololuCS);

	return EXIT_SUCCESS;
}

HARDWAREX_API int GetValueFromThreadPololux(POLOLU* pPololu, int channel, int* pValue)
{
	UNREFERENCED_PARAMETER(pPololu);
	UNREFERENCED_PARAMETER(channel);

	// id[pPololu->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&PololuCS);
	*pValue = valuePololu;
	LeaveCriticalSection(&PololuCS);

	return EXIT_SUCCESS;
}

HARDWAREX_API int StartThreadPololux(POLOLU* pPololu)
{
	bExitPololu = FALSE;
	InitCriticalSection(&PololuCS);
	return CreateDefaultThread(PololuThread, (void*)pPololu, &PololuThreadId);
}

HARDWAREX_API int StopThreadPololux(POLOLU* pPololu)
{
	UNREFERENCED_PARAMETER(pPololu);

	bExitPololu = TRUE;
	WaitForThread(PololuThreadId);
	DeleteCriticalSection(&PololuCS);
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

#pragma region RPLIDAR
HARDWAREX_API RPLIDAR* CreateRPLIDARx(void)
{
	return (RPLIDAR*)calloc(1, sizeof(RPLIDAR));
}

HARDWAREX_API void DestroyRPLIDARx(RPLIDAR* pRPLIDAR)
{
	return free(pRPLIDAR);
}

HARDWAREX_API int GetScanDataResponseRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistance, double* pAngle, BOOL* pbNewScan, int *pQuality)
{
	return GetScanDataResponseRPLIDAR(pRPLIDAR, pDistance, pAngle, pbNewScan, pQuality);
}

HARDWAREX_API int GetExpressScanDataResponseRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistances, double* pAngles, BOOL* pbNewScan)
{
	return GetExpressScanDataResponseRPLIDAR(pRPLIDAR, pDistances, pAngles, pbNewScan);
}

HARDWAREX_API int ConnectRPLIDARx(RPLIDAR* pRPLIDAR, char* szCfgFilePath)
{
	return ConnectRPLIDAR(pRPLIDAR, szCfgFilePath);
}

HARDWAREX_API int DisconnectRPLIDARx(RPLIDAR* pRPLIDAR)
{
	return DisconnectRPLIDAR(pRPLIDAR);
}

THREAD_PROC_RETURN_VALUE RPLIDARScanThread(void* pParam)
{
	RPLIDAR* pRPLIDAR = (RPLIDAR*)pParam;
	double angle = 0;
	double distance = 0;
	BOOL bNewScan = FALSE;
	int quality = 0;

	for (;;)
	{
		//mSleep(50);
		angle = 0;
		distance = 0;
		GetScanDataResponseRPLIDAR(pRPLIDAR, &distance, &angle, &bNewScan, &quality);
		EnterCriticalSection(&RPLIDARCS);
		distanceRPLIDAR = distance;
		angleRPLIDAR = angle;
		bNewScanRPLIDAR = bNewScan;
		qualityRPLIDAR = quality;
		LeaveCriticalSection(&RPLIDARCS);
		if (bExitScanRPLIDAR) break;
	}

	return 0;
}

THREAD_PROC_RETURN_VALUE RPLIDARExpressScanThread(void* pParam)
{
	RPLIDAR* pRPLIDAR = (RPLIDAR*)pParam;
	double angles[NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR];
	double distances[NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR];
	BOOL bNewScan = FALSE;

	for (;;)
	{
		//mSleep(50);
		memset(distances, 0, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
		memset(angles, 0, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
		GetExpressScanDataResponseRPLIDAR(pRPLIDAR, distances, angles, &bNewScan);
		EnterCriticalSection(&RPLIDARCS);
		memcpy(distancesRPLIDAR, distances, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
		memcpy(anglesRPLIDAR, angles, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
		bNewScanRPLIDAR = bNewScan;
		LeaveCriticalSection(&RPLIDARCS);
		if (bExitExpressScanRPLIDAR) break;
	}

	return 0;
}

HARDWAREX_API int GetScanDataResponseFromThreadRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistance, double* pAngle, BOOL* pbNewScan, int *pQuality)
{
	UNREFERENCED_PARAMETER(pRPLIDAR);

	// id[pRPLIDAR->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&RPLIDARCS);
	*pDistance = distanceRPLIDAR;
	*pAngle = angleRPLIDAR;
	*pbNewScan = bNewScanRPLIDAR;
	*pQuality = qualityRPLIDAR;
	LeaveCriticalSection(&RPLIDARCS);

	return EXIT_SUCCESS;
}

HARDWAREX_API int GetExpressScanDataResponseFromThreadRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistances, double* pAngles, BOOL* pbNewScan)
{
	UNREFERENCED_PARAMETER(pRPLIDAR);

	// id[pRPLIDAR->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&RPLIDARCS);
	memcpy(pDistances, distancesRPLIDAR, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
	memcpy(pAngles, anglesRPLIDAR, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
	*pbNewScan = bNewScanRPLIDAR;
	LeaveCriticalSection(&RPLIDARCS);

	return EXIT_SUCCESS;
}

HARDWAREX_API int StartScanThreadRPLIDARx(RPLIDAR* pRPLIDAR)
{
	bExitScanRPLIDAR = FALSE;
	InitCriticalSection(&RPLIDARCS);
	return CreateDefaultThread(RPLIDARScanThread, (void*)pRPLIDAR, &RPLIDARScanThreadId);
}

HARDWAREX_API int StopScanThreadRPLIDARx(RPLIDAR* pRPLIDAR)
{
	UNREFERENCED_PARAMETER(pRPLIDAR);

	bExitScanRPLIDAR = TRUE;
	WaitForThread(RPLIDARScanThreadId);
	DeleteCriticalSection(&RPLIDARCS);
	return EXIT_SUCCESS;
}

HARDWAREX_API int StartExpressScanThreadRPLIDARx(RPLIDAR* pRPLIDAR)
{
	bExitExpressScanRPLIDAR = FALSE;
	InitCriticalSection(&RPLIDARCS);
	return CreateDefaultThread(RPLIDARExpressScanThread, (void*)pRPLIDAR, &RPLIDARExpressScanThreadId);
}

HARDWAREX_API int StopExpressScanThreadRPLIDARx(RPLIDAR* pRPLIDAR)
{
	UNREFERENCED_PARAMETER(pRPLIDAR);

	bExitExpressScanRPLIDAR = TRUE;
	WaitForThread(RPLIDARExpressScanThreadId);
	DeleteCriticalSection(&RPLIDARCS);
	return EXIT_SUCCESS;
}
#pragma endregion

#ifdef ENABLE_MAVLINK_SUPPORT
#pragma region MAVLinkDevice
HARDWAREX_API MAVLINKDEVICE* CreateMAVLinkDevicex(void)
{
	return (MAVLINKDEVICE*)calloc(1, sizeof(MAVLINKDEVICE));
}

HARDWAREX_API void DestroyMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice)
{
	return free(pMAVLinkDevice);
}

HARDWAREX_API MAVLINKDATA* CreateMAVLinkDatax(void)
{
	return (MAVLINKDATA*)calloc(1, sizeof(MAVLINKDATA));
}

HARDWAREX_API void DestroyMAVLinkDatax(MAVLINKDATA* pMAVLinkData)
{
	return free(pMAVLinkData);
}

HARDWAREX_API int GetLatestDataMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice, MAVLINKDATA* pMAVLinkData)
{
	return GetLatestDataMAVLinkDevice(pMAVLinkDevice, pMAVLinkData);
}

HARDWAREX_API int SetAllPWMsMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice, int* selectedchannels, int* pws)
{
	return SetAllPWMsMAVLinkDevice(pMAVLinkDevice, selectedchannels, pws);
}

HARDWAREX_API int ConnectMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice, char* szCfgFilePath)
{
	return ConnectMAVLinkDevice(pMAVLinkDevice, szCfgFilePath);
}

HARDWAREX_API int DisconnectMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice)
{
	return DisconnectMAVLinkDevice(pMAVLinkDevice);
}

THREAD_PROC_RETURN_VALUE MAVLinkDeviceThread(void* pParam)
{
	MAVLINKDEVICE* pMAVLinkDevice = (MAVLINKDEVICE*)pParam;
	int selectedchannels[NB_CHANNELS_PWM_MAVLINKDEVICE];
	int pws[NB_CHANNELS_PWM_MAVLINKDEVICE];
	MAVLINKDATA mavlinkdata;

	for (;;)
	{
		mSleep(25);
		EnterCriticalSection(&MAVLinkDeviceCS);
		memcpy(selectedchannels, selectedchannelsMAVLinkDevice, NB_CHANNELS_PWM_MAVLINKDEVICE*sizeof(int));
		memcpy(pws, pwsMAVLinkDevice, NB_CHANNELS_PWM_MAVLINKDEVICE*sizeof(int));
		LeaveCriticalSection(&MAVLinkDeviceCS);
		SetAllPWMsMAVLinkDevice(pMAVLinkDevice, selectedchannels, pws);
		mSleep(25);
		memset(&mavlinkdata, 0, sizeof(MAVLINKDATA));
		GetLatestDataMAVLinkDevice(pMAVLinkDevice, &mavlinkdata);
		EnterCriticalSection(&MAVLinkDeviceCS);
		mavlinkdataMAVLinkDevice = mavlinkdata;
		LeaveCriticalSection(&MAVLinkDeviceCS);
		if (bExitMAVLinkDevice) break;
	}

	return 0;
}

HARDWAREX_API int SetAllPWMsFromThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice, int* selectedchannels, int* pws)
{
	UNREFERENCED_PARAMETER(pMAVLinkDevice);

	// id[pMAVLinkDevice->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&MAVLinkDeviceCS);
	memcpy(selectedchannelsMAVLinkDevice, selectedchannels, NB_CHANNELS_PWM_MAVLINKDEVICE*sizeof(int));
	memcpy(pwsMAVLinkDevice, pws, NB_CHANNELS_PWM_MAVLINKDEVICE*sizeof(int));
	LeaveCriticalSection(&MAVLinkDeviceCS);

	return EXIT_SUCCESS;
}

HARDWAREX_API int GetLatestDataFromThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice, MAVLINKDATA* pMAVLinkData)
{
	UNREFERENCED_PARAMETER(pMAVLinkDevice);

	// id[pMAVLinkDevice->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&MAVLinkDeviceCS);
	*pMAVLinkData = mavlinkdataMAVLinkDevice;
	LeaveCriticalSection(&MAVLinkDeviceCS);

	return EXIT_SUCCESS;
}

HARDWAREX_API int StartThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice)
{
	bExitMAVLinkDevice = FALSE;
	InitCriticalSection(&MAVLinkDeviceCS);
	return CreateDefaultThread(MAVLinkDeviceThread, (void*)pMAVLinkDevice, &MAVLinkDeviceThreadId);
}

HARDWAREX_API int StopThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice)
{
	UNREFERENCED_PARAMETER(pMAVLinkDevice);

	bExitMAVLinkDevice = TRUE;
	WaitForThread(MAVLinkDeviceThreadId);
	DeleteCriticalSection(&MAVLinkDeviceCS);
	return EXIT_SUCCESS;
}
#pragma endregion
#endif // ENABLE_MAVLINK_SUPPORT
