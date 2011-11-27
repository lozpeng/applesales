#ifndef OWSCENE_IMAGELAYER_H_
#define OWSCENE_IMAGELAYER_H_

#include <owScene/export.h>
#include <owScene/Layer.h>
#include <owScene/TerrainTile.h>
#include <osg/Image>

namespace owScene
{
	class Terrain;

	/**影像层，插件中重载实现CreatImage方法，创建返回Image对象*/
	class OWSCENE_EXPORT ImageLayer : public Layer
	{
	public:
		ImageLayer();
		ImageLayer(const ImageLayer& lyr, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

	public:

		virtual osg::Image* CreatImage(const TerrainTile* tile, unsigned int tilesize,ProgressBase* p=NULL) =0;

		virtual void setEnable(bool enable);
		virtual bool getEnable();

		virtual void read(const Config& config);
		virtual void write(Config& config);

	protected:

		virtual ~ImageLayer();

	};
}

#endif //OWSCENE_IMAGELAYER_H_