#include <owScene/Terrain.h>
#include <owScene/Common.h>
#include <owScene/Registry.h>
#include <owScene/ImageLayersRenderTech.h>

#include <owUtil/Log.h>
#include <owUtil/OperateDuringUpdate.h>

#include <osg/FrontFace>
#include <osg/CullFace>
#include <osgSim/OverlayNode>

#include <OpenThreads/ScopedLock>
#include <iostream>

#define DEFAULTSPSTRING "wgs84"
#define DEFAULTMINX -180.0
#define DEFAULTMAXX 180.0
#define DEFAULTMINY -90.0
#define DEFAULTMAXY 90.0

using namespace owScene;

static int s_terrain_uid = 0;

//默认为全球坐标，WGS84投影
Terrain::Terrain() : _maxlevel(MAXLEVEL),_verticalscale(1.f),_skitradio(0.02f),_mintilerange(3.f),_tilesize(32),_imagesize(64),
	_sp(new SpatialProperty(new GeoExtent(DEFAULTMINX,DEFAULTMINY,DEFAULTMAXX,DEFAULTMAXY),SpatialReference::create(DEFAULTSPSTRING)))
{
	validate();
	registry();
}

Terrain::Terrain(SpatialProperty* sp) : _maxlevel(MAXLEVEL),_verticalscale(1.f),_skitradio(0.2f),_mintilerange(6.f),_tilesize(32),_imagesize(64),_sp(sp)
{
	validate();
	registry();
}

Terrain::Terrain(const Terrain& terrain, const CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/) : CoordinateSystemNode(terrain,copyop)
{
	_maxlevel=terrain._maxlevel;
	_verticalscale = terrain._verticalscale;
	_skitradio = terrain._skitradio;
	_mintilerange = terrain._mintilerange;
	_sp = terrain._sp;
	_tilesize = terrain._tilesize;
	_imagesize = terrain._imagesize;
	_numTilesWideAtLod0 = terrain._numTilesWideAtLod0;
	_numTilesHighAtLod0 = terrain._numTilesHighAtLod0;
	_tilefactroy = terrain._tilefactroy;
	_terrainrendertech = terrain._terrainrendertech;
	
	registry();
}

int Terrain::getUID() const
{
	return _uid;
}

void Terrain::Initialize(ProgressBase* p/*=NULL*/)
{
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_elelyrmutex);
		std::vector<osg::ref_ptr<ElevationLayer>>::iterator e_iter = _elelayers.begin();
		for(e_iter;e_iter!=_elelayers.end();++e_iter)
		{
			(*e_iter)->initialize(p);
		}
	}

	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_imglyrmutex);
		std::vector<osg::ref_ptr<ImageLayer>>::iterator i_iter =  _imglyrs.begin();
		for(i_iter;i_iter!=_imglyrs.end();++i_iter)
		{
			(*i_iter)->initialize(p);
		}
	}

	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_fealyrmutex);
		std::vector<osg::ref_ptr<FeatureLayer>>::iterator f_iter =  _featurelyrs.begin();
		for(f_iter;f_iter!=_featurelyrs.end();++f_iter)
		{
			(*f_iter)->initialize(p);
		}
	}

	Init();
}

void Terrain::unInitialize(ProgressBase* p/* = NULL*/)
{
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_elelyrmutex);
		std::vector<osg::ref_ptr<ElevationLayer>>::iterator e_iter = _elelayers.begin();
		for(e_iter;e_iter!=_elelayers.end();++e_iter)
		{
			(*e_iter)->unInitialize(p);
		}
	}

	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_imglyrmutex);
		std::vector<osg::ref_ptr<ImageLayer>>::iterator i_iter =  _imglyrs.begin();
		for(i_iter;i_iter!=_imglyrs.end();++i_iter)
		{
			(*i_iter)->unInitialize(p);
		}
	}

	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_fealyrmutex);
		std::vector<osg::ref_ptr<FeatureLayer>>::iterator f_iter =  _featurelyrs.begin();
		for(f_iter;f_iter!=_featurelyrs.end();++f_iter)
		{
			(*f_iter)->unInitialize(p);
		}
	}

}

void Terrain::setMaxLevel(unsigned int level)
{
	_maxlevel = level;
}

