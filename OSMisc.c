/***************************************************************************************************************:')

OSMisc.c

Miscellaneous things.

Fabrice Le Bars

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

#include "OSMisc.h"

// Need to be undefined at the end of the file...
// min and max might cause incompatibilities with GCC...
#ifndef _MSC_VER
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif // !max
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif // !min
#endif // !_MSC_VER

#ifndef DISABLE_USER_INPUT_FUNCTIONS
#ifndef DISABLE_USER_INPUT_TIMEOUT_FUNCTIONS
//// From olsrd...
//void clear_console(void)
//{
//#if !defined WINCE
//	HANDLE Hand;
//	CONSOLE_SCREEN_BUFFER_INFO Info;
//	unsigned long Written;
//	static COORD Home = { 0, 0 };
//
//	Hand = GetStdHandle(STD_OUTPUT_HANDLE);
//
//	if (Hand == INVALID_HANDLE_VALUE)
//		return;
//
//	if (!GetConsoleScreenBufferInfo(Hand, &Info))
//		return;
//
//	if (!FillConsoleOutputCharacter(Hand, ' ', Info.dwSize.X * Info.dwSize.Y, Home, &Written))
//		return;
//
//	if (!FillConsoleOutputAttribute(Hand, Info.wAttributes, Info.dwSize.X * Info.dwSize.Y, Home, &Written))
//		return;
//
//	SetConsoleCursorPosition(Hand, Home);
//#endif
//}

//// From olsrd...
//int isatty(int fd)
//{
//#if !defined WINCE
//	HANDLE Hand;
//	CONSOLE_SCREEN_BUFFER_INFO Info;
//	unsigned long Events;
//
//	if (fd == 0) {
//		Hand = GetStdHandle(STD_INPUT_HANDLE);
//		return GetNumberOfConsoleInputEvents(Hand, &Events);
//	}
//
//	else if (fd == 1) {
//		Hand = GetStdHandle(STD_OUTPUT_HANDLE);
//		return GetConsoleScreenBufferInfo(Hand, &Info);
//	}
//
//	else if (fd == 2) {
//		Hand = GetStdHandle(STD_ERROR_HANDLE);
//		return GetConsoleScreenBufferInfo(Hand, &Info);
//	}
//
//	return -1;
//#else
//	return 0;
//#endif
//}

/*
Prompt for the user to press any key until a specified timeout.

UINT timeout : (IN) Time to wait to get at least 1 char in ms (with a 
precision of tenths of s, max is MAX_TIMEOUT_PROMPTGETUSERINPUTTIMEOUT).

Return : The first character pressed.
*/
char PromptForUserInputTimeout(UINT timeout)
{
#ifdef _WIN32
	HANDLE hStdin = INVALID_HANDLE_VALUE;
	DWORD fdwMode = 0, fdwSaveOldMode = 0;
	INPUT_RECORD irInBuf[1]; 
	DWORD cNumRead = 0;
	//char buf[32];
	//DWORD dwReadBytes = 0;
	CHRONO chrono;
	double duration = 0;

	fprintf(stdout, "Press any key to continue . . . ");
	fflush(stdout);

	hStdin = CreateFile(_T("CONIN$"), 
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE, 
		NULL, // No security attributes.
		OPEN_EXISTING, // Must use OPEN_EXISTING.
		0,    // Ignored for console.
		NULL  // Ignored for console.
		);

	//hStdin = GetStdHandle(STD_INPUT_HANDLE); 

	GetConsoleMode(hStdin, &fdwSaveOldMode);

	//fdwMode = fdwSaveOldMode&~(ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT);
	fdwMode = ENABLE_PROCESSED_INPUT;

	SetConsoleMode(hStdin, fdwMode);

	FlushConsoleInputBuffer(hStdin);

	memset(irInBuf, 0, 1*sizeof(INPUT_RECORD));
	//memset(buf, 0, 32);

	//if (WaitForSingleObject(hStdin, (DWORD)timeout) == WAIT_OBJECT_0)
	//	ReadConsoleInput(hStdin, irInBuf, 1, &cNumRead);
	//	//ReadFile(hStdin, buf, 32, &dwReadBytes, NULL);

	StartChrono(&chrono);
	while (irInBuf->EventType != KEY_EVENT)
	{
		memset(irInBuf, 0, 1*sizeof(INPUT_RECORD));
		GetTimeElapsedChrono(&chrono, &duration);
		if ((int)timeout-(int)(duration*1000) > 0)
		{
			// min to try to handle also wrap around of the time in the integer values...
			timeout = (UINT)min((int)timeout-(int)(duration*1000), (int)timeout);
		}
		else
		{
			// We reached the timeout.
			break;
		}
		if (WaitForSingleObject(hStdin, (DWORD)timeout) == WAIT_OBJECT_0)
		{
			//PRINT_DEBUG_MESSAGE_OSMISC(("%s. \n", GetLastErrorMsg()));
			ReadConsoleInput(hStdin, irInBuf, 1, &cNumRead);
		}
	}
	StopChrono(&chrono, &duration);

	SetConsoleMode(hStdin, fdwSaveOldMode);
	
	//FlushConsoleInputBuffer(hStdin);

	CloseHandle(hStdin);

	fprintf(stdout, "\n");
	fflush(stdout);

	return (char)irInBuf[0].Event.KeyEvent.uChar.AsciiChar;
	//return buf[0];
#else 
	struct termios term, back;
	char buf[32];
	ssize_t nbbytes = 0;

	fprintf(stdout, "Press any key to continue . . . ");
	fflush(stdout);

	tcgetattr(STDIN_FILENO, &term); // Get the stdin terminal information.
	memcpy(&back, &term, sizeof(term)); // Save it.

	term.c_lflag &= ~(ICANON|ECHO); // Modify terminal options.
	term.c_cc[VTIME] = timeout/100; // Time to wait for every character read in tenths of seconds.
	term.c_cc[VMIN] = 0; // Minimum number of characters to read. 

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term); // Modify stdin attributes.

	tcflush(STDIN_FILENO, TCIFLUSH); // Flush any previous input on stdin.

	memset(buf, 0, 32);

	nbbytes = read(STDIN_FILENO, buf, 32); // Wait for a character.

	if (nbbytes == 0) buf[0] = 0;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &back); // Restore previous attributes.

	fprintf(stdout, "\n");
	fflush(stdout);

	return buf[0];
