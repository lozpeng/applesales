#include <owScene/TerrainTileFactory.h>
#include <owScene/TilePagedLod.h>
#include <sstream>

using namespace owScene;

TerrainTileFactory::TerrainTileFactory(Terrain* terrain) : _terrain(terrain)
{
	;
}

TerrainTile* TerrainTileFactory::createSubTile(const TileKey& tilekey)
{
	SpatialProperty* sp = calculateSpatialProperty(tilekey);

	if(!sp)
		return NULL;

	TerrainTile* tt = new TerrainTile(tilekey,sp);

	tt->setParentTerrain(_terrain);

	//地表
	_terrain->applyElvLayers(tt);
	tt->dirtyHeight();

	//纹理
	_terrain->applyImageLayers(tt);
	tt->dirtyImage();

	//更新地表和纹理
	tt->dirty();

	//为了使得矢量贴着地面，需要用到地表节点，所以矢量更新放在地表更新之后
	//
	_terrain->applyFeatureLayers(tt);
	//
	tt->dirtyFeature();
	//
	tt->dirty();


	//应用地形渲染技术
	TerrainRenderTech* tech = _terrain->getTerrainRenderTech();
	if(tech)
		tech->apply(tt);

	//应用大气渲染技术
	/*TerrainRenderTech* atmtech = _terrain->getAtmTerrainRenderTech();
	if(atmtech)
		atmtech->apply(tt);*/

	//注册地形块数据
	_terrain->registTerrainTile(tt);

	return tt;
}

osg::Node* TerrainTileFactory::createTile(const TileKey& tilekey)
{
	if(!_terrain)
		return NULL;

	osg::Group* g = new osg::Group;

	TileKey childkey0 = tilekey.sub(0);
	TileKey childkey1 = tilekey.sub(1);
	TileKey childkey2 = tilekey.sub(2);
	TileKey childkey3 = tilekey.sub(3);

	TerrainTile* tt0 = createSubTile(childkey0);
	TerrainTile* tt1 = createSubTile(childkey1);
	TerrainTile* tt2 = createSubTile(childkey2);
	TerrainTile* tt3 = createSubTile(childkey3);

	//如果达到最大级数，不再细分
	if(tilekey.level()==_terrain->getMaxLevel() - 1)
	{
		g->addChild(tt0);
		g->addChild(tt1);
		g->addChild(tt2);
		g->addChild(tt3);
		return g;
	}

	TilePagedLod* p0 = new TilePagedLod(_terrain);
	TilePagedLod* p1 = new TilePagedLod(_terrain);
	TilePagedLod* p2 = new TilePagedLod(_terrain);
	TilePagedLod* p3 = new TilePagedLod(_terrain);

	p0->addChild(tt0);
	p1->addChild(tt1);
	p2->addChild(tt2);
	p3->addChild(tt3);

	//动态计算可见距离，主要目的是使远处的地形更加稀疏，减少面数。
	double minrange = 1.0;
	double maxrange = _terrain->getMinTileRange();
	double range = (maxrange-minrange)*(tilekey.level()+1)/_terrain->getMaxLevel()+minrange;

	double dis0 = tt0->getBound().radius()*range;
	double dis1 = tt1->getBound().radius()*range;
	double dis2 = tt2->getBound().radius()*range;
	double dis3 = tt3->getBound().radius()*range;

	p0->setFileName(0,"");
	p1->setFileName(0,"");
	p2->setFileName(0,"");
	p3->setFileName(0,"");

	p0->setRange(0,dis0,FLT_MAX);
	p1->setRange(0,dis1,FLT_MAX);
	p2->setRange(0,dis2,FLT_MAX);
	p3->setRange(0,dis3,FLT_MAX);

	std::ostringstream os; 
	os<<_terrain->getUID()<<"_"<<childkey0.level()<<"_"<<childkey0.x()<<"_"<<childkey0.y()<<".tile";
	p0->setFileName(1,os.str());
	os.str("");
	os<<_terrain->getUID()<<"_"<<childkey1.level()<<"_"<<childkey1.x()<<"_"<<childkey1.y()<<".tile";
	p1->setFileName(1,os.str());
	os.str("");
	os<<_terrain->getUID()<<"_"<<childkey2.level()<<"_"<<childkey2.x()<<"_"<<childkey2.y()<<".tile";
	p2->setFileName(1,os.str());
	os.str("");
	os<<_terrain->getUID()<<"_"<<childkey3.level()<<"_"<<childkey3.x()<<"_"<<childkey3.y()<<".tile";
	p3->setFileName(1,os.str());

	p0->setRange(1,0,dis0);
	p1->setRange(1,0,dis1);
	p2->setRange(1,0,dis2);
	p3->setRange(1,0,dis3);

	p0->setCenter(tt0->getBound().center());
	p1->setCenter(tt1->getBound().center());
	p2->setCenter(tt2->getBound().center());
	p3->setCenter(tt3->getBound().center());

	g->addChild(p0);
	g->addChild(p1);
	g->addChild(p2);
	g->addChild(p3);

	return g;
}

