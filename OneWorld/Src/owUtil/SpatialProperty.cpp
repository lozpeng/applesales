#include <owUtil/SpatialProperty.h>

using namespace owUtil;

SpatialProperty::SpatialProperty()
{
	;
}

SpatialProperty::SpatialProperty(GeoExtent* e, SpatialReference* sp) : _extent(e),_sp(sp)
{

}

SpatialProperty::~SpatialProperty()
{
	;
}

void SpatialProperty::setGeoExtent(GeoExtent* e)
{
	_extent = e;
}

GeoExtent* SpatialProperty::getGeoExtent()
{
	return _extent.get();
}

const GeoExtent* SpatialProperty::getGeoExtent() const
{
	return _extent.get();
}

void SpatialProperty::setSrs(SpatialReference* sp)
{
	_sp = sp;
}

SpatialReference* SpatialProperty::getSrs()
{
	return _sp.get();
}

const SpatialReference* SpatialProperty::getSrs() const
{
	return _sp.get();
}

bool SpatialProperty::isValid()
{
	return _extent.valid() && 
		_extent->isValid() && 
		_sp.valid();
}