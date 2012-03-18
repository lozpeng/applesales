// otSymbolSelector.cpp : 实现文件
//

#include "stdafx.h"
#include "otMapControl.h"
#include "otSymbolSelector.h"
#include "CotSymbolList.h"

// CotSymbolSelector

IMPLEMENT_DYNCREATE(CotSymbolSelector, CCmdTarget)


CotSymbolSelector::CotSymbolSelector()
{
	EnableAutomation();
	
	// 为了使应用程序在 OLE 自动化对象处于活动状态时保持
	//	运行，构造函数调用 AfxOleLockApp。
	
	AfxOleLockApp();
}

CotSymbolSelector::~CotSymbolSelector()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	// 	析构函数调用 AfxOleUnlockApp。
	
	AfxOleUnlockApp();
}


void CotSymbolSelector::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清除代码。

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CotSymbolSelector, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CotSymbolSelector, CCmdTarget)
	DISP_FUNCTION_ID(CotSymbolSelector, "SelectSymbol", dispidSelectSymbol, SelectSymbol, VT_UNKNOWN, VTS_UNKNOWN)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IotSymbolSelector 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {1E5E4427-9C21-4DD0-867E-BAC51C6DAD63}
static const IID IID_IotSymbolSelector =
{ 0x1E5E4427, 0x9C21, 0x4DD0, { 0x86, 0x7E, 0xBA, 0xC5, 0x1C, 0x6D, 0xAD, 0x63 } };

BEGIN_INTERFACE_MAP(CotSymbolSelector, CCmdTarget)
	INTERFACE_PART(CotSymbolSelector, IID_IotSymbolSelector, Dispatch)
END_INTERFACE_MAP()

// {61F0A120-2A95-442F-B541-4B3C309ECAF0}
IMPLEMENT_OLECREATE_FLAGS(CotSymbolSelector, "otMapControl.otSymbolSelector", afxRegApartmentThreading, 0x61f0a120, 0x2a95, 0x442f, 0xb5, 0x41, 0x4b, 0x3c, 0x30, 0x9e, 0xca, 0xf0)


// CotSymbolSelector 消息处理程序

IotSymbol* CotSymbolSelector::SelectSymbol(IotSymbol* symbol)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!symbol)
	{
		return NULL;
	}

	IOriginDataPtr pData;
	symbol->QueryInterface(__uuidof(IOriginData),(void**)&pData);

	long ldata;

	pData->get_OriginData(&ldata);

	Display::ISymbolPtr pSymbol =*((Display::ISymbolPtr*)ldata);

	otComUI::CotSymbolList symbollist;

	pSymbol = symbollist.SelectSymbol(pSymbol);

	if(!pSymbol)
	{
		return NULL;
	}

	Display::ISymbolPtr *ppSymbol =new Display::ISymbolPtr(pSymbol);

	IotSymbol *pretSymbol =NULL;


	IotSymbolConvertPtr pCon;

	CoCreateInstance(CLSID_otSymbolConvert,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotSymbolConvert),(void**)&pCon);

	pCon->ConvertSymbol(long(ppSymbol),VARIANT_TRUE,&pretSymbol);

	return NULL;
}
