#ifndef OWSCENE_REGISTRY_H_
#define OWSCENE_REGISTRY_H_

#include <owScene/export.h>
#include <owScene/Terrain.h>

#include <osg/Referenced>

using namespace owScene;

namespace owScene
{
	class OWSCENE_EXPORT Registry : public osg::Referenced
	{
	public:

		/** 单件类*/
		static Registry& instance();

		/** 注册terrain，在Terrain构造时调用*/
		void registTerrain(Terrain* terrain);
		/** 反注册terrain*/
		void unRegisTerrain(int id);
		/** 获得注册的terrain，用于TerrainTileReadWriter*/
		Terrain* getRegistTerrain(int id);

	protected:

		Registry();
		~Registry();

	private:

		std::map<int,osg::ref_ptr<Terrain>> _terrainmap;
	};
}

#endif //OWSCENE_REGISTRY_H_