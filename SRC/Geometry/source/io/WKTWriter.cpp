/**********************************************************************
 * $Id: WKTWriter.cpp 1820 2006-09-06 16:54:23Z mloskot $
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

#include <Geometry/io/WKTWriter.h>
#include <Geometry/io/Writer.h>
#include <Geometry/geom/Coordinate.h>
#include <Geometry/geom/Point.h>
#include <Geometry/geom/LinearRing.h>
#include <Geometry/geom/LineString.h>
#include <Geometry/geom/Polygon.h>
#include <Geometry/geom/MultiPoint.h>
#include <Geometry/geom/MultiLineString.h>
#include <Geometry/geom/MultiPolygon.h>
#include <Geometry/geom/CoordinateSequence.h>
#include <Geometry/geom/PrecisionModel.h>
#include <Geometry/geom/Circle.h>
#include <Geometry/geom/Ellipse.h>
#include <Geometry/geom/BezierSpline.h>

#include <typeinfo>
#include <cstdio> // should avoid this
#include <string>
#include <sstream>
#include <cassert>

#define PRINT_Z 0

using namespace std;
using namespace GEOMETRY::geom;

namespace GEOMETRY {
namespace io { // geos.io

WKTWriter::WKTWriter() {
	isFormatted=false;
	level=0;
	formatter="%f";
}

WKTWriter::~WKTWriter() {}

/*static*/
string
WKTWriter::toLineString(const CoordinateSequence& seq)
{
	stringstream buf("LINESTRING ", ios_base::in|ios_base::out);
	unsigned int npts = seq.getSize();
	if ( npts == 0 )
	{
		buf << "EMPTY";
	}
	else
	{
		buf << "(";
		for (unsigned int i=0; i<npts; ++i)
		{
			if (i) buf << ", ";
			buf << seq.getX(i) << " " << seq.getY(i);
#if PRINT_Z
			buf << seq.getZ(i);
#endif
		}
		buf << ")";
	}

	return buf.str();
}

/*static*/
string
WKTWriter::toLineString(const Coordinate& p0, const Coordinate& p1)
{
	stringstream ret("LINESTRING (", ios_base::in|ios_base::out);
	ret << p0.x << " " << p0.y;
#if PRINT_Z
	ret << " " << p0.z;
#endif
	ret << ", " << p1.x << " " << p1.y;
#if PRINT_Z
	ret << " " << p1.z;
#endif

	return ret.str();
}

/*static*/
string
WKTWriter::toPoint(const Coordinate& p0)
{
	stringstream ret("POINT (", ios_base::in|ios_base::out);
#if PRINT_Z
	ret << p0.x << " " << p0.y  << " " << p0.z << " )";
#else
	ret << p0.x << " " << p0.y  << " )";
#endif
	return ret.str();
}

string
WKTWriter::createFormatter(const PrecisionModel* precisionModel)
{
	// the default number of decimal places is 16, which is sufficient
	// to accomodate the maximum precision of a double.
	int decimalPlaces = precisionModel->getMaximumSignificantDigits();
	string fmt="%.";
	char buffer[255];
	sprintf(buffer,"%i",decimalPlaces);
	fmt.append(buffer);
	fmt.append("f");
	return fmt;
}

//string WKTWriter::stringOfChar(char ch, int count) {
	//string str="";
	//for (int i=0;i<count;i++) str+=ch;
	//return string(count, ch);
//}

string WKTWriter::write(const Geometry *geometry) {
	Writer sw;
//	try {
		writeFormatted(geometry,false,&sw);
//	} catch (const IOException ex) {
//		Assert::shouldNeverReachHere();
//	}
	string res=sw.toString();
	return res;
}

void WKTWriter::write(const Geometry *geometry, Writer *writer) {
	writeFormatted(geometry, false, writer);
}

string WKTWriter::writeFormatted(const Geometry *geometry) {
	Writer sw;
	writeFormatted(geometry, true, &sw);
	return sw.toString();
}

void WKTWriter::writeFormatted(const Geometry *geometry, Writer *writer) {
	writeFormatted(geometry, true, writer);
}

void WKTWriter::writeFormatted(const Geometry *geometry, bool isFormatted, Writer *writer) {
	this->isFormatted=isFormatted;
	formatter=createFormatter(geometry->getPrecisionModel());
	appendGeometryTaggedText(geometry, 0, writer);
}

