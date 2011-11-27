#pragma once

#include <owScene/Export.h>

#include <owScene/geopoint.h>

#include <owUtil/GeoExtent.h>

using namespace owUtil;

namespace owScene
{
	/** A list of point lists (a "part"). */
	typedef std::vector<GeoPointList> GeoPartList;

	/**
	* A set of points that taken together form a one- or multi-part shape.
	*/
	class OWSCENE_EXPORT GeoShape
	{
	public:
		/** Types of shapes. */
		enum ShapeType 
		{
			/** The shape type is not known. */
			TYPE_UNSPECIFIED,

			/** Shape is a series of unconnected points. */
			TYPE_POINT,

			/** Each shape part forms a line string. */
			TYPE_LINE,

			/** Each shape part forms a closed polygon. */
			TYPE_POLYGON
		};      

	public:
		/**
		* Constructs a new, empty shape.
		*/
		GeoShape();

		/**
		* Copy constructor. 
		*/
		GeoShape( const GeoShape& to_copy );

		/**
		* Creates a new, empty shape.
		* 
		* @param type
		*      Shape type - see GeoShape::ShapeType
		*/
		GeoShape( const ShapeType& type);

		/**
		* Gets the shape type.
		*/
		const ShapeType& getShapeType() const;

		/**
		* Sets the shape type (see GeoShape::ShapeType)
		*/
		void setShapeType( const ShapeType& type );

		/**
		* Gets the number of parts that comprise this shape.
		*/
		unsigned int getPartCount() const;

		/**
		* Gets a shape part.
		* @param part
		*      Index of the part to get.
		*/
		const GeoPointList& getPart( unsigned int part ) const;

		/**
		* Gets a shape part.
		* @param part
		*      Index of the part to get.
		*/
		GeoPointList& getPart( unsigned int part );

		/**
		* Gets a reference to the entire list of parts.
		*/
		const GeoPartList& getParts() const;

		/**
		* Gets a reference to the entire list of parts.
		*/
		GeoPartList& getParts();

		/**
		* Gets the total number of points in the shape (sum of all parts).
		*/
		unsigned int getTotalPointCount() const;

		/**
		* Adds a new, empty part to the shape and returns a reference to it.
		*/
		GeoPointList& addPart();

		/**
		* Adds a part to the shape and returns a reference to it.
		*/
		GeoPointList& addPart( const GeoPointList& part );

		/**
		* Adds a new part to the shape, preallocating space for the points,
		* and returns a reference to it.
		* @param num_points
		*      The number of points to preallocate in the part.
		*/
		GeoPointList& addPart( unsigned int num_points );

		/**
		* Visits each point in the shape with a user-provided visitor.
		*/
		bool accept( GeoPointVisitor& visitor );

		/**
		* Visits each point in the shape with a user-provided visitor.
		*/
		bool accept( GeoPointVisitor& visitor ) const;

		/**
		* Gets the spatial extent (minimum bounding rectangle) of all
		* the geodata within the shape.
		*/
		const GeoExtent* getExtent() const;

		/**
		* center
		*/
		osg::Vec2 getCenter() const;

		/**
		* Gets the spatial extent (minimum bounding rectangle) of all
		* the geodata within the shape.
		*/
		GeoExtent* getExtent();

		/** ÖØÐÂ¼ÆËã·¶Î§*/
		void caculateExtent();

	public:

		bool intersects( const GeoExtent* ex ) const;

	public:

		virtual ~GeoShape();

	private:

		ShapeType   shape_type;
		GeoPartList parts;
		osg::ref_ptr<GeoExtent> extent_cache;
	};

	class OWSCENE_EXPORT GeoShapeList : public std::vector<GeoShape>
	{
	public:
		GeoShapeList() { }
		GeoShapeList( int capacity ) : std::vector<GeoShape>( capacity ) { }

		bool accept( GeoPartVisitor& visitor );
		bool accept( GeoPartVisitor& visitor ) const;

		bool accept( GeoPointVisitor& visitor );
		bool accept( GeoPointVisitor& visitor ) const;

	public:
		//TODO: geometry functions.
		bool intersects( const GeoExtent* extent ) const;
	};
}