#include <osgDB/ReaderWriter>
#include <osgDB/FileNameUtils>
#include <osgDB/Options>
#include <osgDB/Registry>
#include <owPlugins/ly_feature_geometry/FeatureGeometryLayer.h>

using namespace owPlugins;

class FeatureGeometryLayerFactory : public osgDB::ReaderWriter
{
public:
	FeatureGeometryLayerFactory(){}

	virtual const char* className()
	{
		return "FeatureGeometryLayerFactory";
	}

	virtual bool acceptsExtension(const std::string& extension) const
	{
		return osgDB::equalCaseInsensitive( extension, "ly_feature_geometry" );
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

		FeatureGeometryLayer* gmflyr  = new FeatureGeometryLayer();
		gmflyr->read(*config);

		return gmflyr;
	}
};

REGISTER_OSGPLUGIN(ly_feature_geometry, FeatureGeometryLayerFactory)