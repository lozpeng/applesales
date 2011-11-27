#include <owScene/Layer.h>

using namespace owScene;

static unsigned int s_createLayerUID() 
{
	static unsigned int s_uid = 0;
	s_uid++;
	return s_uid;
}

Layer::Layer() : _minLevel(MINLEVEL),_maxLevel(MAXLEVEL),_valid(false),_uid(s_createLayerUID()),_parentTerrain(NULL)
{
	;
}

Layer::Layer(const Layer& lyr, const CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/) : Object(lyr,copyop)
{
	_minLevel=lyr._minLevel;
	_maxLevel=lyr._maxLevel;
	_valid=lyr._valid;
	_uid=lyr._uid;
	_parentTerrain = lyr._parentTerrain;
}

unsigned int Layer::getUID() const
{
	return _uid;
}

void Layer::setLevel(unsigned int min,unsigned int max)
{
	if(min>max)
		return;
	_minLevel = min;
	_maxLevel = max;
}

const SpatialProperty* Layer::getSP() const
{
	return _sp.get();
}

bool Layer::isGlobe()
{
	if (!_sp->getSrs()->isGeographic()) return false;

	if (_sp->getGeoExtent()->width() < 360 && _sp->getGeoExtent()->height() < 180) return false;

	return true;
}

void Layer::read(const Config& config)
{
	_minLevel = config.value<int>("minlevel",MINLEVEL);
	_maxLevel = config.value<int>("maxlevel",MAXLEVEL);
	_layerName = config.value<std::string>("layername","layer");

	setName(_layerName.c_str());
}

void Layer::write(Config& config) const
{
	//TODO
}

void Layer::setDataSource(DataSource* datesource)
{
	//如果数据源已经存在，将不会重新设置数据源
	if(_datasource.valid())
		return;
	_datasource = datesource;
}

DataSource* Layer::getDataSource() const
{
	return _datasource.get();
}