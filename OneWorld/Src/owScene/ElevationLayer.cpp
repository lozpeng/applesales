#include <owScene/ElevationLayer.h>

using namespace owScene;

ElevationLayer::ElevationLayer()
{
	;
}

ElevationLayer::ElevationLayer(const ElevationLayer& lyr, const CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/) : Layer(lyr,copyop)
{
	;
}

ElevationLayer::~ElevationLayer()
{
	
}

void ElevationLayer::setEnable(bool enable)
{
	//TODO
}

bool ElevationLayer::getEnable()
{
	//TODO

	return false;
}

void ElevationLayer::read(const Config& config)
{
	Layer::read(config);
	//TODO
}

void ElevationLayer::write(Config& config)
{
	Layer::write(config);
	//TODO
}