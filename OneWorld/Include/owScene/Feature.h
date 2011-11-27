#ifndef OWSCENE_FEATRUE_H_
#define OWSCENE_FEATRUE_H_

#include <owScene/Export.h>

#include <owScene/geoshape.h>
#include <owScene/attribute.h>

#include <vector>
#include <list>
#include <osg/Referenced>

using namespace osg;
using namespace owUtil;

namespace owScene
{
	typedef long FeatureOID;

	/** 矢量记录类*/
	class OWSCENE_EXPORT Feature : public osg::Referenced
	{
	public:
		/** 获得矢量记录id号*/
		virtual const FeatureOID& getOID() const =0;

		/** 获取矢量图形*/
		virtual const GeoShapeList& getShapes() const =0;

		/** 获取矢量图形*/
		virtual GeoShapeList& getShapes() =0;

		/** 判断是否有图形数据*/
		virtual bool hasShapeData() const =0;

		/** 获取图像数据类型*/
		virtual GeoShape::ShapeType getShapeType() const =0;

		/** 获得图形数据维数*/
		virtual int getShapeDim() const =0;

		/** 获得属性*/
		virtual Attribute getAttribute( const std::string& key ) const =0;

		/** 获得所有属性*/
		virtual AttributeList getAttributes() const =0;

		/** 用户自定义属性*/
		virtual void setAttribute( const std::string& key, const std::string& value ) =0;

		virtual void setAttribute( const std::string& key, int value ) =0;

		virtual void setAttribute( const std::string& key, double value ) =0;

		virtual void setAttribute( const std::string& key, bool value ) =0;
	};

	/** Feature集合 */
	typedef std::vector< osg::ref_ptr<Feature> > FeatureList;


	/** FeatureID集合 */
	typedef std::vector< FeatureOID > FeatureOIDList;

	/**
	* Common base class for Feature implementations.
	*/
	class OWSCENE_EXPORT FeatureBase : public Feature
	{
	public:

		virtual Attribute getAttribute( const std::string& key ) const;

		virtual AttributeList getAttributes() const;

		virtual void setAttribute( const std::string& key, const std::string& value );

		virtual void setAttribute( const std::string& key, int value );

		virtual void setAttribute( const std::string& key, double value );

		virtual void setAttribute( const std::string& key, bool value );

		virtual bool hasShapeData() const;

		virtual GeoShape::ShapeType getShapeType() const;

		virtual int getShapeDim() const;


	protected:

		const AttributeTable& getUserAttrs() const;

	private:

		AttributeTable  user_attrs;
	};
}

#endif //OWSCENE_FEATRUE_H_