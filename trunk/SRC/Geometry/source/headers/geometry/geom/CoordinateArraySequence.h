/**********************************************************************
 * $Id: CoordinateArraySequence.h 1958 2007-01-09 15:08:22Z strk $
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

#ifndef GEOMETRY_GEOM_COORDINATEARRAYSEQUENCE_H
#define GEOMETRY_GEOM_COORDINATEARRAYSEQUENCE_H

#include <vector>

//#include <Geometry/platform.h>
#include <Geometry/geom/CoordinateSequence.h>

#include <Geometry/inline.h>

// Forward declarations
namespace GEOMETRY {
	namespace geom { 
		class Coordinate;
	}
}


namespace GEOMETRY {
namespace geom { // geos.geom

/// The default implementation of CoordinateSequence
class CoordinateArraySequence : public CoordinateSequence {
public:

	CoordinateArraySequence(const CoordinateArraySequence &cl);

	CoordinateSequence *clone() const;

	//const Coordinate& getCoordinate(int pos) const;
	Coordinate& getAt(size_t pos) const;

	/// Copy Coordinate at position i to Coordinate c
	virtual void getAt(size_t i, Coordinate& c) const;

	//int size() const;
	size_t getSize() const;
	const std::vector<Coordinate>* toVector() const;

	/// Construct an empty sequence
	CoordinateArraySequence();

	/// Construct sequence taking ownership of given Coordinate vector
	CoordinateArraySequence(std::vector<Coordinate> *coords);

	/// Construct sequence allocating space for n coordinates
	CoordinateArraySequence(size_t n);

	~CoordinateArraySequence();

	bool isEmpty() const;

	void add(const Coordinate& c);

	virtual void add(const Coordinate& c, bool allowRepeated);

	void setAt(const Coordinate& c, size_t pos);

	void deleteAt(size_t pos);

	std::string toString() const;

	void setPoints(const std::vector<Coordinate> &v);

	double getOrdinate(size_t index,
			size_t ordinateIndex) const;

	void setOrdinate(size_t index, size_t ordinateIndex,
			double value);

	void expandEnvelope(Envelope &env) const;

	size_t getDimension() const { return 3; }

	void apply_rw(const CoordinateFilter *filter); 

	void apply_ro(CoordinateFilter *filter) const; 

	virtual CoordinateSequence& removeRepeatedPoints();

	virtual void insert(size_t pos,const Coordinate& c);

	//������еĵ�
	virtual void ClearAll();

	Coordinate *GetPtPointer(size_t i);

private:
	std::vector<Coordinate> *vect;
};

/// This is for backward API compatibility
typedef CoordinateArraySequence DefaultCoordinateSequence;

} // namespace GEOMETRY.geom
} // namespace GEOMETRY

//#ifdef GEOS_INLINE
//# include "Geometry/geom/CoordinateArraySequence.inl"
//#endif

#endif // ndef GEOS_GEOM_COORDINATEARRAYSEQUENCE_H

/**********************************************************************
 * $Log$
 * Revision 1.4  2006/06/12 10:10:39  strk
 * Fixed getGeometryN() to take size_t rather then int, changed unsigned int parameters to size_t.
 *
 * Revision 1.3  2006/05/03 08:58:34  strk
 * added new non-static CoordinateSequence::removeRepeatedPoints() mutator.
 *
 * Revision 1.2  2006/03/24 09:52:41  strk
 * USE_INLINE => GEOS_INLINE
 *
 * Revision 1.1  2006/03/09 16:46:49  strk
 * GEOMETRY::geom namespace definition, first pass at headers split
 *
 **********************************************************************/
