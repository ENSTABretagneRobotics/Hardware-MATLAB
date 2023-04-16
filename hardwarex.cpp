#include "hardwarex.h"

#ifdef __cplusplus
#include <deque>
#endif // __cplusplus

#define MAX_NB_DEVICES_HARDWAREX 16

#pragma region Global variables
void* addrsSBG[MAX_NB_DEVICES_HARDWAREX] = { NULL };
THREAD_IDENTIFIER SBGThreadId[MAX_NB_DEVICES_HARDWAREX];
CRITICAL_SECTION SBGCS[MAX_NB_DEVICES_HARDWAREX];
SBGDATA sbgdataSBG[MAX_NB_DEVICES_HARDWAREX];
int resSBG[MAX_NB_DEVICES_HARDWAREX];
BOOL bExitSBG[MAX_NB_DEVICES_HARDWAREX];

void* addrsMT[MAX_NB_DEVICES_HARDWAREX] = { NULL };
THREAD_IDENTIFIER MTThreadId[MAX_NB_DEVICES_HARDWAREX];
CRITICAL_SECTION MTCS[MAX_NB_DEVICES_HARDWAREX];
MTDATA mtdataMT[MAX_NB_DEVICES_HARDWAREX];
int resMT[MAX_NB_DEVICES_HARDWAREX];
BOOL bExitMT[MAX_NB_DEVICES_HARDWAREX];

void* addrsRazorAHRS[MAX_NB_DEVICES_HARDWAREX] = { NULL };
THREAD_IDENTIFIER RazorAHRSThreadId[MAX_NB_DEVICES_HARDWAREX];
CRITICAL_SECTION RazorAHRSCS[MAX_NB_DEVICES_HARDWAREX];
RAZORAHRSDATA razorahrsdataRazorAHRS[MAX_NB_DEVICES_HARDWAREX];
int resRazorAHRS[MAX_NB_DEVICES_HARDWAREX];
BOOL bExitRazorAHRS[MAX_NB_DEVICES_HARDWAREX];

// No thread yet for MDM...

void* addrsP33x[MAX_NB_DEVICES_HARDWAREX] = { NULL };
THREAD_IDENTIFIER P33xThreadId[MAX_NB_DEVICES_HARDWAREX];
CRITICAL_SECTION P33xCS[MAX_NB_DEVICES_HARDWAREX];
double pressureP33x[MAX_NB_DEVICES_HARDWAREX];
double temperatureP33x[MAX_NB_DEVICES_HARDWAREX];
int resP33x[MAX_NB_DEVICES_HARDWAREX];
BOOL bExitP33x[MAX_NB_DEVICES_HARDWAREX];

void* addrsNMEADevice[MAX_NB_DEVICES_HARDWAREX] = { NULL };
THREAD_IDENTIFIER NMEADeviceThreadId[MAX_NB_DEVICES_HARDWAREX];
CRITICAL_SECTION NMEADeviceCS[MAX_NB_DEVICES_HARDWAREX];
NMEADATA nmeadataNMEADevice[MAX_NB_DEVICES_HARDWAREX];
int resNMEADevice[MAX_NB_DEVICES_HARDWAREX];
BOOL bExitNMEADevice[MAX_NB_DEVICES_HARDWAREX];

void* addrsublox[MAX_NB_DEVICES_HARDWAREX] = { NULL };
THREAD_IDENTIFIER ubloxNMEAThreadId[MAX_NB_DEVICES_HARDWAREX];
THREAD_IDENTIFIER ubloxUBXThreadId[MAX_NB_DEVICES_HARDWAREX];
CRITICAL_SECTION ubloxCS[MAX_NB_DEVICES_HARDWAREX];
NMEADATA nmeadataublox[MAX_NB_DEVICES_HARDWAREX];
UBXDATA ubxdataublox[MAX_NB_DEVICES_HARDWAREX];
int resublox[MAX_NB_DEVICES_HARDWAREX];
BOOL bExitNMEAublox[MAX_NB_DEVICES_HARDWAREX];
BOOL bExitUBXublox[MAX_NB_DEVICES_HARDWAREX];

void* addrsIM483I[MAX_NB_DEVICES_HARDWAREX] = { NULL };
THREAD_IDENTIFIER IM483IThreadId[MAX_NB_DEVICES_HARDWAREX];
CRITICAL_SECTION IM483ICS[MAX_NB_DEVICES_HARDWAREX];
double angleIM483I[MAX_NB_DEVICES_HARDWAREX];
int resIM483I[MAX_NB_DEVICES_HARDWAREX];
BOOL bExitIM483I[MAX_NB_DEVICES_HARDWAREX];

void* addrsSSC32[MAX_NB_DEVICES_HARDWAREX] = { NULL };
THREAD_IDENTIFIER SSC32ThreadId[MAX_NB_DEVICES_HARDWAREX];
CRITICAL_SECTION SSC32CS[MAX_NB_DEVICES_HARDWAREX];
int selectedchannelsSSC32[MAX_NB_DEVICES_HARDWAREX][NB_CHANNELS_PWM_SSC32];
int pwsSSC32[MAX_NB_DEVICES_HARDWAREX][NB_CHANNELS_PWM_SSC32];
int resSSC32[MAX_NB_DEVICES_HARDWAREX];
BOOL bExitSSC32[MAX_NB_DEVICES_HARDWAREX];

void* addrsPololu[MAX_NB_DEVICES_HARDWAREX] = { NULL };
THREAD_IDENTIFIER PololuThreadId[MAX_NB_DEVICES_HARDWAREX];
CRITICAL_SECTION PololuCS[MAX_NB_DEVICES_HARDWAREX];
int selectedchannelsPololu[MAX_NB_DEVICES_HARDWAREX][NB_CHANNELS_PWM_POLOLU];
int pwsPololu[MAX_NB_DEVICES_HARDWAREX][NB_CHANNELS_PWM_POLOLU];
int valuesPololu[MAX_NB_DEVICES_HARDWAREX][NB_CHANNELS_POLOLU];
int resPololu[MAX_NB_DEVICES_HARDWAREX];
BOOL bExitPololu[MAX_NB_DEVICES_HARDWAREX];

void* addrsHokuyo[MAX_NB_DEVICES_HARDWAREX] = { NULL };
THREAD_IDENTIFIER HokuyoThreadId[MAX_NB_DEVICES_HARDWAREX];
CRITICAL_SECTION HokuyoCS[MAX_NB_DEVICES_HARDWAREX];
double anglesHokuyo[MAX_NB_DEVICES_HARDWAREX][MAX_SLITDIVISION_HOKUYO];
double distancesHokuyo[MAX_NB_DEVICES_HARDWAREX][MAX_SLITDIVISION_HOKUYO];
int resHokuyo[MAX_NB_DEVICES_HARDWAREX];
BOOL bExitHokuyo[MAX_NB_DEVICES_HARDWAREX];

void* addrsRPLIDAR[MAX_NB_DEVICES_HARDWAREX] = { NULL };
THREAD_IDENTIFIER RPLIDARScanThreadId[MAX_NB_DEVICES_HARDWAREX];
THREAD_IDENTIFIER RPLIDARExpressScanThreadId[MAX_NB_DEVICES_HARDWAREX];
THREAD_IDENTIFIER RPLIDAROtherScanThreadId[MAX_NB_DEVICES_HARDWAREX];
CRITICAL_SECTION RPLIDARCS[MAX_NB_DEVICES_HARDWAREX];
double angleRPLIDAR[MAX_NB_DEVICES_HARDWAREX];
double distanceRPLIDAR[MAX_NB_DEVICES_HARDWAREX];
int nbMeasurementsRPLIDAR[MAX_NB_DEVICES_HARDWAREX];
double anglesRPLIDAR[MAX_NB_DEVICES_HARDWAREX][MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR];
double distancesRPLIDAR[MAX_NB_DEVICES_HARDWAREX][MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR];
BOOL bNewScanRPLIDAR[MAX_NB_DEVICES_HARDWAREX];
int qualityRPLIDAR[MAX_NB_DEVICES_HARDWAREX];
#ifdef __cplusplus
std::deque<double> anglesvectorRPLIDAR[MAX_NB_DEVICES_HARDWAREX];
std::deque<double> distancesvectorRPLIDAR[MAX_NB_DEVICES_HARDWAREX];
#endif // __cplusplus
int resRPLIDAR[MAX_NB_DEVICES_HARDWAREX];
BOOL bExitScanRPLIDAR[MAX_NB_DEVICES_HARDWAREX];
BOOL bExitExpressScanRPLIDAR[MAX_NB_DEVICES_HARDWAREX];
BOOL bExitOtherScanRPLIDAR[MAX_NB_DEVICES_HARDWAREX];

