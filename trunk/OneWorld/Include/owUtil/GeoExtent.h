#ifndef owUtil_GEOEXTENT_H_
#define owUtil_GEOEXTENT_H_

#include <owUtil/export.h>
#include <owUtil/config.h>
#include <osg/Referenced>
#include <osg/Vec2d>

namespace owUtil
{
	/** µÿ¿Ì∑∂Œß*/
	class OWUTIL_EXPORT GeoExtent : public osg::Referenced
	{
	public:

		GeoExtent(
			double xmin = FLT_MAX, double ymin = FLT_MAX,
			double xmax = -FLT_MAX, double ymax = -FLT_MAX );

		GeoExtent(const GeoExtent* rhs);

	public:

		double xMin() const { return _xmin; }
		double& xMin() { return _xmin; }

		double yMin() const { return _ymin; }
		double& yMin() { return _ymin; }

		double xMax() const { return _xmax; }
		double& xMax() { return _xmax; }

		double yMax() const { return _ymax; }
		double& yMax() { return _ymax; }

		double width() const;
		double height() const;

		void center( double& out_x, double& out_y ) const;

		osg::Vec2d center() const;

		double area() const;

		std::string toString() const;

	public:

		void reset();
		bool isValid() const;
		bool contains(double x, double y) const;
		bool contains(const GeoExtent* rhs) const;
		bool intersects( const GeoExtent* rhs ) const;
		void expandToInclude( double x, double y );
		void expandToInclude( const GeoExtent* rhs );
		void expand( double x, double y );
		GeoExtent* intersect(const GeoExtent* rhs) const;

		bool isEquivalentTo(const GeoExtent* rhs) const ;

		bool isPoint() const;

	public:

		void read(const Config* config);

		void write(Config* config) const ;

	protected:

		virtual ~GeoExtent() {;}

	private:

		bool crossesDateLine() const;

	private:

		double _xmin, _ymin, _xmax, _ymax;
	};
}

#endif //owUtil_GEOEXTENT_H_