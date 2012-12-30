#ifndef _owUtil_CONFIG_H_
#define _owUtil_CONFIG_H_

#include <owUtil/export.h>
#include <osg/Referenced>
#include <osg/ref_ptr>

#include <map>
#include <list>
#include <string>
#include <owUtil/StringUtils.h>

namespace owUtil
{

	typedef std::list<class Config> ConfigSet;

	/** 属性集合*/
	struct Properties : public std::map<std::string,std::string> 
	{
		std::string get( const std::string& key ) const 
		{
			std::map<std::string,std::string>::const_iterator i = find(key);
			return i != end()? i->second : std::string();
		}
	};

    /**
     * A template for defining "optional" class members. An optional member has a default value
     * and a flag indicating whether the member is "set".
     * This is used extensively in osgEarth's ConfigOptions subsystem.
     */
    template<typename T> struct optional {
        optional() : _set(false), _value(T()), _defaultValue(T()) { }
        optional(T defaultValue) : _set(false), _value(defaultValue), _defaultValue(defaultValue) { }
        optional(T defaultValue, T value) : _set(true), _value(value), _defaultValue(defaultValue) { }
        optional(const optional<T>& rhs) { (*this)=rhs; }
        virtual ~optional() { }
        optional<T>& operator =(const optional<T>& rhs) { _set=rhs._set; _value=rhs._value; _defaultValue=rhs._defaultValue; return *this; }
        const T& operator =(const T& value) { _set=true; _value=value; return _value; }
        bool operator ==(const optional<T>& rhs) const { return _set && rhs._set && _value==rhs._value; }
        bool operator !=(const optional<T>& rhs) const { return !( (*this)==rhs); }
        bool operator ==(const T& value) const { return _value==value; }
        bool operator !=(const T& value) const { return _value!=value; }
        bool isSetTo(const T& value) const { return _set && _value==value; } // differs from == in that the value must be explicity set
        bool isSet() const { return _set; }
        void unset() { _set = false; _value=_defaultValue; }

        //T& get() { return _value; }
        const T& get() const { return _value; }
        const T& value() const { return _value; }
        const T& defaultValue() const { return _defaultValue; }

        // gets a mutable reference, automatically setting
        T& mutable_value() { _set = true; return _value; }

        void init(T defValue) { _value=defValue; _defaultValue=defValue; unset(); }

        operator const T*() const { return &_value; }

        T* operator ->() { _set=true; return &_value; }
        const T* operator ->() const { return &_value; }

    private:
        bool _set;
        T _value;
        T _defaultValue;
        typedef T* optional::*unspecified_bool_type;

    public:
        operator unspecified_bool_type() const { return 0; }
    };

	/** 定义一个结构体用于存储数据，包括key值、属性和孩子节点*/
	class OWUTIL_EXPORT Config : public osg::Referenced
	{
	public:
		Config() { }
		Config( const std::string& key ) : _key(key) { }
		Config( const std::string& key, const std::string& value ) : _key( key ), _defaultValue( value ) { }

		Config( const Config& rhs ) : _key(rhs._key), _defaultValue(rhs._defaultValue), _attrs(rhs._attrs), _children(rhs._children) { }

		virtual ~Config(){ _children.clear(); }

	public:

		bool empty() const { return _key.empty() && _attrs.empty() && _children.empty(); }

		std::string& key();
		const std::string& key() const;

		bool hasValue( const std::string& key ) const {
			return !value(key).empty();
		}

		const std::string& value() const { return _defaultValue; }
		std::string& value() { return _defaultValue; }

		Properties& attrs() { return _attrs; }
		const Properties& attrs() const { return _attrs; }

		std::string attr( const std::string& name ) const;
		std::string& attr( const std::string& name ) { return _attrs[name]; }

		void removeAttr(const std::string& name) { _attrs.erase(name); }

		const Config& child( const std::string& key ) const;

		ConfigSet& children() { return _children; }
		const ConfigSet& children() const { return _children; }
		ConfigSet children( const std::string& key );
		const ConfigSet children( const std::string& key ) const;

		bool hasChild( const std::string& key ) const;
		void removeChild( const std::string& key );
		void addChild(Config* child);

		void clear();

		void merge( const Config& rhs );

		const std::string value( const std::string& key ) const {
			std::string r = trim(child(key).value());
			if ( r.empty() )
				r = attr(key);
			return r;
		}

