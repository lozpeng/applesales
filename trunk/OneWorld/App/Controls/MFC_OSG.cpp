// MFC_OSG.cpp : implementation of the cOSG class
//
#include "stdafx.h"
#include <process.h>
#include "MFC_OSG.h"
#include <osgGA/StateSetManipulator>
#include <owScene/PreRenderGroup.h>
#include <owScene/Terrain.h>
#include <owScene/AtmosphericScatteringRenderTech.h>
#include <owNavi/AutoClipPlaneHandler.h>
#include <owUtil/LocaleReadWriteCallback.h>

cOSG::cOSG(HWND hWnd) :
   m_hWnd(hWnd) 
{
}

cOSG::~cOSG()
{
    mViewer->setDone(true);
    Sleep(1000);
    mViewer->stopThreading();

    delete mViewer;
}

void cOSG::InitOSG(std::string modelname)
{
    // Store the name of the model to load
	
    m_ModelName = osgDB::findLibraryFile(modelname);;

    // Init different parts of OSG
    InitManipulators();
    InitSceneGraph();
    InitCameraConfig();
}

void cOSG::InitManipulators(void)
{
    // Create a trackball manipulator
	tm = new owNavi::TerrainManipulator2();
	osgDB::Registry::instance()->setReadFileCallback(new ReadChsFileCallBack());
	osgDB::Registry::instance()->setWriteFileCallback(new WriteChsFileCallback());
	osg::DisplaySettings::instance()->setNumOfDatabaseThreadsHint(8);
	osg::setNotifyLevel(osg::ALWAYS);
}


void cOSG::InitSceneGraph(void)
{

	// Create the viewer for this window
	mViewer = new osgViewer::Viewer();

    // Load the Model from the model name
	mRoot = dynamic_cast<owScene::Scene*>(osgDB::readNodeFile(m_ModelName));
 
	//add atmospheric
	//osg::ref_ptr<owScene::AtmosphericScatteringRenderTech> atmos = new owScene::AtmosphericScatteringRenderTech(mViewer);
	//mRoot->SetAtmospheric(atmos);

}

void cOSG::InitCameraConfig(void)
{
    // Local Variable to hold window size data
    RECT rect;

    
    // Get the current window size
    ::GetWindowRect(m_hWnd, &rect);

    // Init the GraphicsContext Traits
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;

    // Init the Windata Variable that holds the handle for the Window to display OSG in.
    osg::ref_ptr<osg::Referenced> windata = new osgViewer::GraphicsWindowWin32::WindowData(m_hWnd);

    // Setup the traits parameters
    traits->x = 0;
    traits->y = 0;
    traits->width = rect.right - rect.left;
    traits->height = rect.bottom - rect.top;
    traits->windowDecoration = false;
    traits->doubleBuffer = true;
    traits->sharedContext = 0;
    traits->setInheritedWindowPixelFormat = true;
    traits->inheritedWindowData = windata;

    // Create the Graphics Context
    osg::GraphicsContext* gc = osg::GraphicsContext::createGraphicsContext(traits.get());

    // Init a new Camera (Master for this View)
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;

    // Assign Graphics Context to the Camera
    camera->setGraphicsContext(gc);

    // Set the viewport for the Camera
    camera->setViewport(new osg::Viewport(traits->x, traits->y, traits->width, traits->height));

    // Set projection matrix and camera attribtues
    camera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    camera->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.4f, 1.0f));
    camera->setProjectionMatrixAsPerspective(
        30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0, 1000.0);

    // Add the Camera to the Viewer
    //mViewer->addSlave(camera.get());
    mViewer->setCamera(camera.get());

    // Add the Camera Manipulator to the Viewer
    mViewer->setCameraManipulator(tm.get());

    // Set the Scene Data
    mViewer->setSceneData(mRoot.get());


	// Add event Handler to the viewer
	mViewer->addEventHandler(new osgViewer::StatsHandler);
	mViewer->addEventHandler(new owNavi::AutoClipPlaneHandler(mRoot->GetTerrain()));
	mViewer->addEventHandler(new osgGA::StateSetManipulator(mViewer->getCamera()->getOrCreateStateSet()));

	//set manipulator node
	tm->setNode(mRoot->GetTerrain());

    // Realize the Viewer
    mViewer->realize();

}

void cOSG::PreFrameUpdate()
{
    // Due any preframe updates in this routine
}

void cOSG::PostFrameUpdate()
{
    // Due any postframe updates in this routine
}

void cOSG::Render(void* ptr)
{
    cOSG* osg = (cOSG*)ptr;

    osgViewer::Viewer* viewer = osg->getViewer();

    // You have two options for the main viewer loop
    //      viewer->run()   or
    //      while(!viewer->done()) { viewer->frame(); }

    //viewer->run();
    while(!viewer->done())
    {
        osg->PreFrameUpdate();
        viewer->frame();
        osg->PostFrameUpdate();
        //Sleep(10);         // Use this command if you need to allow other processes to have cpu time
    }

    // For some reason this has to be here to avoid issue: 
    // if you have multiple OSG windows up 
    // and you exit one then all stop rendering
    //AfxMessageBox("Exit Rendering Thread");

    _endthread();
}
