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
	/** 块工厂类：用于生产块数据。当TilePagedLod在需要分解的条件下，会调用TerrainTileReadWriter插件，插件
	* 中会调用Terrain中工厂类的createTile方法。createTile方法会创建相应的块节点返回TerrainTileReadWriter，并
	* 最终加入到场景中渲染。createTile创建的TerrainTile会放到Terrain块缓冲中（by the way，块从缓冲中删除是
	* 在TilePagedLod析构的过程中剔除）。
	* 此外：当Terrain中对层进行操作时，会调用工厂中相应的update***方法更新块数据。
	*/
	class OWSCENE_EXPORT TerrainTileFactory : public osg::Referenced
	{
		friend class Terrain;
	public:
		
		TerrainTileFactory(Terrain* terrain);

		/** 创建一个块*/
		osg::Node* createTile(const TileKey& tilekey);
		
		/** 创建地形的根节点*/
		osg::Group* createRoot();

	private:
		~TerrainTileFactory(){}

		//创建子块，createTile实际上是创建了四块子块
		TerrainTile* createSubTile(const TileKey& tilekey);

		// 根据Tilekey计算在Terrain地形上的地理范围
		SpatialProperty* calculateSpatialProperty(const TileKey& tilekey);

		// 按照Terrain地理范围来计算获得根节点上的分块TileKey
		void getRootKeys(std::vector<TileKey>& keys);

		// 按照Terrain地理范围来计算在某一金字塔级别地形块的地理范围
		void getTileDimensions(unsigned int lod, double& out_width, double& out_height);

	private:

		Terrain* _terrain;
	};
}

#endif //OWSCENE_TILEFACTORY_H_