#ifdef ENABLE_MAVLINK_SUPPORT
void* addrsMAVLinkDevice[MAX_NB_DEVICES_HARDWAREX] = { NULL };
THREAD_IDENTIFIER MAVLinkDeviceThreadId[MAX_NB_DEVICES_HARDWAREX];
CRITICAL_SECTION MAVLinkDeviceCS[MAX_NB_DEVICES_HARDWAREX];
int selectedchannelsMAVLinkDevice[MAX_NB_DEVICES_HARDWAREX][NB_CHANNELS_PWM_MAVLINKDEVICE];
int pwsMAVLinkDevice[MAX_NB_DEVICES_HARDWAREX][NB_CHANNELS_PWM_MAVLINKDEVICE];
MAVLINKDATA mavlinkdataMAVLinkDevice[MAX_NB_DEVICES_HARDWAREX];
int resMAVLinkDevice[MAX_NB_DEVICES_HARDWAREX];
BOOL bExitMAVLinkDevice[MAX_NB_DEVICES_HARDWAREX];
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
	int id = 0, res = EXIT_FAILURE;

	while (addrsSBG[id] != NULL)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = ConnectSBG(pSBG, szCfgFilePath);
	if (res != EXIT_SUCCESS) return res;

	addrsSBG[id] = pSBG;

	return EXIT_SUCCESS;
}

HARDWAREX_API int DisconnectSBGx(SBG* pSBG)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsSBG[id] != pSBG)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = DisconnectSBG(pSBG);
	if (res != EXIT_SUCCESS) return res;

	addrsSBG[id] = NULL;

	return EXIT_SUCCESS;
}

THREAD_PROC_RETURN_VALUE SBGThread(void* pParam)
{
	SBG* pSBG = (SBG*)pParam;
	int id = 0, res = EXIT_FAILURE, err = EXIT_SUCCESS;
	SBGDATA sbgdata;

	while (addrsSBG[id] != pSBG)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return 0;
	}

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
			EnterCriticalSection(&SBGCS[id]);
			sbgdataSBG[id] = sbgdata;
			resSBG[id] = err;
			LeaveCriticalSection(&SBGCS[id]);
		}
		if (bExitSBG[id]) break;
	}

	return 0;
}

HARDWAREX_API int GetLatestDataFromThreadSBGx(SBG* pSBG, SBGDATA* pSBGData)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsSBG[id] != pSBG)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&SBGCS[id]);
	*pSBGData = sbgdataSBG[id];
	res = resSBG[id];
	LeaveCriticalSection(&SBGCS[id]);

	return res;
}

HARDWAREX_API int StartThreadSBGx(SBG* pSBG)
{
	int id = 0;

	while (addrsSBG[id] != pSBG)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	resSBG[id] = EXIT_FAILURE;
	bExitSBG[id] = FALSE;
	memset(&sbgdataSBG, 0, sizeof(SBGDATA));
	InitCriticalSection(&SBGCS[id]);
	return CreateDefaultThread(SBGThread, (void*)pSBG, &SBGThreadId[id]);
}

HARDWAREX_API int StopThreadSBGx(SBG* pSBG)
{
	int id = 0;

	while (addrsSBG[id] != pSBG)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	bExitSBG[id] = TRUE;
	WaitForThread(SBGThreadId[id]);
	DeleteCriticalSection(&SBGCS[id]);
	resSBG[id] = EXIT_FAILURE;
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
	int id = 0, res = EXIT_FAILURE;

	while (addrsMT[id] != NULL)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = ConnectMT(pMT, szCfgFilePath);
	if (res != EXIT_SUCCESS) return res;

	addrsMT[id] = pMT;

	return EXIT_SUCCESS;
}

HARDWAREX_API int DisconnectMTx(MT* pMT)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsMT[id] != pMT)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = DisconnectMT(pMT);
	if (res != EXIT_SUCCESS) return res;

	addrsMT[id] = NULL;

	return EXIT_SUCCESS;
}

THREAD_PROC_RETURN_VALUE MTThread(void* pParam)
{
	MT* pMT = (MT*)pParam;
	int id = 0, res = EXIT_FAILURE, err = EXIT_SUCCESS;
	MTDATA mtdata;

	while (addrsMT[id] != pMT)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return 0;
	}

	memset(&mtdata, 0, sizeof(MTDATA));
	for (;;)
	{
		mSleep(pMT->threadperiod);
		//memset(&mtdata, 0, sizeof(MTDATA));
		res = GetLatestDataMT(pMT, &mtdata);
		if (res != EXIT_SUCCESS) err = res;
		//if (GetLatestDataMT(pMT, &mtdata) == EXIT_SUCCESS)
		{
			EnterCriticalSection(&MTCS[id]);
			mtdataMT[id] = mtdata;
			resMT[id] = err;
			LeaveCriticalSection(&MTCS[id]);
		}
		if (bExitMT[id]) break;
	}

	return 0;
}

HARDWAREX_API int GetLatestDataFromThreadMTx(MT* pMT, MTDATA* pMTData)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsMT[id] != pMT)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&MTCS[id]);
	*pMTData = mtdataMT[id];
	res = resMT[id];
	LeaveCriticalSection(&MTCS[id]);

	return res;
}

HARDWAREX_API int StartThreadMTx(MT* pMT)
{
	int id = 0;

	while (addrsMT[id] != pMT)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	resMT[id] = EXIT_FAILURE;
	bExitMT[id] = FALSE;
	memset(&mtdataMT, 0, sizeof(MTDATA));
	InitCriticalSection(&MTCS[id]);
	return CreateDefaultThread(MTThread, (void*)pMT, &MTThreadId[id]);
}

HARDWAREX_API int StopThreadMTx(MT* pMT)
{
	int id = 0;

	while (addrsMT[id] != pMT)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	bExitMT[id] = TRUE;
	WaitForThread(MTThreadId[id]);
	DeleteCriticalSection(&MTCS[id]);
	resMT[id] = EXIT_FAILURE;
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
	int id = 0, res = EXIT_FAILURE;

	while (addrsRazorAHRS[id] != NULL)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = ConnectRazorAHRS(pRazorAHRS, szCfgFilePath);
	if (res != EXIT_SUCCESS) return res;

	addrsRazorAHRS[id] = pRazorAHRS;

	return EXIT_SUCCESS;
}

HARDWAREX_API int DisconnectRazorAHRSx(RAZORAHRS* pRazorAHRS)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsRazorAHRS[id] != pRazorAHRS)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = DisconnectRazorAHRS(pRazorAHRS);
	if (res != EXIT_SUCCESS) return res;

	addrsRazorAHRS[id] = NULL;

	return EXIT_SUCCESS;
}

THREAD_PROC_RETURN_VALUE RazorAHRSThread(void* pParam)
{
	RAZORAHRS* pRazorAHRS = (RAZORAHRS*)pParam;
	int id = 0, res = EXIT_FAILURE, err = EXIT_SUCCESS;
	RAZORAHRSDATA razorahrsdata;

	while (addrsRazorAHRS[id] != pRazorAHRS)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return 0;
	}

	memset(&razorahrsdata, 0, sizeof(RAZORAHRSDATA));
	for (;;)
	{
		mSleep(pRazorAHRS->threadperiod);
		//memset(&razorahrsdata, 0, sizeof(RAZORAHRSDATA));
		res = GetLatestDataRazorAHRS(pRazorAHRS, &razorahrsdata);
		if (res != EXIT_SUCCESS) err = res;
		//if (GetLatestDataRazorAHRS(pRazorAHRS, &razorahrsdata) == EXIT_SUCCESS)
		{
			EnterCriticalSection(&RazorAHRSCS[id]);
			razorahrsdataRazorAHRS[id] = razorahrsdata;
			resRazorAHRS[id] = err;
			LeaveCriticalSection(&RazorAHRSCS[id]);
		}
		if (bExitRazorAHRS[id]) break;
	}

	return 0;
}

HARDWAREX_API int GetLatestDataFromThreadRazorAHRSx(RAZORAHRS* pRazorAHRS, RAZORAHRSDATA* pRazorAHRSData)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsRazorAHRS[id] != pRazorAHRS)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&RazorAHRSCS[id]);
	*pRazorAHRSData = razorahrsdataRazorAHRS[id];
	res = resRazorAHRS[id];
	LeaveCriticalSection(&RazorAHRSCS[id]);

	return res;
}

