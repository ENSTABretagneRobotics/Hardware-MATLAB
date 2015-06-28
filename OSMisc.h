/***************************************************************************************************************:')

OSMisc.h

Miscellaneous things.

Fabrice Le Bars
mean() and var() from Guillaume Brosse and Antone Borissov
fgets2() by Luc Jaulin

Created : 2009-01-28

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

#ifndef OSMISC_H
#define OSMISC_H

#ifdef WINCE
#define DISABLE_USER_INPUT_FUNCTIONS
#define DISABLE_USER_INPUT_TIMEOUT_FUNCTIONS
#endif // WINCE

#include "OSCore.h"

#ifndef DISABLE_USER_INPUT_FUNCTIONS
#ifndef DISABLE_USER_INPUT_TIMEOUT_FUNCTIONS
#include "OSTime.h"
#endif // DISABLE_USER_INPUT_TIMEOUT_FUNCTIONS
#endif // DISABLE_USER_INPUT_FUNCTIONS

/*
Debug macros specific to OSMisc.
*/
#ifdef _DEBUG_MESSAGES_OSUTILS
#	define _DEBUG_MESSAGES_OSMISC
#endif // _DEBUG_MESSAGES_OSUTILS

#ifdef _DEBUG_WARNINGS_OSUTILS
#	define _DEBUG_WARNINGS_OSMISC
#endif // _DEBUG_WARNINGS_OSUTILS

#ifdef _DEBUG_ERRORS_OSUTILS
#	define _DEBUG_ERRORS_OSMISC
#endif // _DEBUG_ERRORS_OSUTILS

#ifdef _DEBUG_MESSAGES_OSMISC
#	define PRINT_DEBUG_MESSAGE_OSMISC(params) PRINT_DEBUG_MESSAGE(params)
#else
#	define PRINT_DEBUG_MESSAGE_OSMISC(params)
#endif // _DEBUG_MESSAGES_OSMISC

#ifdef _DEBUG_WARNINGS_OSMISC
#	define PRINT_DEBUG_WARNING_OSMISC(params) PRINT_DEBUG_WARNING(params)
#else
#	define PRINT_DEBUG_WARNING_OSMISC(params)
#endif // _DEBUG_WARNINGS_OSMISC

#ifdef _DEBUG_ERRORS_OSMISC
#	define PRINT_DEBUG_ERROR_OSMISC(params) PRINT_DEBUG_ERROR(params)
#else
#	define PRINT_DEBUG_ERROR_OSMISC(params)
#endif // _DEBUG_ERRORS_OSMISC

#ifndef DISABLE_USER_INPUT_FUNCTIONS
#ifdef _WIN32
#else 
#include <termios.h>
#endif // _WIN32
#endif // DISABLE_USER_INPUT_FUNCTIONS

//// To check...
//#ifdef __GNUC__
//#define _stricmp strcasecmp
//#define _strnicmp strncasecmp
//#define stricmp _stricmp
//#define strnicmp _strnicmp
//#endif // __GNUC__

#define MAX_BUF_LEN 256

#define MAX_TIMEOUT_PROMPTGETUSERINPUTTIMEOUT 25500

// Kelvin to Celsius degrees conversions.
#define KELVIN2CELSIUS(temperature) ((temperature)-273.15)
#define CELSIUS2KELVIN(temperature) ((temperature)+273.15)

// Earth radius in m.
#define EARTH_RADIUS 6371000

#define EAST_NORTH_UP_COORDINATE_SYSTEM 0
#define NORTH_EAST_DOWN_COORDINATE_SYSTEM 1
#define NORTH_WEST_UP_COORDINATE_SYSTEM 2

/*
Return an angle between -M_PI and M_PI.

double theta : (IN) Value.

Return : The converted angle.
*/
inline double fmod_2PI(double theta)
{
	return fmod(fmod(theta, 2*M_PI)+3*M_PI, 2*M_PI)-M_PI;
}

inline double fmod_360(double theta)
{
	return fmod(fmod(theta, 2*180.0)+3*180.0, 2*180.0)-180.0;
}

inline double quantification(double v, double step)
{
	//double q = 0;
	//q = q >= 0? floor(v/step+0.5): ceil(v/step-0.5);
	//q = q*step;
	return floor(v/step+0.5)*step;
}

#ifndef SQR_DEFINED
#define SQR_DEFINED
/*
Compute the square of a value.

double x : (IN) Value.

Return : The square of x.
*/
inline double sqr(double x)
{
	return x*x;
}
#endif // SQR_DEFINED

