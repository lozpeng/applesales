/**********************************************************************
 * $Id: ByteOrderValues.h 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2005-2006 Refractions Research Inc.
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#ifndef GEOS_IO_BYTEORDERVALUES_H
#define GEOS_IO_BYTEORDERVALUES_H

#include <Geometry/platform.h>

namespace GEOMETRY {
namespace io {

/*
 * \class ByteOrderValues io.h geos.h
 * 
 * Methods to read and write primitive datatypes from/to byte
 * sequences, allowing the byte order to be specified
 * 
 * Similar to the standard Java <code>ByteBuffer</code> class.
 */
class ByteOrderValues {

public:

	static int ENDIAN_BIG;
	static int ENDIAN_LITTLE;

	static int getInt(const unsigned char *buf, int byteOrder);
	static void putInt(int intValue, unsigned char *buf, int byteOrder);

	static int64 getLong(const unsigned char *buf, int byteOrder);
	static void putLong(int64 longValue, unsigned char *buf, int byteOrder);

	static double getDouble(const unsigned char *buf, int byteOrder);
	static void putDouble(double doubleValue, unsigned char *buf, int byteOrder);

};

} // namespace io
} // namespace GEOMETRY

#endif // #ifndef GEOS_IO_BYTEORDERVALUES_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/20 18:18:14  strk
 * io.h header split
 *
 **********************************************************************/
