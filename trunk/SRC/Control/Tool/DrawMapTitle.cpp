#include "stdafx.h"
#include "DrawMapTitle.h"
#include "ILayoutCtrl.h"
#include "MapTitle.h"
#include "MapFrame.h"



namespace Control
{

static CDrawMapTitle gDrawMapTitle;

CDrawMapTitle::CDrawMapTitle() : ICommand("DrawMapTitleCmd")
{
	
}

CDrawMapTitle::~CDrawMapTitle()
{

}

void CDrawMapTitle::Initialize(Framework::IUIObject *pTargetControl)
{
	ICommand::Initialize(pTargetControl);


	//��ȡ���ͼ�ؼ�
	m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);

}
void CDrawMapTitle::Click()
{
	ICommand::Click();

	//��ȡ���ͼ�ؼ�
	if(!m_pLayoutCtrl)
		return;

	Element::IElementPtr pElement = m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->GetSelectedElement(0);
	if(!pElement || pElement->GetType() != Element::ET_MAP_FRAME_ELEMENT)
		return;

	Element::CMapFrame* pMapFrame = dynamic_cast<Element::CMapFrame*>(pElement.get());
	Carto::CMapPtr pMap = pMapFrame->GetMap();
	if(!pMap)
		return;

	Element::CMapTitlePtr pMapTitle = pMapFrame->CreateMapSurroundElement(Element::ET_MAP_TITLE);
	if(!pMapTitle)
		return;

	m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->UnselectAllElements();
	m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->AddElement(pMapTitle);
	m_pLayoutCtrl->GetPageLayout()->GetGraphicLayer()->SelectElement(pMapTitle);	
	//m_pLayoutCtrl->GetPageLayout()->GetElementOperationStack()->AddOperation(otElement::OPT_ADD, pMapTitle);
	m_pLayoutCtrl->UpdateControl();

	//����ActiveActionΪѡ��ͼԪ
	m_pLayoutCtrl->SetCurTool("SelectFrameElementsTool");
}

}