// usLayoutControlPropPage.cpp : CusLayoutControlPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "usLayoutControl.h"
#include "usLayoutControlPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CusLayoutControlPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CusLayoutControlPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CusLayoutControlPropPage, "USLAYOUTCONTRO.usLayoutControPropPage.1",
	0x4665a085, 0xe42c, 0x4e84, 0x9c, 0xc0, 0x97, 0x18, 0x75, 0xe0, 0xe6, 0xe6)



// CusLayoutControlPropPage::CusLayoutControlPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CusLayoutControlPropPage ��ϵͳע�����

BOOL CusLayoutControlPropPage::CusLayoutControlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_USLAYOUTCONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CusLayoutControlPropPage::CusLayoutControlPropPage - ���캯��

CusLayoutControlPropPage::CusLayoutControlPropPage() :
	COlePropertyPage(IDD, IDS_USLAYOUTCONTROL_PPG_CAPTION)
{
}



// CusLayoutControlPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CusLayoutControlPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CusLayoutControlPropPage ��Ϣ�������
