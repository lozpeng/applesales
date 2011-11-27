#include <owNavi/AutoClipPlaneHandler.h>
#include <iostream>

using namespace owNavi;

AutoClipPlaneHandler::AutoClipPlaneHandler(Terrain* terrain ) :
_geocentric(false),
_frame(0),
_nfrAtRadius( 0.00001 ),
_nfrAtDoubleRadius( 0.0049 ),
_rp( -1 ),
_autoFarPlaneClipping(false),
_terrain(terrain)
{
	//NOP
	if ( _terrain )
	{
		_geocentric = _terrain->isGeoCentric();
		if ( _geocentric )
			_rp = _terrain->getEllipsoidModel()->getRadiusPolar();
	}
}

bool 
AutoClipPlaneHandler::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
{
	if ( ea.getEventType() == osgGA::GUIEventAdapter::FRAME && _frame++ > 1 )
	{
		frame( aa );
	}
	return false;
}

void
AutoClipPlaneHandler::frame( osgGA::GUIActionAdapter& aa )
{
	osg::Camera* cam = aa.asView()->getCamera();

	osg::Matrix m = aa.asView()->getCamera()->getViewMatrix();
	if ( _rp < 0 )
	{
		if ( _geocentric )
			_rp = _terrain->getEllipsoidModel()->getRadiusPolar();
	}

	if ( _rp > 0 && _geocentric ) // _mapNode.valid() && _geocentric )
	{
		cam->setComputeNearFarMode( osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR );
		//osg::CullSettings::ComputeNearFarMode type = cam->getComputeNearFarMode();

		osg::Vec3d eye, center, up;
		cam->getViewMatrixAsLookAt( eye, center, up );
		//std::cout<<eye._v[0]<<" "<<eye._v[1]<<" "<<eye._v[2]<<std::endl;

		double d = eye.length();

		if ( d > _rp )
		{
			double fovy, ar, znear, zfar, finalZfar, outr;
			cam->getProjectionMatrixAsPerspective( fovy, ar, znear, finalZfar );

			/*osg::Vec3 teye,tcenter,tup;
			cam->getViewMatrixAsLookAt(teye,tcenter,tup);*/

			// far clip at the horizon:

			//atmospheirc out r
			outr = _rp + _rp * 0.015;

			zfar = sqrt( d*d - _rp*_rp ) + sqrt( outr*outr - _rp*_rp );

			if (_autoFarPlaneClipping)
			{
				finalZfar = zfar;
			}

			double nfr = _nfrAtRadius + _nfrAtDoubleRadius * ((d-_rp)/d);
			znear = osg::clampAbove( zfar * nfr, 1.0 );

			cam->setProjectionMatrixAsPerspective( fovy, ar, znear, finalZfar );
		}
	}
}

