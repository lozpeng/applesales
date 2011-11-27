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
	/** ���ο��ࣺ��TerainTileFactory������Terrian�в��ʵ���ٴα���*/
	class OWSCENE_EXPORT TerrainTile : public osg::Group
	{
	public:
		TerrainTile(const TileKey& key, SpatialProperty* sp);
		
		TerrainTile(const TerrainTile& tile, const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		META_Node(owScene,TerrainTile);

	public:

		/** tile key*/
		const TileKey& getTileKey() const { return _key; }

		/** ����Χ*/
		const SpatialProperty* getSP() const { return _sp; }

		/** ��õ��νڵ�
		*/
		TileSurfaceNode* getTileSurfaceNode();

		/** ����Terrain*/
		void setParentTerrain(Terrain* t) { _parentTerrain = t; }
		Terrain* getParentTerrain() { return _parentTerrain; }
		const Terrain* getParentTerrain() const { return _parentTerrain; }

	public:

		/** ���Ӹ߳�����
		*/
		void addHeight(unsigned int index, HeightProxy* height);

		/** ����߳�����*/
		void insertHeight(unsigned int index, unsigned int pos, HeightProxy* height);

		/** �Ƴ��̲߳�*/
		void removeHeight(unsigned int index);

		/** ��ø̲߳�*/
		HeightProxy* getHeight(unsigned int index);

		/** ���ø߳�λ��*/
		void setHeightPos(unsigned int index, unsigned int newpos);

		/** ���ø߳̿������*/
		void EnableHeight(unsigned int index, bool enable);

		/** ���һ������ͼ*/
		void addImage(unsigned int index,ImageProxy* image);

		/** ����һ������ͼ*/
		void InsertImage(unsigned int index, ImageProxy* image,unsigned int pos);

		/** ɾ��һ������ͼ*/
		void removeImage(unsigned int index);

		/** ���һ������ͼ*/
		ImageProxy* getImage(unsigned int index);

		/** ���������λ��*/
		void setImagePos(unsigned int index, unsigned int newpos);

		/** ���������*/
		void EnableImage(unsigned int index, bool enable);

		/** ���һ��FeatureLayer�������Ľڵ�*/
		void addFeatureGroupNode(unsigned int index, FeatureGroupNode* fn);

		/** ɾ��һ��FeatureLayer�����Ľڵ�*/
		void removeFeatureGroupNode(unsigned int index);

		//
		void genSlicePoints(std::vector<osg::Vec3d> ins, std::vector<osg::Vec3d>& outs) const;

		//
		void genIntersectPoint(const osg::Vec3d& first,const osg::Vec3d& second, osg::Vec3d& out) const;

		/** ���һ��FeatureLayer����Ľڵ�*/
		FeatureGroupNode* getFeatureGroupNode(unsigned int index);

		/** ���ÿ�����*/
		void EnableFeatureGroupNode(unsigned int index, bool enable);

		/** ���¿�*/
		void dirty();

		/** ���ø��µ��α�־*/
		void dirtyHeight() { _hdirty = true; }

		/** ���ø��������־*/
		void dirtyImage() { _idirty = true; }

		/** ���ø���ʸ����־*/
		void dirtyFeature() { _fdirty = true; }

	public:

		/** ���ø߳����ţ����µ������ţ�ʵ�ʸ����˵��εĸ߳�ֵ�����ཻ��ʱ����Ϊ
		 * ���ź�ĸ߳�ֵ
		 */
		void setVerticalScale(float vs);

		/** ���������͸����*/
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