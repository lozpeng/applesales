#include "stdafx.h"
#include "DrawScaleBar.h"
#include "AlternatingScaleBar.h"
#include "TextSymbol.h"

#include "IMapCtrl.h"
#include "ILayoutCtrl.h"
#include "Map.h"
#include "MapFrame.h"

#include "DllResource.h"

//#include "ScaleBarProperSheet.h"

namespace Control
{

static CDrawScaleBarCmd gDrawScaleBar;

CDrawScaleBarCmd::CDrawScaleBarCmd() : ICommand("DrawScaleBarCmd")
{

}

CDrawScaleBarCmd::~CDrawScaleBarCmd()
{

}

void CDrawScaleBarCmd::Initialize(Framework::IUIObject *pTargetControl)
{
	ICommand::Initialize(pTargetControl);

	//获取活动地图控件
	m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);

}
void CDrawScaleBarCmd::Click()
{
	ICommand::Click();

	//获取活动制图控件
	if(!m_pLayoutCtrl)
		return;

	Element::IElementPtr pElement = m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->GetSelectedElement(0);
	if(!pElement || pElement->GetType() != Element::ET_MAP_FRAME_ELEMENT)
		return;

	Element::CMapFrame* pMapFrame = dynamic_cast<Element::CMapFrame*>(pElement.get());
	Carto::CMapPtr pMap = pMapFrame->GetMap();
	if(!pMap)
		return;

	Element::CAlternatingScaleBarPtr pAlternatingScaleBar = pMapFrame->CreateMapSurroundElement(Element::ET_ALTERNATING_SCALEBAR);
	if(!pAlternatingScaleBar)
		return;

	//CDllResource hdll;
	//CScaleBarProperSheet sheet("属性");
	//sheet.SetElement(pAlternatingScaleBar);
	//if(sheet.DoModal()==IDOK)
	//{
	//	Element::IScaleBarPtr pScaleBar = sheet.GetElement();
	//	m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->UnselectAllElements();
	//	m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->AddElement(pScaleBar);
	//	m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->SelectElement(pScaleBar);	
	//	//m_pLayoutCtrl->GetPageLayout()->GetElementOperationStack()->AddOperation(otElement::OPT_ADD, pScaleBar);
	//	m_pLayoutCtrl->UpdateControl();
	//}

	//设置ActiveAction为选择图元
	m_pLayoutCtrl->SetCurTool("SelectFrameElementsTool");
	CWnd *pWnd =dynamic_cast<CWnd*>(m_pLayoutCtrl);
	pWnd->SetFocus();
}


}