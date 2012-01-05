#include "stdafx.h"
#include "DrawNorthArrow.h"
#include "MarkerNorthArrow.h"
#include "CharMarkerSymbol.h"
#include "Map.h"
#include "MapFrame.h"
#include "ISymbolListCtrl.h"

namespace Control
{

static CDrawNorthArrowCmd gDrawNorthArrowCmd;

CDrawNorthArrowCmd::CDrawNorthArrowCmd() : ICommand("DrawNorthArrowCmd")
{
	
}

CDrawNorthArrowCmd::~CDrawNorthArrowCmd()
{

}

void CDrawNorthArrowCmd::Initialize(Framework::IUIObject *pTargetControl)
{
	ICommand::Initialize(pTargetControl);


	//获取活动地图控件
	m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);

}
void CDrawNorthArrowCmd::Click()
{
	ICommand::Click();

	//获取活动制图控件
	if(!m_pLayoutCtrl)
		return;

	Display::CCharMarkerSymbolPtr pSymbol(new Display::CCharMarkerSymbol);

	Framework::ISymbolListCtrl *pCtrl =dynamic_cast<Framework::ISymbolListCtrl*>(Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppSymbolLstCtrl));
	if(pCtrl)
	{
		pSymbol =pCtrl->SelectSymbol2(pSymbol);
	}

	if(!pSymbol)
		return;


	//获取活动制图控件
	Framework::ILayoutCtrl* pLayoutCtrl = Framework::ILayoutCtrl::GetActiveLayoutCtrl();
	if(!pLayoutCtrl)
		return;

	Element::IElementPtr pElement = pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->GetSelectedElement(0);
	if(!pElement || pElement->GetType() != Element::ET_MAP_FRAME_ELEMENT)
		return;

	Element::CMapFrame* pMapFrame = dynamic_cast<Element::CMapFrame*>(pElement.get());
	Carto::CMapPtr pMap = pMapFrame->GetMap();
	if(!pMap)
		return;

	Element::CMarkerNorthArrowPtr pNorthArrow = pMapFrame->CreateMapSurroundElement(Element::ET_MARKER_NORTH_ARROW);
	if(!pNorthArrow)
		return;

	pNorthArrow->SetSymbol(pSymbol);

	pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->UnselectAllElements();
	pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->AddElement(pNorthArrow);
	pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->SelectElement(pNorthArrow);	
	//pLayoutCtrl->GetPageLayout()->GetElementOperationStack()->AddOperation(otElement::OPT_ADD, pNorthArrow);
	pLayoutCtrl->UpdateControl();

	//设置ActiveAction为选择图元
	m_pLayoutCtrl->SetCurTool("SelectFrameElementsTool");

	CWnd *pWnd =dynamic_cast<CWnd*>(pLayoutCtrl);
	pWnd->SetFocus();
	
}


}