void
WKTWriter::appendGeometryTaggedText(const Geometry *geometry, int level,
		Writer *writer)
{
	indent(level, writer);
	if (typeid(*geometry)==typeid(Point)) {
		Point* point=(Point*)geometry;
		appendPointTaggedText(point->getCoordinate(),level,writer);
	} else if (typeid(*geometry)==typeid(LinearRing)) {
		appendLinearRingTaggedText((LinearRing*) geometry, level, writer);
	} else if (typeid(*geometry)==typeid(LineString)) {
		appendLineStringTaggedText((LineString*)geometry, level, writer);
	} else if (typeid(*geometry)==typeid(LinearRing)) {
		appendLinearRingTaggedText((LinearRing*)geometry, level, writer);
	} else if (typeid(*geometry)==typeid(Polygon)) {
		appendPolygonTaggedText((Polygon*)geometry, level, writer);
	} else if (typeid(*geometry)==typeid(MultiPoint)) {
		appendMultiPointTaggedText((MultiPoint*)geometry, level, writer);
	} else if (typeid(*geometry)==typeid(MultiLineString)) {
		appendMultiLineStringTaggedText((MultiLineString*)geometry, level, writer);
	} else if (typeid(*geometry)==typeid(MultiPolygon)) {
		appendMultiPolygonTaggedText((MultiPolygon*)geometry, level, writer);
	} else if (typeid(*geometry)==typeid(GeometryCollection)) {
		appendGeometryCollectionTaggedText((GeometryCollection*)geometry, level, writer);
	} else if (typeid(*geometry)==typeid(Circle)) {
		appendCircleTaggedText((Circle*)geometry, level, writer);
	} else if (typeid(*geometry)==typeid(Ellipse)) {
		appendEllipseTaggedText((Ellipse*)geometry, level, writer);
	} else if (typeid(*geometry)==typeid(BezierSpline)) {
		appendBezierSplineTaggedText((BezierSpline*)geometry, level, writer);
	} else {
		assert(0); // Unsupported Geometry implementation
	}
}

/*protected*/
void
WKTWriter::appendPointTaggedText(const Coordinate* coordinate, int level,
		Writer *writer)
{
	writer->write("POINT ");
	appendPointText(coordinate, level, writer);
}

void
WKTWriter::appendLineStringTaggedText(const LineString *lineString, int level,
		Writer *writer)
{
	writer->write("LINESTRING ");
	appendLineStringText(lineString, level, false, writer);
}

/*
 * Converts a <code>LinearRing</code> to &lt;LinearRing Tagged Text&gt;
 * format, then appends it to the writer.
 *
 * @param  linearRing  the <code>LinearRing</code> to process
 * @param  writer      the output writer to append to
 */
void WKTWriter::appendLinearRingTaggedText(const LinearRing* linearRing, int level, Writer *writer) {
	writer->write("LINEARRING ");
	appendLineStringText((LineString*)linearRing, level, false, writer);
}

void WKTWriter::appendPolygonTaggedText(const Polygon *polygon, int level, Writer *writer) {
	writer->write("POLYGON ");
	appendPolygonText(polygon, level, false, writer);
}

void WKTWriter::appendMultiPointTaggedText(const MultiPoint *multipoint, int level, Writer *writer) {
	writer->write("MULTIPOINT ");
	appendMultiPointText(multipoint, level, writer);
}

void WKTWriter::appendMultiLineStringTaggedText(const MultiLineString *multiLineString, int level,Writer *writer) {
	writer->write("MULTILINESTRING ");
	appendMultiLineStringText(multiLineString, level, false, writer);
}

void WKTWriter::appendMultiPolygonTaggedText(const MultiPolygon *multiPolygon, int level, Writer *writer) {
	writer->write("MULTIPOLYGON ");
	appendMultiPolygonText(multiPolygon, level, writer);
}

void WKTWriter::appendGeometryCollectionTaggedText(const GeometryCollection *geometryCollection, int level,Writer *writer) {
	writer->write("GEOMETRYCOLLECTION ");
	appendGeometryCollectionText(geometryCollection, level, writer);
}

void WKTWriter::appendCircleTaggedText(const Circle *circle, int level,Writer *writer) {
	writer->write("CIRCLE ");
	appendCircleText(circle, level, writer);
}

void WKTWriter::appendEllipseTaggedText(const Ellipse *ellipse, int level,Writer *writer) {
	writer->write("ELLIPSE ");
	appendEllipseText(ellipse, level, writer);
}

void WKTWriter::appendBezierSplineTaggedText(const BezierSpline *bezierSpline, int level,Writer *writer) {
	writer->write("BEZIERSPLINE ");
	appendBezierSplineText(bezierSpline, level, writer);
}


void
WKTWriter::appendPointText(const Coordinate* coordinate, int /*level*/,
		Writer *writer)
{
	if (coordinate==NULL) {
		writer->write("EMPTY");
	} else {
		writer->write("(");
		appendCoordinate(coordinate, writer);
		writer->write(")");
	}
}

void
WKTWriter::appendCoordinate(const Coordinate* coordinate,
		Writer *writer)
{
	string out="";
	out+=writeNumber(coordinate->x);
	out+=" ";
	out+=writeNumber(coordinate->y);
#if PRINT_Z
	out+=" ";
	out+=writeNumber(coordinate->z);
#endif
	writer->write(out);
}