#endif // _WIN32
}

/*
Wait for the user to press any key until a specified timeout.

UINT timeout : (IN) Time to wait to get at least 1 char in ms (with a 
precision of tenths of s, max is MAX_TIMEOUT_PROMPTGETUSERINPUTTIMEOUT).

Return : The first character pressed.
*/
char GetUserInputTimeout(UINT timeout)
{
#ifdef _WIN32
	HANDLE hStdin = INVALID_HANDLE_VALUE;
	DWORD fdwMode = 0, fdwSaveOldMode = 0;
	INPUT_RECORD irInBuf[1]; 
	DWORD cNumRead = 0;
	//char buf[32];
	//DWORD dwReadBytes = 0;
	CHRONO chrono;
	double duration = 0;

	hStdin = CreateFile(_T("CONIN$"), 
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE, 
		NULL, // No security attributes.
		OPEN_EXISTING, // Must use OPEN_EXISTING.
		0,    // Ignored for console.
		NULL  // Ignored for console.
		);

	//hStdin = GetStdHandle(STD_INPUT_HANDLE); 

	GetConsoleMode(hStdin, &fdwSaveOldMode);

	//fdwMode = fdwSaveOldMode&~(ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT);
	fdwMode = ENABLE_PROCESSED_INPUT;

	SetConsoleMode(hStdin, fdwMode);

	FlushConsoleInputBuffer(hStdin);

	memset(irInBuf, 0, 1*sizeof(INPUT_RECORD));
	//memset(buf, 0, 32);

	//if (WaitForSingleObject(hStdin, (DWORD)timeout) == WAIT_OBJECT_0)
	//	ReadConsoleInput(hStdin, irInBuf, 1, &cNumRead);
	//	//ReadFile(hStdin, buf, 32, &dwReadBytes, NULL);

	StartChrono(&chrono);
	while (irInBuf->EventType != KEY_EVENT)
	{
		memset(irInBuf, 0, 1*sizeof(INPUT_RECORD));
		GetTimeElapsedChrono(&chrono, &duration);
		if ((int)timeout-(int)(duration*1000) > 0)
		{
			// min to try to handle also wrap around of the time in the integer values...
			timeout = (UINT)min((int)timeout-(int)(duration*1000), (int)timeout);
		}
		else
		{
			// We reached the timeout.
			break;
		}
		if (WaitForSingleObject(hStdin, (DWORD)timeout) == WAIT_OBJECT_0)
		{
			//PRINT_DEBUG_MESSAGE_OSMISC(("%s. \n", GetLastErrorMsg()));
			ReadConsoleInput(hStdin, irInBuf, 1, &cNumRead);
		}
	}
	StopChrono(&chrono, &duration);

	SetConsoleMode(hStdin, fdwSaveOldMode);

	//FlushConsoleInputBuffer(hStdin);

	CloseHandle(hStdin);

	return (char)irInBuf[0].Event.KeyEvent.uChar.AsciiChar;
	//return buf[0];
#else 
	struct termios term, back;
	char buf[32];
	ssize_t nbbytes = 0;

	tcgetattr(STDIN_FILENO, &term); // Get the stdin terminal information.
	memcpy(&back, &term, sizeof(term)); // Save it.

	term.c_lflag &= ~(ICANON|ECHO); // Modify terminal options.
	term.c_cc[VTIME] = timeout/100; // Time to wait for every character read in tenths of seconds.
	term.c_cc[VMIN] = 0; // Minimum number of characters to read. 

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term); // Modify stdin attributes.

	tcflush(STDIN_FILENO, TCIFLUSH); // Flush any previous input on stdin.

	memset(buf, 0, 32);

	nbbytes = read(STDIN_FILENO, buf, 32); // Wait for a character.

	if (nbbytes == 0) buf[0] = 0;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &back); // Restore previous attributes.

	return buf[0];
