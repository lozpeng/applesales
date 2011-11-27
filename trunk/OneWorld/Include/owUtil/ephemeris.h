#ifndef _OWUTIL_EPHEMERIS_H
#define _OWUTIL_EPHEMERIS_H

#include <owUtil/export.h>

namespace owUtil
{
	class OWUTIL_EXPORT Ephemeris
	{
	public:
		static void GetSunPos(double mjd, double lat, double lon, double elev, double *sun_alt, double *sun_az);

		static void GetSunPos2(double mjd, double& X, double& Y, double& Z);

		static double GetMJD(int year, int month, int day, int hour, int min, int sec,double lon);
		
	};

}

#endif

