//
// GeometrySerializor.cpp
//

#include <Geometry/io/GeometrySerializor.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/CoordinateArraySequence.h>
#include <Geometry/geom/ISegment.h>
#include <Geometry/geom/Point.h>
#include <Geometry/geom/LinearRing.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geom/Geometry.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/MultiPoint.h>
#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/MultiPolygon.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/PrecisionModel.h>
#include <Geometry/geom/Circle.h>
#include <Geometry/geom/Ellipse.h>
#include <Geometry/geom/BezierCurve.h>
#include <Geometry/geom/BezierSpline.h>

#include <geometry/geom/GeometryFactory.h>


#include <typeinfo>
#include <cstdio> // should avoid this
#include <cassert>

using namespace std;
using namespace GEOMETRY::geom;

namespace GEOMETRY { // Namepspace GEOMETRY
	namespace io {		// NameSpace  TT_GEOMETRY_IO

GeometySerializor::GeometySerializor()
{
	m_pGeometry = NULL;
}

GeometySerializor::GeometySerializor( Geometry *pGeometry )
{
	m_pGeometry = pGeometry;
}

GeometySerializor::~GeometySerializor()
{
	//have nothing needed to do 
}

Geometry* GeometySerializor::serialization( otSystem::IArchive &ar )
{
	GeometryTypeId typeID;
	if ( ar.IsRead() )
	{
		long nTypeID;
		ar & nTypeID;
		typeID = ( GeometryTypeId )nTypeID;
	}
	else
	{
		typeID = m_pGeometry->getGeometryTypeId();
		long nTypeID = typeID;
		ar & nTypeID;
	}

	if ( typeID == GEOS_POINT ) 
		RWPoint( ar );
	else if ( typeID == GEOS_LINESTRING )
		RWLineString( ar );
	else if ( typeID == GEOS_LINEARRING ) 
		RWLinearRing( ar ); 
	else if ( typeID == GEOS_POLYGON )
		RWPolygon( ar );  
	else if ( typeID == GEOS_MULTIPOINT )
		RWMultiPoint( ar );
	else if ( typeID == GEOS_MULTILINESTRING )
		RWMultiLineString( ar );
	else if ( typeID == GEOS_MULTIPOLYGON )
		RWMultiPolygon( ar );
	else if ( typeID == GEOS_GEOMETRYCOLLECTION )
		RWGeometryCollection( ar );
	else if ( typeID == GEOM_CIRCLE )
		RWCircle( ar );
	else if ( typeID == GEOM_ELLIPSE )
		RWEllipse( ar );
	else if ( typeID == GEOM_BEZIERSPLINE )
		RWBezierSpline( ar );
	else
		assert(0); // Unsupported m_pGeometry implementation

	return m_pGeometry;
}

void GeometySerializor::SetGeometry( Geometry *pGeometry )
{
	m_pGeometry = pGeometry;
}

void GeometySerializor::RWPoint( otSystem::IArchive &ar )
{
	if( ar.IsRead() )
	{
		Coordinate coord;
		RWCoordinate( ar, coord );

		if ( m_pGeometry )
			GeometryFactory::getDefaultInstance()->destroyGeometry( m_pGeometry );

		m_pGeometry = GeometryFactory::getDefaultInstance()->createPoint( coord );
	}
	else
	{
		assert( m_pGeometry != NULL ); //m_pGeometry is Null

		GEOMETRY::geom::Point *pPoint = dynamic_cast<GEOMETRY::geom::Point *>( m_pGeometry );
		const Coordinate *pCoord = pPoint->getCoordinate();
		RWCoordinate( ar, const_cast<Coordinate *>( pCoord ) );
	}
}

void GeometySerializor::RWLineString( otSystem::IArchive &ar )
{
	m_pGeometry = RWLineString( ar, dynamic_cast<LineString *>( m_pGeometry ) );
}

void GeometySerializor::RWLinearRing( otSystem::IArchive &ar )
{
	m_pGeometry = RWLinearRing( ar, dynamic_cast<LinearRing *>( m_pGeometry ) );
}

void GeometySerializor::RWPolygon( otSystem::IArchive &ar )
{
	m_pGeometry = RWPolygon( ar, dynamic_cast<Polygon *>( m_pGeometry ) );
}

void GeometySerializor::RWMultiPoint( otSystem::IArchive &ar )
{
	if( ar.IsRead() )
	{
		CoordinateSequence *pCoordSq = NULL;
		pCoordSq = RWCoordinateSequence( ar, pCoordSq );

		if ( m_pGeometry )
			GeometryFactory::getDefaultInstance()->destroyGeometry( m_pGeometry );

		m_pGeometry = GeometryFactory::getDefaultInstance()->createMultiPoint( *pCoordSq );
	}
	else
	{
		assert( m_pGeometry != NULL );

		MultiPoint *pMultiPt= dynamic_cast<MultiPoint *>( m_pGeometry );
		CoordinateSequence	*pCoordSq = pMultiPt->getCoordinates();

		RWCoordinateSequence( ar, pCoordSq );
	}

}

void GeometySerializor::RWMultiLineString( otSystem::IArchive &ar )
{
	if( ar.IsRead() )
	{
		long nNumLines;
		ar & nNumLines;

		vector<Geometry *> vecLines;
		for ( long i = 0; i < nNumLines; ++i )
		{
			LineString *pLs = NULL;
			pLs = RWLineString( ar, pLs );
			vecLines.push_back( pLs );
		}

		if ( m_pGeometry )
			GeometryFactory::getDefaultInstance()->destroyGeometry( m_pGeometry );

		m_pGeometry = GeometryFactory::getDefaultInstance()->createMultiLineString( vecLines );
	}
	else
	{
		assert( m_pGeometry != NULL );

		MultiLineString *pMulLineString = dynamic_cast<MultiLineString *>( m_pGeometry );

		long nNumLineString = pMulLineString->getNumGeometries();

		ar & nNumLineString;

		for ( long i  = 0; i < nNumLineString; ++i )
		{
			LineString *pLineString =dynamic_cast<LineString *>( pMulLineString->GetGeometry( i ) );
			pLineString = RWLineString( ar, pLineString );
		}
	}
}

void GeometySerializor::RWMultiPolygon( otSystem::IArchive &ar )
{
	if( ar.IsRead() )
	{
		long nNumPolygons;
		ar & nNumPolygons;

		vector<Geometry *> vecPolygons;
		for ( long i = 0; i < nNumPolygons; ++i )
		{
			GEOMETRY::geom::Polygon *pPolygon = NULL;
			pPolygon = RWPolygon( ar, pPolygon );
			vecPolygons.push_back( pPolygon );
		}

		if ( m_pGeometry )
			GeometryFactory::getDefaultInstance()->destroyGeometry( m_pGeometry );

		m_pGeometry = GeometryFactory::getDefaultInstance()->createMultiPolygon( vecPolygons );
	}
	else
	{
		assert( m_pGeometry != NULL );

		MultiPolygon *pMulPolygon = dynamic_cast<MultiPolygon *>( m_pGeometry );

		long nNumPolygons = pMulPolygon->getNumGeometries();

		ar & nNumPolygons;

		for ( long i = 0; i < nNumPolygons; ++i )
		{
			GEOMETRY::geom::Polygon *pPolygon = dynamic_cast<GEOMETRY::geom::Polygon *>( pMulPolygon->GetGeometry( i ) );
			pPolygon = RWPolygon( ar, pPolygon );
		}
	}
}

void GeometySerializor::RWGeometryCollection( otSystem::IArchive &ar )
{
	if( ar.IsRead() )
	{
		long nNumGeometries;
		ar & nNumGeometries;

		vector<Geometry *> vecGeometries;
		for ( long i = 0; i < nNumGeometries; ++i )
		{
			GEOMETRY::geom::Geometry *pGeometry = NULL;

			if ( typeid(*m_pGeometry) == typeid(MultiPoint) )
			{
				Coordinate coord;
				RWCoordinate( ar, coord );
				pGeometry = GeometryFactory::getDefaultInstance()->createPoint();
				pGeometry->AddPoint( coord );
			}
			else if ( typeid(*m_pGeometry) == typeid(MultiLineString) )
			{
				pGeometry = RWLineString( ar, dynamic_cast<LineString *>( pGeometry) );
			}
			else if ( typeid(*m_pGeometry) == typeid(MultiPolygon) )
			{
				pGeometry = RWPolygon( ar, dynamic_cast<Polygon *>( pGeometry ) );
			}

			vecGeometries.push_back( pGeometry );
		}

		if ( m_pGeometry )
			GeometryFactory::getDefaultInstance()->destroyGeometry( m_pGeometry );

		m_pGeometry = GeometryFactory::getDefaultInstance()->createGeometryCollection( vecGeometries );
	}
	else
	{
		assert( m_pGeometry != NULL );

		GeometryCollection *pGeoCollection = dynamic_cast<GeometryCollection *>( m_pGeometry );

		long nNumGeometries = pGeoCollection->getNumGeometries();

		ar & nNumGeometries;

		for ( long i = 0; i < nNumGeometries; ++i )
		{
			GEOMETRY::geom::Geometry *pGeometry =dynamic_cast<GEOMETRY::geom::Geometry *>( pGeoCollection->GetGeometry( i ) );
			if ( typeid(*m_pGeometry) == typeid(MultiPoint) )
			{
				Coordinate coord = ( dynamic_cast<MultiPoint *>( m_pGeometry ) )->GetPoint( i );
				RWCoordinate( ar, coord );
			}
			else if ( typeid(*m_pGeometry) == typeid(MultiLineString) )
			{
				pGeometry = RWLineString( ar, dynamic_cast<LineString *>( pGeometry) );
			}
			else if ( typeid(*m_pGeometry) == typeid(MultiPolygon) )
			{
				pGeometry = RWPolygon( ar, dynamic_cast<Polygon *>( pGeometry ) );
			}
		}
	}
}

void GeometySerializor::RWCircle( otSystem::IArchive &ar )
{
	if( ar.IsRead() )
	{
		Coordinate coordCenter;
		RWCoordinate( ar, coordCenter );

		double radius;
		ar & radius;

		if ( m_pGeometry )
			GeometryFactory::getDefaultInstance()->destroyGeometry( m_pGeometry );

		m_pGeometry = GeometryFactory::getDefaultInstance()->createCircle( coordCenter, radius );
	}
	else
	{
		assert( m_pGeometry != NULL );

		GEOMETRY::geom::Circle *pCircle = dynamic_cast<GEOMETRY::geom::Circle *>( m_pGeometry );

		Coordinate coordCenter = pCircle->GetCenterPoint();
		RWCoordinate( ar, coordCenter );

		double radius = pCircle->GetRadius();
		ar & radius;
	}
}

void GeometySerializor::RWEllipse( otSystem::IArchive &ar )
{
	if( ar.IsRead() )
	{
		Coordinate coordCenter;
		RWCoordinate( ar, coordCenter );

		double semiMajor;
		ar & semiMajor;

		double semiMinor;
		ar & semiMinor;

		if ( m_pGeometry )
			GeometryFactory::getDefaultInstance()->destroyGeometry( m_pGeometry );

		Envelope env( coordCenter.x - semiMajor, coordCenter.x + semiMajor, coordCenter.y - semiMinor, coordCenter.y + semiMinor );
		m_pGeometry = GeometryFactory::getDefaultInstance()->createEllipse( env );
	}
	else
	{
		assert( m_pGeometry != NULL );

		GEOMETRY::geom::Ellipse *pEllipse = dynamic_cast<GEOMETRY::geom::Ellipse *>( m_pGeometry );

		Coordinate coordCenter = pEllipse->GetCenterPoint();
		RWCoordinate( ar, coordCenter );

		double semiMajor, semiMinor;
		pEllipse->GetAxes( &semiMajor, &semiMinor ); 

		ar & semiMajor;
		ar & semiMinor;
	}
}

void GeometySerializor::RWBezierSpline( otSystem::IArchive &ar)
{
	if( ar.IsRead() )
	{
		long nNumKots;
		ar & nNumKots;

		vector<Coordinate> vecCoords;
		for ( long i = 0; i < nNumKots; ++i )
		{
			Coordinate coord;
			RWCoordinate( ar, coord );
			vecCoords.push_back( coord );
		}

		if ( m_pGeometry )
			GeometryFactory::getDefaultInstance()->destroyGeometry( m_pGeometry );
		
		m_pGeometry = GeometryFactory::getDefaultInstance()->createBezierSpline( vecCoords );
	}
	else
	{
		assert( m_pGeometry != NULL );

		GEOMETRY::geom::BezierSpline *pBzSpline = dynamic_cast<GEOMETRY::geom::BezierSpline *>( m_pGeometry );

		vector<Coordinate> vecCoords;
		pBzSpline->Getknots( vecCoords );

		long nNumKots = vecCoords.size();

		ar & nNumKots;

		for ( long i = 0; i < nNumKots; ++i )
			RWCoordinate( ar, vecCoords[i] );
	}
}

Coordinate * GeometySerializor::RWCoordinate(otSystem::IArchive &ar, Coordinate *pCoord )
{
	if ( ar.IsRead() )
	{
		if ( pCoord != NULL)
		{
			delete pCoord;
			pCoord = NULL;
		}
		pCoord = new Coordinate;
	}

	assert( pCoord  != NULL );

	ar & pCoord->x;
	ar & pCoord->y;
	ar & pCoord->z;
	ar & pCoord->m;

	return pCoord;
}

void GeometySerializor::RWCoordinate(otSystem::IArchive &ar, Coordinate &pCoord )
{
	ar & pCoord.x;
	ar & pCoord.y;
	ar & pCoord.z;
	ar & pCoord.m;
}

CoordinateSequence * GeometySerializor::RWCoordinateSequence( otSystem::IArchive &ar, CoordinateSequence *pCoordSeq )
{
	if ( ar.IsRead() )
	{
		long nNumCoord;
		ar & nNumCoord;

		if ( pCoordSeq != NULL )
			delete pCoordSeq;

		vector<Coordinate> *vecCoords = new vector<Coordinate>();
		pCoordSeq = new CoordinateArraySequence( vecCoords );
		
		for ( long i = 0; i < nNumCoord; ++i )
		{
			Coordinate coord;
			RWCoordinate( ar, coord );
			pCoordSeq->add( coord );
		}
	}
	else
	{
		assert( pCoordSeq != NULL ); //m_pGeometry is Null

		long nNumCoord = pCoordSeq->getSize();
		ar & nNumCoord;

		for ( long i = 0; i < nNumCoord; ++i )
		{
			Coordinate coord = pCoordSeq->getAt( i );
			RWCoordinate( ar, coord );
		}
	}

	return pCoordSeq;
}

void GeometySerializor::RWCoordinateSequence( otSystem::IArchive &ar, CoordinateSequence &CoordSeq )
{
	if ( ar.IsRead() )
	{
		long nNumCoord;
		ar & nNumCoord;

		CoordSeq.ClearAll();
		for ( long i = 0; i < nNumCoord; ++i )
		{
			Coordinate coord;
			RWCoordinate( ar, coord );
			CoordSeq.add( coord );
		}
	}
	else
	{
		long nNumCoord = CoordSeq.getSize();
		ar & nNumCoord;

		for ( long i = 0; i < nNumCoord; ++i )
		{
			Coordinate coord = CoordSeq.getAt( i );
			RWCoordinate( ar, coord );
		}
	}
}

LinearRing *  GeometySerializor::RWLinearRing( otSystem::IArchive &ar, LinearRing *pLr )
{
	if( ar.IsRead() )
	{
		if ( pLr )
			GeometryFactory::getDefaultInstance()->destroyGeometry( pLr );
	
		bool isContainArc;
		ar & isContainArc;

		if ( !isContainArc  )
		{
			CoordinateSequence *pCoordSq = NULL;
			pCoordSq = RWCoordinateSequence( ar, pCoordSq );

			pLr = GeometryFactory::getDefaultInstance()->createLinearRing( *pCoordSq );
		}
		else
		{
			pLr = GeometryFactory::getDefaultInstance()->createLinearRing();
			
			long nNumSegments;
			ar & nNumSegments;
			
			for ( long i = 0; i < nNumSegments; ++i )
			{
				ISegment *pSegment = NULL;
				pSegment = RWSegment( ar, pSegment );
				
				pLr->AddSegment( pSegment );
			}
		}
	}
	else
	{
		assert( pLr != NULL );

		bool isContainArc = pLr->IsContainArc();
		ar & isContainArc;

		if ( !pLr->IsContainArc() )
		{
			CoordinateSequence	*pCoordSq = pLr->getCoordinates();

			pCoordSq = RWCoordinateSequence( ar, pCoordSq );
		}
		else
		{
			long nNumSegments = pLr->SegmentCount();
			ar & nNumSegments;

			for ( long i = 0; i < nNumSegments; ++i )
			{
				ISegment *pSegment = pLr->GetSegment( i );
				pSegment = RWSegment( ar, pSegment );
			}
		}
	}

	return pLr;
}

void  GeometySerializor::RWLinearRing( otSystem::IArchive &ar, LinearRing &lr )
{
	if( ar.IsRead() )
	{
		bool isContainArc;
		ar & isContainArc;

		if ( !isContainArc )  
		{
			CoordinateSequence *pCoordSq = NULL;
			pCoordSq = RWCoordinateSequence( ar, pCoordSq );

			lr.SetEmpty();

			lr.setPoints( pCoordSq );
		}
		else
		{
			lr.SetEmpty();

			long nNumSegments;
			ar & nNumSegments;

			for ( long i = 0; i < nNumSegments; ++i )
			{
				ISegment *pSegment = NULL;
				pSegment = RWSegment( ar, pSegment );

				lr.AddSegment( pSegment );
			}
		}
	}
	else
	{
		bool isContainArc = lr.IsContainArc();
		ar & isContainArc;

		if ( !isContainArc )
		{
			CoordinateSequence	*pCoordSq = lr.getCoordinates();

			pCoordSq = RWCoordinateSequence( ar, pCoordSq );
		}
		else
		{
			long nNumSegments = lr.SegmentCount();
			ar & nNumSegments;

			for ( long i = 0; i < nNumSegments; ++i )
			{
				ISegment *pSegment = lr.GetSegment( i );
				pSegment = RWSegment( ar, pSegment );
			}
		}
	}
}

LineString * GeometySerializor::RWLineString( otSystem::IArchive &ar, LineString *pLs )
{
	if( ar.IsRead() )
	{
		if ( pLs )
			GeometryFactory::getDefaultInstance()->destroyGeometry( pLs );

		bool isContainArc;
		ar & isContainArc;

		if ( !isContainArc )
		{
			CoordinateSequence *pCoordSq = NULL;
			pCoordSq = RWCoordinateSequence( ar, pCoordSq );

			pLs = GeometryFactory::getDefaultInstance()->createLineString( *pCoordSq );
		}
		else
		{
			pLs = GeometryFactory::getDefaultInstance()->createLineString();

			long nNumSegments;
			ar & nNumSegments;

			for ( long i = 0; i < nNumSegments; ++i )
			{
				ISegment *pSegment = NULL;
				pSegment = RWSegment( ar, pSegment );

				pLs->AddSegment( pSegment );
			}
		}
	}
	else
	{
		assert( pLs != NULL );

		bool isContainArc = pLs->IsContainArc();
		ar & isContainArc;

		if ( !isContainArc )
		{
			CoordinateSequence	*pCoordSq = pLs->getCoordinates();

			pCoordSq = RWCoordinateSequence( ar, pCoordSq );
		}
		else
		{
			long nNumSegments = pLs->SegmentCount();
			ar & nNumSegments;

			for ( long i = 0; i < nNumSegments; ++i )
			{
				ISegment *pSegment = pLs->GetSegment( i );
				pSegment = RWSegment( ar, pSegment );
			}
		}
	}

	return pLs;
}

void  GeometySerializor::RWLineString( otSystem::IArchive &ar, LineString &ls )
{
	if( ar.IsRead() )
	{

		bool isContainArc;
		ar & isContainArc;

		if ( !isContainArc  )
		{
			CoordinateSequence *pCoordSq = NULL;
			pCoordSq = RWCoordinateSequence( ar, pCoordSq );

			ls.SetEmpty();

			ls.setPoints( pCoordSq );
		}
		else
		{
			ls.SetEmpty();

			long nNumSegments;
			ar & nNumSegments;

			for ( long i = 0; i < nNumSegments; ++i )
			{
				ISegment *pSegment = NULL;
				pSegment = RWSegment( ar, pSegment );

				ls.AddSegment( pSegment );
			}
		}
	}
	else
	{
		bool isContainArc = ls.IsContainArc();
		ar & isContainArc;
		
		if ( !isContainArc )
		{
			CoordinateSequence	*pCoordSq = ls.getCoordinates();

			pCoordSq = RWCoordinateSequence( ar, pCoordSq );
		}
		else
		{
			long nNumSegments = ls.SegmentCount();
			ar & nNumSegments;

			for ( long i = 0; i < nNumSegments; ++i )
			{
				ISegment *pSegment = ls.GetSegment( i );
				pSegment = RWSegment( ar, pSegment );
			}
		}
	}
}

GEOMETRY::geom::Polygon *  GeometySerializor::RWPolygon( otSystem::IArchive &ar, GEOMETRY::geom::Polygon *pPolygon )
{
	if( ar.IsRead() )
	{		
		LinearRing *pShell = NULL;
		pShell = RWLinearRing( ar, pShell );

		long nNumHoles;
		ar & nNumHoles;

		vector<Geometry *> *pHoles = new vector<Geometry *>;
		for ( long i = 0; i < nNumHoles; ++i )
		{
			LinearRing *pHole = NULL;
			pHole = RWLinearRing( ar, pHole );
			pHoles->push_back( pHole );
		}

		if ( pPolygon )
			GeometryFactory::getDefaultInstance()->destroyGeometry( pPolygon );

		pPolygon = GeometryFactory::getDefaultInstance()->createPolygon( pShell, pHoles );
	}
	else
	{
		assert( pPolygon != NULL );

		LineString *shell = const_cast<LineString *>( pPolygon->getExteriorRing() );
		shell = RWLineString( ar, shell );

		long nNumHoles = pPolygon->getNumInteriorRing();

		ar & nNumHoles;

		for ( long i = 0; i < nNumHoles; ++i )
		{
			LineString *pHole = const_cast<LineString *>( pPolygon->getInteriorRingN( i ) );
			pHole = RWLineString( ar, pHole );
		}	
	}

	return pPolygon;
}

void GeometySerializor::RWPolygon( otSystem::IArchive &ar, GEOMETRY::geom::Polygon &polygon )
{
	if( ar.IsRead() )
	{		
		polygon.SetEmpty();

		LinearRing *pShell = NULL;
		pShell = RWLinearRing( ar, pShell );
		polygon.SetExteriorRing( pShell );

		long nNumHoles;
		ar & nNumHoles;

		for ( long i = 0; i < nNumHoles; ++i )
		{
			LinearRing *pHole = NULL;
			pHole = RWLinearRing( ar, pHole );
			polygon.AddGeometry( pHole );
		}
	}
	else
	{
		LineString *pShell = const_cast<LineString *>( polygon.getExteriorRing() );
		RWLineString( ar, pShell );

		long nNumHoles = polygon.getNumInteriorRing();

		ar & nNumHoles;

		for ( long i = 0; i < nNumHoles; ++i )
		{
			LineString *pHole = const_cast<LineString *>( polygon.getInteriorRingN( i ) );
			pHole = RWLineString( ar, pHole );
		}	
	}
}

ISegment * GeometySerializor::RWSegment( otSystem::IArchive &ar, GEOMETRY::geom::ISegment *pSegment )
{
	if ( ar.IsRead() )
	{
		long nID;
		ar & nID;
		GeometryTypeId nTypeID = ( GeometryTypeId ) nID;
		
		if ( pSegment != NULL )
			GeometryFactory::getDefaultInstance()->destroyGeometry( pSegment );

		if ( nTypeID == GEOM_BEZIERCURVE ) 
		{
			Coordinate coordFrom;
			RWCoordinate( ar, coordFrom );

			Coordinate coordEnd;
			RWCoordinate( ar, coordEnd );

			Coordinate firstCtrlPt;
			RWCoordinate( ar, firstCtrlPt );

			Coordinate secondCtrlPt;
			RWCoordinate( ar, secondCtrlPt );
			
			pSegment = new BezierCurve( coordFrom, firstCtrlPt, secondCtrlPt , coordEnd );
		}
		else if( nTypeID ==  GEOM_CIRCULARARC ) 
		{
			Coordinate coordCenter;
			RWCoordinate( ar, coordCenter );

			double radius;
			ar & radius;

			double fromAngle;
			ar & fromAngle;

			double centerAngle;
			ar & centerAngle;

			pSegment = GeometryFactory::getDefaultInstance()->createCircularArc( coordCenter, radius, fromAngle, centerAngle );
		}
		else if( nTypeID ==  GEOM_ELLIPTICARC ) 
		{
			Coordinate coordCenter;
			RWCoordinate( ar, coordCenter );

			double semiMajor, semiMinor;
			ar & semiMajor;
			ar & semiMinor;

			double rotateAngle;
			ar & rotateAngle;

			Coordinate coordFrom;
			RWCoordinate( ar, coordFrom );

			Coordinate coordEnd;
			RWCoordinate( ar, coordEnd );

			bool isCounterClock;
			ar & isCounterClock;

			pSegment = GeometryFactory::getDefaultInstance()->createEllipticArc( coordCenter, semiMajor, semiMinor, rotateAngle, coordFrom, coordEnd, isCounterClock );
		}
		else if( nTypeID ==  GEOM_LINE ) 
		{
			Coordinate coordFrom;
			RWCoordinate( ar, coordFrom );

			Coordinate coordEnd;
			RWCoordinate( ar, coordEnd );

			pSegment = new Line( coordFrom, coordEnd );
		}
	}
	else
	{
		assert( pSegment != NULL );
		
		GeometryTypeId nTypeID = pSegment->getGeometryTypeId();
		long nID = nTypeID;
		ar & nID;

		if ( nTypeID == GEOM_BEZIERCURVE ) 
		{
			Coordinate coordFrom = pSegment->GetFromPoint();
			RWCoordinate( ar, coordFrom );

			Coordinate coordEnd = pSegment->GetToPoint();
			RWCoordinate( ar, coordEnd );

			Coordinate firstCtrlPt = (dynamic_cast<BezierCurve *>(pSegment))->GetFirstCtrlPoint();
			RWCoordinate( ar, firstCtrlPt );

			Coordinate secondCtrlPt = (dynamic_cast<BezierCurve *>(pSegment))->GetSecondCtrlPoint();
			RWCoordinate( ar, secondCtrlPt );
		}
		else if( nTypeID ==  GEOM_CIRCULARARC ) 
		{
			Coordinate coordCenter = (dynamic_cast<CircularArc *>(pSegment))->GetCenterPoint();
			RWCoordinate( ar, coordCenter );

			double radius = (dynamic_cast<CircularArc *>(pSegment))->GetRadius();
			ar & radius;

			double fromAngle = (dynamic_cast<CircularArc *>(pSegment))->GetStartAngle();
			ar & fromAngle;

			double centerAngle = (dynamic_cast<CircularArc *>(pSegment))->GetCenterAngle();
			ar & centerAngle;
		}
		else if( nTypeID ==  GEOM_ELLIPTICARC ) 
		{
			Coordinate coordCenter = (dynamic_cast<EllipticArc *>(pSegment))->GetCenterPoint();
			RWCoordinate( ar, coordCenter );

			double semiMajor, semiMinor;
			(dynamic_cast<EllipticArc *>(pSegment))->GetAxes( &semiMajor, &semiMinor );
			ar & semiMajor;
			ar & semiMinor;

			double rotateAngle = (dynamic_cast<EllipticArc *>(pSegment))->GetRotAngle();
			ar & rotateAngle;

			Coordinate coordFrom = pSegment->GetFromPoint();
			RWCoordinate( ar, coordFrom );

			Coordinate coordEnd = pSegment->GetToPoint();
			RWCoordinate( ar, coordEnd );

			bool isCounterClock = (dynamic_cast<EllipticArc *>(pSegment))->IsCounterClock();
			ar & isCounterClock;
		}
		else if( nTypeID ==  GEOM_LINE ) 
		{
			Coordinate coordFrom = pSegment->GetFromPoint();
			RWCoordinate( ar, coordFrom );

			Coordinate coordEnd = pSegment->GetToPoint();
			RWCoordinate( ar, coordEnd );
		}
	}

	return pSegment;
}



}// Namepspace GEOMETRY
}// NameSpace  TT_GEOMETRY_IO
