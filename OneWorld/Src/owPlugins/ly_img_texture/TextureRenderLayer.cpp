#include <owPlugins/ly_img_texture/TextureRenderLayer.h>
#include <owScene/DataSourceFactory.h>
#include <owScene/PreRenderGroup.h>
#include <owScene/TerrainTile.h>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/LineWidth>
#include <osg/Hint>
#include <osg/PolygonMode>
#include <osg/Texture2D>
#include <osgDB/WriteFile>
#include <osgDB/ReadFile>
#include <osgUtil/Tessellator>
#include <osgUtil/DelaunayTriangulator>

using namespace owPlugins;
using namespace owUtil;

bool TextureRenderLayer::initialize(ProgressBase* base/*=NULL*/)
{
	if(!getDataSource())
	{
		if(_sourcename.empty())
			return false;

		DataSource* datasource = DataSourceFactory::Instance().getRegistryDataSource(_sourcename);

		if(!datasource)
			return false;

		setDataSource(datasource);
	}


	FeatureSource* feature_source = dynamic_cast<FeatureSource*>(getDataSource());
	if(!feature_source)
		return false;

	if(!feature_source->Connect(base))
		return false;

	if(!feature_source->bValid())
		return false;

	_image = osgDB::readImageFile(_imagefile);

	//
	setSP(feature_source->getSP());

	//
	setValid(true);

	return true;
}

bool TextureRenderLayer::unInitialize(ProgressBase* base/*=NULL*/)
{
	if(getDataSource())
		return getDataSource()->disConnect(base);
	return true;
}

osg::Image* TextureRenderLayer::CreatImage(const TerrainTile* tile,unsigned int tilesize,ProgressBase* p/*=NULL*/)
{
	if(!bValid())
		return NULL;

	if(!tile)
		return NULL;

	if(tile->getTileKey().level()<getMinLevel() || tile->getTileKey().level()>getMaxLevel())
		return NULL;

	//获取矢量节点集
	osg::Group* g = createFeatureGroup(tile,p);
	if(!g)
		return NULL;

	//设置osg::Image
	osg::ref_ptr<osg::Image> image = new osg::Image;
	image->allocateImage(tilesize, tilesize, 1, GL_RGBA, GL_UNSIGNED_BYTE);
	image->setName(tile->getTileKey().tostring());
	image->setDataVariance(osg::Object::DYNAMIC);

	//设置overlay相机
	owScene::PreRenderGroup* group = owScene::getGlobalPreRenderGroup();
	osg::Camera* camera =  group->createCamera(image, tile->getSP()->getGeoExtent(), tilesize);

	//
	camera->addChild(g);
	group->addCamera(camera);
	return image.release();
}

void TextureRenderLayer::read(const Config& config)
{
	_sourcename = config.attr("datasource");
	_imagefile = config.attr("imagefile");
}

void TextureRenderLayer::write(Config& config) const
{

}

osg::Group* TextureRenderLayer::createFeatureGroup(const TerrainTile* tile, ProgressBase* p)
{
	if(!tile)
		return NULL;

	FeatureSource* fs = (FeatureSource*)getDataSource();
	if(!fs)
		return NULL;

	const SpatialProperty* sp = tile->getSP();
	const SpatialProperty* local_sp = getSP();

	if(!sp || !sp->getSrs() || !local_sp || !local_sp->getSrs())
		return NULL;

	FeatureCursor* fc;

	if(sp->getSrs()->isEquivalentTo(local_sp->getSrs()))
	{
		const GeoExtent* q_ex = sp->getGeoExtent();
		fc = fs->createFeatureCursor(*sp);
	}
	else
	{
		osg::ref_ptr<GeoExtent> q_ex = new GeoExtent(sp->getGeoExtent());
		osg::ref_ptr<SpatialProperty> sp2 = new SpatialProperty(q_ex.get(), ((SpatialProperty*)local_sp)->getSrs());

		sp->getSrs()->transformExtent(local_sp->getSrs(),
			q_ex->xMin(),q_ex->yMin(),q_ex->xMax(),q_ex->yMax());

		sp2->setGeoExtent(q_ex.get());
		fc = fs->createFeatureCursor(*sp2);
	}

	if(!fc)
		return NULL;

	osg::Group* g = new osg::Group;

	while(fc->hasNext())
	{
		Feature* f = fc->next();
		osg::Node* n = readOrGetFromCache(tile,f);
		if(n)
		{
			g->addChild(n);
		}
		opcache();
	}

	//
	osg::StateSet *state = g->getOrCreateStateSet();
	osg::ref_ptr<osg::LineWidth>  lw = new osg::LineWidth(0.1);
	state->setAttribute(lw.get());

	return g;

}

void TextureRenderLayer::opcache()
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
	if(_nodecache.size()>10)
	{
		unsigned int isize = 0;
		while(isize<10)
		{
			_nodecache.erase(_nodecache.begin());
			isize++;
		}
	}
}

osg::Node* TextureRenderLayer::readOrGetFromCache(const TerrainTile* tile, Feature* f)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
	if(!tile || !f)
		return NULL;
	NodeCache::iterator iter = _nodecache.find(f->getOID());
	if(iter!=_nodecache.end())
		return (*iter).second.get();
	else
	{
		osg::Node* node = createFeatureNode(tile,f);
		if(!node)
			return NULL;
		node->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
		_nodecache[f->getOID()]=node;
		return node;
	}
}

osg::Node* TextureRenderLayer::createFeatureNode(const TerrainTile* tile, Feature* f)
{
	
	osg::Geode *geode= new osg::Geode;

	GeoShapeList shapes = f->getShapes();

	for(int i=0; i<shapes.size(); i++)
	{
		osg::Geometry* geometry = new osg::Geometry;
		osg::Vec3Array* vertexs = new osg::Vec3Array;
		osg::Vec3Array* nomals = new osg::Vec3Array;
		GeoShape shape = shapes[i];

		geometry->setVertexArray(vertexs);
		geometry->setNormalArray(nomals);
		nomals->push_back(Vec3(0,0,1));
		geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

		//纹理
		//------------------------------------------
		osg::Texture2D* t2d = new osg::Texture2D;
		t2d->setDataVariance(osg::Object::DYNAMIC); 
		t2d->setWrap(osg::Texture2D::WRAP_S, osg::Texture2D::REPEAT);
		t2d->setWrap(osg::Texture2D::WRAP_T, osg::Texture2D::REPEAT);
		t2d->setWrap(osg::Texture2D::WRAP_R, osg::Texture2D::REPEAT);
		t2d->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::NEAREST);
		t2d->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::NEAREST);

		t2d->setImage(_image.get());

		geometry->getOrCreateStateSet()->setTextureAttributeAndModes(0,t2d, osg::StateAttribute::ON);
		geometry->getOrCreateStateSet()->setMode(GL_BLEND,osg::StateAttribute::ON);
		geometry->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
		//------------------------------------------

		geode->addDrawable(geometry);


		//构建顶点数组
		int l=0;
		const SpatialReference* srs = getSP()->getSrs();
		const SpatialReference* tile_srs = tile->getSP()->getSrs();

		for(int j=0; j<shape.getPartCount(); j++)
		{
			std::vector<osg::Vec3d> ins, outs;
			osg::DrawElementsUShort* dui = new osg::DrawElementsUShort(osg::DrawElements::POLYGON);

			GeoPointList points= shape.getPart(j);
			ins.insert(ins.end(), points.begin(), points.end());

			if(!srs->isEquivalentTo(tile_srs))
			{
				srs->transformPoints(tile_srs, &ins);
			}

			for(int k=0; k<ins.size() - 1; k++)
			{
				//顶点
				Vec3 v(ins[k]._v[0],ins[k]._v[1],ins[k]._v[2]);
				vertexs->push_back(ins[k]);

				//图元
				dui->push_back(l++);
			}

			if (_image.valid()) {
				float repeat=0.0005, ry=0.0005; // how often to repeat texture
				osg::Vec2Array *tcoords=new osg::Vec2Array;
				for (osg::Vec3Array::iterator itr=vertexs->begin(); itr!=vertexs->end(); itr++) {
					osg::Vec2 tcatxy((*itr).x()/repeat,(*itr).y()/ry);
					tcoords->push_back(tcatxy);
				}
				geometry->setTexCoordArray(0,tcoords);
			}

			//添加图元集
			geometry->addPrimitiveSet(dui);

		}
		osg::ref_ptr<osgUtil::Tessellator> tscx=new osgUtil::Tessellator; // this assembles all the constraints
		tscx->setTessellationType(osgUtil::Tessellator::TESS_TYPE_GEOMETRY);
		//tscx->setBoundaryOnly(true);
		tscx->setWindingType( osgUtil::Tessellator::TESS_WINDING_NONZERO); 

		tscx->retessellatePolygons(*(geometry)); 
	}

	return geode;

}
