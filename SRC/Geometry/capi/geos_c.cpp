/************************************************************************
 *
 * $Id: geos_c.cpp 2535 2009-06-01 17:14:28Z pramsey $
 *
 * C-Wrapper for GEOS library
 *
 * Copyright (C) 2005-2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 * Author: Sandro Santilli <strk@refractions.net>
 *
 ***********************************************************************/

#include <Geometry/geom/prep/PreparedGeometryFactory.h> 
#include <Geometry/io/WKTReader.h>
#include <Geometry/io/WKBReader.h>
#include <Geometry/io/WKTWriter.h>
#include <Geometry/io/WKBWriter.h>
#include <Geometry/io/CLocalizer.h>
#include <Geometry/operation/overlay/OverlayOp.h>
#include <Geometry/operation/union/CascadedPolygonUnion.h>

// Some extra magic to make type declarations in geos_c.h work - for cross-checking of types in header.
#define GEOSGeometry GEOMETRY::geom::Geometry
#define GEOSPreparedGeometry GEOMETRY::geom::prep::PreparedGeometry
#define GEOSCoordSequence GEOMETRY::geom::CoordinateSequence
#define GEOSWKTReader_t GEOMETRY::io::WKTReader
#define GEOSWKTWriter_t GEOMETRY::io::WKTWriter
#define GEOSWKBReader_t GEOMETRY::io::WKBReader
#define GEOSWKBWriter_t GEOMETRY::io::WKBWriter

#include "geos_c.h"

/// Define this if you want operations triggering Exceptions to
/// be printed (will use the NOTIFY channel - only implemented for GEOSUnion so far)
///
#undef VERBOSE_EXCEPTIONS

#if defined(_MSC_VER)
#  define GEOS_DLL     __declspec(dllexport)
#else
#  define GEOS_DLL
#endif

// import the most frequently used definitions globally
using GEOMETRY::geom::Geometry;
using GEOMETRY::geom::LineString;
using GEOMETRY::geom::Polygon;
using GEOMETRY::geom::CoordinateSequence;
using GEOMETRY::geom::GeometryFactory;

using GEOMETRY::io::WKTReader;
using GEOMETRY::io::WKTWriter;
using GEOMETRY::io::WKBReader;
using GEOMETRY::io::WKBWriter;
using GEOMETRY::io::CLocalizer;

using GEOMETRY::operation::overlay::OverlayOp;
using GEOMETRY::operation::overlay::overlayOp;
using GEOMETRY::operation::geounion::CascadedPolygonUnion;


typedef std::auto_ptr<Geometry> GeomAutoPtr;

//## GLOBALS ################################################

// NOTE: SRID will have to be changed after geometry creation
GEOSContextHandle_t handle = NULL;

