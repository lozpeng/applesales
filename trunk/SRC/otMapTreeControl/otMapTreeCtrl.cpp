// otMapTreeCtrl.cpp : CotMapTreeCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "otMapTreeControl.h"
#include "otMapTreeCtrl.h"
#include "otMapTreePpg.h"
#include "DlgAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CotMapTreeCtrl, COleControl)



// 消息映射

BEGIN_MESSAGE_MAP(CotMapTreeCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CotMapTreeCtrl, COleControl)
	DISP_FUNCTION_ID(CotMapTreeCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CotMapTreeCtrl, "SetFriendControl", dispidSetFriendControl, SetFriendControl, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(CotMapTreeCtrl, "Update", dispidUpdate, Update, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_EX_ID(CotMapTreeCtrl, "HasLine", dispidHasLine, GetHasLine, SetHasLine, VT_BOOL)
	DISP_PROPERTY_EX_ID(CotMapTreeCtrl, "ShowPopMenu", dispidShowPopMenu, GetShowPopMenu, SetShowPopMenu, VT_BOOL)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CotMapTreeCtrl, COleControl)
	EVENT_CUSTOM_ID("OnDoubleClick", eventidOnDoubleClick, FireDoubleClick, VTS_I4 VTS_I4 VTS_I4 VTS_I4 )
	EVENT_CUSTOM_ID("OnMouseDown", eventidOnMouseDown, FireMouseDown, VTS_I4 VTS_I4 VTS_I4 VTS_I4 )
	EVENT_CUSTOM_ID("OnMouseUp", eventidOnMouseUp, FireMouseUp, VTS_I4 VTS_I4 VTS_I4 VTS_I4 )
	EVENT_CUSTOM_ID("OnMouseMove", eventidOnMouseMove, FireMouseMove, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CotMapTreeCtrl, 1)
	PROPPAGEID(CotMapTreePropPage::guid)
END_PROPPAGEIDS(CotMapTreeCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CotMapTreeCtrl, "OTMAPTREECONTROL.otMapTreeCtrl.1",
	0x87a8ef82, 0x3ced, 0x4cda, 0xaf, 0xc2, 0x7e, 0x6a, 0x36, 0xfd, 0xe4, 0x90)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CotMapTreeCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID BASED_CODE IID_DotMapTreeControl =
		{ 0xF8C383A6, 0xBC41, 0x43ED, { 0x8D, 0xEA, 0x6B, 0xFE, 0xD5, 0x91, 0xB1, 0x92 } };
const IID BASED_CODE IID_DotMapTreeControlEvents =
		{ 0xA9D71CB3, 0x7908, 0x4C84, { 0xB5, 0x47, 0x1F, 0x6B, 0xA6, 0xDF, 0xEF, 0xBC } };



// 控件类型信息

static const DWORD BASED_CODE _dwotMapTreeControlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CotMapTreeCtrl, IDS_OTMAPTREECONTROL, _dwotMapTreeControlOleMisc)



// CotMapTreeCtrl::CotMapTreeCtrlFactory::UpdateRegistry -
// 添加或移除 CotMapTreeCtrl 的系统注册表项

BOOL CotMapTreeCtrl::CotMapTreeCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_OTMAPTREECONTROL,
			IDB_OTMAPTREECONTROL,
			afxRegApartmentThreading,
			_dwotMapTreeControlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


const int nBorderSize = 1;
// CotMapTreeCtrl::CotMapTreeCtrl - 构造函数

CotMapTreeCtrl::CotMapTreeCtrl()
{
	InitializeIIDs(&IID_DotMapTreeControl, &IID_DotMapTreeControlEvents);
	// TODO: 在此初始化控件的实例数据。

	m_pMapControl =NULL;

	
}



// CotMapTreeCtrl::~CotMapTreeCtrl - 析构函数

CotMapTreeCtrl::~CotMapTreeCtrl()
{
	// TODO: 在此清理控件的实例数据。
	if(m_pMapControl)
	{
		m_pMapControl->Release();
		m_pMapControl =NULL;
	}
}



// CotMapTreeCtrl::OnDraw - 绘图函数

void CotMapTreeCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。

}



// CotMapTreeCtrl::DoPropExchange - 持久性支持

void CotMapTreeCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
	PX_Bool(pPX, _T("HasLine"), m_hasLine, TRUE);

	PX_Bool(pPX, _T("ShowPopMenu"), m_wndTree.m_bShowMenu, TRUE);
}



// CotMapTreeCtrl::OnResetState - 将控件重置为默认状态

void CotMapTreeCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}



// CotMapTreeCtrl::AboutBox - 向用户显示“关于”框

void CotMapTreeCtrl::AboutBox()
{
	CDlgAbout dlgAbout;
	dlgAbout.DoModal();
}



// CotMapTreeCtrl 消息处理程序

int CotMapTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	DWORD dstyle;
	if(m_hasLine)
	{
		dstyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES |TVS_LINESATROOT| TVS_HASBUTTONS | TVS_SHOWSELALWAYS ;
	}
	else
	{
		dstyle = WS_CHILD | WS_VISIBLE |TVS_LINESATROOT| TVS_HASBUTTONS | TVS_SHOWSELALWAYS ;
	}
	
	if(!m_wndTree.Create( dstyle , CRect(0,0,0,0) , this , 1 ))
	{
		return -1;
	}

	//设置父控件
	m_wndTree.SetParentCtrl(this);

	return 0;
}

void CotMapTreeCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rectTree;
	m_wndTree.GetWindowRect (rectTree);
	ScreenToClient (rectTree);

	rectTree.InflateRect (nBorderSize, nBorderSize);
	dc.Draw3dRect (rectTree,	::GetSysColor (COLOR_3DSHADOW), 
		::GetSysColor (COLOR_3DSHADOW));
}

void CotMapTreeCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	m_wndTree.SetWindowPos (NULL, nBorderSize, nBorderSize, 
		cx - 2 * nBorderSize, cy - 2 * nBorderSize,
		SWP_NOACTIVATE | SWP_NOZORDER);
}

void CotMapTreeCtrl::SetFriendControl(IDispatch* MapControl)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(m_pMapControl)
	{
		m_pMapControl->Release();
	}
	if(MapControl!=NULL)
	{
		MapControl->QueryInterface(__uuidof(_DotMapControl),(void**)&m_pMapControl);
		if(m_pMapControl)
		{
			if(::IsWindow(m_wndTree.GetSafeHwnd()))
			{
                //初始化树
                m_wndTree.SetMapCtrl(m_pMapControl);
				m_wndTree.Refresh();

			}
		}
	}
	else
	{
		m_pMapControl =NULL;

	}
	
}

void CotMapTreeCtrl::Update(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(::IsWindow(m_wndTree.GetSafeHwnd()))
	{
		//更新树的内容
		m_wndTree.Refresh();

	}

}

VARIANT_BOOL CotMapTreeCtrl::GetHasLine()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    if(m_hasLine)
	{
		return VARIANT_TRUE;
	}
	else
	{
		return VARIANT_FALSE;
	}
}

void CotMapTreeCtrl::SetHasLine(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    if(newVal==VARIANT_FALSE)
	{
		m_wndTree.ModifyStyle(TVS_HASLINES,0);
		m_hasLine =FALSE;

		
	}
	else
	{
		m_wndTree.ModifyStyle(0,TVS_HASLINES);
		m_hasLine =TRUE;
	}
	
}

VARIANT_BOOL CotMapTreeCtrl::GetShowPopMenu()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(m_wndTree.m_bShowMenu)
	{
		return VARIANT_TRUE;
	}
	else
	{
		return VARIANT_FALSE;
	}
}

void CotMapTreeCtrl::SetShowPopMenu(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(newVal==VARIANT_FALSE)
	{
		
        m_wndTree.m_bShowMenu =FALSE;

	}
	else
	{
		m_wndTree.m_bShowMenu =TRUE;
	}

}




/************************************************************************************
* CotMapTreeCtrl的事件
*
*************************************************************************************/

void CotMapTreeCtrl::FireDoubleClick(LONG button, LONG flag, LONG X, LONG Y)
{
	FireEvent(eventidOnDoubleClick, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4 ), button, flag, X, Y);
}

void CotMapTreeCtrl::FireMouseDown(LONG button, LONG flag, LONG x, LONG y)
{
	FireEvent(eventidOnMouseDown, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4 ), button, flag, x, y);
}

void CotMapTreeCtrl::FireMouseUp(LONG button, LONG flag, LONG x, LONG y)
{
	FireEvent(eventidOnMouseUp, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4 ), button, flag, x, y);
}

void CotMapTreeCtrl::FireMouseMove(LONG button, LONG flag, LONG x, LONG y)
{
	FireEvent(eventidOnMouseMove, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4 ), button, flag, x, y);
}

void CotMapTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	//触发单击事件
	FireMouseDown(1,0,point.x,point.y);

	COleControl::OnLButtonDown(nFlags, point);
}

void CotMapTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	//触发鼠标抬起事件
	FireMouseUp(1,0,point.x,point.y);

	COleControl::OnLButtonUp(nFlags, point);
}

void CotMapTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//触发双击事件
	FireDoubleClick(1,0,point.x,point.y);

	COleControl::OnLButtonDblClk(nFlags, point);
}

void CotMapTreeCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	long button =0;
	if(nFlags&MK_LBUTTON)
	{
		button =1;
	}
	else if(nFlags & MK_RBUTTON)
	{
		button =2;
	}
	else if(nFlags & MK_MBUTTON)
	{
		button =3;
	}
	else
	{
		button =0;
	}
	//触发移动事件
	FireMouseMove(button,0,point.x,point.y);

	COleControl::OnMouseMove(nFlags, point);
}

void CotMapTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	//触发单击事件
	FireMouseDown(2,0,point.x,point.y);

	COleControl::OnRButtonDown(nFlags, point);
}

void CotMapTreeCtrl::OnRButtonUp(UINT nFlags, CPoint point)
{
	//触发鼠标抬起事件
	FireMouseUp(2,0,point.x,point.y);

	COleControl::OnRButtonUp(nFlags, point);
}
