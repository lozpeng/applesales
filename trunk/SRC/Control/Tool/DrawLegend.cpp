#include "stdafx.h"
#include "DrawLegend.h"
#include "Legend.h"

#include "IMapCtrl.h"
#include "ILayoutCtrl.h"
#include "Map.h"
#include "MapFrame.h"

#include "DllResource.h"

namespace Control
{

static CDrawLegendCmd gDrawLegend;

CDrawLegendCmd::CDrawLegendCmd() : ICommand("DrawLegendCmd")
{

}

CDrawLegendCmd::~CDrawLegendCmd()
{

}
void CDrawLegendCmd::Initialize(Framework::IUIObject *pTargetControl)
{
	ICommand::Initialize(pTargetControl);


	//获取活动地图控件
	m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);

}
void CDrawLegendCmd::Click()
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

	Element::CLegendPtr pLegend = pMapFrame->CreateMapSurroundElement(Element::ET_LEGEND);
	if(!pLegend)
		return;

	m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->AddElement(pLegend);
	m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->UnselectAllElements();
	m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->SelectElement(pLegend);
	
	//加入回退堆栈
	//pLayoutCtrl->GetPageLayout()->GetElementOperationStack()->AddOperation(Element::OPT_ADD, pLegend);

	//设置ActiveAction为选择图元
	m_pLayoutCtrl->SetCurTool("SelectFrameElementsTool");
	m_pLayoutCtrl->UpdateControl();
	
}


}