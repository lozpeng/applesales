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

		/** ������*/
		static Registry& instance();

		/** ע��terrain����Terrain����ʱ����*/
		void registTerrain(Terrain* terrain);
		/** ��ע��terrain*/
		void unRegisTerrain(int id);
		/** ���ע���terrain������TerrainTileReadWriter*/
		Terrain* getRegistTerrain(int id);

	protected:

		Registry();
		~Registry();

	private:

		std::map<int,osg::ref_ptr<Terrain>> _terrainmap;
	};
}

#endif //OWSCENE_REGISTRY_H_