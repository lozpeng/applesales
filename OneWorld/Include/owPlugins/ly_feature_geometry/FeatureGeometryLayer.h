#ifndef OWPLUGINS_FEATURE_GEOMETRY_LAYER_H_
#define OWPLUGINS_FEATURE_GEOMETRY_LAYER_H_

#include <owScene/FeatureLayer.h>

using namespace owScene;

namespace owPlugins
{
	class FeatureGeometryLayer : public FeatureLayer
	{
	public:
		FeatureGeometryLayer();
		~FeatureGeometryLayer();

		META_Object(owScene,FeatureGeometryLayer)

	public:

		virtual osg::Node* createNode(const TerrainTile* tile, Feature* f);

		virtual void read(const Config& config);
		virtual void write(Config& config);

		virtual void setEnable(bool enable);
		virtual bool getEnable();

		virtual bool initialize(ProgressBase* base=NULL);
		virtual bool unInitialize(ProgressBase* base=NULL);

	protected:

		FeatureGeometryLayer(const FeatureGeometryLayer& gl, const CopyOp& copyop = CopyOp::SHALLOW_COPY)
		{
			//not support
		}

	private:

		//
		std::string _sourcename;
	};
}

#endif //GSPLUGINS_FEATURE_GEOMETRY_LAYER_H_