// Prevent Visual Studio Intellisense from defining _WIN32 and _MSC_VER when we use 
// Visual Studio to edit Linux or Borland C++ code.
#ifdef __linux__
#	undef _WIN32
#endif // __linux__
#if defined(__GNUC__) || defined(__BORLANDC__)
#	undef _MSC_VER
#endif // defined(__GNUC__) || defined(__BORLANDC__)

#ifndef RPLIDAR_H
#define RPLIDAR_H

#include "OSMisc.h"
#include "RS232Port.h"

#ifndef DISABLE_RPLIDARTHREAD
#include "OSThread.h"
#endif // !DISABLE_RPLIDARTHREAD

#if !defined(__cplusplus) && defined(ENABLE_RPLIDAR_SDK_SUPPORT)
#undef ENABLE_RPLIDAR_SDK_SUPPORT
#endif // !defined(__cplusplus) && defined(ENABLE_RPLIDAR_SDK_SUPPORT)

// Temp...
//#undef ENABLE_RPLIDAR_SDK_SUPPORT
//#define FORCE_RPLIDAR_SDK_V1

#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
#ifdef _MSC_VER
// Disable some Visual Studio warnings.
#pragma warning(disable : 4200) 
#endif // _MSC_VER

#ifdef FORCE_RPLIDAR_SDK_V1
#include "../include/rplidar.h"
using namespace rp::standalone::rplidar;
// Different depending on the SDK version...
#ifdef SLAMTEC_LIDAR_SDK_VERSION
#define DRIVER_TYPE_SERIALPORT CHANNEL_TYPE_SERIALPORT
#define DRIVER_TYPE_TCP CHANNEL_TYPE_TCP
#define DRIVER_TYPE_UDP CHANNEL_TYPE_UDP
#else
#define CHANNEL_TYPE_SERIALPORT DRIVER_TYPE_SERIALPORT
#define CHANNEL_TYPE_TCP DRIVER_TYPE_TCP
#define CHANNEL_TYPE_UDP 0x2
#define SL_IS_OK(x) IS_OK(x)
#define SL_IS_FAIL(x) IS_FAIL(x)
#define SL_LIDAR_STATUS_ERROR RPLIDAR_STATUS_ERROR
#define SL_LIDAR_RESP_MEASUREMENT_SYNCBIT RPLIDAR_RESP_MEASUREMENT_SYNCBIT
#define SL_LIDAR_CONF_SCAN_COMMAND_EXPRESS RPLIDAR_CONF_SCAN_COMMAND_EXPRESS
#define sl_lidar_response_device_health_t rplidar_response_device_health_t
#define sl_lidar_response_device_info_t rplidar_response_device_info_t
#define sl_lidar_response_measurement_node_hq_t rplidar_response_measurement_node_hq_t
#endif // SLAMTEC_LIDAR_SDK_VERSION
#else
#include "../include/sl_lidar.h" 
#include "../include/sl_lidar_driver.h"
using namespace sl;
#endif // FORCE_RPLIDAR_SDK_V1

#ifdef _MSC_VER
// Restore the Visual Studio warnings previously disabled.
#pragma warning(default : 4200) 
#endif // _MSC_VER

#include <deque>
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

// Need to be undefined at the end of the file...
// min and max might cause incompatibilities...
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif // !max
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif // !min

#define TIMEOUT_MESSAGE_RPLIDAR 4.0 // In s.
// Should be at least 2 * number of bytes to be sure to contain entirely the biggest desired message (or group of messages) + 1.
#define MAX_NB_BYTES_RPLIDAR 1024

#pragma region RPLIDAR-SPECIFIC DEFINITIONS
#ifndef ENABLE_RPLIDAR_SDK_SUPPORT
#define MIN_BUF_LEN_RPLIDAR 2

#define NB_BYTES_RESPONSE_DESCRIPTOR_RPLIDAR 7
#define NB_BYTES_CHECKSUM_RPLIDAR 1

#define START_FLAG1_RPLIDAR 0xA5
#define START_FLAG2_RPLIDAR 0x5A

#define SEND_MODE_MASK_RPLIDAR 0xC0
#define SEND_MODE_SHIFT_RPLIDAR 6
#define DATA_RESPONSE_LENGTH_MASK_RPLIDAR 0x3FFFFFFF

// Single Request-Single Response Mode
// Single Request-Multiple Response Mode
// Single Request-No Response : need to wait a little bit after the request wince there will be no response...
#define SINGLE_REQUEST_SINGLE_RESPONSE_SEND_MODE_RPLIDAR 0x00
#define SINGLE_REQUEST_MULTIPLE_RESPONSE_SEND_MODE_RPLIDAR 0x01

// Commands without payload and response.
#define STOP_REQUEST_RPLIDAR 0x25
#define SCAN_REQUEST_RPLIDAR 0x20
#define FORCE_SCAN_REQUEST_RPLIDAR 0x21
#define RESET_REQUEST_RPLIDAR 0x40

// Commands without payload but have response
#define GET_INFO_REQUEST_RPLIDAR 0x50
#define GET_HEALTH_REQUEST_RPLIDAR 0x52
#define GET_SAMPLERATE_REQUEST_RPLIDAR 0x59 // Added in FW ver 1.17.

// Commands with payload and without response
#define SET_MOTOR_SPEED_CTRL_REQUEST_RPLIDAR 0xA8
#define NEW_BAUDRATE_CONFIRM_REQUEST_RPLIDAR 0x90 // Added in FW ver 1.30. // Undocumented...

// Commands with payload and have response
#define EXPRESS_SCAN_REQUEST_RPLIDAR 0x82 // Added in FW ver 1.17.
#define HQ_SCAN_REQUEST_RPLIDAR 0x83 // Added in FW ver 1.24.
#define GET_LIDAR_CONF_REQUEST_RPLIDAR 0x84 // Added in FW ver 1.24.
#define SET_LIDAR_CONF_REQUEST_RPLIDAR 0x85 // Added in FW ver 1.24. // Undocumented...
// Commands added for A2 to set RPLIDAR motor PWM when using accessory board.
#define SET_MOTOR_PWM_REQUEST_RPLIDAR 0xF0 // Undocumented...
#define GET_ACC_BOARD_FLAG_REQUEST_RPLIDAR 0xFF // Undocumented...

// Responses.
#define DEVINFO_RESPONSE_RPLIDAR 0x04
#define DEVHEALTH_RESPONSE_RPLIDAR 0x06
#define MEASUREMENT_RESPONSE_RPLIDAR 0x81
#define MEASUREMENT_CAPSULED_RESPONSE_RPLIDAR 0x82 // Added in FW ver 1.17.
#define MEASUREMENT_HQ_RESPONSE_RPLIDAR 0x83 // Added in FW ver 1.17.
#define SAMPLERATE_RESPONSE_RPLIDAR 0x15 // Added in FW ver 1.17.
#define MEASUREMENT_CAPSULED_ULTRA_RESPONSE_RPLIDAR 0x84 // Added in FW ver 1.23alpha.
#define MEASUREMENT_DENSE_CAPSULED_RESPONSE_RPLIDAR 0x85 // Added in FW ver 1.24.
#define GET_LIDAR_CONF_RESPONSE_RPLIDAR 0x20 // Added in FW ver 1.24.
#define SET_LIDAR_CONF_RESPONSE_RPLIDAR 0x21 // Added in FW ver 1.24.
#define ACC_BOARD_FLAG_RESPONSE_RPLIDAR 0xFF // Added in FW ver 1.24.

#define LIDAR_CONF_SCAN_MODE_COUNT_RPLIDAR                0x00000070
#define LIDAR_CONF_SCAN_MODE_US_PER_SAMPLE_RPLIDAR        0x00000071
#define LIDAR_CONF_SCAN_MODE_MAX_DISTANCE_RPLIDAR         0x00000074
#define LIDAR_CONF_SCAN_MODE_ANS_TYPE_RPLIDAR             0x00000075
#define LIDAR_CONF_LIDAR_MAC_ADDR_RPLIDAR                 0x00000079
#define LIDAR_CONF_SCAN_MODE_TYPICAL_RPLIDAR              0x0000007C
#define LIDAR_CONF_SCAN_MODE_NAME_RPLIDAR                 0x0000007F
#define LIDAR_CONF_DETECTED_SERIAL_BPS_RPLIDAR            0x000000A1
#else
#endif // !ENABLE_RPLIDAR_SDK_SUPPORT

#define NB_BYTES_SERIAL_NUMBER_RPLIDAR 16
#define MAX_BUF_LEN_SERIAL_NUMBER_RPLIDAR (2*NB_BYTES_SERIAL_NUMBER_RPLIDAR+1)

#define STATUS_OK_RPLIDAR 0x00
#define STATUS_WARNING_RPLIDAR 0x01
#define STATUS_ERROR_RPLIDAR 0x02

// Undocumented...
#define MAX_MOTOR_PWM_RPLIDAR 1023
#define DEFAULT_MOTOR_PWM_RPLIDAR 660
#define DEFAULT_MOTOR_SPEED_RPLIDAR (0xFFFFu)

#define SCAN_MODE_RPLIDAR 0
#define LEGACY_EXPRESS_SCAN_MODE_RPLIDAR 254
#define FORCE_SCAN_MODE_RPLIDAR 255

#define CHECK_BIT_MASK_SCAN_DATA_RESPONSE_RPLIDAR 0x01
#define START_BIT_MASK_SCAN_DATA_RESPONSE_RPLIDAR 0x01
#define INVERTED_START_BIT_MASK_SCAN_DATA_RESPONSE_RPLIDAR 0x02

#define MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR 8192

#define NB_BYTES_SCAN_DATA_RESPONSE_RPLIDAR 5
#define NB_BYTES_FORCE_SCAN_DATA_RESPONSE_RPLIDAR NB_BYTES_SCAN_DATA_RESPONSE_RPLIDAR
#define NB_BYTES_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR 84
#define NB_BYTES_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR 132
#define NB_BYTES_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR 84

#define NB_CABINS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR 16
#define NB_CABINS_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR 32
#define NB_CABINS_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR 40

#define NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR (2*NB_CABINS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR)
#define NB_MEASUREMENTS_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR (3*NB_CABINS_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR)
#define NB_MEASUREMENTS_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR NB_CABINS_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR

// Arbitrarily set to the max of the different scan modes...
#define NB_MEASUREMENTS_OTHER_SCAN_DATA_RESPONSE_RPLIDAR NB_MEASUREMENTS_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR

#define MAX_NB_SCAN_MODES_RPLIDAR 16

struct RPLIDARSCANMODE
{
	int id;
	double us_per_sample;
	double max_distance;
	int ans_type;
	char scan_mode[64];
};
typedef struct RPLIDARSCANMODE RPLIDARSCANMODE;

struct RPLIDARSCAN
{
	double distance; 
	double angle; 
	BOOL bNewScan; 
	int quality;
};
typedef struct RPLIDARSCAN RPLIDARSCAN;

#pragma endregion
struct RPLIDAR
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
#ifdef FORCE_RPLIDAR_SDK_V1
	RPlidarDriver* drv;
	void* channel; // Kept as padding for MATLAB compatibility since it does not seem to support C++ types in the configuration used...
	std::deque<sl_lidar_response_measurement_node_hq_t>* nodes_cache;
#else
	ILidarDriver* drv;
	IChannel* channel;
	std::deque<sl_lidar_response_measurement_node_hq_t>* nodes_cache;
#endif // FORCE_RPLIDAR_SDK_V1
#else
	void* drv; // Kept as padding for MATLAB compatibility since it does not seem to support C++ types in the configuration used...
	void* channel; // Kept as padding for MATLAB compatibility since it does not seem to support C++ types in the configuration used...
	void* nodes_cache; // Kept as padding for MATLAB compatibility since it does not seem to support C++ types in the configuration used...
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
	RS232PORT RS232Port; // Kept as padding for MATLAB compatibility since it does not seem to support C++ types in the configuration used...
	int model;
	int hardware;
	int firmware_major;
	int firmware_minor;
	char SerialNumber[MAX_BUF_LEN_SERIAL_NUMBER_RPLIDAR];
	int Tstandard; // Time in us used when RPLIDAR takes a single laser ranging in SCAN mode.
	int Texpress; // Time in us used when RPLIDAR takes a single laser ranging in EXPRESS_SCAN mode.
	int esversion; // Express Scan version.
	unsigned char esdata_prev[NB_BYTES_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR];
	unsigned char eesdata_prev[NB_BYTES_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR];
	unsigned char desdata_prev[NB_BYTES_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR];
	FILE* pfSaveFile; // Used to save raw data, should be handled specifically...
	//RPLIDARDATA LastRPLIDARData;
	char szCfgFilePath[256];
	// Parameters.
	char szDevPath[256];
	int BaudRate;
	int timeout;
	int threadperiod;
	BOOL bSaveRawData;
	BOOL bStartScanModeAtStartup;
	int ScanMode;
	int motordelay;
	int motorPWM;
	int maxhist;
	double alpha_max_err;
	double d_max_err;
};
typedef struct RPLIDAR RPLIDAR;

inline double AngleDiffRPLIDAR(double start_angle_1, double start_angle_2)
{
	if (start_angle_1 <= start_angle_2) return start_angle_2-start_angle_1;
	else return 360+start_angle_2-start_angle_1;
}

#ifndef ENABLE_RPLIDAR_SDK_SUPPORT
// req must contain a valid request of reqlen bytes.
inline unsigned char ComputeChecksumRPLIDAR(unsigned char* req, int reqlen)
{
	int i = 0;
	unsigned char res = 0;

	while (i < reqlen-NB_BYTES_CHECKSUM_RPLIDAR)
	{
		res ^= req[i];
		i++;
	}
	return res;
}

// req must contain a valid request of reqlen bytes.
inline int GetSendModeFromResponseDescriptorRPLIDAR(unsigned char* req, int reqlen)
{
	UNREFERENCED_PARAMETER(reqlen);
	return ((SEND_MODE_MASK_RPLIDAR & req[5]) >> SEND_MODE_SHIFT_RPLIDAR);
}

// req must contain a valid request of reqlen bytes.
inline int GetDataResponseLengthFromResponseDescriptorRPLIDAR(unsigned char* req, int reqlen)
{
	int len = 0;
	UNREFERENCED_PARAMETER(reqlen);
	len = ((req[5]<<24)|(req[4]<<16)|(req[3]<<8)|(req[2])) & DATA_RESPONSE_LENGTH_MASK_RPLIDAR;
	return len;
}

