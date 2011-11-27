#include <owScene/TileSurfaceNode.h>
#include <owScene/Terrain.h>

using namespace owScene;

TileSurfaceNode::TileSurfaceNode() : _parenttile(NULL),_geode(NULL),_geometry(NULL),_vertexs(NULL),_nomals(NULL),_texcoors(NULL),_height(NULL)
{
	_geode = new osg::Geode;
	_geometry = new osg::Geometry;

	addChild(_geode);
	_geode->addDrawable(_geometry);
}

TileSurfaceNode::TileSurfaceNode(const TileSurfaceNode& sn,const CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/) : osg::MatrixTransform(sn,copyop)
{
	_parenttile=sn._parenttile;
	_geode=sn._geode;
	_geometry=sn._geometry;
	_vertexs=sn._vertexs;
	_nomals=sn._nomals;
	_texcoors=sn._texcoors;
	_tilesize=sn._tilesize;
	_xinterval=sn._xinterval;
	_yinterval=sn._yinterval;
	_origin=sn._origin;
	_height = sn._height;
}

void TileSurfaceNode::setVerticalScale(float scale)
{

}

float TileSurfaceNode::getHeight(unsigned int c, unsigned int r)
{
	return _height->getValue(c,r);
}

void TileSurfaceNode::constructGeometry(Height* hf)
{
	if(!hf || !_parenttile)
		return;
	Terrain* terrain = _parenttile->getParentTerrain();
	const GeoExtent* extent = _parenttile->getSP()->getGeoExtent();

	_height = hf;

	///块大小
	_tilesize = terrain->getTileSize();
	///X和Y方向上的步长
	_xinterval = extent->width() / (_tilesize-1);
	_yinterval = extent->height() / (_tilesize-1);

	///起始点高度和起始点坐标
	double originHeight = 0.0/*getHeight(image, 0, 0)*/;
	_origin.set(extent->center().x(), extent->center().y(), originHeight);

	bool bGlobal = terrain->isGeoCentric();

	osg::Quat lvcsRotate;
	osg::Quat inverseRotate;
	osg::Matrix invMatrix;

	///如果地形模型需要转换到全球地心坐标系下 首先转换原点坐标
	if (!bGlobal)
		setMatrix(osg::Matrix::scale(1.0, 1.0, terrain->getVerticalScale()) * osg::Matrix::translate(_origin));
	else
	{
		terrain->getSP()->getSrs()->getEllipsoid()->convertLatLongHeightToXYZ(
			osg::DegreesToRadians(_origin.y()),
			osg::DegreesToRadians(_origin.x()),
			_origin.z(),
			_origin.x(),_origin.y(),_origin.z());

		osg::Vec3 up = _origin;
		up.normalize();
		lvcsRotate.makeRotate(osg::Vec3(0.0, 0.0, 1.0), up);
		inverseRotate = lvcsRotate.inverse();
		setMatrix(osg::Matrix::rotate(lvcsRotate)*osg::Matrix::translate(_origin));
		invMatrix = osg::Matrix::inverse(getMatrix());
	}

	/// 构造顶点
	_vertexs = new osg::Vec3Array((_tilesize+4)*_tilesize);
	_texcoors = new osg::Vec2Array((_tilesize+4)*_tilesize);

	osg::Vec4Array* colors = new osg::Vec4Array(1);
	(*colors)[0] = osg::Vec4(1.f, 1.f, 1.f, 1.f);

	_geometry->setColorArray(colors);
	_geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
	_geometry->setVertexArray(_vertexs);
	_geometry->setTexCoordArray(0, _texcoors);

	/// 构造顶点数组
	for (unsigned int i=0; i<_tilesize; i++)
	{
		osg::Vec3 rowPosition = osg::Vec3(0, _yinterval*i, 0);

		for (unsigned int j=0; j<_tilesize; j++)
		{
			if (bGlobal)
			{
				float height = getHeight(j, i);
				(*_vertexs)[i*_tilesize + j] = osg::Vec3(_xinterval*j, _yinterval*i, height) + osg::Vec3(extent->xMin(), extent->yMin(), 0.0);

				double x = 0; 
				double y = 0;
				double z = 0;

				double lat = (*_vertexs)[i*_tilesize + j].y();
				double lng = (*_vertexs)[i*_tilesize + j].x();
				double hei = (*_vertexs)[i*_tilesize + j].z();

				terrain->getSP()->getSrs()->getEllipsoid()->convertLatLongHeightToXYZ(
					osg::DegreesToRadians(lat),
					osg::DegreesToRadians(lng),
					hei,
					x,y,z);
				(*_vertexs)[i*_tilesize + j].set(x,y,z);
				(*_vertexs)[i*_tilesize + j] = invMatrix.preMult((*_vertexs)[i*_tilesize + j]);
			} 
			else
				(*_vertexs)[i*_tilesize + j] = osg::Vec3(_xinterval*j+extent->xMin(), _yinterval*i+extent->yMin(), getHeight(j, i)) - _origin;

			(*_texcoors)[i*_tilesize + j].x() = (j==_tilesize-1) ? 1.0f : (float)(j)/(float)(_tilesize-1);
			(*_texcoors)[i*_tilesize + j].y() = (i==_tilesize-1) ? 1.0f : (float)(i)/(float)(_tilesize-1);
		}
	}

	unsigned int currSize = _tilesize * _tilesize;
	float skirtLength;
	
	if (bGlobal)
	{
		float globe_radius = terrain->getSP()->getSrs()->getEllipsoid()->getRadiusEquator();
		skirtLength = globe_radius * osg::DegreesToRadians(extent->width()) * terrain->getSkirtRadio();
	} else
	{
		skirtLength = extent->width() * terrain->getSkirtRadio();
	}

	osg::Vec3 skirtVector;

	if (bGlobal)
	{
		skirtVector = _origin;
		skirtVector.normalize();
		skirtVector =  skirtVector * -skirtLength;

		skirtVector = inverseRotate * skirtVector;	
	}
	else
		skirtVector.set(0, 0, -skirtLength);

	/// AROUND SKIRTS
	for (unsigned int i=0; i<_tilesize; i++)
	{
		if (!bGlobal)
		{
			(*_vertexs)[currSize+i] = (*_vertexs)[i] + skirtVector; 
			(*_vertexs)[currSize+_tilesize+i] = (*_vertexs)[(_tilesize-1)*_tilesize+i] + skirtVector;
			(*_vertexs)[currSize+2*_tilesize+i] = (*_vertexs)[i*_tilesize] + skirtVector;
			(*_vertexs)[currSize+3*_tilesize+i] = (*_vertexs)[(i+1)*_tilesize-1] + skirtVector;
		}
		else
		{
			skirtVector = getMatrix().preMult((*_vertexs)[i]); skirtVector.normalize(); skirtVector = skirtVector * skirtLength; skirtVector = inverseRotate * skirtVector;
			(*_vertexs)[currSize+i] = (*_vertexs)[i] - skirtVector; 
			skirtVector = getMatrix().preMult((*_vertexs)[(_tilesize-1)*_tilesize+i]); skirtVector.normalize(); skirtVector = skirtVector * skirtLength; skirtVector = inverseRotate * skirtVector;
			//skirtVector = (*mVertexs)[(mTileSize-1)*mTileSize+i] + mOrigin; skirtVector.normalize(); skirtVector = skirtVector * skirtLength;
			(*_vertexs)[currSize+_tilesize+i] = (*_vertexs)[(_tilesize-1)*_tilesize+i] - skirtVector;
			skirtVector = getMatrix().preMult((*_vertexs)[i*_tilesize]); skirtVector.normalize(); skirtVector = skirtVector * skirtLength; skirtVector = inverseRotate * skirtVector;
			//skirtVector = (*mVertexs)[i*mTileSize] + mOrigin; skirtVector.normalize(); skirtVector = skirtVector * skirtLength;
			(*_vertexs)[currSize+2*_tilesize+i] = (*_vertexs)[i*_tilesize] - skirtVector;
			skirtVector = getMatrix().preMult((*_vertexs)[(i+1)*_tilesize-1]); skirtVector.normalize(); skirtVector = skirtVector * skirtLength; skirtVector = inverseRotate * skirtVector;
			//skirtVector = (*mVertexs)[(i+1)*mTileSize-1] + mOrigin; skirtVector.normalize(); skirtVector = skirtVector * skirtLength;
			(*_vertexs)[currSize+3*_tilesize+i] = (*_vertexs)[(i+1)*_tilesize-1] - skirtVector;
		}

		(*_texcoors)[currSize+i] = (*_texcoors)[i];
		(*_texcoors)[currSize+_tilesize+i] = (*_texcoors)[(_tilesize-1)*_tilesize+i];
		(*_texcoors)[currSize+2*_tilesize+i] = (*_texcoors)[i*_tilesize];
		(*_texcoors)[currSize+3*_tilesize+i] = (*_texcoors)[(i+1)*_tilesize-1];
	}

	///法向量数组
	_nomals = new osg::Vec3Array((_tilesize+4)*_tilesize);
	_geometry->setNormalArray(_nomals);
	_geometry->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);

	for (unsigned int i=0; i<_tilesize; i++)
	{
		for (unsigned int j=0; j<_tilesize; j++)
		{
			if (bGlobal)
			{
				osg::Vec3 localNormal = getNormal(j, i, bGlobal);
				osg::Vec3 pos = getPosition(j, i);
				pos.normalize();

				osg::Matrix matrix = osg::Matrix::rotate(osg::Vec3(0, 0, 1.0), pos);
				localNormal = osg::Matrixd::transform3x3(localNormal,matrix);
				localNormal = osg::Matrixd::transform3x3(localNormal, getInverseMatrix());
				localNormal.normalize();
				(*_nomals)[i*_tilesize+j] = localNormal;
			}else 
				(*_nomals)[i*_tilesize+j] = getNormal(j, i,bGlobal);
		}
	}

	/// AROUND SKIRTS
	for (unsigned int i=0; i<_tilesize; i++)
	{
		/// Top Skirt
		(*_nomals)[currSize+i] = (*_nomals)[i]; 
		/// Bottom Skirt
		(*_nomals)[currSize+_tilesize+i] = (*_nomals)[(_tilesize-1)*_tilesize+i];
		/// Left Skirt
		(*_nomals)[currSize+2*_tilesize+i] = (*_nomals)[i*_tilesize];
		/// Right Skirt
		(*_nomals)[currSize+3*_tilesize+i] = (*_nomals)[(i+1)*_tilesize-1];
	}

	osg::ref_ptr<osg::DrawElementsUShort> dui;

	for (unsigned int i = 0; i<_tilesize-1; i++)
	{
		dui = new osg::DrawElementsUShort(osg::DrawElements::TRIANGLE_STRIP);
		for (unsigned int j=0; j<_tilesize; j++)
		{
			dui->push_back(i*_tilesize + j);
			dui->push_back((i+1)*_tilesize + j);
		}
		_geometry->addPrimitiveSet(dui);
	}

	//top skirt
	dui = new osg::DrawElementsUShort(osg::DrawElements::TRIANGLE_STRIP);
	for (unsigned int i=0; i<_tilesize; i++)
	{
		dui->push_back(currSize+i);
		dui->push_back(i);
	}
	_geometry->addPrimitiveSet(dui);

	// bottom skirt
	dui = new osg::DrawElementsUShort(osg::DrawElements::TRIANGLE_STRIP);
	for (unsigned int i=0; i<_tilesize; i++)
	{
		dui->push_back(currSize-_tilesize+i);
		dui->push_back(currSize+_tilesize+i);
	}
	_geometry->addPrimitiveSet(dui);

	// left skirt
	dui = new osg::DrawElementsUShort(osg::DrawElements::TRIANGLE_STRIP);
	for (unsigned int i=0; i<_tilesize; i++)
	{
		dui->push_back(currSize+2*_tilesize+i);
		dui->push_back(i*_tilesize);
	}
	_geometry->addPrimitiveSet(dui);

	// right skirt
	dui = new osg::DrawElementsUShort(osg::DrawElements::TRIANGLE_STRIP);
	for (unsigned int i=0; i<_tilesize; i++)
	{
		dui->push_back((i+1)*_tilesize-1);
		dui->push_back(currSize+3*_tilesize+i);
	}
	_geometry->addPrimitiveSet(dui);
}

