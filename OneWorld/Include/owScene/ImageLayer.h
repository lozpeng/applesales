#ifndef OWSCENE_IMAGELAYER_H_
#define OWSCENE_IMAGELAYER_H_

#include <owScene/export.h>
#include <owScene/Layer.h>
#include <owScene/TerrainTile.h>
#include <osg/Image>

namespace owScene
{
	class Terrain;

	/**Ӱ��㣬���������ʵ��CreatImage��������������Image����*/
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