/***************************************************************************************************************:')

OSComputerRS232Port.h

Computer RS232 port handling (open, close, read, write,...).

Fabrice Le Bars

Created : 2009-03-28

***************************************************************************************************************:)*/

// Prevent Visual Studio Intellisense from defining _WIN32 and _MSC_VER when we use 
// Visual Studio to edit Linux or Borland C++ code.
#ifdef __linux__
#	undef _WIN32
#endif // __linux__
#if defined(__GNUC__) || defined(__BORLANDC__)
#	undef _MSC_VER
#endif // defined(__GNUC__) || defined(__BORLANDC__)

#ifndef OSCOMPUTERRS232PORT_H
#define OSCOMPUTERRS232PORT_H

#include "OSTime.h"

/*
Debug macros specific to OSComputerRS232Port.
*/
#ifdef _DEBUG_MESSAGES_OSUTILS
#	define _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
#endif // _DEBUG_MESSAGES_OSUTILS

#ifdef _DEBUG_WARNINGS_OSUTILS
#	define _DEBUG_WARNINGS_OSCOMPUTERRS232PORT
#endif // _DEBUG_WARNINGS_OSUTILS

#ifdef _DEBUG_ERRORS_OSUTILS
#	define _DEBUG_ERRORS_OSCOMPUTERRS232PORT
#endif // _DEBUG_ERRORS_OSUTILS

#ifdef _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
#	define PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(params) PRINT_DEBUG_MESSAGE(params)
#else
#	define PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(params)
#endif // _DEBUG_MESSAGES_OSCOMPUTERRS232PORT

#ifdef _DEBUG_WARNINGS_OSCOMPUTERRS232PORT
#	define PRINT_DEBUG_WARNING_OSCOMPUTERRS232PORT(params) PRINT_DEBUG_WARNING(params)
#else
#	define PRINT_DEBUG_WARNING_OSCOMPUTERRS232PORT(params)
#endif // _DEBUG_WARNINGS_OSCOMPUTERRS232PORT

#ifdef _DEBUG_ERRORS_OSCOMPUTERRS232PORT
#	define PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(params) PRINT_DEBUG_ERROR(params)
#else
#	define PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(params)
#endif // _DEBUG_ERRORS_OSCOMPUTERRS232PORT

#ifdef _WIN32
#else 
#ifndef DISABLE_SELECT_OSCOMPUTERRS232PORT
#include <sys/select.h>
#endif // !DISABLE_SELECT_OSCOMPUTERRS232PORT
#if !defined(DISABLE_FORCE_CLEAR_DTR) || defined(ENABLE_DTR_FUNCTIONS)
#include <sys/ioctl.h>
#endif // !defined(DISABLE_FORCE_CLEAR_DTR) || defined(ENABLE_DTR_FUNCTIONS)
#ifndef DISABLE_CUSTOM_BAUDRATE
#include <sys/ioctl.h>
#ifdef __APPLE__
#include <IOKit/serial/ioss.h>
#endif // __APPLE__
#ifdef __linux__
#include <linux/serial.h>
#pragma push_macro("termios")
#undef termios
#define termios termbits_termios
#include <asm/termbits.h> // Not compatible with termios.h, see https://stackoverflow.com/questions/37710525/including-termios-h-and-asm-termios-h-in-the-same-project...
#undef termios
#pragma pop_macro("termios")
#endif // __linux__
#endif // !DISABLE_CUSTOM_BAUDRATE
#include <termios.h>
#endif // _WIN32

#ifndef _WIN32
#define NOPARITY            0
#define ODDPARITY           1
#define EVENPARITY          2
#define MARKPARITY          3
#define SPACEPARITY         4

#define ONESTOPBIT          0
#define TWOSTOPBITS         2
#endif // !_WIN32

#define MAX_COMPUTERRS232PORT_TIMEOUT 25500
#define MAX_COMPUTERRS232PORT_NAME_LENGTH (128-8)

inline UINT _BaudRate2Constant(UINT BaudRate)
{
#ifdef _WIN32
	switch (BaudRate)
	{
	case 110:
		return CBR_110;
	case 300:
		return CBR_300;
	case 600:
		return CBR_600;
	case 1200:
		return CBR_1200;
	case 2400:
		return CBR_2400;
	case 4800:
		return CBR_4800;
	case 9600:
		return CBR_9600;
	case 14400:
		return CBR_14400;
	case 19200:
		return CBR_19200;
	case 38400:
		return CBR_38400;
	case 56000:
		return CBR_56000;
	case 57600:
		return CBR_57600;
	case 115200:
		return CBR_115200;
	case 128000:
		return CBR_128000;
	case 256000:
		return CBR_256000;
	default:
		return 0;
	}
#else 
	switch (BaudRate)
	{
	case 50:
		return B50;
	case 75:
		return B75;
	case 110:
		return B110;
	case 134:
		return B134;
	case 150:
		return B150;
	case 200:
		return B200;
	case 300:
		return B300;
	case 600:
		return B600;
	case 1200:
		return B1200;
	case 1800:
		return B1800;
	case 2400:
		return B2400;
	case 4800:
		return B4800;
	case 9600:
		return B9600;
	case 19200:
		return B19200;
	case 38400:
		return B38400;
	case 57600:
		return B57600;
	case 115200:
		return B115200;
	case 230400:
		return B230400;
#ifndef __APPLE__
	case 460800:
		return B460800;
	case 500000:
		return B500000;
	case 576000:
		return B576000;
	case 921600:
		return B921600;
	case 1000000:
		return B1000000;
	case 1152000:
		return B1152000;
	case 1500000:
		return B1500000;
	case 2000000:
		return B2000000;
	case 2500000:
		return B2500000;
	case 3000000:
		return B3000000;
	case 3500000:
		return B3500000;
	case 4000000:
		return B4000000;
#endif // !__APPLE__
	default:
		return 0;
	}
#endif // _WIN32
}

