// usMapControlPropPage.cpp : CusMapControlPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "usMapControl.h"
#include "usMapControlPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CusMapControlPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CusMapControlPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CusMapControlPropPage, "USMAPCONTROL.usMapControlPropPage.1",
	0x54b73994, 0xc506, 0x4891, 0x89, 0x48, 0x82, 0x34, 0x1d, 0xf, 0x82, 0x45)



// CusMapControlPropPage::CusMapControlPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CusMapControlPropPage ��ϵͳע�����

BOOL CusMapControlPropPage::CusMapControlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_USMAPCONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CusMapControlPropPage::CusMapControlPropPage - ���캯��

CusMapControlPropPage::CusMapControlPropPage() :
	COlePropertyPage(IDD, IDS_USMAPCONTROL_PPG_CAPTION)
{
}



// CusMapControlPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CusMapControlPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CusMapControlPropPage ��Ϣ�������
