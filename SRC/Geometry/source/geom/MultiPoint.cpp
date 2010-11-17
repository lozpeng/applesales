/**********************************************************************
 * $Id: MultiPoint.cpp 1820 2006-09-06 16:54:23Z mloskot $
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

#include <Geometry/geom/MultiPoint.h>
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/operation/IsSimpleOp.h>
#include <Geometry/geom/Dimension.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/Point.h>
#include <vector>

using namespace std;

//using namespace GEOMETRY::operation;

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

/*protected*/
MultiPoint::MultiPoint(vector<Geometry *> *newPoints, const GeometryFactory *factory)
	:
	GeometryCollection(newPoints,factory)
{
}


MultiPoint::~MultiPoint(){}

Dimension::DimensionType
MultiPoint::getDimension() const {
	return Dimension::P; // point
}

int MultiPoint::getBoundaryDimension() const {
	return Dimension::False;
}

string MultiPoint::getGeometryType() const {
	return "MultiPoint";
}

Geometry* MultiPoint::getBoundary() const {
	return getFactory()->createGeometryCollection(NULL);
}

bool MultiPoint::isSimple() const {
	operation::IsSimpleOp iso;
	return iso.isSimple(this);
	
	//Geometry *in = toInternalGeometry(this);
	//bool issimple = iso.isSimple((MultiPoint *)in);
	//if ( (MultiPoint *)in != this ) delete(in);
	//return issimple;
}

//bool MultiPoint::isValid() const { return true; }

bool
MultiPoint::equalsExact(const Geometry *other, double tolerance) const
{
    if (!isEquivalentClass(other)) {
      return false;
    }
	return GeometryCollection::equalsExact(other,tolerance);
  }

const Coordinate* MultiPoint::getCoordinateN(int n) const {
	return ((*geometries)[n])->getCoordinate();
}
GeometryTypeId
MultiPoint::getGeometryTypeId() const {
	return GEOS_MULTIPOINT;
}

void MultiPoint::SetEmpty()
{
	GeometryCollection::iterator iter;
	for(iter=geometries->begin();iter!=geometries->end();iter++)
	{
		delete (*iter);
	}
	geometries->clear();
}


/******************************************************************************************************
*以下实现了ISnap接口
*
******************************************************************************************************/
bool MultiPoint::SnapVertex(Coordinate *pPoint,double tolerance,Coordinate *poutPt,double *searchDis,long *plpartIndex,long *plvertexIndex)
{
	long lnum = getNumPoints();
	if(lnum<=0)
	{
		return false;
	}
	Coordinate vertex,temppt;


	double mindis =1e38,distance;
    
	bool bfind =false;
    for(long i=0;i<lnum;i++)
	{
        vertex =(*geometries)[i]->GetPoint(0);
		distance =sqrt((vertex.x-pPoint->x)*(vertex.x-pPoint->x) +(vertex.y-pPoint->y)*(vertex.y-pPoint->y));

		if(distance>tolerance)
		{
			continue;
		}
        if(distance<mindis)
		{

			bfind =true;
            mindis = distance;
			temppt =vertex;
			
              
			*plpartIndex =i;
            *plvertexIndex =0;


		}
	}

	if(!bfind)
	{
		return false;
	}

	*poutPt=temppt;
	
    
	*searchDis =mindis;

    return true;
     

}

/******************************************************************************************************
*以下实现了IPointCollection接口
*
******************************************************************************************************/
long MultiPoint::PointCount() const
{
	return (long)getNumPoints();
}

void MultiPoint::AddPoint(GEOMETRY::geom::Coordinate &coord)
{
	//构造一个点对象，将它加入到图形列表中
	Point *p = this->getFactory()->createPoint(coord);

	geometries->push_back(static_cast<Geometry*>(p));
}

void MultiPoint::InsertPoint(int index, GEOMETRY::geom::Coordinate &newpoint)
{
	if(index<0 || index>=getNumPoints())
	{
		return;
	}
    
    Point *p = this->getFactory()->createPoint(newpoint);

	
	geometries->insert(geometries->begin()+index+1,static_cast<Geometry*>(p));


   
}

