#include "stdafx.h"
#include "ActionSketch.h"
#include "IMapCtrl.h"
#include "Editor.h"
#include "EditorRes.h"
#include "resource.h"

namespace otEditor
{

static CActionSketch gActionSketch;

CActionSketch::CActionSketch() : IAction("ActionSketch")
{
	RegisterAction("ActionSketch",this);
}

CActionSketch::~CActionSketch()
{

} 

void CActionSketch::Triger()
{
	//��ȡ���ͼ�ؼ�
	otFramework::IMapCtrl *pMapCtrl = otFramework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//���ù������
	pMapCtrl->SetCursorType(cursorNormal);

	IAction::Initialize();
}

void CActionSketch::LButtonDownEvent (UINT nFlags, CPoint point)
{
	//��ȡ���ͼ�ؼ�
	otFramework::IMapCtrl *pMapCtrl = otFramework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//��ȡ�����
	otCarto::CGeoMapPtr pMap = pMapCtrl->GetActiveMap();
	if(!pMap)
		return;

	otEditor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return;
	}

	//���ñ༭�ռ��״̬
	pEdit->SetbSketch(true);

	pEdit->SetbEditFeature(false);

	pEdit->SetbEditVertex(true);

	TT_GEOMETRY::geom::Coordinate inPt,outPt;
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

void CActionSketch::MouseMoveEvent (UINT nFlags, CPoint point)
{

	//��ȡ���ͼ�ؼ�
	otFramework::IMapCtrl *pMapCtrl = otFramework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//��ȡ�����
	otCarto::CGeoMapPtr pMap = pMapCtrl->GetActiveMap();
	if(!pMap)
		return;

	otEditor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return;
	}
	TT_GEOMETRY::geom::Coordinate inPt,outPt;
	pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,inPt);

	pEdit->Snap(inPt,outPt);

	pMapCtrl->UpdateControl(drawEdit);


}

void CActionSketch::LButtonUpEvent (UINT nFlags, CPoint point)
{


}

void CActionSketch::LButtonDblClkEvent(UINT nFlags, CPoint point)
{
	//��ȡ���ͼ�ؼ�
	otFramework::IMapCtrl *pMapCtrl = otFramework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//��ȡ�����
	otCarto::CGeoMapPtr pMap = pMapCtrl->GetActiveMap();
	if(!pMap)
		return;

	otEditor::CEditorPtr pEdit =pMap->GetEditor();
	if(!pEdit)
	{
		return;
	}

	//��������
	pEdit->FinishSketch();

    m_clickPt.x =-1;
	m_clickPt.y =-1;
}

void CActionSketch::RButtonDownEvent(UINT nFlags, CPoint point)
{
	//��ȡ���ͼ�ؼ�
	otFramework::IMapCtrl *pMapCtrl = otFramework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	CWnd* pWnd =dynamic_cast<CWnd*>(pMapCtrl);
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
	}
}

}