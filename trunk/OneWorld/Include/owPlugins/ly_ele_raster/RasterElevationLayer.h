#ifndef OWPLUGINS_RASTERELEVATIONLAYER_H_
#define OWPLUGINS_RASTERELEVATIONLAYER_H_

#include <owScene/ElevationLayer.h>


using namespace owScene;
using namespace osg;

namespace owPlugins
{
	class RasterElevationLayer : public ElevationLayer
	{
	public:
		RasterElevationLayer(){}
		~RasterElevationLayer(){}

		META_Object(owPlugins,RasterElevationLayer)

	public:

		virtual bool initialize(ProgressBase* base=NULL);
		virtual bool unInitialize(ProgressBase* base=NULL);

		virtual Height* CreatHeight(const TerrainTile* tile,unsigned int tilesize,ProgressBase* p=NULL);

		virtual void read(const Config& config);
		virtual void write(Config& config) const;

	protected:

		RasterElevationLayer(const RasterElevationLayer& el, const CopyOp& copyop = CopyOp::SHALLOW_COPY)
		{
			//not support
		}

	private:

		std::string _sourcename;
	};
}

#endif //OWPLUGINS_RASTERELEVATIONLAYER_H_