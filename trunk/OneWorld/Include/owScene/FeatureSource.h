#ifndef OWSCENE_FEATURESOURCE_H_
#define OWSCENE_FEATURESOURCE_H_

#include <owScene/export.h>
#include <owScene/Feature.h>
#include <owScene/FeatureCursor.h>
#include <owUtil/DataSource.h>
#include <owUtil/SpatialProperty.h>
#include <owUtil/config.h>

using namespace owUtil;

namespace owScene
{
	/** 矢量数据源基类*/
	class OWSCENE_EXPORT FeatureSource : public DataSource
	{
	public:
		FeatureSource(){}

	public:

		/** 返回所有记录*/
		virtual FeatureCursor* createFeatureCursor() = 0;

		/** 通过表达式获得记录*/
		virtual FeatureCursor* createFeatureCursor(const std::string& exp) = 0;

		/** 通过范围和投影获得记录*/
		virtual FeatureCursor* createFeatureCursor(const SpatialProperty& sp) = 0;

		/** 通过索引获得记录*/
		virtual Feature* createFeature(FeatureOID id) = 0;

		/** 获得矢量记录数目*/
		virtual unsigned int getFeaturesCount() const= 0;

		/** 获得表头*/
		virtual const AttributeSchemaList& getAttributeSchemaList() const= 0;

	protected:

		virtual ~FeatureSource(){}

	};
}

#endif //OWSCENE_FEATURESOURCE_H_