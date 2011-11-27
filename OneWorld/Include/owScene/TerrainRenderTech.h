#ifndef OWSCENE_TERRAINRENDERTECH_H_
#define OWSCENE_TERRAINRENDERTECH_H_

#include <owScene/export.h>
#include <owScene/TerrainTile.h>
#include <osg/Object>
#include <osg/Program>
#include <osg/Uniform>

using namespace osg;

namespace owScene
{
	/** ������Ⱦ���������εı��֣�����shader����*/
	class OWSCENE_EXPORT TerrainRenderTech : public osg::Object
	{	

	protected: //���ܴ��������ʵ��

		TerrainRenderTech();
		TerrainRenderTech(const TerrainRenderTech&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

	public:

		META_Object(owScene,TerrainRenderTech);

		virtual void apply(TerrainTile* tile);
		virtual void unapply(TerrainTile* tile);

		//virtual osg::Node* GetOSGNode() {return NULL;}

	protected:

		virtual ~TerrainRenderTech();

	protected:

		osg::ref_ptr<osg::Program> _program;
		std::vector<osg::ref_ptr<osg::Uniform>> _uniforms;
	};
}

#endif //OWSCENE_TERRAINRENDERTECH_H_