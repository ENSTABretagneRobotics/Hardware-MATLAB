/***************************************************************************************************************:')

OSTime.c

Functions related to the time.

Fabrice Le Bars
GetTickCount() from the file ue9.c provided by www.labjack.com
strtime_m() and strtime_fns() are based on a part of an example in the MSDN library

Created : 2009-01-28

***************************************************************************************************************:)*/

// Prevent Visual Studio Intellisense from defining _WIN32 and _MSC_VER when we use 
// Visual Studio to edit Linux or Borland C++ code.
#ifdef __linux__
#	undef _WIN32
#endif // __linux__
#if defined(__GNUC__) || defined(__BORLANDC__)
#	undef _MSC_VER
#endif // defined(__GNUC__) || defined(__BORLANDC__)

#include "OSTime.h"

char strftime_m_tmpbuf[64]; // Used to store the string returned by strtime_m().
char strftimeex_m_tmpbuf[64]; // Used to store the string returned by strtimeex_m().
char strftime_fns_tmpbuf[64]; // Used to store the string returned by strtime_fns().
char strftimeex_fns_tmpbuf[64]; // Used to store the string returned by strtimeex_fns().

/*
Return a string like ctime() but in this format :

2007-08-27 19:28:04\0

(without the "\n" of ctime()).
Should not be used in concurrent threads as the string value returned might 
be changed by another thread.

Return : This string.
*/
char* strtime_m(void)
{
#ifndef WINCE
	time_t t;
	struct tm *timeptr = NULL;

	memset(strftime_m_tmpbuf, 0, sizeof(strftime_m_tmpbuf));

	time(&t);
	timeptr = localtime(&t);

	if (timeptr == NULL)
	{
		return strftime_m_tmpbuf;
	}

	// Use strftime to build a customized time string. 
	if (strftime(
		strftime_m_tmpbuf,
		sizeof(strftime_m_tmpbuf),
		"%Y-%m-%d %H:%M:%S",
		timeptr
		) <= 0)
	{
		memset(strftime_m_tmpbuf, 0, sizeof(strftime_m_tmpbuf));
		return strftime_m_tmpbuf;
	}
#else
	int nb = 0;
	TCHAR* tstr = (TCHAR*)calloc(sizeof(strftime_m_tmpbuf), sizeof(TCHAR));

	memset(strftime_m_tmpbuf, 0, sizeof(strftime_m_tmpbuf));

	if (tstr == NULL)
	{
		return strftime_m_tmpbuf;
	}

	memset(tstr, 0, sizeof(strftime_m_tmpbuf)*sizeof(TCHAR));

	// Use GetDateFormat() and GetTimeFormat() to build a customized time string. 
	nb = GetDateFormat(
		MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT), // Locale.
		0, // Flags.
		NULL, // Current local system date.
		_T("yyyy'-'MM'-'dd' '"), // Format the string. 
		tstr, 
		sizeof(strftime_m_tmpbuf)
		);
	if (nb <= 0)
	{
		free(tstr); tstr = NULL;
		return strftime_m_tmpbuf;
	}

	if (GetTimeFormat(
		MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT), // Locale.
		0, // Flags.
		NULL, // Current local system time.
		_T("HH':'mm':'ss"), // Format the string. 
		tstr+(nb-1), 
		sizeof(strftime_m_tmpbuf)-(nb-1)
		) <= 0)
	{
		free(tstr); tstr = NULL;
		return strftime_m_tmpbuf;
	}

#ifdef UNICODE
	wcstombs(strftime_m_tmpbuf, tstr, sizeof(strftime_m_tmpbuf));
#else
	memcpy(strftime_m_tmpbuf, tstr, sizeof(strftime_m_tmpbuf));
#endif // UNICODE
	strftime_m_tmpbuf[sizeof(strftime_m_tmpbuf)-1] = 0;
	free(tstr); tstr = NULL;
#endif // !WINCE

	return strftime_m_tmpbuf;
}