extern "C" {

void
initGEOS (GEOSMessageHandler nf, GEOSMessageHandler ef)
{
    handle = initGEOS_r( nf, ef );
}

void
finishGEOS ()
{
    if (handle != NULL) 
    { 
        finishGEOS_r( handle ); 
        handle = NULL; 
    } 
}

void 
GEOSFree (void* buffer) 
{ 
    GEOSFree_r( handle, buffer ); 
} 
    
/****************************************************************
** relate()-related functions
** return 0 = false, 1 = true, 2 = error occured
**
*/
char
GEOSDisjoint(const Geometry *g1, const Geometry *g2)
{
    return GEOSDisjoint_r( handle, g1, g2 );
}

char
GEOSTouches(const Geometry *g1, const Geometry *g2)
{
    return GEOSTouches_r( handle, g1, g2 );
}

char
GEOSIntersects(const Geometry *g1, const Geometry *g2)
{
    return GEOSIntersects_r( handle, g1, g2 );
}

char
GEOSCrosses(const Geometry *g1, const Geometry *g2)
{
    return GEOSCrosses_r( handle, g1, g2 );
}

char
GEOSWithin(const Geometry *g1, const Geometry *g2)
{
    return GEOSWithin_r( handle, g1, g2 );
}

// call g1->contains(g2)
// returns 0 = false
//         1 = true
//         2 = error was trapped
char
GEOSContains(const Geometry *g1, const Geometry *g2)
{
    return GEOSContains_r( handle, g1, g2 );
}

char
GEOSOverlaps(const Geometry *g1, const Geometry *g2)
{
    return GEOSOverlaps_r( handle, g1, g2 );
}


//-------------------------------------------------------------------
// low-level relate functions
//------------------------------------------------------------------

char
GEOSRelatePattern(const Geometry *g1, const Geometry *g2, const char *pat)
{
    return GEOSRelatePattern_r( handle, g1, g2, pat );
}

char *
GEOSRelate(const Geometry *g1, const Geometry *g2)
{
    return GEOSRelate_r( handle, g1, g2 );
}



//-----------------------------------------------------------------
// isValid
//-----------------------------------------------------------------


char
GEOSisValid(const Geometry *g1)
{
    return GEOSisValid_r( handle, g1 );
}

char *
GEOSisValidReason(const Geometry *g1)
{
    return GEOSisValidReason_r( handle, g1 );
}

//-----------------------------------------------------------------
// general purpose
//-----------------------------------------------------------------

char
GEOSEquals(const Geometry *g1, const Geometry *g2)
{
    return GEOSEquals_r( handle, g1, g2 );
}

char
GEOSEqualsExact(const Geometry *g1, const Geometry *g2, double tolerance)
{
    return GEOSEqualsExact_r( handle, g1, g2, tolerance );
}

int
GEOSDistance(const Geometry *g1, const Geometry *g2, double *dist)
{
    return GEOSDistance_r( handle, g1, g2, dist );
}

int
GEOSArea(const Geometry *g, double *area)
{
    return GEOSArea_r( handle, g, area );
}

int
GEOSLength(const Geometry *g, double *length)
{
    return GEOSLength_r( handle, g, length );
}

Geometry *
GEOSGeomFromWKT(const char *wkt)
{
    return GEOSGeomFromWKT_r( handle, wkt );
}

char *
GEOSGeomToWKT(const Geometry *g1)
{
    return GEOSGeomToWKT_r( handle, g1 );
}

// Remember to free the result!
unsigned char *
GEOSGeomToWKB_buf(const Geometry *g, size_t *size)
{
    return GEOSGeomToWKB_buf_r( handle, g, size );
}

Geometry *
GEOSGeomFromWKB_buf(const unsigned char *wkb, size_t size)
{
    return GEOSGeomFromWKB_buf_r( handle, wkb, size );
}

/* Read/write wkb hex values.  Returned geometries are
   owned by the caller.*/
unsigned char *
GEOSGeomToHEX_buf(const Geometry *g, size_t *size)
{
    return GEOSGeomToHEX_buf_r( handle, g, size );
}

Geometry *
GEOSGeomFromHEX_buf(const unsigned char *hex, size_t size)
{
    return GEOSGeomFromHEX_buf_r( handle, hex, size );
}

char
GEOSisEmpty(const Geometry *g1)
{
    return GEOSisEmpty_r( handle, g1 );
}

char
GEOSisSimple(const Geometry *g1)
{
    return GEOSisSimple_r( handle, g1 );
}

char
GEOSisRing(const Geometry *g)
{
    return GEOSisRing_r( handle, g );
}



//free the result of this
char *
GEOSGeomType(const Geometry *g1)
{
    return GEOSGeomType_r( handle, g1 );
}

// Return postgis geometry type index
int
GEOSGeomTypeId(const Geometry *g1)
{
    return GEOSGeomTypeId_r( handle, g1 );
}




//-------------------------------------------------------------------
// GEOS functions that return geometries
//-------------------------------------------------------------------

Geometry *
GEOSEnvelope(const Geometry *g1)
{
    return GEOSEnvelope_r( handle, g1 );
}

Geometry *
GEOSIntersection(const Geometry *g1, const Geometry *g2)
{
    return GEOSIntersection_r( handle, g1, g2 );
}

Geometry *
GEOSBuffer(const Geometry *g1, double width, int quadrantsegments)
{
    return GEOSBuffer_r( handle, g1, width, quadrantsegments );
}

Geometry *
GEOSConvexHull(const Geometry *g1)
{
    return GEOSConvexHull_r( handle, g1 );
}

Geometry *
GEOSDifference(const Geometry *g1, const Geometry *g2)
{
    return GEOSDifference_r( handle, g1, g2 );
}

Geometry *
GEOSBoundary(const Geometry *g1)
{
    return GEOSBoundary_r( handle, g1 );
}

Geometry *
GEOSSymDifference(const Geometry *g1, const Geometry *g2)
{
    return GEOSSymDifference_r( handle, g1, g2 );
}

Geometry *
GEOSUnion(const Geometry *g1, const Geometry *g2)
{
    return GEOSUnion_r( handle, g1, g2 );
}

Geometry *
GEOSUnionCascaded(const Geometry *g1)
{
	return GEOSUnionCascaded_r( handle, g1 );
}

Geometry *
GEOSPointOnSurface(const Geometry *g1)
{
    return GEOSPointOnSurface_r( handle, g1 );
}





//-------------------------------------------------------------------
// memory management functions
//------------------------------------------------------------------


void
GEOSGeom_destroy(Geometry *a)
{
    return GEOSGeom_destroy_r( handle, a );
}


int
GEOSGetNumCoordinates(const Geometry *g1)
{
    return GEOSGetNumCoordinates_r( handle, g1 );
}

/*
 * Return -1 on exception, 0 otherwise. 
 * Converts Geometry to normal form (or canonical form).
 */
int
GEOSNormalize(Geometry *g1)
{
    return GEOSNormalize_r( handle, g1 );
}

int
GEOSGetNumInteriorRings(const Geometry *g1)
{
    return GEOSGetNumInteriorRings_r( handle, g1 );
}


// returns -1 on error and 1 for non-multi geometries
int
GEOSGetNumGeometries(const Geometry *g1)
{
    return GEOSGetNumGeometries_r( handle, g1 );
}


/*
 * Call only on GEOMETRYCOLLECTION or MULTI*.
 * Return a pointer to the internal Geometry.
 */
const Geometry *
GEOSGetGeometryN(const Geometry *g1, int n)
{
    return GEOSGetGeometryN_r( handle, g1, n );
}


/*
 * Call only on polygon
 * Return a copy of the internal Geometry.
 */
const Geometry *
GEOSGetExteriorRing(const Geometry *g1)
{
    return GEOSGetExteriorRing_r( handle, g1 );
}

/*
 * Call only on polygon
 * Return a pointer to internal storage, do not destroy it.
 */
const Geometry *
GEOSGetInteriorRingN(const Geometry *g1, int n)
{
    return GEOSGetInteriorRingN_r( handle, g1, n );
}

Geometry *
GEOSGetCentroid(const Geometry *g)
{
    return GEOSGetCentroid_r( handle, g );
}

Geometry *
GEOSGeom_createCollection(int type, Geometry **geoms, unsigned int ngeoms)
{
    return GEOSGeom_createCollection_r( handle, type, geoms, ngeoms );
}

Geometry *
GEOSPolygonize(const Geometry * const * g, unsigned int ngeoms)
{
    return GEOSPolygonize_r( handle, g, ngeoms );
}

Geometry *
GEOSPolygonizer_getCutEdges(const Geometry * const * g, unsigned int ngeoms)
{
    return GEOSPolygonizer_getCutEdges_r( handle, g, ngeoms );
}

Geometry *
GEOSLineMerge(const Geometry *g)
{
    return GEOSLineMerge_r( handle, g );
}

int
GEOSGetSRID(const Geometry *g1)
{
    return GEOSGetSRID_r( handle, g1 );
}

void
GEOSSetSRID(Geometry *g, int srid)
{
    GEOSSetSRID_r( handle, g, srid);
}

char 
GEOSHasZ(const Geometry *g)
{
    return GEOSHasZ_r( handle, g );
}

int
GEOS_getWKBOutputDims()
{
    return GEOS_getWKBOutputDims_r( handle );
}

int
GEOS_setWKBOutputDims(int newdims)
{
    return GEOS_setWKBOutputDims_r( handle, newdims );
}

int
GEOS_getWKBByteOrder()
{
	return GEOS_getWKBByteOrder_r( handle );
}

int
GEOS_setWKBByteOrder(int byteOrder)
{
	return GEOS_setWKBByteOrder_r( handle, byteOrder );
}


CoordinateSequence *
GEOSCoordSeq_create(unsigned int size, unsigned int dims)
{
    return GEOSCoordSeq_create_r( handle, size, dims );
}

int
GEOSCoordSeq_setOrdinate(CoordinateSequence *s, unsigned int idx, unsigned int dim, double val)
{
    return GEOSCoordSeq_setOrdinate_r( handle, s, idx, dim, val );
}

int
GEOSCoordSeq_setX(CoordinateSequence *s, unsigned int idx, double val)
{
	return GEOSCoordSeq_setOrdinate(s, idx, 0, val);
}

int
GEOSCoordSeq_setY(CoordinateSequence *s, unsigned int idx, double val)
{
	return GEOSCoordSeq_setOrdinate(s, idx, 1, val);
}

int
GEOSCoordSeq_setZ(CoordinateSequence *s, unsigned int idx, double val)
{
	return GEOSCoordSeq_setOrdinate(s, idx, 2, val);
}

CoordinateSequence *
GEOSCoordSeq_clone(const CoordinateSequence *s)
{
    return GEOSCoordSeq_clone_r( handle, s );
}

int
GEOSCoordSeq_getOrdinate(const CoordinateSequence *s, unsigned int idx, unsigned int dim, double *val)
{
    return GEOSCoordSeq_getOrdinate_r( handle, s, idx, dim, val );
}

int
GEOSCoordSeq_getX(const CoordinateSequence *s, unsigned int idx, double *val)
{
	return GEOSCoordSeq_getOrdinate(s, idx, 0, val);
}

int
GEOSCoordSeq_getY(const CoordinateSequence *s, unsigned int idx, double *val)
{
	return GEOSCoordSeq_getOrdinate(s, idx, 1, val);
}

int
GEOSCoordSeq_getZ(const CoordinateSequence *s, unsigned int idx, double *val)
{
	return GEOSCoordSeq_getOrdinate(s, idx, 2, val);
}

int
GEOSCoordSeq_getSize(const CoordinateSequence *s, unsigned int *size)
{
    return GEOSCoordSeq_getSize_r( handle, s, size );
}

int
GEOSCoordSeq_getDimensions(const CoordinateSequence *s, unsigned int *dims)
{
    return GEOSCoordSeq_getDimensions_r( handle, s, dims );
}

void
GEOSCoordSeq_destroy(CoordinateSequence *s)
{
    return GEOSCoordSeq_destroy_r( handle, s );
}

const CoordinateSequence *
GEOSGeom_getCoordSeq(const Geometry *g)
{
    return GEOSGeom_getCoordSeq_r( handle, g );
}

Geometry *
GEOSGeom_createPoint(CoordinateSequence *cs)
{
    return GEOSGeom_createPoint_r( handle, cs );
}

Geometry *
GEOSGeom_createLinearRing(CoordinateSequence *cs)
{
    return GEOSGeom_createLinearRing_r( handle, cs );
}

Geometry *
GEOSGeom_createLineString(CoordinateSequence *cs)
{
    return GEOSGeom_createLineString_r( handle, cs );
}

Geometry *
GEOSGeom_createPolygon(Geometry *shell, Geometry **holes, unsigned int nholes)
{
    return GEOSGeom_createPolygon_r( handle, shell, holes, nholes );
}

Geometry *
GEOSGeom_clone(const Geometry *g)
{
    return GEOSGeom_clone_r( handle, g );
}

int
GEOSGeom_getDimensions(const Geometry *g)
{
    return GEOSGeom_getDimensions_r( handle, g );
}

Geometry *
GEOSSimplify(const Geometry *g1, double tolerance)
{
    return GEOSSimplify_r( handle, g1, tolerance );
}

Geometry *
GEOSTopologyPreserveSimplify(const Geometry *g1, double tolerance)
{
    return GEOSTopologyPreserveSimplify_r( handle, g1, tolerance );
}


/* WKT Reader */
WKTReader *
GEOSWKTReader_create()
{
    return GEOSWKTReader_create_r( handle );
}

void
GEOSWKTReader_destroy(WKTReader *reader)
{
    GEOSWKTReader_destroy_r( handle, reader );
}


Geometry*
GEOSWKTReader_read(WKTReader *reader, const char *wkt)
{
    return GEOSWKTReader_read_r( handle, reader, wkt );
}

/* WKT Writer */
WKTWriter *
GEOSWKTWriter_create()
{
    return GEOSWKTWriter_create_r( handle );
}

void
GEOSWKTWriter_destroy(WKTWriter *Writer)
{
    GEOSWKTWriter_destroy_r( handle, Writer );
}


char*
GEOSWKTWriter_write(WKTWriter *writer, const Geometry *geom)
{
    return GEOSWKTWriter_write_r( handle, writer, geom );
}

/* WKB Reader */
WKBReader *
GEOSWKBReader_create()
{
    return GEOSWKBReader_create_r( handle );
}

void
GEOSWKBReader_destroy(WKBReader *reader)
{
    GEOSWKBReader_destroy_r( handle, reader );
}


Geometry*
GEOSWKBReader_read(WKBReader *reader, const unsigned char *wkb, size_t size)
{
    return GEOSWKBReader_read_r( handle, reader, wkb, size );
}

Geometry*
GEOSWKBReader_readHEX(WKBReader *reader, const unsigned char *hex, size_t size)
{
    return GEOSWKBReader_readHEX_r( handle, reader, hex, size );
}

/* WKB Writer */
WKBWriter *
GEOSWKBWriter_create()
{
    return GEOSWKBWriter_create_r( handle );
}

void
GEOSWKBWriter_destroy(WKBWriter *Writer)
{
    GEOSWKBWriter_destroy_r( handle, Writer );
}


/* The owner owns the result */
unsigned char*
GEOSWKBWriter_write(WKBWriter *writer, const Geometry *geom, size_t *size)
{
    return GEOSWKBWriter_write_r( handle, writer, geom, size );
}

/* The owner owns the result */
unsigned char*
GEOSWKBWriter_writeHEX(WKBWriter *writer, const Geometry *geom, size_t *size)
{
    return GEOSWKBWriter_writeHEX_r( handle, writer, geom, size );
}

int
GEOSWKBWriter_getOutputDimension(const GEOSWKBWriter* writer)
{
    return GEOSWKBWriter_getOutputDimension_r( handle, writer );
}

void
GEOSWKBWriter_setOutputDimension(GEOSWKBWriter* writer, int newDimension)
{
    GEOSWKBWriter_setOutputDimension_r( handle, writer, newDimension );
}

int
GEOSWKBWriter_getByteOrder(const GEOSWKBWriter* writer)
{
    return GEOSWKBWriter_getByteOrder_r( handle, writer );
}

void
GEOSWKBWriter_setByteOrder(GEOSWKBWriter* writer, int newByteOrder)
{
    GEOSWKBWriter_setByteOrder_r( handle, writer, newByteOrder );
}

char
GEOSWKBWriter_getIncludeSRID(const GEOSWKBWriter* writer)
{
    return GEOSWKBWriter_getIncludeSRID_r( handle, writer );
}

void
GEOSWKBWriter_setIncludeSRID(GEOSWKBWriter* writer, const char newIncludeSRID)
{
    GEOSWKBWriter_setIncludeSRID_r( handle, writer, newIncludeSRID );
}


//-----------------------------------------------------------------
// Prepared Geometry 
//-----------------------------------------------------------------

const GEOMETRY::geom::prep::PreparedGeometry*
GEOSPrepare(const Geometry *g)
{
    return GEOSPrepare_r( handle, g );
}

void
GEOSPreparedGeom_destroy(const GEOMETRY::geom::prep::PreparedGeometry *a)
{
    GEOSPreparedGeom_destroy_r( handle, a );
}

char
GEOSPreparedContains(const GEOMETRY::geom::prep::PreparedGeometry *pg1, const Geometry *g2)
{
    return GEOSPreparedContains_r( handle, pg1, g2 );
}

char
GEOSPreparedContainsProperly(const GEOMETRY::geom::prep::PreparedGeometry *pg1, const Geometry *g2)
{
    return GEOSPreparedContainsProperly_r( handle, pg1, g2 );
}

char
GEOSPreparedCovers(const GEOMETRY::geom::prep::PreparedGeometry *pg1, const Geometry *g2)
{
    return GEOSPreparedCovers_r( handle, pg1, g2 );
}

char
GEOSPreparedIntersects(const GEOMETRY::geom::prep::PreparedGeometry *pg1, const Geometry *g2)
{
    return GEOSPreparedIntersects_r( handle, pg1, g2 );
}

} /* extern "C" */
