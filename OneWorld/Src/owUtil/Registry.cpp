#include <owUtil/Registry.h>
#include <osgDB/Registry>

using namespace owUtil;

// from MimeTypes.cpp
extern const char* builtinMimeTypeExtMappings[];

Registry& Registry::instance()
{
	static Registry s_registry;
	return s_registry;
}

Registry::Registry()
{
	// add built-in mime-type extension mappings
	for( int i=0; ; i+=2 )
	{
		std::string mimeType = builtinMimeTypeExtMappings[i];
		if ( mimeType.length() == 0 )
			break;
		addMimeTypeExtensionMapping( mimeType, builtinMimeTypeExtMappings[i+1] );
	}
}

Registry::~Registry()
{
	;
}


void Registry::addMimeTypeExtensionMapping(const std::string fromMimeType, const std::string toExt)
{
	_mimeTypeExtMap[fromMimeType] = toExt;
}

osgDB::ReaderWriter* 
Registry::getReaderWriterForMimeType(const std::string& mimeType)
{
	MimeTypeExtensionMap::const_iterator i = _mimeTypeExtMap.find( mimeType );
	return i != _mimeTypeExtMap.end()?
		osgDB::Registry::instance()->getReaderWriterForExtension( i->second ) :
	NULL;
}
