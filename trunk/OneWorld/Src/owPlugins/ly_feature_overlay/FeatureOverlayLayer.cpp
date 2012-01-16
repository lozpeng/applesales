#include <owPlugins/ly_feature_overlay/FeatureOverlayLayer.h>
#include <owScene/DataSourceFactory.h>
#include <owScene/PreRenderGroup.h>
#include <owScene/TerrainTile.h>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/LineWidth>
#include <osg/Hint>
#include <osg/PolygonMode>
#include <osgDB/WriteFile>
#include <osgUtil/Tessellator>

using namespace owPlugins;
using namespace owUtil;

FeatureOverlayLayer::FeatureOverlayLayer() :  _color(1.0, 1.0, 0.0, 0.4), _line_width(1.0)
{

}

bool FeatureOverlayLayer::initialize(ProgressBase* base/*=NULL*/)
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

	//
	setSP(feature_source->getSP());

	//
	setValid(true);

	return true;
}

bool FeatureOverlayLayer::unInitialize(ProgressBase* base/*=NULL*/)
{
	if(getDataSource())
		return getDataSource()->disConnect(base);
	return true;
}

osg::Image* FeatureOverlayLayer::CreatImage(const TerrainTile* tile,unsigned int tilesize,ProgressBase* p/*=NULL*/)
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
	osg::Camera* camera =  group->createCamera(image.get(), tile->getSP()->getGeoExtent(), tilesize);

	camera->addChild(g);
	group->addCamera(camera);
	return image.release();
}

void FeatureOverlayLayer::read(const Config& config)
{
	_sourcename = config.attr("datasource");
	ImageLayer::read(config);
}

void FeatureOverlayLayer::write(Config& config) const
{

}

osg::Group* FeatureOverlayLayer::createFeatureGroup(const TerrainTile* tile, ProgressBase* p)
{
	if(!tile)
		return NULL;

	FeatureSource* fs = (FeatureSource*)getDataSource();
	if(!fs)
		return NULL;

	if(tile->getTileKey().level()<getMinLevel() || tile->getTileKey().level()>getMaxLevel())
		return NULL;

	const SpatialProperty* sp = tile->getSP();
	const SpatialProperty* local_sp = getSP();

	if(!sp || !sp->getSrs() || !local_sp || !local_sp->getSrs())
		return NULL;

	osg::ref_ptr<FeatureCursor> fc;

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

	if(!fc.valid())
		return NULL;

	//
	osg::Group* g = new osg::Group;
	while(fc->hasNext())
	{
		osg::ref_ptr<Feature> f = fc->next();
		osg::Node* n = createFeatureNode(tile,f.get());
		if(n)
		{
			g->addChild(n);
		}
	}

	//
	osg::StateSet *state = g->getOrCreateStateSet();
	osg::ref_ptr<osg::LineWidth>  lw = new osg::LineWidth(_line_width);
	state->setAttribute(lw.get());

	return g;

}

osg::Node* FeatureOverlayLayer::createFeatureNode(const TerrainTile* tile, Feature* f)
{
	
	osg::Geode *_geode= new osg::Geode;

	GeoShapeList shapes = f->getShapes();

	for(int i=0; i<shapes.size(); i++)
	{
		osg::ref_ptr<osg::Geometry> _geometry = new osg::Geometry;
		osg::ref_ptr<osg::Vec3Array> _vertexs = new osg::Vec3Array;
		osg::ref_ptr<osg::Vec3Array> _nomals = new osg::Vec3Array;
		GeoShape shape = shapes[i];

		_geometry->setVertexArray(_vertexs.get());
		_geometry->setNormalArray(_nomals);
		_nomals->push_back(Vec3(0,0,1));
		_geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

		_geode->addDrawable(_geometry.get());

		//顶点颜色
		osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
		colors->push_back(_color);

		_geometry->setColorArray(colors);
		_geometry->setColorBinding(osg::Geometry::BIND_OVERALL);


		//构建顶点数组
		int l=0;
		const SpatialReference* srs = getSP()->getSrs();
		const SpatialReference* tile_srs = tile->getSP()->getSrs();

		for(int j=0; j<shape.getPartCount(); j++)
		{
			std::vector<osg::Vec3d> ins, outs;


			osg::ref_ptr<osg::DrawElementsUShort> dui = new osg::DrawElementsUShort(osg::DrawElements::LINE_LOOP);

			GeoPointList points= shape.getPart(j);
			ins.insert(ins.end(), points.begin(), points.end());

			if(!srs->isEquivalentTo(tile_srs))
			{
				srs->transformPoints(tile_srs, &ins);
			}

			for(int k=0; k<ins.size(); k++)
			{
				//顶点
				Vec3 v(ins[k]._v[0],ins[k]._v[1],ins[k]._v[2]);
				_vertexs->push_back(ins[k]);

				//图元
				dui->push_back(l++);
			}

			//添加图元集
			_geometry->addPrimitiveSet(dui);

		}

		if(shape.getShapeType() == GeoShape::TYPE_POLYGON)
		{
			osgUtil::Tessellator tess;
			tess.setTessellationType( osgUtil::Tessellator::TESS_TYPE_GEOMETRY );
			tess.setWindingType( osgUtil::Tessellator::TESS_WINDING_POSITIVE );
			tess.retessellatePolygons( *_geometry );
		}

	}

	return _geode;

}
