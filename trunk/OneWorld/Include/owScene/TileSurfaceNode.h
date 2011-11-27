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
	/** ���νڵ㣬��TerrainTile������LocalSurface�Ķ��������Ѿ���Tile���ĵ�Ļ����Ͼ���
	 * ƽ�ƣ�tile���Ĺ�����matrix���ڹ���TileSurfaceNode��ֹ����
	 */
	class TerrainTile;
	class OWSCENE_EXPORT TileSurfaceNode : public osg::MatrixTransform
	{
	public:
		TileSurfaceNode();

		TileSurfaceNode(const TileSurfaceNode&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

		META_Node(owScene,TileSurfaceNode);

	public:

		/**�������ڵ�tile*/
		void setParentTile(TerrainTile* tile) { _parenttile = tile; }
		TerrainTile* getParentTile() { return _parenttile; }

		/**�������ű���*/
		void setVerticalScale(float scale);

		/**�����ر�ڵ�*/
		void constructGeometry(Height* hf);

		/**���ٱߵĵ��η��*/
		void seamNeighbor(TileSurfaceNode* nbnode, TileKey::NEIGHBORS nb);

		/**��õر�geode*/
		osg::Geode* getLocalSurface() { return _geode; }

	private:

		/**���û��λ��*/
		void setPosition(unsigned int c, unsigned int r,const osg::Vec3& pos);
		osg::Vec3 getPosition(unsigned int c, unsigned int r);

		/**���û�÷�����*/
		void setNormal(unsigned int c, unsigned int r,const osg::Vec3& n);
		osg::Vec3 getNormal(unsigned int c, unsigned int r);
		osg::Vec3 getNormal(unsigned int c, unsigned int r, bool bGlobal);

		/**��ø߳�*/
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