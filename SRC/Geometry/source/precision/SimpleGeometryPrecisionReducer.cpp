/**********************************************************************
 * $Id: SimpleGeometryPrecisionReducer.cpp 2530 2009-05-27 19:01:09Z pramsey $
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
 ***********************************************************************
 *
 * Last port: precision/SimpleGeometryPrecisionReducer.cpp rev. 1.10 (JTS-1.7)
 *
 **********************************************************************/

#include <Geometry/precision/SimpleGeometryPrecisionReducer.h>
#include <Geometry/geom/util/GeometryEditor.h>
#include <Geometry/geom/util/CoordinateOperation.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/CoordinateSequenceFactory.h>
#include <Geometry/geom/PrecisionModel.h>
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geom/LinearRing.h>

#include <vector>
#include <typeinfo>

using namespace std;
using namespace GEOMETRY::geom;
using namespace GEOMETRY::geom::util;

namespace GEOMETRY {
namespace precision { // geos.precision

class PrecisionReducerCoordinateOperation: public geom::util::CoordinateOperation {
using CoordinateOperation::edit;
private:
	SimpleGeometryPrecisionReducer *sgpr;
public:
	PrecisionReducerCoordinateOperation(SimpleGeometryPrecisionReducer *newSgpr);
	CoordinateSequence* edit(const CoordinateSequence *coordinates, const Geometry *geom);
};

PrecisionReducerCoordinateOperation::PrecisionReducerCoordinateOperation(SimpleGeometryPrecisionReducer *newSgpr)
{
	sgpr=newSgpr;
}

CoordinateSequence*
PrecisionReducerCoordinateOperation::edit(const CoordinateSequence *cs, const Geometry *geom)
{
	if (cs->getSize()==0) return NULL;

	unsigned int csSize=cs->getSize();

	vector<Coordinate> *vc = new vector<Coordinate>(csSize);

	// copy coordinates and reduce
	for (unsigned int i=0; i<csSize; ++i) {
		Coordinate coord=cs->getAt(i);
		sgpr->getPrecisionModel()->makePrecise(&coord);
		//reducedCoords->setAt(*coord,i);
		(*vc)[i] = coord;
	}

	CoordinateSequence *reducedCoords = geom->getFactory()->getCoordinateSequenceFactory()->create(vc);

	// remove repeated points, to simplify returned geometry as much as possible
	CoordinateSequence *noRepeatedCoords=CoordinateSequence::removeRepeatedPoints(reducedCoords);

	/**
	* Check to see if the removal of repeated points
	* collapsed the coordinate List to an invalid length
	* for the type of the parent geometry.
	* It is not necessary to check for Point collapses, since the coordinate list can
	* never collapse to less than one point.
	* If the length is invalid, return the full-length coordinate array
	* first computed, or null if collapses are being removed.
	* (This may create an invalid geometry - the client must handle this.)
	*/
	unsigned int minLength = 0;
	if (typeid(*geom)==typeid(LineString)) minLength = 2;
	if (typeid(*geom)==typeid(LinearRing)) minLength = 4;
	CoordinateSequence *collapsedCoords = reducedCoords;
	if (sgpr->getRemoveCollapsed())
	{
		delete reducedCoords; 
		reducedCoords=0;
		collapsedCoords=0;
	}
	// return null or orginal length coordinate array
	if (noRepeatedCoords->getSize()<minLength) {
		delete noRepeatedCoords;
		return collapsedCoords;
	}
	// ok to return shorter coordinate array
	delete reducedCoords;
	return noRepeatedCoords;
}


//---------------------------------------------------------------


SimpleGeometryPrecisionReducer::SimpleGeometryPrecisionReducer(
		const PrecisionModel *pm)
	:
	newPrecisionModel(pm),
	removeCollapsed(true)
{
	//removeCollapsed = true;
	//changePrecisionModel = false;
	//newPrecisionModel = pm;
}

/**
 * Sets whether the reduction will result in collapsed components
 * being removed completely, or simply being collapsed to an (invalid)
 * Geometry of the same type.
 *
 * @param removeCollapsed if <code>true</code> collapsed components will be removed
 */
void
SimpleGeometryPrecisionReducer::setRemoveCollapsedComponents(bool nRemoveCollapsed)
{
	removeCollapsed=nRemoveCollapsed;
}

const PrecisionModel*
SimpleGeometryPrecisionReducer::getPrecisionModel()
{
	return newPrecisionModel;
}

bool
SimpleGeometryPrecisionReducer::getRemoveCollapsed()
{
	return removeCollapsed;
}

Geometry*
SimpleGeometryPrecisionReducer::reduce(const Geometry *geom)
{
	GeometryEditor geomEdit;
	PrecisionReducerCoordinateOperation prco(this);
	Geometry *g=geomEdit.edit(geom, &prco);
	return g;
}

} // namespace GEOMETRY.precision
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.14  2006/04/03 13:56:54  strk
 * Made externally-owned PrecisionModel  const
 *
 * Revision 1.13  2006/03/23 09:17:19  strk
 * precision.h header split, minor optimizations
 *
 **********************************************************************/

