#include <owUtil/config.h>
#include <owUtil/XmlUtils.h>
#include <sstream>


using namespace owUtil;


Config& emptyConfig()
{
	static Config _emptyConfig;
	return _emptyConfig;
}

bool
Config::loadXML( std::istream& in )
{
	osg::ref_ptr<XmlDocument> xml = XmlDocument::load( in );
	if ( xml.valid() )
		*this = xml->getConfig();
	return xml.valid();
}

void Config::clear()
{
	_attrs.clear();
	_key="";
	_children.clear();
}

std::string Config::attr( const std::string& name ) const {
	Properties::const_iterator i = _attrs.find(name);
	return i != _attrs.end()? i->second : "";
}

const ConfigSet Config::children( const std::string& key ) const {
	ConfigSet r;
	for(ConfigSet::const_iterator i = _children.begin(); i != _children.end(); i++ ) {
		if ( (i)->key() == key )
			r.push_back( *i );
	}
	return r;
}

ConfigSet Config::children( const std::string& key )
{
	ConfigSet r;
	for(ConfigSet::const_iterator i = _children.begin(); i != _children.end(); i++ ) {
		if ( (i)->key() == key )
			r.push_back( *i );
	}
	return r;
}


std::string
Config::toString( int indent ) const
{
	std::stringstream buf;
	buf << std::fixed;
	for( int i=0; i<indent; i++ ) buf << "  ";
	buf << "{ " << (_key.empty()? "anonymous" : _key) << ": ";
	if ( !_defaultValue.empty() ) buf << _defaultValue;
	if ( !_attrs.empty() ) {
		buf << std::endl;
		for( int i=0; i<indent+1; i++ ) buf << "  ";
		buf << "attrs: [ ";
		for( Properties::const_iterator a = _attrs.begin(); a != _attrs.end(); a++ )
			buf << a->first << "=" << a->second << ", ";
		buf << " ]";
	}
	if ( !_children.empty() ) {
		for( ConfigSet::const_iterator c = _children.begin(); c != _children.end(); c++ )
			buf << std::endl << (*c).toString( indent+1 );
	}

	buf << " }";

	std::string bufStr;
	bufStr = buf.str();
	return bufStr;
}

std::string& Config::key()
{ 
	return _key; 
}

const std::string& Config::key() const 
{ 
	return _key; 
}

bool Config::hasChild( const std::string& key ) const {
	for(ConfigSet::const_iterator i = _children.begin(); i != _children.end(); i++ )
		if ( (i)->key() == key )
			return true;
	return false;
}

void Config::removeChild( const std::string& key ) {        
	for(ConfigSet::iterator i = _children.begin(); i != _children.end(); ) {
		if ( (i)->key() == key )
			i = _children.erase( i );
		else
			++i;
	}
}

void Config::addChild(Config* child)
{
	if(!child)
		return;
	if(child->key().empty())
		return;
	_children.push_back(*child);
}

const Config&
Config::child( const std::string& childName ) const
{
	for( ConfigSet::const_iterator i = _children.begin(); i != _children.end(); i++ ) {
		if ( i->key() == childName )
			return *i;
	}
	return emptyConfig();
}


void
Config::merge( const Config& rhs ) 
{
	for( Properties::const_iterator a = rhs._attrs.begin(); a != rhs._attrs.end(); ++a )
		_attrs[ a->first ] = a->second;

	for( ConfigSet::const_iterator c = rhs._children.begin(); c != rhs._children.end(); ++c )
		addChild( *c );
}