#if (defined(_WIN32) && (defined(ENABLE_GETTIMEOFDAY_WIN32) || defined(ENABLE_SYS_TIME_H_WIN32))) || (!defined(_WIN32))
/*
Return a string like ctime() but in this format :

2007-08-27 19:28:04:00\0

(without the "\n" of ctime()).
Should not be used in concurrent threads as the string value returned might
be changed by another thread.

Return : This string.
*/
char* strtimeex_m(void)
{
	char sztmp[4];
	struct timeval tv;
#ifndef WINCE
	time_t tt;
	struct tm *timeptr = NULL;

	memset(strftimeex_m_tmpbuf, 0, sizeof(strftimeex_m_tmpbuf));

	if (gettimeofday(&tv, NULL) != EXIT_SUCCESS) { tv.tv_sec = 0; tv.tv_usec = 0; time(&tt); }
	else { tt = tv.tv_sec; }
	timeptr = localtime(&tt);

	if (timeptr == NULL)
	{
		return strftimeex_m_tmpbuf;
	}

	// Use strftime to build a customized time string. 
	if (strftime(
		strftimeex_m_tmpbuf,
		sizeof(strftimeex_m_tmpbuf),
		"%Y-%m-%d %H:%M:%S",
		timeptr
	) <= 0)
	{
		memset(strftimeex_m_tmpbuf, 0, sizeof(strftimeex_m_tmpbuf));
		return strftimeex_m_tmpbuf;
	}
#else
	int nb = 0;
	TCHAR* tstr = (TCHAR*)calloc(sizeof(strftimeex_m_tmpbuf), sizeof(TCHAR));

	memset(strftimeex_m_tmpbuf, 0, sizeof(strftimeex_m_tmpbuf));

	if (tstr == NULL)
	{
		return strftimeex_m_tmpbuf;
	}

	memset(tstr, 0, sizeof(strftimeex_m_tmpbuf)*sizeof(TCHAR));

	// Use GetDateFormat() and GetTimeFormat() to build a customized time string. 
	nb = GetDateFormat(
		MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT), // Locale.
		0, // Flags.
		NULL, // Current local system date.
		_T("yyyy'-'MM'-'dd' '"), // Format the string. 
		tstr,
		sizeof(strftimeex_m_tmpbuf)
	);
	if (nb <= 0)
	{
		free(tstr); tstr = NULL;
		return strftimeex_m_tmpbuf;
	}

	if (GetTimeFormat(
		MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT), // Locale.
		0, // Flags.
		NULL, // Current local system time.
		_T("HH':'mm':'ss"), // Format the string. 
		tstr+(nb-1),
		sizeof(strftimeex_m_tmpbuf)-(nb-1)
	) <= 0)
	{
		free(tstr); tstr = NULL;
		return strftimeex_m_tmpbuf;
	}

	if (gettimeofday(&tv, NULL) != EXIT_SUCCESS) { tv.tv_sec = 0; tv.tv_usec = 0; }

#ifdef UNICODE
	wcstombs(strftimeex_m_tmpbuf, tstr, sizeof(strftimeex_m_tmpbuf));
#else
	memcpy(strftimeex_m_tmpbuf, tstr, sizeof(strftimeex_m_tmpbuf));
#endif // UNICODE
	strftimeex_m_tmpbuf[sizeof(strftimeex_m_tmpbuf)-sizeof(sztmp)-1] = 0;
	free(tstr); tstr = NULL;
#endif // !WINCE

#ifndef DISABLE_USE_SNPRINTF
	snprintf(sztmp, sizeof(sztmp), ":%02d", (int)(tv.tv_usec/10000));
#else
	sprintf(sztmp, ":%02d", (int)(tv.tv_usec/10000));
#endif // DISABLE_USE_SNPRINTF
	strcat(strftimeex_fns_tmpbuf, sztmp);

	return strftimeex_m_tmpbuf;
}
#endif // (defined(_WIN32) && (defined(ENABLE_GETTIMEOFDAY_WIN32) || defined(ENABLE_SYS_TIME_H_WIN32))) || (!defined(_WIN32))

/*
Return a string like ctime() but in this format :

2007-08-27_19h28min04s\0

(without the "\n", ":", " " of ctime() in order to be safely used in file names).
Should not be used in concurrent threads as the string value returned might 
be changed by another thread.

Return : This string.
*/
char* strtime_fns(void)	
{
#ifndef WINCE
	time_t t;
	struct tm *timeptr = NULL;

	memset(strftime_fns_tmpbuf, 0, sizeof(strftime_fns_tmpbuf));

	time(&t);
	timeptr = localtime(&t);

	if (timeptr == NULL)
	{
		return strftime_fns_tmpbuf;
	}

	// Use strftime to build a customized time string. 
	if (strftime(
		strftime_fns_tmpbuf,
		sizeof(strftime_fns_tmpbuf),
		"%Y-%m-%d_%Hh%Mmin%Ss",
		timeptr
		) <= 0)
	{
		memset(strftime_fns_tmpbuf, 0, sizeof(strftime_fns_tmpbuf));
		return strftime_fns_tmpbuf;
	}
#else
	int nb = 0;
	TCHAR* tstr = (TCHAR*)calloc(sizeof(strftime_fns_tmpbuf), sizeof(TCHAR));

	memset(strftime_fns_tmpbuf, 0, sizeof(strftime_fns_tmpbuf));

	if (tstr == NULL)
	{
		return strftime_fns_tmpbuf;
	}

	memset(tstr, 0, sizeof(strftime_fns_tmpbuf)*sizeof(TCHAR));

	// Use GetDateFormat() and GetTimeFormat() to build a customized time string. 
	nb = GetDateFormat(
		MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT), // Locale.
		0, // Flags.
		NULL, // Current local system date.
		_T("yyyy'-'MM'-'dd'_'"), // Format the string. 
		tstr, 
		sizeof(strftime_fns_tmpbuf)
		);
	if (nb <= 0)
	{
		free(tstr); tstr = NULL;
		return strftime_fns_tmpbuf;
	}

	if (GetTimeFormat(
		MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT), // Locale.
		0, // Flags.
		NULL, // Current local system time.
		_T("HH'h'mm'min'ss's'"), // Format the string. 
		tstr+(nb-1), 
		sizeof(strftime_fns_tmpbuf)-(nb-1)
		) <= 0)
	{
		free(tstr); tstr = NULL;
		return strftime_fns_tmpbuf;
	}

