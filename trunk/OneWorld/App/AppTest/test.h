#include <osgViewer/Viewer>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <owScene/PreRenderGroup.h>
#include <owScene/Terrain.h>
#include <owNavi/TerrainManipulator2.h>
#include <owScene/Scene.h>
#include <osgDB/Registry>
#include <osgDB/ReaderWriter>
#include <osgDB/ReadFile>
#include <owUtil/LocaleReadWriteCallback.h>
#include <owNavi/AutoClipPlaneHandler.h>
#include <owNavi/selectHandler.h>

int test(int argc, char* argv[])
{

	osgDB::Registry::instance()->setReadFileCallback(new owUtil::ReadChsFileCallBack());
	osgDB::Registry::instance()->setWriteFileCallback(new owUtil::WriteChsFileCallback());
	osg::DisplaySettings::instance()->setNumOfDatabaseThreadsHint(8);
	osg::setNotifyLevel(osg::ALWAYS);

	osgViewer::Viewer viewer;
	osg::ArgumentParser arguments(&argc,argv);

	//
	owScene::Scene* e = (owScene::Scene*)osgDB::readNodeFiles(arguments);

	owScene::AtmosphericScatteringRenderTech *att = new owScene::AtmosphericScatteringRenderTech(&viewer);
	e->SetAtmospheric(att);
	viewer.setSceneData(e);

	viewer.setCameraManipulator(new owNavi::TerrainManipulator2());
	viewer.addEventHandler(new osgViewer::StatsHandler);
	viewer.addEventHandler(new owNavi::AutoClipPlaneHandler(e->GetTerrain()));
	viewer.addEventHandler(new owNavi::SelNodeHandler());
	viewer.addEventHandler(new osgViewer::ThreadingHandler);
	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));

	viewer.getCameraManipulator()->setNode(e->GetTerrain());;
	viewer.setUpViewInWindow(100,100,800,600);

	return viewer.run();
}