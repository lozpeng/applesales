#include "stdafx.h"
#include "SketchTool.h"
#include "IMapCtrl.h"
#include "CEditor.h"
#include "resource.h"

namespace Editor
{

static CSketchTool gSketchTool;

CSketchTool::CSketchTool() : ITool("SketchTool")
{
	
}

CSketchTool::~CSketchTool()
{

} 

	//��ʼ��
void CSketchTool::Initialize(Framework::IUIObject *pTargetControl)
{
	ITool::Initialize(pTargetControl);
}

void CSketchTool::LButtonDownEvent (UINT nFlags, CPoint point)
{
	//��ȡ���ͼ�ؼ�
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//��ȡ�����
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;

	CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return;
	}

	//���ñ༭�ռ��״̬
	pEdit->SetbSketch(true);

	pEdit->SetbEditFeature(false);

	pEdit->SetbEditVertex(true);

	GEOMETRY::geom::Coordinate inPt,outPt;
	pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,inPt);

	pEdit->Snap(inPt,outPt);

    CPoint  cpt;
	pMap->GetDisplay()->GetDisplayTransformation().ConvertGeoToDisplay(outPt.x,outPt.y,cpt.x,cpt.y);

	//�����ԭ�ص����ʱ������ӵ�

	if(cpt!=m_clickPt)
	{
		pEdit->AddSketchPoint(outPt);

		pMapCtrl->UpdateControl(drawEdit);

		m_clickPt =cpt;
	} 

}

void CSketchTool::MouseMoveEvent (UINT nFlags, CPoint point)
{

	//��ȡ���ͼ�ؼ�
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//��ȡ�����
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


}

void CSketchTool::LButtonDblClkEvent(UINT nFlags, CPoint point)
{
	//��ȡ���ͼ�ؼ�
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//��ȡ�����
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;

	Editor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return;
	}

	//��������
	pEdit->FinishSketch();

    m_clickPt.x =-1;
	m_clickPt.y =-1;
}

void CSketchTool::RButtonDownEvent(UINT nFlags, CPoint point)
{
	//��ȡ���ͼ�ؼ�
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