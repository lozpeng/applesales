#include <owPlugins/ly_ele_raster/RasterElevationLayer.h>
#include <owScene/DataSourceFactory.h>
#include <owScene/RasterSource.h>

using namespace owPlugins;

bool RasterElevationLayer::initialize(ProgressBase* base/*=NULL*/)
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

	return true;
}

bool RasterElevationLayer::unInitialize(ProgressBase* base/*=NULL*/)
{
	if(getDataSource())
		return getDataSource()->disConnect(base);
	return true;
}

Height* RasterElevationLayer::CreatHeight(const TerrainTile* tile,unsigned int tilesize,ProgressBase* p/*=NULL*/)
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

	return rastersource->CreatHeight(sp,tilesize,p);
}

void RasterElevationLayer::read(const Config& config)
{
	ElevationLayer::read(config);
	_sourcename = config.attr("datasource");
}

void RasterElevationLayer::write(Config& config) const
{

}