void TileSurfaceNode::seamNeighbor(TileSurfaceNode* nbnode, TileKey::NEIGHBORS nb)
{
	if(!nbnode)
		return;

	switch (nb)
	{
	case TileKey::LEFT:
		for (unsigned int i=0; i<_tilesize; i++)
		{
			setPosition(0, i, nbnode->getPosition(_tilesize-1, i));
			setNormal(0, i, nbnode->getNormal(_tilesize-1, i));
		}
		break;
	case TileKey::RIGHT:
		for (unsigned int i=0; i<_tilesize; i++)
		{
			setPosition(_tilesize-1, i, nbnode->getPosition((unsigned int)0, i));
			setNormal(_tilesize-1, i, nbnode->getNormal(0, i));
		}
		break;
	case TileKey::TOP:
		for (unsigned int i=0; i<_tilesize; i++)
		{
			setPosition(i, _tilesize-1, nbnode->getPosition(i, (unsigned int)0));
			setNormal(i, _tilesize-1, nbnode->getNormal(i, 0));
		}
		break;
	case TileKey::BOTTOM:
		for (unsigned int i=0; i<_tilesize; i++)
		{
			setPosition(i, 0, nbnode->getPosition(i, _tilesize-1));
			setNormal(i, 0, nbnode->getNormal(i, _tilesize-1));
		}
		break;
	}

	return;
}

