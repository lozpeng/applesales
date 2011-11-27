#include <owScene/Scene.h>
#include <owScene/PreRenderGroup.h>
#include <owScene/SunModel.h>

using namespace owScene;

Scene::Scene(const Scene& fn,const CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/)
: Group(fn,copyop)
{

}


void Scene::Initialize() 
{ 
	//
	addChild(owScene::getGlobalPreRenderGroup());

	//
	CreateLightSource();
}

void Scene::CreateLightSource()
{
	owScene::SunModel* sun = new owScene::SunModel;
	sun->Init(2011,6,18,12,0,0, 117);

	addChild(sun);


}