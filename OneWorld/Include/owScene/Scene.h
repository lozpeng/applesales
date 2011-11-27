#ifndef _OWSCENE_EARTHNODE_H
#define _OWSCENE_EARTHNODE_H


#include <owScene/export.h>
#include <owScene/AtmosphericScatteringRenderTech.h>
#include <owScene/Terrain.h>
#include <owScene/ModelSpace.h>
#include <osg/Group>

namespace owScene
{

	class OWSCENE_EXPORT Scene : public osg::Group
	{
	public:

		Scene(){}

		Scene(const Scene& fgn, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		META_Node(owScene,Scene);

	public:

		//初始化
		void Initialize();

		//
		void SetTerrain(Terrain* terrain) { _terrain = terrain; addChild(terrain);}
		Terrain* GetTerrain() { return _terrain.get(); }

		//
		void SetAtmospheric(AtmosphericScatteringRenderTech*  atmospheric) { _atmospheric = atmospheric; addChild(atmospheric->GetOSGNode());}
		AtmosphericScatteringRenderTech* GetAtmospheric() { return _atmospheric.get(); }

		//
		void SetModelSpace(ModelSpace* modelspace) { _modelspace = modelspace; addChild(modelspace); }
		ModelSpace* GetModelSpace() { return _modelspace.get(); }

	protected:

		~Scene(){}

		void CreateLightSource();

	private:

		//地形节点
		osg::ref_ptr<Terrain> _terrain;

		//大气绘制对象
		osg::ref_ptr<AtmosphericScatteringRenderTech> _atmospheric;

		//模型节点
		osg::ref_ptr<ModelSpace> _modelspace;
	};

}

#endif