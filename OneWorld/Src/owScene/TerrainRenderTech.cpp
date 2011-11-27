#include <owScene/TerrainRenderTech.h>

using namespace owScene;

TerrainRenderTech::TerrainRenderTech()
{
	_program = new osg::Program();
}

TerrainRenderTech::TerrainRenderTech(const TerrainRenderTech& tech,const CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/)
: Object(tech,copyop)
{
	_program = tech._program;
}

TerrainRenderTech::~TerrainRenderTech()
{
	;
}

void TerrainRenderTech::apply(TerrainTile* tile)
{
	if(!_program.valid())
		return;
	if(!tile)
		return;
	TileSurfaceNode* sfn = tile->getTileSurfaceNode();
	if(!sfn)
		return;

	osg::Geometry* geometry = sfn->getLocalSurface()->getDrawable(0)->asGeometry();
	if(geometry)
	{
		osg::StateSet* ss = geometry->getOrCreateStateSet();

		ss->setAttributeAndModes(_program.get());

		for (unsigned int i=0; i<_uniforms.size(); i++)
		{
			osg::Uniform* u = _uniforms[i].get();
			if(u)
				ss->addUniform(u);
		}
	}

}

void TerrainRenderTech::unapply(TerrainTile* tile)
{
	if(!tile)
		return;

	TileSurfaceNode* sfn = tile->getTileSurfaceNode();
	if(!sfn)
		return;
	osg::StateSet* ss = sfn->getOrCreateStateSet();

	ss->removeAttribute(_program.get());

	for (unsigned int i=0; i<_uniforms.size(); i++)
	{
		osg::Uniform* u = _uniforms[i].get();
		if(u)
			ss->removeUniform(u);
	}
}