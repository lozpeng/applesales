#ifndef OWPLUGINS_FEATURE_OVERLAY_LAYER_H_
#define OWPLUGINS_FEATURE_OVERLAY_LAYER_H_

#include <owScene/ImageLayer.h>
#include <owScene/TerrainTile.h>
#include <owScene/FeatureSource.h>

using namespace owScene;
using namespace osg;

namespace owPlugins
{
	class FeatureOverlayLayer : public ImageLayer
	{
	public:
		FeatureOverlayLayer();
		~FeatureOverlayLayer(){}

		META_Object(owPlugins,FeatureOverlayLayer)

	public:

		virtual bool initialize(ProgressBase* base=NULL);
		virtual bool unInitialize(ProgressBase* base=NULL);

		virtual osg::Image* CreatImage(const TerrainTile* tile,unsigned int tilesize,ProgressBase* p=NULL);

		virtual void read(const Config& config);
		virtual void write(Config& config) const;

		///线宽
		float GetLineWidth() const {return _line_width;}
		bool SetLineWidth(float line_width) { _line_width = line_width; return true;}

		///颜色
		const osg::Vec4 GetColor() const {return _color;}
		bool SetColor(const osg::Vec4 color) { _color = color; return true;}

	protected:

		FeatureOverlayLayer(const FeatureOverlayLayer& el, const CopyOp& copyop = CopyOp::SHALLOW_COPY)
		{
			//not support
		}

	private:

		//
		osg::Node* createFeatureNode(const TerrainTile* tile, Feature* f);

		//
		osg::Group* createFeatureGroup(const TerrainTile* tile, ProgressBase* p);

		//
		osg::Camera* CreateOverlayCamera(osg::Image* image,  const GeoExtent* extent, int tilesize);

	private:

		std::string _sourcename;

		//线宽
		float _line_width;

		//颜色
		osg::Vec4 _color;

	};
}
	
#endif //OWPLUGINS_FEATURE_OVERLAY_LAYER_H_