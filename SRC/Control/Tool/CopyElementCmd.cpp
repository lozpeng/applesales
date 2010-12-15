#include "stdafx.h"
#include "CopyElementCmd.h"


namespace Control
{

	static CCopyElementCmd gCopyElementCmd;

	CCopyElementCmd::CCopyElementCmd() : ICommand("CopyElementCmd")
	{

	}

	CCopyElementCmd::~CCopyElementCmd()
	{

	}
	void CCopyElementCmd::Initialize(Framework::IUIObject *pTargetControl)
	{
		ICommand::Initialize(pTargetControl);

		//获取活动地图控件
		m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
	}

	void CCopyElementCmd::Click()
	{
		ICommand::Click();

		if(!m_pMapCtrl)
			return;
		//获取活动地区
		Carto::CMapPtr  pMap = m_pMapCtrl->GetMap();
		if(!pMap)
			return;

		Carto::CGraphicLayerPtr pLayer = pMap->GetGraphicLayer();
		if(!pLayer)
			return;

		if(pLayer->GetSelectedElementCount() == 0)
			return;

		long offsetDis = 5;
		double offsetGeo; 
		pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(offsetDis,offsetGeo);

		Element::CElementCollection* copies = m_pMapCtrl->GetElementCopyContainer();

		copies->Clear();

		for(int i=0; i<pLayer->GetSelectedElementCount(); i++)
		{
			Element::IElementPtr pCopy = pLayer->GetSelectedElement(i);
			copies->Add(pCopy);
		}

		m_pMapCtrl->SetCurTool("SelectElementsTool");
	}

}