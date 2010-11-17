/**********************************************************************
 * $Id: ShortCircuitedGeometryVisitor.h 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************/

#ifndef GEOMETRY_GEOM_UTIL_SHORTCIRCUITEDGEOMETRYVISITOR_H
#define GEOMETRY_GEOM_UTIL_SHORTCIRCUITEDGEOMETRYVISITOR_H

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class Geometry;
	}
}


namespace GEOMETRY {
namespace geom { // geos.geom
namespace util { // geos.geom.util

/** \brief
 * A visitor to Geometry elements which can
 * be short-circuited by a given condition
 *
 * Last port: geom/util/ShortCircuitedGeometryVisitor.java rev. 1.1 (JTS-1.7)
 */
class ShortCircuitedGeometryVisitor
{

private:

	bool done;

protected:

	virtual void visit(const Geometry &element)=0;
	virtual bool isDone()=0;

public:

	ShortCircuitedGeometryVisitor()
		:
		done(false)
		{}

	void applyTo(const Geometry &geom);

	virtual ~ShortCircuitedGeometryVisitor() {}

};

} // namespace GEOMETRY.geom.util
} // namespace GEOMETRY.geom
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/geom/util/ShortCircuitedGeometryVisitor.inl"
//#endif

#endif

/**********************************************************************
 * $Log$
 * Revision 1.3  2006/06/08 11:20:24  strk
 * Added missing virtual destructor to abstract classes.
 *
 * Revision 1.2  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/
