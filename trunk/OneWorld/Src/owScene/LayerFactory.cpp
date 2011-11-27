#include <owScene/LayerFactory.h>
#include <osgDB/ReadFile>

using namespace owScene;


LayerFactory& LayerFactory::Instance()
{
	static LayerFactory s_layerfactory;
	return s_layerfactory;
}

LayerFactory::LayerFactory()
{

}

LayerFactory::~LayerFactory()
{

}

ElevationLayer* LayerFactory::createElevationLayer(const Config& config)
{
	std::string type = config.key();
	if(type!="elevation")
		return NULL;

	std::string driver = config.attr("driver");
	if(driver.empty())
		return NULL;

	std::string filename = "geoscape.ly_ele_"+driver;

	osg::ref_ptr<osgDB::Options> op = new osgDB::Options;
	Config* c = new Config(config);
	op->setUserData(c);

	osg::Object* object = osgDB::readObjectFile(filename,op.get());

	ElevationLayer* elelyr = dynamic_cast<ElevationLayer*>(object);

	if(elelyr)
		return elelyr;

	return NULL;
}	

ImageLayer* LayerFactory::createImageLayer(const Config& config)
{
	std::string type = config.key();
	if(type!="image")
		return NULL;

	std::string driver = config.attr("driver");
	if(driver.empty())
		return NULL;

	std::string filename = "geoscape.ly_img_"+driver;

	osg::ref_ptr<osgDB::Options> op = new osgDB::Options;
	Config* c = new Config(config);
	op->setUserData(c);

	osg::Object* object = osgDB::readObjectFile(filename,op.get());

	ImageLayer* imglyr = dynamic_cast<ImageLayer*>(object);

	if(imglyr)
		return imglyr;

	return NULL;

}

FeatureLayer* LayerFactory::createFeatureLayer(const Config& config)
{
	std::string type = config.key();
	if(type!="feature")
		return NULL;

	std::string driver = config.attr("driver");
	if(driver.empty())
		return NULL;

	std::string filename = "geoscape.ly_feature_"+driver;

	osg::ref_ptr<osgDB::Options> op = new osgDB::Options;
	Config* c = new Config(config);
	op->setUserData(c);

	osg::Object* object = osgDB::readObjectFile(filename,op.get());

	FeatureLayer* featurelyr = dynamic_cast<FeatureLayer*>(object);

	if(featurelyr)
		return featurelyr;

	return NULL;
}