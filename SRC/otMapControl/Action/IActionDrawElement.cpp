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

	//清空选择集
	pGraphicLayer->UnselectAllElements();

	//设置光标类型
	pMapCtrl->SetCursorType(cursorCross);

	IAction::Init(pMapCtrl,pMap);
}

void IActionDrawElement::LButtonDownEvent (UINT nFlags, CPoint point)
{
	//记录移动起点
	cPtStart = cPtEnd = point;

	
	//锁定鼠标
	m_pMapCtrl->SetCapture();
}
void IActionDrawElement::MouseMoveEvent (UINT nFlags, CPoint point)
{
	if(!(nFlags&MK_LBUTTON)) 
		return;

	//记录移动点位置
	cPtEnd = point;
}
void IActionDrawElement::LButtonUpEvent (UINT nFlags, CPoint point)
{

	//锁定鼠标
	m_pMapCtrl->ReleaseCapture();

}

void IActionDrawElement::LButtonDblClkEvent (UINT nFlags, CPoint point)
{
	
	//更新绘制
	m_pMapCtrl->UpdateContent((otDrawContent)(otDrawElement));


	ReleaseCapture();
}