string WKTWriter::writeNumber(double d) {
	string out="";
	char buffer[255];
	sprintf(buffer,formatter.c_str(),d);
	out.append(buffer);
	out.append("");
	return out;
}

void
WKTWriter::appendLineStringText(const LineString *lineString, int level,
		bool doIndent, Writer *writer)
{
	if (lineString->isEmpty()) {
		writer->write("EMPTY");
	} else {
		if (doIndent) indent(level, writer);
		writer->write("(");
		for(size_t i=0, n=lineString->getNumPoints(); i<n; ++i)
		{
			if (i>0) {
				writer->write(", ");
				if (i%10==0) indent(level + 2, writer);
			}
			appendCoordinate(&(lineString->getCoordinateN(i)), writer);
		}
		writer->write(")");
	}
}

void
WKTWriter::appendPolygonText(const Polygon *polygon, int /*level*/,
		bool indentFirst, Writer *writer)
{
	if (polygon->isEmpty()) {
		writer->write("EMPTY");
	} else {
		if (indentFirst) indent(level, writer);
		writer->write("(");
		appendLineStringText(polygon->getExteriorRing(), level, false, writer);
		for (size_t i=0, n=polygon->getNumInteriorRing(); i<n; ++i)
		{
			writer->write(", ");
			const LineString *ls=polygon->getInteriorRingN(i);
			appendLineStringText(ls, level + 1, true, writer);
		}
		writer->write(")");
	}
}

void
WKTWriter::appendMultiPointText(const MultiPoint *multiPoint,
		int /*level*/, Writer *writer)
{
	if (multiPoint->isEmpty()) {
		writer->write("EMPTY");
	} else {
		writer->write("(");
		for (unsigned int i=0, n=multiPoint->getNumGeometries();
				i<n; i++)
		{
			if (i > 0)
			{
				writer->write(", ");
			}
			appendCoordinate(
				((Point* )multiPoint->getGeometryN(i))->getCoordinate(),
				writer);
		}
		writer->write(")");
	}
}

void WKTWriter::appendMultiLineStringText(const MultiLineString *multiLineString, int level, bool indentFirst,
											Writer *writer) {
	if (multiLineString->isEmpty()) {
		writer->write("EMPTY");
	} else {
		int level2=level;
		bool doIndent=indentFirst;
		writer->write("(");
		for (unsigned int i=0, n=multiLineString->getNumGeometries();
				i<n; i++)
		{
			if (i>0) {
				writer->write(", ");
				level2=level+1;
				doIndent=true;
			}
			appendLineStringText((LineString *) multiLineString->getGeometryN(i), level2, doIndent, writer);
		}
		writer->write(")");
	}
}

void WKTWriter::appendMultiPolygonText(const MultiPolygon *multiPolygon, int level, Writer *writer) {
	if (multiPolygon->isEmpty()) {
		writer->write("EMPTY");
	} else {
		int level2=level;
		bool doIndent=false;
		writer->write("(");
		for (unsigned int i=0, n=multiPolygon->getNumGeometries();
				i < n; i++)
		{
			if (i>0) {
				writer->write(", ");
				level2=level+1;
				doIndent=true;
			}
			appendPolygonText((Polygon *) multiPolygon->getGeometryN(i), level2, doIndent, writer);
		}
		writer->write(")");
	}
}

void
WKTWriter::appendGeometryCollectionText(
		const GeometryCollection *geometryCollection,
		int level,
		Writer *writer)
{
	if (geometryCollection->isEmpty()) {
		writer->write("EMPTY");
	} else {
		int level2=level;
		writer->write("(");
		for (unsigned int i=0, n=geometryCollection->getNumGeometries();
				i < n ; ++i)
		{
			if (i>0) {
				writer->write(", ");
				level2=level+1;
			}
			appendGeometryTaggedText(geometryCollection->getGeometryN(i),level2,writer);
		}
		writer->write(")");
	}
}

void
WKTWriter::appendCircleText(const Circle* circle, int /*level*/,
						   Writer *writer)
{
	if (circle==NULL) {
		writer->write("EMPTY");
	} else {
		writer->write("(");

		string out="";
		out+=writeNumber(circle->GetCenterPoint().x);
		out+=" ";
		out+=writeNumber(circle->GetCenterPoint().y);
		out+=" ";
		out+=writeNumber(circle->GetRadius());
			
		writer->write(out);
		
		writer->write(")");
	}
}

