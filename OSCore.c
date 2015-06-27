/***************************************************************************************************************:')

OSCore.c

Include the main Linux and Windows headers. Some Windows types ported to Linux.
Debug and error handling functions, macros and strings.

Fabrice Le Bars

Created : 2007

Version status : Tested some parts

***************************************************************************************************************:)*/

// Prevent Visual Studio Intellisense from defining _WIN32 and _MSC_VER when we use 
// Visual Studio to edit Linux or Borland C++ code.
#ifdef __linux__
#	undef _WIN32
#endif // __linux__
#if defined(__GNUC__) || defined(__BORLANDC__)
#	undef _MSC_VER
#endif // defined(__GNUC__) || defined(__BORLANDC__)

#include "OSCore.h"

const char* szOSUtilsErrMsgs[] = {
	"The operation completed successfully. ", // EXIT_SUCCESS
	"The operation failed. ", // EXIT_FAILURE
	"The operation timed out. ", // EXIT_TIMEOUT
	"The parameter is incorrect. ", // EXIT_INVALID_PARAMETER
	"Invalid data. ", // EXIT_INVALID_DATA
	"Name too long. ", // EXIT_NAME_TOO_LONG
	"Out of memory. ", // EXIT_OUT_OF_MEMORY
	"The object is nonsignaled. ", // EXIT_OBJECT_NONSIGNALED
	"Cannot create another system semaphore. ", // EXIT_TOO_MANY_SEMAPHORES
	"The thread was killed. ", // EXIT_KILLED_THREAD
	"The thread was canceled. ", // EXIT_CANCELED_THREAD
	"Overlapped I/O operation is in progress. ", // EXIT_IO_PENDING
	"The process was killed. ", // EXIT_KILLED_PROCESS
	"Element changed. ", // EXIT_CHANGED
	"Element not changed. ", // EXIT_NOT_CHANGED
	"Element found. ", // EXIT_FOUND
	"Element not found. ", // EXIT_NOT_FOUND
	"Not implemented. ", // EXIT_NOT_IMPLEMENTED
	""
};

/*
Format a message corresponding to the last error in a system call (thread-
safe).

char* buf : (INOUT) Valid pointer to a buffer that will receive the message.
int buflen : (IN) Size of the buffer in bytes.

Return : buf or NULL if buf is too small.
*/
char* FormatLastErrorMsg(char* buf, int buflen)
{
#ifdef _WIN32
	TCHAR* tstr = NULL;
#endif // _WIN32

	if (buflen < 32)
	{
		return NULL;
	}

#ifdef _WIN32
	tstr = (TCHAR*)calloc((size_t)buflen, sizeof(TCHAR));

	memset(buf, 0, (size_t)buflen);

	if (tstr == NULL)
	{
		sprintf(buf, "calloc failed. ");
		buf[buflen-1] = 0;
		return buf;
	}

	memset(tstr, 0, (size_t)(buflen*sizeof(TCHAR)));

	if (!FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS | 
		FORMAT_MESSAGE_MAX_WIDTH_MASK, // Remove the line break at the end. 
		// Note that there is still a dot and a space at the end.
		NULL,
		GetLastError(),
		0,
		tstr,
		(DWORD)buflen,
		NULL
		))
	{
		sprintf(buf, "FormatMessage failed. ");
		buf[buflen-1] = 0;
		free(tstr); tstr = NULL;
		return buf;
	}

#ifdef UNICODE
	wcstombs(buf, tstr, buflen);
#else
	memcpy(buf, tstr, buflen);
#endif // UNICODE
	buf[buflen-1] = 0;
	free(tstr); tstr = NULL;
#else
	char* lpMsgBuf = (char*)calloc((size_t)buflen, sizeof(char));

	memset(buf, 0, (size_t)buflen);

	if (lpMsgBuf == NULL)
	{
		sprintf(buf, "calloc failed. ");
		buf[buflen-1] = 0;
		return buf;
	}

	memset(lpMsgBuf, 0, (size_t)buflen);

	// Note that pthreads do not use errno!

#ifdef __ANDROID__
	if (strerror_r(errno, lpMsgBuf, (size_t)buflen-3) == EXIT_SUCCESS)
	{
		// Here the use of snprintf() is mandatory to be sure that buf do not overflow...
		snprintf(buf, (size_t)buflen, "%s. ", lpMsgBuf);
	}
	else
	{
		sprintf(buf, "strerror_r failed. ");
	}
#else
	// GNU version of strerror_r() is strange...
	// Here the use of snprintf() is mandatory to be sure that buf do not overflow...
	snprintf(buf, (size_t)buflen, "%s. ", strerror_r(errno, lpMsgBuf, (size_t)buflen-3));
#endif // __ANDROID__

	buf[buflen-1] = 0;

	free(lpMsgBuf); lpMsgBuf = NULL;
#endif // _WIN32

	return buf;
}

#ifdef _DEBUG_DISPLAY
void fprintf_stdout(const char * _Format, ...)
{
	va_list VaList;

	va_start(VaList, _Format);
	vfprintf(stdout, _Format, VaList);
	fflush(stdout);
	va_end(VaList);
}

void fprintf_stderr(const char * _Format, ...)
{
	va_list VaList;

	va_start(VaList, _Format);
	vfprintf(stderr, _Format, VaList);
	fflush(stderr);
	va_end(VaList);
}
#endif // _DEBUG_DISPLAY

#ifdef _DEBUG_FILE
void fprintf_messages_file(const char * _Format, ...)
{
	FILE* file;
	va_list VaList;

	va_start(VaList, _Format);
	file = fopen(MESSAGES_FILENAME, "a");
	vfprintf(file, _Format, VaList);
	fclose(file);
	va_end(VaList);
}

void fprintf_warnings_file(const char * _Format, ...)
{
	FILE* file;
	va_list VaList;

	va_start(VaList, _Format);
	file = fopen(WARNINGS_FILENAME, "a");
	vfprintf(file, _Format, VaList);
	fclose(file);
	va_end(VaList);
}

void fprintf_errors_file(const char * _Format, ...)
{
	FILE* file;
	va_list VaList;

	va_start(VaList, _Format);
	file = fopen(ERRORS_FILENAME, "a");
	vfprintf(file, _Format, VaList);
	fclose(file);
	va_end(VaList);
}
#endif // _DEBUG_FILE
