#ifndef OWSCENE_TILEFACTORY_H_
#define OWSCENE_TILEFACTORY_H_

#include <owScene/export.h>
#include <osg/Referenced>
#include <osg/Geode>
#include <owScene/TerrainTile.h>
#include <owScene/TileKey.h>
#include <owScene/Terrain.h>

namespace owScene
{
	/** �鹤���ࣺ�������������ݡ���TilePagedLod����Ҫ�ֽ�������£������TerrainTileReadWriter��������
	* �л����Terrain�й������createTile������createTile�����ᴴ����Ӧ�Ŀ�ڵ㷵��TerrainTileReadWriter����
	* ���ռ��뵽��������Ⱦ��createTile������TerrainTile��ŵ�Terrain�黺���У�by the way����ӻ�����ɾ����
	* ��TilePagedLod�����Ĺ������޳�����
	* ���⣺��Terrain�жԲ���в���ʱ������ù�������Ӧ��update***�������¿����ݡ�
	*/
	class OWSCENE_EXPORT TerrainTileFactory : public osg::Referenced
	{
		friend class Terrain;
	public:
		
		TerrainTileFactory(Terrain* terrain);

		/** ����һ����*/
		osg::Node* createTile(const TileKey& tilekey);
		
		/** �������εĸ��ڵ�*/
		osg::Group* createRoot();

	private:
		~TerrainTileFactory(){}

		//�����ӿ飬createTileʵ�����Ǵ������Ŀ��ӿ�
		TerrainTile* createSubTile(const TileKey& tilekey);

		// ����Tilekey������Terrain�����ϵĵ���Χ
		SpatialProperty* calculateSpatialProperty(const TileKey& tilekey);

		// ����Terrain����Χ�������ø��ڵ��ϵķֿ�TileKey
		void getRootKeys(std::vector<TileKey>& keys);

		// ����Terrain����Χ��������ĳһ������������ο�ĵ���Χ
		void getTileDimensions(unsigned int lod, double& out_width, double& out_height);

	private:

		Terrain* _terrain;
	};
}

#endif //OWSCENE_TILEFACTORY_H_