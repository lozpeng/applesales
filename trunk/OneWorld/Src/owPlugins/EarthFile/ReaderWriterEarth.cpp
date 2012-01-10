#include <owScene/Terrain.h>
#include <owUtil/XmlUtils.h>
#include <owUtil/HTTPClient.h>
#include <owPlugins/EarthFile/MapSerialize.h>

#include <osgDB/ReaderWriter>
#include <osgDB/FileNameUtils>
#include <osgDB/Registry>

using namespace owPlugins;

class ReaderWriterEarth : public osgDB::ReaderWriter
{
public:
	ReaderWriterEarth() {}

	virtual const char* className()
	{
		return "OSG Earth ReaderWriter";
	}

	virtual bool acceptsExtension(const std::string& extension) const
	{
		return osgDB::equalCaseInsensitive( extension, "earth" );
	}

	virtual ReadResult readObject(const std::string& file_name, const Options* options) const
	{
		return readNode( file_name, options );
	}

	virtual WriteResult writeNode(const osg::Node& node, const std::string& fileName, const Options* options ) const
	{
		if ( !acceptsExtension( osgDB::getFileExtension(fileName) ) )
			return WriteResult::FILE_NOT_HANDLED;

		std::ofstream out( fileName.c_str());
		if ( out.is_open() )
			return writeNode( node, out, options );

		return WriteResult::ERROR_IN_WRITING_FILE;            
	}

	virtual WriteResult writeNode(const osg::Node& node, std::ostream& out, const Options* options ) const
	{
		return WriteResult::FILE_SAVED;
	}

	virtual ReadResult readNode(const std::string& fileName, const Options* options) const
	{
		std::string ext = osgDB::getFileExtension( fileName );
		if ( !acceptsExtension( ext ) )
			return ReadResult::FILE_NOT_HANDLED;

		{
			std::string buf;
			if ( HTTPClient::readString( fileName, buf ) != HTTPClient::RESULT_OK )
				return ReadResult::ERROR_IN_READING_FILE;

			osg::ref_ptr<Options> myOptions = options ? static_cast<Options*>(options->clone(osg::CopyOp::DEEP_COPY_ALL)) : new Options();
			myOptions->setPluginData( "__ReaderWriterOsgEarth::ref_uri", (void*)&fileName );

			std::stringstream in( buf );
			return readNode( in, myOptions.get() );
		}
	}

	virtual ReadResult readNode(std::istream& in, const Options* options ) const
	{
		osg::ref_ptr<XmlDocument> doc = XmlDocument::load( in );
		if ( !doc.valid() )
			return ReadResult::ERROR_IN_READING_FILE;

		Config docConf = doc->getConfig();

		// support both "map" and "earth" tag names at the top level
		Config conf;
		if ( docConf.hasChild( "map" ) )
			conf = docConf.child( "map" );
		else if ( docConf.hasChild( "earth" ) )
			conf = docConf.child( "earth" );

		owScene::Scene* e =0L;
		MapSerialize serialize;

		if ( !conf.empty() )
		{
			e = serialize.deserialize(conf, "");
		}

		return ReadResult(e);
	}
};

REGISTER_OSGPLUGIN(earth, ReaderWriterEarth)