HARDWAREX_API int StartThreadRazorAHRSx(RAZORAHRS* pRazorAHRS)
{
	int id = 0;

	while (addrsRazorAHRS[id] != pRazorAHRS)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	resRazorAHRS[id] = EXIT_FAILURE;
	bExitRazorAHRS[id] = FALSE;
	memset(&razorahrsdataRazorAHRS, 0, sizeof(RAZORAHRSDATA));
	InitCriticalSection(&RazorAHRSCS[id]);
	return CreateDefaultThread(RazorAHRSThread, (void*)pRazorAHRS, &RazorAHRSThreadId[id]);
}

HARDWAREX_API int StopThreadRazorAHRSx(RAZORAHRS* pRazorAHRS)
{
	int id = 0;

	while (addrsRazorAHRS[id] != pRazorAHRS)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	bExitRazorAHRS[id] = TRUE;
	WaitForThread(RazorAHRSThreadId[id]);
	DeleteCriticalSection(&RazorAHRSCS[id]);
	resRazorAHRS[id] = EXIT_FAILURE;
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
	int id = 0, res = EXIT_FAILURE;

	while (addrsP33x[id] != NULL)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = ConnectP33x(pP33x, szCfgFilePath);
	if (res != EXIT_SUCCESS) return res;

	addrsP33x[id] = pP33x;

	return EXIT_SUCCESS;
}

HARDWAREX_API int DisconnectP33xx(P33X* pP33x)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsP33x[id] != pP33x)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = DisconnectP33x(pP33x);
	if (res != EXIT_SUCCESS) return res;

	addrsP33x[id] = NULL;

	return EXIT_SUCCESS;
}

THREAD_PROC_RETURN_VALUE P33xThread(void* pParam)
{
	P33X* pP33x = (P33X*)pParam;
	int id = 0, res = EXIT_FAILURE, err = EXIT_SUCCESS;
	double pressure = 0, temperature = 0;

	while (addrsP33x[id] != pP33x)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return 0;
	}

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
		EnterCriticalSection(&P33xCS[id]);
		pressureP33x[id] = pressure;
		temperatureP33x[id] = temperature;
		resP33x[id] = err;
		LeaveCriticalSection(&P33xCS[id]);
		if (bExitP33x[id]) break;
	}

	return 0;
}

HARDWAREX_API int GetPressureFromThreadP33xx(P33X* pP33x, double* pPressure)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsP33x[id] != pP33x)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&P33xCS[id]);
	*pPressure = pressureP33x[id];
	res = resP33x[id];
	LeaveCriticalSection(&P33xCS[id]);

	return res;
}

HARDWAREX_API int GetTemperatureFromThreadP33xx(P33X* pP33x, double* pTemperature)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsP33x[id] != pP33x)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&P33xCS[id]);
	*pTemperature = temperatureP33x[id];
	res = resP33x[id];
	LeaveCriticalSection(&P33xCS[id]);

	return res;
}

HARDWAREX_API int StartThreadP33xx(P33X* pP33x)
{
	int id = 0;

	while (addrsP33x[id] != pP33x)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	resP33x[id] = EXIT_FAILURE;
	bExitP33x[id] = FALSE;
	InitCriticalSection(&P33xCS[id]);
	return CreateDefaultThread(P33xThread, (void*)pP33x, &P33xThreadId[id]);
}

HARDWAREX_API int StopThreadP33xx(P33X* pP33x)
{
	int id = 0;

	while (addrsP33x[id] != pP33x)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	bExitP33x[id] = TRUE;
	WaitForThread(P33xThreadId[id]);
	DeleteCriticalSection(&P33xCS[id]);
	resP33x[id] = EXIT_FAILURE;
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
	int id = 0, res = EXIT_FAILURE;

	while (addrsNMEADevice[id] != NULL)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = ConnectNMEADevice(pNMEADevice, szCfgFilePath);
	if (res != EXIT_SUCCESS) return res;

	addrsNMEADevice[id] = pNMEADevice;

	return EXIT_SUCCESS;
}

HARDWAREX_API int DisconnectNMEADevicex(NMEADEVICE* pNMEADevice)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsNMEADevice[id] != pNMEADevice)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = DisconnectNMEADevice(pNMEADevice);
	if (res != EXIT_SUCCESS) return res;

	addrsNMEADevice[id] = NULL;

	return EXIT_SUCCESS;
}

THREAD_PROC_RETURN_VALUE NMEADeviceThread(void* pParam)
{
	NMEADEVICE* pNMEADevice = (NMEADEVICE*)pParam;
	int id = 0, res = EXIT_FAILURE, err = EXIT_SUCCESS;
	NMEADATA nmeadata;

	while (addrsNMEADevice[id] != pNMEADevice)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return 0;
	}

	memset(&nmeadata, 0, sizeof(NMEADATA));
	for (;;)
	{
		mSleep(pNMEADevice->threadperiod);
		memset(&nmeadata, 0, sizeof(NMEADATA));
		res = GetLatestDataNMEADevice(pNMEADevice, &nmeadata);
		if (res != EXIT_SUCCESS) err = res;
		EnterCriticalSection(&NMEADeviceCS[id]);
		nmeadataNMEADevice[id] = nmeadata;
		resNMEADevice[id] = err;
		LeaveCriticalSection(&NMEADeviceCS[id]);
		if (bExitNMEADevice[id]) break;
	}

	return 0;
}

HARDWAREX_API int GetLatestDataFromThreadNMEADevicex(NMEADEVICE* pNMEADevice, NMEADATA* pNMEAData)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsNMEADevice[id] != pNMEADevice)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&NMEADeviceCS[id]);
	*pNMEAData = nmeadataNMEADevice[id];
	res = resNMEADevice[id];
	LeaveCriticalSection(&NMEADeviceCS[id]);

	return res;
}

HARDWAREX_API int StartThreadNMEADevicex(NMEADEVICE* pNMEADevice)
{
	int id = 0;

	while (addrsNMEADevice[id] != pNMEADevice)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	resNMEADevice[id] = EXIT_FAILURE;
	bExitNMEADevice[id] = FALSE;
	InitCriticalSection(&NMEADeviceCS[id]);
	return CreateDefaultThread(NMEADeviceThread, (void*)pNMEADevice, &NMEADeviceThreadId[id]);
}

HARDWAREX_API int StopThreadNMEADevicex(NMEADEVICE* pNMEADevice)
{
	int id = 0;

	while (addrsNMEADevice[id] != pNMEADevice)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	bExitNMEADevice[id] = TRUE;
	WaitForThread(NMEADeviceThreadId[id]);
	DeleteCriticalSection(&NMEADeviceCS[id]);
	resNMEADevice[id] = EXIT_FAILURE;
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
	int id = 0, res = EXIT_FAILURE;

	while (addrsublox[id] != NULL)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = Connectublox(publox, szCfgFilePath);
	if (res != EXIT_SUCCESS) return res;

	addrsublox[id] = publox;

	return EXIT_SUCCESS;
}

HARDWAREX_API int Disconnectubloxx(UBLOX* publox)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsublox[id] != publox)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = Disconnectublox(publox);
	if (res != EXIT_SUCCESS) return res;

	addrsublox[id] = NULL;

	return EXIT_SUCCESS;
}

THREAD_PROC_RETURN_VALUE ubloxNMEAThread(void* pParam)
{
	UBLOX* publox = (UBLOX*)pParam;
	int id = 0, res = EXIT_FAILURE, err = EXIT_SUCCESS;
	NMEADATA nmeadata;

	while (addrsublox[id] != publox)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return 0;
	}

	memset(&nmeadata, 0, sizeof(NMEADATA));
	for (;;)
	{
		//mSleep(publox->threadperiod);
		//memset(&nmeadata, 0, sizeof(NMEADATA));
		res = GetNMEASentenceublox(publox, &nmeadata);
		if (res != EXIT_SUCCESS) err = res;
		//if (GetNMEASentenceublox(publox, &nmeadata) == EXIT_SUCCESS)
		{
			EnterCriticalSection(&ubloxCS[id]);
			nmeadataublox[id] = nmeadata;
			resublox[id] = err;
			LeaveCriticalSection(&ubloxCS[id]);
		}
		if (bExitNMEAublox[id]) break;
	}

	return 0;
}

