#include <owScene/TerrainTile.h>
#include <owScene/Terrain.h>
#include <owScene/ImageLayersRenderTech.h>
#include <OpenThreads/ScopedLock>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osg/io_utils>
#include <osg/Texture2D>
#include <osg/NodeCallback>
#include <iostream>
#include <osgSim/ElevationSlice>
#include <osgDB/ReadFile>
#include <osgUtil/LineSegmentIntersector>
#include <osgUtil/UpdateVisitor>

using namespace owScene;

//更新回调函数
class TerrainTileUpdateCallback : public osg::NodeCallback
{
public:
	TerrainTileUpdateCallback(){}

	void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		TerrainTile* tile = dynamic_cast<TerrainTile*>(node);
		if(tile)
			tile->dirty();

		traverse(node,nv);
	}
};

TerrainTile::TerrainTile() : _hdirty(false),_idirty(false),_fdirty(false),_parentTerrain(NULL)
{
	setUpdateCallback(new TerrainTileUpdateCallback);
}

TerrainTile::~TerrainTile()
{
	_maphp.clear();
	_mapfgn.clear();
	_mapip.clear();
}

TerrainTile::TerrainTile(const TileKey& key,SpatialProperty* sp) : _key(key),_sp(sp), _hdirty(false),_idirty(false),_fdirty(false),_parentTerrain(NULL)
{
	setUpdateCallback(new TerrainTileUpdateCallback);

}

TerrainTile::TerrainTile(const TerrainTile& tile, const CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/)
: Group(tile,copyop)
{
	_key = tile._key;
	_sp = tile._sp;
	_maphp = tile._maphp;
	_mapfgn = tile._mapfgn;
	_mapip = tile._mapip;
	_tsfnode = tile._tsfnode;
	_hdirty = tile._hdirty;
	_idirty = tile._idirty;
	_fdirty = tile._fdirty;
	_parentTerrain=tile._parentTerrain;
	setUpdateCallback(new TerrainTileUpdateCallback);
}

TileSurfaceNode* TerrainTile::getTileSurfaceNode()
{
	return _tsfnode.get();
}

void TerrainTile::setVerticalScale(float vs)
{
	
}

void TerrainTile::addHeight(unsigned int index, HeightProxy* height)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_mutex);
	if(!height)
		return;

	HeightProxyIndexPair hpip(index,height);
	_maphp.resize(_maphp.size()+1);
	_maphp[_maphp.size()-1]=hpip;
}

void TerrainTile::insertHeight(unsigned int index, unsigned int pos, HeightProxy* height)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_mutex);
	if(!height)
		return;
	if(pos>_maphp.size())
		return;
	HeightProxyIndexPair hpip(index,height);
	_maphp.insert(_maphp.begin()+pos,hpip);
}


void TerrainTile::removeHeight(unsigned int index)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_mutex);
	HeightProxys::iterator iter = _maphp.begin();
	for(;iter!=_maphp.end();++iter)
	{
		if((*iter).first==index)
		{
			_maphp.erase(iter);
			break;
		}
	}
}

HeightProxy* TerrainTile::getHeight(unsigned int index)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_mutex);
	HeightProxys::iterator iter = _maphp.begin();
	for(;iter!=_maphp.end();++iter)
	{
		if((*iter).first==index)
		{
			return (*iter).second.get();
		}
	}
	return NULL;
}


void TerrainTile::setHeightPos(unsigned int index, unsigned int newpos)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_mutex);
	if(newpos>_maphp.size())
		return;
	HeightProxys::iterator iter = _maphp.begin();
	for(;iter!=_maphp.end();++iter)
	{
		if((*iter).first==index)
		{
			HeightProxyIndexPair temp = *iter;
			_maphp.erase(iter);
			insertHeight(temp.first,newpos,temp.second.get());
			break;
		}
	}
}


void TerrainTile::EnableHeight(unsigned int index, bool enable)
{
	//TODO
}

void TerrainTile::addImage(unsigned int index,ImageProxy* image)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_mutex);
	if(!image)
		return;

	ImageProxyIndexPair ipip(index,image);
	_mapip.resize(_mapip.size()+1);
	_mapip[_mapip.size()-1]=ipip;
}

void TerrainTile::InsertImage(unsigned int index, ImageProxy* image,unsigned int pos)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_mutex);
	if(!image)
		return;
	if(pos>_mapip.size())
		return;
	ImageProxyIndexPair ipip(index,image);
	_mapip.insert(_mapip.begin()+pos,ipip);
}

void TerrainTile::removeImage(unsigned int index)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_mutex);
	ImageProxys::iterator iter = _mapip.begin();
	for(;iter!=_mapip.end();++iter)
	{
		if((*iter).first==index)
		{
			bool bhasdata = (*iter).second->valid();
			_mapip.erase(iter);
			break;
		}
	}
}

