#include "StdAfx.h"
#include "IActionDrawElement.h"
#include "../otMapControl.h"
#include "../otMapCtrl.h"

IActionDrawElement::IActionDrawElement(long id): IAction(id)
{
	RegisterAction(id,this);
}

IActionDrawElement::~IActionDrawElement(void)
{
}

void IActionDrawElement::Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap)
{
	if((!pMapCtrl) ||(!pMap))
	{
        return;
	}
	Carto::CGraphicLayerPtr pGraphicLayer = pMap->GetGraphicLayer();
	if(!pGraphicLayer)
		return;

	//���ѡ��
	pGraphicLayer->UnselectAllElements();

	//���ù������
	pMapCtrl->SetCursorType(cursorCross);

	IAction::Init(pMapCtrl,pMap);
}

void IActionDrawElement::LButtonDownEvent (UINT nFlags, CPoint point)
{
	//��¼�ƶ����
	cPtStart = cPtEnd = point;

	
	//�������
	m_pMapCtrl->SetCapture();
}
void IActionDrawElement::MouseMoveEvent (UINT nFlags, CPoint point)
{
	if(!(nFlags&MK_LBUTTON)) 
		return;

	//��¼�ƶ���λ��
	cPtEnd = point;
}
void IActionDrawElement::LButtonUpEvent (UINT nFlags, CPoint point)
{

	//�������
	m_pMapCtrl->ReleaseCapture();

}

void IActionDrawElement::LButtonDblClkEvent (UINT nFlags, CPoint point)
{
	
	//���»���
	m_pMapCtrl->UpdateContent((otDrawContent)(otDrawElement));


	ReleaseCapture();
}