void TileSurfaceNode::setPosition(unsigned int c, unsigned int r,const osg::Vec3& pos)
{
	(*_vertexs)[r*_tilesize + c] = getInverseMatrix().preMult(pos);
}

osg::Vec3 TileSurfaceNode::getPosition(unsigned int c, unsigned int r)
{
	return getMatrix().preMult( (*_vertexs)[r*_tilesize + c] );
}

void TileSurfaceNode::setNormal(unsigned int c, unsigned int r,const osg::Vec3& n)
{
	(*_nomals)[r*_tilesize + c] = osg::Matrixd::transform3x3(n, getInverseMatrix());
}

osg::Vec3 TileSurfaceNode::getNormal(unsigned int c, unsigned int r)
{
	return osg::Matrixd::transform3x3((*_nomals)[r*_tilesize + c], getMatrix());
}

osg::Vec3 TileSurfaceNode::getNormal(unsigned int c, unsigned int r, bool bGlobal)
{
#if 0
	double xInterval = _xinterval;
	double yInterval = _yinterval;

	if (bGlobal)
	{
		xInterval = osg::DegreesToRadians(xInterval) * _parenttile->getParentTerrain()->getSP()->getSrs()->getEllipsoid()->getRadiusPolar();
		yInterval = osg::DegreesToRadians(yInterval) * _parenttile->getParentTerrain()->getSP()->getSrs()->getEllipsoid()->getRadiusEquator();
	}

	// four point normal generation.
	double dz_dx;
	if (c==0)
	{
		dz_dx = (getHeight(c+1,r)-getHeight(c,r))/xInterval;
	}
	else if (c==_tilesize-1)
	{
		dz_dx = (getHeight(c,r)-getHeight(c-1,r))/xInterval;
	}
	else // assume 0<c<_numColumns-1
	{
		dz_dx = 0.5f*(getHeight(c+1,r)-getHeight(c-1,r))/xInterval;
	}

	double dz_dy;
	if (r==0)
	{
		dz_dy = (getHeight(c,r+1)-getHeight(c,r))/yInterval;
	}
	else if (r==_tilesize-1)
	{
		dz_dy = (getHeight(c,r)-getHeight(c,r-1))/yInterval;
	}
	else // assume 0<r<_numRows-1
	{
		dz_dy = 0.5f*(getHeight(c,r+1)-getHeight(c,r-1))/yInterval;
	}

	osg::Vec3 normal(-dz_dx,-dz_dy,1.0f);
	normal.normalize();

	return normal;
#else
	return osg::Vec3(0.f,0.f,1.f);
#endif
}
