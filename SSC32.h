// Prevent Visual Studio Intellisense from defining _WIN32 and _MSC_VER when we use 
// Visual Studio to edit Linux or Borland C++ code.
#ifdef __linux__
#	undef _WIN32
#endif // __linux__
#if defined(__GNUC__) || defined(__BORLANDC__)
#	undef _MSC_VER
#endif // defined(__GNUC__) || defined(__BORLANDC__)

#ifndef SSC32_H
#define SSC32_H

#include "OSMisc.h"
#include "RS232Port.h"

#ifndef DISABLE_SSC32THREAD
#include "OSThread.h"
#endif // DISABLE_SSC32THREAD

//#define TIMEOUT_MESSAGE_SSC32 4.0 // In s.
// Should be at least 2 * number of bytes to be sure to contain entirely the biggest desired message (or group of messages) + 1.
#define MAX_NB_BYTES_SSC32 512

// Only the 5 first channels are used for the moment...
#define NB_CHANNELS_PWM_SSC32 5

// In us.
#define DEFAULT_ABSOLUTE_MIN_PW_SSC32 500

// In us.
#define DEFAULT_MIN_PW_SSC32 1000

// In us.
#define DEFAULT_MID_PW_SSC32 1500

// In us.
#define DEFAULT_MAX_PW_SSC32 2000

// In us.
#define DEFAULT_ABSOLUTE_MAX_PW_SSC32 2500

struct SSC32
{
	RS232PORT RS232Port;
	FILE* pfSaveFile; // Used to save raw data, should be handled specifically...
	int LastPWs[NB_CHANNELS_PWM_SSC32];
	char szCfgFilePath[256];
	char szDevPath[256];
	int BaudRate;
	int timeout;
	BOOL bSaveRawData;
	int MinPWs[NB_CHANNELS_PWM_SSC32];
	int MidPWs[NB_CHANNELS_PWM_SSC32];
	int MaxPWs[NB_CHANNELS_PWM_SSC32];
	int ThresholdPWs[NB_CHANNELS_PWM_SSC32];
	double CoefPWs[NB_CHANNELS_PWM_SSC32];
	int bProportionalPWs[NB_CHANNELS_PWM_SSC32];
	int rudderchan;
	int rightthrusterchan;
	int leftthrusterchan;
	int rightfluxchan;
	int leftfluxchan;
	double MinAngle;
	double MaxAngle;
};
typedef struct SSC32 SSC32;

