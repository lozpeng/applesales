#ifndef _OWSCENE_PROPERTY_H_
#define _OWSCENE_PROPERTY_H_ 1

#include <owScene/Export.h>

#include <osg/Vec2>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Matrix>
#include <vector>

namespace owScene
{
	class OWSCENE_EXPORT Property
	{
	public:
		Property();
		Property( const std::string& name, const std::string& value );
		Property( const std::string& name, int value );
		Property( const std::string& name, float value );
		Property( const std::string& name, double value );
		Property( const std::string& name, bool value );
		Property( const std::string& name, const osg::Vec2f& value );
		Property( const std::string& name, const osg::Vec3f& value );
		Property( const std::string& name, const osg::Vec4f& value );
		Property( const std::string& name, const osg::Matrix& value );
		Property( const std::string& name, osg::Referenced* value );

		const std::string& getName() const;
		const std::string& getValue() const;
		int getIntValue( int def ) const;
		float getFloatValue( float def ) const;
		double getDoubleValue( double def ) const;
		bool getBoolValue( bool def ) const;
		osg::Vec2 getVec2Value() const;
		osg::Vec3 getVec3Value() const;
		osg::Vec4 getVec4Value() const;
		osg::Matrix getMatrixValue() const;
		osg::Referenced* getRefValue();
		bool isValid() const;

		const char* asString() const;
		double asDouble() const;
		int asInt() const;
		bool asBool() const;

		Property static invalid();

	private:
		std::string name;
		std::string value;
		osg::ref_ptr<osg::Referenced> ref_value;
		bool valid;
	};

	class OWSCENE_EXPORT Properties : public std::vector<Property>
	{
	public:
		bool exists( const std::string& name ) const;
		int getIntValue( const std::string& name, int def ) const;
		float getFloatValue( const std::string& name, float def ) const;
		double getDoubleValue( const std::string& name, double def ) const;
		bool getBoolValue( const std::string& name, bool def ) const;
		osg::Vec2 getVec2Value( const std::string& name ) const;
		osg::Vec3 getVec3Value( const std::string& name ) const;
		osg::Vec4 getVec4Value( const std::string& name ) const;
		std::string getValue( const std::string& name, std::string def ) const;
		osg::Referenced* getRefValue( const std::string& name );
		void remove( const std::string& key );
		Property get( const std::string& name ) const;
		void set( const Property& p );
	};

	class /*interface*/ OWSCENE_EXPORT IObjectWithProperties
	{
	public:
		virtual void setProperty( const Property& prop ) =0;        
		virtual Properties getProperties() const =0;
	};
}

#endif //_OWSCENE_PROPERTY_H_