void
WKTWriter::appendEllipseText(const Ellipse* ellipse, int /*level*/,
							Writer *writer)
{
	if (ellipse==NULL) {
		writer->write("EMPTY");
	} else {
		writer->write("(");

		string out="";
		out+=writeNumber(ellipse->GetCenterPoint() .x);
		out+=" ";
		out+=writeNumber(ellipse->GetCenterPoint().y);
		
		double axesMajor, axesMinor;
		ellipse->GetAxes(&axesMajor, &axesMinor);
		out+=" ";
		out+=writeNumber(axesMajor);
		out+=" ";
		out+=writeNumber(axesMinor);

		writer->write(out);

		writer->write(")");
	}
}

void
WKTWriter::appendBezierSplineText(const BezierSpline* bezierSpline, int /*level*/,
							Writer *writer)
{
	if (bezierSpline==NULL) {
		writer->write("EMPTY");
	} else {
		writer->write("(");

		std::vector<Coordinate> knots;
		bezierSpline->Getknots(knots);
		long ptCnt = knots.size();
		string out="";
		out+=writeNumber(ptCnt);

		for(int i=0; i<ptCnt; i++)
		{
			out+=" ";
			out+=writeNumber(knots[i].x);
			out+=" ";
			out+=writeNumber(knots[i].y);
		}

		writer->write(out);


		writer->write(")");
	}
}

void WKTWriter::indent(int level, Writer *writer) {
	if (!isFormatted || level<=0) return;
	writer->write("\n");
	//writer->write(stringOfChar(' ', INDENT * level));
	writer->write(string(INDENT * level, ' '));
}

} // namespace GEOMETRY.io
} // namespace GEOMETRY

/**********************************************************************
 * $Log$
 * Revision 1.35  2006/06/12 16:55:53  strk
 * fixed compiler warnings, fixed some methods to omit unused parameters.
 *
 * Revision 1.34  2006/06/08 17:58:57  strk
 * Polygon::getNumInteriorRing() return size_t, Polygon::interiorRingN() takes size_t.
 *
 * Revision 1.33  2006/06/01 11:49:36  strk
 * Reduced installed headers form geomgraph namespace
 *
 * Revision 1.32  2006/04/28 11:12:31  strk
 * removed warnings related to change in getNumPoints() return type.
 *
 * Revision 1.31  2006/04/07 09:54:30  strk
 * Geometry::getNumGeometries() changed to return 'unsigned int'
 * rather then 'int'
 *
 * Revision 1.30  2006/03/22 16:58:35  strk
 * Removed (almost) all inclusions of geom.h.
 * Removed obsoleted .cpp files.
 * Fixed a bug in WKTReader not using the provided CoordinateSequence
 * implementation, optimized out some memory allocations.
 *
 * Revision 1.29  2006/03/20 18:18:15  strk
 * io.h header split
 *
 * Revision 1.28  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 * Revision 1.27  2006/03/06 19:40:47  strk
 * GEOMETRY::util namespace. New GeometryCollection::iterator interface, many cleanups.
 *
 * Revision 1.26  2006/03/06 15:23:14  strk
 * GEOMETRY::io namespace
 *
 * Revision 1.25  2006/03/03 10:46:21  strk
 * Removed 'using namespace' from headers, added missing headers in .cpp files, removed useless includes in headers (bug#46)
 *
 * Revision 1.24  2006/02/09 15:52:47  strk
 * GEOSException derived from std::exception; always thrown and cought by const ref.
 *
 * Revision 1.23  2006/02/08 17:18:28  strk
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
 * Revision 1.22  2006/01/18 17:46:57  strk
 * Fixed leak in ::writeFormatted(Geometry *)
 *
 * Revision 1.21  2004/12/08 13:54:43  strk
 * gcc warnings checked and fixed, general cleanups.
 *
 * Revision 1.20  2004/10/21 22:29:54  strk
 * Indentation changes and some more COMPUTE_Z rules
 *
 * Revision 1.19  2004/10/20 17:32:14  strk
 * Initial approach to 2.5d intersection()
 *
 * Revision 1.18  2004/07/19 13:19:31  strk
 * Documentation fixes
 *
 * Revision 1.17  2004/07/07 09:38:12  strk
 * Dropped WKTWriter::stringOfChars (implemented by std::string).
 * Dropped WKTWriter default constructor (internally created GeometryFactory).
 * Updated XMLTester to respect the changes.
 * Main documentation page made nicer.
 *
 * Revision 1.16  2004/07/02 13:28:27  strk
 * Fixed all #include lines to reflect headers layout change.
 * Added client application build tips in README.
 *
 * Revision 1.15  2004/03/18 10:42:44  ybychkov
 * "IO" and "Util" upgraded to JTS 1.4
 * "Geometry" partially upgraded.
 *
 * Revision 1.14  2003/11/07 01:23:42  pramsey
 * Add standard CVS headers licence notices and copyrights to all cpp and h
 * files.
 *
 *
 **********************************************************************/