ImageProxy* TerrainTile::getImage(unsigned int index)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_mutex);
	ImageProxys::iterator iter = _mapip.begin();
	for(;iter!=_mapip.end();++iter)
	{
		if((*iter).first==index)
		{
			return (*iter).second.get();
		}
	}
	return NULL;
}

void TerrainTile::setImagePos(unsigned int index, unsigned int newpos)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_mutex);
	if(newpos>_mapip.size())
		return;
	ImageProxyIndexPair temp;
	ImageProxys::iterator iter = _mapip.begin();
	for(;iter!=_mapip.end();++iter)
	{
		if((*iter).first==index)
		{
			temp = *iter;
			_mapip.erase(iter);
			InsertImage(temp.first,temp.second.get(),newpos);
			break;
		}
	}
}

void TerrainTile::EnableImage(unsigned int index, bool enable)
{
	//TODO
}

void TerrainTile::setImageOpacity(unsigned int index, float op)
{

}

void TerrainTile::traverse(NodeVisitor& nv)
{
	osgUtil::UpdateVisitor* uv = dynamic_cast<osgUtil::UpdateVisitor*>(&nv);
	if(uv)
		return osg::Group::traverse(nv);
	return osg::Group::traverse(nv);
}

void TerrainTile::addFeatureGroupNode(unsigned int index, FeatureGroupNode* fn)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_mutex);
	if(!fn)
		return;

	FGNIndexPair fpip(index,fn);
	_mapfgn.resize(_mapfgn.size()+1);
	_mapfgn[_mapfgn.size()-1]=fpip;
}

void TerrainTile::removeFeatureGroupNode(unsigned int index)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_mutex);
	FGNIndexPairs::iterator iter = _mapfgn.begin();
	for(;iter!=_mapfgn.end();++iter)
	{
		if((*iter).first==index)
		{
			setDataVariance(osg::Object::DYNAMIC);
			removeChild((*iter).second.get());
			_mapfgn.erase(iter);
			break;
		}
	}
}

void TerrainTile::genSlicePoints(std::vector<osg::Vec3d> ins, std::vector<osg::Vec3d>& outs) const
{
	if(!_tsfnode.get())
	{
		outs.insert(outs.end(), ins.begin(), ins.end());
		return;
	}

	osg::ref_ptr<osg::CoordinateSystemNode> slice_node = new osg::CoordinateSystemNode(_parentTerrain->getFormat(), _parentTerrain->getCoordinateSystem());
	slice_node->addChild(_tsfnode.get());
	
	for(int i=0; i<(ins.size()-1); i++)
	{

		osgSim::ElevationSlice es;
		es.setDatabaseCacheReadCallback(NULL);

		es.setStartPoint(ins[i]);
		es.setEndPoint(ins[i+1]);

		es.computeIntersections(slice_node);

		osgSim::ElevationSlice::Vec3dList rv = es.getIntersections();

		outs.insert(outs.end(), rv.begin(), rv.end());

	}
}

void TerrainTile::genIntersectPoint(const osg::Vec3d& first,const osg::Vec3d& second, osg::Vec3d& out) const
{
	if(!_tsfnode.valid())
		return;

	osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector(first, second);

	osgUtil::IntersectionVisitor intersectVisitor( intersector.get());
	intersectVisitor.setReadCallback(NULL);

	_tsfnode->accept(intersectVisitor);
	if ( intersector->containsIntersections() )
	{
		osgUtil::LineSegmentIntersector::Intersections& intersections = intersector->getIntersections();
		for(osgUtil::LineSegmentIntersector::Intersections::iterator itr = intersections.begin();
			itr != intersections.end();
			++itr)
		{
			const osgUtil::LineSegmentIntersector::Intersection& intersection = *itr;
			out = intersection.getWorldIntersectPoint();
		}
	}
}

FeatureGroupNode* TerrainTile::getFeatureGroupNode(unsigned int index)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_mutex);
	FGNIndexPairs::iterator iter = _mapfgn.begin();
	for(;iter!=_mapfgn.end();++iter)
	{
		if((*iter).first==index)
		{
			return (*iter).second.get();
		}
	}
	return NULL;
}

void TerrainTile::EnableFeatureGroupNode(unsigned int index, bool enable)
{
	//TODO
}

void TerrainTile::dirty()
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);

	if(_hdirty)
	{
		//do something to eles
		updateHeight();
		_hdirty = false;
	}

	if(_idirty)
	{
		//do something to imgs
		updateImage();
		_idirty = false;
	}

	if(_fdirty)
	{
		//do something to fs
		updateFeatures();
		_fdirty = false;
	}
}

Height* TerrainTile::createFlatHeight()
{
	Height* result = new Height;
	result->allocate(_parentTerrain->getTileSize(),_parentTerrain->getTileSize(),0.f);

	return result;
}

