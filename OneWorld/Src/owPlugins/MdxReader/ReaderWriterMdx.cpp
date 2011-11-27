#include <owScene/Terrain.h>
#include <owScene/ModelLayer.h>
#include <owUtil/XmlUtils.h>
#include <owUtil/HTTPClient.h>
#include <owScene/ModelObject.h>

#include <osgDB/ReaderWriter>
#include <osgDB/FileNameUtils>
#include <osgDB/Registry>

//using namespace gsPlugins;

class ReaderWriterMdx : public osgDB::ReaderWriter
{
public:
	ReaderWriterMdx() {}

	virtual const char* className()
	{
		return "Mdx ReaderWriter";
	}

	virtual bool acceptsExtension(const std::string& extension) const
	{
		return osgDB::equalCaseInsensitive( extension, "mdx" );
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
		if ( docConf.hasChild( "mdx" ) )
			conf = docConf.child( "mdx" );

		//
		SpatialReference* srs = (SpatialReference*)options->getUserData();
		osg::ref_ptr<osg::Group> _group = new osg::Group;
		std::string path = conf.value("path");
		Config models = conf.child("models");
		ConfigSet modelset = models.children("model");

		for(ConfigSet::iterator i=modelset.begin(); i!=modelset.end(); i++)
		{
			Config modelconf = *i;

			osg::ref_ptr<owScene::ModelObject> mo = new owScene::ModelObject;
			mo->SetPath(path);
			mo->SetSrs(srs);
			mo->read(modelconf);

			_group->addChild(mo.get());
		}
		return _group.get();
	}
};

REGISTER_OSGPLUGIN(mdx, ReaderWriterMdx)
