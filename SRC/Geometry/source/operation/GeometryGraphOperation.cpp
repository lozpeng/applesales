/**********************************************************************
 * $Id: GeometryGraphOperation.cpp 1820 2006-09-06 16:54:23Z mloskot $
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

#include <Geometry/operation/GeometryGraphOperation.h>
#include <Geometry/algorithm/LineIntersector.h>
#include <Geometry/geomgraph/GeometryGraph.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/PrecisionModel.h>

#include <cassert>

using namespace GEOMETRY::algorithm;
using namespace GEOMETRY::geomgraph;
using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace operation { // geos.operation

//LineIntersector* GeometryGraphOperation::li=new LineIntersector();

GeometryGraphOperation::GeometryGraphOperation(const Geometry *g0,
		const Geometry *g1)
	:
	arg(2)
{
	const PrecisionModel* pm0 = g0->getPrecisionModel();
	assert(pm0);

	const PrecisionModel* pm1 = g1->getPrecisionModel();
	assert(pm1);

	// use the most precise model for the result
	if (pm0->compareTo(pm1) >= 0)
		setComputationPrecision(pm0);
	else
		setComputationPrecision(pm1);

	arg[0]=new GeometryGraph(0, g0);
	arg[1]=new GeometryGraph(1, g1);
}


GeometryGraphOperation::GeometryGraphOperation(const Geometry *g0):
	arg(1)
{
	const PrecisionModel* pm0 = g0->getPrecisionModel();
	assert(pm0);

	setComputationPrecision(pm0);

	arg[0]=new GeometryGraph(0, g0);
}

const Geometry*
GeometryGraphOperation::getArgGeometry(unsigned int i) const
{
	assert(i<arg.size());
	return arg[i]->getGeometry();
}

/*protected*/
void
GeometryGraphOperation::setComputationPrecision(const PrecisionModel* pm)
{
	assert(pm);
	resultPrecisionModel=pm;
	li.setPrecisionModel(resultPrecisionModel);
}

GeometryGraphOperation::~GeometryGraphOperation()
{
	for(unsigned int i=0; i<arg.size(); ++i)
	{
		delete arg[i];
	}
}

} // namespace GEOMETRY.operation
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.23  2006/04/03 15:54:34  strk
 * - getArgGeometry() parameter type changed from 'int' to 'unsigned int'
 * - Added port informations
 * - minor assertions checking
 * - minor cleanups
 *
 * Revision 1.22  2006/03/21 21:42:54  strk
 * planargraph.h header split, planargraph:: classes renamed to match JTS symbols
 *
 * Revision 1.21  2006/03/02 14:34:43  strk
 * GeometryGraphOperation::li made a non-static member, and not more a pointer
 *
 * Revision 1.20  2006/02/27 09:05:33  strk
 * Doxygen comments, a few inlines and general cleanups
 *
 * Revision 1.19  2006/02/19 19:46:49  strk
 * Packages <-> namespaces mapping for most GEOS internal code (uncomplete, but working). Dir-level libs for index/ subdirs.
 *
 **********************************************************************/