unsigned int Terrain::getMaxLevel() const
{
	return _maxlevel;
}

void Terrain::setVerticalScale(float scale)
{
	//TODO:更新场景

	_verticalscale=scale;
}

float Terrain::getVerticalScale() const
{
	return _verticalscale;
}

void Terrain::setSkirtRadio(float radio)
{
	if(radio<0.f)
		return;
	//TODO:更新场景

	_skitradio=radio;
}

float Terrain::getSkirtRadio() const
{
	return _skitradio;
}

void Terrain::setMinTileRange(float radio)
{
	if(radio<0.f)
		return;
	//TODO:更新场景

	_mintilerange=radio;
}

void Terrain::setTileSize(unsigned int size)
{
	_tilesize=size;
}

unsigned int Terrain::getTileSize() const
{
	return _tilesize;
}

void Terrain::setImageSize(unsigned int size)
{
	_imagesize = size;
}

unsigned int Terrain::getImageSize() const
{
	return _imagesize;
}

float Terrain::getMinTileRange() const
{
	return _mintilerange;
}

bool Terrain::isGeoCentric() const
{
	return getEllipsoidModel()!=NULL;
}

void Terrain::addEvelationLayer(ElevationLayer* elelyr)
{
	if(!elelyr)
		return;

	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_elelyrmutex);
		elelyr->setParentTerrain(this);
		_elelayers.push_back(elelyr);
	}

	//TODO:更新场景
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_cachemutex);

		if(_tilecache.empty())
			return;

		TerrainTiles::iterator iter = _tilecache.begin();
		for(;iter!=_tilecache.end();++iter)
		{
			TerrainTile* t = (*iter).second.get();

			Height* hf = elelyr->CreatHeight(t,getTileSize());
			HeightProxy* hp = new HeightProxy(hf);
			t->addHeight(elelyr->getUID(),hp);

			if(hp->get())
				t->dirtyHeight();
		}

	}
}

void Terrain::insertEvelationLayer(ElevationLayer* elelyr,unsigned int pos)
{
	if(!elelyr)
		return;

	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_elelyrmutex);
		if(pos>_elelayers.size())//超过范围，插个屁？
			return;

		elelyr->setParentTerrain(this);
		_elelayers.insert(_elelayers.begin()+pos,elelyr);
	}

	//TODO:更新场景
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_cachemutex);

		if(_tilecache.empty())
			return;
		TerrainTiles::iterator iter = _tilecache.begin();
		for(;iter!=_tilecache.end();++iter)
		{
			TerrainTile* t = (*iter).second.get();


			Height* hf = elelyr->CreatHeight(t,getTileSize());
			HeightProxy* hp = new HeightProxy(hf);

			t->insertHeight(elelyr->getUID(),pos,hp);

			if(hp->get())
				t->dirtyHeight();
		}
	}
}

void Terrain::removeEvelationLayer(ElevationLayer* elelyr)
{
	if(!elelyr)
		return;

	unsigned int uid = elelyr->getUID();

	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_elelyrmutex);
		bool bfind = false;
		std::vector<osg::ref_ptr<ElevationLayer>>::iterator e_iter = _elelayers.begin();
		for(e_iter;e_iter!=_elelayers.end();++e_iter)
		{
			if((*e_iter)==elelyr)
			{
				bfind = true;
				break;
			}
		}
		if(!bfind)
			return;

		_elelayers.erase(e_iter);
	}

	//TODO:更新场景
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_cachemutex);

		if(_tilecache.empty())
			return;
		TerrainTiles::iterator iter = _tilecache.begin();
		for(;iter!=_tilecache.end();++iter)
		{
			TerrainTile* t = (*iter).second.get();
			bool ndtodirty = false;
			if(t->getHeight(uid))
				ndtodirty = true;
			t->removeHeight(uid);
			t->dirtyHeight();
		}
	}

}

unsigned int Terrain::getElevationLayersCount()
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_elelyrmutex);
	return _elelayers.size();
}

ElevationLayer* Terrain::getEvelationLayer(unsigned int i)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_elelyrmutex);
	if(i>=_elelayers.size())
		return NULL;
	return _elelayers[i].get();
}

