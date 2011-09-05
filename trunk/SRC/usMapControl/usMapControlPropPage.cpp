// usMapControlPropPage.cpp : CusMapControlPropPage 属性页类的实现。

#include "stdafx.h"
#include "usMapControl.h"
#include "usMapControlPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CusMapControlPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CusMapControlPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CusMapControlPropPage, "USMAPCONTROL.usMapControlPropPage.1",
	0x54b73994, 0xc506, 0x4891, 0x89, 0x48, 0x82, 0x34, 0x1d, 0xf, 0x82, 0x45)



// CusMapControlPropPage::CusMapControlPropPageFactory::UpdateRegistry -
// 添加或移除 CusMapControlPropPage 的系统注册表项

BOOL CusMapControlPropPage::CusMapControlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_USMAPCONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CusMapControlPropPage::CusMapControlPropPage - 构造函数

CusMapControlPropPage::CusMapControlPropPage() :
	COlePropertyPage(IDD, IDS_USMAPCONTROL_PPG_CAPTION)
{
}



// CusMapControlPropPage::DoDataExchange - 在页和属性间移动数据

void CusMapControlPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CusMapControlPropPage 消息处理程序
