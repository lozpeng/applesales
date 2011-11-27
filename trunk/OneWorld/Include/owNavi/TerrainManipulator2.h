#ifndef GSUTIL_TERRAINMANIPULATOR2_H_
#define GSUTIL_TERRAINMANIPULATOR2_H_

#include <owNavi/export.h>
#include <owScene/Terrain.h>
#include <osgGA/TerrainManipulator>

namespace owNavi
{
	class OWNAVI_EXPORT TerrainManipulator2 : public osgGA::TerrainManipulator
	{
	public:

		TerrainManipulator2( int flags = DEFAULT_SETTINGS );
		TerrainManipulator2( const TerrainManipulator2& tm,
			const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY );

		//META_Object( owNavi, TerrainManipulator2 );

	protected:

		virtual bool performMovementMiddleMouseButton( const double eventTimeDelta, const double dx, const double dy );
		virtual bool performMovementLeftMouseButton(  const double eventTimeDelta, const double dx, const double dy  );
		virtual bool performMovementRightMouseButton( const double eventTimeDelta, const double dx, const double dy );

	public:
		//��ָ��Layer���ĵ�õ���ֱ���õ����ͼ����lookat
		virtual void LookAtLayer(owScene::Layer* pLayer, osg::Matrix& lookat);
	};

}

#endif