#endif // _WIN32
}
#endif // !DISABLE_USER_INPUT_TIMEOUT_FUNCTIONS

/*
Prompt for the user to press any key.

Return : The first character pressed.
*/
char PromptForUserInput(void)
{
#ifdef _WIN32
	HANDLE hStdin = INVALID_HANDLE_VALUE;
	DWORD fdwMode = 0, fdwSaveOldMode = 0;
	INPUT_RECORD irInBuf[1]; 
	DWORD cNumRead = 0;
	//char buf[32];
	//DWORD dwReadBytes = 0;

	fprintf(stdout, "Press any key to continue . . . ");
	fflush(stdout);

	hStdin = CreateFile(_T("CONIN$"), 
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE, 
		NULL, // No security attributes.
		OPEN_EXISTING, // Must use OPEN_EXISTING.
		0,    // Ignored for console.
		NULL  // Ignored for console.
		);

	//hStdin = GetStdHandle(STD_INPUT_HANDLE); 

	GetConsoleMode(hStdin, &fdwSaveOldMode);

	//fdwMode = fdwSaveOldMode&~(ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT);
	fdwMode = ENABLE_PROCESSED_INPUT;

	SetConsoleMode(hStdin, fdwMode);

	FlushConsoleInputBuffer(hStdin);

	memset(irInBuf, 0, 1*sizeof(INPUT_RECORD));
	//memset(buf, 0, 32);

	//if (WaitForSingleObject(hStdin, INFINITE) == WAIT_OBJECT_0)
	//	ReadConsoleInput(hStdin, irInBuf, 1, &cNumRead);
	//	//ReadFile(hStdin, buf, 32, &dwReadBytes, NULL);

	while (irInBuf->EventType != KEY_EVENT)
		ReadConsoleInput(hStdin, irInBuf, 1, &cNumRead);

	SetConsoleMode(hStdin, fdwSaveOldMode);
	
	//FlushConsoleInputBuffer(hStdin);

	CloseHandle(hStdin);

	fprintf(stdout, "\n");
	fflush(stdout);

	return (char)irInBuf[0].Event.KeyEvent.uChar.AsciiChar;
	//return buf[0];
#else 
	struct termios term, back;
	char buf[32];
	ssize_t nbbytes = 0;

	fprintf(stdout, "Press any key to continue . . . ");
	fflush(stdout);

	tcgetattr(STDIN_FILENO, &term); // Get the stdin terminal information.
	memcpy(&back, &term, sizeof(term)); // Save it.

	term.c_lflag &= ~(ICANON|ECHO); // Modify terminal options.
	term.c_cc[VTIME] = 0; // Infinite waiting time.
	term.c_cc[VMIN] = 1; // Minimum number of characters.

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term); // Modify stdin attributes.

	tcflush(STDIN_FILENO, TCIFLUSH); // Flush any previous input on stdin.

	memset(buf, 0, 32);

	nbbytes = read(STDIN_FILENO, buf, 32); // Wait for a character.

	if (nbbytes == 0) buf[0] = 0;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &back); // Restore previous attributes.

	fprintf(stdout, "\n");
	fflush(stdout);

	return buf[0];