#ifndef SIGN_DEFINED
#define SIGN_DEFINED
/*
Return x/epsilon if x is between -epsilon and epsilon or -1 if x is negative, 
+1 if x is positive.

double x : (IN) Value.
double epsilon : (IN) Threshold.

Return : -1, +1 or x/epsilon.
*/
inline double sign(double x, double epsilon)
{ 
	if (x >= epsilon) 
		return 1;
	else if (x <= -epsilon) 
		return -1;
	else 
		return x/epsilon;
}
#endif // SIGN_DEFINED

#ifndef MEAN_DEFINED
#define MEAN_DEFINED
/*
Compute the mean of a table.

double* tab : (IN) Table.
int tab_length : (IN) Number of elements in the table.

Return : The mean.
*/
inline double mean(double* tab, int tab_length)	
{
	double m = 0;
	int i = 0;

	for (i = tab_length-1; i >= 0; i--)	
	{
		m += tab[i];
	}
	m = m/tab_length;

	return m;
}
#endif // MEAN_DEFINED

#ifndef VAR_DEFINED
#define VAR_DEFINED
/*
Compute the variance of a table.

double* tab : (IN) Table.
int tab_length : (IN) Number of elements in the table.

Return : The variance.
*/
inline double var(double* tab, int tab_length)	
{
	double m = 0;
	double v = 0;
	int i = 0;

	for (i = tab_length-1; i >= 0; i--)	
	{
		m += tab[i];
	}
	m = m/tab_length;
	for (i = tab_length-1; i >= 0; i--)	
	{
		v += sqr(tab[i]-m);
	}
	v = v/tab_length;

	return v;
}
#endif // VAR_DEFINED

/*
Compute the mean of a table using a table of numbers of occurences for each value.

double* tab_values : (IN) Table of the different values.
double* tab_numbers : (IN) Table of the number of occurences for each value.
int tab_length : (IN) Number of elements in the table of values (should be the same for 
the table of numbers).

Return : The mean.
*/
inline double meann(double* tab_values, double* tab_numbers, int tab_length)	
{
	double m = 0;
	double n = 0;
	int i = 0;

	for (i = tab_length-1; i >= 0; i--)	
	{
		n += tab_numbers[i];
		m += tab_numbers[i]*tab_values[i];
	}
	m = m/n;

	return m;
}

/*
Compute the variance of a table using a table of numbers of occurences for each value.

double* tab_values : (IN) Table of the different values.
double* tab_numbers : (IN) Table of the number of occurences for each value.
int tab_length : (IN) Number of elements in the table of values (should be the same for 
the table of numbers).

Return : The variance.
*/
inline double varn(double* tab_values, double* tab_numbers, int tab_length)	
{
	double m = 0;
	double v = 0;
	double n = 0;
	int i = 0;

	for (i = tab_length-1; i >= 0; i--)	
	{
		n += tab_numbers[i];
		m += tab_numbers[i]*tab_values[i];
	}
	m = m/n;
	for (i = tab_length-1; i >= 0; i--)	
	{
		v += tab_numbers[i]*sqr(tab_values[i]-m);
	}
	v = v/n;

	return v;
}

#ifndef FGETS2_DEFINED
#define FGETS2_DEFINED
/*
Return a line of a file using fgets(), skipping lines that begin with a '%'. 
Return NULL when a line begin with a '$' or when fgets() return NULL.

FILE* file : (IN) Pointer to a file.
char* line : (IN) Storage location for data.
int nbChar : (IN) Maximum number of characters to read.

Return : The line or NULL.
*/
inline char* fgets2(FILE* file, char* line, int nbChar)
{ 
	char* r = NULL;

	do   
	{
		r = fgets(line, nbChar, file);
	} 
	while ((line[0] == '%') && (r != NULL));

	if (line[0] == '$')
	{
		r = NULL;
	}

	return r;
}
#endif // FGETS2_DEFINED

/*
Return a line of a file using fgets(), skipping lines that begin with a '%' 
(Scilab-style comments), a '#' (Linux configuration files-style comments) or 
"//" (C-style comments). 
Return NULL when a line begin with a '$' or when fgets() return NULL, or if 
the maximum number of characters to read is less than 2.

FILE* file : (IN) Pointer to a file.
char* line : (IN) Storage location for data.
int nbChar : (IN) Maximum number of characters to read.

Return : The line or NULL.
*/
inline char* fgets3(FILE* file, char* line, int nbChar)
{ 
	char* r = NULL;

	if (nbChar < 2)
	{
		return NULL;
	}

	do   
	{
		r = fgets(line, nbChar, file);
	} 
	while ((
		(line[0] == '%')||
		(line[0] == '#')||
		((line[0] == '/')&&(line[1] == '/'))
		) && (r != NULL));

	if (line[0] == '$')
	{
		r = NULL;
	}

	return r;
}

