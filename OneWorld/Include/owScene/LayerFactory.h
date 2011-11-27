#ifndef OWSCENE_LAYERFACTORY_H_
#define OWSCENE_LAYERFACTORY_H_

#include <owScene/export.h>
#include <owScene/ElevationLayer.h>
#include <owScene/ImageLayer.h>
#include <owScene/FeatureLayer.h>

#include <osg/Referenced>

namespace owScene
{
	class OWSCENE_EXPORT LayerFactory : public osg::Referenced
	{
	public:
		static LayerFactory& Instance();

		/** ���ݸ������������̲߳㣬����ü�����Ӧ�Ĳ��*/
		ElevationLayer* createElevationLayer(const Config& config);

		/** ���ݸ�����������Ӱ��㣬����ü�����Ӧ���*/
		ImageLayer* createImageLayer(const Config& config);

		/** ���ݸ�����������ʸ���㣬����ü�����Ӧ���*/
		FeatureLayer* createFeatureLayer(const Config& config);

	protected:

		LayerFactory();
		~LayerFactory();

	};
}

#endif //OWSCENE_LAYERFACTORY_H_