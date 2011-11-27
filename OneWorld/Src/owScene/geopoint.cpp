#include <owScene/geopoint.h>

#include <sstream>

using namespace owScene;

GeoPoint::GeoPoint()
{
	dim = 0;
}


GeoPoint
GeoPoint::invalid()
{
	return GeoPoint();
}


GeoPoint::GeoPoint( const GeoPoint& rhs )
: osg::Vec3d( rhs )
{
	dim = rhs.dim;
}


GeoPoint::GeoPoint( const osg::Vec2d& _input)
: osg::Vec3d( _input.x(), _input.y(), 0.0 )
{
	dim = 2;
}


GeoPoint::GeoPoint( const osg::Vec3d& _input)
: osg::Vec3d( _input )
{
	dim = 3;
}


GeoPoint::GeoPoint( double _x, double _y)
: osg::Vec3d( _x, _y, 0.0 )
{
	dim = 2;
}


GeoPoint::GeoPoint( double _x, double _y, double _z)
: osg::Vec3d( _x, _y, _z )
{
	dim = 3;
}


GeoPoint::~GeoPoint()
{
	//NOP
}

bool
GeoPoint::isValid() const
{
	return dim > 0;
}


bool
GeoPoint::operator == ( const GeoPoint& rhs ) const
{
	return
		isValid() && rhs.isValid() &&
		getDim() == rhs.getDim() &&
		x() == rhs.x() &&
		(getDim() < 2 || y() == rhs.y()) &&
		(getDim() < 3 || z() == rhs.z());
}


unsigned int
GeoPoint::getDim() const
{
	return dim;
}

void
GeoPoint::setDim( int _dim )
{
	dim = _dim > 0 && _dim <= 3? _dim : dim;
}


std::string
GeoPoint::toString() const
{
	std::stringstream str;
	if ( isValid() && getDim() == 2 )
		str << x() << ", " << y();
	else if ( isValid() && getDim() == 3 )
		str << x() << ", " << y() << ", " << z();
	else
		str << "INVALID";
	return str.str();
}


/**************************************************************************/

bool
GeoPointList::intersects( const GeoExtent* ex ) const
{
	if(!ex)
		return false;

	//TODO: srs transform

	if ( ex->isPoint() ) // do a point-in-polygon test
	{
		double x = ex->xMin();
		double y = ex->yMin();
		bool result = false;
		const GeoPointList& polygon = *this;
		for( unsigned int i=0, j=polygon.size()-1; i<polygon.size(); j = i++ )
		{
			if ((((polygon[i].y() <= y) && (y < polygon[j].y())) ||
				((polygon[j].y() <= y) && (y < polygon[i].y()))) &&
				(x < (polygon[j].x()-polygon[i].x()) * (y-polygon[i].y())/(polygon[j].y()-polygon[i].y())+polygon[i].x()))
			{
				result = !result;
			}
		}
		return result;
	}
	else // check for all points within extent -- not actually correct //TODO
	{
		osg::ref_ptr<GeoExtent> e = new GeoExtent();;
		for( GeoPointList::const_iterator i = begin(); i != end(); i++ )
		{
			e->expandToInclude( (*i).x(),(*i).y() );
		}
		return e->intersects(ex);
	}    
}

bool
GeoPointList::isClosed() const
{
	return size() >= 2 && front() == back();
}