// otMapTreeCtrl.cpp : CotMapTreeCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "otMapTreeControl.h"
#include "otMapTreeCtrl.h"
#include "otMapTreePpg.h"
#include "DlgAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CotMapTreeCtrl, COleControl)



// ��Ϣӳ��

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



// ����ӳ��

BEGIN_DISPATCH_MAP(CotMapTreeCtrl, COleControl)
	DISP_FUNCTION_ID(CotMapTreeCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CotMapTreeCtrl, "SetFriendControl", dispidSetFriendControl, SetFriendControl, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(CotMapTreeCtrl, "Update", dispidUpdate, Update, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_EX_ID(CotMapTreeCtrl, "HasLine", dispidHasLine, GetHasLine, SetHasLine, VT_BOOL)
	DISP_PROPERTY_EX_ID(CotMapTreeCtrl, "ShowPopMenu", dispidShowPopMenu, GetShowPopMenu, SetShowPopMenu, VT_BOOL)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CotMapTreeCtrl, COleControl)
	EVENT_CUSTOM_ID("OnDoubleClick", eventidOnDoubleClick, FireDoubleClick, VTS_I4 VTS_I4 VTS_I4 VTS_I4 )
	EVENT_CUSTOM_ID("OnMouseDown", eventidOnMouseDown, FireMouseDown, VTS_I4 VTS_I4 VTS_I4 VTS_I4 )
	EVENT_CUSTOM_ID("OnMouseUp", eventidOnMouseUp, FireMouseUp, VTS_I4 VTS_I4 VTS_I4 VTS_I4 )
	EVENT_CUSTOM_ID("OnMouseMove", eventidOnMouseMove, FireMouseMove, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CotMapTreeCtrl, 1)
	PROPPAGEID(CotMapTreePropPage::guid)
END_PROPPAGEIDS(CotMapTreeCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CotMapTreeCtrl, "OTMAPTREECONTROL.otMapTreeCtrl.1",
	0x87a8ef82, 0x3ced, 0x4cda, 0xaf, 0xc2, 0x7e, 0x6a, 0x36, 0xfd, 0xe4, 0x90)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CotMapTreeCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID BASED_CODE IID_DotMapTreeControl =
		{ 0xF8C383A6, 0xBC41, 0x43ED, { 0x8D, 0xEA, 0x6B, 0xFE, 0xD5, 0x91, 0xB1, 0x92 } };
const IID BASED_CODE IID_DotMapTreeControlEvents =
		{ 0xA9D71CB3, 0x7908, 0x4C84, { 0xB5, 0x47, 0x1F, 0x6B, 0xA6, 0xDF, 0xEF, 0xBC } };



// �ؼ�������Ϣ

static const DWORD BASED_CODE _dwotMapTreeControlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CotMapTreeCtrl, IDS_OTMAPTREECONTROL, _dwotMapTreeControlOleMisc)



// CotMapTreeCtrl::CotMapTreeCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CotMapTreeCtrl ��ϵͳע�����

BOOL CotMapTreeCtrl::CotMapTreeCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

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
// CotMapTreeCtrl::CotMapTreeCtrl - ���캯��

CotMapTreeCtrl::CotMapTreeCtrl()
{
	InitializeIIDs(&IID_DotMapTreeControl, &IID_DotMapTreeControlEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�

	m_pMapControl =NULL;

	
}



// CotMapTreeCtrl::~CotMapTreeCtrl - ��������

CotMapTreeCtrl::~CotMapTreeCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
	if(m_pMapControl)
	{
		m_pMapControl->Release();
		m_pMapControl =NULL;
	}
}



// CotMapTreeCtrl::OnDraw - ��ͼ����

void CotMapTreeCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣

}



// CotMapTreeCtrl::DoPropExchange - �־���֧��

void CotMapTreeCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
	PX_Bool(pPX, _T("HasLine"), m_hasLine, TRUE);

	PX_Bool(pPX, _T("ShowPopMenu"), m_wndTree.m_bShowMenu, TRUE);
}



// CotMapTreeCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CotMapTreeCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CotMapTreeCtrl::AboutBox - ���û���ʾ�����ڡ���

void CotMapTreeCtrl::AboutBox()
{
	CDlgAbout dlgAbout;
	dlgAbout.DoModal();
}



// CotMapTreeCtrl ��Ϣ�������

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

	//���ø��ؼ�
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
                //��ʼ����
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
		//������������
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
* CotMapTreeCtrl���¼�
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
	//���������¼�
	FireMouseDown(1,0,point.x,point.y);

	COleControl::OnLButtonDown(nFlags, point);
}

void CotMapTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	//�������̧���¼�
	FireMouseUp(1,0,point.x,point.y);

	COleControl::OnLButtonUp(nFlags, point);
}

void CotMapTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//����˫���¼�
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
	//�����ƶ��¼�
	FireMouseMove(button,0,point.x,point.y);

	COleControl::OnMouseMove(nFlags, point);
}

void CotMapTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	//���������¼�
	FireMouseDown(2,0,point.x,point.y);

	COleControl::OnRButtonDown(nFlags, point);
}

void CotMapTreeCtrl::OnRButtonUp(UINT nFlags, CPoint point)
{
	//�������̧���¼�
	FireMouseUp(2,0,point.x,point.y);

	COleControl::OnRButtonUp(nFlags, point);
}
