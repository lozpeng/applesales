/**********************************************************************
 * $Id: GeometryCombiner.cpp 2253 2009-01-23 23:58:18Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#include <Geometry/geom/util/GeometryCombiner.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/GeometryCollection.h>

namespace GEOMETRY {
namespace geom { // geos.geom
namespace util { // geos.geom.util

Geometry* GeometryCombiner::combine(std::vector<Geometry*> const& geoms)
{
    GeometryCombiner combiner(geoms);
    return combiner.combine();
}

Geometry* GeometryCombiner::combine(Geometry* g0, Geometry* g1)
{
    std::vector<Geometry*> geoms;
    geoms.push_back(g0);
    geoms.push_back(g1);

    GeometryCombiner combiner(geoms);
    return combiner.combine();
}

Geometry* GeometryCombiner::combine(Geometry* g0, Geometry* g1, Geometry* g2)
{
    std::vector<Geometry*> geoms;
    geoms.push_back(g0);
    geoms.push_back(g1);
    geoms.push_back(g2);

    GeometryCombiner combiner(geoms);
    return combiner.combine();
}

GeometryCombiner::GeometryCombiner(std::vector<Geometry*> const& geoms)
  : geomFactory(extractFactory(geoms)), skipEmpty(false), inputGeoms(geoms)
{
}

GeometryFactory const* 
GeometryCombiner::extractFactory(std::vector<Geometry*> const& geoms) 
{
    return geoms.empty() ? NULL : geoms.front()->getFactory();
}

Geometry* GeometryCombiner::combine()
{
    std::vector<Geometry*> elems;

    std::vector<Geometry*>::const_iterator end = inputGeoms.end();
    for (std::vector<Geometry*>::const_iterator i = inputGeoms.begin(); 
         i != end; ++i) 
    {
        extractElements(*i, elems);
    }

    if (elems.empty()) {
        if (geomFactory != NULL) {
            return geomFactory->createGeometryCollection(NULL);
        }
        return NULL;
    }

    // return the "simplest possible" geometry
    return geomFactory->buildGeometry(elems);
}

void 
GeometryCombiner::extractElements(Geometry* geom, std::vector<Geometry*>& elems)
{
    if (geom == NULL)
        return;

    for (std::size_t i = 0; i < geom->getNumGeometries(); ++i) {
        Geometry* elemGeom = const_cast<Geometry*>(geom->getGeometryN(i));
        if (skipEmpty && elemGeom->isEmpty())
            continue;
        elems.push_back(elemGeom);
    }
}

} // namespace GEOMETRY.geom.util
} // namespace GEOMETRY.geom
} // namespace GEOMETRY