ElevationLayer* Terrain::getEvelationLayerByUid(unsigned int uid)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_elelyrmutex);
	for(unsigned int i=0;i<_elelayers.size();++i)
	{
		ElevationLayer* lyr = _elelayers[i];
		if(lyr->getUID()==uid)
		{
			return lyr;
		}
	}

	return NULL;
}

void Terrain::setElevationLayerPos(ElevationLayer* elelyr,unsigned int newpos)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_elelyrmutex);
	if(!elelyr)
		return;
	if(newpos>_elelayers.size())//超过范围，插个屁？
		return;
	std::vector<osg::ref_ptr<ElevationLayer>>::iterator e_iter = _elelayers.begin();
	for(e_iter;e_iter!=_elelayers.end();++e_iter)
	{
		if((*e_iter)==elelyr)
		{
			osg::ref_ptr<ElevationLayer> temp = *e_iter;
			removeEvelationLayer(temp.get());
			insertEvelationLayer(temp.get(),newpos);
			break;
		}
	}

}

unsigned int Terrain::getElevationLayerPos(ElevationLayer* elelyr)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_elelyrmutex);
	if(!elelyr)
		return 0;
	unsigned int result = 0;
	for(unsigned int i=0;i<_elelayers.size();++i)
	{
		ElevationLayer* lyr = _elelayers[i];
		if(lyr==elelyr)
		{
			return result;
		}
		result++;
	}

	return result;
}

void Terrain::addImageLayer(ImageLayer* imglyr)
{
	if(!imglyr)
		return;

	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_imglyrmutex);
		if(!imglyr)
			return;

		imglyr->setParentTerrain(this);
		_imglyrs.push_back(imglyr);
	}


	//TODO:更新场景
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_cachemutex);

		if(_tilecache.empty())
			return;
		TerrainTiles::iterator iter = _tilecache.begin();
		for(;iter!=_tilecache.end();++iter)
		{
			TerrainTile* t =(*iter).second.get();

			osg::Image* img =imglyr->CreatImage(t,getImageSize());
			ImageProxy* ip = new ImageProxy(img);
			t->addImage(imglyr->getUID(),ip);

			if(ip->get())
				t->dirtyImage();
		}
	}
}

void Terrain::insertImageLayer(ImageLayer* imglyr, unsigned int pos)
{
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_imglyrmutex);
		if(!imglyr)
			return;
		if(pos>_imglyrs.size())//超过范围，插个屁？
			return;

		imglyr->setParentTerrain(this);
		_imglyrs.insert(_imglyrs.begin()+pos,imglyr);
	}

	//TODO:更新场景
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_cachemutex);

		if(_tilecache.empty())
			return;
		TerrainTiles::iterator iter = _tilecache.begin();
		for(;iter!=_tilecache.end();++iter)
		{
			TerrainTile* t = (*iter).second.get();

			osg::Image* img =imglyr->CreatImage(t,getImageSize());
			ImageProxy* ip = new ImageProxy(img);
			t->InsertImage(imglyr->getUID(),ip,pos);
			if(ip->get())
				t->dirtyImage();
		}
	}
}

void Terrain::removeImageLayer(ImageLayer* imglyr)
{
	if(!imglyr)
		return;
	unsigned int uid = imglyr->getUID();

	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_imglyrmutex);
		bool bfind = false;
		std::vector<osg::ref_ptr<ImageLayer>>::iterator i_iter = _imglyrs.begin();
		for(i_iter;i_iter!=_imglyrs.end();++i_iter)
		{
			if((*i_iter)==imglyr)
			{
				bfind = true;
				break;
			}
		}
		if(!bfind)
			return;

		_imglyrs.erase(i_iter);
	}
	//TODO:更新场景
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_cachemutex);

		if(_tilecache.empty())
			return;
		TerrainTiles::iterator iter = _tilecache.begin();
		for(;iter!=_tilecache.end();++iter)
		{
			TerrainTile* t =(*iter).second.get();
			bool ndtodirty = false;
			if(t->getImage(uid))
				ndtodirty = true;
			t->removeImage(uid);
			if(ndtodirty)
				t->dirtyImage();
		}
	}
}

unsigned int Terrain::getImageLayersCount() 
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_imglyrmutex);
	return _imglyrs.size();
}

ImageLayer* Terrain::getImageLayer(unsigned int i)
{
	OpenThreads::ScopedLock< OpenThreads::Mutex> lock(_imglyrmutex);
	if(i>=_imglyrs.size())
		return NULL;
	return _imglyrs[i].get();
}

ImageLayer* Terrain::getImageLayerByUid(unsigned int uid) 
{
	OpenThreads::ScopedLock< OpenThreads::Mutex> lock(_imglyrmutex);
	for(unsigned int i=0;i<_imglyrs.size();++i)
	{
		ImageLayer* lyr = _imglyrs[i];
		if(lyr->getUID()==uid)
		{
			return lyr;
		}
	}

	return NULL;
}

void Terrain::setImageLayerPos(ImageLayer* imglyr, unsigned int newpos)
{
	if(!imglyr)
		return;
	if(newpos>_imglyrs.size())//超过范围，插个屁？
		return;

	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> _lock(_imglyrmutex);
		std::vector<osg::ref_ptr<ImageLayer>>::iterator i_iter = _imglyrs.begin();
		for(i_iter;i_iter!=_imglyrs.end();++i_iter)
		{
			if((*i_iter)==imglyr)
			{
				osg::ref_ptr<ImageLayer> temp = *i_iter;
				removeImageLayer(temp.get());
				insertImageLayer(temp.get(),newpos);
				break;
			}
		}
	}

}

unsigned int Terrain::getImageLayerPos(ImageLayer* imglyr) 
{
	OpenThreads::ScopedLock< OpenThreads::Mutex> _lock(_imglyrmutex);
	if(!imglyr)
		return 0;
	unsigned int result = 0;

	for(unsigned int i=0;i<_imglyrs.size();++i)
	{
		ImageLayer* lyr = _imglyrs[i];
		if(lyr==imglyr)
		{
			return result;
		}
		result++;
	}

	return result;
}

void Terrain::addFeatureLayer(FeatureLayer* flyr)
{
	if(!flyr)
		return;
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_fealyrmutex);

		flyr->setParentTerrain(this);
		_featurelyrs.push_back(flyr);
	}

	//TODO:更新场景
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_cachemutex);

		if(_tilecache.empty())
			return;
		TerrainTiles::iterator iter = _tilecache.begin();
		for(;iter!=_tilecache.end();++iter)
		{
			TerrainTile* t = (*iter).second.get();

			FeatureGroupNode* fg = flyr->createFeatureGroupNode(t);
			if(fg)
			{
				t->addFeatureGroupNode(flyr->getUID(),fg);
				t->dirtyFeature();
			}
		}
	}
}

void Terrain::removeFeatureLayer(FeatureLayer* flyr)
{
	if(!flyr)
		return;

	unsigned int uid = flyr->getUID();

	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_fealyrmutex);

		bool bfind = false;
		std::vector<osg::ref_ptr<FeatureLayer>>::iterator f_iter = _featurelyrs.begin();
		for(f_iter;f_iter!=_featurelyrs.end();++f_iter)
		{
			if((*f_iter)==flyr)
			{
				bfind = true;
				break;
			}
		}
		if(!bfind)
			return;
		_featurelyrs.erase(f_iter);
	}

	//TODO:更新场景
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_cachemutex);

		if(_tilecache.empty())
			return;
		TerrainTiles::iterator iter = _tilecache.begin();
		for(;iter!=_tilecache.end();++iter)
		{
			TerrainTile* t = (*iter).second.get();
			bool ndtodirty = false;
			if(t->getFeatureGroupNode(uid))
				ndtodirty = true;
			t->removeFeatureGroupNode(uid);
			t->dirtyFeature();
		}
	}
}

unsigned int Terrain::getFeatureLayersCount()
{
	OpenThreads::ScopedLock< OpenThreads::Mutex> lock(_fealyrmutex);
	return _featurelyrs.size();
}

FeatureLayer* Terrain::getFeatureLayer(unsigned int i) 
{
	OpenThreads::ScopedLock< OpenThreads::Mutex> lock(_fealyrmutex);
	if(i>=_featurelyrs.size())
		return NULL;
	return _featurelyrs[i].get();
}

