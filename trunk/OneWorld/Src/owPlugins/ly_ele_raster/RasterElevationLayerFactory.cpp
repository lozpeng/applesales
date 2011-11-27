#include <osgDB/ReaderWriter>
#include <osgDB/FileNameUtils>
#include <osgDB/Options>
#include <osgDB/Registry>
#include <owPlugins/ly_ele_raster/RasterElevationLayer.h>

using namespace owPlugins;

class RasterElevationLayerFactory : public osgDB::ReaderWriter
{
public:
	RasterElevationLayerFactory(){}

	virtual const char* className()
	{
		return "RasterElevationLayerFactory";
	}

	virtual bool acceptsExtension(const std::string& extension) const
	{
		return osgDB::equalCaseInsensitive( extension, "ly_ele_raster" );
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

		RasterElevationLayer* rasterelelayer  = new RasterElevationLayer();
		rasterelelayer->read(*config);

		return rasterelelayer;
	}
};

REGISTER_OSGPLUGIN(ly_ele_raster, RasterElevationLayerFactory)