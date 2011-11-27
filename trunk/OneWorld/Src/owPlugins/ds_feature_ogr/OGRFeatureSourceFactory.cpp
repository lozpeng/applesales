#include <osgDB/ReaderWriter>
#include <osgDB/FileNameUtils>
#include <osgDB/Options>
#include <osgDB/Registry>
#include <owPlugins/ds_feature_ogr/OGRFeatureSource.h>

using namespace owPlugins;

class OGRFeatureSourceFactory : public osgDB::ReaderWriter
{
public:
	OGRFeatureSourceFactory(){}

	virtual const char* className()
	{
		return "OGRFeatureSourceFactory";
	}

	virtual bool acceptsExtension(const std::string& extension) const
	{
		return osgDB::equalCaseInsensitive( extension, "ds_feature_ogr" );
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

		OGRFeatureSource* ogrsource = new OGRFeatureSource();
		ogrsource->read(*config);

		return ogrsource;
	}
};

REGISTER_OSGPLUGIN(ds_feature_ogr, OGRFeatureSourceFactory)