FeatureLayer* Terrain::getFeatureLayerByUid(unsigned int uid) 
{
	OpenThreads::ScopedLock< OpenThreads::Mutex> lock(_fealyrmutex);

	for(unsigned int i=0;i<_featurelyrs.size();++i)
	{
		FeatureLayer* lyr = _featurelyrs[i];
		if(lyr->getUID()==uid)
		{
			return lyr;
		}
	}

	return NULL;
}

void Terrain::applyElvLayers(TerrainTile* tile) 
{
	if(!tile)
		return;

	{
		OpenThreads::ScopedLock< OpenThreads::Mutex> lock(_elelyrmutex);

		for(unsigned int i=0;i<_elelayers.size();++i)
		{
			ElevationLayer* lyr = _elelayers[i];

			Height* hf = lyr->CreatHeight(tile,getTileSize());
			HeightProxy* hp = new HeightProxy(hf);

			tile->addHeight(lyr->getUID(),hp);
		}
	}
}

void Terrain::applyFeatureLayers(TerrainTile* tile) 
{
	if(!tile)
		return;

	{
		OpenThreads::ScopedLock< OpenThreads::Mutex> lock(_fealyrmutex);	

		for(unsigned int i=0;i<_featurelyrs.size();++i)
		{
			FeatureLayer* lyr = _featurelyrs[i];

			FeatureGroupNode* fg = lyr->createFeatureGroupNode(tile);

			//------------------------------------------
			/*osgSim::OverlayNode* overlayNode = new osgSim::OverlayNode(osgSim::OverlayNode::OBJECT_DEPENDENT_WITH_ORTHOGRAPHIC_OVERLAY);
			overlayNode->setContinuousUpdate(true);
			overlayNode->setOverlaySubgraph(fg);
			//overlayNode->setOverlayBaseHeight(1);
			overlayNode->addChild(tile->getTileSurfaceNode());

			osg::Group * root = new osg::Group();
			root->addChild(overlayNode);

			if (root)
			{
				tile->addFeatureGroupNode(lyr->getUID(),dynamic_cast<owScene::FeatureGroupNode*>(root));
			}*/
			//------------------------------------------
			if(fg)
				tile->addFeatureGroupNode(lyr->getUID(),fg);
		}
	}

}

void Terrain::applyImageLayers(TerrainTile* tile) 
{
	if(!tile)
		return;

	{
		OpenThreads::ScopedLock< OpenThreads::Mutex> lock(_imglyrmutex);

		for(unsigned int i=0;i<_imglyrs.size();++i)
		{
			ImageLayer* lyr = _imglyrs[i];
			osg::Image* img = lyr->CreatImage(tile,getImageSize());
			ImageProxy* ip = new ImageProxy(img);
			tile->addImage(lyr->getUID(),ip);
		}
	}
}


Terrain::~Terrain()
{
	removeChild(0,getNumChildren());
}

void Terrain::Init()
{
	//创建根节点
	if(_tilefactroy.valid())
	{
		osg::ref_ptr<osg::Group> outTiles = _tilefactroy->createRoot();
		for(unsigned int i=0;i<outTiles->getNumChildren();++i)
		{
			addChild(outTiles->getChild(i));
		}
	}
}

void Terrain::UnInit()
{

}

TerrainTileFactory* Terrain::getTileFactory() const
{
	return _tilefactroy.get();
}

void Terrain::setTerrainRenderTech(TerrainRenderTech* tech)
{	
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_cachemutex);

	if(!tech)
		return;
	_terrainrendertech = tech;

	//遍历更新块数据
	if(_tilecache.empty())
		return;
	TerrainTiles::iterator iter = _tilecache.begin();
	for(iter;iter!=_tilecache.end();++iter)
	{
		_terrainrendertech->apply((*iter).second.get());
	}
}

TerrainRenderTech* Terrain::getTerrainRenderTech()
{
	return _terrainrendertech.get();
}

const TerrainRenderTech* Terrain::getTerrainRenderTech() const
{
	return _terrainrendertech.get();
}


