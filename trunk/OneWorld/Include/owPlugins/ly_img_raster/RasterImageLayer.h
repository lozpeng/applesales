#ifndef OWPLUGINS_RASTERIMAGELAYER_H_
#define OWPLUGINS_RASTERIMAGELAYER_H_

#include <owScene/ImageLayer.h>

using namespace owScene;
using namespace osg;

namespace owPlugins
{
	class RasterImageLayer : public ImageLayer
	{
	public:
		RasterImageLayer(){}
		~RasterImageLayer(){}

		META_Object(owPlugins,RasterImageLayer)

	public:

		virtual bool initialize(ProgressBase* base=NULL);
		virtual bool unInitialize(ProgressBase* base=NULL);

		virtual osg::Image* CreatImage(const TerrainTile* tile,unsigned int tilesize,ProgressBase* p=NULL);

		virtual void read(const Config& config);
		virtual void write(Config& config) const;

	protected:

		RasterImageLayer(const RasterImageLayer& el, const CopyOp& copyop = CopyOp::SHALLOW_COPY)
		{
			//not support
		}

	private:

		std::string _sourcename;
	};
}

#endif //OWPLUGINS_RASTERIMAGELAYER_H_