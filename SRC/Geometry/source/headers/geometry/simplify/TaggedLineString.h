/**********************************************************************
 * $Id: TaggedLineString.h 1820 2006-09-06 16:54:23Z mloskot $
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2006 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 *
 * Last port: simplify/TaggedLineString.java rev. 1.2 (JTS-1.7.1)
 *
 **********************************************************************
 *
 * NOTES: This class can be optimized to work with vector<Coordinate*>
 *        rather then with CoordinateSequence. Also, LineSegment should
 *        be replaced with a class not copying Coordinates.
 *
 **********************************************************************/

#ifndef _GEOS_SIMPLIFY_TAGGEDLINESTRING_H_
#define _GEOS_SIMPLIFY_TAGGEDLINESTRING_H_ 

#include <vector>
#include <memory>

// Forward declarations
namespace GEOMETRY {
	namespace geom {
		class Coordinate;
		class CoordinateSequence;
		class Geometry;
		class LineString;
		class LinearRing;
	}
	namespace simplify {
		class TaggedLineSegment;
	}
}

namespace GEOMETRY {
namespace simplify { // GEOMETRY::simplify


/** \brief
 *
 * Contains and owns a list of TaggedLineSegments
 *
 */
class TaggedLineString {

public:

	typedef std::vector<geom::Coordinate> CoordVect;
	
	typedef std::auto_ptr<CoordVect> CoordVectPtr;

	typedef geom::CoordinateSequence CoordSeq;

	typedef std::auto_ptr<geom::CoordinateSequence> CoordSeqPtr;

	TaggedLineString(const geom::LineString* nParentLine,
			size_t minimumSize=2);

	~TaggedLineString();

	size_t getMinimumSize() const;

	const geom::LineString* getParent() const;

	const CoordSeq* getParentCoordinates() const;

	CoordSeqPtr getResultCoordinates() const;

	size_t getResultSize() const;

	TaggedLineSegment* getSegment(size_t);

	const TaggedLineSegment* getSegment(size_t) const;

	std::vector<TaggedLineSegment*>& getSegments();

	const std::vector<TaggedLineSegment*>& getSegments() const;

	void addToResult(std::auto_ptr<TaggedLineSegment> seg);

	std::auto_ptr<geom::Geometry> asLineString() const;

	std::auto_ptr<geom::Geometry> asLinearRing() const;

private:

	const geom::LineString* parentLine;

	// TaggedLineSegments owned by this object
	std::vector<TaggedLineSegment*> segs;

	// TaggedLineSegments owned by this object
	std::vector<TaggedLineSegment*> resultSegs;

	size_t minimumSize;

	void init();

	static CoordVectPtr extractCoordinates(
			const std::vector<TaggedLineSegment*>& segs);

	// Copying is turned off
	TaggedLineString(const TaggedLineString&);
	TaggedLineString& operator= (const TaggedLineString&);

};

} // namespace GEOMETRY::simplify
} // namespace GEOMETRY

#endif // _GEOS_SIMPLIFY_TAGGEDLINESTRING_H_ 

/**********************************************************************
 * $Log$
 * Revision 1.7  2006/06/12 11:29:23  strk
 * unsigned int => size_t
 *
 * Revision 1.6  2006/04/13 21:52:34  strk
 * Many debugging lines and assertions added. Fixed bug in TaggedLineString class.
 *
 * Revision 1.5  2006/04/13 16:04:10  strk
 * Made TopologyPreservingSimplifier implementation successfully build
 *
 * Revision 1.4  2006/04/13 09:21:45  mloskot
 * Removed definition of copy ctor and assignment operator for TaggedLineString class.
 * According to following rule: Declaring, but not defining, private copy operations has
 * the effect of "turning off" copying for the class.
 *
 * Revision 1.3  2006/04/12 17:19:57  strk
 * Ported TaggedLineStringSimplifier class, made LineSegment class
 * polymorphic to fix derivation of TaggedLineSegment
 *
 * Revision 1.2  2006/04/12 15:20:37  strk
 * LineSegmentIndex class
 *
 * Revision 1.1  2006/04/12 14:22:12  strk
 * Initial implementation of TaggedLineSegment and TaggedLineString classes
 *
 **********************************************************************/
