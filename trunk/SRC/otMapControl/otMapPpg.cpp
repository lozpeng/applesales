// otMapPpg.cpp : CotMapPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "otMapControl.h"
#include "otMapPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CotMapPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CotMapPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CotMapPropPage, "OTMAPCONTROL.otMapPropPage.1",
	0x78b2db90, 0xa518, 0x4cdf, 0x91, 0xdf, 0x7a, 0x83, 0xd, 0x1b, 0x1f, 0x5d)



// CotMapPropPage::CotMapPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CotMapPropPage ��ϵͳע�����

BOOL CotMapPropPage::CotMapPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_OTMAPCONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CotMapPropPage::CotMapPropPage - ���캯��

CotMapPropPage::CotMapPropPage() :
	COlePropertyPage(IDD, IDS_OTMAPCONTROL_PPG_CAPTION)
{
}



// CotMapPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CotMapPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CotMapPropPage ��Ϣ�������
