/**********************************************************************
 * $Id: ByteOrderDataInStream.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_IO_BYTEORDERDATAINSTREAM_H
#define GEOS_IO_BYTEORDERDATAINSTREAM_H

//#include <Geometry/platform.h>
//#include <Geometry/io/ParseException.h>
//#include <Geometry/io/ByteOrderValues.h>
#include <Geometry/inline.h>

#include <iosfwd> // ostream, istream (if we remove inlines)

namespace GEOMETRY {
namespace io {

/*
 * \class ByteOrderDataInStream io.h geos.h
 * 
 * Allows reading an stream of primitive datatypes from an underlying
 * istream, with the representation being in either common byte ordering.
 *
 */
class ByteOrderDataInStream {

public:

	ByteOrderDataInStream(std::istream *s=NULL);

	~ByteOrderDataInStream();

	/**
	 * Allows a single ByteOrderDataInStream to be reused
	 * on multiple istream.
	 */
	void setInStream(std::istream *s);

	void setOrder(int order);

	unsigned char readByte(); // throws ParseException

	int readInt(); // throws ParseException

	long readLong(); // throws ParseException

	double readDouble(); // throws ParseException

private:
	int byteOrder;
	std::istream *stream;

	// buffers to hold primitive datatypes
	unsigned char buf[8];

};

} // namespace io
} // namespace GEOMETRY

#ifdef GEOS_INLINE
#include <Geometry/io/ByteOrderDataInStream.inl>
#endif

#endif // #ifndef GEOS_IO_BYTEORDERDATAINSTREAM_H

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/03/28 11:26:13  strk
 * ByteOrderDataInStream inlines moved to .inl file, updated
 * implementation files includes.
 *
 * Revision 1.1  2006/03/20 18:18:14  strk
 * io.h header split
 *
 **********************************************************************/
