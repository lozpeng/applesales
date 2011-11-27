#ifndef OWPLUGINS_GDALRASTERSOURCE_H_
#define OWPLUGINS_GDALRASTERSOURCE_H_

#include <owScene/RasterSource.h>

using namespace owScene;
using namespace osg;

namespace owPlugins
{
	class GdalRasterSource : public RasterSource
	{
	public:
		GdalRasterSource();
		~GdalRasterSource();

		META_Object(owPlugins,GdalRasterSource)

	protected:

		GdalRasterSource(const GdalRasterSource& source, const CopyOp& copyop=CopyOp::SHALLOW_COPY)
		{
			//no support
		}

	public:
		virtual std::string	getUrl();
		virtual Height* CreatHeight(const SpatialProperty* sp,unsigned int size,ProgressBase* p=NULL);

		virtual osg::Image* CreateImage(const SpatialProperty* sp,unsigned int size,ProgressBase* p=NULL);

		virtual bool Connect(owUtil::ProgressBase* p =NULL);

		virtual bool disConnect(owUtil::ProgressBase* p = NULL);

	public:

		virtual void read(const Config& config);

		virtual void write(Config& config) const;

	private:

		//读取影像数据
		osg::Image* readImage(const GeoExtent* extent, int size);

		osg::Image* readRGBImage(const GeoExtent* extent, int size);
		osg::Image* readPanImage(const GeoExtent* extent, int size);
		osg::Image* readPalImage(const GeoExtent* extent, int size);
		osg::Image* readAlphaImage(const GeoExtent* extent, int size);
		
		//读取高程数据
		osg::Image* readHeight(const GeoExtent* extent, int size);

	private:

		std::string _url;

		unsigned int _heightChannel;

		unsigned int _imageRChannel;
		unsigned int _imageGChannel;
		unsigned int _imageBChannel;

		unsigned int _imagePChannel;

		unsigned int _alphaChannel;

		unsigned int _paletteChannel;

		unsigned int _width;
		unsigned int _height;
		unsigned int _bands;

		bool _bResample;

		void* _gdalDataSet;
	};
}

#endif //OWPLUGINS_GDALRASTERSOURCE_H_