void MultiPoint::ReplacePoint(int index, GEOMETRY::geom::Coordinate &newpoint)
{
    if(index<0 || index>=getNumPoints())
	{
		return;
	}
	(*geometries)[index]->ReplacePoint(0,newpoint);
}

void MultiPoint::RemovePoint(int index)
{
    if(index<0 || index>=getNumPoints())
	{
		return;
	}
	geometries->erase(geometries->begin()+index);
}

Coordinate MultiPoint::GetPoint(int index)
{
     if(index<0 || index>=getNumPoints())
	{
		return Coordinate();
	}
 
	 return (*geometries)[index]->GetPoint(0);


}

/******************************************************************************************************
*以下实现了ITransForm接口
*
******************************************************************************************************/
void MultiPoint::Move(double dx, double dy)
{
	for(size_t i=0;i<geometries->size();i++)
	{
		(*geometries)[i]->Move(dx,dy);

	}

	this->geometryChangedAction();

}

void MultiPoint::Mirror(const Coordinate &p1,const Coordinate &p2)
{
   
    
    for(size_t i=0;i<geometries->size();i++)
	{
		(*geometries)[i]->Mirror(p1,p2);

	}
}

void MultiPoint::Scale(const GEOMETRY::geom::Coordinate &OriginPt, double dx, double dy)
{
	for(size_t i=0;i<geometries->size();i++)
	{
		(*geometries)[i]->Scale(OriginPt,dx,dy);

	}
}

