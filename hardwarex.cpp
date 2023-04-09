#include "hardwarex.h"

#ifdef __cplusplus
#include <deque>
#endif // __cplusplus

#pragma region Global variables
THREAD_IDENTIFIER SBGThreadId;
CRITICAL_SECTION SBGCS;
SBGDATA sbgdataSBG;
int resSBG = EXIT_FAILURE;
BOOL bExitSBG = FALSE;

THREAD_IDENTIFIER MTThreadId;
CRITICAL_SECTION MTCS;
MTDATA mtdataMT;
int resMT = EXIT_FAILURE;
BOOL bExitMT = FALSE;

THREAD_IDENTIFIER RazorAHRSThreadId;
CRITICAL_SECTION RazorAHRSCS;
RAZORAHRSDATA razorahrsdataRazorAHRS;
int resRazorAHRS = EXIT_FAILURE;
BOOL bExitRazorAHRS = FALSE;

// No thread yet for MDM...

THREAD_IDENTIFIER P33xThreadId;
CRITICAL_SECTION P33xCS;
double pressureP33x = 0;
double temperatureP33x = 0;
int resP33x = EXIT_FAILURE;
BOOL bExitP33x = FALSE;

THREAD_IDENTIFIER NMEADeviceThreadId;
CRITICAL_SECTION NMEADeviceCS;
NMEADATA nmeadataNMEADevice;
int resNMEADevice = EXIT_FAILURE;
BOOL bExitNMEADevice = FALSE;

THREAD_IDENTIFIER ubloxNMEAThreadId;
THREAD_IDENTIFIER ubloxUBXThreadId;
CRITICAL_SECTION ubloxCS;
NMEADATA nmeadataublox;
UBXDATA ubxdataublox;
int resublox = EXIT_FAILURE;
BOOL bExitNMEAublox = FALSE;
BOOL bExitUBXublox = FALSE;

THREAD_IDENTIFIER IM483IThreadId;
CRITICAL_SECTION IM483ICS;
double angleIM483I = 0;
int resIM483I = EXIT_FAILURE;
BOOL bExitIM483I = FALSE;

THREAD_IDENTIFIER SSC32ThreadId;
CRITICAL_SECTION SSC32CS;
int selectedchannelsSSC32[NB_CHANNELS_PWM_SSC32];
int pwsSSC32[NB_CHANNELS_PWM_SSC32];
int resSSC32 = EXIT_FAILURE;
BOOL bExitSSC32 = FALSE;

THREAD_IDENTIFIER PololuThreadId;
CRITICAL_SECTION PololuCS;
int selectedchannelsPololu[NB_CHANNELS_PWM_POLOLU];
int pwsPololu[NB_CHANNELS_PWM_POLOLU];
int valuesPololu[NB_CHANNELS_POLOLU];
int resPololu = EXIT_FAILURE;
BOOL bExitPololu = FALSE;

THREAD_IDENTIFIER HokuyoThreadId;
CRITICAL_SECTION HokuyoCS;
double anglesHokuyo[MAX_SLITDIVISION_HOKUYO];
double distancesHokuyo[MAX_SLITDIVISION_HOKUYO];
int resHokuyo = EXIT_FAILURE;
BOOL bExitHokuyo = FALSE;

THREAD_IDENTIFIER RPLIDARScanThreadId;
THREAD_IDENTIFIER RPLIDARExpressScanThreadId;
THREAD_IDENTIFIER RPLIDAROtherScanThreadId;
CRITICAL_SECTION RPLIDARCS;
double angleRPLIDAR = 0;
double distanceRPLIDAR = 0;
int nbMeasurementsRPLIDAR = 0;
double anglesRPLIDAR[MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR];
double distancesRPLIDAR[MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR];
BOOL bNewScanRPLIDAR = FALSE;
int qualityRPLIDAR = 0;
#ifdef __cplusplus
std::deque<double> anglesvectorRPLIDAR;
std::deque<double> distancesvectorRPLIDAR;
#endif // __cplusplus
int resRPLIDAR = EXIT_FAILURE;
BOOL bExitScanRPLIDAR = FALSE;
BOOL bExitExpressScanRPLIDAR = FALSE;
BOOL bExitOtherScanRPLIDAR = FALSE;

#ifdef ENABLE_MAVLINK_SUPPORT
THREAD_IDENTIFIER MAVLinkDeviceThreadId;
CRITICAL_SECTION MAVLinkDeviceCS;
int selectedchannelsMAVLinkDevice[NB_CHANNELS_PWM_MAVLINKDEVICE];
int pwsMAVLinkDevice[NB_CHANNELS_PWM_MAVLINKDEVICE];
MAVLINKDATA mavlinkdataMAVLinkDevice;
int resMAVLinkDevice = EXIT_FAILURE;
BOOL bExitMAVLinkDevice = FALSE;
#endif // ENABLE_MAVLINK_SUPPORT
#pragma endregion

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
#ifdef ENABLE_SBG_SDK_SUPPORT
	return GetLatestDataSBG(pSBG, pSBGData);
#else
	return GetFrameSBG(pSBG, pSBGData);
#endif // ENABLE_SBG_SDK_SUPPORT
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
	int res = EXIT_FAILURE, err = EXIT_SUCCESS;
	SBGDATA sbgdata;

	memset(&sbgdata, 0, sizeof(SBGDATA));
	for (;;)
	{
#ifdef ENABLE_SBG_SDK_SUPPORT
		mSleep(pSBG->threadperiod);
#endif // ENABLE_SBG_SDK_SUPPORT
		//memset(&sbgdata, 0, sizeof(SBGDATA));
#ifdef ENABLE_SBG_SDK_SUPPORT
		res = GetLatestDataSBG(pSBG, &sbgdata);
		if (res != EXIT_SUCCESS) err = res;
		//if (GetLatestDataSBG(pSBG, &sbgdata) == EXIT_SUCCESS)
#else
		res = GetFrameSBG(pSBG, &sbgdata);
		if (res != EXIT_SUCCESS) err = res;
		//if (GetFrameSBG(pSBG, &sbgdata) == EXIT_SUCCESS)
#endif // ENABLE_SBG_SDK_SUPPORT
		{
			EnterCriticalSection(&SBGCS);
			sbgdataSBG = sbgdata;
			resSBG = err;
			LeaveCriticalSection(&SBGCS);
		}
		if (bExitSBG) break;
	}

	return 0;
}

HARDWAREX_API int GetLatestDataFromThreadSBGx(SBG* pSBG, SBGDATA* pSBGData)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pSBG);

	// id[pSBG->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&SBGCS);
	*pSBGData = sbgdataSBG;
	res = resSBG;
	LeaveCriticalSection(&SBGCS);

	return res;
}

HARDWAREX_API int StartThreadSBGx(SBG* pSBG)
{
	resSBG = EXIT_FAILURE;
	bExitSBG = FALSE;
	memset(&sbgdataSBG, 0, sizeof(SBGDATA));
	InitCriticalSection(&SBGCS);
	return CreateDefaultThread(SBGThread, (void*)pSBG, &SBGThreadId);
}

