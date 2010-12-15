#include "stdafx.h"
#include "CutElementCmd.h"

namespace Control
{

	static CCutElementCmd gCutElementCmd;

	CCutElementCmd::CCutElementCmd() : ICommand("CutElementCmd")
	{

	}

	CCutElementCmd::~CCutElementCmd()
	{

	}
	void CCutElementCmd::Initialize(Framework::IUIObject *pTargetControl)
	{
		ICommand::Initialize(pTargetControl);

		//获取活动地图控件
		m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
	}

	void CCutElementCmd::Click()
	{
		ICommand::Click();

		if(!m_pMapCtrl)
			return;


		Carto::CGraphicLayerPtr pLayer = m_pMapCtrl->GetMap()->GetGraphicLayer();
		if(!pLayer)
			return;

		Element::CElementCollection* copies = m_pMapCtrl->GetElementCopyContainer();

		copies->Clear();

		for(int i=0; i<pLayer->GetSelectedElementCount(); i++)
		{
			Element::IElementPtr pElement = pLayer->GetSelectedElement(i);
			copies->Add(pElement);
			pLayer->RemoveElement(pElement);
		}

		pLayer->UnselectAllElements();

		m_pMapCtrl->SetCurTool("SelectElementsTool");
	}

}