#include "stdafx.h"
#include "SketchTool.h"
#include "IMapCtrl.h"
#include "CEditor.h"
#include "Editor.h"
#include "resource.h"
#include "Featurelayer.h"
extern CEditorApp theApp;

namespace Editor
{

static CSketchTool gSketchTool;

CSketchTool::CSketchTool() : ITool("SketchTool")
{

	cursorNormal = NULL;
}

CSketchTool::~CSketchTool()
{

} 

	//初始化
void CSketchTool::Initialize(Framework::IUIObject *pTargetControl)
{
	ITool::Initialize(pTargetControl);
	
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	cursorNormal =::LoadCursor( theApp.m_hInstance , ATL_MAKEINTRESOURCE( IDC_Arrow));
	
	pMapCtrl->SetCursor(cursorNormal);
}

void CSketchTool::LButtonDownEvent (UINT nFlags, CPoint point)
{
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;

	CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return;
	}

	//设置编辑空间的状态
	pEdit->SetbSketch(true);

	pEdit->SetbEditFeature(false);

	pEdit->SetbEditVertex(true);

	GEOMETRY::geom::Coordinate inPt,outPt;
	pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,inPt);

	pEdit->Snap(inPt,outPt);

    CPoint  cpt;
	pMap->GetDisplay()->GetDisplayTransformation().ConvertGeoToDisplay(outPt.x,outPt.y,cpt.x,cpt.y);

	//如果在原地点击的时候，则不添加点

	if(cpt!=m_clickPt)
	{
		pEdit->AddSketchPoint(outPt);

		pMapCtrl->UpdateControl(drawEdit);

		m_clickPt =cpt;
	} 

}

void CSketchTool::MouseMoveEvent (UINT nFlags, CPoint point)
{

	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return;
	}
	GEOMETRY::geom::Coordinate inPt,outPt;
	pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,inPt);

	pEdit->Snap(inPt,outPt);

	pMapCtrl->UpdateControl(drawEdit);


}

void CSketchTool::LButtonUpEvent (UINT nFlags, CPoint point)
{

	//绘制点要素 结束
	//结束绘制
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit||!pEdit->GetCurLayer())
	{
		return;
	}
	if(Carto::LAYER_TYPE::FeatureLayer == pEdit->GetCurLayer()->GetLayerType())
	{
		Carto::CFeatureLayer* pFeatureLayer = (Carto::CFeatureLayer*)pEdit->GetCurLayer();
		long iFeatureType = pFeatureLayer->GetFeatureType();
		if(iFeatureType== GEOMETRY::geom::GEOS_POINT)
		{
			pEdit->FinishSketch();

			m_clickPt.x =-1;
			m_clickPt.y =-1;
		}

	}

}

void CSketchTool::LButtonDblClkEvent(UINT nFlags, CPoint point)
{
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return;
	}

	//结束绘制
	pEdit->FinishSketch();

    m_clickPt.x =-1;
	m_clickPt.y =-1;
}

void CSketchTool::RButtonDownEvent(UINT nFlags, CPoint point)
{
	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	/*CWnd* pWnd =dynamic_cast<CWnd*>(pMapCtrl);
	if(!pWnd)
	{
		return;
	}
	CDllResource hdll;
	CMenu Menu;


	if (Menu.LoadMenu(IDR_MENU_EDIT_SKETCH))
	{
		CMenu* pPopup = NULL;
		pPopup = Menu.GetSubMenu(0);
		if (pPopup!=NULL)
		{
			CPoint srnPoint = point;
			pWnd->ClientToScreen(&srnPoint);
			pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,srnPoint.x,srnPoint.y,pWnd);
		}
	}*/
}

}