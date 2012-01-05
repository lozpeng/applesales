#include "stdafx.h"
#include "LayoutZoomFullExtent.h"
#include "ILayoutCtrl.h"

namespace Control
{

static CLayoutZoomFullExtentCmd gLayoutZoomFullExtent;

CLayoutZoomFullExtentCmd::CLayoutZoomFullExtentCmd() : ICommand("LayoutZoomFullExtent")
{
	
}

CLayoutZoomFullExtentCmd::~CLayoutZoomFullExtentCmd()
{

}
void CLayoutZoomFullExtentCmd::Initialize(Framework::IUIObject *pTargetControl)
{
	ICommand::Initialize(pTargetControl);


	//获取活动地图控件
	m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);

}
void CLayoutZoomFullExtentCmd::Click()
{
	ICommand::Click();

	//获取活动制图控件
	if(!m_pLayoutCtrl)
		return;

	//获取活动地区
	Carto::CPageLayoutPtr pPageLayout = m_pLayoutCtrl->GetPageLayout();
	if(!pPageLayout)
		return;

	pPageLayout->GetDisplay()->GetDisplayTransformation().FitViewBound(pPageLayout->GetExtent());

	m_pLayoutCtrl->UpdateControl();
}

}