THREAD_PROC_RETURN_VALUE ubloxUBXThread(void* pParam)
{
	UBLOX* publox = (UBLOX*)pParam;
	int id = 0, res = EXIT_FAILURE, err = EXIT_SUCCESS;
	UBXDATA ubxdata;

	while (addrsublox[id] != publox)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return 0;
	}

	memset(&ubxdata, 0, sizeof(UBXDATA));
	for (;;)
	{
		//mSleep(publox->threadperiod);
		//memset(&ubxdata, 0, sizeof(UBXDATA));
		res = GetUBXPacketublox(publox, &ubxdata);
		if (res != EXIT_SUCCESS) err = res;
		//if (GetUBXPacketublox(publox, &ubxdata) == EXIT_SUCCESS)
		{
			EnterCriticalSection(&ubloxCS[id]);
			ubxdataublox[id] = ubxdata;
			resublox[id] = err;
			LeaveCriticalSection(&ubloxCS[id]);
		}
		if (bExitUBXublox[id]) break;
	}

	return 0;
}

HARDWAREX_API int GetNMEASentenceFromThreadubloxx(UBLOX* publox, NMEADATA* pNMEAData)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsublox[id] != publox)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&ubloxCS[id]);
	*pNMEAData = nmeadataublox[id];
	res = resublox[id];
	LeaveCriticalSection(&ubloxCS[id]);

	return res;
}

HARDWAREX_API int GetUBXPacketFromThreadubloxx(UBLOX* publox, UBXDATA* pUBXData)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsublox[id] != publox)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&ubloxCS[id]);
	*pUBXData = ubxdataublox[id];
	res = resublox[id];
	LeaveCriticalSection(&ubloxCS[id]);

	return res;
}

HARDWAREX_API int StartNMEAThreadubloxx(UBLOX* publox)
{
	int id = 0;

	while (addrsublox[id] != publox)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	resublox[id] = EXIT_FAILURE;
	bExitNMEAublox[id] = FALSE;
	memset(&nmeadataublox, 0, sizeof(NMEADATA));
	InitCriticalSection(&ubloxCS[id]);
	return CreateDefaultThread(ubloxNMEAThread, (void*)publox, &ubloxNMEAThreadId[id]);
}

HARDWAREX_API int StopNMEAThreadubloxx(UBLOX* publox)
{
	int id = 0;

	while (addrsublox[id] != publox)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	bExitNMEAublox[id] = TRUE;
	WaitForThread(ubloxNMEAThreadId[id]);
	DeleteCriticalSection(&ubloxCS[id]);
	resublox[id] = EXIT_FAILURE;
	return EXIT_SUCCESS;
}

HARDWAREX_API int StartUBXThreadubloxx(UBLOX* publox)
{
	int id = 0;

	while (addrsublox[id] != publox)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	resublox[id] = EXIT_FAILURE;
	bExitUBXublox[id] = FALSE;
	memset(&ubxdataublox, 0, sizeof(UBXDATA));
	InitCriticalSection(&ubloxCS[id]);
	return CreateDefaultThread(ubloxUBXThread, (void*)publox, &ubloxUBXThreadId[id]);
}

HARDWAREX_API int StopUBXThreadubloxx(UBLOX* publox)
{
	int id = 0;

	while (addrsublox[id] != publox)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	bExitUBXublox[id] = TRUE;
	WaitForThread(ubloxUBXThreadId[id]);
	DeleteCriticalSection(&ubloxCS[id]);
	resublox[id] = EXIT_FAILURE;
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
	int id = 0, res = EXIT_FAILURE;

	while (addrsIM483I[id] != NULL)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = ConnectIM483I(pIM483I, szCfgFilePath);
	if (res != EXIT_SUCCESS) return res;

	addrsIM483I[id] = pIM483I;

	return EXIT_SUCCESS;
}

HARDWAREX_API int DisconnectIM483Ix(IM483I* pIM483I)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsIM483I[id] != pIM483I)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = DisconnectIM483I(pIM483I);
	if (res != EXIT_SUCCESS) return res;

	addrsIM483I[id] = NULL;

	return EXIT_SUCCESS;
}

THREAD_PROC_RETURN_VALUE IM483IThread(void* pParam)
{
	IM483I* pIM483I = (IM483I*)pParam;
	int id = 0, res = EXIT_FAILURE, err = EXIT_SUCCESS;
	double angle = 0;

	while (addrsIM483I[id] != pIM483I)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return 0;
	}

	mSleep(pIM483I->threadperiod);

	for (;;)
	{
		EnterCriticalSection(&IM483ICS[id]);
		angle = angleIM483I[id];
		LeaveCriticalSection(&IM483ICS[id]);
		res = SetMaxAngleIM483I(pIM483I, angle);
		if (res != EXIT_SUCCESS) err = res;
		mSleep(pIM483I->threadperiod);
		EnterCriticalSection(&IM483ICS[id]);
		resIM483I[id] = err;
		LeaveCriticalSection(&IM483ICS[id]);
		if (bExitIM483I[id]) break;
	}

	return 0;
}

HARDWAREX_API int SetMaxAngleFromThreadIM483Ix(IM483I* pIM483I, double angle)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsIM483I[id] != pIM483I)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&IM483ICS[id]);
	angleIM483I[id] = angle;
	res = resIM483I[id];
	LeaveCriticalSection(&IM483ICS[id]);

	return res;
}

HARDWAREX_API int StartThreadIM483Ix(IM483I* pIM483I)
{
	int id = 0;

	while (addrsIM483I[id] != pIM483I)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	resIM483I[id] = EXIT_FAILURE;
	bExitIM483I[id] = FALSE;
	InitCriticalSection(&IM483ICS[id]);
	return CreateDefaultThread(IM483IThread, (void*)pIM483I, &IM483IThreadId[id]);
}

HARDWAREX_API int StopThreadIM483Ix(IM483I* pIM483I)
{
	int id = 0;

	while (addrsIM483I[id] != pIM483I)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	bExitIM483I[id] = TRUE;
	WaitForThread(IM483IThreadId[id]);
	DeleteCriticalSection(&IM483ICS[id]);
	resIM483I[id] = EXIT_FAILURE;
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
	int id = 0, res = EXIT_FAILURE;

	while (addrsSSC32[id] != NULL)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = ConnectSSC32(pSSC32, szCfgFilePath);
	if (res != EXIT_SUCCESS) return res;

	addrsSSC32[id] = pSSC32;

	return EXIT_SUCCESS;
}

HARDWAREX_API int DisconnectSSC32x(SSC32* pSSC32)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsSSC32[id] != pSSC32)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = DisconnectSSC32(pSSC32);
	if (res != EXIT_SUCCESS) return res;

	addrsSSC32[id] = NULL;

	return EXIT_SUCCESS;
}

THREAD_PROC_RETURN_VALUE SSC32Thread(void* pParam)
{
	SSC32* pSSC32 = (SSC32*)pParam;
	int id = 0, res = EXIT_FAILURE, err = EXIT_SUCCESS;
	int selectedchannels[NB_CHANNELS_PWM_SSC32];
	int pws[NB_CHANNELS_PWM_SSC32];

	while (addrsSSC32[id] != pSSC32)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return 0;
	}

	mSleep(pSSC32->threadperiod);

	for (;;)
	{
		EnterCriticalSection(&SSC32CS[id]);
		memcpy(selectedchannels, selectedchannelsSSC32[id], NB_CHANNELS_PWM_SSC32*sizeof(int));
		memcpy(pws, pwsSSC32[id], NB_CHANNELS_PWM_SSC32*sizeof(int));
		LeaveCriticalSection(&SSC32CS[id]);
		res = SetAllPWMsSSC32(pSSC32, selectedchannels, pws);
		if (res != EXIT_SUCCESS) err = res;
		mSleep(pSSC32->threadperiod);
		EnterCriticalSection(&SSC32CS[id]);
		resSSC32[id] = err;
		LeaveCriticalSection(&SSC32CS[id]);
		if (bExitSSC32[id]) break;
	}

	return 0;
}

HARDWAREX_API int SetAllPWMsFromThreadSSC32x(SSC32* pSSC32, int* selectedchannels, int* pws)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsSSC32[id] != pSSC32)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&SSC32CS[id]);
	memcpy(selectedchannelsSSC32[id], selectedchannels, NB_CHANNELS_PWM_SSC32*sizeof(int));
	memcpy(pwsSSC32[id], pws, NB_CHANNELS_PWM_SSC32*sizeof(int));
	res = resSSC32[id];
	LeaveCriticalSection(&SSC32CS[id]);

	return res;
}

HARDWAREX_API int StartThreadSSC32x(SSC32* pSSC32)
{
	int id = 0;

	while (addrsSSC32[id] != pSSC32)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	resSSC32[id] = EXIT_FAILURE;
	bExitSSC32[id] = FALSE;
	InitCriticalSection(&SSC32CS[id]);
	return CreateDefaultThread(SSC32Thread, (void*)pSSC32, &SSC32ThreadId[id]);
}