//void Terrain::setAtmTerrainRenderTech(TerrainRenderTech* tech)
//{	
//	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_cachemutex);
//
//	if(!tech)
//		return;
//	_atmterrainrendertech = tech;
//
//	if(_atmterrainrendertech->GetOSGNode())
//		addChild(_atmterrainrendertech->GetOSGNode());
//
//	//遍历更新块数据
//	if(_tilecache.empty())
//		return;
//	TerrainTiles::iterator iter = _tilecache.begin();
//	for(iter;iter!=_tilecache.end();++iter)
//	{
//		_atmterrainrendertech->apply((*iter).second.get());
//	}
//}
//
//TerrainRenderTech* Terrain::getAtmTerrainRenderTech()
//{
//	return _atmterrainrendertech.get();
//}
//
//const TerrainRenderTech* Terrain::getAtmTerrainRenderTech() const
//{
//	return _atmterrainrendertech.get();
//}


void Terrain::registry()
{
	s_terrain_uid++;
	_uid = s_terrain_uid;
	owScene::Registry::instance().registTerrain(this);
}

void Terrain::validate()
{
	//地理范围
	if(!_sp.valid() || !_sp->isValid())
	{
		std::ostringstream os;
		os<<"输入地理范围和投影不正确！创建默认的地理范围(-180，180，-90,90)和投影（WGS84）";
		LOG_WARNING(os.str());
		_sp = new SpatialProperty(new GeoExtent(
			DEFAULTMINX,DEFAULTMINY,DEFAULTMAXX,DEFAULTMAXY),SpatialReference::create(DEFAULTSPSTRING));
	}

	const SpatialReference* srs = _sp->getSrs();
	if(srs)
	{
		setFormat(srs->getInitType());
		setCoordinateSystem(srs->getInitString());
		if(srs->isGeographic() && srs->getEllipsoid())
		{
			const EllipsoidModel* em = srs->getEllipsoid();
			setEllipsoidModel(new EllipsoidModel(em->getRadiusEquator(),em->getRadiusPolar()));
		}
	}

	//顶级分块
	const GeoExtent* ex = _sp->getGeoExtent();

	double w = ex->width();
	double h = ex->height();

	if(osg::equivalent(w,h))
	{
		_numTilesWideAtLod0 = 1;
		_numTilesHighAtLod0 = 1;
	}
	else
	{
		_numTilesWideAtLod0 = w>h ? (osg::equivalent(fmodf(w,h),0.f) ? unsigned int(w/h) : unsigned int(w/h)+1) : 1;
		_numTilesHighAtLod0 = w>h ? 1 : (osg::equivalent(fmodf(w,h),0.f) ? unsigned int(w/h) : unsigned int(w/h)+1);
	}


	//块工厂
	_tilefactroy = new TerrainTileFactory(this);

	//创建渲染技术
	_terrainrendertech = new ImageLayersRenderTech(ImageLayersRenderTech::AUTO);

	//背面裁剪,terrainnode朝向地心为前面,背向地心为背面
	getOrCreateStateSet()->setAttributeAndModes(new CullFace(CullFace::FRONT), StateAttribute::ON);


}

void Terrain::registTerrainTile(TerrainTile* tile)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_cachemutex);
	if(!tile)
		return;
	_tilecache[tile->getTileKey().tostring()]=tile;
	//std::cout<<"registTerrainTile: "<<"TileCache size is"<<_tilecache.size()<<std::endl;
}

void Terrain::unregisTerrainTile(TerrainTile* tile)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_cachemutex);
	if(!tile)
		return;
	if(_tilecache.empty())
		return;
	TerrainTiles::iterator iter = _tilecache.find(tile->getTileKey().tostring());
	if(iter!=_tilecache.end())
	{
		_tilecache.erase(iter);
		//std::cout<<"unregistTerrainTile "<<"TileCache size is"<<_tilecache.size()<<std::endl;
	}
}

TerrainTile* Terrain::getRegistTerrainTile(const TileKey& key)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_cachemutex);
	if(_tilecache.empty())
		return NULL;
	TerrainTiles::iterator iter = _tilecache.find(key.tostring());
	if(iter!=_tilecache.end())
	{
		return (*iter).second.get();
	}
	return NULL;
}

void Terrain::read(const Config& config)
{
	//TODO
}

void Terrain::write(Config& config) const
{
	//TODO
}

unsigned int Terrain::getNumTilesWideAtLod0() const
{
	return _numTilesWideAtLod0;
}

unsigned int Terrain::getNumTilesHighAtLod() const
{
	return _numTilesHighAtLod0;
}