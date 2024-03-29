#include <owScene/property.h>

#include <sstream>
#include <algorithm>

using namespace owScene;

static std::string
normalize( std::string input )
{
	std::string output = input;
	std::replace( output.begin(), output.end(), '-', '_' );
	return output;
}

Property
Property::invalid()
{
	return Property();
}

Property::Property()
{
	valid = false;
}

Property::Property( const std::string& _name, const std::string& _value )
{
	name = normalize( _name );
	value = _value;
	valid = true;
}

Property::Property( const std::string& _name, int _value )
{
	name = normalize( _name );
	std::stringstream ss;
	ss << _value;
	value = ss.str();
	valid = true;
}

Property::Property( const std::string& _name, float _value )
{
	name = normalize( _name );
	std::stringstream ss;
	ss << _value;
	value = ss.str();
	valid = true;
}

Property::Property( const std::string& _name, double _value )
{
	name = normalize( _name );
	std::stringstream ss;
	ss << _value;
	value = ss.str();
	valid = true;
}

Property::Property( const std::string& _name, bool _value )
{
	name = normalize( _name );
	value = _value? "true" : "false";
	valid = true;
}

Property::Property( const std::string& _name, const osg::Vec2f& _v )
{
	name = normalize( _name );
	std::stringstream ss;
	ss << _v[0] << " " << _v[1];
	value = ss.str();
	valid = true;
}

Property::Property( const std::string& _name, const osg::Vec3f& _v )
{
	name = normalize( _name );
	std::stringstream ss;
	ss << _v[0] << " " << _v[1] << " " << _v[2];
	value = ss.str();
	valid = true;
}

Property::Property( const std::string& _name, const osg::Vec4f& _v )
{
	name = normalize( _name );
	std::stringstream ss;
	ss << _v[0] << " " << _v[1] << " " << _v[2] << " " << _v[3];
	value = ss.str();
	valid = true;
}

Property::Property( const std::string& _name, const osg::Matrix& _v )
{
	name = normalize( _name );
	std::stringstream ss;
	const osg::Matrix::value_type* p = _v.ptr();
	for( int i=0; i<15; i++ ) ss << *p++ << " ";
	ss << *p;
	value = ss.str();
	valid = true;
}

Property::Property( const std::string& _name, osg::Referenced* _rv )
{
	name = normalize( _name );
	ref_value = _rv;
	valid = true;
}

bool
Property::isValid() const
{
	return valid;
}

const std::string& 
Property::getName() const
{
	return name;
}

const std::string& 
Property::getValue() const
{
	return value;
}

osg::Referenced*
Property::getRefValue()
{
	return ref_value.get();
}

int 
Property::getIntValue( int def ) const
{
	return value.length() > 0? ::atoi( value.c_str() ) : def;
}

float 
Property::getFloatValue( float def ) const
{
	return value.length() > 0? (float)::atof( value.c_str() ) : def;
}

double 
Property::getDoubleValue( double def ) const
{
	return value.length() > 0? ::atof( value.c_str() ) : def;
}

bool 
Property::getBoolValue( bool def ) const
{
	std::string temp = value;
	std::transform( temp.begin(), temp.end(), temp.begin(), tolower );
	return temp == "true" || temp == "yes" || temp == "on" ? true : false;
}

osg::Vec2f
Property::getVec2Value() const
{
	osg::Vec2 v;
	std::stringstream ss( value );
	ss >> v[0] >> v[1];
	return v;
}

osg::Vec3
Property::getVec3Value() const
{
	osg::Vec3 v;
	std::stringstream ss( value );
	ss >> v[0] >> v[1] >> v[2];
	return v;
}

osg::Vec4
Property::getVec4Value() const
{
	osg::Vec4 v;
	std::stringstream ss( value );
	ss >> v[0] >> v[1] >> v[2] >> v[3];
	return v;
}

osg::Matrix
Property::getMatrixValue() const
{
	osg::Matrix m;
	std::stringstream ss( value );
	osg::Matrix::value_type* p = m.ptr();
	for( int i=0; i<16; i++ ) ss >> *p++;
	return m;
}