/*
Return : EXIT_SUCCESS if the beginning of buf contains a valid response descriptor (there might be other data at the end), 
EXIT_OUT_OF_MEMORY if the response descriptor is incomplete (check *pnbBytesToRequest to know how many additional bytes 
should be requested, -1 if unknown) or EXIT_FAILURE if there is an error (check *pnbBytesToDiscard to know how 
many bytes can be safely discarded).
*/
inline int AnalyzeResponseDescriptorRPLIDAR(unsigned char* buf, int buflen, int* pDataResponseLength, int* pSendMode, int* pDataType, 
							int* pnbBytesToRequest, int* pnbBytesToDiscard)
{
	*pDataResponseLength = 0;
	*pnbBytesToRequest = -1;
	*pnbBytesToDiscard = 0;
	if (buflen < NB_BYTES_RESPONSE_DESCRIPTOR_RPLIDAR)
	{
		*pnbBytesToRequest = NB_BYTES_RESPONSE_DESCRIPTOR_RPLIDAR-buflen;
		return EXIT_OUT_OF_MEMORY;
	}
	if ((buf[0] != START_FLAG1_RPLIDAR)||(buf[1] != START_FLAG2_RPLIDAR))
	{
		printf("Warning : RPLIDAR bad start flag. \n");
		*pnbBytesToDiscard = 1; // We are only sure that the first start flag byte can be discarded...
		return EXIT_FAILURE;
	}
	*pDataResponseLength = GetDataResponseLengthFromResponseDescriptorRPLIDAR(buf, buflen);	
	*pSendMode = GetSendModeFromResponseDescriptorRPLIDAR(buf, buflen);	
	*pDataType = buf[6];

	return EXIT_SUCCESS;
}

/*
Return : EXIT_SUCCESS if the beginning of *pFoundResponseDescriptor contains a valid response descriptor (there might be other data 
at the end), 
EXIT_OUT_OF_MEMORY if the response descriptor is incomplete (check *pnbBytesToRequest to know how many additional bytes 
should be requested, -1 if unknown) or EXIT_FAILURE if no compatible response descriptor could be found. 
Data in the beginning of buf might have been discarded (check *pnbBytesDiscarded to know how many bytes were discarded).
*/
inline int FindResponseDescriptorRPLIDAR(unsigned char* buf, int buflen, int* pDataResponseLength, int* pSendMode, int* pDataType, 
						 int* pnbBytesToRequest, unsigned char** pFoundResponseDescriptor, int* pnbBytesDiscarded)
{
	int res = EXIT_FAILURE, nbBytesToRequest = -1, nbBytesToDiscard = 0;

	*pnbBytesToRequest = -1;
	*pFoundResponseDescriptor = buf;
	*pnbBytesDiscarded = 0;

	for (;;)
	{
		res = AnalyzeResponseDescriptorRPLIDAR(*pFoundResponseDescriptor, buflen-(*pnbBytesDiscarded), pDataResponseLength, pSendMode, pDataType, &nbBytesToRequest, &nbBytesToDiscard);
		switch (res)
		{
		case EXIT_SUCCESS:
			return EXIT_SUCCESS;
		case EXIT_OUT_OF_MEMORY:
			(*pnbBytesToRequest) = nbBytesToRequest;
			return EXIT_OUT_OF_MEMORY;
		default:
			(*pFoundResponseDescriptor) += nbBytesToDiscard;
			(*pnbBytesDiscarded) += nbBytesToDiscard;
			if (buflen-(*pnbBytesDiscarded) <= 0)
			{
				*pFoundResponseDescriptor = NULL;
				return EXIT_FAILURE;
			}
			break;
		}
	} 
}

inline int GetResponseDescriptorRPLIDAR(RPLIDAR* pRPLIDAR, int* pDataResponseLength, int* pSendMode, int* pDataType)
{
	unsigned char recvbuf[MAX_NB_BYTES_RPLIDAR];
	int BytesReceived = 0, recvbuflen = 0, res = EXIT_FAILURE, nbBytesToRequest = 0, nbBytesDiscarded = 0;
	unsigned char* ptr = NULL;
	CHRONO chrono;

	StartChrono(&chrono);

	// Prepare the buffers.
	memset(recvbuf, 0, sizeof(recvbuf));
	recvbuflen = MAX_NB_BYTES_RPLIDAR-1; // The last character must be a 0 to be a valid string for sscanf.
	BytesReceived = 0;

	// Suppose that there are not so many data to discard.
	// First try to get directly the desired response descriptor...

	nbBytesToRequest = NB_BYTES_RESPONSE_DESCRIPTOR_RPLIDAR;
	if (ReadAllRS232Port(&pRPLIDAR->RS232Port, recvbuf, nbBytesToRequest) != EXIT_SUCCESS)
	{
		printf("Error reading data from a RPLIDAR. \n");
		return EXIT_FAILURE;
	}
	BytesReceived += nbBytesToRequest;
	
	for (;;)
	{
		res = FindResponseDescriptorRPLIDAR(recvbuf, BytesReceived, pDataResponseLength, pSendMode, pDataType, &nbBytesToRequest, &ptr, &nbBytesDiscarded);
		if (res == EXIT_SUCCESS) break;
		if (res == EXIT_FAILURE)
		{
			nbBytesToRequest = min(NB_BYTES_RESPONSE_DESCRIPTOR_RPLIDAR, nbBytesDiscarded);
		}	
		memmove(recvbuf, recvbuf+nbBytesDiscarded, BytesReceived-nbBytesDiscarded);
		BytesReceived -= nbBytesDiscarded;
		if (BytesReceived+nbBytesToRequest > recvbuflen)
		{
			printf("Error reading data from a RPLIDAR : Invalid data. \n");
			return EXIT_INVALID_DATA;
		}
		if (ReadAllRS232Port(&pRPLIDAR->RS232Port, recvbuf+BytesReceived, nbBytesToRequest) != EXIT_SUCCESS)
		{
			printf("Error reading data from a RPLIDAR. \n");
			return EXIT_FAILURE;
		}
		BytesReceived += nbBytesToRequest;
		if (GetTimeElapsedChronoQuick(&chrono) > TIMEOUT_MESSAGE_RPLIDAR)
		{
			printf("Error reading data from a RPLIDAR : Response descriptor timeout. \n");
			return EXIT_TIMEOUT;
		}
	}

	if (BytesReceived-nbBytesDiscarded-NB_BYTES_RESPONSE_DESCRIPTOR_RPLIDAR > 0)
	{
		printf("Warning getting data from a RPLIDAR : Unexpected data after a response descriptor. \n");
	}

	return EXIT_SUCCESS;
}

/*
Return : EXIT_SUCCESS if the beginning of buf contains a valid data response (there might be other data at the end),
EXIT_OUT_OF_MEMORY if the data response is incomplete (check *pnbBytesToRequest to know how many additional bytes
should be requested, -1 if unknown) or EXIT_FAILURE if there is an error (check *pnbBytesToDiscard to know how
many bytes can be safely discarded).
*/
inline int AnalyzeScanDataResponseRPLIDAR(unsigned char* buf, int buflen, BOOL* pbNewScan, int* pQuality, double* pAngle, double* pDistance,
	int* pnbBytesToRequest, int* pnbBytesToDiscard)
{
	unsigned short angle_q6 = 0;
	unsigned short distance_q2 = 0;

	*pnbBytesToRequest = -1;
	*pnbBytesToDiscard = 0;
	if (buflen < NB_BYTES_SCAN_DATA_RESPONSE_RPLIDAR)
	{
		*pnbBytesToRequest = NB_BYTES_SCAN_DATA_RESPONSE_RPLIDAR-buflen;
		return EXIT_OUT_OF_MEMORY;
	}
	*pbNewScan = (buf[0] & START_BIT_MASK_SCAN_DATA_RESPONSE_RPLIDAR);
	if (*pbNewScan == ((buf[0] & INVERTED_START_BIT_MASK_SCAN_DATA_RESPONSE_RPLIDAR) >> 1))
	{
		printf("Warning : RPLIDAR bad inversed start bit. \n");
		*pnbBytesToDiscard = 1; // We are only sure that the first byte can be discarded...
		return EXIT_FAILURE;
	}
	if ((buf[1] & CHECK_BIT_MASK_SCAN_DATA_RESPONSE_RPLIDAR) != 1)
	{
		printf("Warning : RPLIDAR bad check bit. \n");
		*pnbBytesToDiscard = 1; // We are only sure that the first byte can be discarded...
		return EXIT_FAILURE;
	}
	*pQuality = (unsigned char)(buf[0] >> 2);
	angle_q6 = (buf[2] << 7)|(buf[1] >> 1);
	distance_q2 = (buf[4] << 8)|buf[3];
	// Convert in rad.
	*pAngle = fmod_2PI_deg2rad(-angle_q6/64.0);
	// Convert in m.
	*pDistance = distance_q2/4000.0;

	return EXIT_SUCCESS;
}

/*
Return : EXIT_SUCCESS if the beginning of *pFoundScanDataResponse contains a valid data response (there might be other data
at the end),
EXIT_OUT_OF_MEMORY if the data response is incomplete (check *pnbBytesToRequest to know how many additional bytes
should be requested, -1 if unknown) or EXIT_FAILURE if no compatible data response could be found.
Data in the beginning of buf might have been discarded (check *pnbBytesDiscarded to know how many bytes were discarded).
*/
inline int FindScanDataResponseRPLIDAR(unsigned char* buf, int buflen, BOOL* pbNewScan, int* pQuality, double* pAngle, double* pDistance,
	int* pnbBytesToRequest, unsigned char** pFoundScanDataResponse, int* pnbBytesDiscarded)
{
	int res = EXIT_FAILURE, nbBytesToRequest = -1, nbBytesToDiscard = 0;

	*pnbBytesToRequest = -1;
	*pFoundScanDataResponse = buf;
	*pnbBytesDiscarded = 0;

	for (;;)
	{
		res = AnalyzeScanDataResponseRPLIDAR(*pFoundScanDataResponse, buflen-(*pnbBytesDiscarded), pbNewScan, pQuality, pAngle, pDistance, &nbBytesToRequest, &nbBytesToDiscard);
		switch (res)
		{
		case EXIT_SUCCESS:
			return EXIT_SUCCESS;
		case EXIT_OUT_OF_MEMORY:
			(*pnbBytesToRequest) = nbBytesToRequest;
			return EXIT_OUT_OF_MEMORY;
		default:
			(*pFoundScanDataResponse) += nbBytesToDiscard;
			(*pnbBytesDiscarded) += nbBytesToDiscard;
			if (buflen-(*pnbBytesDiscarded) <= 0)
			{
				*pFoundScanDataResponse = NULL;
				return EXIT_FAILURE;
			}
			break;
		}
	}
}