inline UINT _Constant2BaudRate(UINT Constant)
{
#ifdef _WIN32
	switch (Constant)
	{
	case CBR_110:
		return 110;
	case CBR_300:
		return 300;
	case CBR_600:
		return 600;
	case CBR_1200:
		return 1200;
	case CBR_2400:
		return 2400;
	case CBR_4800:
		return 4800;
	case CBR_9600:
		return 9600;
	case CBR_14400:
		return 14400;
	case CBR_19200:
		return 19200;
	case CBR_38400:
		return 38400;
	case CBR_56000:
		return 56000;
	case CBR_57600:
		return 57600;
	case CBR_115200:
		return 115200;
	case CBR_128000:
		return 128000;
	case CBR_256000:
		return 256000;
	default:
		return 0;
	}
#else 
	switch (Constant)
	{
	case B50:
		return 50;
	case B75:
		return 75;
	case B110:
		return 110;
	case B134:
		return 134;
	case B150:
		return 150;
	case B200:
		return 200;
	case B300:
		return 300;
	case B600:
		return 600;
	case B1200:
		return 1200;
	case B1800:
		return 1800;
	case B2400:
		return 2400;
	case B4800:
		return 4800;
	case B9600:
		return 9600;
	case B19200:
		return 19200;
	case B38400:
		return 38400;
	case B57600:
		return 57600;
	case B115200:
		return 115200;
	case B230400:
		return 230400;
#ifndef __APPLE__
	case B460800:
		return 460800;
	case B500000:
		return 500000;
	case B576000:
		return 576000;
	case B921600:
		return 921600;
	case B1000000:
		return 1000000;
	case B1152000:
		return 1152000;
	case B1500000:
		return 1500000;
	case B2000000:
		return 2000000;
	case B2500000:
		return 2500000;
	case B3000000:
		return 3000000;
	case B3500000:
		return 3500000;
	case B4000000:
		return 4000000;
#endif // !__APPLE__
	default:
		return 0;
	}
#endif // _WIN32
}

/*
Open a computer RS232 port. Use CloseComputerRS232Port() to close it at the end.

HANDLE* phDev : (INOUT) Valid pointer that will receive an identifier of the
computer RS232 port opened.
char* szDevice : (IN) Computer RS232 port to open.

Return : EXIT_SUCCESS, EXIT_NAME_TOO_LONG or EXIT_FAILURE.
*/
inline int OpenComputerRS232Port(HANDLE* phDev, char* szDevice)
{
#ifdef _WIN32
	HANDLE hDev = INVALID_HANDLE_VALUE;
	char szDeviceTemp[2*(MAX_COMPUTERRS232PORT_NAME_LENGTH+8)];
	TCHAR tstr[2*(MAX_COMPUTERRS232PORT_NAME_LENGTH+8)];

	if (strlen(szDevice) > MAX_COMPUTERRS232PORT_NAME_LENGTH)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("OpenComputerRS232Port error (%s) : %s"
			"(szDevice=%s)\n", 
			strtime_m(), 
			szOSUtilsErrMsgs[EXIT_NAME_TOO_LONG], 
			szDevice));
		return EXIT_NAME_TOO_LONG;
	}

	// To be able to use COM10 and greater we need to add "\\.\" (that becomes "\\\\.\\" 
	// in C because the '\' is a special character).
	memset(szDeviceTemp, 0, sizeof(szDeviceTemp));
#ifdef WINCE
	strcpy(szDeviceTemp, szDevice);
#else
	sprintf(szDeviceTemp, "\\\\.\\%s", szDevice);
#endif // WINCE

#ifdef UNICODE
	mbstowcs(tstr, szDeviceTemp, sizeof(szDeviceTemp)/2);
#else
	memcpy(tstr, szDeviceTemp, sizeof(szDeviceTemp)/2);
#endif // UNICODE
	tstr[sizeof(tstr)/sizeof(TCHAR)-1] = 0;

	hDev = CreateFile( 
		tstr,
		GENERIC_READ|GENERIC_WRITE,
		0, // Must be opened with exclusive-access.
		NULL, // No security attributes.
		OPEN_EXISTING, // Must use OPEN_EXISTING.
		0, // Not overlapped I/O. Should use FILE_FLAG_WRITE_THROUGH and maybe also FILE_FLAG_NO_BUFFERING?
		NULL // hTemplate must be NULL for comm devices.
		);

	if (hDev == INVALID_HANDLE_VALUE)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("OpenComputerRS232Port error (%s) : %s"
			"(szDevice=%s)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			szDevice));
		return EXIT_FAILURE;
	}