#endif // _WIN32
}

/*
Wait for the user to press any key.

Return : The first character pressed.
*/
char GetUserInput(void)
{
#ifdef _WIN32
	HANDLE hStdin = INVALID_HANDLE_VALUE;
	DWORD fdwMode = 0, fdwSaveOldMode = 0;
	INPUT_RECORD irInBuf[1]; 
	DWORD cNumRead = 0;
	//char buf[32];
	//DWORD dwReadBytes = 0;

	hStdin = CreateFile(_T("CONIN$"), 
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE, 
		NULL, // No security attributes.
		OPEN_EXISTING, // Must use OPEN_EXISTING.
		0,    // Ignored for console.
		NULL  // Ignored for console.
		);

	//hStdin = GetStdHandle(STD_INPUT_HANDLE); 

	GetConsoleMode(hStdin, &fdwSaveOldMode);

	//fdwMode = fdwSaveOldMode&~(ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT);
	fdwMode = ENABLE_PROCESSED_INPUT;

	SetConsoleMode(hStdin, fdwMode);

	FlushConsoleInputBuffer(hStdin);

	memset(irInBuf, 0, 1*sizeof(INPUT_RECORD));
	//memset(buf, 0, 32);

	//if (WaitForSingleObject(hStdin, INFINITE) == WAIT_OBJECT_0)
	//	ReadConsoleInput(hStdin, irInBuf, 1, &cNumRead);
	//	//ReadFile(hStdin, buf, 32, &dwReadBytes, NULL);

	while (irInBuf->EventType != KEY_EVENT)
		ReadConsoleInput(hStdin, irInBuf, 1, &cNumRead);

	SetConsoleMode(hStdin, fdwSaveOldMode);

	//FlushConsoleInputBuffer(hStdin);

	CloseHandle(hStdin);

	return (char)irInBuf[0].Event.KeyEvent.uChar.AsciiChar;
	//return buf[0];
#else 
	struct termios term, back;
	char buf[32];
	ssize_t nbbytes = 0;

	tcgetattr(STDIN_FILENO, &term); // Get the stdin terminal information.
	memcpy(&back, &term, sizeof(term)); // Save it.

	term.c_lflag &= ~(ICANON|ECHO); // Modify terminal options.
	term.c_cc[VTIME] = 0; // Infinite waiting time.
	term.c_cc[VMIN] = 1; // Minimum number of characters.

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term); // Modify stdin attributes.

	tcflush(STDIN_FILENO, TCIFLUSH); // Flush any previous input on stdin.

	memset(buf, 0, 32);

	nbbytes = read(STDIN_FILENO, buf, 32); // Wait for a character.

	if (nbbytes == 0) buf[0] = 0;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &back); // Restore previous attributes.

	return buf[0];
