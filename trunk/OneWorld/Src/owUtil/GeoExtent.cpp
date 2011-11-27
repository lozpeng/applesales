#include <owUtil/GeoExtent.h>

#include <sstream>

using namespace owUtil;


GeoExtent::GeoExtent(double xmin, double ymin, double xmax, double ymax) :
_xmin(xmin),_ymin(ymin),_xmax(xmax),_ymax(ymax)
{
	;
}

GeoExtent::GeoExtent(const GeoExtent* rhs)
{
	if(rhs)
	{
		_xmin = rhs->xMin();
		_ymin = rhs->yMin();
		_xmax = rhs->xMax();
		_ymax = rhs->yMax();
	}
}

void GeoExtent::reset()
{
	_xmin = FLT_MAX;
	_ymin = FLT_MAX;
	_xmax = -FLT_MAX;
	_ymax = -FLT_MAX;
}

bool GeoExtent::isEquivalentTo(const GeoExtent* rhs) const 
{
	if(!rhs)
		return false;

	if ( !isValid() && !rhs->isValid() )
		return true;

	else
	{
		return
			isValid() && rhs->isValid() &&
			osg::equivalent(_xmin,rhs->xMin()) &&
			osg::equivalent(_ymin,rhs->yMin()) &&
			osg::equivalent(_xmax,rhs->xMax()) &&
			osg::equivalent(_ymax,rhs->yMax());
	}
}

bool
GeoExtent::isValid() const
{
	return width() > 0 && height() > 0;
}

double
GeoExtent::width() const
{
	return crossesDateLine()?
		(180-_xmin) + (_xmax+180) :
	_xmax - _xmin;
}

double
GeoExtent::height() const
{
	return _ymax - _ymin;
}

void
GeoExtent::center( double& out_x, double& out_y ) const
{
	out_x = _xmin+width()/2.0;
	out_y = _ymin+height()/2.0;
}

osg::Vec2d
GeoExtent::center() const
{
	return osg::Vec2d(_xmin+width()/2.0,_ymin+height()/2.0);
}

bool
GeoExtent::crossesDateLine() const
{
	return _xmax < _xmin;
}

bool
GeoExtent::contains(double x, double y) const
{
	double local_x = x, local_y = y;

	//Account for small rounding errors along the edges of the extent
	if (osg::equivalent(_xmin, local_x)) local_x = _xmin;
	if (osg::equivalent(_xmax, local_x)) local_x = _xmax;
	if (osg::equivalent(_ymin, local_y)) local_y = _ymin;
	if (osg::equivalent(_ymax, local_y)) local_y = _ymax;
	return local_x >= _xmin && local_x <= _xmax && local_y >= _ymin && local_y <= _ymax;

}

bool 
GeoExtent::contains(const GeoExtent* rhs) const
{
	if(!rhs)
		return false;

	return contains(rhs->xMin(),rhs->yMin())
		&& contains(rhs->xMin(),rhs->yMax())
		&& contains(rhs->xMax(),rhs->yMin())
		&& contains(rhs->xMax(),rhs->yMax());
}

bool
GeoExtent::intersects( const GeoExtent* rhs ) const
{
	if(!rhs)
		return false;

	bool valid = isValid();
	if ( !valid ) return false;

	bool exclusive =
		_xmin > rhs->xMax() ||
		_xmax < rhs->xMin() ||
		_ymin > rhs->yMax() ||
		_ymax < rhs->yMin();

	return !exclusive;
}

GeoExtent* GeoExtent::intersect(const GeoExtent* rhs) const
{
	if(!rhs)
		return NULL;
	if(!intersects(rhs))
		return NULL;

	double xmin = _xmin < rhs->xMin() ? rhs->xMin() : _xmin;
	double xmax = _xmax < rhs->xMax() ? _xmax : rhs->xMax();
	double ymin = _ymin < rhs->yMin() ? rhs->yMin() : _ymin;
	double ymax = _ymax < rhs->yMax() ? _ymax : rhs->yMax();

	return new GeoExtent(xmin,ymin,xmax,ymax);
}

bool GeoExtent::isPoint() const
{
	if(!isValid())
		return false;
	return osg::equivalent(_xmin,_xmax)
		&& osg::equivalent(_ymin,_ymax);
}

void
GeoExtent::expandToInclude( double x, double y )
{
	if ( x < _xmin ) _xmin = x;
	if ( x > _xmax ) _xmax = x;
	if ( y < _ymin ) _ymin = y;
	if ( y > _ymax ) _ymax = y;
}

void GeoExtent::expandToInclude(const GeoExtent *rhs)
{
	if(!rhs)
		return;
	expandToInclude( rhs->xMin(), rhs->yMin() );
	expandToInclude( rhs->xMax(), rhs->yMax() );
}

void
GeoExtent::expand( double x, double y )
{
	_xmin -= .5*x;
	_xmax += .5*x;
	_ymin -= .5*y;
	_ymax += .5*y;
}

double
GeoExtent::area() const
{
	return width() * height();
}

std::string
GeoExtent::toString() const
{
	std::stringstream buf;
	if ( !isValid() )
		buf << "INVALID";
	else
		buf << "MIN=" << _xmin << "," << _ymin << " MAX=" << _xmax << "," << _ymax;
	std::string bufStr;
	bufStr = buf.str();
	return bufStr;
}

void GeoExtent::read(const Config* config)
{
	//TODO
}

void GeoExtent::write(Config* config) const 
{
	//TODO
}