#ifndef DISABLE_FORCE_CLEAR_DTR
	if (!EscapeCommFunction(hDev, CLRDTR))
	{
		PRINT_DEBUG_WARNING_OSCOMPUTERRS232PORT(("OpenComputerRS232Port warning (%s) : %s"
			"(szDevice=%s)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			szDevice));
	}
#endif // !DISABLE_FORCE_CLEAR_DTR

	*phDev = hDev;
#else 
	// The O_NOCTTY flag tells UNIX that this program does not want to be the
	// "controlling terminal" for that port. If you don't specify this then any input (such
	// as keyboard abort signals and so forth) will affect your process. Programs like
	// getty(1M/8) use this feature when starting the login process, but normally a
	// user program does not want this behavior.
	// The O_NDELAY flag tells UNIX that this program does not care what state the
	// DCD signal line is in - whether the other end of the port is up and running. If
	// you do not specify this flag, your process will be put to sleep until the DCD
	// signal line is the space voltage.
	// Should use O_SYNC and maybe also O_DIRECT?
	int fd = open(szDevice, O_RDWR|O_NOCTTY|O_NDELAY);
#ifndef DISABLE_FORCE_CLEAR_DTR
	int dtr_bit = TIOCM_DTR;
#endif // !DISABLE_FORCE_CLEAR_DTR

	if (fd == -1)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("OpenComputerRS232Port error (%s) : %s"
			"(szDevice=%s)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			szDevice));
		return EXIT_FAILURE;
	}

	// The read function can be made to return immediately by
	// doing the following :
	// fcntl(fd, F_SETFL, FNDELAY);
	// The FNDELAY option causes the read function to return 0 if no characters are
	// available on the port. To restore normal (blocking) behavior, call fcntl() without
	// the FNDELAY option:
	if (fcntl(fd, F_SETFL, 0) == (-1))
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("OpenComputerRS232Port error (%s) : (F_SETFL) %s"
			"(szDevice=%s)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			szDevice));
		close(fd);
		return EXIT_FAILURE;
	}

#ifndef DISABLE_FORCE_CLEAR_DTR
	if (ioctl(fd, TIOCMBIC, &dtr_bit) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_WARNING_OSCOMPUTERRS232PORT(("OpenComputerRS232Port warning (%s) : (TIOCMBIC) %s"
			"(szDevice=%s)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			szDevice));
	}
#endif // !DISABLE_FORCE_CLEAR_DTR

#ifndef DISABLE_IGNORE_SIGPIPE
	// See https://stackoverflow.com/questions/17332646/server-dies-on-send-if-client-was-closed-with-ctrlc...
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
	{
		PRINT_DEBUG_WARNING_OSCOMPUTERRS232PORT(("OpenComputerRS232Port warning (%s) : (SIGPIPE, SIG_IGN) %s"
			"(szDevice=%s)\n",
			strtime_m(),
			"signal failed ",
			szDevice));
	}
#endif // DISABLE_IGNORE_SIGPIPE

	*phDev = (HANDLE)(intptr_t)fd;
#endif // _WIN32

	return EXIT_SUCCESS;
}

/*
Close a computer RS232 port opened by OpenComputerRS232Port().

HANDLE hDev : (IN) Identifier of the computer RS232 port.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int CloseComputerRS232Port(HANDLE hDev)
{
#ifdef _WIN32
	if (!CloseHandle(hDev))
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("CloseComputerRS232Port error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}
#else
	if (close((intptr_t)hDev) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("CloseComputerRS232Port error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}
#endif // _WIN32

	return EXIT_SUCCESS;
}

/*
Set the options of a computer RS232 port.

HANDLE hDev : (IN) Identifier of the computer RS232 port.
UINT BaudRate : (IN) Baud rate at which the device connected to the computer RS232 port operates.
BYTE ParityMode : (IN) Parity mode. Should be either NOPARITY, ODDPARITY, EVENPARITY, MARKPARITY or SPACEPARITY.
BOOL bCheckParity : (IN) If TRUE, enable input parity checking.
BYTE nbDataBits : (IN) Number of bits of the data bytes.
BYTE StopBitsMode : (IN) Stop bits mode. Should be either ONESTOPBIT or TWOSTOPBITS.
UINT timeout : (IN) Time to wait to get at least 1 byte in ms (near 1000 ms for example, max is 
MAX_COMPUTERRS232PORT_TIMEOUT).

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int SetOptionsComputerRS232Port(HANDLE hDev, UINT BaudRate, BYTE ParityMode, BOOL bCheckParity, BYTE nbDataBits, 
									   BYTE StopBitsMode, UINT timeout)
{

	// Should we do something like PurgeComm(g_hCom,PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR) / tcflush
	// in the beginning of this function?

#ifdef _WIN32
	DCB dcb;
	COMMTIMEOUTS timeouts;

	memset(&dcb, 0, sizeof(DCB));

	if (!GetCommState(hDev, &dcb))
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : %s"
			"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
			"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
		return EXIT_FAILURE;
	}

	memset(&timeouts, 0, sizeof(COMMTIMEOUTS));

	if (!GetCommTimeouts(hDev, &timeouts))
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : %s"
			"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
			"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
		return EXIT_FAILURE;
	}

	// Binary mode.
	dcb.fBinary = TRUE;
	// No flow control.
	dcb.fOutxCtsFlow = FALSE;			
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fDsrSensitivity = FALSE;		 
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	dcb.fAbortOnError = FALSE;

	dcb.BaudRate = _BaudRate2Constant(BaudRate);
	if (dcb.BaudRate == 0)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : %s"
			"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
			"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n", 
			strtime_m(), 
			"Invalid BaudRate. ", 
			hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
		return EXIT_FAILURE;
	}

	// An even parity bit will be set to "1" if the number of 1's + 1 is even, and an odd 
	// parity bit will be set to "1" if the number of 1's +1 is odd.
	// If the parity bit is present but not used, it may be referred to as mark parity 
	// (when the parity bit is always 1) or space parity (the bit is always 0).
	// None parity means that no parity bit is sent at all. 
	dcb.Parity = ParityMode;
	dcb.fParity = bCheckParity;
	dcb.fErrorChar = FALSE; // Indicates whether bytes received with parity errors are 
	// replaced with the character specified by the ErrorChar member. 
	dcb.ByteSize = nbDataBits;
	dcb.StopBits = StopBitsMode;

	// The SetCommState() function reconfigures the communications resource, but it does not affect
	// the internal output and input buffers of the specified driver. The buffers are not flushed, 
	// and pending read and write operations are not terminated prematurely.
	if (!SetCommState(hDev, &dcb))
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : %s"
			"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
			"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
		return EXIT_FAILURE;
	}

	// Special mode for read timeouts.
	timeouts.ReadIntervalTimeout = MAXDWORD;
	timeouts.ReadTotalTimeoutConstant = timeout;
	timeouts.ReadTotalTimeoutMultiplier = MAXDWORD;
	//timeouts.WriteTotalTimeoutConstant = 0; // Linux does not seem to have options for write timeouts, so disable for Windows...?
	timeouts.WriteTotalTimeoutConstant = timeout;
	timeouts.WriteTotalTimeoutMultiplier = 0;

	if (!SetCommTimeouts(hDev, &timeouts))
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : %s"
			"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
			"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
		return EXIT_FAILURE;
	}
#else 
	struct termios options;
	speed_t speed = 0;
	BOOL bCustomBaudrate = FALSE;

	memset(&options, 0, sizeof(options));

	if (tcgetattr((intptr_t)hDev, &options) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : %s"
			"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
			"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
		return EXIT_FAILURE;
	}

	// Basic raw/non-canonical setup.
	// The terminal attributes are set as follows : 
	// termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	// termios_p->c_oflag &= ~OPOST;
	// termios_p->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	// termios_p->c_cflag &= ~(CSIZE | PARENB);
	// termios_p->c_cflag |= CS8;
	cfmakeraw(&options);

	// The c_cflag member contains two options that should always be enabled,
	// CLOCAL and CREAD. These will ensure that your program does not become
	// the 'owner' of the port subject to sporatic job control and hangup signals, and
	// also that the serial interface driver will read incoming data bytes.
	options.c_cflag |= (CLOCAL | CREAD);

	// Raw input, no echo, no signals.
	options.c_lflag &= ~(ICANON | IEXTEN | ECHO | ECHOE | ECHOK | ECHONL | ISIG);

	// Raw input.
	options.c_iflag &= ~(IGNBRK | BRKINT | INLCR | IGNCR | ICRNL);

	// Raw output.
	options.c_oflag &= ~(OPOST | ONLCR | ONOCR | ONLRET | OCRNL);

	// Disable hardware flow control.
#ifdef CRTSCTS
	options.c_cflag &= ~CRTSCTS;
#endif // CRTSCTS
#ifdef CNEW_RTSCTS
	options.c_cflag &= ~CNEW_RTSCTS;
#endif // CNEW_RTSCTS

	// Disable software flow control.
	options.c_iflag &= ~(IXON | IXOFF | IXANY);

	speed = _BaudRate2Constant(BaudRate);
	if (speed == 0)
	{
		// Baud rate is probably non-standard...
		bCustomBaudrate = TRUE;

		// See https://stackoverflow.com/questions/19440268/how-to-set-a-non-standard-baudrate-on-a-serial-port-device-on-linux.

		speed = _BaudRate2Constant(38400);

		// Linux-only, not compatible with all devices...?
		//options.c_cflag &= ~(CBAUD | CBAUDEX);
		//options.c_cflag |= speed;
		//tty.alt_speed = BaudRate; // ???
	}

	if (cfsetospeed(&options, speed) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : %s"
			"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
			"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n",
			strtime_m(),
			GetLastErrorMsg(),
			hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
		return EXIT_FAILURE;
	}

	if (cfsetispeed(&options, speed) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : %s"
			"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
			"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n",
			strtime_m(),
			GetLastErrorMsg(),
			hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
		return EXIT_FAILURE;
	}

	// An even parity bit will be set to "1" if the number of 1's + 1 is even, and an odd 
	// parity bit will be set to "1" if the number of 1's +1 is odd.
	// If the parity bit is present but not used, it may be referred to as mark parity 
	// (when the parity bit is always 1) or space parity (the bit is always 0).
	// None parity means that no parity bit is sent at all. 
	switch (ParityMode)
	{
	case NOPARITY:
#ifndef __APPLE__
		options.c_cflag &= ~CMSPAR;
#endif // !__APPLE__
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~PARODD;
		break;
	case MARKPARITY:
#ifndef __APPLE__
		options.c_cflag |= CMSPAR;
#endif // !__APPLE__
		options.c_cflag &= ~PARENB;
		options.c_cflag |= PARODD;
		break;
	case SPACEPARITY:
#ifndef __APPLE__
		options.c_cflag |= CMSPAR;
#endif // !__APPLE__
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~PARODD;
		break;
	case ODDPARITY:
#ifndef __APPLE__
		options.c_cflag &= ~CMSPAR;
#endif // !__APPLE__
		options.c_cflag |= PARENB;
		options.c_cflag |= PARODD;
		break;
	case EVENPARITY:
#ifndef __APPLE__
		options.c_cflag &= ~CMSPAR;
#endif // !__APPLE__
		options.c_cflag |= PARENB;
		options.c_cflag &= ~PARODD;
		break;
	default:
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : %s"
			"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
			"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n",
			strtime_m(),
			"Invalid parity mode. ",
			hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
		return EXIT_FAILURE;
	}

	// The most likely scenario where this flag is useful is if the communication channel is 
	// configured for parity and seven bits per character. In this case, the eigth bit on every 
	// received character is a parity bit, not part of the data payload. The user program does 
	// not need to know the value of the parity bit.
	options.c_iflag &= ~ISTRIP;

	options.c_iflag &= ~PARMRK; // Never mark a framing or parity error with prefix bytes.
	options.c_iflag |= IGNPAR; // A character with a framing or parity error will be discarded.
	// This is only valid (at least for parity errors) if parity checking is enabled.

	if (bCheckParity)
	{
		options.c_iflag |= INPCK;
	}
	else
	{
		options.c_iflag &= ~INPCK;
	}

	options.c_cflag &= ~CSIZE; // Erase the previous flag for the number of data bits.

	switch (nbDataBits)
	{
	case 8:
		options.c_cflag |= CS8;
		break;
	case 7:
		options.c_cflag |= CS7;
		break;
	case 6:
		options.c_cflag |= CS6;
		break;
	case 5:
		options.c_cflag |= CS5;
		break;
	default :
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : %s"
			"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
			"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n", 
			strtime_m(), 
			"Invalid number of data bits. ", 
			hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
		return EXIT_FAILURE;
	}

	switch (StopBitsMode)
	{
	case ONESTOPBIT:
		options.c_cflag &= ~CSTOPB;
		break;
	case TWOSTOPBITS:
		options.c_cflag |= CSTOPB;
		break;
	default :
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : %s"
			"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
			"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n", 
			strtime_m(), 
			"Invalid stop bits mode. ", 
			hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
		return EXIT_FAILURE;
	}

	if (timeout/100 > 255)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : %s"
			"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
			"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n", 
			strtime_m(), 
			"Too high timeout value. ", 
			hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
		return EXIT_FAILURE;
	}

	// Timeouts.
	options.c_cc[VMIN] = 0; // Minimum number of characters to read. 
	options.c_cc[VTIME] = timeout/100; // Time to wait for every character read in tenths of seconds.

	if (tcsetattr((intptr_t)hDev, TCSADRAIN, &options) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : %s"
			"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
			"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
		return EXIT_FAILURE;
	}

	if (bCustomBaudrate)
	{
#ifndef DISABLE_CUSTOM_BAUDRATE

		// See https://github.com/wjwwood/serial/blob/master/src/impl/unix.cc,
		// https://stackoverflow.com/questions/4968529/how-to-set-baud-rate-to-307200-on-linux/7152671, 
		// https://stackoverflow.com/questions/23492088/c-code-for-non-standard-baud-rate-on-debian-raspberry-pi.

#if defined(__APPLE__) && defined(IOSSIOSPEED)
		
		// See https://developer.apple.com/library/archive/samplecode/SerialPortSample/Listings/SerialPortSample_SerialPortSample_c.html.

		// Starting with Tiger, the IOSSIOSPEED ioctl can be used to set arbitrary baud rates
		// other than those specified by POSIX. The driver for the underlying serial hardware
		// ultimately determines which baud rates can be used. This ioctl sets both the input
		// and output speed.
		speed_t new_baud = (speed_t)BaudRate;

		if (ioctl((intptr_t)hDev, IOSSIOSPEED, &new_baud) == -1)
		{
			PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : (IOSSIOSPEED) %s"
				"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
				"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n",
				strtime_m(),
				GetLastErrorMsg(),
				hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
			return EXIT_FAILURE;
		}
#elif defined(__linux__) && defined(TCSETS2)

		// See https://stackoverflow.com/questions/12646324/how-can-i-set-a-custom-baud-rate-on-linux.

		struct termios2 options2;

		memset(&options2, 0, sizeof(struct termios2));
		if (ioctl((intptr_t)hDev, TCGETS2, &options2) == -1)
		{
			PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : (TCGETS2) %s"
				"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
				"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n",
				strtime_m(),
				GetLastErrorMsg(),
				hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
			return EXIT_FAILURE;
		}

		options2.c_cflag &= ~CBAUD; // Remove current BAUD rate.
		options2.c_cflag |= BOTHER; // Allow custom BAUD rate using int input.
		options2.c_ispeed = BaudRate; // Set the input BAUD rate.
		options2.c_ospeed = BaudRate; // Set the output BAUD rate.

		if (ioctl((intptr_t)hDev, TCSETS2, &options2) == -1)
		{
			PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : (TCSETS2) %s"
				"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
				"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n",
				strtime_m(),
				GetLastErrorMsg(),
				hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
			return EXIT_FAILURE;
		}
#elif defined(__linux__) && defined(TIOCSSERIAL)
		struct serial_struct ser;

		memset(&ser, 0, sizeof(struct serial_struct));
		if (ioctl((intptr_t)hDev, TIOCGSERIAL, &ser) == -1)
		{
			PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : (TIOCGSERIAL) %s"
				"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
				"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n",
				strtime_m(),
				GetLastErrorMsg(),
				hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
			return EXIT_FAILURE;
		}

		// Set custom divisor.
		if (BaudRate != 0) ser.custom_divisor = ser.baud_base/(int)BaudRate;
		// Update flags.
		ser.flags &= ~ASYNC_SPD_MASK;
		ser.flags |= ASYNC_SPD_CUST;

		if (ioctl((intptr_t)hDev, TIOCSSERIAL, &ser) == -1)
		{
			PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : (TIOCSSERIAL) %s"
				"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
				"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n",
				strtime_m(),
				GetLastErrorMsg(),
				hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
			return EXIT_FAILURE;
		}
#else
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : %s"
			"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
			"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n",
			strtime_m(),
			"Invalid BaudRate. ",
			hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
		return EXIT_FAILURE;
#endif 
#else
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetOptionsComputerRS232Port error (%s) : %s"
			"(hDev=%#x, BaudRate=%u, ParityMode=%u, bCheckParity=%u, "
			"nbDataBits=%u, StopBitsMode=%u, timeout=%u)\n",
			strtime_m(),
			"Invalid BaudRate. ",
			hDev, BaudRate, (UINT)ParityMode, (UINT)bCheckParity, (UINT)nbDataBits, (UINT)StopBitsMode, timeout));
		return EXIT_FAILURE;
#endif // !DISABLE_CUSTOM_BAUDRATE
	}
	

#endif // _WIN32

	return EXIT_SUCCESS;
}

/*
Get the options of a computer RS232 port.

HANDLE hDev : (IN) Identifier of the computer RS232 port.
UINT* pBaudRate : (INOUT) Valid pointer that will receive the baud rate at
which the computer RS232 port operates.
BYTE* pParityMode : (INOUT) Valid pointer that will receive the computer RS232 port
parity mode. It will be either NOPARITY, ODDPARITY, EVENPARITY, MARKPARITY or
SPACEPARITY.
BOOL* pbCheckParity : (INOUT) Valid pointer that will receive TRUE if input 
parity checking is enabled, FALSE otherwise.
BYTE* pNbDataBits : (INOUT) Valid pointer that will receive the number of bits
of the data bytes.
BYTE* pStopBitsMode : (INOUT) Valid pointer that will receive the computer RS232 port
stop bits mode. It will be either ONESTOPBIT or TWOSTOPBITS.
UINT* pTimeout : (INOUT) Valid pointer that will receive the time to wait for 
every character read/write in ms.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int GetOptionsComputerRS232Port(HANDLE hDev, UINT* pBaudRate, BYTE* pParityMode, BOOL* pbCheckParity, BYTE* pNbDataBits, 
									   BYTE* pStopBitsMode, UINT* pTimeout)
{
#ifdef _WIN32
	DCB dcb;
	COMMTIMEOUTS timeouts;

	memset(&dcb, 0, sizeof(DCB));

	if (!GetCommState(hDev, &dcb))
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("GetOptionsComputerRS232Port error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}

	memset(&timeouts, 0, sizeof(COMMTIMEOUTS));

	if (!GetCommTimeouts(hDev, &timeouts))
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("GetOptionsComputerRS232Port error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}

	*pBaudRate = _Constant2BaudRate(dcb.BaudRate); 
	if (*pBaudRate == 0)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("GetOptionsComputerRS232Port error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			"Invalid BaudRate. ", 
			hDev));
		return EXIT_FAILURE;
	}

	*pParityMode = dcb.Parity;
	*pbCheckParity = dcb.fParity?TRUE:FALSE;
	*pNbDataBits = dcb.ByteSize;
	*pStopBitsMode = dcb.StopBits;
	*pTimeout = timeouts.ReadTotalTimeoutConstant;
#else 
	struct termios options;

	memset(&options, 0, sizeof(options));

	if (tcgetattr((intptr_t)hDev, &options) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("GetOptionsComputerRS232Port error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}

	*pBaudRate = _Constant2BaudRate(cfgetispeed(&options)); 
	if (*pBaudRate == 0)
	{
		// Baud rate is probably non-standard...
#ifndef DISABLE_CUSTOM_BAUDRATE
#if defined(MAC_OS_X_VERSION_10_4) && (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_4)
		PRINT_DEBUG_WARNING_OSCOMPUTERRS232PORT(("GetOptionsComputerRS232Port warning (%s) : %s(hDev=%#x)\n",
			strtime_m(),
			"Invalid BaudRate. ",
			hDev));
#elif defined(__linux__) && defined(TCSETS2)
		struct termios2 options2;
		memset(&options2, 0, sizeof(struct termios2));
		if (ioctl((intptr_t)hDev, TCGETS2, &options2) == -1)
		{
			PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("GetOptionsComputerRS232Port error (%s) : (TCGETS2) %s(hDev=%#x)\n",
				strtime_m(),
				GetLastErrorMsg(),
				hDev));
			return EXIT_FAILURE;
		}
		*pBaudRate = options2.c_ospeed;
#elif defined(__linux__) && defined(TIOCSSERIAL)
		struct serial_struct ser;
		memset(&ser, 0, sizeof(struct serial_struct));
		if (ioctl((intptr_t)hDev, TIOCGSERIAL, &ser) == -1)
		{
			PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("GetOptionsComputerRS232Port error (%s) : (TIOCGSERIAL) %s(hDev=%#x)\n",
				strtime_m(),
				GetLastErrorMsg(),
				hDev));
			return EXIT_FAILURE;
		}
		if (ser.custom_divisor != 0) *pBaudRate = ser.baud_base/(int)ser.custom_divisor;
#else
		PRINT_DEBUG_WARNING_OSCOMPUTERRS232PORT(("GetOptionsComputerRS232Port warning (%s) : %s(hDev=%#x)\n",
			strtime_m(),
			"Invalid BaudRate. ",
			hDev));
#endif 
#else
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("GetOptionsComputerRS232Port error (%s) : %s(hDev=%#x)\n",
			strtime_m(),
			"Invalid BaudRate. ",
			hDev));
		return EXIT_FAILURE;
#endif // !DISABLE_CUSTOM_BAUDRATE
	}

#ifndef __APPLE__
	switch (options.c_cflag & (CMSPAR | PARENB | PARODD))
#else
	switch (options.c_cflag & (PARENB | PARODD))
#endif // !__APPLE__
	{
	case 0:
		*pParityMode = NOPARITY;
		break;
#ifndef __APPLE__
	case (CMSPAR | PARODD):
		*pParityMode = MARKPARITY;
		break;
	case (CMSPAR):
		*pParityMode = SPACEPARITY;
		break;
#endif // !__APPLE__
	case (PARENB | PARODD):
		*pParityMode = ODDPARITY;
		break;
	case (PARENB):
		*pParityMode = EVENPARITY;
		break;
	default:
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("GetOptionsComputerRS232Port error (%s) : %s(hDev=%#x)\n",
			strtime_m(),
			"Invalid parity mode. ",
			hDev));
		return EXIT_FAILURE;
	}

	*pbCheckParity = (options.c_iflag & INPCK)?TRUE:FALSE;

	switch (options.c_cflag & CSIZE)
	{
	case CS8:
		*pNbDataBits = 8;
		break;
	case CS7:
		*pNbDataBits = 7;
		break;
	case CS6:
		*pNbDataBits = 6;
		break;
	case CS5:
		*pNbDataBits = 5;
		break;
	default:
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("GetOptionsComputerRS232Port error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			"Invalid number of data bits. ", 
			hDev));
		return EXIT_FAILURE;
	}

	*pStopBitsMode = (options.c_cflag & CSTOPB)?TWOSTOPBITS:ONESTOPBIT;

	*pTimeout = options.c_cc[VTIME]*100;
#endif // _WIN32

	return EXIT_SUCCESS;
}

/*
Discard non-transmitted output data and non-read input data on a computer RS232 port.

HANDLE hDev : (IN) Identifier of the computer RS232 port.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int PurgeComputerRS232Port(HANDLE hDev)
{
#ifdef _WIN32
	if (!PurgeComm(hDev, PURGE_RXCLEAR | PURGE_TXCLEAR))
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("PurgeComputerRS232Port error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}
#else 
	if (tcflush((intptr_t)hDev, TCIOFLUSH) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("PurgeComputerRS232Port error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}
#endif // _WIN32

	return EXIT_SUCCESS;
}

#ifdef ENABLE_DRAINRS232PORT
/*
Empty the OS internal output buffer and wait until all output written to the serial 
port has been transmitted (synchronous operation subject to flow control). Will not 
return until all pending write operations have been transmitted.

HANDLE hDev : (IN) Identifier of the computer RS232 port.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int DrainComputerRS232Port(HANDLE hDev)
{
#ifdef _WIN32
	if (!FlushFileBuffers(hDev))
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("DrainComputerRS232Port error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}
#else 
	if (tcdrain((intptr_t)hDev) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("DrainComputerRS232Port error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}
#endif // _WIN32

	return EXIT_SUCCESS;
}
#endif // ENABLE_DRAINRS232PORT

#ifdef ENABLE_DTR_FUNCTIONS
inline int SetDTRState(HANDLE hDev, BOOL bClear)
{
#ifdef _WIN32
	DWORD dwFunc = bClear? CLRDTR: SETDTR;
	if (!EscapeCommFunction(hDev, dwFunc))
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetDTRState error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}
#else 
	int dtr_bit = TIOCM_DTR;
	int cmd = bClear? TIOCMBIC: TIOCMBIS;
	if (ioctl((intptr_t)hDev, cmd, &dtr_bit) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SetDTRState error (%s) : (TIOCMBIC/TIOCMBIS) %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}
#endif // _WIN32

	return EXIT_SUCCESS;
}

inline int GetDTRState(HANDLE hDev, BOOL* pbClear)
{
#ifdef _WIN32
	PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("GetDTRState error (%s) : %s(hDev=%#x)\n", 
		strtime_m(), 
		szOSUtilsErrMsgs[EXIT_NOT_IMPLEMENTED], 
		hDev));
	return EXIT_NOT_IMPLEMENTED;
#else 
	int bits = 0;
	if (ioctl((intptr_t)hDev, TIOCMGET, &bits) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("GetDTRState error (%s) : (TIOCMGET) %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}
	if (bits & TIOCM_DTR)
		*pbClear = FALSE;
	else
		*pbClear = TRUE;
#endif // _WIN32

	return EXIT_SUCCESS;
}
#endif // ENABLE_DTR_FUNCTIONS

/*
Check for any data available to read on a computer RS232 port.

HANDLE hDev : (IN) Identifier of the computer RS232 port.

Return : EXIT_SUCCESS if there is data to read, EXIT_TIMEOUT if there is currently no data
 available or EXIT_FAILURE if there is an error.
*/
inline int CheckAvailableBytesComputerRS232Port(HANDLE hDev)
{
#ifdef _WIN32
	COMSTAT stats;

	memset(&stats, 0, sizeof(COMSTAT));
	if (!ClearCommError(hDev, NULL, &stats))
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("CheckAvailableBytesComputerRS232Port error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}
	if (stats.cbInQue <= 0) return EXIT_TIMEOUT;
#else
	int bytes_avail = 0;

	if (ioctl((intptr_t)hDev, FIONREAD, &bytes_avail) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("CheckAvailableBytesComputerRS232Port error (%s) : (FIONREAD) %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}
	if (bytes_avail <= 0) return EXIT_TIMEOUT;
#endif // _WIN32

	return EXIT_SUCCESS;
}

/*
Wait for data to read on a computer RS232 port.

HANDLE hDev : (IN) Identifier of the computer RS232 port.
int timeout : (IN) Max time to wait before returning in ms.
int checkingperiod : (IN) Checking period in ms.

Return : EXIT_SUCCESS if there is data to read, EXIT_TIMEOUT if there is currently no data
 available or EXIT_FAILURE if there is an error.
*/
inline int WaitForComputerRS232Port(HANDLE hDev, int timeout, int checkingperiod)
{
#ifdef _WIN32
	COMSTAT stats;
	CHRONO chrono;

	StartChrono(&chrono);
	do
	{
		memset(&stats, 0, sizeof(COMSTAT));
		if (ClearCommError(hDev, NULL, &stats))
		{
			if (stats.cbInQue <= 0) mSleep(checkingperiod);
			else
			{
				StopChronoQuick(&chrono);
				return EXIT_SUCCESS;
			}
		}
		else
		{
			StopChronoQuick(&chrono);
			PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("WaitForComputerRS232Port error (%s) : %s"
				"(hDev=%#x, timeout=%d, checkingperiod=%d)\n",
				strtime_m(),
				GetLastErrorMsg(),
				hDev, timeout, checkingperiod));
			return EXIT_FAILURE;
		}
	} while (GetTimeElapsedChronoQuick(&chrono) <= timeout);
	StopChronoQuick(&chrono);
	return EXIT_TIMEOUT;
#else
#ifdef DISABLE_SELECT_OSCOMPUTERRS232PORT
	CHRONO chrono;

	StartChrono(&chrono);
	do
	{
		int bytes_avail = 0;

		if (ioctl((intptr_t)hDev, FIONREAD, &bytes_avail) == EXIT_SUCCESS)
		{
			if (bytes_avail <= 0) mSleep(checkingperiod);
			else
			{
				StopChronoQuick(&chrono);
				return EXIT_SUCCESS;
			}
		}
		else
		{
			StopChronoQuick(&chrono);
			PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("WaitForComputerRS232Port error (%s) : (FIONREAD) %s"
				"(hDev=%#x, timeout=%d, checkingperiod=%d)\n",
				strtime_m(),
				GetLastErrorMsg(),
				hDev, timeout, checkingperiod));
			return EXIT_FAILURE;
		}
	} while (GetTimeElapsedChronoQuick(&chrono) <= timeout);
	StopChronoQuick(&chrono);
	return EXIT_TIMEOUT;
#else
	fd_set dev_set;
	int iResult = -1;
	struct timeval tv;

	UNREFERENCED_PARAMETER(checkingperiod);

	// Initialize a fd_set and add the socket to it.
	FD_ZERO(&dev_set);
	FD_SET((intptr_t)hDev, &dev_set);

	tv.tv_sec = (long)(timeout/1000);
	tv.tv_usec = (long)((timeout%1000)*1000);

	// Wait for the readability of the device in the fd_set, with a timeout.
	iResult = select((int)(intptr_t)hDev+1, &dev_set, NULL, NULL, &tv);

	// Remove the device from the set.
	FD_CLR((intptr_t)hDev, &dev_set);

	if (iResult == -1)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("WaitForComputerRS232Port error (%s) : %s"
			"(hDev=%#x, timeout=%d, checkingperiod=%d)\n",
			strtime_m(),
			"select failed. ",
			hDev, timeout, checkingperiod));
		return EXIT_FAILURE;
	}

	if (iResult == 0)
	{
		// The timeout on select() occured.
		return EXIT_TIMEOUT;
	}

	return EXIT_SUCCESS;
#endif // DISABLE_SELECT_OSCOMPUTERRS232PORT
#endif // _WIN32
}

/*
Send a hardware break (continuous stream of zero-valued bits) for a specific duration on a 
computer RS232 port.

HANDLE hDev : (IN) Identifier of the computer RS232 port.
int duration : (IN) Duration of the break in ms.

Return : EXIT_SUCCESS or EXIT_FAILURE if there is an error.
*/
inline int SendBreakComputerRS232Port(HANDLE hDev, int duration)
{
#ifdef _WIN32
	if (!SetCommBreak(hDev))
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SendBreakComputerRS232Port error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}
	mSleep(duration);
	if (!ClearCommBreak(hDev))
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SendBreakComputerRS232Port error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}
#else 
	if (tcsendbreak((intptr_t)hDev, duration) != EXIT_SUCCESS)
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("SendBreakComputerRS232Port error (%s) : %s(hDev=%#x)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev));
		return EXIT_FAILURE;
	}
#endif // _WIN32

	return EXIT_SUCCESS;
}

