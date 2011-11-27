#ifndef OWSCENE_TERRAIN_H_
#define OWSCENE_TERRAIN_H_

#include <owScene/export.h>
#include <owScene/ElevationLayer.h>
#include <owScene/ImageLayer.h>
#include <owScene/FeatureLayer.h>
#include <owScene/TileKey.h>
#include <owScene/TerrainTile.h>
#include <owScene/TerrainTileFactory.h>
#include <owScene/TerrainRenderTech.h>

#include <owUtil/ProgressBase.h>
#include <owUtil/config.h>
#include <osg/CoordinateSystemNode>
#include <OpenThreads/Mutex>
#include <vector>

using namespace osg;

namespace owScene
{

	/** Terrain类管理了三个方面的内容：
	* 1、构建地形需要的各种参数：投影、地理范围、高程比例等；
	* 2、图层管理：高程层、影像层和矢量层；
	* 3、块缓冲管理：管理地形块的缓冲，并在更改图层的时候刷新缓冲中的地形块
	* 此外，每个Terrain中都包含了一个块工厂，用于构建块数据。
	*/
	class OWSCENE_EXPORT Terrain : public osg::CoordinateSystemNode
	{
		friend class TerrainTileFactory;
	public:

		/** 默认构造函数，投影为WGS84全球投影，地理范围为-180,180,-90,90*/
		Terrain();

		/** 地理属性构造Terrain*/
		Terrain(SpatialProperty* sp);