HARDWAREX_API int StopThreadSBGx(SBG* pSBG)
{
	UNREFERENCED_PARAMETER(pSBG);

	bExitSBG = TRUE;
	WaitForThread(SBGThreadId);
	DeleteCriticalSection(&SBGCS);
	resSBG = EXIT_FAILURE;
	return EXIT_SUCCESS;
}
#pragma endregion

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
	int res = EXIT_FAILURE, err = EXIT_SUCCESS;
	MTDATA mtdata;

	memset(&mtdata, 0, sizeof(MTDATA));
	for (;;)
	{
		mSleep(pMT->threadperiod);
		//memset(&mtdata, 0, sizeof(MTDATA));
		res = GetLatestDataMT(pMT, &mtdata);
		if (res != EXIT_SUCCESS) err = res;
		//if (GetLatestDataMT(pMT, &mtdata) == EXIT_SUCCESS)
		{
			EnterCriticalSection(&MTCS);
			mtdataMT = mtdata;
			resMT = err;
			LeaveCriticalSection(&MTCS);
		}
		if (bExitMT) break;
	}

	return 0;
}

HARDWAREX_API int GetLatestDataFromThreadMTx(MT* pMT, MTDATA* pMTData)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pMT);

	// id[pMT->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&MTCS);
	*pMTData = mtdataMT;
	res = resMT;
	LeaveCriticalSection(&MTCS);

	return res;
}

HARDWAREX_API int StartThreadMTx(MT* pMT)
{
	resMT = EXIT_FAILURE;
	bExitMT = FALSE;
	memset(&mtdataMT, 0, sizeof(MTDATA));
	InitCriticalSection(&MTCS);
	return CreateDefaultThread(MTThread, (void*)pMT, &MTThreadId);
}

HARDWAREX_API int StopThreadMTx(MT* pMT)
{
	UNREFERENCED_PARAMETER(pMT);

	bExitMT = TRUE;
	WaitForThread(MTThreadId);
	DeleteCriticalSection(&MTCS);
	resMT = EXIT_FAILURE;
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
	int res = EXIT_FAILURE, err = EXIT_SUCCESS;
	RAZORAHRSDATA razorahrsdata;

	memset(&razorahrsdata, 0, sizeof(RAZORAHRSDATA));
	for (;;)
	{
		mSleep(pRazorAHRS->threadperiod);
		//memset(&razorahrsdata, 0, sizeof(RAZORAHRSDATA));
		res = GetLatestDataRazorAHRS(pRazorAHRS, &razorahrsdata);
		if (res != EXIT_SUCCESS) err = res;
		//if (GetLatestDataRazorAHRS(pRazorAHRS, &razorahrsdata) == EXIT_SUCCESS)
		{
			EnterCriticalSection(&RazorAHRSCS);
			razorahrsdataRazorAHRS = razorahrsdata;
			resRazorAHRS = err;
			LeaveCriticalSection(&RazorAHRSCS);
		}
		if (bExitRazorAHRS) break;
	}

	return 0;
}

HARDWAREX_API int GetLatestDataFromThreadRazorAHRSx(RAZORAHRS* pRazorAHRS, RAZORAHRSDATA* pRazorAHRSData)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pRazorAHRS);

	// id[pRazorAHRS->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&RazorAHRSCS);
	*pRazorAHRSData = razorahrsdataRazorAHRS;
	res = resRazorAHRS;
	LeaveCriticalSection(&RazorAHRSCS);

	return res;
}

HARDWAREX_API int StartThreadRazorAHRSx(RAZORAHRS* pRazorAHRS)
{
	resRazorAHRS = EXIT_FAILURE;
	bExitRazorAHRS = FALSE;
	memset(&razorahrsdataRazorAHRS, 0, sizeof(RAZORAHRSDATA));
	InitCriticalSection(&RazorAHRSCS);
	return CreateDefaultThread(RazorAHRSThread, (void*)pRazorAHRS, &RazorAHRSThreadId);
}

HARDWAREX_API int StopThreadRazorAHRSx(RAZORAHRS* pRazorAHRS)
{
	UNREFERENCED_PARAMETER(pRazorAHRS);

	bExitRazorAHRS = TRUE;
	WaitForThread(RazorAHRSThreadId);
	DeleteCriticalSection(&RazorAHRSCS);
	resRazorAHRS = EXIT_FAILURE;
	return EXIT_SUCCESS;
}
#pragma endregion

#pragma region MDM
HARDWAREX_API MDM* CreateMDMx(void)
{
	return (MDM*)calloc(1, sizeof(MDM));
}

HARDWAREX_API void DestroyMDMx(MDM* pMDM)
{
	return free(pMDM);
}

HARDWAREX_API int SendDataMDMx(MDM* pMDM, unsigned char* buf, int buflen, int* pSentBytes)
{
	return SendDataMDM(pMDM, buf, buflen, pSentBytes);
}

HARDWAREX_API int RecvDataMDMx(MDM* pMDM, unsigned char* buf, int buflen, int* pReceivedBytes)
{
	return RecvDataMDM(pMDM, buf, buflen, pReceivedBytes);
}

HARDWAREX_API int PurgeDataMDMx(MDM* pMDM)
{
	return PurgeDataMDM(pMDM);
}

HARDWAREX_API int ConnectMDMx(MDM* pMDM, char* szCfgFilePath)
{
	return ConnectMDM(pMDM, szCfgFilePath);
}

HARDWAREX_API int DisconnectMDMx(MDM* pMDM)
{
	return DisconnectMDM(pMDM);
}
#pragma endregion

#pragma region P33x
HARDWAREX_API P33X* CreateP33xx(void)
{
	return (P33X*)calloc(1, sizeof(P33X));
}

HARDWAREX_API void DestroyP33xx(P33X* pP33x)
{
	return free(pP33x);
}

HARDWAREX_API int GetPressureP33xx(P33X* pP33x, double* pPressure)
{
	return GetPressureP33x(pP33x, pPressure);
}

HARDWAREX_API int GetTemperatureP33xx(P33X* pP33x, double* pTemperature)
{
	return GetTemperatureP33x(pP33x, pTemperature);
}

HARDWAREX_API int ConnectP33xx(P33X* pP33x, char* szCfgFilePath)
{
	return ConnectP33x(pP33x, szCfgFilePath);
}

HARDWAREX_API int DisconnectP33xx(P33X* pP33x)
{
	return DisconnectP33x(pP33x);
}

THREAD_PROC_RETURN_VALUE P33xThread(void* pParam)
{
	P33X* pP33x = (P33X*)pParam;
	int res = EXIT_FAILURE, err = EXIT_SUCCESS;
	double pressure = 0, temperature = 0;

	for (;;)
	{
		mSleep(pP33x->threadperiod/2);
		pressure = 0;
		res = GetPressureP33x(pP33x, &pressure);
		if (res != EXIT_SUCCESS) err = res;
		mSleep(pP33x->threadperiod/2);
		temperature = 0;
		res = GetTemperatureP33x(pP33x, &temperature);
		if (res != EXIT_SUCCESS) err = res;
		EnterCriticalSection(&P33xCS);
		pressureP33x = pressure;
		temperatureP33x = temperature;
		resP33x = err;
		LeaveCriticalSection(&P33xCS);
		if (bExitP33x) break;
	}

	return 0;
}

HARDWAREX_API int GetPressureFromThreadP33xx(P33X* pP33x, double* pPressure)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pP33x);

	// id[pP33x->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&P33xCS);
	*pPressure = pressureP33x;
	res = resP33x;
	LeaveCriticalSection(&P33xCS);

	return res;
}

HARDWAREX_API int GetTemperatureFromThreadP33xx(P33X* pP33x, double* pTemperature)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pP33x);

	// id[pP33x->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&P33xCS);
	*pTemperature = temperatureP33x;
	res = resP33x;
	LeaveCriticalSection(&P33xCS);

	return res;
}

HARDWAREX_API int StartThreadP33xx(P33X* pP33x)
{
	resP33x = EXIT_FAILURE;
	bExitP33x = FALSE;
	InitCriticalSection(&P33xCS);
	return CreateDefaultThread(P33xThread, (void*)pP33x, &P33xThreadId);
}

