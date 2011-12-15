#include "stdafx.h"
#include "DrawMapFrameElementCmd.h"
#include "IMapCtrl.h"
#include "ILayoutCtrl.h"
#include "Map.h"
#include "MapFrame.h"

namespace Control
{

static CDrawMapFrameElementCmd gDrawMapFrameElementCmd;

CDrawMapFrameElementCmd::CDrawMapFrameElementCmd() : ICommand("DrawMapFrameElementCmd")
{
	
}

CDrawMapFrameElementCmd::~CDrawMapFrameElementCmd()
{

}

void CDrawMapFrameElementCmd::Initialize(Framework::IUIObject *pTargetControl)
{
	ICommand::Initialize(pTargetControl);


	//获取活动地图控件
	m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);
	if(!m_pLayoutCtrl)
		return;
}
void CDrawMapFrameElementCmd::Click()
{
	ICommand::Click();

	//获取活动制图控件
	Framework::ILayoutCtrl* pLayoutCtrl = Framework::ILayoutCtrl::GetActiveLayoutCtrl();
	m_pLayoutCtrl = pLayoutCtrl;
	if(!m_pLayoutCtrl)
		return;

	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;
	Carto::CMapPtr pMap = pMapCtrl->GetMap();

	GEOMETRY::geom::Envelope env = m_pLayoutCtrl->GetPageLayout()->GetPage()->GetPageEnvelope();
	env.expandBy(-10);
	GEOMETRY::geom::Geometry* pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&env);
	Element::CMapFramePtr pMapFrame = new Element::CMapFrame(*pGeometry, pMap);
	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeometry);
	m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->UnselectAllElements();
	m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->AddElement(pMapFrame);
	m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->SelectElement(pMapFrame);
	//pLayoutCtrl->GetPageLayout()->GetElementOperationStack()->AddOperation(Element::PT_ADD, pMapFrame);
	m_pLayoutCtrl->UpdateControl(drawAll);

	//设置ActiveAction为选择图元
	m_pLayoutCtrl->SetCurTool("SelectFrameElements");
}


}