#endif // _WIN32
}

/*
Wait for the user to press any key.
See also getch() or kbhit() functions (conio.h).

Return : Nothing.
*/
void WaitForUserInput(void)
{
#ifdef USE_PAUSE_CMD
#ifdef _WIN32
	system("pause");
#else
	system("read -n1 -r -s -p \"Press any key to continue . . . \" && (printf \"\\n\\n\")");
#endif // _WIN32
#else 
#ifdef _WIN32
	HANDLE hStdin = INVALID_HANDLE_VALUE;
	DWORD fdwMode = 0, fdwSaveOldMode = 0;
	INPUT_RECORD irInBuf[1]; 
	DWORD cNumRead = 0;
	//char buf[32];
	//DWORD dwReadBytes = 0;

	fprintf(stdout, "Press any key to continue . . . ");
	fflush(stdout);

	hStdin = CreateFile(_T("CONIN$"), 
		GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE, 
		NULL, // No security attributes.
		OPEN_EXISTING, // Must use OPEN_EXISTING.
		0,    // Ignored for console.
		NULL  // Ignored for console.
		);

	//hStdin = GetStdHandle(STD_INPUT_HANDLE); 

	GetConsoleMode(hStdin, &fdwSaveOldMode);

	//fdwMode = fdwSaveOldMode&~(ENABLE_LINE_INPUT|ENABLE_ECHO_INPUT);
	//fdwMode = fdwSaveOldMode&~(ENABLE_ECHO_INPUT|ENABLE_LINE_INPUT|ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT);
	fdwMode = ENABLE_PROCESSED_INPUT;

	SetConsoleMode(hStdin, fdwMode);

	FlushConsoleInputBuffer(hStdin);

	memset(irInBuf, 0, 1*sizeof(INPUT_RECORD));
	//memset(buf, 0, 32);

	//if (WaitForSingleObject(hStdin, INFINITE) == WAIT_OBJECT_0)
	//	ReadConsoleInput(hStdin, irInBuf, 1, &cNumRead);
	//	//ReadFile(hStdin, buf, 32, &dwReadBytes, NULL);

	while (irInBuf->EventType != KEY_EVENT)
		ReadConsoleInput(hStdin, irInBuf, 1, &cNumRead);

	SetConsoleMode(hStdin, fdwSaveOldMode);

	//FlushConsoleInputBuffer(hStdin);

	CloseHandle(hStdin);

	fprintf(stdout, "\n");
	fflush(stdout);
#else 
	struct termios term, back;
	char buf[32];
	ssize_t nbbytes = 0;

	fprintf(stdout, "Press any key to continue . . . ");
	fflush(stdout);

	tcgetattr(STDIN_FILENO, &term); // Get the stdin terminal information.
	memcpy(&back, &term, sizeof(term)); // Save it.

	term.c_lflag &= ~(ICANON|ECHO); // Modify terminal options.
	term.c_cc[VTIME] = 0; // Infinite waiting time.
	term.c_cc[VMIN] = 1; // Minimum number of characters.

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term); // Modify stdin attributes.

	tcflush(STDIN_FILENO, TCIFLUSH); // Flush any previous input on stdin.

	memset(buf, 0, 32);

	nbbytes = read(STDIN_FILENO, buf, 32); // Wait for a character.

	if (nbbytes == 0) buf[0] = 0;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &back); // Restore previous attributes.

	fprintf(stdout, "\n");
	fflush(stdout);
