// usLayoutControlPropPage.cpp : CusLayoutControlPropPage 属性页类的实现。

#include "stdafx.h"
#include "usLayoutControl.h"
#include "usLayoutControlPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CusLayoutControlPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CusLayoutControlPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CusLayoutControlPropPage, "USLAYOUTCONTRO.usLayoutControPropPage.1",
	0x4665a085, 0xe42c, 0x4e84, 0x9c, 0xc0, 0x97, 0x18, 0x75, 0xe0, 0xe6, 0xe6)



// CusLayoutControlPropPage::CusLayoutControlPropPageFactory::UpdateRegistry -
// 添加或移除 CusLayoutControlPropPage 的系统注册表项

BOOL CusLayoutControlPropPage::CusLayoutControlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_USLAYOUTCONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CusLayoutControlPropPage::CusLayoutControlPropPage - 构造函数

CusLayoutControlPropPage::CusLayoutControlPropPage() :
	COlePropertyPage(IDD, IDS_USLAYOUTCONTROL_PPG_CAPTION)
{
}



// CusLayoutControlPropPage::DoDataExchange - 在页和属性间移动数据

void CusLayoutControlPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CusLayoutControlPropPage 消息处理程序
