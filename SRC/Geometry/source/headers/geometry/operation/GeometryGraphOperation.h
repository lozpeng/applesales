/**********************************************************************
 * $Id: GeometryGraphOperation.h 1820 2006-09-06 16:54:23Z mloskot $
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
 **********************************************************************
 *
 * Last port: operation/GeometryGraphOperation.java rev. 1.14 (JTS-1.7)
 *
 **********************************************************************/

#ifndef GEOS_OPERATION_GEOMETRYGRAPHOPERATION_H
#define GEOS_OPERATION_GEOMETRYGRAPHOPERATION_H

#include <Geometry/algorithm/LineIntersector.h> // for composition

#include <vector>

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class Geometry;
		class PrecisionModel;
	}
	namespace geomgraph {
		class GeometryGraph;
	}
}


namespace GEOMETRY {
namespace operation { // geos.operation

/// The base class for operations that require GeometryGraph
class GeometryGraphOperation {

public:

	GeometryGraphOperation(const geom::Geometry *g0,
			const geom::Geometry *g1);

	GeometryGraphOperation(const geom::Geometry *g0);

	virtual ~GeometryGraphOperation();

	const geom::Geometry* getArgGeometry(unsigned int i) const;

protected:

	algorithm::LineIntersector li;

	const geom::PrecisionModel* resultPrecisionModel;

	/** \brief
	 * The operation args into an array so they can be accessed by index
	 */
	std::vector<geomgraph::GeometryGraph*> arg; 

	void setComputationPrecision(const geom::PrecisionModel* pm);
};

} // namespace GEOMETRY.operation
} // namespace GEOMETRY

#endif

/**********************************************************************
 * $Log$
 * Revision 1.2  2006/04/03 15:54:33  strk
 * - getArgGeometry() parameter type changed from 'int' to 'unsigned int'
 * - Added port informations
 * - minor assertions checking
 * - minor cleanups
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/

