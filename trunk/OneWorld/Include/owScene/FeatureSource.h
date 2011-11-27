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
	/** ʸ������Դ����*/
	class OWSCENE_EXPORT FeatureSource : public DataSource
	{
	public:
		FeatureSource(){}

	public:

		/** �������м�¼*/
		virtual FeatureCursor* createFeatureCursor() = 0;

		/** ͨ�����ʽ��ü�¼*/
		virtual FeatureCursor* createFeatureCursor(const std::string& exp) = 0;

		/** ͨ����Χ��ͶӰ��ü�¼*/
		virtual FeatureCursor* createFeatureCursor(const SpatialProperty& sp) = 0;

		/** ͨ��������ü�¼*/
		virtual Feature* createFeature(FeatureOID id) = 0;

		/** ���ʸ����¼��Ŀ*/
		virtual unsigned int getFeaturesCount() const= 0;

		/** ��ñ�ͷ*/
		virtual const AttributeSchemaList& getAttributeSchemaList() const= 0;

	protected:

		virtual ~FeatureSource(){}

	};
}

#endif //OWSCENE_FEATURESOURCE_H_