/**********************************************************************
 * $Id: LineSegment.h 1820 2006-09-06 16:54:23Z mloskot $
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

#ifndef GEOMETRY_GEOM_LINESEGMENT_H
#define GEOMETRY_GEOM_LINESEGMENT_H

#include <Geometry/geom/Coordinate.h> // for composition

#include <Geometry/inline.h>

#include <iostream> // for ostream

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class CoordinateSequence;
	}
}

namespace GEOMETRY {
namespace geom { // GEOMETRY::geom

/**
 * Represents a line segment defined by two Coordinate.
 * Provides methods to compute various geometric properties
 * and relationships of line segments.
 * 
 * This class is designed to be easily mutable (to the extent of
 * having its contained points public).
 * This supports a common pattern of reusing a single LineSegment
 * object as a way of computing segment properties on the
 * segments defined by arrays or lists of {@link Coordinate}s.
 *
 * TODO: have this class keep pointers rather then real Coordinates ?
 */
class LineSegment {
public:

	friend std::ostream& operator<< (std::ostream& o, const LineSegment& l);

	Coordinate p0; /// Segment start

	Coordinate p1; /// Segemnt end

	LineSegment();

	LineSegment(const LineSegment &ls);

	/// Constructs a LineSegment with the given start and end Coordinates.
	LineSegment(const Coordinate& c0, const Coordinate& c1);

	virtual ~LineSegment();

	void setCoordinates(const Coordinate& c0, const Coordinate& c1);

	// obsoleted, use operator[] instead
	//const Coordinate& getCoordinate(size_t i) const;

	const Coordinate& operator[](size_t i) const;
	Coordinate& operator[](size_t i);

	void setCoordinates(const LineSegment& ls);

	/// Computes the length of the line segment.
	double getLength() const;

	/// Tests whether the segment is horizontal.
	//
	/// @return <code>true</code> if the segment is horizontal
	///
	bool isHorizontal() const;

	/// Tests whether the segment is vertical.
	//
	/// @return <code>true</code> if the segment is vertical
	///
	bool isVertical() const;

	/**
	 * Determines the orientation of a LineSegment relative to this segment.
	 * The concept of orientation is specified as follows:
	 * Given two line segments A and L,
	 * <ul
	 * <li>A is to the left of a segment L if A lies wholly in the
	 * closed half-plane lying to the left of L
	 * <li>A is to the right of a segment L if A lies wholly in the
	 * closed half-plane lying to the right of L
	 * <li>otherwise, A has indeterminate orientation relative to L.
	 *     This happens if A is collinear with L or if A crosses
	 *     the line determined by L.
	 * </ul>
	 *
	 * @param seg the LineSegment to compare
	 *
	 * @return 1 if seg is to the left of this segment
	 * @return -1 if seg is to the right of this segment
	 * @return 0 if seg has indeterminate orientation relative
	 *	     to this segment
	 */
	int orientationIndex(const LineSegment& seg) const;

	int orientationIndex(const LineSegment* seg) const;

	/// Reverses the direction of the line segment.
	void reverse();

	/// Puts the line segment into a normalized form.
	//
	/// This is useful for using line segments in maps and indexes when
	/// topological equality rather than exact equality is desired.
	///
	void normalize();

	/// @return the angle this segment makes with the x-axis (in radians)
	double angle() const;

	/// Computes the distance between this line segment and another one.
	double distance(const LineSegment& ls) const;

	/// Computes the distance between this line segment and a point.
	double distance(const Coordinate& p) const;

	/** \brief
	 * Computes the perpendicular distance between the (infinite)
	 * line defined by this line segment and a point.
	 */
	double distancePerpendicular(const Coordinate& p) const;

	/**
	 * Compute the projection factor for the projection of the point p
	 * onto this LineSegment.  The projection factor is the constant k
	 * by which the vector for this segment must be multiplied to
	 * equal the vector for the projection of p.
	 */
	double projectionFactor(const Coordinate& p) const;

	/** \brief
	 * Compute the projection of a point onto the line determined
	 * by this line segment.
	 * 
	 * Note that the projected point
	 * may lie outside the line segment.  If this is the case,
	 * the projection factor will lie outside the range [0.0, 1.0].
	 */
	void project(const Coordinate& p, Coordinate& ret) const;