HARDWAREX_API int StopThreadSSC32x(SSC32* pSSC32)
{
	int id = 0;

	while (addrsSSC32[id] != pSSC32)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	bExitSSC32[id] = TRUE;
	WaitForThread(SSC32ThreadId[id]);
	DeleteCriticalSection(&SSC32CS[id]);
	resSSC32[id] = EXIT_FAILURE;
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
	int id = 0, res = EXIT_FAILURE;

	while (addrsPololu[id] != NULL)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = ConnectPololu(pPololu, szCfgFilePath);
	if (res != EXIT_SUCCESS) return res;

	addrsPololu[id] = pPololu;

	return EXIT_SUCCESS;
}

HARDWAREX_API int DisconnectPololux(POLOLU* pPololu)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsPololu[id] != pPololu)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = DisconnectPololu(pPololu);
	if (res != EXIT_SUCCESS) return res;

	addrsPololu[id] = NULL;

	return EXIT_SUCCESS;
}

THREAD_PROC_RETURN_VALUE PololuThread(void* pParam)
{
	POLOLU* pPololu = (POLOLU*)pParam;
	int id = 0, res = EXIT_FAILURE, err = EXIT_SUCCESS;
	int selectedchannels[NB_CHANNELS_PWM_POLOLU];
	int pws[NB_CHANNELS_PWM_POLOLU];
	int value = 0;

	while (addrsPololu[id] != pPololu)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return 0;
	}

	memset(valuesPololu, 0, NB_CHANNELS_POLOLU*sizeof(int));
	
	mSleep(pPololu->threadperiod);

	for (;;)
	{
		EnterCriticalSection(&PololuCS[id]);
		memcpy(selectedchannels, selectedchannelsPololu[id], NB_CHANNELS_PWM_POLOLU*sizeof(int));
		memcpy(pws, pwsPololu[id], NB_CHANNELS_PWM_POLOLU*sizeof(int));
		LeaveCriticalSection(&PololuCS[id]);
		res = SetAllPWMsPololu(pPololu, selectedchannels, pws);
		if (res != EXIT_SUCCESS) err = res;
		mSleep(10);
		if (pPololu->winddiranaloginputchan != -1)
		{
			value = 0;
			res = GetValuePololu(pPololu, pPololu->winddiranaloginputchan, &value);
			if (res != EXIT_SUCCESS) err = res;
			mSleep(10);
			EnterCriticalSection(&PololuCS[id]);
			valuesPololu[id][pPololu->winddiranaloginputchan] = value;
			resPololu[id] = err;
			LeaveCriticalSection(&PololuCS[id]);
		}
		//else mSleep(10);
		if (pPololu->windspeedanaloginputchan != -1)
		{
			value = 0;
			res = GetValuePololu(pPololu, pPololu->windspeedanaloginputchan, &value);
			if (res != EXIT_SUCCESS) err = res;
			mSleep(10);
			EnterCriticalSection(&PololuCS[id]);
			valuesPololu[id][pPololu->windspeedanaloginputchan] = value;
			resPololu[id] = err;
			LeaveCriticalSection(&PololuCS[id]);
		}
		//else mSleep(10);
		if (pPololu->vbat1analoginputchan != -1)
		{
			value = 0;
			res = GetValuePololu(pPololu, pPololu->vbat1analoginputchan, &value);
			if (res != EXIT_SUCCESS) err = res;
			mSleep(10);
			EnterCriticalSection(&PololuCS[id]);
			valuesPololu[id][pPololu->vbat1analoginputchan] = value;
			resPololu[id] = err;
			LeaveCriticalSection(&PololuCS[id]);
		}
		//else mSleep(10);
		if (pPololu->ibat1analoginputchan != -1)
		{
			value = 0;
			res = GetValuePololu(pPololu, pPololu->ibat1analoginputchan, &value);
			if (res != EXIT_SUCCESS) err = res;
			mSleep(10);
			EnterCriticalSection(&PololuCS[id]);
			valuesPololu[id][pPololu->ibat1analoginputchan] = value;
			resPololu[id] = err;
			LeaveCriticalSection(&PololuCS[id]);
		}
		//else mSleep(10);
		if (pPololu->vbat2analoginputchan != -1)
		{
			value = 0;
			res = GetValuePololu(pPololu, pPololu->vbat2analoginputchan, &value);
			if (res != EXIT_SUCCESS) err = res;
			mSleep(10);
			EnterCriticalSection(&PololuCS[id]);
			valuesPololu[id][pPololu->vbat2analoginputchan] = value;
			resPololu[id] = err;
			LeaveCriticalSection(&PololuCS[id]);
		}
		//else mSleep(10);
		if (pPololu->ibat2analoginputchan != -1)
		{
			value = 0;
			res = GetValuePololu(pPololu, pPololu->ibat2analoginputchan, &value);
			if (res != EXIT_SUCCESS) err = res;
			mSleep(10);
			EnterCriticalSection(&PololuCS[id]);
			valuesPololu[id][pPololu->ibat2analoginputchan] = value;
			resPololu[id] = err;
			LeaveCriticalSection(&PololuCS[id]);
		}
		//else mSleep(10);
		if (pPololu->switchanaloginputchan != -1)
		{
			value = 0;
			res = GetValuePololu(pPololu, pPololu->switchanaloginputchan, &value);
			if (res != EXIT_SUCCESS) err = res;
			mSleep(10);
			EnterCriticalSection(&PololuCS[id]);
			valuesPololu[id][pPololu->switchanaloginputchan] = value;
			resPololu[id] = err;
			LeaveCriticalSection(&PololuCS[id]);
		}
		//else mSleep(10);
		EnterCriticalSection(&PololuCS[id]);
		resPololu[id] = err;
		LeaveCriticalSection(&PololuCS[id]);
		if (bExitPololu[id]) break;
	}

	return 0;
}

HARDWAREX_API int SetAllPWMsFromThreadPololux(POLOLU* pPololu, int* selectedchannels, int* pws)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsPololu[id] != pPololu)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&PololuCS[id]);
	memcpy(selectedchannelsPololu[id], selectedchannels, NB_CHANNELS_PWM_POLOLU*sizeof(int));
	memcpy(pwsPololu[id], pws, NB_CHANNELS_PWM_POLOLU*sizeof(int));
	res = resPololu[id];
	LeaveCriticalSection(&PololuCS[id]);

	return res;
}

HARDWAREX_API int GetValueFromThreadPololux(POLOLU* pPololu, int channel, int* pValue)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsPololu[id] != pPololu)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&PololuCS[id]);
	if ((channel >= 0)&&(channel < NB_CHANNELS_POLOLU)) *pValue = valuesPololu[id][channel];
	res = resPololu[id];
	LeaveCriticalSection(&PololuCS[id]);

	return res;
}

HARDWAREX_API int StartThreadPololux(POLOLU* pPololu)
{
	int id = 0;

	while (addrsPololu[id] != pPololu)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	resPololu[id] = EXIT_FAILURE;
	bExitPololu[id] = FALSE;
	InitCriticalSection(&PololuCS[id]);
	return CreateDefaultThread(PololuThread, (void*)pPololu, &PololuThreadId[id]);
}

HARDWAREX_API int StopThreadPololux(POLOLU* pPololu)
{
	int id = 0;

	while (addrsPololu[id] != pPololu)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	bExitPololu[id] = TRUE;
	WaitForThread(PololuThreadId[id]);
	DeleteCriticalSection(&PololuCS[id]);
	resPololu[id] = EXIT_FAILURE;
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
	int id = 0, res = EXIT_FAILURE;

	while (addrsHokuyo[id] != NULL)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = ConnectHokuyo(pHokuyo, szCfgFilePath);
	if (res != EXIT_SUCCESS) return res;

	addrsHokuyo[id] = pHokuyo;

	return EXIT_SUCCESS;
}

HARDWAREX_API int DisconnectHokuyox(HOKUYO* pHokuyo)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsHokuyo[id] != pHokuyo)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = DisconnectHokuyo(pHokuyo);
	if (res != EXIT_SUCCESS) return res;

	addrsHokuyo[id] = NULL;

	return EXIT_SUCCESS;
}