// pw in us.
inline int SetPWMSSC32(SSC32* pSSC32, int channel, int pw)
{
	char sendbuf[MAX_NB_BYTES_SSC32];
	int sendbuflen = 0;

	if (pSSC32->bProportionalPWs[channel])
	{
		pw = (int)(pSSC32->CoefPWs[channel]*(pw-DEFAULT_MID_PW_SSC32));
		if (pw >= 0)
			pw = pSSC32->MidPWs[channel]+pw*(pSSC32->MaxPWs[channel]-pSSC32->MidPWs[channel])
			/(DEFAULT_MAX_PW_SSC32-DEFAULT_MID_PW_SSC32);
		else
			pw = pSSC32->MidPWs[channel]+pw*(pSSC32->MinPWs[channel]-pSSC32->MidPWs[channel])
			/(DEFAULT_MIN_PW_SSC32-DEFAULT_MID_PW_SSC32);
	}
	else
	{
		pw = DEFAULT_MID_PW_SSC32+(int)(pSSC32->CoefPWs[channel]*(pw-DEFAULT_MID_PW_SSC32));
	}

	pw = max(min(pw, pSSC32->MaxPWs[channel]), pSSC32->MinPWs[channel]);
	//pw = max(min(pw, DEFAULT_ABSOLUTE_MAX_PW_SSC32), DEFAULT_ABSOLUTE_MIN_PW_SSC32);

	// The requested PWM is only applied if it is slightly different from the current value.
	if (abs(pw-pSSC32->LastPWs[channel]) < pSSC32->ThresholdPWs[channel]) return EXIT_SUCCESS;

	// Prepare data to send to device.
	memset(sendbuf, 0, sizeof(sendbuf));
	sprintf(sendbuf, "#%dP%d\r", channel, pw);
	sendbuflen = (int)strlen(sendbuf);

	if (WriteAllRS232Port(&pSSC32->RS232Port, (unsigned char*)sendbuf, sendbuflen) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	if ((pSSC32->bSaveRawData)&&(pSSC32->pfSaveFile))
	{
		fwrite(sendbuf, sendbuflen, 1, pSSC32->pfSaveFile);
		fflush(pSSC32->pfSaveFile);
	}

	// Update last known value.
	pSSC32->LastPWs[channel] = pw;

	return EXIT_SUCCESS;
}

// pw in us.
inline int SetAllPWMsSSC32(SSC32* pSSC32, int* selectedchannels, int* pws)
{
	char szTmp[MAX_NB_BYTES_SSC32];
	char sendbuf[MAX_NB_BYTES_SSC32];
	int sendbuflen = 0;
	int channel = 0;
	int pws_tmp[NB_CHANNELS_PWM_SSC32];

	memset(szTmp, 0, sizeof(szTmp));

	// Prepare data to send to device.
	memset(sendbuf, 0, sizeof(sendbuf));

	memcpy(pws_tmp, pws, sizeof(pws_tmp));

	for (channel = 0; channel < NB_CHANNELS_PWM_SSC32; channel++)
	{
		if (!selectedchannels[channel]) continue;

		if (pSSC32->bProportionalPWs[channel])
		{
			pws_tmp[channel] = (int)(pSSC32->CoefPWs[channel]*(pws_tmp[channel]-DEFAULT_MID_PW_SSC32));
			if (pws_tmp[channel] >= 0)
				pws_tmp[channel] = pSSC32->MidPWs[channel]+pws_tmp[channel]*(pSSC32->MaxPWs[channel]-pSSC32->MidPWs[channel])
				/(DEFAULT_MAX_PW_SSC32-DEFAULT_MID_PW_SSC32);
			else
				pws_tmp[channel] = pSSC32->MidPWs[channel]+pws_tmp[channel]*(pSSC32->MinPWs[channel]-pSSC32->MidPWs[channel])
				/(DEFAULT_MIN_PW_SSC32-DEFAULT_MID_PW_SSC32);
		}
		else
		{
			pws_tmp[channel] = DEFAULT_MID_PW_SSC32+(int)(pSSC32->CoefPWs[channel]*(pws_tmp[channel]-DEFAULT_MID_PW_SSC32));
		}

		pws_tmp[channel] = max(min(pws_tmp[channel], pSSC32->MaxPWs[channel]), pSSC32->MinPWs[channel]);
		//pws_tmp[channel] = max(min(pws_tmp[channel], DEFAULT_ABSOLUTE_MAX_PW_SSC32), DEFAULT_ABSOLUTE_MIN_PW_SSC32);

		// The requested PWM is only applied if it is slightly different from the current value.
		if (abs(pws_tmp[channel]-pSSC32->LastPWs[channel]) < pSSC32->ThresholdPWs[channel]) continue;

		//printf("%d %d %d %d %d\n", channel, pws_tmp[channel], pSSC32->LastPWs[channel], abs(pws_tmp[channel]-pSSC32->LastPWs[channel]), pSSC32->ThresholdPWs[channel]);

		sprintf(szTmp, "#%dP%d", channel, pws_tmp[channel]);
		strcat(sendbuf, szTmp);
	}

	if (sendbuf[0] == 0) return EXIT_SUCCESS;

	strcat(sendbuf, "\r");
	sendbuflen = (int)strlen(sendbuf);

	//printf("%s\n", sendbuf);

	if (WriteAllRS232Port(&pSSC32->RS232Port, (unsigned char*)sendbuf, sendbuflen) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	if ((pSSC32->bSaveRawData)&&(pSSC32->pfSaveFile))
	{
		fwrite(sendbuf, sendbuflen, 1, pSSC32->pfSaveFile);
		fflush(pSSC32->pfSaveFile);
	}

	for (channel = 0; channel < NB_CHANNELS_PWM_SSC32; channel++)
	{
		if (!selectedchannels[channel]) continue;

		// The requested PWM should have been only applied if it was slightly different from the current value.
		if (abs(pws_tmp[channel]-pSSC32->LastPWs[channel]) < pSSC32->ThresholdPWs[channel]) continue;

		// Update last known value.
		pSSC32->LastPWs[channel] = pws_tmp[channel];
	}

	return EXIT_SUCCESS;
}

inline int SetRudderSSC32(SSC32* pSSC32, double angle)
{
	int pw = 0;

	// Convert angle (in rad) into SSC32 pulse width (in us).
	pw = DEFAULT_MID_PW_SSC32+(int)(angle*(DEFAULT_MAX_PW_SSC32-DEFAULT_MIN_PW_SSC32)
		/(pSSC32->MaxAngle-pSSC32->MinAngle));

	pw = max(min(pw, DEFAULT_MAX_PW_SSC32), DEFAULT_MIN_PW_SSC32);

	return SetPWMSSC32(pSSC32, pSSC32->rudderchan, pw);
}

inline int SetThrustersSSC32(SSC32* pSSC32, double urt, double ult)
{
	int selectedchannels[NB_CHANNELS_PWM_SSC32];
	int pws[NB_CHANNELS_PWM_SSC32];

	memset(selectedchannels, 0, sizeof(selectedchannels));
	memset(pws, 0, sizeof(pws));

	// Convert u (in [-1;1]) into SSC32 pulse width (in us).
	pws[pSSC32->rightthrusterchan] = DEFAULT_MID_PW_SSC32+(int)(urt*(DEFAULT_MAX_PW_SSC32-DEFAULT_MIN_PW_SSC32)/2.0);
	pws[pSSC32->leftthrusterchan] = DEFAULT_MID_PW_SSC32+(int)(ult*(DEFAULT_MAX_PW_SSC32-DEFAULT_MIN_PW_SSC32)/2.0);

	pws[pSSC32->rightthrusterchan] = max(min(pws[pSSC32->rightthrusterchan], DEFAULT_MAX_PW_SSC32), DEFAULT_MIN_PW_SSC32);
	pws[pSSC32->leftthrusterchan] = max(min(pws[pSSC32->leftthrusterchan], DEFAULT_MAX_PW_SSC32), DEFAULT_MIN_PW_SSC32);

	selectedchannels[pSSC32->rightthrusterchan] = 1;
	selectedchannels[pSSC32->leftthrusterchan] = 1;

	return SetAllPWMsSSC32(pSSC32, selectedchannels, pws);
}

inline int SetFluxSSC32(SSC32* pSSC32, double urf, double ulf)
{
	int selectedchannels[NB_CHANNELS_PWM_SSC32];
	int pws[NB_CHANNELS_PWM_SSC32];

	memset(selectedchannels, 0, sizeof(selectedchannels));
	memset(pws, 0, sizeof(pws));

	// Convert u (in [-1;1]) into SSC32 pulse width (in us).
	pws[pSSC32->rightfluxchan] = DEFAULT_MID_PW_SSC32+(int)(urf*(DEFAULT_MAX_PW_SSC32-DEFAULT_MIN_PW_SSC32)/2.0);
	pws[pSSC32->leftfluxchan] = DEFAULT_MID_PW_SSC32+(int)(ulf*(DEFAULT_MAX_PW_SSC32-DEFAULT_MIN_PW_SSC32)/2.0);

	pws[pSSC32->rightfluxchan] = max(min(pws[pSSC32->rightfluxchan], DEFAULT_MAX_PW_SSC32), DEFAULT_MIN_PW_SSC32);
	pws[pSSC32->leftfluxchan] = max(min(pws[pSSC32->leftfluxchan], DEFAULT_MAX_PW_SSC32), DEFAULT_MIN_PW_SSC32);

	selectedchannels[pSSC32->rightfluxchan] = 1;
	selectedchannels[pSSC32->leftfluxchan] = 1;

	return SetAllPWMsSSC32(pSSC32, selectedchannels, pws);
}

inline int SetRudderThrustersFluxSSC32(SSC32* pSSC32, double angle, double urt, double ult, double urf, double ulf)
{
	int selectedchannels[NB_CHANNELS_PWM_SSC32];
	int pws[NB_CHANNELS_PWM_SSC32];

	memset(selectedchannels, 0, sizeof(selectedchannels));
	memset(pws, 0, sizeof(pws));

	// Convert angle (in rad) into SSC32 pulse width (in us).
	pws[pSSC32->rudderchan] = DEFAULT_MID_PW_SSC32+(int)(angle*(DEFAULT_MAX_PW_SSC32-DEFAULT_MIN_PW_SSC32)
		/(pSSC32->MaxAngle-pSSC32->MinAngle));
	// Convert u (in [-1;1]) into SSC32 pulse width (in us).
	pws[pSSC32->rightthrusterchan] = DEFAULT_MID_PW_SSC32+(int)(urt*(DEFAULT_MAX_PW_SSC32-DEFAULT_MIN_PW_SSC32)/2.0);
	pws[pSSC32->leftthrusterchan] = DEFAULT_MID_PW_SSC32+(int)(ult*(DEFAULT_MAX_PW_SSC32-DEFAULT_MIN_PW_SSC32)/2.0);
	pws[pSSC32->rightfluxchan] = DEFAULT_MID_PW_SSC32+(int)(urf*(DEFAULT_MAX_PW_SSC32-DEFAULT_MIN_PW_SSC32)/2.0);
	pws[pSSC32->leftfluxchan] = DEFAULT_MID_PW_SSC32+(int)(ulf*(DEFAULT_MAX_PW_SSC32-DEFAULT_MIN_PW_SSC32)/2.0);

	pws[pSSC32->rudderchan] = max(min(pws[pSSC32->rudderchan], DEFAULT_MAX_PW_SSC32), DEFAULT_MIN_PW_SSC32);
	pws[pSSC32->rightthrusterchan] = max(min(pws[pSSC32->rightthrusterchan], DEFAULT_MAX_PW_SSC32), DEFAULT_MIN_PW_SSC32);
	pws[pSSC32->leftthrusterchan] = max(min(pws[pSSC32->leftthrusterchan], DEFAULT_MAX_PW_SSC32), DEFAULT_MIN_PW_SSC32);
	pws[pSSC32->rightfluxchan] = max(min(pws[pSSC32->rightfluxchan], DEFAULT_MAX_PW_SSC32), DEFAULT_MIN_PW_SSC32);
	pws[pSSC32->leftfluxchan] = max(min(pws[pSSC32->leftfluxchan], DEFAULT_MAX_PW_SSC32), DEFAULT_MIN_PW_SSC32);

	selectedchannels[pSSC32->rudderchan] = 1;
	selectedchannels[pSSC32->rightthrusterchan] = 1;
	selectedchannels[pSSC32->leftthrusterchan] = 1;
	selectedchannels[pSSC32->rightfluxchan] = 1;
	selectedchannels[pSSC32->leftfluxchan] = 1;

	return SetAllPWMsSSC32(pSSC32, selectedchannels, pws);
}

inline int CheckSSC32(SSC32* pSSC32)
{
	if (SetRudderSSC32(pSSC32, -0.25) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	mSleep(2000);
	if (SetRudderSSC32(pSSC32, 0.25) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	mSleep(2000);
	if (SetRudderSSC32(pSSC32, 0.0) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	mSleep(2000);

	if (SetThrustersSSC32(pSSC32, -0.25, -0.25) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	mSleep(2000);
	if (SetThrustersSSC32(pSSC32, 0.0, 0.0) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	mSleep(2000);
	if (SetThrustersSSC32(pSSC32, 0.25, 0.25) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	mSleep(2000);
	if (SetThrustersSSC32(pSSC32, 0.0, 0.0) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	mSleep(2000);

	if (SetFluxSSC32(pSSC32, -0.25, -0.25) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	mSleep(2000);
	if (SetFluxSSC32(pSSC32, 0.25, 0.25) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}
	mSleep(2000);

	return EXIT_SUCCESS;
}

// SSC32 must be initialized to 0 before (e.g. SSC32 ssc32; memset(&ssc32, 0, sizeof(SSC32));)!
inline int ConnectSSC32(SSC32* pSSC32, char* szCfgFilePath)
{
	FILE* file = NULL;
	char line[256];
	int channel = 0;

	memset(line, 0, sizeof(line));

	// Default values.
	memset(pSSC32->szDevPath, 0, sizeof(pSSC32->szDevPath));
	sprintf(pSSC32->szDevPath, "COM1");
	pSSC32->BaudRate = 115200;
	pSSC32->timeout = 1000;
	pSSC32->bSaveRawData = 1;
	for (channel = 0; channel < NB_CHANNELS_PWM_SSC32; channel++)
	{
		pSSC32->MinPWs[channel] = 1000;
		pSSC32->MidPWs[channel] = 1500;
		pSSC32->MaxPWs[channel] = 2000;
		pSSC32->ThresholdPWs[channel] = 0;
		pSSC32->CoefPWs[channel] = 1;
		pSSC32->bProportionalPWs[channel] = 1;
	}
	pSSC32->rudderchan = 2;
	pSSC32->rightthrusterchan = 1;
	pSSC32->leftthrusterchan = 0;
	pSSC32->rightfluxchan = 4;
	pSSC32->leftfluxchan = 3;
	pSSC32->MinAngle = -0.5;
	pSSC32->MaxAngle = 0.5;

	sprintf(pSSC32->szCfgFilePath, "%.255s", szCfgFilePath);

	// Load data from a file.
	file = fopen(szCfgFilePath, "r");
	if (file != NULL)
	{
		if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
		if (sscanf(line, "%255s", pSSC32->szDevPath) != 1) printf("Invalid configuration file.\n");
		if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
		if (sscanf(line, "%d", &pSSC32->BaudRate) != 1) printf("Invalid configuration file.\n");
		if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
		if (sscanf(line, "%d", &pSSC32->timeout) != 1) printf("Invalid configuration file.\n");
		if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
		if (sscanf(line, "%d", &pSSC32->bSaveRawData) != 1) printf("Invalid configuration file.\n");

		for (channel = 0; channel < NB_CHANNELS_PWM_SSC32; channel++)
		{
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%d", &pSSC32->MinPWs[channel]) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%d", &pSSC32->MidPWs[channel]) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%d", &pSSC32->MaxPWs[channel]) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%d", &pSSC32->ThresholdPWs[channel]) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%lf", &pSSC32->CoefPWs[channel]) != 1) printf("Invalid configuration file.\n");
			if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
			if (sscanf(line, "%d", &pSSC32->bProportionalPWs[channel]) != 1) printf("Invalid configuration file.\n");
		}

		if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
		if (sscanf(line, "%d", &pSSC32->rudderchan) != 1) printf("Invalid configuration file.\n");
		if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
		if (sscanf(line, "%d", &pSSC32->rightthrusterchan) != 1) printf("Invalid configuration file.\n");
		if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
		if (sscanf(line, "%d", &pSSC32->leftthrusterchan) != 1) printf("Invalid configuration file.\n");
		if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
		if (sscanf(line, "%d", &pSSC32->rightfluxchan) != 1) printf("Invalid configuration file.\n");
		if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
		if (sscanf(line, "%d", &pSSC32->leftfluxchan) != 1) printf("Invalid configuration file.\n");

		if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
		if (sscanf(line, "%lf", &pSSC32->MinAngle) != 1) printf("Invalid configuration file.\n");
		if (fgets3(file, line, sizeof(line)) == NULL) printf("Invalid configuration file.\n");
		if (sscanf(line, "%lf", &pSSC32->MaxAngle) != 1) printf("Invalid configuration file.\n");

		if (fclose(file) != EXIT_SUCCESS) printf("fclose() failed.\n");
	}
	else
	{
		printf("Configuration file not found.\n");
	}

	for (channel = 0; channel < NB_CHANNELS_PWM_SSC32; channel++)
	{
		if (
			(pSSC32->MinPWs[channel] < DEFAULT_ABSOLUTE_MIN_PW_SSC32)||(pSSC32->MinPWs[channel] > DEFAULT_ABSOLUTE_MAX_PW_SSC32)||
			(pSSC32->MidPWs[channel] < DEFAULT_ABSOLUTE_MIN_PW_SSC32)||(pSSC32->MidPWs[channel] > DEFAULT_ABSOLUTE_MAX_PW_SSC32)||
			(pSSC32->MaxPWs[channel] < DEFAULT_ABSOLUTE_MIN_PW_SSC32)||(pSSC32->MaxPWs[channel] > DEFAULT_ABSOLUTE_MAX_PW_SSC32)||
			(pSSC32->MinPWs[channel] > pSSC32->MidPWs[channel])||(pSSC32->MidPWs[channel] > pSSC32->MaxPWs[channel])||
			(pSSC32->ThresholdPWs[channel] < 0)
			)
		{
			printf("Invalid parameters : channel %d.\n", channel);
			pSSC32->MinPWs[channel] = 1000;
			pSSC32->MidPWs[channel] = 1500;
			pSSC32->MaxPWs[channel] = 2000;
			pSSC32->ThresholdPWs[channel] = 0;
			pSSC32->CoefPWs[channel] = 1;
			pSSC32->bProportionalPWs[channel] = 1;
		}
	}

	if ((pSSC32->rudderchan < 0)||(pSSC32->rudderchan >= NB_CHANNELS_PWM_SSC32))
	{
		printf("Invalid parameter : rudderchan.\n");
		pSSC32->rudderchan = 2;
	}
	if ((pSSC32->rightthrusterchan < 0)||(pSSC32->rightthrusterchan >= NB_CHANNELS_PWM_SSC32))
	{
		printf("Invalid parameter : rightthrusterchan.\n");
		pSSC32->rightthrusterchan = 1;
	}
	if ((pSSC32->leftthrusterchan < 0)||(pSSC32->leftthrusterchan >= NB_CHANNELS_PWM_SSC32))
	{
		printf("Invalid parameter : leftthrusterchan.\n");
		pSSC32->leftthrusterchan = 0;
	}
	if ((pSSC32->rightfluxchan < 0)||(pSSC32->rightfluxchan >= NB_CHANNELS_PWM_SSC32))
	{
		printf("Invalid parameter : rightfluxchan.\n");
		pSSC32->rightfluxchan = 4;
	}
	if ((pSSC32->leftfluxchan < 0)||(pSSC32->leftfluxchan >= NB_CHANNELS_PWM_SSC32))
	{
		printf("Invalid parameter : leftfluxchan.\n");
		pSSC32->leftfluxchan = 3;
	}

	if (pSSC32->MaxAngle-pSSC32->MinAngle <= 0.001)
	{
		printf("Invalid parameters : MaxAngle or MinAngle.\n");
		pSSC32->MinAngle = -0.5;
		pSSC32->MaxAngle = 0.5;
	}

	// Used to save raw data, should be handled specifically...
	//pSSC32->pfSaveFile = NULL;

	for (channel = 0; channel < NB_CHANNELS_PWM_SSC32; channel++)
	{
		pSSC32->LastPWs[channel] = 0;
	}

	if (OpenRS232Port(&pSSC32->RS232Port, pSSC32->szDevPath) != EXIT_SUCCESS)
	{
		printf("Unable to connect to a SSC32.\n");
		return EXIT_FAILURE;
	}

	if (SetOptionsRS232Port(&pSSC32->RS232Port, pSSC32->BaudRate, NOPARITY, FALSE, 8, 
		ONESTOPBIT, (UINT)pSSC32->timeout) != EXIT_SUCCESS)
	{
		printf("Unable to connect to a SSC32.\n");
		CloseRS232Port(&pSSC32->RS232Port);
		return EXIT_FAILURE;
	}

	printf("SSC32 connected.\n");

	return EXIT_SUCCESS;
}

inline int DisconnectSSC32(SSC32* pSSC32)
{
	if (CloseRS232Port(&pSSC32->RS232Port) != EXIT_SUCCESS)
	{
		printf("SSC32 disconnection failed.\n");
		return EXIT_FAILURE;
	}

	printf("SSC32 disconnected.\n");

	return EXIT_SUCCESS;
}

#ifndef DISABLE_SSC32THREAD
THREAD_PROC_RETURN_VALUE SSC32Thread(void* pParam);
#endif // DISABLE_SSC32THREAD

#endif // SSC32_H