Height* TerrainTile::combineHeight()
{
	//如果没有高程数据，创建一个平坦的高程
	if(_maphp.empty())
		return createFlatHeight();

	//如果只有一个就直接返回
	if(_maphp.size()==1)
	{
		HeightProxy* h = (*(_maphp.begin())).second.get();
		if(!h->valid())//如果为空，则说明插件中没有创建出相应的高程数据
			return createFlatHeight();
		return h->get();
	}

	//先创建出一个平的地形，在下面给各个点赋值
	Height* h = createFlatHeight();

	//遍历获得数据，对该块数据赋值。从上到下层，如果获得高程值不为0.f，即为得到了值。
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_mutex);
		for(unsigned int j=0;j<_parentTerrain->getTileSize();++j)
		{
			for(unsigned int i=0;i<_parentTerrain->getTileSize();++i)
			{
				float v = 0.f;
				HeightProxys::iterator iter = _maphp.begin();
				for(;iter!=_maphp.end();++iter)
				{
					HeightProxy* thp = (*iter).second.get();
					if(thp->valid()) //如果存在高程数据，获取高程数据
					{
						Height* th = thp->get();
						float v_ji = th->getValue(j,i);
						if(!osg::equivalent(v_ji,0.f))//判断高程数据是否为0,0默认为缺省的无效值，如果不为0为正常值
						{
							v = v_ji;
							break;
						}
					}
				}
				h->setValue(j,i,v);
			}
		}
	}
	
	return h;
}

void TerrainTile::updateHeight()
{
	if(!_parentTerrain)
		return;
	Height* h = combineHeight();

	//地块表面构建
	TileSurfaceNode* surfaceNode = new TileSurfaceNode();
	surfaceNode->setParentTile(this);
	surfaceNode->constructGeometry(h);

	//先移除原先的节点，如果存在的话
	setDataVariance(osg::Object::DYNAMIC);
	if(_tsfnode.valid())
	{
		removeChild(_tsfnode.get());
	}

	_tsfnode = surfaceNode;

	seamTileSufaceNode();

	addChild(_tsfnode.get());
}

void TerrainTile::seamTileSufaceNode()
{
	TileKey top_key = _key.neighbor(TileKey::TOP);
	osg::ref_ptr<TerrainTile> top_tile = _parentTerrain->getRegistTerrainTile(top_key);
	if (top_tile.get() && top_tile->getTileSurfaceNode())
		_tsfnode->seamNeighbor(top_tile->getTileSurfaceNode(),TileKey::TOP);

	TileKey bottom_key = _key.neighbor(TileKey::BOTTOM);
	osg::ref_ptr<TerrainTile> bottom_tile = _parentTerrain->getRegistTerrainTile(bottom_key);
	if (bottom_tile.get() && bottom_tile->getTileSurfaceNode())
		_tsfnode->seamNeighbor(bottom_tile->getTileSurfaceNode(),TileKey::BOTTOM);

	TileKey right_key = _key.neighbor(TileKey::RIGHT);
	osg::ref_ptr<TerrainTile> right_tile = _parentTerrain->getRegistTerrainTile(right_key);
	if (right_tile.get() && right_tile->getTileSurfaceNode())
		_tsfnode->seamNeighbor(right_tile->getTileSurfaceNode(),TileKey::RIGHT);

	TileKey left_key = _key.neighbor(TileKey::LEFT);
	osg::ref_ptr<TerrainTile> left_tile = _parentTerrain->getRegistTerrainTile(left_key);
	if (left_tile.get() && left_tile->getTileSurfaceNode())
		_tsfnode->seamNeighbor(left_tile->getTileSurfaceNode(),TileKey::LEFT);
}

void TerrainTile::updateImage()
{
	if(!_tsfnode.valid())
		return;

	osg::Geode* locsurfacenode = _tsfnode->getLocalSurface();
	if(!locsurfacenode)
		return;

	osg::Drawable* drawable = locsurfacenode->getDrawable(0);
	if(!drawable)
		return;

	osg::Geometry* geometry = drawable->asGeometry();

	if(!geometry)
		return;

	//纹理
	{
		typedef std::vector<osg::ref_ptr<osg::Image>> ImageList;
		ImageList imglst;

		ImageProxys::iterator iter = _mapip.begin();
		for(;iter!=_mapip.end();++iter)
		{
			osg::Image* image = (*iter).second->get();
			if(image)
				imglst.push_back(image);
		}

		ImageLayersRenderTech* imgLRT = dynamic_cast<ImageLayersRenderTech*>(_parentTerrain->getTerrainRenderTech());
		if (imgLRT)
		{
			//imgLRT->setType(ImageLayersRenderTech::Type::TEXTURE2D);
			imgLRT->applyTexture(geometry,imglst);
		}
	}
	geometry->getOrCreateStateSet()->setMode(GL_BLEND,osg::StateAttribute::ON);
	geometry->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	
}

void TerrainTile::updateFeatures()
{
	for(int i=0; i<_mapfgn.size(); i++)
	{
		FGNIndexPair fp = _mapfgn[i];
		addChild(fp.second);
	}
}