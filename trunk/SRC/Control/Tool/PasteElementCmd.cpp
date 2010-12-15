#include "stdafx.h"
#include "PasteElementCmd.h"


namespace Control
{

static CPasteElementCmd gPasteElementCmd;

CPasteElementCmd::CPasteElementCmd() : ICommand("PasteElementCmd")
{
	
}

CPasteElementCmd::~CPasteElementCmd()
{

}
void CPasteElementCmd::Initialize(Framework::IUIObject *pTargetControl)
{
	ICommand::Initialize(pTargetControl);

	//获取活动地图控件
	m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
}


void CPasteElementCmd::Click()
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

	Element::CElementCollection* copies = m_pMapCtrl->GetElementCopyContainer();

	if(copies->IsEmpty())
		return;

	pLayer->UnselectAllElements();

	long offsetDis = 10;
	double offsetGeo; 
	pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(offsetDis,offsetGeo);

	for(int i=0; i<copies->Count(); i++)
	{
		Element::IElementPtr pElement = copies->QueryElement(i);
		
		Element::IElementPtr pCopy = pElement->Clone();

		pCopy->Move(offsetGeo, offsetGeo);

		pLayer->AddElement(pCopy);

		pLayer->SelectElement(pCopy);
	}

	//加入回退堆栈
	//pMap->GetElementOperationStack()->AddOperation(otElement::OPT_EDIT_PROPERTY, pLayer->GetSelectedElements());

	m_pMapCtrl->UpdateControl(drawElement | drawEdit);

	m_pMapCtrl->SetCurTool("SelectElementsTool");
}

}