void MultiPoint::Rotate(const Coordinate &OriginPt,double angle)
{
	for(size_t i=0;i<geometries->size();i++)
	{
		(*geometries)[i]->Rotate(OriginPt,angle);

	}
}


} // namespace GEOMETRY::geom
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.34  2006/05/04 15:49:39  strk
 * updated all Geometry::getDimension() methods to return Dimension::DimensionType (closes bug#93)
 *
 * Revision 1.33  2006/04/28 10:55:39  strk
 * Geometry constructors made protected, to ensure all constructions use GeometryFactory,
 * which has been made friend of all Geometry derivates. getNumPoints() changed to return
 * size_t.
 *
 * Revision 1.32  2006/03/22 16:58:34  strk
 * Removed (almost) all inclusions of geom.h.
 * Removed obsoleted .cpp files.
 * Fixed a bug in WKTReader not using the provided CoordinateSequence
 * implementation, optimized out some memory allocations.
 *
 * Revision 1.31  2006/03/09 16:46:47  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 * Revision 1.30  2006/03/03 10:46:21  strk
 * Removed 'using namespace' from headers, added missing headers in .cpp files, removed useless includes in headers (bug#46)
 *
 * Revision 1.29  2006/02/19 19:46:49  strk
 * Packages <-> namespaces mapping for most GEOS internal code (uncomplete, but working). Dir-level libs for index/ subdirs.
 *
 * Revision 1.28  2006/02/08 17:18:28  strk
 * - New WKTWriter::toLineString and ::toPoint convenience methods
 * - New IsValidOp::setSelfTouchingRingFormingHoleValid method
 * - New Envelope::centre()
 * - New Envelope::intersection(Envelope)
 * - New Envelope::expandBy(distance, [ydistance])
 * - New LineString::reverse()
 * - New MultiLineString::reverse()
 * - New Geometry::buffer(distance, quadSeg, endCapStyle)
 * - Obsoleted toInternalGeometry/fromInternalGeometry
 * - More const-correctness in Buffer "package"
 *
 * Revision 1.27  2006/01/31 19:07:33  strk
 * - Renamed DefaultCoordinateSequence to CoordinateArraySequence.
 * - Moved GetNumGeometries() and GetGeometryN() interfaces
 *   from GeometryCollection to Geometry class.
 * - Added getAt(int pos, Coordinate &to) funtion to CoordinateSequence class.
 * - Reworked automake scripts to produce a static lib for each subdir and
 *   then link all subsystem's libs togheter
 * - Moved C-API in it's own top-level dir capi/
 * - Moved source/bigtest and source/test to tests/bigtest and test/xmltester
 * - Fixed PointLocator handling of LinearRings
 * - Changed CoordinateArrayFilter to reduce memory copies
 * - Changed UniqueCoordinateArrayFilter to reduce memory copies
 * - Added CGAlgorithms::isPointInRing() version working with
 *   Coordinate::ConstVect type (faster!)
 * - Ported JTS-1.7 version of ConvexHull with big attention to
 *   memory usage optimizations.
 * - Improved XMLTester output and user interface
 * - GEOMETRY::geom::util namespace used for geom/util stuff
 * - Improved memory use in GEOMETRY::geom::util::PolygonExtractor
 * - New ShortCircuitedGeometryVisitor class
 * - New operation/predicate package
 *
 * Revision 1.26  2005/11/10 10:47:09  strk
 * Renamed MultiPoint::getCoordinate(int) to MultiPoint::getCoordinateN(int)
 * to avoid hiding of Geometry::getCoordinate().
 *
 * Revision 1.25  2004/09/13 12:39:14  strk
 * Made Point and MultiPoint subject to Validity tests.
 *
 * Revision 1.24  2004/09/12 03:51:27  pramsey
 * Casting changes to allow OS/X compilation.
 *
 * Revision 1.23  2004/07/22 08:45:50  strk
 * Documentation updates, memory leaks fixed.
 *
 * Revision 1.22  2004/07/08 19:34:49  strk
 * Mirrored JTS interface of CoordinateSequence, factory and
 * default implementations.
 * Added CoordinateArraySequenceFactory::instance() function.
 *
 * Revision 1.21  2004/07/06 17:58:22  strk
 * Removed deprecated Geometry constructors based on PrecisionModel and
 * SRID specification. Removed SimpleGeometryPrecisionReducer capability
 * of changing Geometry's factory. Reverted Geometry::factory member
 * to be a reference to external factory.
 *
 * Revision 1.20  2004/07/05 10:50:20  strk
 * deep-dopy construction taken out of Geometry and implemented only
 * in GeometryFactory.
 * Deep-copy geometry construction takes care of cleaning up copies
 * on exception.
 * Implemented clone() method for CoordinateSequence
 * Changed createMultiPoint(CoordinateSequence) signature to reflect
 * copy semantic (by-ref instead of by-pointer).
 * Cleaned up documentation.
 *
 * Revision 1.19  2004/07/02 13:28:26  strk
 * Fixed all #include lines to reflect headers layout change.
 * Added client application build tips in README.
 *
 * Revision 1.18  2004/07/01 14:12:44  strk
 *
 * Geometry constructors come now in two flavors:
 * 	- deep-copy args (pass-by-reference)
 * 	- take-ownership of args (pass-by-pointer)
 * Same functionality is available through GeometryFactory,
 * including buildGeometry().
 *
 * Revision 1.17  2004/06/28 21:11:43  strk
 * Moved getGeometryTypeId() definitions from geom.h to each geometry module.
 * Added holes argument check in Polygon.cpp.
 *
 * Revision 1.16  2004/05/07 09:05:13  strk
 * Some const correctness added. Fixed bug in GeometryFactory::createMultiPoint
 * to handle NULL CoordinateSequence.
 *
 * Revision 1.15  2004/04/20 08:52:01  strk
 * GeometryFactory and Geometry const correctness.
 * Memory leaks removed from SimpleGeometryPrecisionReducer
 * and GeometryFactory.
 *
 * Revision 1.14  2004/04/01 10:44:33  ybychkov
 * All "geom" classes from JTS 1.3 upgraded to JTS 1.4
 *
 * Revision 1.13  2004/03/31 07:50:37  ybychkov
 * "geom" partially upgraded to JTS 1.4
 *
 * Revision 1.12  2003/11/07 01:23:42  pramsey
 * Add standard CVS headers licence notices and copyrights to all cpp and h
 * files.
 *
 *
 **********************************************************************/

