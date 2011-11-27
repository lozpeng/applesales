#ifndef OWPLUGINS_TEXTURE_RENDER_LAYER_H_
#define OWPLUGINS_TEXTURE_RENDER_LAYER_H_

#include <owScene/ImageLayer.h>
#include <owScene/TerrainTile.h>
#include <owScene/FeatureSource.h>

using namespace owScene;
using namespace osg;

namespace owPlugins
{
	class TextureRenderLayer : public ImageLayer
	{
	public:
		TextureRenderLayer(){}
		~TextureRenderLayer(){}

		META_Object(owPlugins,TextureRenderLayer)

	public:

		virtual bool initialize(ProgressBase* base=NULL);
		virtual bool unInitialize(ProgressBase* base=NULL);

		virtual osg::Image* CreatImage(const TerrainTile* tile,unsigned int tilesize,ProgressBase* p=NULL);

		virtual void read(const Config& config);
		virtual void write(Config& config) const;

	protected:

		TextureRenderLayer(const TextureRenderLayer& el, const CopyOp& copyop = CopyOp::SHALLOW_COPY)
		{
			//not support
		}

	private:

		//
		osg::Node* createFeatureNode(const TerrainTile* tile, Feature* f);

		//
		osg::Group* createFeatureGroup(const TerrainTile* tile, ProgressBase* p);

		//
		//osg::Camera* CreateOverlayCamera(osg::Image* image,  const GeoExtent* extent, int tilesize);

		void opcache();
		osg::Node* readOrGetFromCache(const TerrainTile* tile, Feature* f);

	private:

		std::string _sourcename;
		std::string _imagefile;
		osg::ref_ptr<osg::Image> _image;
		OpenThreads::Mutex _mutex;
		typedef std::map<owScene::FeatureOID,osg::ref_ptr<osg::Node>> NodeCache;
		NodeCache _nodecache;
	};
}
	
#endif //OWPLUGINS_TEXTURE_RENDER_LAYER_H_