/**********************************************************************
 * $Id: TopologyValidationError.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_OP_TOPOLOGYVALIDATIONERROR_H
#define GEOS_OP_TOPOLOGYVALIDATIONERROR_H

#include <string>

#include <Geometry/geom/Coordinate.h> // for composition

// Forward declarations
// none required

namespace GEOMETRY {
namespace operation { // GEOMETRY::operation
namespace valid { // GEOMETRY::operation::valid

/** \brief
 * Contains information about the nature and location of a {@link Geometry}
 * validation error
 *
 */
class TopologyValidationError {
public:

	enum errorEnum {
		eError,
		eRepeatedPoint,
		eHoleOutsideShell,
		eNestedHoles,
		eDisconnectedInterior,
		eSelfIntersection,
		eRingSelfIntersection,
		eNestedShells,
		eDuplicatedRings,
		eTooFewPoints,
		eInvalidCoordinate,
		eRingNotClosed
	};

	TopologyValidationError(int newErrorType, const geom::Coordinate& newPt);
	TopologyValidationError(int newErrorType);
	geom::Coordinate& getCoordinate();
	std::string getMessage();
	int getErrorType();
	std::string toString();

private:
	// Used const char* to reduce dynamic allocations
	static const char* errMsg[];
	int errorType;
	geom::Coordinate pt;
};


} // namespace GEOMETRY.operation.valid
} // namespace GEOMETRY.operation
} // namespace GEOMETRY

#endif // GEOS_OP_TOPOLOGYVALIDATIONERROR_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/20 16:57:44  strk
 * spatialindex.h and opValid.h headers split
 *
 **********************************************************************/