HARDWAREX_API int StopThreadP33xx(P33X* pP33x)
{
	UNREFERENCED_PARAMETER(pP33x);

	bExitP33x = TRUE;
	WaitForThread(P33xThreadId);
	DeleteCriticalSection(&P33xCS);
	resP33x = EXIT_FAILURE;
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
	int res = EXIT_FAILURE, err = EXIT_SUCCESS;
	NMEADATA nmeadata;

	memset(&nmeadata, 0, sizeof(NMEADATA));
	for (;;)
	{
		mSleep(pNMEADevice->threadperiod);
		memset(&nmeadata, 0, sizeof(NMEADATA));
		res = GetLatestDataNMEADevice(pNMEADevice, &nmeadata);
		if (res != EXIT_SUCCESS) err = res;
		EnterCriticalSection(&NMEADeviceCS);
		nmeadataNMEADevice = nmeadata;
		resNMEADevice = err;
		LeaveCriticalSection(&NMEADeviceCS);
		if (bExitNMEADevice) break;
	}

	return 0;
}

HARDWAREX_API int GetLatestDataFromThreadNMEADevicex(NMEADEVICE* pNMEADevice, NMEADATA* pNMEAData)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pNMEADevice);

	// id[pNMEADevice->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&NMEADeviceCS);
	*pNMEAData = nmeadataNMEADevice;
	res = resNMEADevice;
	LeaveCriticalSection(&NMEADeviceCS);

	return res;
}

HARDWAREX_API int StartThreadNMEADevicex(NMEADEVICE* pNMEADevice)
{
	resNMEADevice = EXIT_FAILURE;
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
	resNMEADevice = EXIT_FAILURE;
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
	int res = EXIT_FAILURE, err = EXIT_SUCCESS;
	NMEADATA nmeadata;

	memset(&nmeadata, 0, sizeof(NMEADATA));
	for (;;)
	{
		//mSleep(publox->threadperiod);
		//memset(&nmeadata, 0, sizeof(NMEADATA));
		res = GetNMEASentenceublox(publox, &nmeadata);
		if (res != EXIT_SUCCESS) err = res;
		//if (GetNMEASentenceublox(publox, &nmeadata) == EXIT_SUCCESS)
		{
			EnterCriticalSection(&ubloxCS);
			nmeadataublox = nmeadata;
			resublox = err;
			LeaveCriticalSection(&ubloxCS);
		}
		if (bExitNMEAublox) break;
	}

	return 0;
}

THREAD_PROC_RETURN_VALUE ubloxUBXThread(void* pParam)
{
	UBLOX* publox = (UBLOX*)pParam;
	int res = EXIT_FAILURE, err = EXIT_SUCCESS;
	UBXDATA ubxdata;

	memset(&ubxdata, 0, sizeof(UBXDATA));
	for (;;)
	{
		//mSleep(publox->threadperiod);
		//memset(&ubxdata, 0, sizeof(UBXDATA));
		res = GetUBXPacketublox(publox, &ubxdata);
		if (res != EXIT_SUCCESS) err = res;
		//if (GetUBXPacketublox(publox, &ubxdata) == EXIT_SUCCESS)
		{
			EnterCriticalSection(&ubloxCS);
			ubxdataublox = ubxdata;
			resublox = err;
			LeaveCriticalSection(&ubloxCS);
		}
		if (bExitUBXublox) break;
	}

	return 0;
}

HARDWAREX_API int GetNMEASentenceFromThreadubloxx(UBLOX* publox, NMEADATA* pNMEAData)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(publox);

	// id[publox->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&ubloxCS);
	*pNMEAData = nmeadataublox;
	res = resublox;
	LeaveCriticalSection(&ubloxCS);

	return res;
}

HARDWAREX_API int GetUBXPacketFromThreadubloxx(UBLOX* publox, UBXDATA* pUBXData)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(publox);

	// id[publox->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&ubloxCS);
	*pUBXData = ubxdataublox;
	res = resublox;
	LeaveCriticalSection(&ubloxCS);

	return res;
}

HARDWAREX_API int StartNMEAThreadubloxx(UBLOX* publox)
{
	resublox = EXIT_FAILURE;
	bExitNMEAublox = FALSE;
	memset(&nmeadataublox, 0, sizeof(NMEADATA));
	InitCriticalSection(&ubloxCS);
	return CreateDefaultThread(ubloxNMEAThread, (void*)publox, &ubloxNMEAThreadId);
}

HARDWAREX_API int StopNMEAThreadubloxx(UBLOX* publox)
{
	UNREFERENCED_PARAMETER(publox);

	bExitNMEAublox = TRUE;
	WaitForThread(ubloxNMEAThreadId);
	DeleteCriticalSection(&ubloxCS);
	resublox = EXIT_FAILURE;
	return EXIT_SUCCESS;
}

HARDWAREX_API int StartUBXThreadubloxx(UBLOX* publox)
{
	resublox = EXIT_FAILURE;
	bExitUBXublox = FALSE;
	memset(&ubxdataublox, 0, sizeof(UBXDATA));
	InitCriticalSection(&ubloxCS);
	return CreateDefaultThread(ubloxUBXThread, (void*)publox, &ubloxUBXThreadId);
}

HARDWAREX_API int StopUBXThreadubloxx(UBLOX* publox)
{
	UNREFERENCED_PARAMETER(publox);

	bExitUBXublox = TRUE;
	WaitForThread(ubloxUBXThreadId);
	DeleteCriticalSection(&ubloxCS);
	resublox = EXIT_FAILURE;
	return EXIT_SUCCESS;
}
#pragma endregion

#pragma region IM483I
HARDWAREX_API IM483I* CreateIM483Ix(void)
{
	return (IM483I*)calloc(1, sizeof(IM483I));
}

HARDWAREX_API void DestroyIM483Ix(IM483I* pIM483I)
{
	return free(pIM483I);
}

HARDWAREX_API int SetMotorTorqueIM483Ix(IM483I* pIM483I, int holdpercent, int runpercent)
{
	return SetMotorTorqueIM483I(pIM483I, holdpercent, runpercent);
}

HARDWAREX_API int SetMotorSpeedIM483Ix(IM483I* pIM483I, int val)
{
	return SetMotorSpeedIM483I(pIM483I, val);
}

HARDWAREX_API int SetMotorRelativeIM483Ix(IM483I* pIM483I, int val, BOOL bForce)
{
	return SetMotorRelativeIM483I(pIM483I, val, bForce);
}

HARDWAREX_API int SetMotorOriginIM483Ix(IM483I* pIM483I)
{
	return SetMotorOriginIM483I(pIM483I);
}

HARDWAREX_API int SetMaxAngleIM483Ix(IM483I* pIM483I, double angle)
{
	return SetMaxAngleIM483I(pIM483I, angle);
}

HARDWAREX_API int CalibrateMotorIM483Ix(IM483I* pIM483I)
{
	return CalibrateMotorIM483I(pIM483I);
}

HARDWAREX_API int ConnectIM483Ix(IM483I* pIM483I, char* szCfgFilePath)
{
	return ConnectIM483I(pIM483I, szCfgFilePath);
}

HARDWAREX_API int DisconnectIM483Ix(IM483I* pIM483I)
{
	return DisconnectIM483I(pIM483I);
}

