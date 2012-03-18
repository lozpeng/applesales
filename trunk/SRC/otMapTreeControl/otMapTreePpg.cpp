// otMapTreePpg.cpp : CotMapTreePropPage 属性页类的实现。

#include "stdafx.h"
#include "otMapTreeControl.h"
#include "otMapTreePpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CotMapTreePropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CotMapTreePropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CotMapTreePropPage, "OTMAPTREECONTR.otMapTreePropPage.1",
	0x363cc662, 0xbfba, 0x473f, 0xb5, 0x74, 0x75, 0x6c, 0x51, 0xf8, 0xd6, 0xd1)



// CotMapTreePropPage::CotMapTreePropPageFactory::UpdateRegistry -
// 添加或移除 CotMapTreePropPage 的系统注册表项

BOOL CotMapTreePropPage::CotMapTreePropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_OTMAPTREECONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CotMapTreePropPage::CotMapTreePropPage - 构造函数

CotMapTreePropPage::CotMapTreePropPage() :
	COlePropertyPage(IDD, IDS_OTMAPTREECONTROL_PPG_CAPTION)
{
}



// CotMapTreePropPage::DoDataExchange - 在页和属性间移动数据

void CotMapTreePropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CotMapTreePropPage 消息处理程序