/*
Write data to a computer RS232 port.

HANDLE hDev : (IN) Identifier of the computer RS232 port.
uint8* writebuf : (IN) Valid pointer to the data to write.
UINT writebuflen : (IN) Number of bytes to write.
int* pWrittenBytes : (INOUT) Valid pointer that will receive the number of bytes written.

Return : EXIT_SUCCESS if some bytes are written, EXIT_TIMEOUT if a timeout occurs or 
EXIT_FAILURE if there is an error.
*/
inline int WriteComputerRS232Port(HANDLE hDev, uint8* writebuf, UINT writebuflen, int* pWrittenBytes)
{
#ifdef _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
	int i = 0;
#endif // _DEBUG_MESSAGES_OSCOMPUTERRS232PORT

#ifdef _WIN32
	if (WriteFile(hDev, writebuf, writebuflen, (LPDWORD)pWrittenBytes, NULL))
	{
#else 
	*pWrittenBytes = write((intptr_t)hDev, writebuf, writebuflen);
	if (*pWrittenBytes >= 0)
	{
#endif // _WIN32
		if (*pWrittenBytes == 0)
		{
			PRINT_DEBUG_WARNING_OSCOMPUTERRS232PORT(("WriteComputerRS232Port warning (%s) : %s"
				"(hDev=%#x, writebuf=%#x, writebuflen=%u)\n", 
				strtime_m(), 
				szOSUtilsErrMsgs[EXIT_TIMEOUT], 
				hDev, writebuf, writebuflen));
			return EXIT_TIMEOUT;
		}
		else
		{
#ifdef _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
			for (i = 0; i < *pWrittenBytes; i++)
			{
				PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("%.2x ", (int)writebuf[i]));
			}
			PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("\n"));
#endif // _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
			PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("Bytes written : %d\n", *pWrittenBytes));
		}
	}
	else
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("WriteComputerRS232Port error (%s) : %s"
			"(hDev=%#x, writebuf=%#x, writebuflen=%u)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev, writebuf, writebuflen));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/*
Read data from a computer RS232 port. 

HANDLE hDev : (IN) Identifier of the computer RS232 port.
uint8* readbuf : (INOUT) Valid pointer that will receive the data read.
UINT readbuflen : (IN) Number of bytes to read.
int* pReadBytes : (INOUT) Valid pointer that will receive the number of bytes read.

Return : EXIT_SUCCESS if some bytes are read, EXIT_TIMEOUT if a timeout occurs or 
EXIT_FAILURE if there is an error.
*/
inline int ReadComputerRS232Port(HANDLE hDev, uint8* readbuf, UINT readbuflen, int* pReadBytes)
{
#ifdef _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
	int i = 0;
#endif // _DEBUG_MESSAGES_OSCOMPUTERRS232PORT

#ifdef _WIN32
	if (ReadFile(hDev, readbuf, readbuflen, (LPDWORD)pReadBytes, NULL))
	{
#else 
	*pReadBytes = read((intptr_t)hDev, readbuf, readbuflen);
	if (*pReadBytes >= 0)
	{
#endif // _WIN32
		if (*pReadBytes == 0)
		{
			PRINT_DEBUG_WARNING_OSCOMPUTERRS232PORT(("ReadComputerRS232Port warning (%s) : %s"
				"(hDev=%#x, readbuf=%#x, readbuflen=%u)\n", 
				strtime_m(), 
				szOSUtilsErrMsgs[EXIT_TIMEOUT], 
				hDev, readbuf, readbuflen));
			return EXIT_TIMEOUT;
		}
		else
		{
#ifdef _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
			for (i = 0; i < *pReadBytes; i++)
			{
				PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("%.2x ", (int)readbuf[i]));
			}
			PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("\n"));
#endif // _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
			PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("Bytes read : %d\n", *pReadBytes));
		}
	}
	else
	{
		PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("ReadComputerRS232Port error (%s) : %s"
			"(hDev=%#x, readbuf=%#x, readbuflen=%u)\n", 
			strtime_m(), 
			GetLastErrorMsg(), 
			hDev, readbuf, readbuflen));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/*
Write data to a computer RS232 port. Retry automatically if all the bytes were not written.

HANDLE hDev : (IN) Identifier of the computer RS232 port.
uint8* writebuf : (IN) Valid pointer to the data to write.
UINT writebuflen : (IN) Number of bytes to write.

Return : EXIT_SUCCESS if all the bytes are written, EXIT_TIMEOUT if a timeout occurs or 
EXIT_FAILURE if there is an error.
*/
inline int WriteAllComputerRS232Port(HANDLE hDev, uint8* writebuf, UINT writebuflen)
{
#ifdef _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
	UINT i = 0;
#endif // _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
	UINT BytesWritten = 0;
	int Bytes = 0;

	while (BytesWritten < writebuflen)
	{
#ifdef _WIN32
		if (WriteFile(hDev, writebuf + BytesWritten, writebuflen - BytesWritten, (LPDWORD)&Bytes, NULL))
		{
#else 
		Bytes = write((intptr_t)hDev, writebuf + BytesWritten, writebuflen - BytesWritten);
		if (Bytes >= 0)
		{
#endif // _WIN32
			if (Bytes == 0)
			{
				PRINT_DEBUG_WARNING_OSCOMPUTERRS232PORT(("WriteAllComputerRS232Port warning (%s) : %s"
					"(hDev=%#x, writebuf=%#x, writebuflen=%u)\n", 
					strtime_m(), 
					szOSUtilsErrMsgs[EXIT_TIMEOUT], 
					hDev, writebuf, writebuflen));
#ifdef _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
				for (i = 0; i < BytesWritten; i++)
				{
					PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("%.2x ", (int)writebuf[i]));
				}
				PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("\n"));
#endif // _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
				PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("Total bytes written : %u\n", BytesWritten));
				return EXIT_TIMEOUT;
			}
			else
			{
				PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("Bytes written : %d\n", Bytes));
			}
		}
		else
		{
			PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("WriteAllComputerRS232Port error (%s) : %s"
				"(hDev=%#x, writebuf=%#x, writebuflen=%u)\n", 
				strtime_m(), 
				GetLastErrorMsg(), 
				hDev, writebuf, writebuflen));
