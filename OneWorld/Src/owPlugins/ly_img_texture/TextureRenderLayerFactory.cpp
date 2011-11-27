#include <osgDB/ReaderWriter>
#include <osgDB/FileNameUtils>
#include <osgDB/Options>
#include <osgDB/Registry>
#include <owPlugins/ly_img_texture/TextureRenderLayer.h>

using namespace owPlugins;

class TextureRenderLayerFactory : public osgDB::ReaderWriter
{
public:
	TextureRenderLayerFactory(){}

	virtual const char* className()
	{
		return "TextureRenderLayerFactory";
	}

	virtual bool acceptsExtension(const std::string& extension) const
	{
		return osgDB::equalCaseInsensitive( extension, "ly_img_texture" );
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

		TextureRenderLayer* texturerenderlayer  = new TextureRenderLayer();
		texturerenderlayer->read(*config);

		return texturerenderlayer;
	}
};

REGISTER_OSGPLUGIN(ly_img_texture, TextureRenderLayerFactory)