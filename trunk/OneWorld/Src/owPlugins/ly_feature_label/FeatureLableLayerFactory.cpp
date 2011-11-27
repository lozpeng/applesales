#include <osgDB/ReaderWriter>
#include <osgDB/FileNameUtils>
#include <osgDB/Options>
#include <osgDB/Registry>
#include <owPlugins/ly_feature_label/FeatureLableLayer.h>

using namespace owPlugins;

class FeatureLabelLayerFactory : public osgDB::ReaderWriter
{
public:
	FeatureLabelLayerFactory(){}

	virtual const char* className()
	{
		return "FeatureLabelLayerFactory";
	}

	virtual bool acceptsExtension(const std::string& extension) const
	{
		return osgDB::equalCaseInsensitive( extension, "ly_feature_label" );
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

		FeatureLabelLayer* gmflyr  = new FeatureLabelLayer();
		gmflyr->read(*config);

		return gmflyr;
	}
};

REGISTER_OSGPLUGIN(ly_feature_label, FeatureLabelLayerFactory)