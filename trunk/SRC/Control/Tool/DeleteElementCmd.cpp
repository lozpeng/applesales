#include "stdafx.h"
#include "DeleteElementCmd.h"

namespace Control
{

static CDeleteElementCmd gDeleteElementCmd;

CDeleteElementCmd::CDeleteElementCmd() : ICommand("DeleteElementCmd")
{
	
}

CDeleteElementCmd::~CDeleteElementCmd()
{

}

void CDeleteElementCmd::Initialize(Framework::IUIObject *pTargetControl)
{
	ICommand::Initialize(pTargetControl);

	//获取活动地图控件
	m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
}


void CDeleteElementCmd::Click()
{
	ICommand::Click();

	if(!m_pMapCtrl)
		return;

	Carto::CMapPtr pMap = m_pMapCtrl->GetMap();
	if(!pMap)
		return;

	Carto::CGraphicLayerPtr pLayer = pMap->GetGraphicLayer();
	if(!pLayer)
		return;

	for(int i=0; i<pLayer->GetSelectedElementCount(); i++)
	{
		pLayer->RemoveElement(pLayer->GetSelectedElement(i));
	}

	//加入回退堆栈
	//pMap->GetElementOperationStack()->AddOperation(Element::OPT_REMOVE, pLayer->GetSelectedElements());

	pLayer->UnselectAllElements();
	m_pMapCtrl->UpdateControl(drawElement | drawEdit);
	m_pMapCtrl->SetCurTool("SelectElements");
}

}