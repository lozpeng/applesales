#include <owScene/ModelLayer.h>
#include <osg/Matrixd>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <math.h>

using namespace owScene;
using namespace owUtil;

ModelLayer::ModelLayer()
{

}

void ModelLayer::read(const Config& config)
{
	//layer propers
	_name = config.value("name");
	_lodratio = config.value<float>("lodratio", 30.0);
	_height = config.value<float>("height",0.0);
	_wkt = config.value("wkt");
	_url = config.value("url");
	_srs = SpatialReference::create(_wkt);
	_root = new osg::Group();

	//
	std::string strcnt;
	osg::ref_ptr<SpatialReference> _srs84 = SpatialReference::create("wgs84");
	osg::Vec3d center2, center;
	double lon,lat,h,radius;
	
	_extent = new GeoExtent;
	strcnt = config.value("extent");
	sscanf(strcnt.c_str(),"%lf,%lf,%lf,%lf", &(_extent->xMin()), &(_extent->xMax()), &(_extent->yMin()),&(_extent->yMax()));
	center2.x() = _extent->center().x();
	center2.y() = _extent->center().y();
	center2.z() = _height;
	radius = sqrt(_extent->width()*_extent->width()+_extent->height()*_extent->height());

	if(!_srs->isEquivalentTo(_srs84))
	{
		_srs->transform(center2._v[0],center2._v[1],_srs84, lon, lat);
		lon = osg::DegreesToRadians(lon);
		lat = osg::DegreesToRadians(lat);
		h = center2._v[2];
	}
	else
	{
		lon = osg::DegreesToRadians(center2._v[0]);
		lat = osg::DegreesToRadians(center2._v[1]);
		h = center2._v[2];
		radius *= 111000.;
	}

	_srs->getEllipsoid()->convertLatLongHeightToXYZ(lat,lon,h, center.x(), center.y(), center.z());

	{
		osg::PagedLOD* pglod = new osg::PagedLOD;
		osg::ref_ptr<osgDB::Options> op = new osgDB::Options;
		op->setUserData(_srs.get());

		pglod->setFileName(0,_url);
		pglod->setRange(0, 0,radius*_lodratio);
		pglod->setCenter(center);
		pglod->setDatabaseOptions(op.get());

		_root->addChild(pglod);
	}
	
}

void ModelLayer::write(Config& config)
{

	//TODO
}

