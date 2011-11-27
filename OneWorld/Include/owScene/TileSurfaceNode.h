#ifndef _OWSCENE_TILESURFACENODE_H_
#define _OWSCENE_TILESURFACENODE_H_

#include <owScene/export.h>
#include <owScene/Height.h>
#include <owScene/TileKey.h>
#include <osg/MatrixTransform>
#include <osg/Geometry>
#include <osg/Geode>

using namespace osg;

namespace owScene
{
	/** 地形节点，由TerrainTile构建。LocalSurface的顶点坐标已经在Tile中心点的基础上经过
	 * 平移，tile中心构建了matrix用于构建TileSurfaceNode防止抖动
	 */
	class TerrainTile;
	class OWSCENE_EXPORT TileSurfaceNode : public osg::MatrixTransform
	{
	public:
		TileSurfaceNode();

		TileSurfaceNode(const TileSurfaceNode&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		META_Node(owScene,TileSurfaceNode);

	public:

		/**设置属于的tile*/
		void setParentTile(TerrainTile* tile) { _parenttile = tile; }
		TerrainTile* getParentTile() { return _parenttile; }

		/**设置缩放比例*/
		void setVerticalScale(float scale);

		/**构建地表节点*/
		void constructGeometry(Height* hf);

		/**和临边的地形缝合*/
		void seamNeighbor(TileSurfaceNode* nbnode, TileKey::NEIGHBORS nb);

		/**获得地表geode*/
		osg::Geode* getLocalSurface() { return _geode; }

	private:

		/**设置获得位置*/
		void setPosition(unsigned int c, unsigned int r,const osg::Vec3& pos);
		osg::Vec3 getPosition(unsigned int c, unsigned int r);

		/**设置获得法向量*/
		void setNormal(unsigned int c, unsigned int r,const osg::Vec3& n);
		osg::Vec3 getNormal(unsigned int c, unsigned int r);
		osg::Vec3 getNormal(unsigned int c, unsigned int r, bool bGlobal);

		/**获得高程*/
		float getHeight(unsigned int c, unsigned int r);

	protected:

		~TileSurfaceNode(){}

	private:

		TerrainTile* _parenttile;
		Height* _height;
		osg::Geode* _geode;
		osg::Geometry* _geometry;
		osg::Vec3Array* _vertexs;
		osg::Vec3Array* _nomals;
		osg::Vec2Array* _texcoors;

		unsigned int _tilesize;
		double _xinterval;
		double _yinterval;
		osg::Vec3d _origin;
	};
}
#endif //_OWSCENE_TILESURFACENODE_H_