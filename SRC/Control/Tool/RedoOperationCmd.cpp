#include "stdafx.h"
#include "RedoOperationCmd.h"



namespace Control
{

	static CRedoOperationCmd gRedoOperationCmd;

	CRedoOperationCmd::CRedoOperationCmd() : ICommand("RedoOperationCmd")
	{

	}

	CRedoOperationCmd::~CRedoOperationCmd()
	{

	}
	void CRedoOperationCmd::Initialize(Framework::IUIObject *pTargetControl)
	{
		ICommand::Initialize(pTargetControl);

		//��ȡ���ͼ�ؼ�
		m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
	}


	void CRedoOperationCmd::Click()
	{
		ICommand::Click();

		if(!m_pMapCtrl)
			return;

		Carto::CMapPtr pMap = m_pMapCtrl->GetMap();
		if(!pMap)
			return;


		//pMap->GetElementOperationStack()->Redo();

		m_pMapCtrl->UpdateControl(drawElement | drawEdit);

		m_pMapCtrl->SetCurTool("SelectElements");
	}

}