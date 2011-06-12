#include "stdafx.h"
#include "FeatureAtrEditCommand.h"
#include "DlgFeatureAttriEdit.h"
#include "IMapCtrl.h"
#include "CEditor.h"
#include "DllResource.h"
#include "FeatureLayer.h"
#include "IWorkspace.h"

namespace Editor
{
	static CFeatureAtrEditCommand gFeatureAtrEditCommand;

	CFeatureAtrEditCommand::CFeatureAtrEditCommand(void) : ICommand("FeatureAtrEditCmd")
	{

	}

	CFeatureAtrEditCommand::~CFeatureAtrEditCommand(void)
	{

	}
	//初始化
	void CFeatureAtrEditCommand::Initialize(Framework::IUIObject *pTargetControl)
	{
		ICommand::Initialize(pTargetControl);
	}
	void CFeatureAtrEditCommand::Click()
	{
		//获取活动地图控件
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return ;

		//获取活动地区
		Carto::CMapPtr pMap = pMapCtrl->GetMap();
		if(!pMap)
			return ;

		Editor::CEditorPtr pEdit =pMap->GetEditor();
		if(!pEdit)
		{
			return ;
		}
		if(!pEdit->IsEditing())
		{
			return;
		}

		CDllResource dllRes;
		std::vector<Carto::ILayer*> alllayers;


		Carto::CLayerArray &layers =pMap->GetLayers();
		int num =layers.GetSize();
		Carto::IFeatureLayerPtr pLayer;
		Geodatabase::IFeatureClass *pFeatureClass =NULL;
		Geodatabase::IWorkspace *pWorkspace =NULL;


		//对地图中的矢量层设置编辑状态
		for(int i=0;i<num;i++)
		{
			pLayer =layers.GetAt(i);
			if(!pLayer)
			{
				continue;
			}

			pFeatureClass =dynamic_cast<Geodatabase::IFeatureClass*>(pLayer->GetDataObject().get());
			if(!pFeatureClass)
			{
				continue;
			}

			pWorkspace =pFeatureClass->GetWorkspace();
			if(!pLayer->GetSelection())
			{
				continue;
			}
			alllayers.push_back(pLayer.get());

		}

		CDlgFeatureAttriEdit dlg;
		dlg.SetFeatures(alllayers,pEdit.get());
		dlg.DoModal();


	}

	
}