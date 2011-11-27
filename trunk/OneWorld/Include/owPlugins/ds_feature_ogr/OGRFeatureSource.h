#ifndef OWPLUGIN_OGRFEATURESOURCE_H_
#define OWPLUGIN_OGRFEATURESOURCE_H_

#include <owScene/FeatureSource.h>
#include <owUtil/Log.h>

using namespace owScene;
class OGRDataSource;
class OGRLayer;

namespace owPlugins
{
	class OGRFeatureSource : public FeatureSource
	{
	public:
		OGRFeatureSource();
		~OGRFeatureSource();

		META_Object(owPlugins,OGRFeatureSource);

	public:

		virtual bool Connect(owUtil::ProgressBase* p=NULL);
		virtual bool disConnect(owUtil::ProgressBase* p=NULL);

		virtual void read(const Config& config);
		virtual void write(Config& config) const;

	public:

		/** 返回所有记录*/
		virtual FeatureCursor* createFeatureCursor();

		/** 通过表达式获得记录*/
		virtual FeatureCursor* createFeatureCursor(const std::string& exp);

		/** 通过范围和投影获得记录*/
		virtual FeatureCursor* createFeatureCursor(const SpatialProperty& sp);

		/** 通过索引获得记录*/
		virtual Feature* createFeature(FeatureOID id);

		/** 获得矢量记录数目*/
		virtual unsigned int getFeaturesCount() const;

		/** 获得表头*/
		virtual const AttributeSchemaList& getAttributeSchemaList() const;

		void test();

	protected:

		OGRFeatureSource(const OGRFeatureSource& source,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY)
		{
			LOG_WARNING("OGRFeatureSource copy construct not support!");
		}

		/**生成表头*/
		void genAttributeSchemaList();

	private:

		//
		AttributeSchemaList _attrbuteschemalist;

		//
		std::string _url;
		std::string _ext;

		//
		OGRDataSource* _poDS;
		OGRLayer* _poLayer;
	};
}

#endif //OWPLUGIN_OGRFEATURESOURCE_H_