/**********************************************************************
 * $Id: OverlayNodeFactory.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_OP_OVERLAY_OVERLAYNODEFACTORY_H
#define GEOS_OP_OVERLAY_OVERLAYNODEFACTORY_H

#include <vector>

#include <Geometry/geomgraph/NodeFactory.h> // for inheritance

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class Coordinate;
	}
	namespace geomgraph {
		class Node;
	}
}

namespace GEOMETRY {
namespace operation { // GEOMETRY::operation
namespace overlay { // GEOMETRY::operation::overlay

/** \brief
 * Creates nodes for use in the geomgraph::PlanarGraph constructed during
 * overlay operations. NOTE: also used by operation::valid
 */
class OverlayNodeFactory: public geomgraph::NodeFactory {
public:
	geomgraph::Node* createNode(const geom::Coordinate &coord) const;
	static const geomgraph::NodeFactory &instance();
};


} // namespace GEOMETRY::operation::overlay
} // namespace GEOMETRY::operation
} // namespace GEOMETRY

#endif // ndef GEOS_OP_OVERLAY_OVERLAYNODEFACTORY_H

/**********************************************************************
 * $Log$
 * Revision 1.1  2006/03/17 13:24:59  strk
 * opOverlay.h header splitted. Reduced header inclusions in operation/overlay implementation files. ElevationMatrixFilter code moved from own file to ElevationMatrix.cpp (ideally a class-private).
 *
 **********************************************************************/