#endif // _WIN32
#endif //USE_PAUSE_CMD
}
#endif // !DISABLE_USER_INPUT_FUNCTIONS

/*
Allocate memory for an array of height*width and initialize it to 0.
An element of this array can then be accessed as follows :

allocated_array[i][j]

The memory allocated can then be freed with free_array2()

int height : (IN) Height of the array to allocate.
int width : (IN) Width of the array to allocate.
size_t SizeOfElements : (IN) Length in bytes of each element.

Return : A pointer to the allocated space.
*/
void* calloc_array2(int height, int width, size_t SizeOfElements)	
{
	int i = 0, ki = 0;
	void** p = NULL;

	p = (void**)calloc(height, sizeof(void*));
	if (p == NULL)	
	{
		return p;
	}

	for (i = 0; i < height; i++)	
	{
		p[i] = (void*)calloc(width, SizeOfElements);
		if (p[i] == NULL)	
		{
			for (ki = 0; ki < height; ki++)	
			{
				free(p[ki]); p[ki] = NULL;
			}
			free(p); p = NULL;
			return p;
		}
	}

	return p;
}

/*
Allocate memory for an array of height*width*depth and initialize it to 0.
An element of this array can then be accessed as follows :

allocated_array[i][j][k]

The memory allocated can then be freed with free_array3().

int height : (IN) Height of the array to allocate.
int width : (IN) Width of the array to allocate.
int depth : (IN) Depth of the array to allocate.
size_t SizeOfElements : (IN) Length in bytes of each element.

Return : A pointer to the allocated space.
*/
void* calloc_array3(int height, int width, int depth, size_t SizeOfElements)	
{
	int i = 0, j = 0, ki = 0, kj = 0;
	void*** p = NULL;

	p = (void***)calloc(height, sizeof(void**));
	if (p == NULL)	
	{
		return p;
	}

	for (i = 0; i < height; i++)	
	{
		p[i] = (void**)calloc(width, sizeof(void*));
		if (p[i] == NULL)	
		{
			for (ki = 0; ki < height; ki++)	
			{
				free(p[ki]); p[ki] = NULL;
			}
			free(p); p = NULL;
			return p;
		}
		for (j = 0; j < width; j++)	
		{
			p[i][j] = (void*)calloc(depth, SizeOfElements);
			if (p[i][j] == NULL)	
			{
				for (ki = 0; ki < height; ki++)	
				{
					for (kj = 0; kj < width; kj++)	
					{
						free(p[ki][kj]); p[ki][kj] = NULL;
					}
					free(p[ki]); p[ki] = NULL;
				}
				free(p); p = NULL;
				return p;
			}
		}
	}

	return p;
}

/*
Free memory allocated by calloc_array2().

void*** p : (INOUT) Array previously allocated.
int height : (IN) Height of the array.

Return : Nothing.
*/
void free_array2(void** p, int height)	
{
	int i = 0;

	if (p == NULL)	
	{
		return;
	}

	for (i = 0; i < height; i++)	
	{
		free(p[i]); p[i] = NULL;
	}
	free(p); p = NULL;
} 

/*
Free memory allocated by calloc_array3().

void*** p : (INOUT) array previously allocated.
int height : (IN) Height of the array.
int width : (IN) Width of the array.

Return : Nothing.
*/
void free_array3(void*** p, int height, int width)	
{
	int i = 0, j = 0;

	if (p == NULL)	
	{
		return;
	}

	for (i = 0; i < height; i++)	
	{
		for (j = 0; j < width; j++)	
		{
			free(p[i][j]); p[i][j] = NULL;
		}
		free(p[i]); p[i] = NULL;
	}
	free(p); p = NULL;
} 

// min and max might cause incompatibilities with GCC...
#ifndef _MSC_VER
#ifdef max
#undef max
#endif // max
#ifdef min
#undef min
#endif // min
#endif // !_MSC_VER