const char* 
Property::asString() const
{
	return value.c_str();
}

double
Property::asDouble() const
{
	return getDoubleValue( 0.0 );
}

int 
Property::asInt() const
{
	return getIntValue( 0 );
}

bool 
Property::asBool() const
{
	return getBoolValue( false );
}

/**************************************************************************/

bool
Properties::exists( const std::string& key ) const
{
	std::string nkey = normalize( key );
	for( Properties::const_iterator i = begin(); i != end(); i++ )
	{
		if ( i->getName() == nkey )
		{
			return true;
		}
	}
	return false;
}

int 
Properties::getIntValue( const std::string& key, int def ) const
{
	std::string nkey = normalize( key );
	for( Properties::const_iterator i = begin(); i != end(); i++ )
	{
		if ( i->getName() == nkey )
		{
			return i->getIntValue( def );
		}
	}
	return def;
}

float 
Properties::getFloatValue( const std::string& key, float def ) const
{
	std::string nkey = normalize( key );
	for( Properties::const_iterator i = begin(); i != end(); i++ )
	{
		if ( i->getName() == nkey )
		{
			return i->getFloatValue( def );
		}
	}
	return def;
}

double 
Properties::getDoubleValue( const std::string& key, double def ) const
{
	std::string nkey = normalize( key );
	for( Properties::const_iterator i = begin(); i != end(); i++ )
	{
		if ( i->getName() == nkey )
		{
			return i->getDoubleValue( def );
		}
	}
	return def;
}

bool 
Properties::getBoolValue( const std::string& key, bool def ) const
{
	std::string nkey = normalize( key );
	for( Properties::const_iterator i = begin(); i != end(); i++ )
	{
		if ( i->getName() == nkey )
		{
			return i->getBoolValue( def );
		}
	}
	return def;
}

osg::Vec2 
Properties::getVec2Value( const std::string& key ) const
{
	std::string nkey = normalize( key );
	for( Properties::const_iterator i = begin(); i != end(); i++ )
	{
		if ( i->getName() == nkey )
		{
			return i->getVec2Value();
		}
	}
	return osg::Vec2(0,0);
}

osg::Vec3 
Properties::getVec3Value( const std::string& key ) const
{
	std::string nkey = normalize( key );
	for( Properties::const_iterator i = begin(); i != end(); i++ )
	{
		if ( i->getName() == nkey )
		{
			return i->getVec3Value();
		}
	}
	return osg::Vec3(0,0,0);
}

osg::Vec4 
Properties::getVec4Value( const std::string& key ) const
{
	std::string nkey = normalize( key );
	for( Properties::const_iterator i = begin(); i != end(); i++ )
	{
		if ( i->getName() == nkey )
		{
			return i->getVec4Value();
		}
	}
	return osg::Vec4(0,0,0,1);
}

std::string 
Properties::getValue( const std::string& key, std::string def ) const
{
	std::string nkey = normalize( key );
	for( Properties::const_iterator i = begin(); i != end(); i++ )
	{
		if ( i->getName() == nkey )
		{
			return i->getValue();
		}
	}
	return def;
}

osg::Referenced*
Properties::getRefValue( const std::string& key )
{
	std::string nkey = normalize( key );
	for( Properties::iterator i = begin(); i != end(); i++ )
	{
		if ( i->getName() == nkey )
		{
			return i->getRefValue();
		}
	}
	return NULL;
}


void
Properties::remove( const std::string& key )
{
	std::string nkey = normalize( key );
	for( Properties::iterator i = begin(); i != end(); i++ )
	{
		if ( i->getName() == nkey )
		{
			erase( i );
			return;
		}
	}
}

void
Properties::set( const Property& prop )
{
	remove( prop.getName() );
	push_back( prop );
}

Property
Properties::get( const std::string& key ) const
{
	std::string nkey = normalize( key );
	for( Properties::const_iterator i = begin(); i != end(); i++ )
	{
		if ( i->getName() == nkey )
		{
			return *i;
		}
	}
	return Property::invalid();
}