/*
Return : EXIT_SUCCESS if the beginning of buf contains a valid data response (there might be other data at the end),
EXIT_OUT_OF_MEMORY if the data response is incomplete (check *pnbBytesToRequest to know how many additional bytes
should be requested, -1 if unknown) or EXIT_FAILURE if there is an error (check *pnbBytesToDiscard to know how
many bytes can be safely discarded).
*/
inline int AnalyzeExpressScanDataResponseRPLIDAR(unsigned char* buf, int buflen, int nb_bytes_response,
	int* pnbBytesToRequest, int* pnbBytesToDiscard)
{
	unsigned char sync = 0, ChkSum = 0;

	*pnbBytesToRequest = -1;
	*pnbBytesToDiscard = 0;
	if (buflen < nb_bytes_response)
	{
		*pnbBytesToRequest = nb_bytes_response-buflen;
		return EXIT_OUT_OF_MEMORY;
	}
	sync = (buf[0] & 0xF0)|(buf[1] >> 4);
	if (sync != START_FLAG1_RPLIDAR)
	{
		printf("Warning : RPLIDAR bad sync1 or sync2. \n");
		*pnbBytesToDiscard = 1; // We are only sure that the first byte can be discarded...
		return EXIT_FAILURE;
	}
	ChkSum = (buf[1] << 4)|(buf[0] & 0x0F);
	// Force ComputeChecksumRPLIDAR() to compute until the last byte...
	if (ChkSum != ComputeChecksumRPLIDAR(buf+2, nb_bytes_response-1))
	{
		printf("Warning : RPLIDAR bad ChkSum. \n");
		*pnbBytesToDiscard = 1; // We are only sure that the first byte can be discarded...
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/*
Return : EXIT_SUCCESS if the beginning of *pFoundScanDataResponse contains a valid data response (there might be other data
at the end),
EXIT_OUT_OF_MEMORY if the data response is incomplete (check *pnbBytesToRequest to know how many additional bytes
should be requested, -1 if unknown) or EXIT_FAILURE if no compatible data response could be found.
Data in the beginning of buf might have been discarded (check *pnbBytesDiscarded to know how many bytes were discarded).
*/
inline int FindExpressScanDataResponseRPLIDAR(unsigned char* buf, int buflen, int nb_bytes_response,
	int* pnbBytesToRequest, unsigned char** pFoundExpressScanDataResponse, int* pnbBytesDiscarded)
{
	int res = EXIT_FAILURE, nbBytesToRequest = -1, nbBytesToDiscard = 0;

	*pnbBytesToRequest = -1;
	*pFoundExpressScanDataResponse = buf;
	*pnbBytesDiscarded = 0;

	for (;;)
	{
		res = AnalyzeExpressScanDataResponseRPLIDAR(*pFoundExpressScanDataResponse, buflen-(*pnbBytesDiscarded), nb_bytes_response, &nbBytesToRequest, &nbBytesToDiscard);
		switch (res)
		{
		case EXIT_SUCCESS:
			return EXIT_SUCCESS;
		case EXIT_OUT_OF_MEMORY:
			(*pnbBytesToRequest) = nbBytesToRequest;
			return EXIT_OUT_OF_MEMORY;
		default:
			(*pFoundExpressScanDataResponse) += nbBytesToDiscard;
			(*pnbBytesDiscarded) += nbBytesToDiscard;
			if (buflen-(*pnbBytesDiscarded) <= 0)
			{
				*pFoundExpressScanDataResponse = NULL;
				return EXIT_FAILURE;
			}
			break;
		}
	}
}

// unsigned char esdataresponse[nb_bytes_response] with nb_bytes_response=NB_BYTES_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR
// or NB_BYTES_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR or NB_BYTES_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR
inline int GetRawExpressScanDataResponseRPLIDAR(RPLIDAR* pRPLIDAR, unsigned char* esdataresponse, int nb_bytes_response)
{
	unsigned char recvbuf[MAX_NB_BYTES_RPLIDAR];
	int BytesReceived = 0, recvbuflen = 0, res = EXIT_FAILURE, nbBytesToRequest = 0, nbBytesDiscarded = 0;
	unsigned char* ptr = NULL;
	CHRONO chrono;

	StartChrono(&chrono);

	// Prepare the buffers.
	memset(recvbuf, 0, sizeof(recvbuf));
	recvbuflen = MAX_NB_BYTES_RPLIDAR-1; // The last character must be a 0 to be a valid string for sscanf.
	BytesReceived = 0;

	// Suppose that there are not so many data to discard.
	// First try to get directly the desired data response...

	nbBytesToRequest = nb_bytes_response;
	if (ReadAllRS232Port(&pRPLIDAR->RS232Port, recvbuf, nbBytesToRequest) != EXIT_SUCCESS)
	{
		printf("Error reading data from a RPLIDAR. \n");
		return EXIT_FAILURE;
	}
	BytesReceived += nbBytesToRequest;

	for (;;)
	{
		res = FindExpressScanDataResponseRPLIDAR(recvbuf, BytesReceived, nb_bytes_response, &nbBytesToRequest, &ptr, &nbBytesDiscarded);
		if (res == EXIT_SUCCESS) break;
		if (res == EXIT_FAILURE)
		{
			nbBytesToRequest = min(nb_bytes_response, nbBytesDiscarded);
		}
		memmove(recvbuf, recvbuf+nbBytesDiscarded, BytesReceived-nbBytesDiscarded);
		BytesReceived -= nbBytesDiscarded;
		if (BytesReceived+nbBytesToRequest > recvbuflen)
		{
			printf("Error reading data from a RPLIDAR : Invalid data. \n");
			return EXIT_INVALID_DATA;
		}
		if (ReadAllRS232Port(&pRPLIDAR->RS232Port, recvbuf+BytesReceived, nbBytesToRequest) != EXIT_SUCCESS)
		{
			printf("Error reading data from a RPLIDAR. \n");
			return EXIT_FAILURE;
		}
		BytesReceived += nbBytesToRequest;
		if (GetTimeElapsedChronoQuick(&chrono) > TIMEOUT_MESSAGE_RPLIDAR)
		{
			printf("Error reading data from a RPLIDAR : Data response timeout. \n");
			return EXIT_TIMEOUT;
		}
	}

	if (BytesReceived-nbBytesDiscarded-nb_bytes_response > 0)
	{
		printf("Warning getting data from a RPLIDAR : Unexpected data after a data response. \n");
	}

	// Store the data...
	memcpy(esdataresponse, recvbuf, nb_bytes_response);

	return EXIT_SUCCESS;
}

inline int GetConfRPLIDAR(RPLIDAR* pRPLIDAR, int type, unsigned char* payload, int payloadsize, unsigned char* resppayload, int resppayloadsize)
{
	unsigned char reqbuf[136];
	int DataResponseLength = 0, SendMode = 0, DataType = 0;

	if ((payloadsize < 0)||(payloadsize > 128))
	{
		printf("Error writing data to a RPLIDAR : Invalid payloadsize. \n");
		return EXIT_FAILURE;
	}

	memset(reqbuf, 0, sizeof(reqbuf));
	reqbuf[0] = START_FLAG1_RPLIDAR;
	reqbuf[1] = GET_LIDAR_CONF_REQUEST_RPLIDAR;
	reqbuf[2] = (unsigned char)(4+payloadsize);
	memcpy(reqbuf+3, (unsigned char*)&type, 4);
	if (payloadsize > 0) memcpy(reqbuf+7, payload, payloadsize);
	reqbuf[7+payloadsize] = ComputeChecksumRPLIDAR(reqbuf, 8+payloadsize);

	// Send request.
	if (WriteAllRS232Port(&pRPLIDAR->RS232Port, reqbuf, 8+payloadsize) != EXIT_SUCCESS)
	{
		printf("Error writing data to a RPLIDAR. \n");
		return EXIT_FAILURE;
	}

	// Receive the response descriptor.
	if (GetResponseDescriptorRPLIDAR(pRPLIDAR, &DataResponseLength, &SendMode, &DataType) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	// Quick check of the response descriptor.
	if (DataType != GET_LIDAR_CONF_RESPONSE_RPLIDAR)
	{
		printf("A RPLIDAR is not responding correctly : Bad response descriptor. \n");
		return EXIT_FAILURE;
	}

	if (DataResponseLength > resppayloadsize)
	{
		printf("Error writing data to a RPLIDAR : Invalid resppayloadsize. \n");
		return EXIT_FAILURE;
	}

	// Receive the data response.
	memset(resppayload, 0, DataResponseLength);
	if (ReadAllRS232Port(&pRPLIDAR->RS232Port, resppayload, DataResponseLength) != EXIT_SUCCESS)
	{
		printf("A RPLIDAR is not responding correctly. \n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
#endif // !ENABLE_RPLIDAR_SDK_SUPPORT

inline int StopRequestRPLIDAR(RPLIDAR* pRPLIDAR)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
	pRPLIDAR->nodes_cache->clear();
	if (SL_IS_FAIL(pRPLIDAR->drv->stop()))
	{
		printf("A RPLIDAR is not responding correctly : stop() failed. \n");
		return EXIT_FAILURE;
	}
#else
	unsigned char reqbuf[] = {START_FLAG1_RPLIDAR,STOP_REQUEST_RPLIDAR};

	// Send request.
	if (WriteAllRS232Port(&pRPLIDAR->RS232Port, reqbuf, sizeof(reqbuf)) != EXIT_SUCCESS)
	{
		printf("Error writing data to a RPLIDAR. \n");
		return EXIT_FAILURE;
	}
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	// Host systems should wait for at least 1 millisecond (ms) before sending another request.
	//uSleep(1000);
	// https://github.com/Slamtec/rplidar_sdk/issues/36.
	//mSleep(20);
	mSleep(pRPLIDAR->motordelay);

	return EXIT_SUCCESS;
}

inline int ResetRequestRPLIDAR(RPLIDAR* pRPLIDAR)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
	if (SL_IS_FAIL(pRPLIDAR->drv->reset()))
	{
		printf("A RPLIDAR is not responding correctly : reset() failed. \n");
		return EXIT_FAILURE;
	}
#else
	unsigned char reqbuf[] = {START_FLAG1_RPLIDAR,RESET_REQUEST_RPLIDAR};

	// Send request.
	if (WriteAllRS232Port(&pRPLIDAR->RS232Port, reqbuf, sizeof(reqbuf)) != EXIT_SUCCESS)
	{
		printf("Error writing data to a RPLIDAR. \n");
		return EXIT_FAILURE;
	}
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	// Host systems should wait for at least 2 milliseconds (ms) before sending another request.
	//uSleep(2000);
	// https://github.com/Slamtec/rplidar_sdk/issues/36.
	//mSleep(20);
	mSleep(pRPLIDAR->motordelay);

	return EXIT_SUCCESS;
}

// Undocumented... 	
// https://github.com/Slamtec/rplidar_sdk/issues/36?
inline int GetStartupMessageRPLIDAR(RPLIDAR* pRPLIDAR)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
	mSleep(100);
#ifdef FORCE_RPLIDAR_SDK_V1
	if (IS_FAIL(pRPLIDAR->drv->clearNetSerialRxCache()))
	{
		printf("A RPLIDAR is not responding correctly : clearNetSerialRxCache() failed. \n");
		return EXIT_FAILURE;
	}
#else
	pRPLIDAR->channel->flush();
#endif // FORCE_RPLIDAR_SDK_V1
#else
	//unsigned char databuf[57]; // A2...
	//unsigned char databuf[MAX_NB_BYTES_RPLIDAR];
	//int nbReadBytes = 0;

	//// Undocumented response for A2...
	//memset(databuf, 0, sizeof(databuf));
	//if (ReadAllRS232Port(&pRPLIDAR->RS232Port, databuf, sizeof(databuf)) != EXIT_SUCCESS)
	//{ 
	//	printf("A RPLIDAR is not responding correctly. \n");
	//	return EXIT_FAILURE;	
	//}

	// Undocumented response...
	mSleep(100);

	//memset(databuf, 0, sizeof(databuf));
	//if (ReadRS232Port(&pRPLIDAR->RS232Port, databuf, sizeof(databuf), &nbReadBytes) != EXIT_SUCCESS)
	//{ 
	//	//printf("Warning : A RPLIDAR might not be responding correctly. \n");
	//	//return EXIT_FAILURE;	
	//}

	if (PurgeRS232Port(&pRPLIDAR->RS232Port) != EXIT_SUCCESS)
	{
		printf("Error purging data from a RPLIDAR. \n");
		return EXIT_FAILURE;
	}
	// Need to purge twice on Mac OS otherwise next read() would fail...?
	if (PurgeRS232Port(&pRPLIDAR->RS232Port) != EXIT_SUCCESS)
	{
		printf("Error purging data from a RPLIDAR. \n");
		return EXIT_FAILURE;
	}
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	return EXIT_SUCCESS;
}

inline int ClearCacheRPLIDAR(RPLIDAR* pRPLIDAR)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
#ifdef FORCE_RPLIDAR_SDK_V1
	if (IS_FAIL(pRPLIDAR->drv->clearNetSerialRxCache()))
	{
		printf("A RPLIDAR is not responding correctly : clearNetSerialRxCache() failed. \n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
#else
	pRPLIDAR->channel->flush();
	return EXIT_SUCCESS;
#endif // FORCE_RPLIDAR_SDK_V1
#else
	if (PurgeRS232Port(&pRPLIDAR->RS232Port) != EXIT_SUCCESS)
	{
		printf("Error purging data from a RPLIDAR. \n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
}

inline int GetHealthRequestRPLIDAR(RPLIDAR* pRPLIDAR, BOOL* pbProtectionStop)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
    sl_lidar_response_device_health_t healthinfo;

	if (SL_IS_FAIL(pRPLIDAR->drv->getHealth(healthinfo)))
	{
		printf("A RPLIDAR is not responding correctly : getHealth() failed. \n");
		return EXIT_FAILURE;
	}

	// Analyze the data response.
	*pbProtectionStop = (healthinfo.status == SL_LIDAR_STATUS_ERROR)? TRUE: FALSE;
#else
	unsigned char reqbuf[] = {START_FLAG1_RPLIDAR,GET_HEALTH_REQUEST_RPLIDAR};
	unsigned char databuf[3];
	int DataResponseLength = 0, SendMode = 0, DataType = 0;

	// Send request.
	if (WriteAllRS232Port(&pRPLIDAR->RS232Port, reqbuf, sizeof(reqbuf)) != EXIT_SUCCESS)
	{
		printf("Error writing data to a RPLIDAR. \n");
		return EXIT_FAILURE;
	}

	// Receive the response descriptor.
	if (GetResponseDescriptorRPLIDAR(pRPLIDAR, &DataResponseLength, &SendMode, &DataType) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	// Quick check of the response descriptor.
	if ((DataResponseLength != 3)||(DataType != DEVHEALTH_RESPONSE_RPLIDAR))
	{ 
		printf("A RPLIDAR is not responding correctly : Bad response descriptor. \n");
		return EXIT_FAILURE;	
	}

	// Receive the data response.
	memset(databuf, 0, sizeof(databuf));
	if (ReadAllRS232Port(&pRPLIDAR->RS232Port, databuf, sizeof(databuf)) != EXIT_SUCCESS)
	{ 
		printf("A RPLIDAR is not responding correctly. \n");
		return EXIT_FAILURE;	
	}

	// Analyze the data response.
	*pbProtectionStop = (databuf[0] == STATUS_ERROR_RPLIDAR)? TRUE: FALSE;
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	return EXIT_SUCCESS;
}

// SerialNumber must be a null-terminated string of at least MAX_BUF_LEN_SERIAL_NUMBER_RPLIDAR bytes, including 0.
inline int GetInfoRequestRPLIDAR(RPLIDAR* pRPLIDAR, int* pModelID, int* pHardwareVersion, int* pFirmwareMajor, int* pFirmwareMinor, char* SerialNumber)
{
	int i = 0;

#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
    sl_lidar_response_device_info_t devinfo;

	if (SL_IS_FAIL(pRPLIDAR->drv->getDeviceInfo(devinfo)))
	{
		printf("A RPLIDAR is not responding correctly : getDeviceInfo() failed. \n");
		return EXIT_FAILURE;
	}

	// Analyze the data response.
	*pModelID = devinfo.model;
	*pFirmwareMinor = (devinfo.firmware_version & 0x00FF);
	*pFirmwareMajor = (devinfo.firmware_version >> 8);
	*pHardwareVersion = devinfo.hardware_version;

	// 128bit unique serial number, when converting to text in hex, the Least Significant Byte prints first.
	memset(SerialNumber, 0, MAX_BUF_LEN_SERIAL_NUMBER_RPLIDAR);
	for (i = 0; i < NB_BYTES_SERIAL_NUMBER_RPLIDAR; i++)
	{
		sprintf(SerialNumber+2*i, "%02X", (int)(unsigned char)devinfo.serialnum[i]);
	}
#else
	unsigned char reqbuf[] = {START_FLAG1_RPLIDAR,GET_INFO_REQUEST_RPLIDAR};
	unsigned char databuf[20];
	int DataResponseLength = 0, SendMode = 0, DataType = 0;

	// Send request.
	if (WriteAllRS232Port(&pRPLIDAR->RS232Port, reqbuf, sizeof(reqbuf)) != EXIT_SUCCESS)
	{
		printf("Error writing data to a RPLIDAR. \n");
		return EXIT_FAILURE;
	}

	// Receive the response descriptor.
	if (GetResponseDescriptorRPLIDAR(pRPLIDAR, &DataResponseLength, &SendMode, &DataType) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	// Quick check of the response descriptor.
	if ((DataResponseLength != 20)||(DataType != DEVINFO_RESPONSE_RPLIDAR))
	{ 
		printf("A RPLIDAR is not responding correctly : Bad response descriptor. \n");
		return EXIT_FAILURE;	
	}

	// Receive the data response.
	memset(databuf, 0, sizeof(databuf));
	if (ReadAllRS232Port(&pRPLIDAR->RS232Port, databuf, sizeof(databuf)) != EXIT_SUCCESS)
	{ 
		printf("A RPLIDAR is not responding correctly. \n");
		return EXIT_FAILURE;	
	}

	// Analyze the data response.
	*pModelID = databuf[0];
	*pFirmwareMinor = databuf[1];
	*pFirmwareMajor = databuf[2];
	*pHardwareVersion = databuf[3];

	// 128bit unique serial number, when converting to text in hex, the Least Significant Byte prints first.
	memset(SerialNumber, 0, MAX_BUF_LEN_SERIAL_NUMBER_RPLIDAR);
	for (i = 0; i < NB_BYTES_SERIAL_NUMBER_RPLIDAR; i++)
	{
		sprintf(SerialNumber+2*i, "%02X", (int)(unsigned char)databuf[i+4]);
	}
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	return EXIT_SUCCESS;
}

// Probably deprecated since it might depend on the scan mode...
// Tstandard, Texpress : Time in us used when RPLIDAR takes a single laser ranging in SCAN and EXPRESS_SCAN modes.
inline int GetSampleRateRequestRPLIDAR(RPLIDAR* pRPLIDAR, int* pTstandard, int* pTexpress)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
	UNREFERENCED_PARAMETER(pRPLIDAR);
	UNREFERENCED_PARAMETER(pTstandard);
	UNREFERENCED_PARAMETER(pTexpress);
	printf("RPLIDAR : Not implemented. \n");
	return EXIT_NOT_IMPLEMENTED;
#else
	unsigned char reqbuf[] = {START_FLAG1_RPLIDAR,GET_SAMPLERATE_REQUEST_RPLIDAR};
	unsigned char databuf[4];
	int DataResponseLength = 0, SendMode = 0, DataType = 0;

	// Send request.
	if (WriteAllRS232Port(&pRPLIDAR->RS232Port, reqbuf, sizeof(reqbuf)) != EXIT_SUCCESS)
	{
		printf("Error writing data to a RPLIDAR. \n");
		return EXIT_FAILURE;
	}

	// Receive the response descriptor.
	if (GetResponseDescriptorRPLIDAR(pRPLIDAR, &DataResponseLength, &SendMode, &DataType) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	// Quick check of the response descriptor.
	if ((DataResponseLength != 4)||(DataType != SAMPLERATE_RESPONSE_RPLIDAR))
	{ 
		printf("A RPLIDAR is not responding correctly : Bad response descriptor. \n");
		return EXIT_FAILURE;	
	}

	// Receive the data response.
	memset(databuf, 0, sizeof(databuf));
	if (ReadAllRS232Port(&pRPLIDAR->RS232Port, databuf, sizeof(databuf)) != EXIT_SUCCESS)
	{ 
		printf("A RPLIDAR is not responding correctly. \n");
		return EXIT_FAILURE;	
	}

	// Analyze the data response.
	*pTstandard = (unsigned short)((databuf[1]<<8)|databuf[0]);
	*pTexpress = (unsigned short)((databuf[3]<<8)|databuf[2]);

	return EXIT_SUCCESS;
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
}

inline int GetTypicalScanModeRPLIDAR(RPLIDAR* pRPLIDAR, int* pScanModeID)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
	unsigned short scanmodeid = 0;

	if (SL_IS_FAIL(pRPLIDAR->drv->getTypicalScanMode(scanmodeid)))
	{
		printf("A RPLIDAR is not responding correctly : getTypicalScanMode() failed. \n");
		return EXIT_FAILURE;
	}
	*pScanModeID = (int)scanmodeid;
	return EXIT_SUCCESS;
#else
	unsigned char databuf[6];
	unsigned short scanmodeid = 0;

	memset(databuf, 0, sizeof(databuf));
	if (GetConfRPLIDAR(pRPLIDAR, LIDAR_CONF_SCAN_MODE_TYPICAL_RPLIDAR, NULL, 0, databuf, 6) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	if (databuf[0] != (unsigned char)LIDAR_CONF_SCAN_MODE_TYPICAL_RPLIDAR)
	{
		printf("A RPLIDAR is not responding correctly : Bad response payload type. \n");
		return EXIT_FAILURE;
	}
	scanmodeid = (unsigned short)((databuf[5]<<8)|databuf[4]);
	*pScanModeID = (int)scanmodeid;
	return EXIT_SUCCESS;
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
}

// MAX_NB_SCAN_MODES_RPLIDAR scanmodes...
inline int GetAllSupportedScanModesRPLIDAR(RPLIDAR* pRPLIDAR, RPLIDARSCANMODE* pScanModes)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
#ifdef FORCE_RPLIDAR_SDK_V1
	std::vector<RplidarScanMode> outModes;
#else
	std::vector<LidarScanMode> outModes;
#endif // FORCE_RPLIDAR_SDK_V1
	unsigned int i = 0;

	if (SL_IS_FAIL(pRPLIDAR->drv->getAllSupportedScanModes(outModes)))
	{
		printf("A RPLIDAR is not responding correctly : getAllSupportedScanModes() failed. \n");
		return EXIT_FAILURE;
	}
	if (outModes.size() > MAX_NB_SCAN_MODES_RPLIDAR) printf("Warning : RPLIDAR unsupported scanmodes. \n");
	memset(pScanModes, 0, sizeof(RPLIDARSCANMODE)*MAX_NB_SCAN_MODES_RPLIDAR);
	for (i = 0; i < min(outModes.size(), (unsigned int)MAX_NB_SCAN_MODES_RPLIDAR); i++)
	{
		pScanModes[i].id = (int)outModes[i].id;
		pScanModes[i].us_per_sample = (double)outModes[i].us_per_sample;
		pScanModes[i].max_distance = (double)outModes[i].max_distance;
		pScanModes[i].ans_type = (int)outModes[i].ans_type;
		memcpy(pScanModes[i].scan_mode, outModes[i].scan_mode, sizeof(pScanModes[i].scan_mode));
	}
	return EXIT_SUCCESS;
#else
	unsigned char databuf[68];
	unsigned short scanmodecount = 0;
	unsigned int i = 0, uspersample = 0, maxdistance = 0;

	memset(databuf, 0, sizeof(databuf));
	if (GetConfRPLIDAR(pRPLIDAR, LIDAR_CONF_SCAN_MODE_COUNT_RPLIDAR, NULL, 0, databuf, 6) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	if (databuf[0] != (unsigned char)LIDAR_CONF_SCAN_MODE_COUNT_RPLIDAR)
	{
		printf("A RPLIDAR is not responding correctly : Bad response payload type. \n");
		return EXIT_FAILURE;
	}
	scanmodecount = (unsigned short)((databuf[5]<<8)|databuf[4]);
	if (scanmodecount <= 0)
	{
		printf("A RPLIDAR is not responding correctly. \n");
		return EXIT_FAILURE;
	}
	if (scanmodecount > MAX_NB_SCAN_MODES_RPLIDAR) printf("Warning : RPLIDAR unsupported scanmodes. \n");

	memset(pScanModes, 0, sizeof(RPLIDARSCANMODE)*MAX_NB_SCAN_MODES_RPLIDAR);
	for (i = 0; i < min(scanmodecount, (unsigned int)MAX_NB_SCAN_MODES_RPLIDAR); i++)
	{
		pScanModes[i].id = (int)i;
		memset(databuf, 0, sizeof(databuf));
		if (GetConfRPLIDAR(pRPLIDAR, LIDAR_CONF_SCAN_MODE_US_PER_SAMPLE_RPLIDAR, (unsigned char*)&i, 2, databuf, 8) != EXIT_SUCCESS)
		{
			return EXIT_FAILURE;
		}
		if (databuf[0] != (unsigned char)LIDAR_CONF_SCAN_MODE_US_PER_SAMPLE_RPLIDAR)
		{
			printf("A RPLIDAR is not responding correctly : Bad response payload type. \n");
			return EXIT_FAILURE;
		}
		memcpy((unsigned char*)&uspersample, databuf+4, 4);
		pScanModes[i].us_per_sample = (double)(uspersample/(1<<8));

		memset(databuf, 0, sizeof(databuf));
		if (GetConfRPLIDAR(pRPLIDAR, LIDAR_CONF_SCAN_MODE_MAX_DISTANCE_RPLIDAR, (unsigned char*)&i, 2, databuf, 8) != EXIT_SUCCESS)
		{
			return EXIT_FAILURE;
		}
		if (databuf[0] != (unsigned char)LIDAR_CONF_SCAN_MODE_MAX_DISTANCE_RPLIDAR)
		{
			printf("A RPLIDAR is not responding correctly : Bad response payload type. \n");
			return EXIT_FAILURE;
		}
		memcpy((unsigned char*)&maxdistance, databuf+4, 4);
		pScanModes[i].max_distance = (double)(maxdistance/(1<<8));

		memset(databuf, 0, sizeof(databuf));
		if (GetConfRPLIDAR(pRPLIDAR, LIDAR_CONF_SCAN_MODE_ANS_TYPE_RPLIDAR, (unsigned char*)&i, 2, databuf, 5) != EXIT_SUCCESS)
		{
			return EXIT_FAILURE;
		}
		if (databuf[0] != (unsigned char)LIDAR_CONF_SCAN_MODE_ANS_TYPE_RPLIDAR)
		{
			printf("A RPLIDAR is not responding correctly : Bad response payload type. \n");
			return EXIT_FAILURE;
		}
		pScanModes[i].ans_type = (int)databuf[4];

		memset(databuf, 0, sizeof(databuf));
		if (GetConfRPLIDAR(pRPLIDAR, LIDAR_CONF_SCAN_MODE_NAME_RPLIDAR, (unsigned char*)&i, 2, databuf, 64) != EXIT_SUCCESS)
		{
			return EXIT_FAILURE;
		}
		if (databuf[0] != (unsigned char)LIDAR_CONF_SCAN_MODE_NAME_RPLIDAR)
		{
			printf("A RPLIDAR is not responding correctly : Bad response payload type. \n");
			return EXIT_FAILURE;
		}
		memset(pScanModes[i].scan_mode, 0, sizeof(pScanModes[i].scan_mode));
		memcpy(pScanModes[i].scan_mode, databuf+4, sizeof(pScanModes[i].scan_mode));
	}
	return EXIT_SUCCESS;
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
}

// Undocumented...
// Inaccurate at the moment since it depends on the hardware version...
inline int CheckMotorControlSupportRequestRPLIDAR(RPLIDAR* pRPLIDAR, int* pSupport)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
#ifdef FORCE_RPLIDAR_SDK_V1
	bool support = false;
#else
	MotorCtrlSupport support;
#endif // FORCE_RPLIDAR_SDK_V1
	if (SL_IS_FAIL(pRPLIDAR->drv->checkMotorCtrlSupport(support)))
	{
		printf("A RPLIDAR is not responding correctly : checkMotorCtrlSupport() failed. \n");
		return EXIT_FAILURE;
	}
	*pSupport = (int)support;
#else
	unsigned char reqbuf[] = {START_FLAG1_RPLIDAR,GET_ACC_BOARD_FLAG_REQUEST_RPLIDAR};
	unsigned char databuf[4];
	int DataResponseLength = 0, SendMode = 0, DataType = 0;

	// Send request.
	if (WriteAllRS232Port(&pRPLIDAR->RS232Port, reqbuf, sizeof(reqbuf)) != EXIT_SUCCESS)
	{
		printf("Error writing data to a RPLIDAR. \n");
		return EXIT_FAILURE;
	}

	// Receive the response descriptor.
	if (GetResponseDescriptorRPLIDAR(pRPLIDAR, &DataResponseLength, &SendMode, &DataType) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	// Quick check of the response descriptor.
	if ((DataResponseLength != 4)||(DataType != GET_ACC_BOARD_FLAG_REQUEST_RPLIDAR))
	{ 
		printf("A RPLIDAR is not responding correctly : Bad response descriptor. \n");
		return EXIT_FAILURE;	
	}

	// Receive the data response.
	memset(databuf, 0, sizeof(databuf));
	if (ReadAllRS232Port(&pRPLIDAR->RS232Port, databuf, sizeof(databuf)) != EXIT_SUCCESS)
	{ 
		printf("A RPLIDAR is not responding correctly. \n");
		return EXIT_FAILURE;	
	}

	// Analyze the data response.
	*pSupport = (databuf[0]&0x01);
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	return EXIT_SUCCESS;
}

// Undocumented...
inline int SetMotorPWMRequestRPLIDAR(RPLIDAR* pRPLIDAR, int pwm)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
#ifdef FORCE_RPLIDAR_SDK_V1
	if (IS_FAIL(pRPLIDAR->drv->setMotorPWM((_u16)pwm)))
	{
		printf("A RPLIDAR is not responding correctly : setMotorPWM() failed. \n");
		return EXIT_FAILURE;
	}
#else
	if (SL_IS_FAIL(pRPLIDAR->drv->setMotorSpeed((sl_u16)pwm)))
	{
		printf("A RPLIDAR is not responding correctly : setMotorSpeed() failed. \n");
		return EXIT_FAILURE;
	}
#endif // FORCE_RPLIDAR_SDK_V1
#else
	unsigned char reqbuf[] = {START_FLAG1_RPLIDAR,SET_MOTOR_PWM_REQUEST_RPLIDAR,0x02,0,0,0};

	reqbuf[3] = (unsigned char)pwm;
	reqbuf[4] = (unsigned char)(pwm>>8);
	reqbuf[5] = ComputeChecksumRPLIDAR(reqbuf, sizeof(reqbuf));

	// Send request.
	if (WriteAllRS232Port(&pRPLIDAR->RS232Port, reqbuf, sizeof(reqbuf)) != EXIT_SUCCESS)
	{
		printf("Error writing data to a RPLIDAR. \n");
		return EXIT_FAILURE;
	}

	mSleep(500);
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	return EXIT_SUCCESS;
}

inline int SetLidarSpinSpeedRequestRPLIDAR(RPLIDAR* pRPLIDAR, int rpm)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
#ifdef FORCE_RPLIDAR_SDK_V1
#ifdef SLAMTEC_LIDAR_SDK_VERSION
	if (IS_FAIL(pRPLIDAR->drv->setMotorPWM((_u16)rpm)))
	{
		printf("A RPLIDAR is not responding correctly : setMotorPWM() failed. \n");
		return EXIT_FAILURE;
	}
#else
	if (IS_FAIL(pRPLIDAR->drv->setLidarSpinSpeed((_u16)rpm)))
	{
		printf("A RPLIDAR is not responding correctly : setLidarSpinSpeed() failed. \n");
		return EXIT_FAILURE;
	}
#endif // SLAMTEC_LIDAR_SDK_VERSION
#else
	if (SL_IS_FAIL(pRPLIDAR->drv->setMotorSpeed((sl_u16)rpm)))
	{
		printf("A RPLIDAR is not responding correctly : setMotorSpeed() failed. \n");
		return EXIT_FAILURE;
	}
#endif // FORCE_RPLIDAR_SDK_V1
#else
	unsigned char reqbuf[] = {START_FLAG1_RPLIDAR,SET_MOTOR_SPEED_CTRL_REQUEST_RPLIDAR,0x02,0,0,0};

	reqbuf[3] = (unsigned char)rpm;
	reqbuf[4] = (unsigned char)(rpm>>8);
	reqbuf[5] = ComputeChecksumRPLIDAR(reqbuf, sizeof(reqbuf));

	// Send request.
	if (WriteAllRS232Port(&pRPLIDAR->RS232Port, reqbuf, sizeof(reqbuf)) != EXIT_SUCCESS)
	{
		printf("Error writing data to a RPLIDAR. \n");
		return EXIT_FAILURE;
	}
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	return EXIT_SUCCESS;
}

inline int StartMotorRPLIDAR(RPLIDAR* pRPLIDAR)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
#ifdef FORCE_RPLIDAR_SDK_V1
	if (IS_FAIL(pRPLIDAR->drv->startMotor()))
	{
		printf("A RPLIDAR is not responding correctly : startMotor() failed. \n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
#else
	// startMotor() equivalent from https://github.com/Slamtec/sllidar_ros2/blob/main/src/sllidar_node.cpp...
	if (SL_IS_FAIL(pRPLIDAR->drv->setMotorSpeed()))
	{
		printf("A RPLIDAR is not responding correctly : setMotorSpeed() failed. \n");
		return EXIT_FAILURE;
	}
	if (SL_IS_FAIL(pRPLIDAR->drv->startScan(0,1)))
	{
		printf("A RPLIDAR is not responding correctly : startScan() failed. \n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
#endif // FORCE_RPLIDAR_SDK_V1
#else
	UNREFERENCED_PARAMETER(pRPLIDAR);
	printf("RPLIDAR : Not implemented. \n");
	return EXIT_NOT_IMPLEMENTED;
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
}

inline int StopMotorRPLIDAR(RPLIDAR* pRPLIDAR)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
#ifdef FORCE_RPLIDAR_SDK_V1
	if (IS_FAIL(pRPLIDAR->drv->stopMotor()))
	{
		printf("A RPLIDAR is not responding correctly : stopMotor() failed. \n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
#else
	if (SL_IS_FAIL(pRPLIDAR->drv->stop()))
	{
		printf("A RPLIDAR is not responding correctly : stop() failed. \n");
		return EXIT_FAILURE;
	}
	if (SL_IS_FAIL(pRPLIDAR->drv->setMotorSpeed(0)))
	{
		printf("A RPLIDAR is not responding correctly : setMotorSpeed() failed. \n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
#endif // FORCE_RPLIDAR_SDK_V1
#else
	UNREFERENCED_PARAMETER(pRPLIDAR);
	printf("RPLIDAR : Not implemented. \n");
	return EXIT_NOT_IMPLEMENTED;
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
}

inline int StartScanRequestRPLIDAR(RPLIDAR* pRPLIDAR)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
	if (SL_IS_FAIL(pRPLIDAR->drv->startScan(false, false)))
	{
		printf("A RPLIDAR is not responding correctly : startScan() failed. \n");
		return EXIT_FAILURE;
	}
	pRPLIDAR->nodes_cache->clear();
#else
	unsigned char reqbuf[] = {START_FLAG1_RPLIDAR,SCAN_REQUEST_RPLIDAR};
	int DataResponseLength = 0, SendMode = 0, DataType = 0;

	// Send request.
	if (WriteAllRS232Port(&pRPLIDAR->RS232Port, reqbuf, sizeof(reqbuf)) != EXIT_SUCCESS)
	{
		printf("Error writing data to a RPLIDAR. \n");
		return EXIT_FAILURE;
	}

	// Receive the response descriptor.
	if (GetResponseDescriptorRPLIDAR(pRPLIDAR, &DataResponseLength, &SendMode, &DataType) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	// Quick check of the response descriptor.
	if ((DataResponseLength != NB_BYTES_SCAN_DATA_RESPONSE_RPLIDAR)||
		(SendMode != SINGLE_REQUEST_MULTIPLE_RESPONSE_SEND_MODE_RPLIDAR)||
		(DataType != MEASUREMENT_RESPONSE_RPLIDAR))
	{ 
		printf("A RPLIDAR is not responding correctly : Bad response descriptor. \n");
		return EXIT_FAILURE;	
	}
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	return EXIT_SUCCESS;
}

inline int StartForceScanRequestRPLIDAR(RPLIDAR* pRPLIDAR)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
	if (SL_IS_FAIL(pRPLIDAR->drv->startScan(true, false)))
	{
		printf("A RPLIDAR is not responding correctly : startScan() failed. \n");
		return EXIT_FAILURE;
	}
	pRPLIDAR->nodes_cache->clear();
#else
	unsigned char reqbuf[] = {START_FLAG1_RPLIDAR,FORCE_SCAN_REQUEST_RPLIDAR};
	int DataResponseLength = 0, SendMode = 0, DataType = 0;

	// Send request.
	if (WriteAllRS232Port(&pRPLIDAR->RS232Port, reqbuf, sizeof(reqbuf)) != EXIT_SUCCESS)
	{
		printf("Error writing data to a RPLIDAR. \n");
		return EXIT_FAILURE;
	}

	// Receive the response descriptor.
	if (GetResponseDescriptorRPLIDAR(pRPLIDAR, &DataResponseLength, &SendMode, &DataType) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	// Quick check of the response descriptor.
	if ((DataResponseLength != NB_BYTES_FORCE_SCAN_DATA_RESPONSE_RPLIDAR)||
		(SendMode != SINGLE_REQUEST_MULTIPLE_RESPONSE_SEND_MODE_RPLIDAR)||
		(DataType != MEASUREMENT_RESPONSE_RPLIDAR))
	{ 
		printf("A RPLIDAR is not responding correctly : Bad response descriptor. \n");
		return EXIT_FAILURE;	
	}
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	return EXIT_SUCCESS;
}

// *pDistance in m, *pAngle in rad.
inline int GetScanDataResponseRPLIDAR(RPLIDAR* pRPLIDAR, double* pDistance, double* pAngle, BOOL* pbNewScan, int* pQuality)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
#if !defined(FORCE_RPLIDAR_SDK_V1) || defined(SLAMTEC_LIDAR_SDK_VERSION)
	sl_lidar_response_measurement_node_hq_t nodes[1+MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR];
#else
	sl_lidar_response_measurement_node_hq_t nodes[1];
#endif // !defined(FORCE_RPLIDAR_SDK_V1) || defined(SLAMTEC_LIDAR_SDK_VERSION)
	size_t nodesCount = sizeof(nodes)/sizeof(sl_lidar_response_measurement_node_hq_t);
	size_t nodesRead = 0;
	int nbMeasurements = 1, j = 0;
	CHRONO chrono;

	StartChrono(&chrono);

	if (!pRPLIDAR->nodes_cache->empty())
	{
		for (j = 0; j < min(nbMeasurements, (int)pRPLIDAR->nodes_cache->size()); j++)
		{
			nodes[j] = pRPLIDAR->nodes_cache->front();
			pRPLIDAR->nodes_cache->pop_front();
		}
		nodesRead = min(nbMeasurements, (int)pRPLIDAR->nodes_cache->size());
	}
	while ((int)nodesRead < nbMeasurements)
	{
		if (GetTimeElapsedChronoQuick(&chrono) > pRPLIDAR->timeout)
		{
			printf("A RPLIDAR is not responding correctly : getScanDataWithIntervalHq() timeout. \n");
			return EXIT_TIMEOUT;
		}
		nodesCount = nbMeasurements-nodesRead;
		if (SL_IS_FAIL(pRPLIDAR->drv->getScanDataWithIntervalHq(nodes+nodesRead, nodesCount)))
		{
			uSleep(1000);
		}
		else nodesRead += nodesCount;
	}
	if ((int)nodesRead > nbMeasurements)
	{
		for (j = nbMeasurements; j < (int)nodesRead; j++)
		{
			pRPLIDAR->nodes_cache->push_back(nodes[j]);
		}
	}

	// Analyze the data response.
	*pbNewScan = (nodes[0].flag & SL_LIDAR_RESP_MEASUREMENT_SYNCBIT);
	*pQuality = (unsigned char)(nodes[0].quality);

	// Convert in rad.
	*pAngle = fmod_2PI_deg2rad(-nodes[0].angle_z_q14*90.0/(1 << 14));

	// Convert in m.
	*pDistance = nodes[0].dist_mm_q2/4000.0;
#else
	unsigned char recvbuf[MAX_NB_BYTES_RPLIDAR];
	int BytesReceived = 0, recvbuflen = 0, res = EXIT_FAILURE, nbBytesToRequest = 0, nbBytesDiscarded = 0;
	unsigned char* ptr = NULL;
	CHRONO chrono;

	StartChrono(&chrono);

	// Prepare the buffers.
	memset(recvbuf, 0, sizeof(recvbuf));
	recvbuflen = MAX_NB_BYTES_RPLIDAR-1; // The last character must be a 0 to be a valid string for sscanf.
	BytesReceived = 0;

	// Suppose that there are not so many data to discard.
	// First try to get directly the desired data response...

	nbBytesToRequest = NB_BYTES_SCAN_DATA_RESPONSE_RPLIDAR;
	if (ReadAllRS232Port(&pRPLIDAR->RS232Port, recvbuf, nbBytesToRequest) != EXIT_SUCCESS)
	{
		printf("Error reading data from a RPLIDAR. \n");
		return EXIT_FAILURE;
	}
	BytesReceived += nbBytesToRequest;
	
	for (;;)
	{
		res = FindScanDataResponseRPLIDAR(recvbuf, BytesReceived, pbNewScan, pQuality, pAngle, pDistance, &nbBytesToRequest, &ptr, &nbBytesDiscarded);
		if (res == EXIT_SUCCESS) break;
		if (res == EXIT_FAILURE)
		{
			nbBytesToRequest = min(NB_BYTES_SCAN_DATA_RESPONSE_RPLIDAR, nbBytesDiscarded);
		}	
		memmove(recvbuf, recvbuf+nbBytesDiscarded, BytesReceived-nbBytesDiscarded);
		BytesReceived -= nbBytesDiscarded;
		if (BytesReceived+nbBytesToRequest > recvbuflen)
		{
			printf("Error reading data from a RPLIDAR : Invalid data. \n");
			return EXIT_INVALID_DATA;
		}
		if (ReadAllRS232Port(&pRPLIDAR->RS232Port, recvbuf+BytesReceived, nbBytesToRequest) != EXIT_SUCCESS)
		{
			printf("Error reading data from a RPLIDAR. \n");
			return EXIT_FAILURE;
		}
		BytesReceived += nbBytesToRequest;
		if (GetTimeElapsedChronoQuick(&chrono) > TIMEOUT_MESSAGE_RPLIDAR)
		{
			printf("Error reading data from a RPLIDAR : Data response timeout. \n");
			return EXIT_TIMEOUT;
		}
	}

	if (BytesReceived-nbBytesDiscarded-NB_BYTES_SCAN_DATA_RESPONSE_RPLIDAR > 0)
	{
		printf("Warning getting data from a RPLIDAR : Unexpected data after a data response. \n");
	}
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	return EXIT_SUCCESS;
}

inline int StartExpressScanRequestRPLIDAR(RPLIDAR* pRPLIDAR)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
	//unsigned short scanMode = 0;

	//if (SL_IS_FAIL(pRPLIDAR->drv->getTypicalScanMode(scanMode)))
	//{
	//	printf("A RPLIDAR is not responding correctly : getTypicalScanMode() failed. \n");
	//	return EXIT_FAILURE;
	//}
	if (SL_IS_FAIL(pRPLIDAR->drv->startScanExpress(false, SL_LIDAR_CONF_SCAN_COMMAND_EXPRESS)))
	{
		printf("A RPLIDAR is not responding correctly : startScanExpress() failed. \n");
		return EXIT_FAILURE;
	}
	pRPLIDAR->nodes_cache->clear();
#else
	unsigned char reqbuf[] = {START_FLAG1_RPLIDAR,EXPRESS_SCAN_REQUEST_RPLIDAR,0x05,0,0,0,0,0,0x22};
	int DataResponseLength = 0, SendMode = 0, DataType = 0;

	// Send request.
	if (WriteAllRS232Port(&pRPLIDAR->RS232Port, reqbuf, sizeof(reqbuf)) != EXIT_SUCCESS)
	{
		printf("Error writing data to a RPLIDAR. \n");
		return EXIT_FAILURE;
	}

	// Receive the response descriptor.
	if (GetResponseDescriptorRPLIDAR(pRPLIDAR, &DataResponseLength, &SendMode, &DataType) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	// Quick check of the response descriptor.
	if ((DataResponseLength != NB_BYTES_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR)||
		(SendMode != SINGLE_REQUEST_MULTIPLE_RESPONSE_SEND_MODE_RPLIDAR)||
		(DataType != MEASUREMENT_CAPSULED_RESPONSE_RPLIDAR))
	{ 
		printf("A RPLIDAR is not responding correctly : Unhandled response descriptor, please try another scan mode. \n");
		return EXIT_NOT_IMPLEMENTED;	
	}

	// The first data response might take some time to come, see https://github.com/ENSTABretagneRobotics/Hardware-MATLAB/issues/2...
	if (WaitForRS232Port(&pRPLIDAR->RS232Port, 1500, 5) != EXIT_SUCCESS)
	{
		printf("A RPLIDAR is not responding correctly. \n");
		return EXIT_FAILURE;
	}

	// Receive the first data response (2 data responses needed for angles computation...).
	memset(pRPLIDAR->esdata_prev, 0, sizeof(pRPLIDAR->esdata_prev));
	if (GetRawExpressScanDataResponseRPLIDAR(pRPLIDAR, pRPLIDAR->esdata_prev, NB_BYTES_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	return EXIT_SUCCESS;
}

// NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR distances, angles...
inline int GetExpressScanDataResponseRPLIDAR(RPLIDAR* pRPLIDAR, double* pDistances, double* pAngles, BOOL* pbNewScan)
{
	int j = 0;

#ifdef ENABLE_RPLIDAR_SDK_SUPPORT	
#if !defined(FORCE_RPLIDAR_SDK_V1) || defined(SLAMTEC_LIDAR_SDK_VERSION)
	sl_lidar_response_measurement_node_hq_t nodes[NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR+MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR];
#else
	sl_lidar_response_measurement_node_hq_t nodes[NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR];
#endif // !defined(FORCE_RPLIDAR_SDK_V1) || defined(SLAMTEC_LIDAR_SDK_VERSION)
	size_t nodesCount = sizeof(nodes)/sizeof(sl_lidar_response_measurement_node_hq_t);
	size_t nodesRead = 0;
	int nbMeasurements = NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR;
	CHRONO chrono;

	StartChrono(&chrono);

	if (!pRPLIDAR->nodes_cache->empty())
	{
		for (j = 0; j < min(nbMeasurements, (int)pRPLIDAR->nodes_cache->size()); j++)
		{
			nodes[j] = pRPLIDAR->nodes_cache->front();
			pRPLIDAR->nodes_cache->pop_front();
		}
		nodesRead = min(nbMeasurements, (int)pRPLIDAR->nodes_cache->size());
	}
	while ((int)nodesRead < nbMeasurements)
	{
		if (GetTimeElapsedChronoQuick(&chrono) > pRPLIDAR->timeout)
		{
			printf("A RPLIDAR is not responding correctly : getScanDataWithIntervalHq() timeout. \n");
			return EXIT_TIMEOUT;
		}
		nodesCount = nbMeasurements-nodesRead;
		if (SL_IS_FAIL(pRPLIDAR->drv->getScanDataWithIntervalHq(nodes+nodesRead, nodesCount)))
		{
			uSleep(1000);
		}
		else nodesRead += nodesCount;
	}
	if ((int)nodesRead > nbMeasurements)
	{
		for (j = nbMeasurements; j < (int)nodesRead; j++)
		{
			pRPLIDAR->nodes_cache->push_back(nodes[j]);
		}
	}

	// Analyze the data response.
	*pbNewScan = 0;

	//memset(pAngles, 0, nbMeasurements*sizeof(double));
	//memset(pDistances, 0, nbMeasurements*sizeof(double));
	for (j = 0; j < nbMeasurements; j++)
	{
		*pbNewScan = (*pbNewScan) | (nodes[j].flag & SL_LIDAR_RESP_MEASUREMENT_SYNCBIT);

		// Convert in rad.
		pAngles[j] = fmod_2PI_deg2rad(-nodes[j].angle_z_q14*90.0/(1 << 14));

		// Convert in m.
		pDistances[j] = nodes[j].dist_mm_q2/4000.0;
	}
#else
	unsigned char databuf[NB_BYTES_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR];
	unsigned short start_angle_q6 = 0;
	unsigned short start_angle_q6_prev = 0;
	unsigned short distance1 = 0;
	unsigned short distance2 = 0;
	char dtheta1_q3 = 0;
	char dtheta2_q3 = 0;
	double dtheta1 = 0;
	double dtheta2 = 0;
	double theta1 = 0;
	double theta2 = 0;

	// Receive the data response.
	memset(databuf, 0, sizeof(databuf));
	if (GetRawExpressScanDataResponseRPLIDAR(pRPLIDAR, databuf, NB_BYTES_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	start_angle_q6 = ((databuf[3] & 0x7F)<<8) | databuf[2];

	// Analyze the previous data response.
	start_angle_q6_prev = ((pRPLIDAR->esdata_prev[3] & 0x7F)<<8) | pRPLIDAR->esdata_prev[2];
	*pbNewScan = pRPLIDAR->esdata_prev[3]>>7;

	//memset(pAngles, 0, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR);
	//memset(pDistances, 0, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR);
	for (j = 0; j < NB_CABINS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR; j++)
	{
		distance1 = ((pRPLIDAR->esdata_prev[4+5*j+1]<<8)|pRPLIDAR->esdata_prev[4+5*j+0])>>2;
		distance2 = ((pRPLIDAR->esdata_prev[4+5*j+3]<<8)|pRPLIDAR->esdata_prev[5*j+2])>>2;
		dtheta1_q3 = ((pRPLIDAR->esdata_prev[4+5*j+0] & 0x03)<<4)|(pRPLIDAR->esdata_prev[4+5*j+4] & 0x0F);
		dtheta2_q3 = ((pRPLIDAR->esdata_prev[4+5*j+2] & 0x03)<<4)|(pRPLIDAR->esdata_prev[4+5*j+4]>>4);
		// Handle the sign bit...
		dtheta1 = ((dtheta1_q3 & 0x20)>>5)? (-~(dtheta1_q3 & 0x1F))/8.0: (dtheta1_q3 & 0x1F)/8.0;
		dtheta2 = ((dtheta2_q3 & 0x20)>>5)? (-~(dtheta2_q3 & 0x1F))/8.0: (dtheta2_q3 & 0x1F)/8.0;

		// k indexes in the formula of the documentation start at 1...
		theta1 = start_angle_q6_prev/64.0+AngleDiffRPLIDAR(start_angle_q6_prev/64.0, start_angle_q6/64.0)*(2*j+1)/(NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR)-dtheta1;
		theta2 = start_angle_q6_prev/64.0+AngleDiffRPLIDAR(start_angle_q6_prev/64.0, start_angle_q6/64.0)*(2*j+2)/(NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR)-dtheta2;

		// Convert in rad.
		pAngles[2*j+0] = fmod_2PI_deg2rad(-theta1);
		pAngles[2*j+1] = fmod_2PI_deg2rad(-theta2);

		// Convert in m.
		pDistances[2*j+0] = distance1/1000.0;
		pDistances[2*j+1] = distance2/1000.0;
	}

	memcpy(pRPLIDAR->esdata_prev, databuf, NB_BYTES_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR);
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	return EXIT_SUCCESS;
}

inline int StartOtherScanRequestRPLIDAR(RPLIDAR* pRPLIDAR, int scanmodeid)
{
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
	if (SL_IS_FAIL(pRPLIDAR->drv->startScanExpress(false, (unsigned short)scanmodeid)))
	{
		printf("A RPLIDAR is not responding correctly : startScanExpress() failed. \n");
		return EXIT_FAILURE;
	}
#else
	unsigned char reqbuf[] = {START_FLAG1_RPLIDAR,EXPRESS_SCAN_REQUEST_RPLIDAR,0x05,0,0,0,0,0,0};
	int DataResponseLength = 0, SendMode = 0, DataType = 0;

	reqbuf[3] = (unsigned char)scanmodeid;
	reqbuf[8] = ComputeChecksumRPLIDAR(reqbuf, sizeof(reqbuf));

	// Send request.
	if (WriteAllRS232Port(&pRPLIDAR->RS232Port, reqbuf, sizeof(reqbuf)) != EXIT_SUCCESS)
	{
		printf("Error writing data to a RPLIDAR. \n");
		return EXIT_FAILURE;
	}

	// Receive the response descriptor.
	if (GetResponseDescriptorRPLIDAR(pRPLIDAR, &DataResponseLength, &SendMode, &DataType) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	// Quick check of the response descriptor.
	if (((DataResponseLength != NB_BYTES_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR)&&(DataResponseLength != NB_BYTES_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR)&&(DataResponseLength != NB_BYTES_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR))||
		(SendMode != SINGLE_REQUEST_MULTIPLE_RESPONSE_SEND_MODE_RPLIDAR)||
		((DataType != MEASUREMENT_CAPSULED_RESPONSE_RPLIDAR)&&(DataType != MEASUREMENT_CAPSULED_ULTRA_RESPONSE_RPLIDAR)&&(DataType != MEASUREMENT_DENSE_CAPSULED_RESPONSE_RPLIDAR)))
	{ 
		printf("A RPLIDAR is not responding correctly : Bad response descriptor. \n");
		return EXIT_FAILURE;	
	}

	// The first data response might take some time to come, see https://github.com/ENSTABretagneRobotics/Hardware-MATLAB/issues/2...
	if (WaitForRS232Port(&pRPLIDAR->RS232Port, 1500, 5) != EXIT_SUCCESS)
	{
		printf("A RPLIDAR is not responding correctly. \n");
		return EXIT_FAILURE;
	}

	pRPLIDAR->esversion = DataType;

	// Receive the first data response (2 data responses needed for angles computation...).
	switch (pRPLIDAR->esversion)
	{
	case MEASUREMENT_CAPSULED_RESPONSE_RPLIDAR:
		PRINT_DEBUG_MESSAGE(("RPLIDAR Legacy Express Scan\n"));
		memset(pRPLIDAR->esdata_prev, 0, sizeof(pRPLIDAR->esdata_prev));
		if (GetRawExpressScanDataResponseRPLIDAR(pRPLIDAR, pRPLIDAR->esdata_prev, NB_BYTES_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR) != EXIT_SUCCESS)
		{
			return EXIT_FAILURE;
		}
		break;
	case MEASUREMENT_CAPSULED_ULTRA_RESPONSE_RPLIDAR:
		PRINT_DEBUG_MESSAGE(("RPLIDAR Extended Express Scan\n"));
		memset(pRPLIDAR->eesdata_prev, 0, sizeof(pRPLIDAR->eesdata_prev));
		if (GetRawExpressScanDataResponseRPLIDAR(pRPLIDAR, pRPLIDAR->eesdata_prev, NB_BYTES_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR) != EXIT_SUCCESS)
		{
			return EXIT_FAILURE;
		}

		// Need to update GetOtherScanDataResponseRPLIDAR()...

		printf("A RPLIDAR is not responding correctly : Unhandled response descriptor, please try another scan mode or rebuild using RPLIDAR SDK. \n");
		return EXIT_NOT_IMPLEMENTED;
		//break;
	case MEASUREMENT_DENSE_CAPSULED_RESPONSE_RPLIDAR:
		PRINT_DEBUG_MESSAGE(("RPLIDAR Dense Express Scan\n"));
		memset(pRPLIDAR->desdata_prev, 0, sizeof(pRPLIDAR->desdata_prev));
		if (GetRawExpressScanDataResponseRPLIDAR(pRPLIDAR, pRPLIDAR->desdata_prev, NB_BYTES_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR) != EXIT_SUCCESS)
		{
			return EXIT_FAILURE;
		}
		break;
	default:
		printf("A RPLIDAR is not responding correctly : Unhandled response descriptor. \n");
		return EXIT_FAILURE;
		//break;
	}
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
	return EXIT_SUCCESS;
}

// MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR distances, angles...
// *pNbMeasurements should contain the actual number of measurements set.
inline int GetOtherScanDataResponseRPLIDAR(RPLIDAR* pRPLIDAR, double* pDistances, double* pAngles, BOOL* pbNewScan, int* pNbMeasurements)
{
	int j = 0;

#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
#if !defined(FORCE_RPLIDAR_SDK_V1) || defined(SLAMTEC_LIDAR_SDK_VERSION)
	sl_lidar_response_measurement_node_hq_t nodes[NB_MEASUREMENTS_OTHER_SCAN_DATA_RESPONSE_RPLIDAR+MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR];
#else
	sl_lidar_response_measurement_node_hq_t nodes[NB_MEASUREMENTS_OTHER_SCAN_DATA_RESPONSE_RPLIDAR];
#endif // !defined(FORCE_RPLIDAR_SDK_V1) || defined(SLAMTEC_LIDAR_SDK_VERSION)
	size_t nodesCount = sizeof(nodes)/sizeof(sl_lidar_response_measurement_node_hq_t);
	size_t nodesRead = 0;
	CHRONO chrono;

	*pNbMeasurements = NB_MEASUREMENTS_OTHER_SCAN_DATA_RESPONSE_RPLIDAR;

	StartChrono(&chrono);

	while ((int)nodesRead < *pNbMeasurements)
	{
		if (GetTimeElapsedChronoQuick(&chrono) > pRPLIDAR->timeout)
		{
			printf("A RPLIDAR is not responding correctly : getScanDataWithIntervalHq() timeout. \n");
			return EXIT_TIMEOUT;
		}
		nodesCount = *pNbMeasurements-nodesRead;
		if (SL_IS_FAIL(pRPLIDAR->drv->getScanDataWithIntervalHq(nodes+nodesRead, nodesCount)))
		{
			uSleep(1000);
		}
		else nodesRead += nodesCount;
	}

	*pNbMeasurements = (int)nodesRead;

	// Analyze the data response.
	*pbNewScan = 0;

	//memset(pAngles, 0, nodesRead*sizeof(double));
	//memset(pDistances, 0, nodesRead*sizeof(double));
	for (j = 0; j < (int)nodesRead; j++)
	{
		*pbNewScan = (*pbNewScan) | (nodes[j].flag & SL_LIDAR_RESP_MEASUREMENT_SYNCBIT);

		// Convert in rad.
		pAngles[j] = fmod_2PI_deg2rad(-nodes[j].angle_z_q14*90.0/(1 << 14));

		// Convert in m.
		pDistances[j] = nodes[j].dist_mm_q2/4000.0;
	}
#else
	unsigned char databuf[max(max(NB_BYTES_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR, NB_BYTES_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR), NB_BYTES_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR)];
	unsigned short start_angle_q6 = 0;
	unsigned short start_angle_q6_prev = 0;

	unsigned short distance1 = 0; // Legacy.
	unsigned short distance2 = 0; // Legacy.
	char dtheta1_q3 = 0; // Legacy.
	char dtheta2_q3 = 0; // Legacy.
	double dtheta1 = 0; // Legacy.
	double dtheta2 = 0; // Legacy.
	double theta1 = 0; // Legacy.
	double theta2 = 0; // Legacy.

	//unsigned int major = 0, predict1 = 0, predict2 = 0; // Extended.

	unsigned short distance = 0; // Dense.
	double theta = 0; // Dense.

	// Receive the data response.
	memset(databuf, 0, sizeof(databuf));
	switch (pRPLIDAR->esversion)
	{
	case MEASUREMENT_CAPSULED_RESPONSE_RPLIDAR:
		if (GetRawExpressScanDataResponseRPLIDAR(pRPLIDAR, databuf, NB_BYTES_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR) != EXIT_SUCCESS)
		{
			return EXIT_FAILURE;
		}
		break;
	case MEASUREMENT_CAPSULED_ULTRA_RESPONSE_RPLIDAR:
		if (GetRawExpressScanDataResponseRPLIDAR(pRPLIDAR, databuf, NB_BYTES_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR) != EXIT_SUCCESS)
		{
			return EXIT_FAILURE;
		}
		break;
	case MEASUREMENT_DENSE_CAPSULED_RESPONSE_RPLIDAR:
		if (GetRawExpressScanDataResponseRPLIDAR(pRPLIDAR, databuf, NB_BYTES_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR) != EXIT_SUCCESS)
		{
			return EXIT_FAILURE;
		}
		break;
	default:
		printf("A RPLIDAR is not responding correctly : Unhandled response descriptor. \n");
		return EXIT_FAILURE;
		//break;
	}

	start_angle_q6 = ((databuf[3] & 0x7F)<<8) | databuf[2];

	switch (pRPLIDAR->esversion)
	{
	case MEASUREMENT_CAPSULED_RESPONSE_RPLIDAR:
		// Analyze the previous data response.
		start_angle_q6_prev = ((pRPLIDAR->esdata_prev[3] & 0x7F)<<8) | pRPLIDAR->esdata_prev[2];
		*pbNewScan = pRPLIDAR->esdata_prev[3]>>7;

		*pNbMeasurements = NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR;

		//memset(pAngles, 0, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR);
		//memset(pDistances, 0, NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR);
		for (j = 0; j < NB_CABINS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR; j++)
		{
			distance1 = ((pRPLIDAR->esdata_prev[4+5*j+1]<<8)|pRPLIDAR->esdata_prev[4+5*j+0])>>2;
			distance2 = ((pRPLIDAR->esdata_prev[4+5*j+3]<<8)|pRPLIDAR->esdata_prev[5*j+2])>>2;
			dtheta1_q3 = ((pRPLIDAR->esdata_prev[4+5*j+0] & 0x03)<<4)|(pRPLIDAR->esdata_prev[4+5*j+4] & 0x0F);
			dtheta2_q3 = ((pRPLIDAR->esdata_prev[4+5*j+2] & 0x03)<<4)|(pRPLIDAR->esdata_prev[4+5*j+4]>>4);
			// Handle the sign bit...
			dtheta1 = ((dtheta1_q3 & 0x20)>>5)? (-~(dtheta1_q3 & 0x1F))/8.0: (dtheta1_q3 & 0x1F)/8.0;
			dtheta2 = ((dtheta2_q3 & 0x20)>>5)? (-~(dtheta2_q3 & 0x1F))/8.0: (dtheta2_q3 & 0x1F)/8.0;

			// k indexes in the formula of the documentation start at 1...
			theta1 = start_angle_q6_prev/64.0+AngleDiffRPLIDAR(start_angle_q6_prev/64.0, start_angle_q6/64.0)*(2*j+1)/(NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR)-dtheta1;
			theta2 = start_angle_q6_prev/64.0+AngleDiffRPLIDAR(start_angle_q6_prev/64.0, start_angle_q6/64.0)*(2*j+2)/(NB_MEASUREMENTS_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR)-dtheta2;

			// Convert in rad.
			pAngles[2*j+0] = fmod_2PI_deg2rad(-theta1);
			pAngles[2*j+1] = fmod_2PI_deg2rad(-theta2);

			// Convert in m.
			pDistances[2*j+0] = distance1/1000.0;
			pDistances[2*j+1] = distance2/1000.0;
		}
		memcpy(pRPLIDAR->esdata_prev, databuf, NB_BYTES_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR);
		break;
	case MEASUREMENT_CAPSULED_ULTRA_RESPONSE_RPLIDAR:
		printf("A RPLIDAR is not responding correctly : Unhandled response descriptor, please try another scan mode or rebuild using RPLIDAR SDK. \n");
		return EXIT_NOT_IMPLEMENTED;

		// Need to check SDK code...  		 

		//// Analyze the previous data response.
		//start_angle_q6_prev = ((pRPLIDAR->eesdata_prev[3] & 0x7F)<<8) | pRPLIDAR->eesdata_prev[2];
		//*pbNewScan = pRPLIDAR->eesdata_prev[3]>>7;

		//*pNbMeasurements = NB_MEASUREMENTS_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR;

		////memset(pAngles, 0, NB_MEASUREMENTS_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR);
		////memset(pDistances, 0, NB_MEASUREMENTS_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR);
		//for (j = 0; j < NB_CABINS_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR; j++)
		//{
		//	major = ((pRPLIDAR->eesdata_prev[4+4*j+1] & 0x0F)<<8)|(pRPLIDAR->eesdata_prev[4+4*j+0]);
		//	predict1 = ((pRPLIDAR->eesdata_prev[4+4*j+2] & 0x03)<<6)|((pRPLIDAR->eesdata_prev[4+4*j+1] & 0xF0)>>4);
		//	predict2 = ((pRPLIDAR->eesdata_prev[4+4*j+3] & 0xFF)<<2)|((pRPLIDAR->eesdata_prev[4+4*j+2] & 0xC0)>>6);

		//	// k indexes in the formula of the documentation start at 1...
		//	theta = start_angle_q6_prev/64.0+AngleDiffRPLIDAR(start_angle_q6_prev/64.0, start_angle_q6/64.0)*j/NB_MEASUREMENTS_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR;

		//	// Convert in rad.
		//	pAngles[j] = fmod_2PI_deg2rad(-theta);

		//	// Convert in m.
		//	pDistances[j] = distance/1000.0;
		//}
		//memcpy(pRPLIDAR->eesdata_prev, databuf, NB_BYTES_EXTENDED_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR);
		//break;
	case MEASUREMENT_DENSE_CAPSULED_RESPONSE_RPLIDAR:
		// Analyze the previous data response.
		start_angle_q6_prev = ((pRPLIDAR->desdata_prev[3] & 0x7F)<<8) | pRPLIDAR->desdata_prev[2];
		*pbNewScan = pRPLIDAR->desdata_prev[3]>>7;

		*pNbMeasurements = NB_MEASUREMENTS_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR;

		//memset(pAngles, 0, NB_MEASUREMENTS_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR);
		//memset(pDistances, 0, NB_MEASUREMENTS_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR);
		for (j = 0; j < NB_CABINS_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR; j++)
		{
			distance = ((pRPLIDAR->desdata_prev[4+2*j+1]<<8)|pRPLIDAR->desdata_prev[4+2*j+0]);

			// k indexes in the formula of the documentation start at 1...
			theta = start_angle_q6_prev/64.0+AngleDiffRPLIDAR(start_angle_q6_prev/64.0, start_angle_q6/64.0)*j/NB_MEASUREMENTS_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR;

			// Convert in rad.
			pAngles[j] = fmod_2PI_deg2rad(-theta);

			// Convert in m.
			pDistances[j] = distance/1000.0;
		}
		memcpy(pRPLIDAR->desdata_prev, databuf, NB_BYTES_DENSE_EXPRESS_SCAN_DATA_RESPONSE_RPLIDAR);
		break;
	default:
		printf("A RPLIDAR is not responding correctly : Unhandled response descriptor. \n");
		return EXIT_FAILURE;
		//break;
	}
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	return EXIT_SUCCESS;
}

// RPLIDAR must be initialized to 0 before (e.g. RPLIDAR rplidar; memset(&rplidar, 0, sizeof(RPLIDAR));)!
inline int ConnectRPLIDAR(RPLIDAR* pRPLIDAR, char* szCfgFilePath)
{
	FILE* file = NULL;
	char line[1024];
	BOOL bProtectionStop = FALSE;

	memset(pRPLIDAR->szCfgFilePath, 0, sizeof(pRPLIDAR->szCfgFilePath));
	sprintf(pRPLIDAR->szCfgFilePath, "%.255s", szCfgFilePath);

	// If szCfgFilePath starts with "hardcoded://", parameters are assumed to be already set in the structure, 
	// otherwise it should be loaded from a configuration file.
	if (strncmp(szCfgFilePath, "hardcoded://", strlen("hardcoded://")) != 0)
	{
		memset(line, 0, sizeof(line));

		// Default values.
		memset(pRPLIDAR->szDevPath, 0, sizeof(pRPLIDAR->szDevPath));
		sprintf(pRPLIDAR->szDevPath, "COM1");
		pRPLIDAR->BaudRate = 115200;
		pRPLIDAR->timeout = 1000;
		pRPLIDAR->threadperiod = 50;
		pRPLIDAR->bSaveRawData = 1;
		pRPLIDAR->bStartScanModeAtStartup = 1;
		pRPLIDAR->ScanMode = SCAN_MODE_RPLIDAR;
		pRPLIDAR->motordelay = 500;
		pRPLIDAR->motorPWM = DEFAULT_MOTOR_PWM_RPLIDAR;
		pRPLIDAR->maxhist = 1024;
		pRPLIDAR->alpha_max_err = 0.01;
		pRPLIDAR->d_max_err = 0.1;

		// Load data from a file.
		file = fopen(szCfgFilePath, "r");
		if (file != NULL)
		{
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%255s", pRPLIDAR->szDevPath) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%d", &pRPLIDAR->BaudRate) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%d", &pRPLIDAR->timeout) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%d", &pRPLIDAR->threadperiod) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%d", &pRPLIDAR->bSaveRawData) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%d", &pRPLIDAR->bStartScanModeAtStartup) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%d", &pRPLIDAR->ScanMode) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%d", &pRPLIDAR->motordelay) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%d", &pRPLIDAR->motorPWM) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%d", &pRPLIDAR->maxhist) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%lf", &pRPLIDAR->alpha_max_err) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%lf", &pRPLIDAR->d_max_err) != 1) printf("Invalid configuration file.\n");
			if (fclose(file) != EXIT_SUCCESS) printf("fclose() failed.\n");
		}
		else
		{
			printf("Configuration file not found.\n");
		}
	}

	if (pRPLIDAR->threadperiod < 0)
	{
		printf("Invalid parameter : threadperiod.\n");
		pRPLIDAR->threadperiod = 50;
	}
	if (pRPLIDAR->ScanMode < 0)
	{
		printf("Invalid parameter : ScanMode.\n");
		pRPLIDAR->ScanMode = SCAN_MODE_RPLIDAR;
	}
	if (pRPLIDAR->motordelay < 0)
	{
		printf("Invalid parameter : motordelay.\n");
		pRPLIDAR->motordelay = 500;
	}
	if ((pRPLIDAR->maxhist < 0)||(pRPLIDAR->maxhist > MAX_NB_MEASUREMENTS_PER_SCAN_RPLIDAR))
	{
		printf("Invalid parameter : maxhist.\n");
		pRPLIDAR->maxhist = 1024;
	}

	// Used to save raw data, should be handled specifically...
	//pRPLIDAR->pfSaveFile = NULL;

#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
#ifdef FORCE_RPLIDAR_SDK_V1
	_u32 drvtype = CHANNEL_TYPE_SERIALPORT;
#else
	int drvtype = CHANNEL_TYPE_SERIALPORT;
#endif // FORCE_RPLIDAR_SDK_V1
	char address[256];
	char port[256];
	int iport = 0, ilport = 0;
	char* ptr = NULL;
	char* ptr2 = NULL;

	memset(address, 0, sizeof(address));
	memset(port, 0, sizeof(port));

	// Try to determine whether it is a server TCP port (e.g. :4001), client IP address and TCP port (e.g. 127.0.0.1:4001), 
	// IP address and UDP ports (e.g. udp://127.0.0.1:4001:4002) or local RS232 port.
	ptr = strchr(pRPLIDAR->szDevPath, ':');
	if ((ptr != NULL)&&(strlen(ptr) >= 6)) ptr2 = strchr(ptr+1, ':');
	if ((strlen(pRPLIDAR->szDevPath) >= 12)&&(strncmp(pRPLIDAR->szDevPath, "tcpsrv://", strlen("tcpsrv://")) == 0)&&(ptr2 != NULL)&&(ptr2[1] != 0))
	{
		memcpy(address, pRPLIDAR->szDevPath+9, ptr2-(pRPLIDAR->szDevPath+9));
		strcpy(port, ptr2+1);
		drvtype = CHANNEL_TYPE_TCP;
	}
	else if ((strlen(pRPLIDAR->szDevPath) >= 9)&&(strncmp(pRPLIDAR->szDevPath, "tcp://", strlen("tcp://")) == 0)&&(ptr2 != NULL)&&(ptr2[1] != 0))
	{
		memcpy(address, pRPLIDAR->szDevPath+6, ptr2-(pRPLIDAR->szDevPath+6));
		strcpy(port, ptr2+1);
		drvtype = CHANNEL_TYPE_TCP;
	}
	else if ((strlen(pRPLIDAR->szDevPath) >= 9)&&(strncmp(pRPLIDAR->szDevPath, "udp://", strlen("udp://")) == 0)&&(ptr2 != NULL)&&(ptr2[1] != 0))
	{
		memcpy(address, pRPLIDAR->szDevPath+6, ptr2-(pRPLIDAR->szDevPath+6));
		sscanf(ptr2, ":%d:%d", &iport, &ilport);
#ifdef FORCE_RPLIDAR_SDK_V1
		printf("Unable to connect to a RPLIDAR : Not implemented.\n");
		return EXIT_NOT_IMPLEMENTED;
#else
		drvtype = CHANNEL_TYPE_UDP;
#endif // FORCE_RPLIDAR_SDK_V1
	}
	else if ((strlen(pRPLIDAR->szDevPath) >= 5)&&(strncmp(pRPLIDAR->szDevPath, "tcp:", strlen("tcp:")) == 0)&&(atoi(pRPLIDAR->szDevPath+4) > 0))
	{
		strcpy(address, "0.0.0.0");
		strcpy(port, pRPLIDAR->szDevPath+4);
		drvtype = CHANNEL_TYPE_TCP;
	}
	else if ((pRPLIDAR->szDevPath[0] == ':')&&(atoi(pRPLIDAR->szDevPath+1) > 0))
	{
		strcpy(address, "0.0.0.0");
		strcpy(port, pRPLIDAR->szDevPath+1);
		drvtype = CHANNEL_TYPE_TCP;
	}
	else if ((ptr != NULL)&&(ptr[1] != 0))
	{
		memcpy(address, pRPLIDAR->szDevPath, ptr-pRPLIDAR->szDevPath);
		strcpy(port, ptr+1);
		drvtype = CHANNEL_TYPE_TCP;
	}
	else
	{
		strcpy(address, pRPLIDAR->szDevPath);
		sprintf(port, "%d", pRPLIDAR->BaudRate);
		drvtype = CHANNEL_TYPE_SERIALPORT;
	}

#ifdef FORCE_RPLIDAR_SDK_V1
	pRPLIDAR->drv = RPlidarDriver::CreateDriver(drvtype);
#else
	pRPLIDAR->drv = *createLidarDriver();
#endif // FORCE_RPLIDAR_SDK_V1
	if (!pRPLIDAR->drv)
	{
		printf("Unable to connect to a RPLIDAR.\n");
		return EXIT_FAILURE;
	}
	
#ifdef FORCE_RPLIDAR_SDK_V1
	if (IS_FAIL(pRPLIDAR->drv->connect(address, atoi(port))))
	{
		printf("Unable to connect to a RPLIDAR.\n");
		RPlidarDriver::DisposeDriver(pRPLIDAR->drv); pRPLIDAR->drv = NULL;
		return EXIT_FAILURE;
	}

	if (IS_FAIL(pRPLIDAR->drv->startMotor()))
	{
		printf("Unable to connect to a RPLIDAR.\n");
		pRPLIDAR->drv->disconnect();
		RPlidarDriver::DisposeDriver(pRPLIDAR->drv); pRPLIDAR->drv = NULL;
		return EXIT_FAILURE;
	}
#else
	if (drvtype == CHANNEL_TYPE_SERIALPORT)
	{
		pRPLIDAR->channel = *createSerialPortChannel(address, atoi(port));
	}
	else if (drvtype == CHANNEL_TYPE_TCP)
	{
		pRPLIDAR->channel = *createTcpChannel(address, atoi(port));
	}
	else if (drvtype == CHANNEL_TYPE_UDP)
	{
		pRPLIDAR->channel = *createUdpChannel(address, atoi(port));
	}
	else
	{
		printf("Unable to connect to a RPLIDAR.\n");
		delete pRPLIDAR->drv; pRPLIDAR->drv = NULL;
		return EXIT_FAILURE;
	}

	if (!pRPLIDAR->channel)
	{
		printf("Unable to connect to a RPLIDAR.\n");
		delete pRPLIDAR->drv; pRPLIDAR->drv = NULL;
		return EXIT_FAILURE;
	}

	if (SL_IS_FAIL(pRPLIDAR->drv->connect(pRPLIDAR->channel)))
	{
		printf("Unable to connect to a RPLIDAR.\n");
		delete pRPLIDAR->channel; pRPLIDAR->channel = NULL;
		delete pRPLIDAR->drv; pRPLIDAR->drv = NULL;
		return EXIT_FAILURE;
	}

	// startMotor() probably only necessary for old versions of the SDK...
	// startMotor() equivalent from https://github.com/Slamtec/sllidar_ros2/blob/main/src/sllidar_node.cpp...
	//if (SL_IS_FAIL(pRPLIDAR->drv->setMotorSpeed()))
	//{
	//	printf("Unable to connect to a RPLIDAR : setMotorSpeed() failed. \n");
	//	return EXIT_FAILURE;
	//}
	//if (SL_IS_FAIL(pRPLIDAR->drv->startScan(0,1)))
	//{
	//	printf("Unable to connect to a RPLIDAR : startScan() failed. \n");
	//	return EXIT_FAILURE;
	//}
#endif // FORCE_RPLIDAR_SDK_V1
#else
	if (OpenRS232Port(&pRPLIDAR->RS232Port, pRPLIDAR->szDevPath) != EXIT_SUCCESS)
	{
		printf("Unable to connect to a RPLIDAR.\n");
		return EXIT_FAILURE;
	}

	if (SetOptionsRS232Port(&pRPLIDAR->RS232Port, pRPLIDAR->BaudRate, NOPARITY, FALSE, 8, 
		ONESTOPBIT, (UINT)pRPLIDAR->timeout) != EXIT_SUCCESS)
	{
		printf("Unable to connect to a RPLIDAR.\n");
		CloseRS232Port(&pRPLIDAR->RS232Port);
		return EXIT_FAILURE;
	}
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
	pRPLIDAR->nodes_cache = new std::deque<sl_lidar_response_measurement_node_hq_t>();
	if (!pRPLIDAR->nodes_cache)
	{
		printf("Unable to connect to a RPLIDAR : Out of memory. .\n");
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
#ifdef FORCE_RPLIDAR_SDK_V1
		pRPLIDAR->drv->stopMotor();
		pRPLIDAR->drv->disconnect();
		RPlidarDriver::DisposeDriver(pRPLIDAR->drv); pRPLIDAR->drv = NULL;
#else
		//pRPLIDAR->drv->setMotorSpeed(0); // Not sure about what to do...
		pRPLIDAR->drv->disconnect();
		delete pRPLIDAR->channel; pRPLIDAR->channel = NULL;
		delete pRPLIDAR->drv; pRPLIDAR->drv = NULL;
#endif // FORCE_RPLIDAR_SDK_V1
#else
		CloseRS232Port(&pRPLIDAR->RS232Port);
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
		return EXIT_OUT_OF_MEMORY;
	}
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	memset(pRPLIDAR->SerialNumber, 0, sizeof(pRPLIDAR->SerialNumber));

	if (pRPLIDAR->bStartScanModeAtStartup)
	{
		GetStartupMessageRPLIDAR(pRPLIDAR);

		// Stop any currently running scan.
		if (StopRequestRPLIDAR(pRPLIDAR) != EXIT_SUCCESS)
		{
			printf("Warning : RPLIDAR STOP failure.\n");
		}

		if (GetInfoRequestRPLIDAR(pRPLIDAR, &pRPLIDAR->model, &pRPLIDAR->hardware, &pRPLIDAR->firmware_major, &pRPLIDAR->firmware_minor, pRPLIDAR->SerialNumber) != EXIT_SUCCESS)
		{
			printf("Warning : RPLIDAR GET_INFO failure.\n");
		}

		if (GetHealthRequestRPLIDAR(pRPLIDAR, &bProtectionStop) != EXIT_SUCCESS)
		{
			printf("Warning : RPLIDAR GET_HEALTH failure.\n");
		}

		if (bProtectionStop)
		{
			if (ResetRequestRPLIDAR(pRPLIDAR) != EXIT_SUCCESS)
			{
				printf("Unable to connect to a RPLIDAR : RESET failure.\n");
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
				delete pRPLIDAR->nodes_cache;
#ifdef FORCE_RPLIDAR_SDK_V1
				pRPLIDAR->drv->stopMotor();
				pRPLIDAR->drv->disconnect();
				RPlidarDriver::DisposeDriver(pRPLIDAR->drv); pRPLIDAR->drv = NULL;
#else
				//pRPLIDAR->drv->setMotorSpeed(0); // Not sure about what to do...
				pRPLIDAR->drv->disconnect();
				delete pRPLIDAR->channel; pRPLIDAR->channel = NULL;
				delete pRPLIDAR->drv; pRPLIDAR->drv = NULL;
#endif // FORCE_RPLIDAR_SDK_V1
#else
				CloseRS232Port(&pRPLIDAR->RS232Port);
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
				return EXIT_FAILURE;
			}
			GetStartupMessageRPLIDAR(pRPLIDAR);
			StopRequestRPLIDAR(pRPLIDAR);
		}

		// Incompatible with old RPLIDAR...
		//if (GetSampleRateRequestRPLIDAR(pRPLIDAR, &pRPLIDAR->Tstandard, &pRPLIDAR->Texpress) != EXIT_SUCCESS)
		//{
		//	printf("Unable to connect to a RPLIDAR : GET_SAMPLERATE failure.\n");
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
		//	delete pRPLIDAR->nodes_cache;
#ifdef FORCE_RPLIDAR_SDK_V1
		//	pRPLIDAR->drv->stopMotor();
		//	pRPLIDAR->drv->disconnect();
		//	RPlidarDriver::DisposeDriver(pRPLIDAR->drv); pRPLIDAR->drv = NULL;
#else
		//	//pRPLIDAR->drv->setMotorSpeed(0); // Not sure about what to do...
		//	pRPLIDAR->drv->disconnect();
		//	delete pRPLIDAR->channel; pRPLIDAR->channel = NULL;
		//	delete pRPLIDAR->drv; pRPLIDAR->drv = NULL;
#endif // FORCE_RPLIDAR_SDK_V1
#else
		//	CloseRS232Port(&pRPLIDAR->RS232Port);
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
		//	return EXIT_FAILURE;
		//}

		SetMotorPWMRequestRPLIDAR(pRPLIDAR, pRPLIDAR->motorPWM);

		memset(pRPLIDAR->esdata_prev, 0, sizeof(pRPLIDAR->esdata_prev));
		memset(pRPLIDAR->eesdata_prev, 0, sizeof(pRPLIDAR->eesdata_prev));
		memset(pRPLIDAR->desdata_prev, 0, sizeof(pRPLIDAR->desdata_prev));
		switch (pRPLIDAR->ScanMode)
		{
		case SCAN_MODE_RPLIDAR:
			if (StartScanRequestRPLIDAR(pRPLIDAR) != EXIT_SUCCESS)
			{
				printf("Unable to connect to a RPLIDAR : SCAN failure.\n");
				SetMotorPWMRequestRPLIDAR(pRPLIDAR, 0);
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
				delete pRPLIDAR->nodes_cache;
#ifdef FORCE_RPLIDAR_SDK_V1
				pRPLIDAR->drv->stopMotor();
				pRPLIDAR->drv->disconnect();
				RPlidarDriver::DisposeDriver(pRPLIDAR->drv); pRPLIDAR->drv = NULL;
#else
				//pRPLIDAR->drv->setMotorSpeed(0); // Not sure about what to do...
				pRPLIDAR->drv->disconnect();
				delete pRPLIDAR->channel; pRPLIDAR->channel = NULL;
				delete pRPLIDAR->drv; pRPLIDAR->drv = NULL;
#endif // FORCE_RPLIDAR_SDK_V1
#else
				CloseRS232Port(&pRPLIDAR->RS232Port);
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
				return EXIT_FAILURE;
			}
			break;
		case LEGACY_EXPRESS_SCAN_MODE_RPLIDAR:
			if (StartExpressScanRequestRPLIDAR(pRPLIDAR) != EXIT_SUCCESS)
			{
				printf("Unable to connect to a RPLIDAR : EXPRESS_SCAN failure.\n");
				SetMotorPWMRequestRPLIDAR(pRPLIDAR, 0);
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
				delete pRPLIDAR->nodes_cache;
#ifdef FORCE_RPLIDAR_SDK_V1
				pRPLIDAR->drv->stopMotor();
				pRPLIDAR->drv->disconnect();
				RPlidarDriver::DisposeDriver(pRPLIDAR->drv); pRPLIDAR->drv = NULL;
#else
				//pRPLIDAR->drv->setMotorSpeed(0); // Not sure about what to do...
				pRPLIDAR->drv->disconnect();
				delete pRPLIDAR->channel; pRPLIDAR->channel = NULL;
				delete pRPLIDAR->drv; pRPLIDAR->drv = NULL;
#endif // FORCE_RPLIDAR_SDK_V1
#else
				CloseRS232Port(&pRPLIDAR->RS232Port);
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
				return EXIT_FAILURE;
			}
			break;
		// Force scan is a special case...
		case FORCE_SCAN_MODE_RPLIDAR:
			if (StartForceScanRequestRPLIDAR(pRPLIDAR) != EXIT_SUCCESS)
			{
				printf("Unable to connect to a RPLIDAR : FORCE_SCAN failure.\n");
				SetMotorPWMRequestRPLIDAR(pRPLIDAR, 0);
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
				delete pRPLIDAR->nodes_cache;
#ifdef FORCE_RPLIDAR_SDK_V1
				pRPLIDAR->drv->stopMotor();
				pRPLIDAR->drv->disconnect();
				RPlidarDriver::DisposeDriver(pRPLIDAR->drv); pRPLIDAR->drv = NULL;
#else
				//pRPLIDAR->drv->setMotorSpeed(0); // Not sure about what to do...
				pRPLIDAR->drv->disconnect();
				delete pRPLIDAR->channel; pRPLIDAR->channel = NULL;
				delete pRPLIDAR->drv; pRPLIDAR->drv = NULL;
#endif // FORCE_RPLIDAR_SDK_V1
#else
				CloseRS232Port(&pRPLIDAR->RS232Port);
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
				return EXIT_FAILURE;
			}
			break;
		default:
			if (StartOtherScanRequestRPLIDAR(pRPLIDAR, pRPLIDAR->ScanMode) != EXIT_SUCCESS)
			{
				printf("Unable to connect to a RPLIDAR : scan mode failure.\n");
				SetMotorPWMRequestRPLIDAR(pRPLIDAR, 0);
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
				delete pRPLIDAR->nodes_cache;
#ifdef FORCE_RPLIDAR_SDK_V1
				pRPLIDAR->drv->stopMotor();
				pRPLIDAR->drv->disconnect();
				RPlidarDriver::DisposeDriver(pRPLIDAR->drv); pRPLIDAR->drv = NULL;
#else
				//pRPLIDAR->drv->setMotorSpeed(0); // Not sure about what to do...
				pRPLIDAR->drv->disconnect();
				delete pRPLIDAR->channel; pRPLIDAR->channel = NULL;
				delete pRPLIDAR->drv; pRPLIDAR->drv = NULL;
#endif // FORCE_RPLIDAR_SDK_V1
#else
				CloseRS232Port(&pRPLIDAR->RS232Port);
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
				return EXIT_FAILURE;
			}
			break;
		}

		// Wait for the motor rotation to become stable.
		mSleep(pRPLIDAR->motordelay);
	}

	printf("RPLIDAR %.32s%.1sconnected.\n", pRPLIDAR->SerialNumber, (pRPLIDAR->SerialNumber[0])? " ": "\0");

	return EXIT_SUCCESS;
}

inline int DisconnectRPLIDAR(RPLIDAR* pRPLIDAR)
{
	if (StopRequestRPLIDAR(pRPLIDAR) != EXIT_SUCCESS)
	{
		printf("Error while disconnecting a RPLIDAR.\n");
		SetMotorPWMRequestRPLIDAR(pRPLIDAR, 0);
#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
		delete pRPLIDAR->nodes_cache;
#ifdef FORCE_RPLIDAR_SDK_V1
		pRPLIDAR->drv->stopMotor();
		pRPLIDAR->drv->disconnect();
		RPlidarDriver::DisposeDriver(pRPLIDAR->drv); pRPLIDAR->drv = NULL;
#else
		//pRPLIDAR->drv->setMotorSpeed(0); // Not sure about what to do...
		pRPLIDAR->drv->disconnect();
		delete pRPLIDAR->channel; pRPLIDAR->channel = NULL;
		delete pRPLIDAR->drv; pRPLIDAR->drv = NULL;
#endif // FORCE_RPLIDAR_SDK_V1
#else
		CloseRS232Port(&pRPLIDAR->RS232Port);
#endif // ENABLE_RPLIDAR_SDK_SUPPORT
		return EXIT_FAILURE;
	}

	SetMotorPWMRequestRPLIDAR(pRPLIDAR, 0);

#ifdef ENABLE_RPLIDAR_SDK_SUPPORT
	delete pRPLIDAR->nodes_cache;
#ifdef FORCE_RPLIDAR_SDK_V1
	pRPLIDAR->drv->stopMotor();
	pRPLIDAR->drv->disconnect();
	RPlidarDriver::DisposeDriver(pRPLIDAR->drv); pRPLIDAR->drv = NULL;
#else
	//pRPLIDAR->drv->setMotorSpeed(0); // Not sure about what to do...
	pRPLIDAR->drv->disconnect();
	delete pRPLIDAR->channel; pRPLIDAR->channel = NULL;
	delete pRPLIDAR->drv; pRPLIDAR->drv = NULL;
#endif // FORCE_RPLIDAR_SDK_V1
#else
	if (CloseRS232Port(&pRPLIDAR->RS232Port) != EXIT_SUCCESS)
	{
		printf("RPLIDAR disconnection failed.\n");
		return EXIT_FAILURE;
	}
#endif // ENABLE_RPLIDAR_SDK_SUPPORT

	printf("RPLIDAR %.32s%.1sdisconnected.\n", pRPLIDAR->SerialNumber, (pRPLIDAR->SerialNumber[0])? " ": "\0");

	return EXIT_SUCCESS;
}

#ifndef DISABLE_RPLIDARTHREAD
THREAD_PROC_RETURN_VALUE RPLIDARThread(void* pParam);
#endif // !DISABLE_RPLIDARTHREAD

// min and max might cause incompatibilities...
#ifdef max
#undef max
#endif // max
#ifdef min
#undef min
#endif // min

#endif // !RPLIDAR_H
