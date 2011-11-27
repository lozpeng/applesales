#ifndef OWSCENE_TERRAINTILE_H_
#define OWSCENE_TERRAINTILE_H_

#include <owScene/export.h>
#include <owScene/TileKey.h>
#include <owScene/TileSurfaceNode.h>
#include <owScene/Height.h>
#include <owScene/ImageProxy.h>
#include <owScene/FeatureNode.h>

#include <owUtil/SpatialProperty.h>

#include <OpenThreads/Mutex>

#include <osg/Group>
#include <map>

using namespace osg;
using namespace owUtil;

namespace owScene
{
	class Terrain;
	/** 地形块类：由TerainTileFactory创建。Terrian中层得实际再次表现*/
	class OWSCENE_EXPORT TerrainTile : public osg::Group
	{
	public:
		TerrainTile(const TileKey& key, SpatialProperty* sp);
		
		TerrainTile(const TerrainTile& tile, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		META_Node(owScene,TerrainTile);

	public:

		/** tile key*/
		const TileKey& getTileKey() const { return _key; }

		/** 地理范围*/
		const SpatialProperty* getSP() const { return _sp; }

		/** 获得地形节点
		*/
		TileSurfaceNode* getTileSurfaceNode();

		/** 设置Terrain*/
		void setParentTerrain(Terrain* t) { _parentTerrain = t; }
		Terrain* getParentTerrain() { return _parentTerrain; }
		const Terrain* getParentTerrain() const { return _parentTerrain; }

	public:

		/** 增加高程数据
		*/
		void addHeight(unsigned int index, HeightProxy* height);

		/** 插入高程数据*/
		void insertHeight(unsigned int index, unsigned int pos, HeightProxy* height);

		/** 移除高程层*/
		void removeHeight(unsigned int index);

		/** 获得高程层*/
		HeightProxy* getHeight(unsigned int index);

		/** 设置高程位置*/
		void setHeightPos(unsigned int index, unsigned int newpos);

		/** 设置高程可用与否*/
		void EnableHeight(unsigned int index, bool enable);

		/** 添加一张纹理图*/
		void addImage(unsigned int index,ImageProxy* image);

		/** 插入一张纹理图*/
		void InsertImage(unsigned int index, ImageProxy* image,unsigned int pos);

		/** 删除一张纹理图*/
		void removeImage(unsigned int index);

		/** 获得一张纹理图*/
		ImageProxy* getImage(unsigned int index);

		/** 设置纹理的位置*/
		void setImagePos(unsigned int index, unsigned int newpos);

		/** 纹理可用性*/
		void EnableImage(unsigned int index, bool enable);

		/** 添加一个FeatureLayer创建出的节点*/
		void addFeatureGroupNode(unsigned int index, FeatureGroupNode* fn);

		/** 删除一个FeatureLayer创建的节点*/
		void removeFeatureGroupNode(unsigned int index);

		//
		void genSlicePoints(std::vector<osg::Vec3d> ins, std::vector<osg::Vec3d>& outs) const;

		//
		void genIntersectPoint(const osg::Vec3d& first,const osg::Vec3d& second, osg::Vec3d& out) const;

		/** 获得一个FeatureLayer对象的节点*/
		FeatureGroupNode* getFeatureGroupNode(unsigned int index);

		/** 设置可用性*/
		void EnableFeatureGroupNode(unsigned int index, bool enable);

		/** 更新块*/
		void dirty();

		/** 设置更新地形标志*/
		void dirtyHeight() { _hdirty = true; }

		/** 设置更新纹理标志*/
		void dirtyImage() { _idirty = true; }

		/** 设置更新矢量标志*/
		void dirtyFeature() { _fdirty = true; }

	public:

		/** 设置高程缩放，更新地形缩放，实际更改了地形的高程值，做相交的时候获得为
		 * 缩放后的高程值
		 */
		void setVerticalScale(float vs);

		/** 设置纹理的透明度*/
		void setImageOpacity(unsigned int index, float op);

	public:

		virtual void traverse(NodeVisitor& nv);

	private:

		TerrainTile();
		~TerrainTile();

		Height* createFlatHeight();
		Height* combineHeight();

		void updateHeight();
		void updateImage();
		void updateFeatures();

		void seamTileSufaceNode();

	private:

		TileKey _key;
		osg::ref_ptr<SpatialProperty> _sp;
		
		osg::ref_ptr<TileSurfaceNode> _tsfnode;

		typedef std::pair<unsigned int,osg::ref_ptr<HeightProxy>> HeightProxyIndexPair;
		typedef std::pair<unsigned int,osg::ref_ptr<ImageProxy>> ImageProxyIndexPair;
		typedef std::pair<unsigned int,osg::ref_ptr<FeatureGroupNode>> FGNIndexPair;
		typedef std::vector<HeightProxyIndexPair> HeightProxys;
		typedef std::vector<ImageProxyIndexPair> ImageProxys;
		typedef std::vector<FGNIndexPair> FGNIndexPairs;

		HeightProxys _maphp;
		ImageProxys _mapip;
		FGNIndexPairs _mapfgn;

		bool _hdirty;
		bool _idirty;
		bool _fdirty;

		OpenThreads::Mutex _mutex;

		Terrain* _parentTerrain;

	};

	typedef std::map<std::string,osg::ref_ptr<TerrainTile>> TerrainTiles; 
}

#endif //OWSCENE_TERRAINTILE_H_