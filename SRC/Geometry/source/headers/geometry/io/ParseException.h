/**********************************************************************
 * $Id: ParseException.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_IO_PARSEEXCEPTION_H
#define GEOS_IO_PARSEEXCEPTION_H

#include <Geometry/util/GEOSException.h>

namespace GEOMETRY {
namespace io {

/**
 * \class ParseException io.h geos.h
 * \brief Notifies a parsing error
 */
class ParseException : public util::GEOSException
{

public:

	ParseException();

	ParseException(const std::string& msg);

	ParseException(const std::string& msg, const std::string& var);

	ParseException(const std::string& msg, double num);

	~ParseException() throw() {};

private:
	static std::string stringify(double num);
};

} // namespace io
} // namespace GEOMETRY

#endif // #ifndef GEOS_IO_PARSEEXCEPTION_H

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/04/04 08:16:46  strk
 * Changed GEOSException hierarchy to be derived from std::runtime_exception.
 * Removed the GEOSException::toString redundant method (use ::what() instead)
 *
 * Revision 1.1  2006/03/20 18:18:14  strk
 * io.h header split
 *
 **********************************************************************/
