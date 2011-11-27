#include <owScene/DataSourceFactory.h>
#include <osgDB/ReadFile>

using namespace owScene;

DataSourceFactory& DataSourceFactory::Instance()
{
	static DataSourceFactory s_datasourcefactory;
	return s_datasourcefactory;
}

DataSourceFactory::DataSourceFactory()
{

}

DataSourceFactory::~DataSourceFactory()
{
	_datasources.clear();
}

void DataSourceFactory::registryDataSource(const std::string& name,DataSource* source)
{
	if(!source || name.empty())
		return;
	_datasources[name]=source;
}

void DataSourceFactory::unregistryDataSource(const std::string& name)
{
	if(name.empty())
		return;
	mapDataSource::iterator iter = _datasources.find(name);
	if(iter!=_datasources.end())
		_datasources.erase(iter);
}

DataSource* DataSourceFactory::getRegistryDataSource(const std::string& name)
{
	if(name.empty())
		return NULL;
	mapDataSource::iterator iter = _datasources.find(name);
	if(iter!=_datasources.end())
		return (*iter).second.get();
	return NULL;
}

FeatureSource* DataSourceFactory::createFeatureSource(const Config& config)
{
	std::string type = config.key();
	if(type!="featuresource")
		return NULL;

	std::string driver = config.attr("driver");
	if(driver.empty())
		return NULL;

	std::string filename = "geoscape.ds_feature_"+driver;

	osg::ref_ptr<osgDB::Options> op = new osgDB::Options;
	Config* c = new Config(config);
	op->setUserData(c);

	osg::Object* object = osgDB::readObjectFile(filename,op.get());

	FeatureSource* featuresource = dynamic_cast<FeatureSource*>(object);

	if(featuresource)
		return featuresource;

	return NULL;
}

RasterSource* DataSourceFactory::createRasterSource(const Config& config)
{
	std::string type = config.key();
	if(type!="rastersource")
		return NULL;

	std::string driver = config.attr("driver");
	if(driver.empty())
		return NULL;

	std::string filename = "geoscape.ds_raster_"+driver;

	osg::ref_ptr<osgDB::Options> op = new osgDB::Options;
	Config* c = new Config(config);
	op->setUserData(c);

	osg::Object* object = osgDB::readObjectFile(filename,op.get());

	RasterSource* rastersource = dynamic_cast<RasterSource*>(object);

	if(rastersource)
		return rastersource;

	return NULL;
}