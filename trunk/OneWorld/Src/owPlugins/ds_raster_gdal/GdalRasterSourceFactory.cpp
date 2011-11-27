#include <osgDB/ReaderWriter>
#include <osgDB/FileNameUtils>
#include <osgDB/Options>
#include <osgDB/Registry>
#include <owPlugins/ds_raster_gdal/GdalRasterSource.h>

using namespace owPlugins;

class GdalRasterSourceFactory : public osgDB::ReaderWriter
{
public:
	GdalRasterSourceFactory(){}

	virtual const char* className()
	{
		return "GdalRasterSourceFactory";
	}

	virtual bool acceptsExtension(const std::string& extension) const
	{
		return osgDB::equalCaseInsensitive( extension, "ds_raster_gdal" );
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

		GdalRasterSource* gdalsource = new GdalRasterSource();
		gdalsource->read(*config);

		return gdalsource;
	}
};

REGISTER_OSGPLUGIN(ds_raster_gdal, GdalRasterSourceFactory)