// otMapTreePpg.cpp : CotMapTreePropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "otMapTreeControl.h"
#include "otMapTreePpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CotMapTreePropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CotMapTreePropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CotMapTreePropPage, "OTMAPTREECONTR.otMapTreePropPage.1",
	0x363cc662, 0xbfba, 0x473f, 0xb5, 0x74, 0x75, 0x6c, 0x51, 0xf8, 0xd6, 0xd1)



// CotMapTreePropPage::CotMapTreePropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CotMapTreePropPage ��ϵͳע�����

BOOL CotMapTreePropPage::CotMapTreePropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_OTMAPTREECONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CotMapTreePropPage::CotMapTreePropPage - ���캯��

CotMapTreePropPage::CotMapTreePropPage() :
	COlePropertyPage(IDD, IDS_OTMAPTREECONTROL_PPG_CAPTION)
{
}



// CotMapTreePropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CotMapTreePropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CotMapTreePropPage ��Ϣ�������
