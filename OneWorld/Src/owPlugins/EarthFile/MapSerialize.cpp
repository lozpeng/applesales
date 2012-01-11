

#include <owPlugins/EarthFile/MapOptions.h>
#include <owPlugins/EarthFile/MapSerialize.h>
#include <owScene/RasterSource.h>
#include <owScene/FeatureLayer.h>
#include <owScene/DataSourceFactory.h>
#include <owScene/LayerFactory.h>
#include <owScene/ModelWorkSpace.h>


using namespace owPlugins;
using namespace owScene;


static int ReceivesShadowTraversalMask = 0x1;
static int CastsShadowTraversalMask = 0x2;

owScene::Scene* MapSerialize::deserialize( const Config& conf, const std::string& referenceURI )
{
	MapOptions mapOptions( conf.child( "options" ) );

	// the reference URI allows osgEarth to resolve relative paths within the configuration
	mapOptions.referenceURI() = referenceURI;

	//data source
	Config ds = conf.child("datasource");

	//raster source
	ConfigSet images = ds.children("rastersource");
	for(ConfigSet::iterator i=images.begin(); i!=images.end(); i++)
	{
		Config image = *i;
		std::string name = image.value("name");

		RasterSource* rastersouce = DataSourceFactory::Instance().createRasterSource(image);
		if(rastersouce)
			DataSourceFactory::Instance().registryDataSource(name,rastersouce);


	}

	//feature source
	ConfigSet features = ds.children("featuresource");
	for(ConfigSet::iterator i=features.begin(); i!=features.end(); i++)
	{
		Config feature = *i;
		std::string name = feature.value("name");

		FeatureSource* featuresouce = DataSourceFactory::Instance().createFeatureSource(feature);
		if(featuresouce)
			DataSourceFactory::Instance().registryDataSource(name,featuresouce);

	}

	//�������ڵ�
	owScene::Scene* root = new owScene::Scene;
	root->Initialize();

	//�������Σ����ͼ��
	owScene::Terrain* t = new owScene::Terrain();
	root->SetTerrain(t);

	int tilesize = mapOptions.getConfig().value<int>("tilesize",64);
	int imagesize = mapOptions.getConfig().value<int>("imagesize",256);

	t->setImageSize(imagesize);
	t->setTileSize(tilesize);

	//layers
	Config layers = conf.child("layers");

	//image layer
	ConfigSet imagelayers = layers.children("image");
	for(ConfigSet::iterator i=imagelayers.begin(); i!=imagelayers.end(); i++)
	{
		Config imagelayer = *i;

		ImageLayer* img = LayerFactory::Instance().createImageLayer(imagelayer);
		t->addImageLayer(img);
	}

	//feature layer
	ConfigSet featurelayers = layers.children("feature");
	for(ConfigSet::iterator i=featurelayers.begin(); i!=featurelayers.end(); i++)
	{
		Config featurelayer = *i;

		FeatureLayer* feature = LayerFactory::Instance().createFeatureLayer(featurelayer);	
		t->addFeatureLayer(feature);
	}

	ConfigSet elelayers = layers.children("elevation");
	for(ConfigSet::iterator i=elelayers.begin(); i!=elelayers.end(); i++)
	{
		Config elelayer = *i;

		ElevationLayer* ele = LayerFactory::Instance().createElevationLayer(elelayer);	
		t->addEvelationLayer(ele);
	}

	t->Initialize();

	//
	Config model = conf.child("model");
	osg::Group* modelRoot = new osg::Group;

	ConfigSet workspaces = model.children("workspace");
	for(ConfigSet::iterator i=workspaces.begin(); i!=workspaces.end(); i++)
	{
		owScene::ModelWorkSpace* modelspace = new owScene::ModelWorkSpace;
		Config spaceconf = *i;
		modelspace->read(spaceconf);

		Config sets = spaceconf.child("sets");
		ConfigSet confModelSets = sets.children("set");

		for(ConfigSet::iterator k=confModelSets.begin(); k!=confModelSets.end(); k++)
		{
			Config confModelSet = *k;
			ModelSet* modelSet = new ModelSet;

			modelSet->setSrs(modelspace->getSrs());
			modelSet->read(confModelSet);
			modelspace->AddMoelSet(modelSet);
		}

		modelRoot->addChild(modelspace);

	}
	root->SetModelRoot(modelRoot);

	return root;
}
