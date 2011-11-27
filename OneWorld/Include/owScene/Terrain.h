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

	/** Terrain�������������������ݣ�
	* 1������������Ҫ�ĸ��ֲ�����ͶӰ������Χ���̱߳����ȣ�
	* 2��ͼ������̲߳㡢Ӱ����ʸ���㣻
	* 3���黺�����������ο�Ļ��壬���ڸ���ͼ���ʱ��ˢ�»����еĵ��ο�
	* ���⣬ÿ��Terrain�ж�������һ���鹤�������ڹ��������ݡ�
	*/
	class OWSCENE_EXPORT Terrain : public osg::CoordinateSystemNode
	{
		friend class TerrainTileFactory;
	public:

		/** Ĭ�Ϲ��캯����ͶӰΪWGS84ȫ��ͶӰ������ΧΪ-180,180,-90,90*/
		Terrain();

		/** �������Թ���Terrain*/
		Terrain(SpatialProperty* sp);

		Terrain(const Terrain& terrain, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		META_Node(owScene,Terrain);

		/** Terrain�����ΨһID,�洢��Registry��Terrain�����У�����tile������ҵ���Ӧ��terrain����*/
		int getUID() const;

	public:

		/** ���ӣ���ʼ���������ݣ����������ڵ����ݣ�
		 ** �Ͽ����ӣ��˳���������*/
		void Initialize(ProgressBase* p=NULL);
		void unInitialize(ProgressBase* p = NULL);

		/** ���û�����Ľ�����������Ĭ��Ϊ32�����ھ��������ܹ��ֽ�������*/
		void setMaxLevel(unsigned int level);
		unsigned int getMaxLevel() const;

		/** ���û�õ��εĸ߳�����ϵ����Ĭ��Ϊ1.0��û������*/
		void setVerticalScale(float scale);
		float getVerticalScale() const;

		/** ���û�õ��ο��ȹ�ߺ͵��γߴ�ı�����Ĭ��Ϊ0.2,���ڷ�ֹ�ѷ�*/
		void setSkirtRadio(float radio);
		float getSkirtRadio() const;

		/** ���û�ÿ�ֽ⵽��һ���ľ��������Ĭ��Ϊ6.0���þ����ǿ�ߴ�͸ò����ĳ˻�*/
		void setMinTileRange(float radio);
		float getMinTileRange() const;

		/** ���õ��θ̶߳�ȡʱ�����ش�С��Ĭ��Ϊ64*/
		void setTileSize(unsigned int size);
		unsigned int getTileSize() const;

		/** ��������Ӱ���ȡʱ�����ش�С��Ĭ��Ϊ256*/
		void setImageSize(unsigned int size);
		unsigned int getImageSize() const;

		/** �����Ƿ�Ϊȫ�����*/
		bool isGeoCentric() const;

		/** ��ȡ����������ڿ���ϵĿ���*/
		unsigned int getNumTilesWideAtLod0() const;

		/** ��ȡ����������ڸ߶��ϵĿ���*/
		unsigned int getNumTilesHighAtLod() const;

		/** ��ȡ�鹤����ÿ��TerrainĬ�Ϲ���һ���鹤��*/
		TerrainTileFactory* getTileFactory() const;

		/** ��ȡ���εĵ���Χ��ͶӰ*/
		const SpatialProperty* getSP() const { return _sp; }
		SpatialProperty* getSP() {return _sp;}

		/** ���õ�����Ⱦ������TerrainĬ�ϴ���һ��������Ⱦ����*/
		void setTerrainRenderTech(TerrainRenderTech* tech);
		TerrainRenderTech* getTerrainRenderTech();
		const TerrainRenderTech* getTerrainRenderTech() const;

		/** ���ô�����Ⱦ������TerrainĬ�ϴ���һ��������Ⱦ����*/
		/*void setAtmTerrainRenderTech(TerrainRenderTech* tech);
		TerrainRenderTech* getAtmTerrainRenderTech();
		const TerrainRenderTech* getAtmTerrainRenderTech() const;*/

	public:

		/** ��Ӹ̲߳�*/
		void addEvelationLayer(ElevationLayer* elelyr);

		/** ����һ���̲߳�*/
		void insertEvelationLayer(ElevationLayer* elelyr,unsigned int pos);

		/** �Ƴ��̲߳�*/
		void removeEvelationLayer(ElevationLayer* elelyr);

		/** ��ø̲߳����*/
		unsigned int getElevationLayersCount() ;

		/** ͨ���������һ���̲߳�*/
		ElevationLayer* getEvelationLayer(unsigned int i) ;

		/** ͨ���̲߳�id��ȡ�̲߳�*/
		ElevationLayer* getEvelationLayerByUid(unsigned int uid) ;

		/** ���ø̲߳��λ��*/
		void setElevationLayerPos(ElevationLayer* elelyr,unsigned int newpos);

		/** ��ø̲߳��λ��*/
		unsigned int getElevationLayerPos(ElevationLayer* elelyr) ;

		/** ���Ӱ���*/
		void addImageLayer(ImageLayer* imglyr);

		/** ����һ��Ӱ���*/
		void insertImageLayer(ImageLayer* imglyr, unsigned int pos);

		/** �Ƴ�һ��Ӱ���*/
		void removeImageLayer(ImageLayer* imglyr);

		/** ���Ӱ���ĸ���*/
		unsigned int getImageLayersCount() ;

		/** ͨ���������Ӱ���*/
		ImageLayer* getImageLayer(unsigned int i) ;

		/** ͨ��Ӱ��id���Ӱ��*/
		ImageLayer* getImageLayerByUid(unsigned int uid) ;

		/** ����Ӱ����λ��*/
		void setImageLayerPos(ImageLayer* imglyr, unsigned int newpos);

		/** ���Ӱ����λ��*/
		unsigned int getImageLayerPos(ImageLayer* imglyr) ;

		/** ���һ��ʸ����*/
		void addFeatureLayer(FeatureLayer* flyr);

		/** �Ƴ�һ��ʸ����*/
		void removeFeatureLayer(FeatureLayer* flyr);

		/** ���ʸ�������*/
		unsigned int getFeatureLayersCount() ;

		/** ͨ�������Ż��ʸ����*/
		FeatureLayer* getFeatureLayer(unsigned int i) ;

		/** ͨ��ʸ����id�Ż�ȡʸ����*/
		FeatureLayer* getFeatureLayerByUid(unsigned int uid) ;

	public:

		/** ������DatabasePager����TerrainTileReadWriter�е���*/
		void registTerrainTile(TerrainTile* tile);

		/** ������DatabasePager����TilePagedLod�����ط���removeExpiredChildren�е���*/
		void unregisTerrainTile(TerrainTile* tile);

		/** ���TerrainTile*/
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
		// ��ȡ�����̲߳㣬Ӧ�õ�tile��
		void applyElvLayers(TerrainTile* tile) ;

		//��ȡ����ʸ���㣬Ӧ�õ�tile��
		void applyFeatureLayers(TerrainTile* tile) ;

		//��ȡ����Ӱ��㣬Ӧ�õ�tile��
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

		//����shader
		//osg::ref_ptr<TerrainRenderTech> _atmterrainrendertech;
	};
}

#endif //OWSCENE_TERRAIN_H_