	/** \brief
	 * Project a line segment onto this line segment and return the resulting
	 * line segment. 
	 *
	 * The returned line segment will be a subset of
	 * the target line line segment.  This subset may be null, if
	 * the segments are oriented in such a way that there is no projection.
	 * 
	 * Note that the returned line may have zero length (i.e. the same endpoints).
	 * This can happen for instance if the lines are perpendicular to one another.
	 *
	 * @param seg the line segment to project
	 * @param ret the projected line segment
	 * @return true if there is an overlap, false otherwise
	 */
	bool project(const LineSegment& seg, LineSegment& ret) const;

	/// Computes the closest point on this line segment to another point.
	//
	/// @param p the point to find the closest point to
	/// @param ret the Coordinate to which the closest point on the line segment
	///            to the point p will be written
	///
	void closestPoint(const Coordinate& p, Coordinate& ret) const;

	/** \brief
	 * Compares this object with the specified object for order.
	 *
	 * Uses the standard lexicographic ordering for the points in the LineSegment.
	 *
	 * @param  o  the LineSegment with which this LineSegment
	 *            is being compared
	 * @return a negative integer, zero, or a positive integer as this
	 *         LineSegment is less than, equal to, or greater than the
	 *         specified LineSegment
	 */
	int compareTo(const LineSegment& other) const;

	/** \brief
	 *  Returns <code>true</code> if <code>other</code> is
	 *  topologically equal to this LineSegment (e.g. irrespective
	 *  of orientation).
	 *
	 * @param  other  a <code>LineSegment</code> with which to do the comparison.
	 * @return true if other is a LineSegment
	 *      with the same values for the x and y ordinates.
	 */
	bool equalsTopo(const LineSegment& other) const;

	/**
	 * Computes the closest points on two line segments.
	 * @param p the point to find the closest point to
	 * @return a pair of Coordinates which are the closest points on
	 * the line segments.
	 * The returned CoordinateSequence must be deleted by caller
	 */
	CoordinateSequence* closestPoints(const LineSegment& line);

	CoordinateSequence* closestPoints(const LineSegment* line);

	/**
	 * Computes an intersection point between two segments,
	 * if there is one.
	 * There may be 0, 1 or many intersection points between two segments.
	 * If there are 0, null is returned. If there is 1 or more, a single
	 * one is returned (chosen at the discretion of the algorithm). 
	 * If more information is required about the details of the
	 * intersection, the LineIntersector class should be used.
	 *
	 * @param line
	 * @param coord the Coordinate to write the result into
	 * @return true if an intersection was found, false otherwise
	 */
	bool intersection(const LineSegment& line, Coordinate& coord) const;

};

std::ostream& operator<< (std::ostream& o, const LineSegment& l);

/// Checks if two LineSegment are equal (2D only check)
bool operator==(const LineSegment& a, const LineSegment& b);


} // namespace GEOMETRY::geom
} // namespace GEOMETRY

#ifdef GEOS_INLINE
# include "Geometry/geom/LineSegment.inl"
#endif

#endif // ndef GEOS_GEOM_LINESEGMENT_H

/**********************************************************************
 * $Log$
 * Revision 1.8  2006/07/21 14:49:58  strk
 * Fixed typo in comment
 *
 * Revision 1.7  2006/06/12 10:10:39  strk
 * Fixed getGeometryN() to take size_t rather then int, changed unsigned int parameters to size_t.
 *
 * Revision 1.6  2006/04/12 17:19:56  strk
 * Ported TaggedLineStringSimplifier class, made LineSegment class
 * polymorphic to fix derivation of TaggedLineSegment
 *
 * Revision 1.5  2006/03/28 09:14:12  strk
 * Headers inclusion fix.
 *
 * Revision 1.4  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.3  2006/03/16 13:28:22  strk
 * obsoleted getCoordinate(), replaced by operator[]
 *
 * Revision 1.2  2006/03/13 22:33:09  strk
 * Added missing forward declarations
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/
