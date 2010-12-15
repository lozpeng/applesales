#include "stdafx.h"
#include "UndoOperationCmd.h"

namespace Control
{

	static CUndoOperationCmd gUndoOperationCommand;

	CUndoOperationCmd::CUndoOperationCmd() : ICommand("UndoOperationCmd")
	{

	}

	CUndoOperationCmd::~CUndoOperationCmd()
	{

	}
	void CUndoOperationCmd::Initialize(Framework::IUIObject *pTargetControl)
	{

		ICommand::Initialize(pTargetControl);

		//获取活动地图控件
		m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
		if(!m_pMapCtrl)
			return;

	}
	void CUndoOperationCmd::Click()
	{
		ICommand::Click();

		if(!m_pMapCtrl)
			return;
		//获取活动地区
		Carto::CMapPtr  m_pMap = m_pMapCtrl->GetMap();
		if(!m_pMap)
			return;

		MessageBox(0,"UNDO","UDNO",0);
		//pMap->GetElementOperationStack()->Undo();

		m_pMapCtrl->UpdateControl(drawElement | drawEdit);

		m_pMapCtrl->SetCurTool("SelectElementsTool");
	}

}