THREAD_PROC_RETURN_VALUE IM483IThread(void* pParam)
{
	IM483I* pIM483I = (IM483I*)pParam;
	int res = EXIT_FAILURE, err = EXIT_SUCCESS;
	double angle = 0;

	mSleep(pIM483I->threadperiod);

	for (;;)
	{
		EnterCriticalSection(&IM483ICS);
		angle = angleIM483I;
		LeaveCriticalSection(&IM483ICS);
		res = SetMaxAngleIM483I(pIM483I, angle);
		if (res != EXIT_SUCCESS) err = res;
		mSleep(pIM483I->threadperiod);
		EnterCriticalSection(&IM483ICS);
		resIM483I = err;
		LeaveCriticalSection(&IM483ICS);
		if (bExitIM483I) break;
	}

	return 0;
}

HARDWAREX_API int SetMaxAngleFromThreadIM483Ix(IM483I* pIM483I, double angle)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pIM483I);

	// id[pIM483I->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&IM483ICS);
	angleIM483I = angle;
	res = resIM483I;
	LeaveCriticalSection(&IM483ICS);

	return res;
}

HARDWAREX_API int StartThreadIM483Ix(IM483I* pIM483I)
{
	resIM483I = EXIT_FAILURE;
	bExitIM483I = FALSE;
	InitCriticalSection(&IM483ICS);
	return CreateDefaultThread(IM483IThread, (void*)pIM483I, &IM483IThreadId);
}

HARDWAREX_API int StopThreadIM483Ix(IM483I* pIM483I)
{
	UNREFERENCED_PARAMETER(pIM483I);

	bExitIM483I = TRUE;
	WaitForThread(IM483IThreadId);
	DeleteCriticalSection(&IM483ICS);
	resIM483I = EXIT_FAILURE;
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

HARDWAREX_API int GetVoltageSSC32x(SSC32* pSSC32, int channel, double* pVoltage)
{
	return GetVoltageSSC32(pSSC32, channel, pVoltage);
}

HARDWAREX_API int GetDigitalInputSSC32x(SSC32* pSSC32, int channel, int* pValue)
{
	return GetDigitalInputSSC32(pSSC32, channel, pValue);
}

HARDWAREX_API int GetPWMSSC32x(SSC32* pSSC32, int channel, int* pPw)
{
	return GetPWMSSC32(pSSC32, channel, pPw);
}

HARDWAREX_API int SetPWMSSC32x(SSC32* pSSC32, int channel, int pw)
{
	return SetPWMSSC32(pSSC32, channel, pw);
}

HARDWAREX_API int SetAllPWMsSSC32x(SSC32* pSSC32, int* selectedchannels, int* pws)
{
	return SetAllPWMsSSC32(pSSC32, selectedchannels, pws);
}

HARDWAREX_API int SetDigitalOutputSSC32x(SSC32* pSSC32, int channel, int value)
{
	return SetDigitalOutputSSC32(pSSC32, channel, value);
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
	int res = EXIT_FAILURE, err = EXIT_SUCCESS;
	int selectedchannels[NB_CHANNELS_PWM_SSC32];
	int pws[NB_CHANNELS_PWM_SSC32];

	mSleep(pSSC32->threadperiod);

	for (;;)
	{
		EnterCriticalSection(&SSC32CS);
		memcpy(selectedchannels, selectedchannelsSSC32, NB_CHANNELS_PWM_SSC32*sizeof(int));
		memcpy(pws, pwsSSC32, NB_CHANNELS_PWM_SSC32*sizeof(int));
		LeaveCriticalSection(&SSC32CS);
		res = SetAllPWMsSSC32(pSSC32, selectedchannels, pws);
		if (res != EXIT_SUCCESS) err = res;
		mSleep(pSSC32->threadperiod);
		EnterCriticalSection(&SSC32CS);
		resSSC32 = err;
		LeaveCriticalSection(&SSC32CS);
		if (bExitSSC32) break;
	}

	return 0;
}

HARDWAREX_API int SetAllPWMsFromThreadSSC32x(SSC32* pSSC32, int* selectedchannels, int* pws)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pSSC32);

	// id[pSSC32->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&SSC32CS);
	memcpy(selectedchannelsSSC32, selectedchannels, NB_CHANNELS_PWM_SSC32*sizeof(int));
	memcpy(pwsSSC32, pws, NB_CHANNELS_PWM_SSC32*sizeof(int));
	res = resSSC32;
	LeaveCriticalSection(&SSC32CS);

	return res;
}

HARDWAREX_API int StartThreadSSC32x(SSC32* pSSC32)
{
	resSSC32 = EXIT_FAILURE;
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
	resSSC32 = EXIT_FAILURE;
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

HARDWAREX_API int GetAllValuesPololux(POLOLU* pPololu, int* selectedchannels, int* ais)
{
	return GetAllValuesPololu(pPololu, selectedchannels, ais);
}

HARDWAREX_API int SetPWMPololux(POLOLU* pPololu, int channel, int pw)
{
	return SetPWMPololu(pPololu, channel, pw);
}

HARDWAREX_API int SetAllPWMsPololux(POLOLU* pPololu, int* selectedchannels, int* pws)
{
	return SetAllPWMsPololu(pPololu, selectedchannels, pws);
}

HARDWAREX_API int SetPWMJrkPololux(POLOLU* pPololu, int pw)
{
	return SetPWMJrkPololu(pPololu, pw);
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
	int res = EXIT_FAILURE, err = EXIT_SUCCESS;
	int selectedchannels[NB_CHANNELS_PWM_POLOLU];
	int pws[NB_CHANNELS_PWM_POLOLU];
	int value = 0;

	memset(valuesPololu, 0, NB_CHANNELS_POLOLU*sizeof(int));
	
	mSleep(pPololu->threadperiod);

	for (;;)
	{
		EnterCriticalSection(&PololuCS);
		memcpy(selectedchannels, selectedchannelsPololu, NB_CHANNELS_PWM_POLOLU*sizeof(int));
		memcpy(pws, pwsPololu, NB_CHANNELS_PWM_POLOLU*sizeof(int));
		LeaveCriticalSection(&PololuCS);
		res = SetAllPWMsPololu(pPololu, selectedchannels, pws);
		if (res != EXIT_SUCCESS) err = res;
		mSleep(10);
		if (pPololu->winddiranaloginputchan != -1)
		{
			value = 0;
			res = GetValuePololu(pPololu, pPololu->winddiranaloginputchan, &value);
			if (res != EXIT_SUCCESS) err = res;
			mSleep(10);
			EnterCriticalSection(&PololuCS);
			valuesPololu[pPololu->winddiranaloginputchan] = value;
			resPololu = err;
			LeaveCriticalSection(&PololuCS);
		}
		//else mSleep(10);
		if (pPololu->windspeedanaloginputchan != -1)
		{
			value = 0;
			res = GetValuePololu(pPololu, pPololu->windspeedanaloginputchan, &value);
			if (res != EXIT_SUCCESS) err = res;
			mSleep(10);
			EnterCriticalSection(&PololuCS);
			valuesPololu[pPololu->windspeedanaloginputchan] = value;
			resPololu = err;
			LeaveCriticalSection(&PololuCS);
		}
		//else mSleep(10);
		if (pPololu->vbat1analoginputchan != -1)
		{
			value = 0;
			res = GetValuePololu(pPololu, pPololu->vbat1analoginputchan, &value);
			if (res != EXIT_SUCCESS) err = res;
			mSleep(10);
			EnterCriticalSection(&PololuCS);
			valuesPololu[pPololu->vbat1analoginputchan] = value;
			resPololu = err;
			LeaveCriticalSection(&PololuCS);
		}
		//else mSleep(10);
		if (pPololu->ibat1analoginputchan != -1)
		{
			value = 0;
			res = GetValuePololu(pPololu, pPololu->ibat1analoginputchan, &value);
			if (res != EXIT_SUCCESS) err = res;
			mSleep(10);
			EnterCriticalSection(&PololuCS);
			valuesPololu[pPololu->ibat1analoginputchan] = value;
			resPololu = err;
			LeaveCriticalSection(&PololuCS);
		}
		//else mSleep(10);
		if (pPololu->vbat2analoginputchan != -1)
		{
			value = 0;
			res = GetValuePololu(pPololu, pPololu->vbat2analoginputchan, &value);
			if (res != EXIT_SUCCESS) err = res;
			mSleep(10);
			EnterCriticalSection(&PololuCS);
			valuesPololu[pPololu->vbat2analoginputchan] = value;
			resPololu = err;
			LeaveCriticalSection(&PololuCS);
		}
		//else mSleep(10);
		if (pPololu->ibat2analoginputchan != -1)
		{
			value = 0;
			res = GetValuePololu(pPololu, pPololu->ibat2analoginputchan, &value);
			if (res != EXIT_SUCCESS) err = res;
			mSleep(10);
			EnterCriticalSection(&PololuCS);
			valuesPololu[pPololu->ibat2analoginputchan] = value;
			resPololu = err;
			LeaveCriticalSection(&PololuCS);
		}
		//else mSleep(10);
		if (pPololu->switchanaloginputchan != -1)
		{
			value = 0;
			res = GetValuePololu(pPololu, pPololu->switchanaloginputchan, &value);
			if (res != EXIT_SUCCESS) err = res;
			mSleep(10);
			EnterCriticalSection(&PololuCS);
			valuesPololu[pPololu->switchanaloginputchan] = value;
			resPololu = err;
			LeaveCriticalSection(&PololuCS);
		}
		//else mSleep(10);
		EnterCriticalSection(&PololuCS);
		resPololu = err;
		LeaveCriticalSection(&PololuCS);
		if (bExitPololu) break;
	}

	return 0;
}

HARDWAREX_API int SetAllPWMsFromThreadPololux(POLOLU* pPololu, int* selectedchannels, int* pws)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pPololu);

	// id[pPololu->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&PololuCS);
	memcpy(selectedchannelsPololu, selectedchannels, NB_CHANNELS_PWM_POLOLU*sizeof(int));
	memcpy(pwsPololu, pws, NB_CHANNELS_PWM_POLOLU*sizeof(int));
	res = resPololu;
	LeaveCriticalSection(&PololuCS);

	return res;
}