#ifdef UNICODE
	wcstombs(strftime_fns_tmpbuf, tstr, sizeof(strftime_fns_tmpbuf));
#else
	memcpy(strftime_fns_tmpbuf, tstr, sizeof(strftime_fns_tmpbuf));
#endif // UNICODE
	strftime_fns_tmpbuf[sizeof(strftime_fns_tmpbuf)-1] = 0;
	free(tstr); tstr = NULL;
#endif // !WINCE

	return strftime_fns_tmpbuf;
}

#if (defined(_WIN32) && (defined(ENABLE_GETTIMEOFDAY_WIN32) || defined(ENABLE_SYS_TIME_H_WIN32))) || (!defined(_WIN32))
/*
Return a string like ctime() but in this format :

2007-08-27_19h28min04s00\0

(without the "\n", ":", " " of ctime() in order to be safely used in file names).
Should not be used in concurrent threads as the string value returned might
be changed by another thread.

Return : This string.
*/
char* strtimeex_fns(void)
{
	char sztmp[3];
	struct timeval tv;
#ifndef WINCE
	time_t tt;
	struct tm *timeptr = NULL;

	memset(strftimeex_fns_tmpbuf, 0, sizeof(strftimeex_fns_tmpbuf));

	if (gettimeofday(&tv, NULL) != EXIT_SUCCESS) { tv.tv_sec = 0; tv.tv_usec = 0; time(&tt); }
	else { tt = tv.tv_sec; }
	timeptr = localtime(&tt);

	if (timeptr == NULL)
	{
		return strftimeex_fns_tmpbuf;
	}

	// Use strftime to build a customized time string. 
	if (strftime(
		strftimeex_fns_tmpbuf,
		sizeof(strftimeex_fns_tmpbuf),
		"%Y-%m-%d_%Hh%Mmin%Ss",
		timeptr
	) <= 0)
	{
		memset(strftimeex_fns_tmpbuf, 0, sizeof(strftimeex_fns_tmpbuf));
		return strftimeex_fns_tmpbuf;
	}
#else
	int nb = 0;
	TCHAR* tstr = (TCHAR*)calloc(sizeof(strftimeex_fns_tmpbuf), sizeof(TCHAR));

	memset(strftimeex_fns_tmpbuf, 0, sizeof(strftimeex_fns_tmpbuf));

	if (tstr == NULL)
	{
		return strftimeex_fns_tmpbuf;
	}

	memset(tstr, 0, sizeof(strftimeex_fns_tmpbuf)*sizeof(TCHAR));

	// Use GetDateFormat() and GetTimeFormat() to build a customized time string. 
	nb = GetDateFormat(
		MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT), // Locale.
		0, // Flags.
		NULL, // Current local system date.
		_T("yyyy'-'MM'-'dd'_'"), // Format the string. 
		tstr,
		sizeof(strftimeex_fns_tmpbuf)
	);
	if (nb <= 0)
	{
		free(tstr); tstr = NULL;
		return strftimeex_fns_tmpbuf;
	}

	if (GetTimeFormat(
		MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT), // Locale.
		0, // Flags.
		NULL, // Current local system time.
		_T("HH'h'mm'min'ss's'"), // Format the string. 
		tstr+(nb-1),
		sizeof(strftimeex_fns_tmpbuf)-(nb-1)
	) <= 0)
	{
		free(tstr); tstr = NULL;
		return strftimeex_fns_tmpbuf;
	}

	if (gettimeofday(&tv, NULL) != EXIT_SUCCESS) { tv.tv_sec = 0; tv.tv_usec = 0; }

#ifdef UNICODE
	wcstombs(strftimeex_fns_tmpbuf, tstr, sizeof(strftimeex_fns_tmpbuf));
#else
	memcpy(strftimeex_fns_tmpbuf, tstr, sizeof(strftimeex_fns_tmpbuf));
#endif // UNICODE
	strftimeex_fns_tmpbuf[sizeof(strftimeex_fns_tmpbuf)-sizeof(sztmp)-1] = 0;
	free(tstr); tstr = NULL;
#endif // !WINCE

#ifndef DISABLE_USE_SNPRINTF
	snprintf(sztmp, sizeof(sztmp), "%02d", (int)(tv.tv_usec/10000));
#else
	sprintf(sztmp, "%02d", (int)(tv.tv_usec/10000));
#endif // DISABLE_USE_SNPRINTF
	strcat(strftimeex_fns_tmpbuf, sztmp);

	return strftimeex_fns_tmpbuf;
}
#endif // (defined(_WIN32) && (defined(ENABLE_GETTIMEOFDAY_WIN32) || defined(ENABLE_SYS_TIME_H_WIN32))) || (!defined(_WIN32))
