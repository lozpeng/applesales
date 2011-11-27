#include <owScene/ImageLayer.h>

using namespace owScene;

ImageLayer::ImageLayer()
{
	;
}

ImageLayer::ImageLayer(const ImageLayer& lyr, const CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/) : Layer(lyr,copyop)
{
	;
}

ImageLayer::~ImageLayer()
{
	;
}

void ImageLayer::setEnable(bool enable)
{
	//TODO

}

bool ImageLayer::getEnable()
{
	//TODO

	return false;
}

void ImageLayer::read(const Config& config)
{
	Layer::read(config);

	//TODO
}

void ImageLayer::write(Config& config)
{
	Layer::write(config);
	//TODO
}