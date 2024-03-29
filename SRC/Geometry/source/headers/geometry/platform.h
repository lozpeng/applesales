/**********************************************************************
 * $Id: platform.h.vc 1982 2007-06-01 13:43:59Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2004 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 * Manually created platform.h for use with x86 Microsoft Visual C++
 */

#ifndef GEOS_PLATFORM_H
#define GEOS_PLATFORM_H

#ifndef _MSC_VER
#error "This platform.h intended for use with MS Visual C++"
#endif

#ifndef WIN32
#define WIN32
#endif

#include <float.h>

// We need M_PI, but on MSVC you need to define _USE_MATH_DEFINES before
// including math.h to get it.  If we are too late (math.h already included)
// we will define it manually.
#define _USE_MATH_DEFINES
#include <math.h>

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

//Defines NaN for intel platforms
#define DoubleNotANumber 1.7e-308

#define ISNAN(x)  _isnan(x)

//Don't forget to define infinities
#define DoubleInfinity 1.7e+308
#define DoubleNegInfinity -1.7e+308

#define FINITE(x) _finite(x)
#define finite(x) _finite(x)

typedef __int64 int64;

#define INT64_CONST_IS_I64 1

inline int getMachineByteOrder() {
        static int endian_check = 1; // don't modify !!
        return *((char *)&endian_check); // 0 == big_endian | xdr,
                                         // 1 == little_endian | ndr
}
#endif
