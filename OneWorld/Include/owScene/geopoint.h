/**
* osgGIS - GIS Library for OpenSceneGraph
* Copyright 2007 Glenn Waldron and Pelican Ventures, Inc.
* http://osggis.org
*
* osgGIS is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#ifndef _OWSCENES_GEOPOINT
#define _OWSCENES_GEOPOINT 1

#include <owScene/Export.h>

#include <owUtil/SpatialReference.h>
#include <owUtil/GeoExtent.h>

#include <osg/Vec3d>
#include <osg/Vec2d>
#include <vector>

using namespace owUtil;

namespace owScene
{
	/**
	* A 2D or 3D georeferenced point in space.
	*/
	class OWSCENE_EXPORT GeoPoint : public osg::Vec3d
	{
	public:
		/**
		* Constructs a new invalid point.
		*/
		GeoPoint();

		/**
		* Copy constructor.
		*/
		GeoPoint( const GeoPoint& to_copy );

		/**
		* Creates a new 2D georeferenced point.
		* @param input
		*      2D point data
		*/
		GeoPoint( const osg::Vec2d& input);

		/**
		* Create a new 3D georeferenced point.
		* @param input
		*      3D point data
		*/
		GeoPoint( const osg::Vec3d& input);

		/**
		* Creates a new 2D georeferenced point.
		* @param x, y
		*      2D point data
		*/
		GeoPoint( double x, double y);

		/**
		* Create a new 3D georeferenced point.
		* @param x, y, z
		*      3D point data
		*/
		GeoPoint( double x, double y, double z);

		/**
		* Returns true if the point contains valid data.
		*/
		bool isValid() const;

		/**
		* Returns the dimensionality of the point (2 or 3)
		*/
		unsigned int getDim() const;

		/**
		* Sets the dimensionality of the point (2 or 3)
		*/
		void setDim( int value );

		/**
		* Gets a readable representation of the point
		*/
		std::string toString() const;

		/**
		* Returns true if this point is mathematically equivalent to another.
		*/
		bool operator == ( const GeoPoint& rhs ) const;

	public:
		/**
		* Creates an invalid point.
		*/
		static GeoPoint invalid();

		virtual ~GeoPoint();

	private:
		unsigned int dim;
	};

	class GeoPointList : public std::vector<GeoPoint>
	{
	public:
		GeoPointList() { }
		GeoPointList( int cap ) : std::vector<GeoPoint>( cap ) { }

	public:
		bool intersects( const GeoExtent* e ) const;

		/**
		* Returns true is the point list is "closed", i.e. the last point
		* is equal to the first (in 2D)
		*/
		bool isClosed() const;
	};

	class GeoPartVisitor
	{
	public:
		GeoPartVisitor() { }
		virtual ~GeoPartVisitor() { }
		virtual bool visitPart( GeoPointList& part ) { return true; }
		virtual bool visitPart( const GeoPointList& part ) { return visitPart( (GeoPointList&)part ); }
	};

	class GeoPointVisitor
	{
	public:
		GeoPointVisitor() {}
		virtual ~GeoPointVisitor() { }
		virtual bool visitPoint( GeoPoint& point ) { 
			return true; }
		virtual bool visitPoint( const GeoPoint& point ) {
			return visitPoint( (GeoPoint&)point ); }
	};
}

#endif// _OWSCENES_GEOPOINT