THREAD_PROC_RETURN_VALUE HokuyoThread(void* pParam)
{
	HOKUYO* pHokuyo = (HOKUYO*)pParam;
	int id = 0, res = EXIT_FAILURE, err = EXIT_SUCCESS;
	double angles[MAX_SLITDIVISION_HOKUYO];
	double distances[MAX_SLITDIVISION_HOKUYO];

	while (addrsHokuyo[id] != pHokuyo)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return 0;
	}

	for (;;)
	{
		//mSleep(pHokuyo->threadperiod);
		memset(distances, 0, MAX_SLITDIVISION_HOKUYO*sizeof(double));
		memset(angles, 0, MAX_SLITDIVISION_HOKUYO*sizeof(double));
		res = GetLatestDataHokuyo(pHokuyo, distances, angles);
		if (res != EXIT_SUCCESS) err = res;
		// if (GetLatestDataHokuyo(pHokuyo, distances, angles) == EXIT8SUCCESS)
		{
			EnterCriticalSection(&HokuyoCS[id]);
			memcpy(distancesHokuyo[id], distances, MAX_SLITDIVISION_HOKUYO*sizeof(double));
			memcpy(anglesHokuyo[id], angles, MAX_SLITDIVISION_HOKUYO*sizeof(double));
			resHokuyo[id] = err;
			LeaveCriticalSection(&HokuyoCS[id]);
		}
		if (bExitHokuyo[id]) break;
	}

	return 0;
}

HARDWAREX_API int GetLatestDataFromThreadHokuyox(HOKUYO* pHokuyo, double* pDistances, double* pAngles)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsHokuyo[id] != pHokuyo)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&HokuyoCS[id]);
	memcpy(pDistances, distancesHokuyo[id], MAX_SLITDIVISION_HOKUYO*sizeof(double));
	memcpy(pAngles, anglesHokuyo[id], MAX_SLITDIVISION_HOKUYO*sizeof(double));
	res = resHokuyo[id];
	LeaveCriticalSection(&HokuyoCS[id]);

	return res;
}

HARDWAREX_API int StartThreadHokuyox(HOKUYO* pHokuyo)
{
	int id = 0;

	while (addrsHokuyo[id] != pHokuyo)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	resHokuyo[id] = EXIT_FAILURE;
	bExitHokuyo[id] = FALSE;
	InitCriticalSection(&HokuyoCS[id]);
	return CreateDefaultThread(HokuyoThread, (void*)pHokuyo, &HokuyoThreadId[id]);
}

HARDWAREX_API int StopThreadHokuyox(HOKUYO* pHokuyo)
{
	int id = 0;

	while (addrsHokuyo[id] != pHokuyo)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	bExitHokuyo[id] = TRUE;
	WaitForThread(HokuyoThreadId[id]);
	DeleteCriticalSection(&HokuyoCS[id]);
	resHokuyo[id] = EXIT_FAILURE;
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
	int id = 0, res = EXIT_FAILURE;

	while (addrsRPLIDAR[id] != NULL)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = ConnectRPLIDAR(pRPLIDAR, szCfgFilePath);
	if (res != EXIT_SUCCESS) return res;

#ifdef __cplusplus
	anglesvectorRPLIDAR[id] = std::deque<double>();
	distancesvectorRPLIDAR[id] = std::deque<double>();
#endif // __cplusplus

	addrsRPLIDAR[id] = pRPLIDAR;

	return EXIT_SUCCESS;
}

HARDWAREX_API int DisconnectRPLIDARx(RPLIDAR* pRPLIDAR)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsRPLIDAR[id] != pRPLIDAR)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

#ifdef __cplusplus
	anglesvectorRPLIDAR[id] = std::deque<double>();
	distancesvectorRPLIDAR[id] = std::deque<double>();
#endif // __cplusplus

	res = DisconnectRPLIDAR(pRPLIDAR);
	if (res != EXIT_SUCCESS) return res;

	addrsRPLIDAR[id] = NULL;

	return EXIT_SUCCESS;
}

THREAD_PROC_RETURN_VALUE RPLIDARScanThread(void* pParam)
{
	RPLIDAR* pRPLIDAR = (RPLIDAR*)pParam;
	int id = 0, res = EXIT_FAILURE, err = EXIT_SUCCESS;
	double angle = 0;
	double distance = 0;
	BOOL bNewScan = FALSE, bAutoNewScan = FALSE;
	int quality = 0, j = 0, nb = 0, nbprev = 0;

	while (addrsRPLIDAR[id] != pRPLIDAR)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return 0;
	}

#ifdef __cplusplus
	EnterCriticalSection(&RPLIDARCS[id]);
	anglesvectorRPLIDAR[id] = std::deque<double>();
	distancesvectorRPLIDAR[id] = std::deque<double>();
	LeaveCriticalSection(&RPLIDARCS[id]);
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
			EnterCriticalSection(&RPLIDARCS[id]);
			distanceRPLIDAR[id] = distance;
			angleRPLIDAR[id] = angle;
			bNewScanRPLIDAR[id] = bNewScan;
			qualityRPLIDAR[id] = quality;

#ifdef __cplusplus
			if (pRPLIDAR->maxhist == 0)
			{
				// Try to detect the beginning of a new scan with the angle discontinuity...
				// Try to be a little bit robust w.r.t. non-decreasing outliers...
				if (((int)anglesvectorRPLIDAR[id].size() >= 5)&&
					((angle-anglesvectorRPLIDAR[id][(int)anglesvectorRPLIDAR[id].size()-5]) > M_PI)&&
					((angle-anglesvectorRPLIDAR[id][(int)anglesvectorRPLIDAR[id].size()-4]) > M_PI)&&
					((angle-anglesvectorRPLIDAR[id][(int)anglesvectorRPLIDAR[id].size()-3]) > M_PI)&&
					((angle-anglesvectorRPLIDAR[id][(int)anglesvectorRPLIDAR[id].size()-2]) > M_PI)&&
					((angle-anglesvectorRPLIDAR[id][(int)anglesvectorRPLIDAR[id].size()-1]) > M_PI))
					bAutoNewScan = TRUE; else bAutoNewScan = FALSE;
				if (bAutoNewScan)
				{
					// Try to automatically remove old data...
					for (j = nbprev-nb-1; j >= 0; j--)
					{
						if ((int)anglesvectorRPLIDAR[id].size() > 0)
						{
							anglesvectorRPLIDAR[id].pop_front();
							distancesvectorRPLIDAR[id].pop_front();
						}
					}
					nbprev = nb;
					nb = 0;
				}
			}

			anglesvectorRPLIDAR[id].push_back(angle);
			distancesvectorRPLIDAR[id].push_back(distance);

			if (pRPLIDAR->maxhist == 0)
			{
				// Try to automatically remove old data...
				nb++;
				if ((nb <= nbprev)&&((int)anglesvectorRPLIDAR[id].size() > 0))
				{
					anglesvectorRPLIDAR[id].pop_front();
					distancesvectorRPLIDAR[id].pop_front();
				}
			}
			if (((pRPLIDAR->maxhist > 0)&&((int)anglesvectorRPLIDAR[id].size() > pRPLIDAR->maxhist))||
				((int)anglesvectorRPLIDAR[id].size() > MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR))
			{
				anglesvectorRPLIDAR[id].pop_front();
				distancesvectorRPLIDAR[id].pop_front();
			}
#endif // __cplusplus

			resRPLIDAR[id] = err;
			LeaveCriticalSection(&RPLIDARCS[id]);
		}
		if (bExitScanRPLIDAR[id]) break;
	}

	return 0;
}

THREAD_PROC_RETURN_VALUE RPLIDARExpressScanThread(void* pParam)
{
	RPLIDAR* pRPLIDAR = (RPLIDAR*)pParam;
	int id = 0, res = EXIT_FAILURE, err = EXIT_SUCCESS;
	double angles[NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR];
	double distances[NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR];
	BOOL bNewScan = FALSE, bAutoNewScan = FALSE;
	int i = 0, j = 0, nb = 0, nbprev = 0;

	while (addrsRPLIDAR[id] != pRPLIDAR)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return 0;
	}

