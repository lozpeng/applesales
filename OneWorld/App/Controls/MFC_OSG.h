#pragma once

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/api/win32/GraphicsWindowWin32>
#include <owNavi/TerrainManipulator2.h>
#include <osgDB/DatabasePager>
#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osgDB/FileUtils>
#include <string>
#include <owScene/Scene.h>
#include "ControlDefine.h"

class CONTROL_DLL cOSG
{
public:
    cOSG(HWND hWnd);
    ~cOSG();

    void InitOSG(std::string filename);
    void InitManipulators(void);
    void InitSceneGraph(void);
    void InitCameraConfig(void);
    void SetupWindow(void);
    void SetupCamera(void);
    void PreFrameUpdate(void);
    void PostFrameUpdate(void);
    void Done(bool value) { mDone = value; }
    bool Done(void) { return mDone; }
    static void Render(void* ptr);
    osgViewer::Viewer* getViewer() { return mViewer; }
	owNavi::TerrainManipulator2*	getTerrainManipulator(){return tm.get();};
	owScene::Scene*					getScene(){return mRoot.get();};
private:
    bool mDone;
    std::string m_ModelName;
    HWND m_hWnd;
    osgViewer::Viewer* mViewer;
    osg::ref_ptr<owScene::Scene> mRoot;

	osg::ref_ptr<owNavi::TerrainManipulator2> tm;

};
