#include "stdafx.h"
#include "LayoutZoomActualSize.h"
#include "ILayoutCtrl.h"

namespace Control
{

static CLayoutZoomActualSizeCmd gLayoutZoomActualSize;

CLayoutZoomActualSizeCmd::CLayoutZoomActualSizeCmd() : ICommand("LayoutZoomActualSize")
{
}

CLayoutZoomActualSizeCmd::~CLayoutZoomActualSizeCmd()
{

}
void CLayoutZoomActualSizeCmd::Initialize(Framework::IUIObject *pTargetControl)
{
	ICommand::Initialize(pTargetControl);


	//��ȡ���ͼ�ؼ�
	m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);

}
void CLayoutZoomActualSizeCmd::Click()
{
	ICommand::Click();

	//��ȡ���ͼ�ؼ�
	if(!m_pLayoutCtrl)
		return;

	//��ȡ�����
	Carto::CPageLayoutPtr pPageLayout = m_pLayoutCtrl->GetPageLayout();
	if(!pPageLayout)
		return;

//	pPageLayout->GetDisplay()->GetDisplayTransformation().FitViewBound(pPageLayout->GetExtent());

	pPageLayout->GetDisplay()->GetDisplayTransformation().SetMapScale(1);

	m_pLayoutCtrl->UpdateControl();
}

}