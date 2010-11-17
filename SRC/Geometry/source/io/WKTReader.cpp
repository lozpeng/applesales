/**********************************************************************
 * $Id: WKTReader.cpp 1820 2006-09-06 16:54:23Z mloskot $
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

#include <Geometry/io/WKTReader.h>
#include <Geometry/io/StringTokenizer.h>
#include <Geometry/io/ParseException.h>
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/Point.h>
#include <Geometry/geom/LinearRing.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/MultiPoint.h>
#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/MultiPolygon.h>
#include <Geometry/geom/CoordinateSequenceFactory.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/PrecisionModel.h>
#include <Geometry/inline.h>
#include <Geometry/geom/Circle.h>
#include <Geometry/geom/Ellipse.h>
#include <Geometry/geom/BezierSpline.h>

#include <sstream>
#include <string>
#include <cassert>

#ifndef GEOS_DEBUG
#define GEOS_DEBUG 0
#endif

#ifdef GEOS_DEBUG
#include <iostream>
#endif

#ifndef GEOS_INLINE
#include <Geometry/io/WKTReader.inl>
#endif

using namespace std;
using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace io { // geos.io

Geometry *
WKTReader::read(const string &wellKnownText)
{
	//auto_ptr<StringTokenizer> tokenizer(new StringTokenizer(wellKnownText));
	StringTokenizer tokenizer(wellKnownText);
	Geometry *g=NULL;
	g=readGeometryTaggedText(&tokenizer);
	return g;
}

CoordinateSequence*
WKTReader::getCoordinates(StringTokenizer *tokenizer)
{
	string nextToken=getNextEmptyOrOpener(tokenizer);
	if (nextToken=="EMPTY") {
		return geometryFactory->getCoordinateSequenceFactory()->create(NULL);
		//new CoordinateArraySequence(); 
	}
	CoordinateSequence *coordinates = \
		geometryFactory->getCoordinateSequenceFactory()->create(NULL);
	Coordinate coord;
	getPreciseCoordinate(tokenizer, coord);
	coordinates->add(coord);
	try {
		nextToken=getNextCloserOrComma(tokenizer);
		while (nextToken==",") {
			getPreciseCoordinate(tokenizer, coord);
			coordinates->add(coord);
			nextToken=getNextCloserOrComma(tokenizer);
		}
	} catch (...) {
		delete coordinates;
		throw;
	}
	return coordinates;
}

void
WKTReader::getPreciseCoordinate(StringTokenizer *tokenizer, Coordinate& coord)
{
	coord.x=getNextNumber(tokenizer);
	coord.y=getNextNumber(tokenizer);
	if (isNumberNext(tokenizer)) {
		coord.z=getNextNumber(tokenizer);
	} else {
		coord.z=DoubleNotANumber;
	}
	precisionModel->makePrecise(coord);
}

bool
WKTReader::isNumberNext(StringTokenizer *tokenizer)
{
	return tokenizer->peekNextToken()==StringTokenizer::TT_NUMBER;
}

double
WKTReader::getNextNumber(StringTokenizer *tokenizer)
{
	int type=tokenizer->nextToken();
	switch(type){
		case StringTokenizer::TT_EOF:
			throw  ParseException("Expected number but encountered end of stream");
		case StringTokenizer::TT_EOL:
			throw  ParseException("Expected number but encountered end of line");
		case StringTokenizer::TT_NUMBER:
			return tokenizer->getNVal();
		case StringTokenizer::TT_WORD:
			throw  ParseException("Expected number but encountered word",tokenizer->getSVal());
		case '(':
			throw  ParseException("Expected number but encountered '('");
		case ')':
			throw  ParseException("Expected number but encountered ')'");
		case ',':
			throw  ParseException("Expected number but encountered ','");
	}
	assert(0); // Encountered unexpected StreamTokenizer type
	return 0;
}

string
WKTReader::getNextEmptyOrOpener(StringTokenizer *tokenizer)
{
	string nextWord=getNextWord(tokenizer);
	if (nextWord=="EMPTY" || nextWord=="(") {
		return nextWord;
	}
	throw  ParseException("Expected 'EMPTY' or '(' but encountered ",nextWord);
}

string
WKTReader::getNextCloserOrComma(StringTokenizer *tokenizer)
{
	string nextWord=getNextWord(tokenizer);
	if (nextWord=="," || nextWord==")") {
		return nextWord;
	}
	throw  ParseException("Expected ')' or ',' but encountered",nextWord);
}

string
WKTReader::getNextCloser(StringTokenizer *tokenizer)
{
	string nextWord=getNextWord(tokenizer);
	if (nextWord==")") {
		return nextWord;
	}
	throw  ParseException("Expected ')' but encountered",nextWord);
}

string
WKTReader::getNextWord(StringTokenizer *tokenizer)
{
	int type=tokenizer->nextToken();
	switch(type){
		case StringTokenizer::TT_EOF:
			throw  ParseException("Expected word but encountered end of stream");
		case StringTokenizer::TT_EOL:
			throw  ParseException("Expected word but encountered end of line");
		case StringTokenizer::TT_NUMBER:
			throw  ParseException("Expected word but encountered number", tokenizer->getNVal());
		case StringTokenizer::TT_WORD:
			return tokenizer->getSVal();
		case '(':
			return "(";
		case ')':
			return ")";
		case ',':
			return ",";
	}
	assert(0);
	//throw  ParseException("Encountered unexpected StreamTokenizer type");
	return "";
}

Geometry*
WKTReader::readGeometryTaggedText(StringTokenizer *tokenizer)
{
	string type = getNextWord(tokenizer);
	if (type=="POINT") {
		return readPointText(tokenizer);
	} else if (type=="LINESTRING") {
		return readLineStringText(tokenizer);
	} else if (type=="LINEARRING") {
		return readLinearRingText(tokenizer);
	} else if (type=="POLYGON") {
		return readPolygonText(tokenizer);
	} else if (type=="MULTIPOINT") {
		return readMultiPointText(tokenizer);
	} else if (type=="MULTILINESTRING") {
		return readMultiLineStringText(tokenizer);
	} else if (type=="MULTIPOLYGON") {
		return readMultiPolygonText(tokenizer);
	} else if (type=="GEOMETRYCOLLECTION") {
		return readGeometryCollectionText(tokenizer);
	}else if (type=="CIRCLE") {
		return readCircleText(tokenizer);
	}else if (type=="ELLIPSE") {
		return readEllipseText(tokenizer);
	}else if (type=="BEZIERSPLINE") {
		return readBezierSplineText(tokenizer);
	}
	throw  ParseException("Unknown type",type);
}

Point*
WKTReader::readPointText(StringTokenizer *tokenizer)
{
	string nextToken=getNextEmptyOrOpener(tokenizer);
	if (nextToken=="EMPTY") {
		return geometryFactory->createPoint(Coordinate::getNull());
	}

	Coordinate coord;
	getPreciseCoordinate(tokenizer, coord);
	getNextCloser(tokenizer);

	return geometryFactory->createPoint(coord);
}

Circle*
WKTReader::readCircleText(StringTokenizer *tokenizer)
{
	string nextToken=getNextEmptyOrOpener(tokenizer);
	if (nextToken=="EMPTY") {
		return geometryFactory->createCircle(0,0);
	}

	Coordinate coordCenter;
	coordCenter.x=getNextNumber(tokenizer);
	coordCenter.y=getNextNumber(tokenizer);
	precisionModel->makePrecise(coordCenter);

	double radius;
	radius = getNextNumber(tokenizer);

	return geometryFactory->createCircle(coordCenter, radius) ;
}

Ellipse*
WKTReader::readEllipseText(StringTokenizer *tokenizer)
{
	string nextToken=getNextEmptyOrOpener(tokenizer);
	if (nextToken=="EMPTY") {
		return geometryFactory->createEllipse(Envelope(0,0,0,0));
	}

	Coordinate coordCenter;
	coordCenter.x=getNextNumber(tokenizer);
	coordCenter.y=getNextNumber(tokenizer);
	precisionModel->makePrecise(coordCenter);

	double axesMajor, axesMinor;
	axesMajor = getNextNumber(tokenizer);
	axesMinor = getNextNumber(tokenizer);

	return geometryFactory->createEllipse(Envelope(coordCenter.x - axesMajor/2, coordCenter.x + axesMajor/2, 
		coordCenter.y - axesMinor/2, coordCenter.y + axesMinor/2)) ;
}

BezierSpline*
WKTReader::readBezierSplineText(StringTokenizer *tokenizer)
{
	std::vector<Coordinate> knots;
	string nextToken=getNextEmptyOrOpener(tokenizer);
	if (nextToken=="EMPTY") {
		return geometryFactory->createBezierSpline(knots);
	}

	long ptCnt = getNextNumber(tokenizer);
	for(int i=0; i<ptCnt; i++)
	{
		Coordinate coord;
		coord.x=getNextNumber(tokenizer);
		coord.y=getNextNumber(tokenizer);
		precisionModel->makePrecise(coord);
		knots.push_back(coord);
	}
	return geometryFactory->createBezierSpline(knots) ;
}

LineString* WKTReader::readLineStringText(StringTokenizer *tokenizer) {
	CoordinateSequence *coords = getCoordinates(tokenizer);
	LineString *ret = geometryFactory->createLineString(coords);
	return ret;
}

LinearRing* WKTReader::readLinearRingText(StringTokenizer *tokenizer) {
	CoordinateSequence *coords = getCoordinates(tokenizer);
	LinearRing *ret;
	ret = geometryFactory->createLinearRing(coords);
	return ret;
}

MultiPoint*
WKTReader::readMultiPointText(StringTokenizer *tokenizer)
{
	string nextToken=getNextEmptyOrOpener(tokenizer);
	if (nextToken=="EMPTY") {
		return geometryFactory->createMultiPoint();
	}

	int tok = tokenizer->peekNextToken();

	if ( tok == StringTokenizer::TT_NUMBER )
	{
		// Try to parse deprecated form "MULTIPOINT(0 0, 1 1)"
		const CoordinateSequenceFactory* csf = \
			geometryFactory->getCoordinateSequenceFactory();
		CoordinateSequence *coords = csf->create(NULL);
		try {
			do {
				Coordinate coord;
				getPreciseCoordinate(tokenizer, coord);
				coords->add(coord);
				nextToken=getNextCloserOrComma(tokenizer);
			} while(nextToken == ",");

			MultiPoint *ret = geometryFactory->createMultiPoint(*coords);
			delete coords;
			return ret;
		} catch (...) {
			delete coords;
			throw;
		}
	}

	else if ( tok == '(' )
	{
		// Try to parse correct form "MULTIPOINT((0 0), (1 1))"
		vector<Geometry *> *points=new vector<Geometry *>();
		try {
			do {
				Point *point=readPointText(tokenizer);
				points->push_back(point);
				nextToken=getNextCloserOrComma(tokenizer);
			} while(nextToken == ",");
			return geometryFactory->createMultiPoint(points);
		} catch (...) {
			// clean up 
			for (size_t i=0; i<points->size(); i++)
			{
				delete (*points)[i];
			}
			delete points;
			throw;
		}
	}

	else 
	{
		stringstream err;
		err << "Unexpected token: ";
		switch (tok)
		{
			case StringTokenizer::TT_WORD:
				err << "WORD " << tokenizer->getSVal();
				break;
			case StringTokenizer::TT_NUMBER:
				err << "NUMBER " << tokenizer->getNVal();
				break;
			case StringTokenizer::TT_EOF:
			case StringTokenizer::TT_EOL:
				err << "EOF or EOL";
				break;
			case '(':
				err << "(";
				break;
			case ')':
				err << ")";
				break;
			case ',':
				err << ",";
				break;
			default:
				err << "??";
				break;
		}
		err << endl;
		throw ParseException(err.str());
		return NULL;
	}
}

Polygon*
WKTReader::readPolygonText(StringTokenizer *tokenizer)
{
	Polygon *poly=NULL;
	LinearRing *shell=NULL;
	string nextToken=getNextEmptyOrOpener(tokenizer);
	if (nextToken=="EMPTY") {
		return geometryFactory->createPolygon(NULL,NULL);
	}

	vector<Geometry *> *holes=new vector<Geometry *>();
	try {
		shell=readLinearRingText(tokenizer);
		nextToken=getNextCloserOrComma(tokenizer);
		while(nextToken==",") {
			LinearRing *hole=readLinearRingText(tokenizer);
			holes->push_back(hole);
			nextToken=getNextCloserOrComma(tokenizer);
		}
		poly = geometryFactory->createPolygon(shell,holes);
	} catch (...) {
		for (unsigned int i=0; i<holes->size(); i++)
			delete (*holes)[i];
		delete holes;
		delete shell;
		throw;
	}
	return poly;
}

MultiLineString* WKTReader::readMultiLineStringText(StringTokenizer *tokenizer) {
	string nextToken=getNextEmptyOrOpener(tokenizer);
	if (nextToken=="EMPTY") {
		return geometryFactory->createMultiLineString(NULL);
	}
	vector<Geometry *> *lineStrings=new vector<Geometry *>();
	LineString *lineString=readLineStringText(tokenizer);
	lineStrings->push_back(lineString);
	nextToken=getNextCloserOrComma(tokenizer);
	while(nextToken==",") {
		LineString *lineString=readLineStringText(tokenizer);
		lineStrings->push_back(lineString);
		nextToken=getNextCloserOrComma(tokenizer);
	}
	MultiLineString *ret = geometryFactory->createMultiLineString(lineStrings);
	//for (int i=0; i<lineStrings->size(); i++) delete (*lineStrings)[i];
	//delete lineStrings;
	return ret;
}

MultiPolygon* WKTReader::readMultiPolygonText(StringTokenizer *tokenizer) {
	string nextToken=getNextEmptyOrOpener(tokenizer);
	if (nextToken=="EMPTY") {
		return geometryFactory->createMultiPolygon(NULL);
	}
	vector<Geometry *> *polygons=new vector<Geometry *>();
	Polygon *polygon=readPolygonText(tokenizer);
	polygons->push_back(polygon);
	nextToken=getNextCloserOrComma(tokenizer);
	while(nextToken==",") {
		Polygon *polygon=readPolygonText(tokenizer);
		polygons->push_back(polygon);
		nextToken=getNextCloserOrComma(tokenizer);
	}
	MultiPolygon *ret = geometryFactory->createMultiPolygon(polygons);
	//for (int i=0; i<polygons->size(); i++) delete (*polygons)[i];
	//delete polygons;
	return ret;
}

GeometryCollection* WKTReader::readGeometryCollectionText(StringTokenizer *tokenizer) {
	string nextToken=getNextEmptyOrOpener(tokenizer);
	if (nextToken=="EMPTY") {
		return geometryFactory->createGeometryCollection(NULL);
	}
	vector<Geometry *> *geoms=new vector<Geometry *>();
	Geometry *geom;
	geom=readGeometryTaggedText(tokenizer);
	geoms->push_back(geom);
	nextToken=getNextCloserOrComma(tokenizer);
	while(nextToken==",") {
		geom=readGeometryTaggedText(tokenizer);
		geoms->push_back(geom);
		nextToken=getNextCloserOrComma(tokenizer);
	}
	GeometryCollection *ret = geometryFactory->createGeometryCollection(geoms);
	//for (int i=0; i<geoms->size(); i++) delete (*geoms)[i];
	//delete geoms;
	return ret;
}

} // namespace GEOMETRY.io
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.42  2006/04/26 16:35:40  strk
 * Had WKTReader accept correct form for MultiPoint
 *
 * Revision 1.41  2006/04/10 12:05:35  strk
 * Added inline-replicator implementation files to make sure
 * functions in .inl files are still available out-of-line.
 * A side effect is this should fix MingW build.
 *
 * Revision 1.40  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.39  2006/03/22 16:58:35  strk
 * Removed (almost) all inclusions of geom.h.
 * Removed obsoleted .cpp files.
 * Fixed a bug in WKTReader not using the provided CoordinateSequence
 * implementation, optimized out some memory allocations.
 *
 **********************************************************************/