		void remove( const std::string& key ) {
			_attrs.erase(key);            
			for(ConfigSet::iterator i = _children.begin(); i != _children.end(); ) {
				if ( i->key() == key )
					i = _children.erase( i );
				else
					++i;
			}
		}

		bool boolValue( bool fallback ) const {
			return as<bool>( _defaultValue, fallback );
		}
		// populates a primitive value.
		template<typename T>
		T value( const std::string& key, T fallback ) const {
			std::string r = attr(key);
			if ( r.empty() && hasChild( key ) )
				r = child(key).value();
			return owUtil::as<T>( r, fallback );
		}

		void addChild( const std::string& key, const std::string& value ) {
			add( key, value );
		}

		void add( const std::string& key, const std::string& value ) {
			_children.push_back( Config( key, value ) );
		}

		void addChild( const Config& conf ) {
			add( conf );
		}

		void add( const Config& conf ) {
			_children.push_back( conf );
		}

		void add( const std::string& key, const Config& conf ) {
			Config temp = conf;
			temp.key() = key;
			add( temp );
		}

		void add( const ConfigSet& set ) {
			for( ConfigSet::const_iterator i = set.begin(); i != set.end(); i++ )
				_children.push_back( *i );
		}

		// populates the output value iff the Config exists.
		template<typename T>
		bool getIfSet( const std::string& key, optional<T>& output ) const {
			std::string r = attr(key);
			if ( r.empty() && hasChild(key) )
				r = child(key).value();
			if ( !r.empty() ) {
				output = as<T>( r, output.defaultValue() );
				return true;
			} 
			else
				return false;
		}

		// for Configurable's
		template<typename T>
		bool getObjIfSet( const std::string& key, optional<T>& output ) const {
			if ( hasChild( key ) ) {
				output = T( child(key) );
				return true;
			}
			else
				return false;
		}

		// populates a Referenced that takes a Config in the constructor.
		template<typename T>
		bool getObjIfSet( const std::string& key, osg::ref_ptr<T>& output ) const {
			if ( hasChild( key ) ) {
				output = new T( child(key) );
				return true;
			}
			else
				return false;
		}

		template<typename X, typename Y>
		bool getIfSet( const std::string& key, const std::string& val, optional<X>& target, const Y& targetValue ) const {
			if ( hasValue( key ) && value( key ) == val ) {
				target = targetValue;
				return true;
			}
			else 
				return false;
		}


		template<typename T>
		void updateIfSet( const std::string& key, const optional<T>& opt ) {
			if ( opt.isSet() ) {
				remove(key);
				add( key, owUtil::toString<T>( opt.value() ) );
			}
		}

		template<typename T>
		void updateObjIfSet( const std::string& key, const osg::ref_ptr<T>& opt ) {
			if ( opt.valid() ) {
				remove(key);
				Config conf = opt->getConfig();
				conf.key() = key;
				add( conf );
			}
		}

		template<typename T>
		void updateObjIfSet( const std::string& key, const optional<T>& obj ) {
			if ( obj.isSet() ) {
				remove(key);
				Config conf = obj->getConfig();
				conf.key() = key;
				add( conf );
			}
		}

		template<typename X, typename Y>
		void updateIfSet( const std::string& key, const std::string& val, const optional<X>& target, const Y& targetValue ) {
			if ( target.isSetTo( targetValue ) ) {
				remove(key);
				add( key, val );
			}
		}


		bool loadXML( std::istream& in );

        std::string toString( int indent =0 ) const;

	protected:
		std::string _key;
		std::string _defaultValue;
		Properties  _attrs;
		ConfigSet   _children;
	};

    /**
     * Base class for all serializable options classes.
     */
    class ConfigOptions // header-only (no export required)
    {
    public:
        ConfigOptions( const Config& conf =Config() )
            : _conf( conf ) { }
        ConfigOptions( const ConfigOptions& rhs )
            : _conf( rhs.getConfig() ) { }

        ConfigOptions& operator = ( const ConfigOptions& rhs ) {
            if ( this != &rhs ) {
                _conf = rhs.getConfig();
                mergeConfig( _conf );
            }
            return *this;
        }

        void merge( const ConfigOptions& rhs ) {
            _conf.merge( rhs._conf );
            mergeConfig( rhs.getConfig() );
        }

        virtual Config getConfig() const { return _conf; }

    protected:
        virtual void mergeConfig( const Config& conf ) { }

        Config _conf;
    };
}

#endif //_owUtil_CONFIG_H_