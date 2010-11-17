/**********************************************************************
 * $Id: PreparedPolygonPredicate.cpp 2194 2008-09-23 23:01:00Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#include <Geometry/geom/prep/PreparedPolygonPredicate.h>
#include <Geometry/geom/prep/PreparedPolygon.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/util/ComponentCoordinateExtracter.h>
#include <Geometry/geom/Location.h>
#include <Geometry/algorithm/locate/PointOnGeometryLocator.h>
#include <Geometry/algorithm/locate/SimplePointInAreaLocator.h>
// std
#include <cstddef>

namespace GEOMETRY {
namespace geom { // geos.geom
namespace prep { // geos.geom.prep
//
// private:
//

//
// protected:
//
bool 
PreparedPolygonPredicate::isAllTestComponentsInTargetArea(const geom::Geometry* testGeom)
{
    geom::Coordinate::ConstVect pts;
    geom::util::ComponentCoordinateExtracter::getCoordinates(*testGeom, pts);

    for (std::size_t i = 0, ni = pts.size(); i < ni; i++)
    {
        const geom::Coordinate* pt = pts[i];
        const int loc = prepPoly->getPointLocator()->locate(pt);
        if (geom::Location::EXTERIOR == loc)
        {
            return false;
        }
    }
    return true;
}

bool 
PreparedPolygonPredicate::isAllTestComponentsInTargetInterior(const geom::Geometry* testGeom)
{
    geom::Coordinate::ConstVect pts;
    geom::util::ComponentCoordinateExtracter::getCoordinates(*testGeom, pts);

    for (std::size_t i = 0, ni = pts.size(); i < ni; i++)
    {
        const geom::Coordinate * pt = pts[i];
        const int loc = prepPoly->getPointLocator()->locate(pt);
        if (geom::Location::INTERIOR != loc)
        {
            return false;
        }
    }
    return true;
}

bool 
PreparedPolygonPredicate::isAnyTestComponentInTargetArea(const geom::Geometry* testGeom)
{
    geom::Coordinate::ConstVect pts;
    geom::util::ComponentCoordinateExtracter::getCoordinates(*testGeom, pts);

    for (std::size_t i = 0, ni = pts.size(); i < ni; i++)
    {
        const Coordinate* pt = pts[i];
        const int loc = prepPoly->getPointLocator()->locate(pt);
        if (geom::Location::EXTERIOR != loc)
        {
            return true;
        }
    }
    return false;
}

bool 
PreparedPolygonPredicate::isAnyTestComponentInTargetInterior( const geom::Geometry * testGeom)
{
    geom::Coordinate::ConstVect pts;
    geom::util::ComponentCoordinateExtracter::getCoordinates(*testGeom, pts);

    for (std::size_t i = 0, ni = pts.size(); i < ni; i++)
    {
        const Coordinate * pt = pts[i];
        const int loc = prepPoly->getPointLocator()->locate(pt);
        if (geom::Location::INTERIOR == loc) 
        {
            return true;
        }
    }
    return false;
}

bool
PreparedPolygonPredicate::isAnyTargetComponentInTestArea(const geom::Geometry* testGeom,
                                                         const geom::Coordinate::ConstVect* targetRepPts)
{
    // TODO - mloskot: Replace manual delete with scoped_ptr
    algorithm::locate::PointOnGeometryLocator* piaLoc = 0;
    piaLoc = new algorithm::locate::SimplePointInAreaLocator(testGeom);

    for (std::size_t i = 0, ni = targetRepPts->size(); i < ni; i++)
    {
        const geom::Coordinate * pt = (*targetRepPts)[i];
        const int loc = piaLoc->locate(pt);
        if (geom::Location::EXTERIOR != loc)
        {
            delete piaLoc;
            return true;
        }
    }

    delete piaLoc;
    return false;
}

//
// public:
//

} // namespace GEOMETRY.geom.prep
} // namespace GEOMETRY.geom
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 *
 **********************************************************************/