#ifdef __cplusplus
	EnterCriticalSection(&RPLIDARCS[id]);
	anglesvectorRPLIDAR[id] = std::deque<double>();
	distancesvectorRPLIDAR[id] = std::deque<double>();
	LeaveCriticalSection(&RPLIDARCS[id]);
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
			EnterCriticalSection(&RPLIDARCS[id]);
			memcpy(distancesRPLIDAR[id], distances, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
			memcpy(anglesRPLIDAR[id], angles, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
			bNewScanRPLIDAR[id] = bNewScan;

#ifdef __cplusplus
			for (i = 0; i < NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR; i++)
			{
				if (pRPLIDAR->maxhist == 0)
				{
					// Try to detect the beginning of a new scan with the angle discontinuity...
					// Try to be a little bit robust w.r.t. non-decreasing outliers...
					if (((int)anglesvectorRPLIDAR[id].size() >= 5)&&
						((angles[i]-anglesvectorRPLIDAR[id][(int)anglesvectorRPLIDAR[id].size()-5]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[id][(int)anglesvectorRPLIDAR[id].size()-4]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[id][(int)anglesvectorRPLIDAR[id].size()-3]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[id][(int)anglesvectorRPLIDAR[id].size()-2]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[id][(int)anglesvectorRPLIDAR[id].size()-1]) > M_PI))
						bAutoNewScan = TRUE; else bAutoNewScan = FALSE;
					if (bAutoNewScan)
					{
						// Try to automatically remove old data...
						for (j = nbprev-nb-1; j >= 0; j--)
						{
							if ((int)anglesvectorRPLIDAR[id].size() > 0)
							{
								anglesvectorRPLIDAR[id].pop_front();
								distancesvectorRPLIDAR[id].pop_front();
							}
						}
						nbprev = nb;
						nb = 0;
					}
				}

				anglesvectorRPLIDAR[id].push_back(angles[i]);
				distancesvectorRPLIDAR[id].push_back(distances[i]);

				if (pRPLIDAR->maxhist == 0)
				{
					// Try to automatically remove old data...
					nb++;
					if ((nb <= nbprev)&&((int)anglesvectorRPLIDAR[id].size() > 0))
					{
						anglesvectorRPLIDAR[id].pop_front();
						distancesvectorRPLIDAR[id].pop_front();
					}
				}
				if (((pRPLIDAR->maxhist > 0)&&((int)anglesvectorRPLIDAR[id].size() > pRPLIDAR->maxhist))||
					((int)anglesvectorRPLIDAR[id].size() > MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR))
				{
					anglesvectorRPLIDAR[id].pop_front();
					distancesvectorRPLIDAR[id].pop_front();
				}
			}
#endif // __cplusplus

			resRPLIDAR[id] = err;
			LeaveCriticalSection(&RPLIDARCS[id]);
		}
		if (bExitExpressScanRPLIDAR[id]) break;
	}

	return 0;
}

THREAD_PROC_RETURN_VALUE RPLIDAROtherScanThread(void* pParam)
{
	RPLIDAR* pRPLIDAR = (RPLIDAR*)pParam;
	int id = 0, res = EXIT_FAILURE, err = EXIT_SUCCESS;
	int nbMeasurements = NB_MEASUREMENTS_OTHER_SCAN_DATA_RESPONSE_RPLIDAR;
	double angles[MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR];
	double distances[MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR];
	BOOL bNewScan = FALSE, bAutoNewScan = FALSE;
	int i = 0, j = 0, nb = 0, nbprev = 0;

	while (addrsRPLIDAR[id] != pRPLIDAR)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return 0;
	}

#ifdef __cplusplus
	EnterCriticalSection(&RPLIDARCS[id]);
	anglesvectorRPLIDAR[id] = std::deque<double>();
	distancesvectorRPLIDAR[id] = std::deque<double>();
	LeaveCriticalSection(&RPLIDARCS[id]);
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
			EnterCriticalSection(&RPLIDARCS[id]);
			nbMeasurementsRPLIDAR[id] = nbMeasurements;
			memcpy(distancesRPLIDAR[id], distances, nbMeasurements*sizeof(double));
			memcpy(anglesRPLIDAR[id], angles, nbMeasurements*sizeof(double));
			bNewScanRPLIDAR[id] = bNewScan;

#ifdef __cplusplus
			for (i = 0; i < nbMeasurements; i++)
			{
				if (pRPLIDAR->maxhist == 0)
				{
					// Try to detect the beginning of a new scan with the angle discontinuity...
					// Try to be a little bit robust w.r.t. non-decreasing outliers...
					if (((int)anglesvectorRPLIDAR[id].size() >= 5)&&
						((angles[i]-anglesvectorRPLIDAR[id][(int)anglesvectorRPLIDAR[id].size()-5]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[id][(int)anglesvectorRPLIDAR[id].size()-4]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[id][(int)anglesvectorRPLIDAR[id].size()-3]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[id][(int)anglesvectorRPLIDAR[id].size()-2]) > M_PI)&&
						((angles[i]-anglesvectorRPLIDAR[id][(int)anglesvectorRPLIDAR[id].size()-1]) > M_PI))
						bAutoNewScan = TRUE; else bAutoNewScan = FALSE;
					if (bAutoNewScan)
					{
						// Try to automatically remove old data...
						for (j = nbprev-nb-1; j >= 0; j--)
						{
							if ((int)anglesvectorRPLIDAR[id].size() > 0)
							{
								anglesvectorRPLIDAR[id].pop_front();
								distancesvectorRPLIDAR[id].pop_front();
							}
						}
						nbprev = nb;
						nb = 0;
					}
				}

				anglesvectorRPLIDAR[id].push_back(angles[i]);
				distancesvectorRPLIDAR[id].push_back(distances[i]);

				if (pRPLIDAR->maxhist == 0)
				{
					// Try to automatically remove old data...
					nb++;
					if ((nb <= nbprev)&&((int)anglesvectorRPLIDAR[id].size() > 0))
					{
						anglesvectorRPLIDAR[id].pop_front();
						distancesvectorRPLIDAR[id].pop_front();
					}
				}
				if (((pRPLIDAR->maxhist > 0)&&((int)anglesvectorRPLIDAR[id].size() > pRPLIDAR->maxhist))||
					((int)anglesvectorRPLIDAR[id].size() > MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR))
				{
					anglesvectorRPLIDAR[id].pop_front();
					distancesvectorRPLIDAR[id].pop_front();
				}
			}
#endif // __cplusplus

			resRPLIDAR[id] = err;
			LeaveCriticalSection(&RPLIDARCS[id]);
		}
		if (bExitOtherScanRPLIDAR[id]) break;
	}

	return 0;
}

HARDWAREX_API int GetScanDataResponseFromThreadRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistance, double* pAngle, BOOL* pbNewScan, int *pQuality)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsRPLIDAR[id] != pRPLIDAR)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&RPLIDARCS[id]);
	*pDistance = distanceRPLIDAR[id];
	*pAngle = angleRPLIDAR[id];
	*pbNewScan = bNewScanRPLIDAR[id];
	*pQuality = qualityRPLIDAR[id];
	res = resRPLIDAR[id];
	LeaveCriticalSection(&RPLIDARCS[id]);

	return res;
}

HARDWAREX_API int GetExpressScanDataResponseFromThreadRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistances, double* pAngles, BOOL* pbNewScan)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsRPLIDAR[id] != pRPLIDAR)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&RPLIDARCS[id]);
	memcpy(pDistances, distancesRPLIDAR[id], NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
	memcpy(pAngles, anglesRPLIDAR[id], NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR*sizeof(double));
	*pbNewScan = bNewScanRPLIDAR[id];
	res = resRPLIDAR[id];
	LeaveCriticalSection(&RPLIDARCS[id]);

	return res;
}

HARDWAREX_API int GetOtherScanDataResponseFromThreadRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistances, double* pAngles, BOOL* pbNewScan, int* pNbMeasurements)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsRPLIDAR[id] != pRPLIDAR)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&RPLIDARCS[id]);
	*pNbMeasurements = nbMeasurementsRPLIDAR[id];
	memcpy(pDistances, distancesRPLIDAR[id], nbMeasurementsRPLIDAR[id]*sizeof(double));
	memcpy(pAngles, anglesRPLIDAR[id], nbMeasurementsRPLIDAR[id]*sizeof(double));
	*pbNewScan = bNewScanRPLIDAR[id];
	res = resRPLIDAR[id];
	LeaveCriticalSection(&RPLIDARCS[id]);

	return res;
}

HARDWAREX_API int GetLast360DataFromThreadRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistances, double* pAngles, int* pNbMeasurements)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsRPLIDAR[id] != pRPLIDAR)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

#ifdef __cplusplus
	EnterCriticalSection(&RPLIDARCS[id]);
	*pNbMeasurements = (int)anglesvectorRPLIDAR[id].size();
	for (int i = *pNbMeasurements-1; i >= 0; i--)
	{
		pAngles[i] = anglesvectorRPLIDAR[id][i];
		pDistances[i] = distancesvectorRPLIDAR[id][i];
	}
	res = resRPLIDAR[id];
	LeaveCriticalSection(&RPLIDARCS[id]);

	if (*pNbMeasurements <= 0) return EXIT_TIMEOUT;
	return res;
