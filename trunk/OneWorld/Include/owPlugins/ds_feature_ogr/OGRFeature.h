#ifndef OWPLUGIN_DATASOURCE_OGRFEATURE
#define OWPLUGIN_DATASOURCE_OGRFEATURE

#include <owScene/Feature.h>

using namespace owScene;

class OGRFeature;
class OGRGeometry;

namespace owPlugins
{
	class OGRGSFeature : public FeatureBase
	{
	public:
		OGRGSFeature(OGRFeature* ogr_feature);
		~OGRGSFeature();

		/** ���ʸ����¼id��*/
		virtual const FeatureOID& getOID() const;

		/** ��ȡʸ��ͼ��*/
		virtual const GeoShapeList& getShapes() const;

		/** ��ȡʸ��ͼ��*/
		virtual GeoShapeList& getShapes();

	protected:

		//
		bool convertFeature();

		bool convertShape(OGRGeometry *poGeometry, GeoShapeList& geoshapes);

		bool convertAttribute();


	private:

		//feature id
		FeatureOID _id;

		//ogr feature
		OGRFeature* _ogr_feature;

		//gs shape
		GeoShapeList _shapelist;

	};
}

#endif //OWPLUGIN_DATASOURCE_OGRFEATURE