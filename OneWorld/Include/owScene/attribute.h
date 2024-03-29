/**
* osgGIS - GIS Library for OpenSceneGraph
* Copyright 2007 Glenn Waldron and Pelican Ventures, Inc.
* http://osggis.org
*
* osgGIS is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#ifndef _OWSCENE_ATTRIBUTE_H_
#define _OWSCENE_ATTRIBUTE_H_ 1

#include <owScene/Export.h>
#include <owScene/property.h>

#include <string>
#include <map>
#include <list>

namespace owScene
{
	/**
	* A single name/value pair, representing a GIS feature attribute record.
	*/
	class OWSCENE_EXPORT Attribute
	{
	public:
		enum Type {
			TYPE_UNSPECIFIED,
			TYPE_STRING,
			TYPE_INT,
			TYPE_DOUBLE,
			TYPE_BOOL
		};

	public:
		Attribute();

		Attribute( const std::string& key, const std::string& value );

		Attribute( const std::string& key, const char* value );

		Attribute( const std::string& key, int value );

		Attribute( const std::string& key, double value );

		Attribute( const std::string& key, bool value );

		bool isValid() const;

		const Type& getType() const;

		const char* getKey();

		const char* asString();

		int asInt();

		double asDouble();

		bool asBool();

	public:
		static Attribute invalid();

	public:
		virtual ~Attribute();

	private:
		bool        valid;
		std::string key;
		Type        type;
		std::string string_value;
		int         int_value;
		double      double_value;
	};

	typedef std::map<std::string,Attribute> AttributeTable;

	typedef std::list<Attribute> AttributeList;


	class OWSCENE_EXPORT AttributeSchema
	{
	public:
		AttributeSchema() { }

		AttributeSchema( const std::string& attr_name, const Attribute::Type& type );

		AttributeSchema( const std::string& attr_name, const Attribute::Type& type, const Properties& props );

		const std::string& getName() const;

		const Attribute::Type& getType() const;

		const Properties& getProperties() const;

	private:
		std::string     name;
		Attribute::Type type;
		Properties      props;
	};

	typedef std::map<std::string,AttributeSchema> AttributeSchemaTable;

	typedef std::list<AttributeSchema> AttributeSchemaList;
}

#endif // _OWSCENE_ATTRIBUTE_H_