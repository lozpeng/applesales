// usLayoutControlCtrl.cpp : CusLayoutCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "usLayoutControl.h"
#include "usLayoutControlCtrl.h"
#include "usLayoutControlPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CusLayoutCtrl, COleControl)



// 消息映射

BEGIN_MESSAGE_MAP(CusLayoutCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CusLayoutCtrl, COleControl)
	DISP_FUNCTION_ID(CusLayoutCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CusLayoutCtrl, COleControl)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CusLayoutCtrl, 1)
	PROPPAGEID(CusLayoutControlPropPage::guid)
END_PROPPAGEIDS(CusLayoutCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CusLayoutCtrl, "USLAYOUTCONTROL.usLayoutControlCtrl.1",
	0x6729de6c, 0xb113, 0x441e, 0x9c, 0xc1, 0xc6, 0x76, 0xa, 0xa5, 0x1, 0xe6)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CusLayoutCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID BASED_CODE IID_DusLayoutControl =
		{ 0x2A2508B5, 0xE59A, 0x40B5, { 0x8C, 0x23, 0x90, 0x9C, 0x2F, 0x8F, 0x65, 0xAF } };
const IID BASED_CODE IID_DusLayoutControlEvents =
		{ 0x5EF20983, 0x2A99, 0x49E8, { 0xB5, 0xC7, 0xF7, 0xDE, 0xCF, 0xD1, 0x78, 0x1A } };



// 控件类型信息

static const DWORD BASED_CODE _dwusLayoutControlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CusLayoutCtrl, IDS_USLAYOUTCONTROL, _dwusLayoutControlOleMisc)



// CusLayoutCtrl::CusLayoutCtrlFactory::UpdateRegistry -
// 添加或移除 CusLayoutCtrl 的系统注册表项

BOOL CusLayoutCtrl::CusLayoutCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_USLAYOUTCONTROL,
			IDB_USLAYOUTCONTROL,
			afxRegApartmentThreading,
			_dwusLayoutControlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CusLayoutCtrl::CusLayoutCtrl - 构造函数

CusLayoutCtrl::CusLayoutCtrl()
{
	InitializeIIDs(&IID_DusLayoutControl, &IID_DusLayoutControlEvents);
	// TODO: 在此初始化控件的实例数据。
}



// CusLayoutCtrl::~CusLayoutCtrl - 析构函数

CusLayoutCtrl::~CusLayoutCtrl()
{
	// TODO: 在此清理控件的实例数据。
}



// CusLayoutCtrl::OnDraw - 绘图函数

void CusLayoutCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// CusLayoutCtrl::DoPropExchange - 持久性支持

void CusLayoutCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}



// CusLayoutCtrl::OnResetState - 将控件重置为默认状态

void CusLayoutCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}



// CusLayoutCtrl::AboutBox - 向用户显示“关于”框

void CusLayoutCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_USLAYOUTCONTROL);
	dlgAbout.DoModal();
}



// CusLayoutCtrl 消息处理程序