		Terrain(const Terrain& terrain, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		META_Node(owScene,Terrain);

		/** Terrain对象的唯一ID,存储于Registry的Terrain缓冲中，用于tile插件中找到对应的terrain对象*/
		int getUID() const;

	public:

		/** 连接：初始化各层数据，并构建根节点数据；
		 ** 断开连接：退出各层数据*/
		void Initialize(ProgressBase* p=NULL);
		void unInitialize(ProgressBase* p = NULL);

		/** 设置获得最大的金字塔级数，默认为32，用于决定地形能够分解的最大级数*/
		void setMaxLevel(unsigned int level);
		unsigned int getMaxLevel() const;

		/** 设置获得地形的高程扩张系数，默认为1.0，没有扩张*/
		void setVerticalScale(float scale);
		float getVerticalScale() const;

		/** 设置获得地形块的裙边和地形尺寸的比例，默认为0.2,用于防止裂缝*/
		void setSkirtRadio(float radio);
		float getSkirtRadio() const;

		/** 设置获得块分解到下一级的距离比例，默认为6.0，该距离是块尺寸和该参数的乘积*/
		void setMinTileRange(float radio);
		float getMinTileRange() const;

		/** 设置地形高程读取时的像素大小，默认为64*/
		void setTileSize(unsigned int size);
		unsigned int getTileSize() const;

		/** 设置纹理影像读取时的像素大小，默认为256*/
		void setImageSize(unsigned int size);
		unsigned int getImageSize() const;

		/** 地形是否为全球地形*/
		bool isGeoCentric() const;

		/** 获取最顶级金字塔在宽度上的块数*/
		unsigned int getNumTilesWideAtLod0() const;

		/** 获取最顶级金字塔在高度上的块数*/
		unsigned int getNumTilesHighAtLod() const;

		/** 获取块工厂，每个Terrain默认构造一个块工厂*/
		TerrainTileFactory* getTileFactory() const;

		/** 获取地形的地理范围及投影*/
		const SpatialProperty* getSP() const { return _sp; }
		SpatialProperty* getSP() {return _sp;}

		/** 设置地形渲染技术，Terrain默认创建一个纹理渲染技术*/
		void setTerrainRenderTech(TerrainRenderTech* tech);
		TerrainRenderTech* getTerrainRenderTech();
		const TerrainRenderTech* getTerrainRenderTech() const;

		/** 设置大气渲染技术，Terrain默认创建一个大气渲染技术*/
		/*void setAtmTerrainRenderTech(TerrainRenderTech* tech);
		TerrainRenderTech* getAtmTerrainRenderTech();
		const TerrainRenderTech* getAtmTerrainRenderTech() const;*/

	public:

		/** 添加高程层*/
		void addEvelationLayer(ElevationLayer* elelyr);

		/** 插入一个高程层*/
		void insertEvelationLayer(ElevationLayer* elelyr,unsigned int pos);

		/** 移除高程层*/
		void removeEvelationLayer(ElevationLayer* elelyr);

		/** 获得高程层个数*/
		unsigned int getElevationLayersCount() ;

		/** 通过索引获得一个高程层*/
		ElevationLayer* getEvelationLayer(unsigned int i) ;

		/** 通过高程层id获取高程层*/
		ElevationLayer* getEvelationLayerByUid(unsigned int uid) ;

		/** 设置高程层的位置*/
		void setElevationLayerPos(ElevationLayer* elelyr,unsigned int newpos);

		/** 获得高程层的位置*/
		unsigned int getElevationLayerPos(ElevationLayer* elelyr) ;

		/** 添加影像层*/
		void addImageLayer(ImageLayer* imglyr);

		/** 插入一个影像层*/
		void insertImageLayer(ImageLayer* imglyr, unsigned int pos);

		/** 移除一个影像层*/
		void removeImageLayer(ImageLayer* imglyr);

		/** 获得影像层的个数*/
		unsigned int getImageLayersCount() ;

		/** 通过索引获得影像层*/
		ImageLayer* getImageLayer(unsigned int i) ;

		/** 通过影像id获得影像*/
		ImageLayer* getImageLayerByUid(unsigned int uid) ;

		/** 设置影像层的位置*/
		void setImageLayerPos(ImageLayer* imglyr, unsigned int newpos);

		/** 获得影像层的位置*/
		unsigned int getImageLayerPos(ImageLayer* imglyr) ;

		/** 添加一个矢量层*/
		void addFeatureLayer(FeatureLayer* flyr);

		/** 移除一个矢量层*/
		void removeFeatureLayer(FeatureLayer* flyr);

		/** 获得矢量层个数*/
		unsigned int getFeatureLayersCount() ;

		/** 通过索引号获得矢量层*/
		FeatureLayer* getFeatureLayer(unsigned int i) ;

		/** 通过矢量层id号获取矢量层*/
		FeatureLayer* getFeatureLayerByUid(unsigned int uid) ;

	public:

		/** 依托于DatabasePager，在TerrainTileReadWriter中调用*/
		void registTerrainTile(TerrainTile* tile);

		/** 依托于DatabasePager，在TilePagedLod中重载方法removeExpiredChildren中调用*/
		void unregisTerrainTile(TerrainTile* tile);

		/** 获得TerrainTile*/
		TerrainTile* getRegistTerrainTile(const TileKey& key);

	public:
		void read(const Config& config);
		void write(Config& config) const;

	protected:
		~Terrain();

		void Init();
		void UnInit();
		void validate();
		void registry();

	private:
		// 读取各个高程层，应用到tile中
		void applyElvLayers(TerrainTile* tile) ;

		//读取各个矢量层，应用到tile中
		void applyFeatureLayers(TerrainTile* tile) ;

		//读取各个影像层，应用到tile中
		void applyImageLayers(TerrainTile* tile) ;

	private:

		int _uid;

		unsigned int _maxlevel;
		float _verticalscale;
		float _skitradio;
		float _mintilerange;
		unsigned int _tilesize;
		unsigned int _imagesize;

		unsigned int _numTilesWideAtLod0;
		unsigned int _numTilesHighAtLod0;

		std::vector<osg::ref_ptr<ElevationLayer>> _elelayers;
		std::vector<osg::ref_ptr<ImageLayer>> _imglyrs;
		std::vector<osg::ref_ptr<FeatureLayer>> _featurelyrs;
		OpenThreads::Mutex _elelyrmutex;
		OpenThreads::Mutex _imglyrmutex;
		OpenThreads::Mutex _fealyrmutex;

		osg::ref_ptr<SpatialProperty> _sp;

		osg::ref_ptr<TerrainTileFactory> _tilefactroy;

		TerrainTiles _tilecache;
		OpenThreads::Mutex _cachemutex;

		osg::ref_ptr<TerrainRenderTech> _terrainrendertech;

		//大气shader
		//osg::ref_ptr<TerrainRenderTech> _atmterrainrendertech;
	};
}

#endif //OWSCENE_TERRAIN_H_