#ifdef _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
			for (i = 0; i < BytesWritten; i++)
			{
				PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("%.2x ", (int)writebuf[i]));
			}
			PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("\n"));
#endif // _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
			PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("Total bytes written : %u\n", BytesWritten));
			return EXIT_FAILURE;
		}

		BytesWritten += Bytes;
	}

#ifdef _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
	for (i = 0; i < BytesWritten; i++)
	{
		PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("%.2x ", (int)writebuf[i]));
	}
	PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("\n"));
#endif // _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
	PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("Total bytes written : %u\n", BytesWritten));

	return EXIT_SUCCESS;
}

/*
Read data from a computer RS232 port. Retry automatically if all the bytes were not read.

HANDLE hDev : (IN) Identifier of the computer RS232 port.
uint8* readbuf : (INOUT) Valid pointer that will receive the data read.
UINT readbuflen : (IN) Number of bytes to read.

Return : EXIT_SUCCESS if all the bytes are read, EXIT_TIMEOUT if a timeout occurs or 
EXIT_FAILURE if there is an error.
*/
inline int ReadAllComputerRS232Port(HANDLE hDev, uint8* readbuf, UINT readbuflen)
{
#ifdef _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
	UINT i = 0;
#endif // _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
	UINT BytesRead = 0;
	int Bytes = 0;

	while (BytesRead < readbuflen)
	{
#ifdef _WIN32
		if (ReadFile(hDev, readbuf + BytesRead, readbuflen - BytesRead, (LPDWORD)&Bytes, NULL))
		{
#else 
		Bytes = read((intptr_t)hDev, readbuf + BytesRead, readbuflen - BytesRead);
		if (Bytes >= 0)
		{
#endif // _WIN32
			if (Bytes == 0)
			{
				PRINT_DEBUG_WARNING_OSCOMPUTERRS232PORT(("ReadAllComputerRS232Port warning (%s) : %s"
					"(hDev=%#x, readbuf=%#x, readbuflen=%u)\n", 
					strtime_m(), 
					szOSUtilsErrMsgs[EXIT_TIMEOUT], 
					hDev, readbuf, readbuflen));
#ifdef _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
				for (i = 0; i < BytesRead; i++)
				{
					PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("%.2x ", (int)readbuf[i]));
				}
				PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("\n"));
#endif // _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
				PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("Total bytes read : %u\n", BytesRead));
				return EXIT_TIMEOUT;
			}
			else
			{
				PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("Bytes read : %d\n", Bytes));
			}
		}
		else
		{
			PRINT_DEBUG_ERROR_OSCOMPUTERRS232PORT(("ReadAllComputerRS232Port error (%s) : %s"
				"(hDev=%#x, readbuf=%#x, readbuflen=%u)\n", 
				strtime_m(), 
				GetLastErrorMsg(), 
				hDev, readbuf, readbuflen));
#ifdef _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
			for (i = 0; i < BytesRead; i++)
			{
				PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("%.2x ", (int)readbuf[i]));
			}
			PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("\n"));
#endif // _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
			PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("Total bytes read : %u\n", BytesRead));
			return EXIT_FAILURE;
		}

		BytesRead += Bytes;
	}

#ifdef _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
	for (i = 0; i < BytesRead; i++)
	{
		PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("%.2x ", (int)readbuf[i]));
	}
	PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("\n"));
#endif // _DEBUG_MESSAGES_OSCOMPUTERRS232PORT
	PRINT_DEBUG_MESSAGE_OSCOMPUTERRS232PORT(("Total bytes read : %u\n", BytesRead));

	return EXIT_SUCCESS;
}

#endif // !OSCOMPUTERRS232PORT_H
