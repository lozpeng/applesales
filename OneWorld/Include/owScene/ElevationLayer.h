#ifndef OWSCENE_ELEVATIONLAYER_H_
#define OWSCENE_ELEVATIONLAYER_H_

#include <owScene/export.h>
#include <owScene/Layer.h>
#include <owScene/Height.h>
#include <owScene/TerrainTile.h>

using namespace owUtil;

namespace owScene
{
	class Terrain;
	/** �̲߳㣬�ڲ����м̳в�ʵ��CreatHeight���������ظ߳�����*/
	class OWSCENE_EXPORT ElevationLayer : public Layer
	{
	public:
		ElevationLayer();
		ElevationLayer(const ElevationLayer& lyr, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

	public:

		virtual Height* CreatHeight(const TerrainTile* tile,unsigned int tilesize,ProgressBase* p=NULL) = 0;

		virtual void setEnable(bool enable);
		virtual bool getEnable();

		virtual void read(const Config& config);
		virtual void write(Config& config);

	protected:

		virtual ~ElevationLayer();

	};


}

#endif //OWSCENE_ELEVATIONLAYER_H_

