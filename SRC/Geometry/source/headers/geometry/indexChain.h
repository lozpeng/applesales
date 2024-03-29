/**********************************************************************
 * $Id: indexChain.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOS_INDEXCHAIN_H
#define GEOS_INDEXCHAIN_H

namespace GEOMETRY {
namespace index { // geos.index

/// Contains classes that implement Monotone Chains
namespace chain { // geos.index.chain

} // namespace GEOMETRY.index.chain
} // namespace GEOMETRY.index
} // namespace GEOMETRY

#include <Geometry/index/chain/MonotoneChain.h>
//#include <Geometry/index/chain/MonotoneChainBuilder.h>
#include <Geometry/index/chain/MonotoneChainOverlapAction.h>
#include <Geometry/index/chain/MonotoneChainSelectAction.h>

#endif

