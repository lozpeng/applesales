#include <owNavi/TerrainManipulator2.h>

using namespace owNavi;


/// Constructor.
TerrainManipulator2::TerrainManipulator2( int flags )
: TerrainManipulator( flags )
{
}


/// Constructor.
TerrainManipulator2::TerrainManipulator2( const TerrainManipulator2& tm, const osg::CopyOp& copyOp )
: osgGA::TerrainManipulator( tm, copyOp )
{

}

bool TerrainManipulator2::performMovementMiddleMouseButton( const double eventTimeDelta, const double dx, const double dy )
{
	return false;
}

bool TerrainManipulator2::performMovementLeftMouseButton(  const double eventTimeDelta, const double dx, const double dy  )
{
	return osgGA::TerrainManipulator::performMovementMiddleMouseButton(eventTimeDelta,dx,dy);
}

bool TerrainManipulator2::performMovementRightMouseButton( const double eventTimeDelta, const double dx, const double dy )
{
	return osgGA::OrbitManipulator::performMovementLeftMouseButton(eventTimeDelta,dx, dy);
}
void TerrainManipulator2::LookAtLayer(owScene::Layer* pLayer, osg::Matrix& lookat)
{
	if (!pLayer)
	{
		return;
	}
	osg::EllipsoidModel mGlobalEM;
	osg::Vec3d eyeUp,eyePos,eyePosLongLat;
	double earthRadius = mGlobalEM.getRadiusEquator();
	const SpatialProperty* pSP = pLayer->getDataSource()->getSP();
	const SpatialReference* pSF = pSP->getSrs();

	{
		const owUtil::GeoExtent* pGeoExtent = pSP->getGeoExtent();
		double dWidth = pGeoExtent->width();
		double dHeight = pGeoExtent->height();
		double dRadius = sqrt(0.25*(dWidth*dWidth+dHeight*dHeight));
		double a = 0;
		double x,y,height ;
		if (pSF->isGeographic())
		{
			height = osg::DegreesToRadians(dRadius) * earthRadius * 4.0;
		} else
		{
			height = 4.0 * dRadius;
		}
		osg::ref_ptr<SpatialReference> _srs84 = SpatialReference::create("wgs84");
		if (!pSF->isEquivalentTo(_srs84))
			pSF->transform(pGeoExtent->center().x(),pGeoExtent->center().y(),_srs84,x,y);
		else
		{
			x = pGeoExtent->center().x();
			y = pGeoExtent->center().y();
		}
		eyePosLongLat.set(x,y,height);
	}
	eyePos = eyePosLongLat;
	double gx, gy, gz;
	mGlobalEM.convertLatLongHeightToXYZ(osg::DegreesToRadians(eyePos.y()), osg::DegreesToRadians(eyePos.x()), eyePos.z(), gx, gy, gz);
	double gx1,gy1,gz1;
	mGlobalEM.convertLatLongHeightToXYZ(osg::DegreesToRadians(eyePos.y()), osg::DegreesToRadians(eyePos.x()),0,gx1,gy1,gz1);
	eyePos.x() = gx;
	eyePos.y() = gy;
	eyePos.z() = gz;
	osg::Vec3d target(gx1,gy1,gz1);
	double distance = (eyePos - target).length();
	osg::Vec3d s,f,u,northVec;
	northVec = osg::Vec3d(0.0,0.0,1.0);
	f = target;
	f.normalize();
	s = northVec^f;
	s.normalize();
	u = f^s;
	u.normalize();
	osg::Vec3d eyePos1 = target + f*distance;
	lookat.makeLookAt(eyePos1,target,u);
}