#else
	return EXIT_NOT_IMPLEMENTED;
#endif // __cplusplus
}

HARDWAREX_API int StartScanThreadRPLIDARx(RPLIDAR* pRPLIDAR)
{
	int id = 0;

	while (addrsRPLIDAR[id] != pRPLIDAR)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	resRPLIDAR[id] = EXIT_FAILURE;
	bExitScanRPLIDAR[id] = FALSE;
	InitCriticalSection(&RPLIDARCS[id]);
	return CreateDefaultThread(RPLIDARScanThread, (void*)pRPLIDAR, &RPLIDARScanThreadId[id]);
}

HARDWAREX_API int StopScanThreadRPLIDARx(RPLIDAR* pRPLIDAR)
{
	int id = 0;

	while (addrsRPLIDAR[id] != pRPLIDAR)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	bExitScanRPLIDAR[id] = TRUE;
	WaitForThread(RPLIDARScanThreadId[id]);
	DeleteCriticalSection(&RPLIDARCS[id]);
	resRPLIDAR[id] = EXIT_FAILURE;
	return EXIT_SUCCESS;
}

HARDWAREX_API int StartExpressScanThreadRPLIDARx(RPLIDAR* pRPLIDAR)
{
	int id = 0;

	while (addrsRPLIDAR[id] != pRPLIDAR)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	resRPLIDAR[id] = EXIT_FAILURE;
	bExitExpressScanRPLIDAR[id] = FALSE;
	InitCriticalSection(&RPLIDARCS[id]);
	return CreateDefaultThread(RPLIDARExpressScanThread, (void*)pRPLIDAR, &RPLIDARExpressScanThreadId[id]);
}

HARDWAREX_API int StopExpressScanThreadRPLIDARx(RPLIDAR* pRPLIDAR)
{
	int id = 0;

	while (addrsRPLIDAR[id] != pRPLIDAR)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	bExitExpressScanRPLIDAR[id] = TRUE;
	WaitForThread(RPLIDARExpressScanThreadId[id]);
	DeleteCriticalSection(&RPLIDARCS[id]);
	resRPLIDAR[id] = EXIT_FAILURE;
	return EXIT_SUCCESS;
}

HARDWAREX_API int StartOtherScanThreadRPLIDARx(RPLIDAR* pRPLIDAR)
{
	int id = 0;

	while (addrsRPLIDAR[id] != pRPLIDAR)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	resRPLIDAR[id] = EXIT_FAILURE;
	bExitOtherScanRPLIDAR[id] = FALSE;
	InitCriticalSection(&RPLIDARCS[id]);
	return CreateDefaultThread(RPLIDAROtherScanThread, (void*)pRPLIDAR, &RPLIDAROtherScanThreadId[id]);
}

HARDWAREX_API int StopOtherScanThreadRPLIDARx(RPLIDAR* pRPLIDAR)
{
	int id = 0;

	while (addrsRPLIDAR[id] != pRPLIDAR)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	bExitOtherScanRPLIDAR[id] = TRUE;
	WaitForThread(RPLIDAROtherScanThreadId[id]);
	DeleteCriticalSection(&RPLIDARCS[id]);
	resRPLIDAR[id] = EXIT_FAILURE;
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
	int id = 0, res = EXIT_FAILURE;

	while (addrsMAVLinkDevice[id] != NULL)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = ConnectMAVLinkDevice(pMAVLinkDevice, szCfgFilePath);
	if (res != EXIT_SUCCESS) return res;

	addrsMAVLinkDevice[id] = pMAVLinkDevice;

	return EXIT_SUCCESS;
}

HARDWAREX_API int DisconnectMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsMAVLinkDevice[id] != pMAVLinkDevice)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	res = DisconnectMAVLinkDevice(pMAVLinkDevice);
	if (res != EXIT_SUCCESS) return res;

	addrsMAVLinkDevice[id] = NULL;

	return EXIT_SUCCESS;
}

THREAD_PROC_RETURN_VALUE MAVLinkDeviceThread(void* pParam)
{
	MAVLINKDEVICE* pMAVLinkDevice = (MAVLINKDEVICE*)pParam;
	int id = 0, res = EXIT_FAILURE, err = EXIT_SUCCESS;
	int selectedchannels[NB_CHANNELS_PWM_MAVLINKDEVICE];
	int pws[NB_CHANNELS_PWM_MAVLINKDEVICE];
	MAVLINKDATA mavlinkdata;

	while (addrsMAVLinkDevice[id] != pMAVLinkDevice)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return 0;
	}

	memset(&mavlinkdata, 0, sizeof(MAVLINKDATA));
	for (;;)
	{
		uSleep(1000*pMAVLinkDevice->threadperiod/2);
		EnterCriticalSection(&MAVLinkDeviceCS[id]);
		memcpy(selectedchannels, selectedchannelsMAVLinkDevice[id], NB_CHANNELS_PWM_MAVLINKDEVICE*sizeof(int));
		memcpy(pws, pwsMAVLinkDevice[id], NB_CHANNELS_PWM_MAVLINKDEVICE*sizeof(int));
		LeaveCriticalSection(&MAVLinkDeviceCS[id]);
		res = SetAllPWMsMAVLinkDevice(pMAVLinkDevice, selectedchannels, pws);
		if (res != EXIT_SUCCESS) err = res;
		uSleep(1000*pMAVLinkDevice->threadperiod/2);
		//memset(&mavlinkdata, 0, sizeof(MAVLINKDATA));
		res = GetLatestDataMAVLinkDevice(pMAVLinkDevice, &mavlinkdata);
		if (res != EXIT_SUCCESS) err = res;
		//if (GetLatestDataMAVLinkDevice(pMAVLinkDevice, &mavlinkdata) == EXIT_SUCCESS)
		{
			EnterCriticalSection(&MAVLinkDeviceCS[id]);
			mavlinkdataMAVLinkDevice[id] = mavlinkdata;
			resMAVLinkDevice[id] = err;
			LeaveCriticalSection(&MAVLinkDeviceCS[id]);
		}
		if (bExitMAVLinkDevice[id]) break;
	}

	return 0;
}

HARDWAREX_API int SetAllPWMsFromThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice, int* selectedchannels, int* pws)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsMAVLinkDevice[id] != pMAVLinkDevice)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&MAVLinkDeviceCS[id]);
	memcpy(selectedchannelsMAVLinkDevice[id], selectedchannels, NB_CHANNELS_PWM_MAVLINKDEVICE*sizeof(int));
	memcpy(pwsMAVLinkDevice[id], pws, NB_CHANNELS_PWM_MAVLINKDEVICE*sizeof(int));
	res = resMAVLinkDevice[id];
	LeaveCriticalSection(&MAVLinkDeviceCS[id]);

	return res;
}

HARDWAREX_API int GetLatestDataFromThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice, MAVLINKDATA* pMAVLinkData)
{
	int id = 0, res = EXIT_FAILURE;

	while (addrsMAVLinkDevice[id] != pMAVLinkDevice)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	EnterCriticalSection(&MAVLinkDeviceCS[id]);
	*pMAVLinkData = mavlinkdataMAVLinkDevice[id];
	res = resMAVLinkDevice[id];
	LeaveCriticalSection(&MAVLinkDeviceCS[id]);

	return res;
}

HARDWAREX_API int StartThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice)
{
	int id = 0;

	while (addrsMAVLinkDevice[id] != pMAVLinkDevice)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	resMAVLinkDevice[id] = EXIT_FAILURE;
	bExitMAVLinkDevice[id] = FALSE;
	memset(&mavlinkdataMAVLinkDevice, 0, sizeof(MAVLINKDATA));
	InitCriticalSection(&MAVLinkDeviceCS[id]);
	return CreateDefaultThread(MAVLinkDeviceThread, (void*)pMAVLinkDevice, &MAVLinkDeviceThreadId[id]);
}

HARDWAREX_API int StopThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice)
{
	int id = 0;

	while (addrsMAVLinkDevice[id] != pMAVLinkDevice)
	{
		id++;
		if (id >= MAX_NB_DEVICES_HARDWAREX) return EXIT_FAILURE;
	}

	bExitMAVLinkDevice[id] = TRUE;
	WaitForThread(MAVLinkDeviceThreadId[id]);
	DeleteCriticalSection(&MAVLinkDeviceCS[id]);
	resMAVLinkDevice[id] = EXIT_FAILURE;
	return EXIT_SUCCESS;
}
#pragma endregion
#endif // ENABLE_MAVLINK_SUPPORT
