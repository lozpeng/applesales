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

		/** �������м�¼*/
		virtual FeatureCursor* createFeatureCursor();

		/** ͨ�����ʽ��ü�¼*/
		virtual FeatureCursor* createFeatureCursor(const std::string& exp);

		/** ͨ����Χ��ͶӰ��ü�¼*/
		virtual FeatureCursor* createFeatureCursor(const SpatialProperty& sp);

		/** ͨ��������ü�¼*/
		virtual Feature* createFeature(FeatureOID id);

		/** ���ʸ����¼��Ŀ*/
		virtual unsigned int getFeaturesCount() const;

		/** ��ñ�ͷ*/
		virtual const AttributeSchemaList& getAttributeSchemaList() const;

		void test();

	protected:

		OGRFeatureSource(const OGRFeatureSource& source,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY)
		{
			LOG_WARNING("OGRFeatureSource copy construct not support!");
		}

		/**���ɱ�ͷ*/
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