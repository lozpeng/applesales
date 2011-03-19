#include "StdAfx.h"
#include "FlickCmd.h"
#include "DllResource.h"
#include "TransparentDLG.h"

namespace Control
{

static CFlickCmd gActionAlternate;

CFlickCmd::CFlickCmd(void):Framework::ICommand("Flick")
{
}
CFlickCmd::~CFlickCmd(void)
{
}

void CFlickCmd::Click()
{
	Control::CDllResource dll;

	//获取活动地图控件
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//获取活动地区
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;

	Carto::ILayerPtr pActiveLayer = pMap->GetActiveLayer();
	if(!pActiveLayer)
		return;

	//设置光标类型
	CTransparentDLG *TransparentDlg=new CTransparentDLG(CTransparentDLG::EHC_ALTERNATE);
	if (TransparentDlg!=NULL)
	{
		TransparentDlg->SetMapCtrl(pMapCtrl);
		TransparentDlg->SetLayer(pActiveLayer);
		TransparentDlg->DoModal();
	}
}

}


