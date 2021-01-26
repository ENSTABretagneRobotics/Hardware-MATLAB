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

// Uncomment the following line to enable RPLIDAR SDK in MATLAB (requires corresponding SDK...).
//#define ENABLE_RPLIDAR_SDK_SUPPORT

// Uncomment the following line to enable SBG SDK in MATLAB (requires corresponding SDK...).
//#define ENABLE_SBG_SDK_SUPPORT

// Uncomment the following line to enable MAVLink in MATLAB (requires corresponding headers and needs Visual Studio 2013 or later (to set in mex -setup and mex -setup C++)...).
//#define ENABLE_MAVLINK_SUPPORT

//#ifndef DISABLE_THREADS_OSNET
//#define DISABLE_THREADS_OSNET
//#endif // !DISABLE_THREADS_OSNET

// To prevent some warnings in MATLAB...
#ifndef DISABLE_HOKUYOTHREAD
#define DISABLE_HOKUYOTHREAD
#endif // !DISABLE_HOKUYOTHREAD
#ifndef DISABLE_IM483ITHREAD
#define DISABLE_IM483ITHREAD
#endif // !DISABLE_IM483ITHREAD
#ifndef DISABLE_MAVLINKDEVICETHREAD
#define DISABLE_MAVLINKDEVICETHREAD
#endif // !DISABLE_MAVLINKDEVICETHREAD
#ifndef DISABLE_MDMTHREAD
#define DISABLE_MDMTHREAD
#endif // !DISABLE_MDMTHREAD
#ifndef DISABLE_MTTHREAD
#define DISABLE_MTTHREAD
#endif // !DISABLE_MTTHREAD
#ifndef DISABLE_NMEADEVICETHREAD
#define DISABLE_NMEADEVICETHREAD
#endif // !DISABLE_NMEADEVICETHREAD
#ifndef DISABLE_P33XTHREAD
#define DISABLE_P33XTHREAD
#endif // !DISABLE_P33XTHREAD
#ifndef DISABLE_POLOLUTHREAD
#define DISABLE_POLOLUTHREAD
#endif // !DISABLE_POLOLUTHREAD
#ifndef DISABLE_RAZORAHRSTHREAD
#define DISABLE_RAZORAHRSTHREAD
#endif // !DISABLE_RAZORAHRSTHREAD
#ifndef DISABLE_RPLIDARTHREAD
#define DISABLE_RPLIDARTHREAD
#endif // !DISABLE_RPLIDARTHREAD
#ifndef DISABLE_SBGTHREAD
#define DISABLE_SBGTHREAD
#endif // !DISABLE_SBGTHREAD
#ifndef DISABLE_SSC32THREAD
#define DISABLE_SSC32THREAD
#endif // !DISABLE_SSC32THREAD
#ifndef DISABLE_UBLOXTHREAD
#define DISABLE_UBLOXTHREAD
#endif // !DISABLE_UBLOXTHREAD

// Not sure why sometimes MATLAB gives errors without that...
#ifdef ENABLE_MAVLINK_SUPPORT
#ifdef __GNUC__
#include <stdint.h>
#endif // __GNUC__
#endif // ENABLE_MAVLINK_SUPPORT

#include "OSCriticalSection.h"
#include "SBG.h"
#include "MT.h"
#include "RazorAHRS.h"
#include "MDM.h"
#include "P33x.h"
#include "NMEADevice.h"
#include "ublox.h"
#include "IM483I.h"
#include "SSC32.h"
#include "Pololu.h"
#include "Hokuyo.h"
#include "RPLIDAR.h"
#ifdef ENABLE_MAVLINK_SUPPORT
#include "MAVLinkDevice.h"
#endif // ENABLE_MAVLINK_SUPPORT

