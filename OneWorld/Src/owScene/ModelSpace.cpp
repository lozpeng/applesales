#include <owScene/ModelSpace.h>

using namespace owScene;


ModelSpace::ModelSpace(const ModelSpace& fn,const osg::CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/)
: Group(fn,copyop)
{

}

void ModelSpace::AddModelLayer(ModelLayer* layer)
{
	_layerlist.push_back(layer);

	osg::Node* node = layer->GetRoot();

	addChild(node);
}