#include <osgDB/ReaderWriter>
#include <osgDB/FileNameUtils>
#include <osgDB/Options>
#include <osgDB/Registry>
#include <owPlugins/ly_img_raster/RasterImageLayer.h>

using namespace owPlugins;

class RasterImageLayerFactory : public osgDB::ReaderWriter
{
public:
	RasterImageLayerFactory(){}

	virtual const char* className()
	{
		return "RasterImageLayerFactory";
	}

	virtual bool acceptsExtension(const std::string& extension) const
	{
		return osgDB::equalCaseInsensitive( extension, "ly_img_raster" );
	}

	virtual ReadResult readObject(const std::string& file_name, const Options* opt) const
	{
		if ( !acceptsExtension( osgDB::getFileExtension( file_name ) ) )
		{
			return ReadResult::FILE_NOT_HANDLED;
		}

		if(!opt)
			return ReadResult::ERROR_IN_READING_FILE;

		const Config* config = dynamic_cast<const Config*>(opt->getUserData());
		if(!config)
			return ReadResult::ERROR_IN_READING_FILE;

		RasterImageLayer* rasterimglayer  = new RasterImageLayer();
		rasterimglayer->read(*config);

		return rasterimglayer;
	}
};

REGISTER_OSGPLUGIN(ly_img_raster, RasterImageLayerFactory)