HARDWAREX_API int GetValueFromThreadPololux(POLOLU* pPololu, int channel, int* pValue)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pPololu);

	// id[pPololu->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&PololuCS);
	if ((channel >= 0)&&(channel < NB_CHANNELS_POLOLU)) *pValue = valuesPololu[channel];
	res = resPololu;
	LeaveCriticalSection(&PololuCS);

	return res;
}

HARDWAREX_API int StartThreadPololux(POLOLU* pPololu)
{
	resPololu = EXIT_FAILURE;
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
	resPololu = EXIT_FAILURE;
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
	int res = EXIT_FAILURE, err = EXIT_SUCCESS;
	double angles[MAX_SLITDIVISION_HOKUYO];
	double distances[MAX_SLITDIVISION_HOKUYO];

	for (;;)
	{
		//mSleep(pHokuyo->threadperiod);
		memset(distances, 0, MAX_SLITDIVISION_HOKUYO*sizeof(double));
		memset(angles, 0, MAX_SLITDIVISION_HOKUYO*sizeof(double));
		res = GetLatestDataHokuyo(pHokuyo, distances, angles);
		if (res != EXIT_SUCCESS) err = res;
		// if (GetLatestDataHokuyo(pHokuyo, distances, angles) == EXIT8SUCCESS)
		{
			EnterCriticalSection(&HokuyoCS);
			memcpy(distancesHokuyo, distances, MAX_SLITDIVISION_HOKUYO*sizeof(double));
			memcpy(anglesHokuyo, angles, MAX_SLITDIVISION_HOKUYO*sizeof(double));
			resHokuyo = err;
			LeaveCriticalSection(&HokuyoCS);
		}
		if (bExitHokuyo) break;
	}

	return 0;
}

HARDWAREX_API int GetLatestDataFromThreadHokuyox(HOKUYO* pHokuyo, double* pDistances, double* pAngles)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pHokuyo);

	// id[pHokuyo->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&HokuyoCS);
	memcpy(pDistances, distancesHokuyo, MAX_SLITDIVISION_HOKUYO*sizeof(double));
	memcpy(pAngles, anglesHokuyo, MAX_SLITDIVISION_HOKUYO*sizeof(double));
	res = resHokuyo;
	LeaveCriticalSection(&HokuyoCS);

	return res;
}

HARDWAREX_API int StartThreadHokuyox(HOKUYO* pHokuyo)
{
	resHokuyo = EXIT_FAILURE;
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
	resHokuyo = EXIT_FAILURE;
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

HARDWAREX_API int StopRequestRPLIDARx(RPLIDAR* pRPLIDAR)
{
	return StopRequestRPLIDAR(pRPLIDAR);
}

HARDWAREX_API int ResetRequestRPLIDARx(RPLIDAR* pRPLIDAR)
{
	return ResetRequestRPLIDAR(pRPLIDAR);
}

HARDWAREX_API int GetStartupMessageRPLIDARx(RPLIDAR* pRPLIDAR)
{
	return GetStartupMessageRPLIDAR(pRPLIDAR);
}

HARDWAREX_API int ClearCacheRPLIDARx(RPLIDAR* pRPLIDAR)
{
	return ClearCacheRPLIDAR(pRPLIDAR);
}

HARDWAREX_API int GetHealthRequestRPLIDARx(RPLIDAR* pRPLIDAR, BOOL* pbProtectionStop)
{
	return GetHealthRequestRPLIDAR(pRPLIDAR, pbProtectionStop);
}

HARDWAREX_API int GetInfoRequestRPLIDARx(RPLIDAR* pRPLIDAR, int* pModelID, int* pHardwareVersion, int* pFirmwareMajor, int* pFirmwareMinor, char* SerialNumber)
{
	return GetInfoRequestRPLIDAR(pRPLIDAR, pModelID, pHardwareVersion, pFirmwareMajor, pFirmwareMinor, SerialNumber);
}

HARDWAREX_API int GetTypicalScanModeRPLIDARx(RPLIDAR* pRPLIDAR, int* pScanModeID)
{
	return GetTypicalScanModeRPLIDAR(pRPLIDAR, pScanModeID);
}

HARDWAREX_API int GetAllSupportedScanModesRPLIDARx(RPLIDAR* pRPLIDAR, int* pScanModeIDs, double* pusPerSamples, double* pMaxDistances, int* pAnsTypes, char** pScanModeNames)
{
	RPLIDARSCANMODE scanmodes[MAX_NB_SCAN_MODES_RPLIDAR];
	int i = 0;
	int res = GetAllSupportedScanModesRPLIDAR(pRPLIDAR, scanmodes);
	for (i = 0; i < MAX_NB_SCAN_MODES_RPLIDAR; i++)
	{
		pScanModeIDs[i] = scanmodes[i].id;
		pusPerSamples[i] = scanmodes[i].us_per_sample;
		pMaxDistances[i] = scanmodes[i].max_distance;
		pAnsTypes[i] = scanmodes[i].ans_type;
		memcpy(pScanModeNames[i], scanmodes[i].scan_mode, 64);
	}
	return res;
}

HARDWAREX_API int SetMotorPWMRequestRPLIDARx(RPLIDAR* pRPLIDAR, int pwm)
{
	return SetMotorPWMRequestRPLIDAR(pRPLIDAR, pwm);
}

HARDWAREX_API int SetLidarSpinSpeedRequestRPLIDARx(RPLIDAR* pRPLIDAR, int rpm)
{
	return SetLidarSpinSpeedRequestRPLIDAR(pRPLIDAR, rpm);
}

HARDWAREX_API int StartMotorRPLIDARx(RPLIDAR* pRPLIDAR)
{
	return StartMotorRPLIDAR(pRPLIDAR);
}

HARDWAREX_API int StopMotorRPLIDARx(RPLIDAR* pRPLIDAR)
{
	return StopMotorRPLIDAR(pRPLIDAR);
}

HARDWAREX_API int StartScanRequestRPLIDARx(RPLIDAR* pRPLIDAR)
{
	return StartScanRequestRPLIDAR(pRPLIDAR);
}

HARDWAREX_API int StartForceScanRequestRPLIDARx(RPLIDAR* pRPLIDAR)
{
	return StartForceScanRequestRPLIDAR(pRPLIDAR);
}

HARDWAREX_API int GetScanDataResponseRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistance, double* pAngle, BOOL* pbNewScan, int *pQuality)
{
	return GetScanDataResponseRPLIDAR(pRPLIDAR, pDistance, pAngle, pbNewScan, pQuality);
}