inline int fload(char* szFilePath, unsigned char* buf, size_t elementsize, size_t count, size_t* pBytesLoaded)
{
	FILE* file = NULL;

	file = fopen(szFilePath, "rb");

	if (file == NULL)
	{
		return EXIT_FAILURE;
	}

	*pBytesLoaded = fread(buf, elementsize, count, file);
	if (*pBytesLoaded <= 0)
	{
		// Empty file, elementsize or count is 0, or there was an error.
		fclose(file);
		return EXIT_FAILURE;
	}

	if (feof(file) == 0)
	{
		// buf was not big enough or there was an error.
		fclose(file);
		return EXIT_FAILURE;
	}

	if (fclose(file) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

inline int fsave(char* szFilePath, unsigned char* buf, size_t elementsize, size_t count, size_t* pBytesSaved)
{
	FILE* file = NULL;

	file = fopen(szFilePath, "wb");

	if (file == NULL)
	{
		return EXIT_FAILURE;
	}

	*pBytesSaved = fwrite(buf, elementsize, count, file);
	if (*pBytesSaved != elementsize*count)
	{
		fclose(file);
		return EXIT_FAILURE;
	}

	if (fclose(file) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

inline int fcopyload(char* szFromFilePath, char* szToFilePath, unsigned char* buf, size_t elementsize, size_t count, size_t* pBytesCopied)
{
	FILE* fromfile = NULL;
	FILE* tofile = NULL;
	size_t BytesRead = 0;

	fromfile = fopen(szFromFilePath, "rb");
	if (fromfile == NULL)
	{
		return EXIT_FAILURE;
	}

	tofile = fopen(szToFilePath, "wb");
	if (tofile == NULL)
	{
		fclose(fromfile);
		return EXIT_FAILURE;
	}

	BytesRead = fread(buf, elementsize, count, fromfile);
	if (BytesRead <= 0)
	{
		// Empty file, elementsize or count is 0, or there was an error.
		fclose(tofile);
		fclose(fromfile);
		return EXIT_FAILURE;
	}

	if (feof(fromfile) == 0)
	{
		// buf was not big enough or there was an error.
		fclose(tofile);
		fclose(fromfile);
		return EXIT_FAILURE;
	}

	*pBytesCopied = fwrite(buf, elementsize, BytesRead, tofile);
	if (*pBytesCopied != BytesRead)
	{
		fclose(tofile);
		fclose(fromfile);
		return EXIT_FAILURE;
	}

	if (fclose(tofile) != EXIT_SUCCESS)
	{
		fclose(fromfile);
		return EXIT_FAILURE;
	}

	if (fclose(fromfile) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

inline int fcopy(char* szFromFilePath, char* szToFilePath, size_t* pBytesCopied)
{
	FILE* fromfile = NULL;
	FILE* tofile = NULL;
	unsigned char buf[1024];
	size_t BytesRead = 0, BytesWritten = 0;

	fromfile = fopen(szFromFilePath, "rb");
	if (fromfile == NULL)
	{
		return EXIT_FAILURE;
	}

	tofile = fopen(szToFilePath, "wb");
	if (tofile == NULL)
	{
		fclose(fromfile);
		return EXIT_FAILURE;
	}

	*pBytesCopied = 0;
	do
	{
		BytesRead = fread(buf, sizeof(buf), 1, fromfile);
		if (BytesRead <= 0)
		{
			// Empty file, elementsize or count is 0, or there was an error.
			fclose(tofile);
			fclose(fromfile);
			return EXIT_FAILURE;
		}

		BytesWritten = fwrite(buf, BytesRead, 1, tofile);
		if (BytesWritten != BytesRead)
		{
			fclose(tofile);
			fclose(fromfile);
			return EXIT_FAILURE;
		}

		*pBytesCopied += BytesWritten;
	}
	while (feof(fromfile) == 0);

	if (fclose(tofile) != EXIT_SUCCESS)
	{
		fclose(fromfile);
		return EXIT_FAILURE;
	}

	if (fclose(fromfile) != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

inline double sensor_err(double bias_err, double max_rand_err)
{
	return bias_err+max_rand_err*(2.0*rand()/(double)RAND_MAX-1.0);
}

// Return theta_star (see http://www.ensta-bretagne.fr/jaulin/paper_jaulin_irsc12.pdf).
inline double LineFollowing(double phi, double e, double gamma_infinite, double r)
{
	//printf("theta_star = %f deg\n", fmod_2PI(phi-(2.0*gamma_infinite/M_PI)*atan(e/r))*180.0/M_PI);
	//printf("theta_star = %f deg\n", fmod_2PI(phi-(2.0*gamma_infinite/M_PI)*atan2(e,r))*180.0/M_PI);

	//return phi-(2.0*gamma_infinite/M_PI)*atan(e/r);
	return phi-(2.0*gamma_infinite/M_PI)*atan2(e,r);
}

/*
Swap the bits of a given number coded on 8 bits.

uint8 x : (IN) The number to swap.

Return : The number swapped.
*/
inline uint8 SwapBits(uint8 x)
{
	return  
		((x & 0x01) << 7) | ((x & 0x02) << 5) | ((x & 0x04) << 3) | ((x & 0x08) << 1) | 
		((x & 0x10) >> 1) | ((x & 0x20) >> 3) | ((x & 0x40) >> 5) | ((x & 0x80) >> 7);
}

inline void SwapBytes(unsigned char* buf, int nb)
{
	int i = 0;
	int sym_i = 0;
	unsigned char byte = 0;

	for (i = nb/2-1; i >= 0; i--)
	{
		sym_i = nb-1-i;
		byte = buf[sym_i];
		buf[sym_i] = buf[i];
		buf[i] = byte;
	}
}

/*
Calculation of CRC-16 checksum over an amount of bytes in the serial buffer.
The calculation is done without the 2 bytes from CRC-16 (receive-mode).

uint8* SC_Buffer : (IN) Buffer from the serial interface.
int SC_Amount : (IN) Amount of bytes which are received or should be transmitted (without CRC-16).
uint8* crc_h : (INOUT) Valid pointer that should receive the MSB of the CRC-16.
uint8* crc_l: (INOUT) Valid pointer that should receive the LSB of the CRC-16.

Return : Nothing.
*/
inline void CalcCRC16(uint8* SC_Buffer, int SC_Amount, uint8* crc_h, uint8* crc_l)
{
	// Locals.
	unsigned int Crc;
	unsigned char n, m, x;

	// Initialization.
	Crc = 0xFFFF;
	m = (unsigned char)SC_Amount;
	x = 0;

	// Loop over all bits.
	while (m > 0)
	{
		Crc ^= SC_Buffer[x];
		for (n = 0; n < 8 ; n++)
		{
			if (Crc &1)
			{
				Crc >>= 1;
				Crc ^= 0xA001;
			}
			else
				Crc >>= 1;
		}
		m--;
		x++;
	}

	// Result.
	*crc_h = (uint8)((Crc>>8)&0xFF);
	*crc_l = (uint8)(Crc&0xFF);
}

/*
Convert GPS data to coordinates in a reference coordinate system.

double lat0 : (IN) GPS latitude of the reference coordinate system origin (in decimal deg).
double long0 : (IN) GPS longitude of the reference coordinate system origin (in decimal deg).
double alt0 : (IN) GPS altitude of the reference coordinate system origin (in m).
double latitude : (IN) GPS latitude (in decimal deg).
double longitude : (IN) GPS longitude (in decimal deg).
double altitude : (IN) GPS altitude (in m).
double* pX : (INOUT) Valid pointer that will receive the x coordinate in the reference coordinate 
system (in m).
double* pY : (INOUT) Valid pointer that will receive the y coordinate in the reference coordinate 
system (in m).
double* pZ : (INOUT) Valid pointer that will receive the z coordinate in the reference coordinate 
system (in m).
int cstype : (IN) Either EAST_NORTH_UP_COORDINATE_SYSTEM, NORTH_EAST_DOWN_COORDINATE_SYSTEM 
or NORTH_WEST_UP_COORDINATE_SYSTEM.

Return : Nothing.
*/
inline void GPS2RefCoordSystem(double lat0, double long0, double alt0,
							   double latitude, double longitude, double altitude,
							   double* pX, double* pY, double* pZ,
							   int cstype)
{
	switch (cstype)
	{
	case NORTH_EAST_DOWN_COORDINATE_SYSTEM:
		*pX = (M_PI/180.0)*EARTH_RADIUS*(latitude-lat0);
		*pY = (M_PI/180.0)*EARTH_RADIUS*(longitude-long0)*cos((M_PI/180.0)*latitude);
		*pZ = alt0-altitude;
		break;
	case NORTH_WEST_UP_COORDINATE_SYSTEM:
		*pX = (M_PI/180.0)*EARTH_RADIUS*(latitude-lat0);
		*pY = (M_PI/180.0)*EARTH_RADIUS*(long0-longitude)*cos((M_PI/180.0)*latitude);
		*pZ = altitude-alt0;
		break;
	default: // EAST_NORTH_UP_COORDINATE_SYSTEM
		*pX = (M_PI/180.0)*EARTH_RADIUS*(longitude-long0)*cos((M_PI/180.0)*latitude);
		*pY = (M_PI/180.0)*EARTH_RADIUS*(latitude-lat0);
		*pZ = altitude-alt0;
		break;
	}
}

/*
Convert coordinates in a reference coordinate system to GPS data.

double lat0 : (IN) GPS latitude of the reference coordinate system origin (in decimal deg).
double long0 : (IN) GPS longitude of the reference coordinate system origin (in decimal deg).
double alt0 : (IN) GPS altitude of the reference coordinate system origin (in m).
double x : (IN) x coordinate in the reference coordinate system (in m).
double y : (IN) y coordinate in the reference coordinate system (in m).
double z : (IN) z coordinate in the reference coordinate system (in m).
double* pLatitude : (INOUT) Valid pointer that will receive the GPS latitude (in decimal deg).
double* pLongitude : (INOUT) Valid pointer that will receive the GPS longitude (in decimal deg).
double* pAltitude : (INOUT) Valid pointer that will receive the GPS altitude (in m).
int cstype : (IN) Either EAST_NORTH_UP_COORDINATE_SYSTEM, NORTH_EAST_DOWN_COORDINATE_SYSTEM 
or NORTH_WEST_UP_COORDINATE_SYSTEM.

Return : Nothing.
*/
inline void RefCoordSystem2GPS(double lat0, double long0, double alt0, 
							   double x, double y, double z,
							   double* pLatitude, double* pLongitude, double* pAltitude,
							   int cstype)
{
	switch (cstype)
	{
	case NORTH_EAST_DOWN_COORDINATE_SYSTEM:
		*pLatitude = (x/(double)EARTH_RADIUS)*(180.0/M_PI)+lat0;
		if ((fabs(*pLatitude-90.0) < DBL_EPSILON)||(fabs(*pLatitude+90.0) < DBL_EPSILON))
		{
			*pLongitude = 0;
		}
		else
		{
			*pLongitude = (y/(double)EARTH_RADIUS)*(180.0/M_PI)/cos((M_PI/180.0)*(*pLatitude))+long0;
		}
		*pAltitude = alt0-z;
		break;
	case NORTH_WEST_UP_COORDINATE_SYSTEM:
		*pLatitude = (x/(double)EARTH_RADIUS)*(180.0/M_PI)+lat0;
		if ((fabs(*pLatitude-90.0) < DBL_EPSILON)||(fabs(*pLatitude+90.0) < DBL_EPSILON))
		{
			*pLongitude = 0;
		}
		else
		{
			*pLongitude = long0-(y/(double)EARTH_RADIUS)*(180.0/M_PI)/cos((M_PI/180.0)*(*pLatitude));
		}
		*pAltitude = z+alt0;
		break;
	default: // EAST_NORTH_UP_COORDINATE_SYSTEM
		*pLatitude = (y/(double)EARTH_RADIUS)*(180.0/M_PI)+lat0;
		if ((fabs(*pLatitude-90.0) < DBL_EPSILON)||(fabs(*pLatitude+90.0) < DBL_EPSILON))
		{
			*pLongitude = 0;
		}
		else
		{
			*pLongitude = (x/(double)EARTH_RADIUS)*(180.0/M_PI)/cos((M_PI/180.0)*(*pLatitude))+long0;
		}
		*pAltitude = z+alt0;
		break;
	}
}

// angle_env : Angle of the x axis of the environment coordinate system 
// w.r.t. an East - North - Up coordinate system, should be set to 0 if no 
// specific environment (i.e. an East - North - Up coordinate system) 
// is used as reference (in rad).
inline void GPS2EnvCoordSystem(double lat_env, double long_env, double alt_env, double angle_env,
							   double latitude, double longitude, double altitude,
							   double* pX, double* pY, double* pZ)
{
	double x_enu = 0, y_enu = 0, z_enu = 0;

	GPS2RefCoordSystem(lat_env, long_env, alt_env, latitude, longitude, altitude, &x_enu, &y_enu, &z_enu, EAST_NORTH_UP_COORDINATE_SYSTEM);

	// Conversion from East - North - Up to environment coordinate system.
	*pX = x_enu*cos(-angle_env)-y_enu*sin(-angle_env);
	*pY = x_enu*sin(-angle_env)+y_enu*cos(-angle_env);
	*pZ = z_enu;
}

inline void EnvCoordSystem2GPS(double lat_env, double long_env, double alt_env, double angle_env, 
							   double x, double y, double z,
							   double* pLatitude, double* pLongitude, double* pAltitude)
{
	double x_enu = 0, y_enu = 0, z_enu = 0;

	// Conversion from environment to East - North - Up coordinate system.
	x_enu = x*cos(angle_env)-y*sin(angle_env);
	y_enu = x*sin(angle_env)+y*cos(angle_env);
	z_enu = z;

	RefCoordSystem2GPS(lat_env, long_env, alt_env, x_enu, y_enu, z_enu, pLatitude, pLongitude, pAltitude, EAST_NORTH_UP_COORDINATE_SYSTEM);
}

// The angles conversions are most of the time used separately...
inline void Robot2EnvCoordSystem(double x_robot, double y_robot, double z_robot, double theta_robot,
								 double x, double y, double z, //double theta,
								 double* pX, double* pY, double* pZ//, double* pTheta
								 )
{
	*pX = x*cos(theta_robot)-y*sin(theta_robot)+x_robot;
	*pY = x*sin(theta_robot)+y*cos(theta_robot)+y_robot;
	*pZ = z+z_robot;
	//*pTheta = theta+theta_robot;
}

inline void EnvCoordSystem2Robot(double x_robot, double y_robot, double z_robot, double theta_robot, 
								 double x, double y, double z, //double theta,
								 double* pX, double* pY, double* pZ//, double* pTheta
								 )
{
	*pX = (x-x_robot)*cos(-theta_robot)-(y-y_robot)*sin(-theta_robot);
	*pY = (x-x_robot)*sin(-theta_robot)+(y-y_robot)*cos(-theta_robot);
	*pZ = z-z_robot;
	//*pTheta = theta-theta_robot;
}

inline void DecDeg2DegDecMin(double decdeg, int* pDeg, double* pDecMin)
{
	*pDeg = (int)decdeg;
	*pDecMin = fabs((decdeg-*pDeg)*60.0);
}

inline void DecDeg2DegMinDecSec(double decdeg, int* pDeg, int* pMin, double* pDecSec)
{
	double decmin;
	DecDeg2DegDecMin(decdeg, pDeg, &decmin);
	*pMin = (int)decmin;
	*pDecSec = (decmin-*pMin)*60.0;
}

inline void DegDecMin2DecDeg(int deg, double decmin, double* pDecDeg)
{
	*pDecDeg = (deg >= 0)?deg+fabs(decmin/60.0):deg-fabs(decmin/60.0);
}

inline void DegMinDecSec2DecDeg(int deg, int min, double decsec, double* pDecDeg)
{
	double decmin = abs(min)+fabs(decsec)/60.0;
	DegDecMin2DecDeg(deg, decmin, pDecDeg);
}

inline void GPSLatitudeDecDeg2DegDecMin(double decdeg, int* pDeg, double* pDecMin, char* pNorthOrSouth)
{
	DecDeg2DegDecMin(decdeg, pDeg, pDecMin);
	*pDeg = abs(*pDeg);
	*pNorthOrSouth = (decdeg >= 0)?'N':'S';
}

inline void GPSLongitudeDecDeg2DegDecMin(double decdeg, int* pDeg, double* pDecMin, char* pEastOrWest)
{
	DecDeg2DegDecMin(decdeg, pDeg, pDecMin);
	*pDeg = abs(*pDeg);
	*pEastOrWest = (decdeg >= 0)?'E':'W';
}

inline void GPSLatitudeDegDecMin2DecDeg(int deg, double decmin, char NorthOrSouth, double* pDecDeg)
{
	DegDecMin2DecDeg(abs(deg), fabs(decmin), pDecDeg);
	*pDecDeg = (NorthOrSouth == 'N')?*pDecDeg:-*pDecDeg;
}

inline void GPSLongitudeDegDecMin2DecDeg(int deg, double decmin, char EastOrWest, double* pDecDeg)
{
	DegDecMin2DecDeg(abs(deg), fabs(decmin), pDecDeg);
	*pDecDeg = (EastOrWest == 'E')?*pDecDeg:-*pDecDeg;
}

inline void GPSLatitudeDecDeg2DegMinDecSec(double val, int* pDeg, int* pMin, double* pDecSec, char* pNorthOrSouth)
{
	DecDeg2DegMinDecSec(val, pDeg, pMin, pDecSec);
	*pDeg = abs(*pDeg);
	*pNorthOrSouth = (val >= 0)?'N':'S';
}

inline void GPSLongitudeDecDeg2DegMinDecSec(double val, int* pDeg, int* pMin, double* pDecSec, char* pEastOrWest)
{
	DecDeg2DegMinDecSec(val, pDeg, pMin, pDecSec);
	*pDeg = abs(*pDeg);
	*pEastOrWest = (val >= 0)?'E':'W';
}

inline void GPSLatitudeDegMinDecSec2DecDeg(int deg, int min, double decsec, char NorthOrSouth, double* pDecDeg)
{
	DegMinDecSec2DecDeg(abs(deg), abs(min), fabs(decsec), pDecDeg);
	*pDecDeg = (NorthOrSouth == 'N')?*pDecDeg:-*pDecDeg;
}

inline void GPSLongitudeDegMinDecSec2DecDeg(int deg, int min, double decsec, char EastOrWest, double* pDecDeg)
{
	DegMinDecSec2DecDeg(abs(deg), abs(min), fabs(decsec), pDecDeg);
	*pDecDeg = (EastOrWest == 'E')?*pDecDeg:-*pDecDeg;
}

/*
Used by HSL2RGB().

double v1 : (IN) 
double v2 : (IN) 
double vH : (IN) 

Return : A value used by HSL2RGB().
*/
inline double Hue_2_RGB(double v1, double v2, double vH)
{
	if (vH < 0) vH += 1;
	if (vH > 1) vH -= 1;
	if (6.0*vH < 1) return (v1+(v2-v1)*6.0*vH);
	if (2.0*vH < 1) return (v2);
	if (3.0*vH < 2) return (v1+(v2-v1)*((2.0/3.0)-vH)*6.0);

	return v1;
}

inline void Gray2RGB_Matlab(UCHAR val, UCHAR* pR, UCHAR* pG, UCHAR* pB)
{
	double h = (2.0/3.0)-(2.0/3.0)*val/255.0;

	*pR = (UCHAR)(255.0*Hue_2_RGB(0,1,h+1.0/3.0));
	*pG = (UCHAR)(255.0*Hue_2_RGB(0,1,h));
	*pB = (UCHAR)(255.0*Hue_2_RGB(0,1,h-1.0/3.0));
}

inline void Gray2RGB_Seanet(UCHAR val, UCHAR* pR, UCHAR* pG, UCHAR* pB)
{
	double h = 1, h1 = 0, v1 = 0, v2 = 1;

	h1 = val/255.0;
	//h = (5.0/6.0)-(2.0/3.0)*h1;
	if (h1 < 1.0/6.0) {h = (5.0/6.0); v2 = 6.0*h1;}
	else if (h1 > 5.0/6.0) {h = (5.0/6.0)-(2.0/3.0); v1 = 6.0*(h1-5.0/6.0);}
	else h = (5.0/6.0)-(h1-1.0/6.0);

	*pR = (UCHAR)(255.0*Hue_2_RGB(v1,v2,h+1.0/3.0));
	*pG = (UCHAR)(255.0*Hue_2_RGB(v1,v2,h));
	*pB = (UCHAR)(255.0*Hue_2_RGB(v1,v2,h-1.0/3.0));
}

/*
Example : k in [0..4], m = 5
255 0 0 - 0
128 128 0 - 1
0 255 0 - 2
0 128 128 - 3
0  0 255 - 4

255-255*k/m, 255*(1-abs(2*(k/m-1/2))), 255*k/m

Be careful to rounding!

(int)(255-255*(int)k/((int)m-1)), 
(int)(255-abs((255*2*(int)k-255*((int)m-1))/((int)m-1))), 
(int)(255*(int)k/((int)m-1))
*/
inline void Gray2RGB_Quick(UCHAR val, UCHAR* pR, UCHAR* pG, UCHAR* pB)
{
	int r = 255-(int)val;
	int g = 255-abs(2*(int)val-255);
	int b = val;

	*pR = (UCHAR)r;
	*pG = (UCHAR)g;
	*pB = (UCHAR)b;
}

/*
Convert from HSL to RGB.

double h : (IN) 
double s : (IN) 
double l : (IN) 
UCHAR* r : (OUT) 
UCHAR* g : (OUT) 
UCHAR* b : (OUT) 

Return : Nothing.
*/
inline void HSL2RGB(double h, double s, double l, UCHAR* r, UCHAR* g, UCHAR* b)
{
	double var_1 = 0;
	double var_2 = 0;

	if (s == 0)
	{
		*r = (UCHAR)(l*255.0);
		*g = (UCHAR)(l*255.0);
		*b = (UCHAR)(l*255.0);
	}
	else
	{
		if (l < 0.5) var_2 = l*(1+s);
		else var_2 = (l+s)-(s*l);

		var_1 = 2*l-var_2;

		*r = (UCHAR)(255.0*Hue_2_RGB(var_1,var_2,h+1.0/3.0));
		*g = (UCHAR)(255.0*Hue_2_RGB(var_1,var_2,h));
		*b = (UCHAR)(255.0*Hue_2_RGB(var_1,var_2,h-1.0/3.0));
	}
}

/*
Convert from HSL to RGB.

double hue : (IN) Hue between 0..240.
double saturation : (IN) Saturation between 0..240.
double luminance : (IN) Luminance between 0..240.
double* pR : (OUT) Pointer to the red between 0..255.
double* pG : (OUT) Pointer to the green between 0..255.
double* pB : (OUT) Pointer to the blue between 0..255.

Return : Nothing.
*/
inline void HSL2RGB_MSPaint(double hue, double saturation, double luminance, double* pR, double* pG, double* pB)
{
	double var_1 = 0;
	double var_2 = 0;

	// Microsoft Paint limits for H,S,L are 0..240.
	hue = hue/240.0;
	saturation = saturation/240.0;
	luminance = luminance/240.0;

	if (saturation == 0)
	{
		*pR = luminance*255.0;
		*pG = luminance*255.0;
		*pB = luminance*255.0;
	}
	else
	{
		if (luminance < 0.5) var_2 = luminance*(1+saturation); else var_2 = (luminance+saturation)-(saturation*luminance);
		var_1 = 2*luminance-var_2;

		*pR = Hue_2_RGB(var_1, var_2, hue+1.0/3.0)*255.0;
		*pG = Hue_2_RGB(var_1, var_2, hue)*255.0;
		*pB = Hue_2_RGB(var_1, var_2, hue-1.0/3.0)*255.0;
	}
}

/*
Convert from RGB to HSL.

double red : (IN) Red between 0..255.
double green : (IN) Green between 0..255.
double blue : (IN) Blue between 0..255.
double* pH : (OUT) Pointer to the hue between 0..240.
double* pS : (OUT) Pointer to the saturation between 0..240.
double* pL : (OUT) Pointer to the luminance between 0..240.

Return : Nothing.
*/
inline void RGB2HSL_MSPaint(double red, double green, double blue, double* pH, double* pS, double* pL)
{
	double minval = min(red, min(green, blue));
	double maxval = max(red, max(green, blue));
	double mdiff = maxval-minval;
	double msum = maxval+minval;
	double hue = 0.0;
	double saturation = 0.0;
	double luminance = msum/510.0;

	if (maxval != minval)
	{
		double rnorm = (maxval-red)/mdiff;
		double gnorm = (maxval-green)/mdiff;
		double bnorm = (maxval-blue)/mdiff;
		saturation = (luminance <= 0.5)?(mdiff/msum):(mdiff/(510.0-msum));
		if (red == maxval)
			hue = 60.0*(6.0+bnorm-gnorm);
		if (green == maxval)
			hue = 60.0*(2.0+rnorm-bnorm);
		if (blue == maxval)
			hue = 60.0*(4.0+gnorm-rnorm);
		if (hue > 360.0)
			hue -= 360.0;
	}

	// Microsoft Paint limits for H,S,L are 0..240.

	*pH = hue*240.0/360.0; 
	*pS = saturation*240.0; 
	*pL = luminance*240.0;
}

/*
Wait for the user to press the ENTER key.

Return : Nothing.
*/
inline void WaitForENTER(void)
{
	fprintf(stdout, "Press ENTER to continue . . . ");
	(void)getchar();
}

#ifndef WINCE
/*
Prompt for the user to press any key until a specified timeout.

UINT timeout : (IN) Time to wait to get at least 1 char in ms (with a 
precision of tenths of s, max is MAX_TIMEOUT_PROMPTGETUSERINPUTTIMEOUT).

Return : The first character pressed.
*/
EXTERN_C char PromptForUserInputTimeout(UINT timeout);

/*
Wait for the user to press any key until a specified timeout.

UINT timeout : (IN) Time to wait to get at least 1 char in ms (with a 
precision of tenths of s, max is MAX_TIMEOUT_PROMPTGETUSERINPUTTIMEOUT).

Return : The first character pressed.
*/
EXTERN_C char GetUserInputTimeout(UINT timeout);

/*
Prompt for the user to press any key.

Return : The first character pressed.
*/
EXTERN_C char PromptForUserInput(void);

/*
Wait for the user to press any key.

Return : The first character pressed.
*/
EXTERN_C char GetUserInput(void);

/*
Wait for the user to press any key.

Return : Nothing.
*/
EXTERN_C void WaitForUserInput(void);
#endif // WINCE

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
EXTERN_C void* calloc_array2(int height, int width, size_t SizeOfElements);

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
EXTERN_C void* calloc_array3(int height, int width, int depth, size_t SizeOfElements);

/*
Free memory allocated by calloc_array2().

void*** p : (INOUT) Array previously allocated.
int height : (IN) Height of the array.

Return : Nothing.
*/
EXTERN_C void free_array2(void** p, int height); 

/*
Free memory allocated by calloc_array3().

void*** p : (INOUT) array previously allocated.
int height : (IN) Height of the array.
int width : (IN) Width of the array.

Return : Nothing.
*/
EXTERN_C void free_array3(void*** p, int height, int width);

inline void useless_function(int useless_param)
{
	UNREFERENCED_PARAMETER(useless_param);
	printf("This function is not so useless!\n");
}

#endif // OSMISC_H
