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


	//��ȡ���ͼ�ؼ�
	m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);

}
void CLayoutZoomFullExtentCmd::Click()
{
	ICommand::Click();

	//��ȡ���ͼ�ؼ�
	if(!m_pLayoutCtrl)
		return;

	//��ȡ�����
	Carto::CPageLayoutPtr pPageLayout = m_pLayoutCtrl->GetPageLayout();
	if(!pPageLayout)
		return;

	pPageLayout->GetDisplay()->GetDisplayTransformation().FitViewBound(pPageLayout->GetExtent());

	m_pLayoutCtrl->UpdateControl();
}

}