#ifdef __cplusplus
extern "C" {
#endif

	HARDWAREX_API SBG* CreateSBGx(void);
	HARDWAREX_API void DestroySBGx(SBG* pSBG);
	HARDWAREX_API SBGDATA* CreateSBGDatax(void);
	HARDWAREX_API void DestroySBGDatax(SBGDATA* pSBGData);
	HARDWAREX_API int GetLatestDataSBGx(SBG* pSBG, SBGDATA* pSBGData);
	HARDWAREX_API int ConnectSBGx(SBG* pSBG, char* szCfgFilePath);
	HARDWAREX_API int DisconnectSBGx(SBG* pSBG);
	HARDWAREX_API int GetLatestDataFromThreadSBGx(SBG* pSBG, SBGDATA* pSBGData);
	HARDWAREX_API int StartThreadSBGx(SBG* pSBG);
	HARDWAREX_API int StopThreadSBGx(SBG* pSBG);

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

	HARDWAREX_API MDM* CreateMDMx(void);
	HARDWAREX_API void DestroyMDMx(MDM* pMDM);
	HARDWAREX_API int SendDataMDMx(MDM* pMDM, unsigned char* buf, int buflen, int* pSentBytes);
	HARDWAREX_API int RecvDataMDMx(MDM* pMDM, unsigned char* buf, int buflen, int* pReceivedBytes);
	HARDWAREX_API int PurgeDataMDMx(MDM* pMDM);
	HARDWAREX_API int ConnectMDMx(MDM* pMDM, char* szCfgFilePath);
	HARDWAREX_API int DisconnectMDMx(MDM* pMDM);

	HARDWAREX_API P33X* CreateP33xx(void);
	HARDWAREX_API void DestroyP33xx(P33X* pP33x);
	HARDWAREX_API int GetPressureP33xx(P33X* pP33x, double* pPressure);
	HARDWAREX_API int GetTemperatureP33xx(P33X* pP33x, double* pTemperature);
	HARDWAREX_API int ConnectP33xx(P33X* pP33x, char* szCfgFilePath);
	HARDWAREX_API int DisconnectP33xx(P33X* pP33x);
	HARDWAREX_API int GetPressureFromThreadP33xx(P33X* pP33x, double* pPressure);
	HARDWAREX_API int GetTemperatureFromThreadP33xx(P33X* pP33x, double* pTemperature);
	HARDWAREX_API int StartThreadP33xx(P33X* pP33x);
	HARDWAREX_API int StopThreadP33xx(P33X* pP33x);

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

	HARDWAREX_API UBLOX* Createubloxx(void);
	HARDWAREX_API void Destroyubloxx(UBLOX* publox);
	HARDWAREX_API UBXDATA* CreateUBXDatax(void);
	HARDWAREX_API void DestroyUBXDatax(UBXDATA* pUBXData);
	HARDWAREX_API int GetNMEASentenceubloxx(UBLOX* publox, NMEADATA* pNMEAData);
	HARDWAREX_API int GetUBXPacketubloxx(UBLOX* publox, UBXDATA* pUBXData);
	HARDWAREX_API int Connectubloxx(UBLOX* publox, char* szCfgFilePath);
	HARDWAREX_API int Disconnectubloxx(UBLOX* publox);
	HARDWAREX_API int GetNMEASentenceFromThreadubloxx(UBLOX* publox, NMEADATA* pNMEAData);
	HARDWAREX_API int GetUBXPacketFromThreadubloxx(UBLOX* publox, UBXDATA* pUBXData);
	HARDWAREX_API int StartNMEAThreadubloxx(UBLOX* publox);
	HARDWAREX_API int StopNMEAThreadubloxx(UBLOX* publox);
	HARDWAREX_API int StartUBXThreadubloxx(UBLOX* publox);
	HARDWAREX_API int StopUBXThreadubloxx(UBLOX* publox);

	HARDWAREX_API IM483I* CreateIM483Ix(void);
	HARDWAREX_API void DestroyIM483Ix(IM483I* pIM483I);
	HARDWAREX_API int SetMotorTorqueIM483Ix(IM483I* pIM483I, int holdpercent, int runpercent);
	HARDWAREX_API int SetMotorSpeedIM483Ix(IM483I* pIM483I, int val);
	HARDWAREX_API int SetMotorRelativeIM483Ix(IM483I* pIM483I, int val, BOOL bForce);
	HARDWAREX_API int SetMotorOriginIM483Ix(IM483I* pIM483I);
	HARDWAREX_API int SetMaxAngleIM483Ix(IM483I* pIM483I, double angle);
	HARDWAREX_API int CalibrateMotorIM483Ix(IM483I* pIM483I);
	HARDWAREX_API int ConnectIM483Ix(IM483I* pIM483I, char* szCfgFilePath);
	HARDWAREX_API int DisconnectIM483Ix(IM483I* pIM483I);
	HARDWAREX_API int SetMaxAngleFromThreadIM483Ix(IM483I* pIM483I, double angle);
	HARDWAREX_API int StartThreadIM483Ix(IM483I* pIM483I);
	HARDWAREX_API int StopThreadIM483Ix(IM483I* pIM483I);

	HARDWAREX_API SSC32* CreateSSC32x(void);
	HARDWAREX_API void DestroySSC32x(SSC32* pSSC32);
	HARDWAREX_API int GetVoltageSSC32x(SSC32* pSSC32, int channel, double* pVoltage);
	HARDWAREX_API int GetDigitalInputSSC32x(SSC32* pSSC32, int channel, int* pValue);
	HARDWAREX_API int GetPWMSSC32x(SSC32* pSSC32, int channel, int* pPw);
	HARDWAREX_API int SetPWMSSC32x(SSC32* pSSC32, int channel, int pw);
	HARDWAREX_API int SetAllPWMsSSC32x(SSC32* pSSC32, int* selectedchannels, int* pws);
	HARDWAREX_API int SetDigitalOutputSSC32x(SSC32* pSSC32, int channel, int value);
	HARDWAREX_API int ConnectSSC32x(SSC32* pSSC32, char* szCfgFilePath);
	HARDWAREX_API int DisconnectSSC32x(SSC32* pSSC32);
	HARDWAREX_API int SetAllPWMsFromThreadSSC32x(SSC32* pSSC32, int* selectedchannels, int* pws);
	HARDWAREX_API int StartThreadSSC32x(SSC32* pSSC32);
	HARDWAREX_API int StopThreadSSC32x(SSC32* pSSC32);

	HARDWAREX_API POLOLU* CreatePololux(void);
	HARDWAREX_API void DestroyPololux(POLOLU* pPololu);
	HARDWAREX_API int GetValuePololux(POLOLU* pPololu, int channel, int* pValue);
	HARDWAREX_API int GetAllValuesPololux(POLOLU* pPololu, int* selectedchannels, int* ais);
	HARDWAREX_API int SetPWMPololux(POLOLU* pPololu, int channel, int pw);
	HARDWAREX_API int SetAllPWMsPololux(POLOLU* pPololu, int* selectedchannels, int* pws);
	HARDWAREX_API int SetPWMJrkPololux(POLOLU* pPololu, int pw);
	HARDWAREX_API int ConnectPololux(POLOLU* pPololu, char* szCfgFilePath);
	HARDWAREX_API int DisconnectPololux(POLOLU* pPololu);
	HARDWAREX_API int SetAllPWMsFromThreadPololux(POLOLU* pPololu, int* selectedchannels, int* pws);
	HARDWAREX_API int GetValueFromThreadPololux(POLOLU* pPololu, int channel, int* pValue);
	HARDWAREX_API int StartThreadPololux(POLOLU* pPololu);
	HARDWAREX_API int StopThreadPololux(POLOLU* pPololu);

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

	HARDWAREX_API RPLIDAR* CreateRPLIDARx(void);
	HARDWAREX_API void DestroyRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int StopRequestRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int ResetRequestRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int GetStartupMessageRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int ClearCacheRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int GetHealthRequestRPLIDARx(RPLIDAR* pRPLIDAR, BOOL* pbProtectionStop);
	HARDWAREX_API int GetInfoRequestRPLIDARx(RPLIDAR* pRPLIDAR, int* pModelID, int* pHardwareVersion, int* pFirmwareMajor, int* pFirmwareMinor, char* SerialNumber);
	HARDWAREX_API int GetTypicalScanModeRPLIDARx(RPLIDAR* pRPLIDAR, int* pScanModeID);
	HARDWAREX_API int GetAllSupportedScanModesRPLIDARx(RPLIDAR* pRPLIDAR, int* pScanModeIDs, double* pusPerSamples, double* pMaxDistances, int* pAnsTypes, char** pScanModeNames);
	HARDWAREX_API int SetMotorPWMRequestRPLIDARx(RPLIDAR* pRPLIDAR, int pwm);
	HARDWAREX_API int SetLidarSpinSpeedRequestRPLIDARx(RPLIDAR* pRPLIDAR, int rpm);
	HARDWAREX_API int StartMotorRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int StopMotorRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int StartScanRequestRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int StartForceScanRequestRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int GetScanDataResponseRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistance, double* pAngle, BOOL* pbNewScan, int* pQuality);
	HARDWAREX_API int StartExpressScanRequestRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int GetExpressScanDataResponseRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistances, double* pAngles, BOOL* pbNewScan);
	HARDWAREX_API int StartOtherScanRequestRPLIDARx(RPLIDAR* pRPLIDAR, int scanmodeid);
	HARDWAREX_API int GetOtherScanDataResponseRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistances, double* pAngles, BOOL* pbNewScan);
	HARDWAREX_API int ConnectRPLIDARx(RPLIDAR* pRPLIDAR, char* szCfgFilePath);
	HARDWAREX_API int DisconnectRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int GetScanDataResponseFromThreadRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistance, double* pAngle, BOOL* pbNewScan, int* pQuality);
	HARDWAREX_API int GetExpressScanDataResponseFromThreadRPLIDARx(RPLIDAR* pRPLIDAR, double* pDistances, double* pAngles, BOOL* pbNewScan);
	HARDWAREX_API int StartScanThreadRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int StopScanThreadRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int StartExpressScanThreadRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int StopExpressScanThreadRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int StartOtherScanThreadRPLIDARx(RPLIDAR* pRPLIDAR);
	HARDWAREX_API int StopOtherScanThreadRPLIDARx(RPLIDAR* pRPLIDAR);

#ifdef ENABLE_MAVLINK_SUPPORT
	HARDWAREX_API MAVLINKDEVICE* CreateMAVLinkDevicex(void);
	HARDWAREX_API void DestroyMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice);
	HARDWAREX_API MAVLINKDATA* CreateMAVLinkDatax(void);
	HARDWAREX_API void DestroyMAVLinkDatax(MAVLINKDATA* pMAVLinkData);
	HARDWAREX_API int GetLatestDataMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice, MAVLINKDATA* pMAVLinkData);
	HARDWAREX_API int SetAllPWMsMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice, int* selectedchannels, int* pws);
	HARDWAREX_API int ConnectMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice, char* szCfgFilePath);
	HARDWAREX_API int DisconnectMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice);
	HARDWAREX_API int SetAllPWMsFromThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice, int* selectedchannels, int* pws);
	HARDWAREX_API int GetLatestDataFromThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice, MAVLINKDATA* pMAVLinkData);
	HARDWAREX_API int StartThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice);
	HARDWAREX_API int StopThreadMAVLinkDevicex(MAVLINKDEVICE* pMAVLinkDevice);
#endif // ENABLE_MAVLINK_SUPPORT

#ifdef __cplusplus
}
#endif

#endif // !HARDWAREX_H