HARDWAREX_API int StartExpressScanRequestRPLIDARx(RPLIDAR* pRPLIDAR)
{
	return StartExpressScanRequestRPLIDAR(pRPLIDAR);
}

HARDWAREX_API int GetExpressScanDataResponseRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistances, double* pAngles, BOOL* pbNewScan)
{
	return GetExpressScanDataResponseRPLIDAR(pRPLIDAR, pDistances, pAngles, pbNewScan);
}

HARDWAREX_API int StartOtherScanRequestRPLIDARx(RPLIDAR* pRPLIDAR, int scanmodeid)
{
	return StartOtherScanRequestRPLIDAR(pRPLIDAR, scanmodeid);
}

HARDWAREX_API int GetOtherScanDataResponseRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistances, double* pAngles, BOOL* pbNewScan, int* pNbMeasurements)
{
	return GetOtherScanDataResponseRPLIDAR(pRPLIDAR, pDistances, pAngles, pbNewScan, pNbMeasurements);
}

HARDWAREX_API int ConnectRPLIDARx(RPLIDAR* pRPLIDAR, char* szCfgFilePath)
{
#ifdef __cplusplus
	anglesvectorRPLIDAR = std::deque<double>();
	distancesvectorRPLIDAR = std::deque<double>();
#endif // __cplusplus

	return ConnectRPLIDAR(pRPLIDAR, szCfgFilePath);
}

HARDWAREX_API int DisconnectRPLIDARx(RPLIDAR* pRPLIDAR)
{
#ifdef __cplusplus
	anglesvectorRPLIDAR = std::deque<double>();
	distancesvectorRPLIDAR = std::deque<double>();
#endif // __cplusplus

	return DisconnectRPLIDAR(pRPLIDAR);
}

THREAD_PROC_RETURN_VALUE RPLIDARScanThread(void* pParam)
{
	RPLIDAR* pRPLIDAR = (RPLIDAR*)pParam;
	int res = EXIT_FAILURE, err = EXIT_SUCCESS;
	double angle = 0;
	double distance = 0;
	BOOL bNewScan = FALSE, bAutoNewScan = FALSE;
	int quality = 0, j = 0, nb = 0, nbprev = 0;

#ifdef __cplusplus
	EnterCriticalSection(&RPLIDARCS);
	anglesvectorRPLIDAR = std::deque<double>();
	distancesvectorRPLIDAR = std::deque<double>();
	LeaveCriticalSection(&RPLIDARCS);
#endif // __cplusplus

	for (;;)
	{
		//mSleep(pRPLIDAR->threadperiod);
		angle = 0;
		distance = 0;
		res = GetScanDataResponseRPLIDAR(pRPLIDAR, &distance, &angle, &bNewScan, &quality);
		if (res != EXIT_SUCCESS) err = res;
		//if (GetScanDataResponseRPLIDAR(pRPLIDAR, &distance, &angle, &bNewScan, &quality) == EXIT_SUCCESS)
		{
			EnterCriticalSection(&RPLIDARCS);
			distanceRPLIDAR = distance;
			angleRPLIDAR = angle;
			bNewScanRPLIDAR = bNewScan;
			qualityRPLIDAR = quality;

#ifdef __cplusplus
			if (pRPLIDAR->maxhist == 0)
			{
				// Try to detect the beginning of a new scan with the angle discontinuity...
				// Try to be a little bit robust w.r.t. non-decreasing outliers...
				if (((int)anglesvectorRPLIDAR.size() >= 5)&&
					((angle-anglesvectorRPLIDAR[(int)anglesvectorRPLIDAR.size()-5]) > M_PI)&&
					((angle-anglesvectorRPLIDAR[(int)anglesvectorRPLIDAR.size()-4]) > M_PI)&&
					((angle-anglesvectorRPLIDAR[(int)anglesvectorRPLIDAR.size()-3]) > M_PI)&&
					((angle-anglesvectorRPLIDAR[(int)anglesvectorRPLIDAR.size()-2]) > M_PI)&&
					((angle-anglesvectorRPLIDAR[(int)anglesvectorRPLIDAR.size()-1]) > M_PI))
					bAutoNewScan = TRUE; else bAutoNewScan = FALSE;
				if (bAutoNewScan)
				{
					// Try to automatically remove old data...
					for (j = nbprev-nb-1; j >= 0; j--)
					{
						if ((int)anglesvectorRPLIDAR.size() > 0)
						{
							anglesvectorRPLIDAR.pop_front();
							distancesvectorRPLIDAR.pop_front();
						}
					}
					nbprev = nb;
					nb = 0;
				}
			}

			anglesvectorRPLIDAR.push_back(angle);
			distancesvectorRPLIDAR.push_back(distance);

			if (pRPLIDAR->maxhist == 0)
			{
				// Try to automatically remove old data...
				nb++;
				if ((nb <= nbprev)&&((int)anglesvectorRPLIDAR.size() > 0))
				{
					anglesvectorRPLIDAR.pop_front();
					distancesvectorRPLIDAR.pop_front();
				}
			}
			if (((pRPLIDAR->maxhist > 0)&&((int)anglesvectorRPLIDAR.size() > pRPLIDAR->maxhist))||
				((int)anglesvectorRPLIDAR.size() > MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR))
			{
				anglesvectorRPLIDAR.pop_front();
				distancesvectorRPLIDAR.pop_front();
			}
#endif // __cplusplus

			resRPLIDAR = err;
			LeaveCriticalSection(&RPLIDARCS);
		}
		if (bExitScanRPLIDAR) break;
	}

	return 0;
}

