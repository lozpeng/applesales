#include <osgDB/ReaderWriter>
#include <osgDB/FileNameUtils>
#include <osgDB/Options>
#include <osgDB/Registry>
#include <owPlugins/ly_feature_overlay/FeatureOverlayLayer.h>

using namespace owPlugins;

class FeatureOverlayLayerFactory : public osgDB::ReaderWriter
{
public:
	FeatureOverlayLayerFactory(){}

	virtual const char* className()
	{
		return "FeatureOverlayLayerFactory";
	}

	virtual bool acceptsExtension(const std::string& extension) const
	{
		return osgDB::equalCaseInsensitive( extension, "ly_img_feature_overlay" );
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

		FeatureOverlayLayer* overlayLayer  = new FeatureOverlayLayer();
		overlayLayer->read(*config);

		return overlayLayer;
	}
};

REGISTER_OSGPLUGIN(ly_img_feature_overlay, FeatureOverlayLayerFactory)