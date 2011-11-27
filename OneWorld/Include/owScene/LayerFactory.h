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

		/** 根据给定参数创建高程层，会调用加载相应的插件*/
		ElevationLayer* createElevationLayer(const Config& config);

		/** 根据给定参数创建影像层，会调用加载相应插件*/
		ImageLayer* createImageLayer(const Config& config);

		/** 根据给定参数创建矢量层，会调用加载相应插件*/
		FeatureLayer* createFeatureLayer(const Config& config);

	protected:

		LayerFactory();
		~LayerFactory();

	};
}

#endif //OWSCENE_LAYERFACTORY_H_