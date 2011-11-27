
#include <owScene/FeatureLayer.h>
#include <owScene/FeatureNode.h>
#include <owScene/TerrainTile.h>

using namespace owScene;

FeatureLayer::FeatureLayer() : _color(1.0, 1.0, 0.0, 0.4), _height_off(10.0), _line_width(1.0)
{
	;
}

FeatureLayer::FeatureLayer(const FeatureLayer& lyr, const CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/) : Layer(lyr,copyop)
{

}

FeatureSource* FeatureLayer::getFeatureSource()
{
	return dynamic_cast<FeatureSource*>(getDataSource());
}

FeatureGroupNode* FeatureLayer::createFeatureGroupNode(const TerrainTile* tile,ProgressBase* p)
{

	if(!tile)
		return NULL;
	FeatureSource* fs = getFeatureSource();
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

	FeatureGroupNode* g = new FeatureGroupNode;

	while(fc->hasNext())
	{
		osg::ref_ptr<Feature> f = fc->next();
		osg::Node* n = createNode(tile,f.get());
		if(n)
		{
			FeatureNode* fn = new FeatureNode();
			fn->setFeature(f);
			fn->setParentLayer(this);
			fn->addChild(n);
			g->addFeatureNode(fn);
		}
	}

	return g;
}

void FeatureLayer::read(const Config& config)
{
	Layer::read(config);
	//TODO
}

void FeatureLayer::write(Config& config)
{
	Layer::write(config);
	//TODO
}