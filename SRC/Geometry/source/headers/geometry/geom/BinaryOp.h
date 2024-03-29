/**********************************************************************
 * $Id: BinaryOp.h 2127 2008-05-20 21:25:21Z mloskot $
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
 **********************************************************************
 *
 * Last port: ORIGINAL WORK
 *
 **********************************************************************
 *
 * This file provides a single templated function, taking two
 * const Geometry pointers, applying a binary operator to them
 * and returning a result Geometry in an auto_ptr<>.
 *
 * The binary operator is expected to take two const Geometry pointers
 * and return a newly allocated Geometry pointer, possibly throwing
 * a TopologyException to signal it couldn't succeed due to robustness
 * issues.
 *
 * This function will catch TopologyExceptions and try again with
 * slightly modified versions of the input. The following heuristic
 * is used:
 *
 *	- Try with original input.
 *	- Try removing common bits from input coordinate values
 *	- Try snaping input geometries to each other
 *	- Try snaping input coordinates to a increasing grid (size from 1/25 to 1)
 *	- Try simplifiying input with increasing tolerance (from 0.01 to 0.04)
 *
 * If none of the step succeeds the original exception is thrown.
 *
 * Note that you can skip Grid snapping, Geometry snapping and Simplify policies
 * by a compile-time define when building geos.
 * See USE_TP_SIMPLIFY_POLICY, USE_PRECISION_REDUCTION_POLICY and
 * USE_SNAPPING_POLICY macros below.
 *
 *
 **********************************************************************/

#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/PrecisionModel.h>
#include <Geometry/precision/CommonBitsRemover.h>
#include <Geometry/precision/SimpleGeometryPrecisionReducer.h>
#include <Geometry/precision/GeometrySnapper.h>
#include <Geometry/simplify/TopologyPreservingSimplifier.h>
#include <Geometry/operation/valid/IsValidOp.h>
#include <Geometry/util/TopologyException.h>
#include <Geometry/util.h>

#include <memory> // for auto_ptr

//#define GEOS_DEBUG_BINARYOP 1


/*
 * Always try original input first
 */
#ifndef USE_ORIGINAL_INPUT
# define USE_ORIGINAL_INPUT 1
#endif

/*
 * Define this to use PrecisionReduction policy
 * in an attempt at by-passing binary operation
 * robustness problems (handles TopologyExceptions)
 */
#ifndef USE_PRECISION_REDUCTION_POLICY
//# define USE_PRECISION_REDUCTION_POLICY 1
#endif

/*
 * Define this to use TopologyPreserving simplification policy
 * in an attempt at by-passing binary operation
 * robustness problems (handles TopologyExceptions)
 */
#ifndef USE_TP_SIMPLIFY_POLICY 
//# define USE_TP_SIMPLIFY_POLICY 1
#endif

/*
 * Use common bits removal policy.
 * If enabled, this would be tried /before/
 * Geometry snapping.
 */
#ifndef USE_COMMONBITS_POLICY
# define USE_COMMONBITS_POLICY 1
#endif

/*
 * Use snapping policy
 */
#ifndef USE_SNAPPING_POLICY
# define USE_SNAPPING_POLICY 1
#endif

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

bool
check_valid(const Geometry& g, const std::string& label)
{
	operation::valid::IsValidOp ivo(&g);
	if ( ! ivo.isValid() )
	{
		std::cerr << label << ": is invalid!"
			<< ivo.getValidationError()->toString() << std::endl;
		return false;
	} 
	return true;
}

/// \brief
/// Apply a binary operation to the given geometries
/// after snapping them to each other after common-bits
/// removal.
///
template <class BinOp>
std::auto_ptr<Geometry>
SnapOp(const Geometry* g0, const Geometry *g1, BinOp _Op)
{
	typedef std::auto_ptr<Geometry> GeomPtr;

#define CBR_BEFORE_SNAPPING 1

	using GEOMETRY::precision::GeometrySnapper;

	// Snap tolerance must be computed on the original
	// (not commonbits-removed) geoms
	double snapTolerance = GeometrySnapper::computeOverlaySnapTolerance(*g0, *g1);
#if GEOS_DEBUG_BINARYOP
	std::cerr<<"Computed snap tolerance: "<<snapTolerance<<std::endl;
#endif

	GEOMETRY::precision::CommonBitsRemover cbr;

#if CBR_BEFORE_SNAPPING
	// Now remove common bits
	GeomPtr rG0( cbr.removeCommonBits(g0->clone()) );
	GeomPtr rG1( cbr.removeCommonBits(g1->clone()) );

#if GEOS_DEBUG_BINARYOP
	check_valid(*rG0, "CBR: removed-bits geom 0");
	check_valid(*rG1, "CBR: removed-bits geom 1");
#endif

	const Geometry& operand0 = *rG0;
	const Geometry& operand1 = *rG1;
#else // don't CBR before snapping
	const Geometry& operand0 = *g0
	const Geometry& operand1 = *g1
#endif

	GeometrySnapper snapper0( operand0 );
	GeomPtr snapG0( snapper0.snapTo(operand1, snapTolerance) );

	// NOTE: second geom is snapped on the snapped first one
	GeometrySnapper snapper1( operand1 );
	GeomPtr snapG1( snapper1.snapTo(*snapG0, snapTolerance) );

#if GEOS_DEBUG_BINARYOP
	check_valid(*snapG0, "SNAP: snapped geom 0");
	check_valid(*snapG1, "SNAP: snapped geom 1");
#endif

	// Run the binary op
	GeomPtr result( _Op(snapG0.get(), snapG1.get()) );

#if GEOS_DEBUG_BINARYOP
	check_valid(*result, "Op result (before common-bits addition");
#endif

#if CBR_BEFORE_SNAPPING
	// Add common bits back in
	cbr.addCommonBits( result.get() );
#endif

#if GEOS_DEBUG_BINARYOP
	check_valid(*result, "Op result (after common-bits addition");
#endif

	return result;
}

template <class BinOp>
std::auto_ptr<Geometry>
BinaryOp(const Geometry* g0, const Geometry *g1, BinOp _Op)
{
	typedef std::auto_ptr<Geometry> GeomPtr;

	GeomPtr ret;
	util::TopologyException origException;

#ifdef USE_ORIGINAL_INPUT
	// Try with original input
	try
	{
#if GEOS_DEBUG_BINARYOP
		std::cerr << "Trying with original input." << std::endl;
#endif
		ret.reset(_Op(g0, g1));
		return ret;
	}
	catch (const util::TopologyException& ex)
	{
		origException=ex;
#if GEOS_DEBUG_BINARYOP
		std::cerr << "Original exception: " << ex.what() << std::endl;
#endif
	}
#endif // USE_ORIGINAL_INPUT


#ifdef USE_COMMONBITS_POLICY
	// Try removing common bits (possibly obsoleted by snapping below)
	try
	{
		GeomPtr rG0;
		GeomPtr rG1;
		precision::CommonBitsRemover cbr;

#if GEOS_DEBUG_BINARYOP
		std::cerr << "Trying with Common bits remover." << std::endl;
#endif

		cbr.add(g0);
		cbr.add(g1);

		rG0.reset( cbr.removeCommonBits(g0->clone()) );
		rG1.reset( cbr.removeCommonBits(g1->clone()) );

#if GEOS_DEBUG_BINARYOP
		if ( ! rG0->isValid() )
		{
			std::cerr << " CBR: geom 0 is invalid!" << std::endl;
		}

		if ( ! rG1->isValid() )
		{
			std::cerr << " CBR: geom 1 is invalid!" << std::endl;
		}
#endif

		ret.reset( _Op(rG0.get(), rG1.get()) );

		cbr.addCommonBits( ret.get() );

		return ret;
	}
	catch (const util::TopologyException& ex)
	{
        UNREFERENCED_PARAMETER(ex);
#if GEOS_DEBUG_BINARYOP
		std::cerr << "CBR: " << ex.what() << std::endl;
#endif
	}
#endif

	// Try with snapping
	//
	// TODO: possible optimization would be reusing the
	//       already common-bit-removed inputs and just
	//       apply geometry snapping, whereas the current
	//       SnapOp function does both.
// {
#if USE_SNAPPING_POLICY

#if GEOS_DEBUG_BINARYOP
	std::cerr << "Trying with snapping " << std::endl;
#endif

	try {
		ret = SnapOp(g0, g1, _Op);
#if GEOS_DEBUG_BINARYOP
	std::cerr << "SnapOp succeeded" << std::endl;
#endif
		return ret;
		
	}
	catch (const util::TopologyException& ex)
	{
        UNREFERENCED_PARAMETER(ex);
#if GEOS_DEBUG_BINARYOP
		std::cerr << "SNAP: " << ex.what() << std::endl;
#endif
	}

#endif // USE_SNAPPING_POLICY }



// {
#if USE_PRECISION_REDUCTION_POLICY


	// Try reducing precision
	try
	{
		int maxPrecision=25;

		for (int precision=maxPrecision; precision; --precision)
		{
			std::auto_ptr<PrecisionModel> pm(new PrecisionModel(precision));
#if GEOS_DEBUG_BINARYOP
			std::cerr << "Trying with precision " << precision << std::endl;
#endif

			precision::SimpleGeometryPrecisionReducer reducer( pm.get() );
			GeomPtr rG0( reducer.reduce(g0) );
			GeomPtr rG1( reducer.reduce(g1) );

			try
			{
				ret.reset( _Op(rG0.get(), rG1.get()) );
				return ret;
			}
			catch (const util::TopologyException& ex)
			{
				if ( precision == 1 ) throw ex;
#if GEOS_DEBUG_BINARYOP
				std::cerr << "Reduced with precision (" << precision << "): "
				          << ex.what() << std::endl;
#endif
			}

		}

	}
	catch (const util::TopologyException& ex)
	{
#if GEOS_DEBUG_BINARYOP
		std::cerr << "Reduced: " << ex.what() << std::endl;
#endif
	}

#endif
// USE_PRECISION_REDUCTION_POLICY }

// {
#if USE_TP_SIMPLIFY_POLICY 

	// Try simplifying
	try
	{

		double maxTolerance = 0.04;
		double minTolerance = 0.01;
		double tolStep = 0.01;

		for (double tol = minTolerance; tol <= maxTolerance; tol += tolStep)
		{
#if GEOS_DEBUG_BINARYOP
			std::cerr << "Trying simplifying with tolerance " << tol << std::endl;
#endif

			GeomPtr rG0( simplify::TopologyPreservingSimplifier::simplify(g0, tol) );
			GeomPtr rG1( simplify::TopologyPreservingSimplifier::simplify(g1, tol) );

			try
			{
				ret.reset( _Op(rG0.get(), rG1.get()) );
				return ret;
			}
			catch (const util::TopologyException& ex)
			{
				if ( tol >= maxTolerance ) throw ex;
#if GEOS_DEBUG_BINARYOP
				std::cerr << "Simplified with tolerance (" << tol << "): "
				          << ex.what() << std::endl;
#endif
			}

		}

		return ret;

	}
	catch (const util::TopologyException& ex)
	{
#if GEOS_DEBUG_BINARYOP
		std::cerr << "Simplified: " << ex.what() << std::endl;
#endif
	}

#endif
// USE_TP_SIMPLIFY_POLICY }

	throw origException;
}


} // namespace GEOMETRY::geom
} // namespace GEOMETRY