osg::Group* TerrainTileFactory::createRoot()
{
	osg::Group* g = new osg::Group;
	
	std::vector<TileKey> keys;
	getRootKeys(keys);

	std::vector<TileKey>::iterator iter = keys.begin();
	for(iter;iter!=keys.end();++iter)
	{
		TilePagedLod* p = new TilePagedLod(_terrain);
		TerrainTile* tile = createSubTile(*iter);
		
		p->addChild(tile);
		double dis = tile->getBound().radius()*_terrain->getMinTileRange();
		p->setFileName(0,"");
		p->setRange(0,dis,FLT_MAX);
		std::ostringstream os; os<<_terrain->getUID()<<"_"<<(*iter).level()<<"_"<<(*iter).x()<<"_"<<(*iter).y()<<".tile";
		p->setFileName(1,os.str());
		p->setRange(1,0,dis);
		p->setCenter(tile->getBound().center());
		g->addChild(p);

	}

	return g;
}

void TerrainTileFactory::getRootKeys(std::vector<TileKey>& keys)
{
	if(!_terrain)
		return;
	keys.clear();
	for (unsigned int c = 0; c < _terrain->getNumTilesWideAtLod0(); ++c)
	{
		for (unsigned int r = 0; r < _terrain->getNumTilesHighAtLod(); ++r)
		{
			keys.push_back( TileKey(0, c, r));
		}
	}
}

void TerrainTileFactory::getTileDimensions(unsigned int lod, double& out_width, double& out_height)
{
	if(!_terrain)
		return;
	const SpatialProperty* sp = _terrain->getSP();
	if(!sp)
		return;
	const GeoExtent* ex = sp->getGeoExtent();
	if(!ex)
		return;

	out_width  = (ex->xMax() - ex->xMin()) / (double)(_terrain->getNumTilesWideAtLod0());
	out_height = (ex->yMax() - ex->yMin()) / (double)(_terrain->getNumTilesHighAtLod());

	for (unsigned int i = 0; i < lod; ++i)
	{
		out_width /= 2.0;
		out_height /= 2.0;
	}
}

SpatialProperty* TerrainTileFactory::calculateSpatialProperty(const TileKey& tilekey)
{
	if(!_terrain)
		return NULL;
	int level = tilekey.level();
	int x = tilekey.x();
	int y = tilekey.y();

	double width, height;
	getTileDimensions(level, width, height);

	SpatialProperty* sp = _terrain->getSP();
	if(!sp)
		return NULL;
	const GeoExtent* ex = sp->getGeoExtent();
	if(!ex)
		return NULL;

	double xmin = ex->xMin() + (width * (double)x);
	double ymax = ex->yMax() - (height * (double)y);
	double xmax = xmin + width;
	double ymin = ymax - height;

	return new SpatialProperty(new GeoExtent( xmin, ymin, xmax, ymax ), sp->getSrs());
}