THREAD_PROC_RETURN_VALUE RPLIDARExpressScanThread(void* pParam)
{
	RPLIDAR* pRPLIDAR = (RPLIDAR*)pParam;
	int res = EXIT_FAILURE, err = EXIT_SUCCESS;
	double angles[NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR];
	double distances[NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR];
	BOOL bNewScan = FALSE, bAutoNewScan = FALSE;
	int i = 0, j = 0, nb = 0, nbprev = 0;

#ifdef __cplusplus
	EnterCriticalSection(&RPLIDARCS);
	anglesvectorRPLIDAR = std::deque<double>();
	distancesvectorRPLIDAR = std::deque<double>();
	LeaveCriticalSection(&RPLIDARCS);
#endif // __cplusplus

	for (;;)
	{
		//mSleep(pRPLIDAR->threadperiod);
		memset(distances, 0, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
		memset(angles, 0, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
		res = GetExpressScanDataResponseRPLIDAR(pRPLIDAR, distances, angles, &bNewScan);
		if (res != EXIT_SUCCESS) err = res;
		//if (GetExpressScanDataResponseRPLIDAR(pRPLIDAR, distances, angles, &bNewScan) == EXIT_SUCCESS)
		{
			EnterCriticalSection(&RPLIDARCS);
			memcpy(distancesRPLIDAR, distances, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
			memcpy(anglesRPLIDAR, angles, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
			bNewScanRPLIDAR = bNewScan;

#ifdef __cplusplus
			for (i = 0; i < NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR; i++)
			{
				if (pRPLIDAR->maxhist == 0)
				{
					// Try to detect the beginning of a new scan with the angle discontinuity...
					// Try to be a little bit robust w.r.t. non-decreasing outliers...
					if (((int)anglesvectorRPLIDAR.size() >= 5)&&
						((angles[i]-anglesvectorRPLIDAR[(int)anglesvectorRPLIDAR.size()-5]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[(int)anglesvectorRPLIDAR.size()-4]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[(int)anglesvectorRPLIDAR.size()-3]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[(int)anglesvectorRPLIDAR.size()-2]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[(int)anglesvectorRPLIDAR.size()-1]) > M_PI))
						bAutoNewScan = TRUE; else bAutoNewScan = FALSE;
					if (bAutoNewScan)
					{
						// Try to automatically remove old data...
						for (j = nbprev-nb-1; j >= 0; j--)
						{
							if ((int)anglesvectorRPLIDAR.size() > 0)
							{
								anglesvectorRPLIDAR.pop_front();
								distancesvectorRPLIDAR.pop_front();
							}
						}
						nbprev = nb;
						nb = 0;
					}
				}

				anglesvectorRPLIDAR.push_back(angles[i]);
				distancesvectorRPLIDAR.push_back(distances[i]);

				if (pRPLIDAR->maxhist == 0)
				{
					// Try to automatically remove old data...
					nb++;
					if ((nb <= nbprev)&&((int)anglesvectorRPLIDAR.size() > 0))
					{
						anglesvectorRPLIDAR.pop_front();
						distancesvectorRPLIDAR.pop_front();
					}
				}
				if (((pRPLIDAR->maxhist > 0)&&((int)anglesvectorRPLIDAR.size() > pRPLIDAR->maxhist))||
					((int)anglesvectorRPLIDAR.size() > MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR))
				{
					anglesvectorRPLIDAR.pop_front();
					distancesvectorRPLIDAR.pop_front();
				}
			}
#endif // __cplusplus

			resRPLIDAR = err;
			LeaveCriticalSection(&RPLIDARCS);
		}
		if (bExitExpressScanRPLIDAR) break;
	}

	return 0;
}

THREAD_PROC_RETURN_VALUE RPLIDAROtherScanThread(void* pParam)
{
	RPLIDAR* pRPLIDAR = (RPLIDAR*)pParam;
	int res = EXIT_FAILURE, err = EXIT_SUCCESS;
	int nbMeasurements = NB_MEASUREMENTS_OTHER_SCAN_DATA_RESPONSE_RPLIDAR;
	double angles[MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR];
	double distances[MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR];
	BOOL bNewScan = FALSE, bAutoNewScan = FALSE;
	int i = 0, j = 0, nb = 0, nbprev = 0;

#ifdef __cplusplus
	EnterCriticalSection(&RPLIDARCS);
	anglesvectorRPLIDAR = std::deque<double>();
	distancesvectorRPLIDAR = std::deque<double>();
	LeaveCriticalSection(&RPLIDARCS);
#endif // __cplusplus

	for (;;)
	{
		//mSleep(pRPLIDAR->threadperiod);
		memset(distances, 0, MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR*sizeof(double));
		memset(angles, 0, MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR*sizeof(double));
		res = GetOtherScanDataResponseRPLIDAR(pRPLIDAR, distances, angles, &bNewScan, &nbMeasurements);
		if (res != EXIT_SUCCESS) err = res;
		//if (GetOtherScanDataResponseRPLIDAR(pRPLIDAR, distances, angles, &bNewScan, &nbMeasurements) == EXIT_SUCCESS)
		{
			EnterCriticalSection(&RPLIDARCS);
			nbMeasurementsRPLIDAR = nbMeasurements;
			memcpy(distancesRPLIDAR, distances, nbMeasurements*sizeof(double));
			memcpy(anglesRPLIDAR, angles, nbMeasurements*sizeof(double));
			bNewScanRPLIDAR = bNewScan;

#ifdef __cplusplus
			for (i = 0; i < nbMeasurements; i++)
			{
				if (pRPLIDAR->maxhist == 0)
				{
					// Try to detect the beginning of a new scan with the angle discontinuity...
					// Try to be a little bit robust w.r.t. non-decreasing outliers...
					if (((int)anglesvectorRPLIDAR.size() >= 5)&&
						((angles[i]-anglesvectorRPLIDAR[(int)anglesvectorRPLIDAR.size()-5]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[(int)anglesvectorRPLIDAR.size()-4]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[(int)anglesvectorRPLIDAR.size()-3]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[(int)anglesvectorRPLIDAR.size()-2]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[(int)anglesvectorRPLIDAR.size()-1]) > M_PI))
						bAutoNewScan = TRUE; else bAutoNewScan = FALSE;
					if (bAutoNewScan)
					{
						// Try to automatically remove old data...
						for (j = nbprev-nb-1; j >= 0; j--)
						{
							if ((int)anglesvectorRPLIDAR.size() > 0)
							{
								anglesvectorRPLIDAR.pop_front();
								distancesvectorRPLIDAR.pop_front();
							}
						}
						nbprev = nb;
						nb = 0;
					}
				}

				anglesvectorRPLIDAR.push_back(angles[i]);
				distancesvectorRPLIDAR.push_back(distances[i]);

				if (pRPLIDAR->maxhist == 0)
				{
					// Try to automatically remove old data...
					nb++;
					if ((nb <= nbprev)&&((int)anglesvectorRPLIDAR.size() > 0))
					{
						anglesvectorRPLIDAR.pop_front();
						distancesvectorRPLIDAR.pop_front();
					}
				}
				if (((pRPLIDAR->maxhist > 0)&&((int)anglesvectorRPLIDAR.size() > pRPLIDAR->maxhist))||
					((int)anglesvectorRPLIDAR.size() > MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR))
				{
					anglesvectorRPLIDAR.pop_front();
					distancesvectorRPLIDAR.pop_front();
				}
			}
#endif // __cplusplus

			resRPLIDAR = err;
			LeaveCriticalSection(&RPLIDARCS);
		}
		if (bExitOtherScanRPLIDAR) break;
	}

	return 0;
}

HARDWAREX_API int GetScanDataResponseFromThreadRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistance, double* pAngle, BOOL* pbNewScan, int *pQuality)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pRPLIDAR);

	// id[pRPLIDAR->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&RPLIDARCS);
	*pDistance = distanceRPLIDAR;
	*pAngle = angleRPLIDAR;
	*pbNewScan = bNewScanRPLIDAR;
	*pQuality = qualityRPLIDAR;
	res = resRPLIDAR;
	LeaveCriticalSection(&RPLIDARCS);

	return res;
}

HARDWAREX_API int GetExpressScanDataResponseFromThreadRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistances, double* pAngles, BOOL* pbNewScan)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pRPLIDAR);

	// id[pRPLIDAR->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&RPLIDARCS);
	memcpy(pDistances, distancesRPLIDAR, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
	memcpy(pAngles, anglesRPLIDAR, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
	*pbNewScan = bNewScanRPLIDAR;
	res = resRPLIDAR;
	LeaveCriticalSection(&RPLIDARCS);

	return res;
}

HARDWAREX_API int GetOtherScanDataResponseFromThreadRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistances, double* pAngles, BOOL* pbNewScan, int* pNbMeasurements)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pRPLIDAR);

	// id[pRPLIDAR->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&RPLIDARCS);
	*pNbMeasurements = nbMeasurementsRPLIDAR;
	memcpy(pDistances, distancesRPLIDAR, nbMeasurementsRPLIDAR*sizeof(double));
	memcpy(pAngles, anglesRPLIDAR, nbMeasurementsRPLIDAR*sizeof(double));
	*pbNewScan = bNewScanRPLIDAR;
	res = resRPLIDAR;
	LeaveCriticalSection(&RPLIDARCS);

	return res;
}

