#include <owPlugins/ly_img_raster/RasterImageLayer.h>
#include <owScene/DataSourceFactory.h>
#include <owScene/RasterSource.h>

using namespace owPlugins;

bool RasterImageLayer::initialize(ProgressBase* base/*=NULL*/)
{
	//如果不存在数据源，将从数据源中获取一个数据源。（存在的情况：有可能是在外部调用setDataSource接口设置）
	if(!getDataSource())
	{
		if(_sourcename.empty())
			return false;

		DataSource* datasource = DataSourceFactory::Instance().getRegistryDataSource(_sourcename);

		if(!datasource)
			return false;

		setDataSource(datasource);
	}


	RasterSource* rastersource = dynamic_cast<RasterSource*>(getDataSource());
	if(!rastersource)
		return false;

	if(!rastersource->Connect(base))
		return false;

	if(!rastersource->bValid())
		return false;

	setValid(true);
	//
	setSP(rastersource->getSP());

	return true;
}

bool RasterImageLayer::unInitialize(ProgressBase* base/*=NULL*/)
{
	if(getDataSource())
		return getDataSource()->disConnect(base);
	return true;
}

osg::Image* RasterImageLayer::CreatImage(const TerrainTile* tile,unsigned int tilesize,ProgressBase* p/*=NULL*/)
{
	if(!bValid())
		return NULL;

	const TileKey key = tile->getTileKey();
	const SpatialProperty* sp = tile->getSP();

	if(key.level()<getMinLevel() || key.level()>getMaxLevel())
		return NULL;

	RasterSource* rastersource = dynamic_cast<RasterSource*>(getDataSource());
	if(!rastersource)
		return NULL;

	return rastersource->CreateImage(sp,tilesize,p);
}

void RasterImageLayer::read(const Config& config)
{
	ImageLayer::read(config);
	_sourcename = config.value("datasource");
}

void RasterImageLayer::write(Config& config) const
{

}