HARDWAREX_API int GetLast360DataFromThreadRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistances, double* pAngles, int* pNbMeasurements)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pRPLIDAR);

	// id[pRPLIDAR->szCfgFile] to be able to handle several devices...

#ifdef __cplusplus
	EnterCriticalSection(&RPLIDARCS);
	*pNbMeasurements = (int)anglesvectorRPLIDAR.size();
	for (int i = *pNbMeasurements-1; i >= 0; i--)
	{
		pAngles[i] = anglesvectorRPLIDAR[i];
		pDistances[i] = distancesvectorRPLIDAR[i];
	}
	res = resRPLIDAR;
	LeaveCriticalSection(&RPLIDARCS);

	if (*pNbMeasurements <= 0) return EXIT_TIMEOUT;
	return res;
#else
	return EXIT_NOT_IMPLEMENTED;
#endif // __cplusplus
}

HARDWAREX_API int StartScanThreadRPLIDARx(RPLIDAR* pRPLIDAR)
{
	resRPLIDAR = EXIT_FAILURE;
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
	resRPLIDAR = EXIT_FAILURE;
	return EXIT_SUCCESS;
}

HARDWAREX_API int StartExpressScanThreadRPLIDARx(RPLIDAR* pRPLIDAR)
{
	resRPLIDAR = EXIT_FAILURE;
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
	resRPLIDAR = EXIT_FAILURE;
	return EXIT_SUCCESS;
}

HARDWAREX_API int StartOtherScanThreadRPLIDARx(RPLIDAR* pRPLIDAR)
{
	resRPLIDAR = EXIT_FAILURE;
	bExitOtherScanRPLIDAR = FALSE;
	InitCriticalSection(&RPLIDARCS);
	return CreateDefaultThread(RPLIDAROtherScanThread, (void*)pRPLIDAR, &RPLIDAROtherScanThreadId);
}

HARDWAREX_API int StopOtherScanThreadRPLIDARx(RPLIDAR* pRPLIDAR)
{
	UNREFERENCED_PARAMETER(pRPLIDAR);

	bExitOtherScanRPLIDAR = TRUE;
	WaitForThread(RPLIDAROtherScanThreadId);
	DeleteCriticalSection(&RPLIDARCS);
	resRPLIDAR = EXIT_FAILURE;
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

HARDWAREX_API int GPSInputMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice, double gps_lat, double gps_lon, double gps_alt, double yaw)
{
	return GPSInputMAVLinkDevice(pMAVLinkDevice, gps_lat, gps_lon, gps_alt, yaw);
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
	int res = EXIT_FAILURE, err = EXIT_SUCCESS;
	int selectedchannels[NB_CHANNELS_PWM_MAVLINKDEVICE];
	int pws[NB_CHANNELS_PWM_MAVLINKDEVICE];
	MAVLINKDATA mavlinkdata;

	memset(&mavlinkdata, 0, sizeof(MAVLINKDATA));
	for (;;)
	{
		uSleep(1000*pMAVLinkDevice->threadperiod/2);
		EnterCriticalSection(&MAVLinkDeviceCS);
		memcpy(selectedchannels, selectedchannelsMAVLinkDevice, NB_CHANNELS_PWM_MAVLINKDEVICE*sizeof(int));
		memcpy(pws, pwsMAVLinkDevice, NB_CHANNELS_PWM_MAVLINKDEVICE*sizeof(int));
		LeaveCriticalSection(&MAVLinkDeviceCS);
		res = SetAllPWMsMAVLinkDevice(pMAVLinkDevice, selectedchannels, pws);
		if (res != EXIT_SUCCESS) err = res;
		uSleep(1000*pMAVLinkDevice->threadperiod/2);
		//memset(&mavlinkdata, 0, sizeof(MAVLINKDATA));
		res = GetLatestDataMAVLinkDevice(pMAVLinkDevice, &mavlinkdata);
		if (res != EXIT_SUCCESS) err = res;
		//if (GetLatestDataMAVLinkDevice(pMAVLinkDevice, &mavlinkdata) == EXIT_SUCCESS)
		{
			EnterCriticalSection(&MAVLinkDeviceCS);
			mavlinkdataMAVLinkDevice = mavlinkdata;
			resMAVLinkDevice = err;
			LeaveCriticalSection(&MAVLinkDeviceCS);
		}
		if (bExitMAVLinkDevice) break;
	}

	return 0;
}

HARDWAREX_API int SetAllPWMsFromThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice, int* selectedchannels, int* pws)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pMAVLinkDevice);

	// id[pMAVLinkDevice->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&MAVLinkDeviceCS);
	memcpy(selectedchannelsMAVLinkDevice, selectedchannels, NB_CHANNELS_PWM_MAVLINKDEVICE*sizeof(int));
	memcpy(pwsMAVLinkDevice, pws, NB_CHANNELS_PWM_MAVLINKDEVICE*sizeof(int));
	res = resMAVLinkDevice;
	LeaveCriticalSection(&MAVLinkDeviceCS);

	return res;
}

HARDWAREX_API int GetLatestDataFromThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice, MAVLINKDATA* pMAVLinkData)
{
	int res = EXIT_FAILURE;

	UNREFERENCED_PARAMETER(pMAVLinkDevice);

	// id[pMAVLinkDevice->szCfgFile] to be able to handle several devices...

	EnterCriticalSection(&MAVLinkDeviceCS);
	*pMAVLinkData = mavlinkdataMAVLinkDevice;
	res = resMAVLinkDevice;
	LeaveCriticalSection(&MAVLinkDeviceCS);

	return res;
}

HARDWAREX_API int StartThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice)
{
	resMAVLinkDevice = EXIT_FAILURE;
	bExitMAVLinkDevice = FALSE;
	memset(&mavlinkdataMAVLinkDevice, 0, sizeof(MAVLINKDATA));
	InitCriticalSection(&MAVLinkDeviceCS);
	return CreateDefaultThread(MAVLinkDeviceThread, (void*)pMAVLinkDevice, &MAVLinkDeviceThreadId);
}

HARDWAREX_API int StopThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice)
{
	UNREFERENCED_PARAMETER(pMAVLinkDevice);

	bExitMAVLinkDevice = TRUE;
	WaitForThread(MAVLinkDeviceThreadId);
	DeleteCriticalSection(&MAVLinkDeviceCS);
	resMAVLinkDevice = EXIT_FAILURE;
	return EXIT_SUCCESS;
}
#pragma endregion
#endif // ENABLE_MAVLINK_SUPPORT
