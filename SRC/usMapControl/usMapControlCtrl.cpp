// usMapControlCtrl.cpp : CusMapCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "usMapControl.h"
#include "usMapControlCtrl.h"
#include "usMapControlPropPage.h"
#include "ShapefileWorkspaceFactory.h"
#include "ShapefileWorkspace.h"
#include "ShapefileFeatureClass.h"
#include "FeatureLayer.h"
#include "RasterLayer.h"
#include "RasterWSFactory.h"
#include "ActivexLoad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CusMapCtrl, COleControl)



// 消息映射

BEGIN_MESSAGE_MAP(CusMapCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CusMapCtrl, COleControl)
	DISP_FUNCTION_ID(CusMapCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CusMapCtrl, "AddShpfile", dispidAddShpfile, AddShpfile, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CusMapCtrl, "Refresh", dispidRefresh, Refresh, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_EX_ID(CusMapCtrl, "CurTool", dispidCurTool, GetCurTool, SetCurTool, VT_I2)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CusMapCtrl, COleControl)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CusMapCtrl, 1)
	PROPPAGEID(CusMapControlPropPage::guid)
END_PROPPAGEIDS(CusMapCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CusMapCtrl, "USMAPCONTROL.usMapControlCtrl.1",
	0xa9e92766, 0xea71, 0x429d, 0xb2, 0x33, 0x80, 0xbc, 0x20, 0xf9, 0xd6, 0x7b)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CusMapCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID BASED_CODE IID_DusMapControl =
		{ 0x68B41220, 0xC2AB, 0x44BE, { 0xAC, 0xB7, 0x9D, 0x72, 0x11, 0x13, 0x5B, 0x56 } };
const IID BASED_CODE IID_DusMapControlEvents =
		{ 0xC1D0682, 0x3FE2, 0x4567, { 0xB4, 0x81, 0x98, 0x2D, 0x6C, 0x49, 0xED, 0x63 } };



// 控件类型信息

static const DWORD BASED_CODE _dwusMapControlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CusMapCtrl, IDS_USMAPCONTROL, _dwusMapControlOleMisc)



// CusMapCtrl::CusMapCtrlFactory::UpdateRegistry -
// 添加或移除 CusMapCtrl 的系统注册表项

BOOL CusMapCtrl::CusMapCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_USMAPCONTROL,
			IDB_USMAPCONTROL,
			afxRegApartmentThreading,
			_dwusMapControlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CusMapCtrl::CusMapCtrl - 构造函数

CusMapCtrl::CusMapCtrl()
{
	InitializeIIDs(&IID_DusMapControl, &IID_DusMapControlEvents);
	// TODO: 在此初始化控件的实例数据。
	CreateAss("USMAPCONTROL");

	SetAutoDetroy(true);

	m_bActiveX =true;

	m_pCurTool =NULL;

	m_Tooltype =NoneTool;
}



// CusMapCtrl::~CusMapCtrl - 析构函数

CusMapCtrl::~CusMapCtrl()
{
	// TODO: 在此清理控件的实例数据。
}



// CusMapCtrl::OnDraw - 绘图函数

void CusMapCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	
}



// CusMapCtrl::DoPropExchange - 持久性支持

void CusMapCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}



// CusMapCtrl::OnResetState - 将控件重置为默认状态

void CusMapCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}



// CusMapCtrl::AboutBox - 向用户显示“关于”框

void CusMapCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_USMAPCONTROL);
	dlgAbout.DoModal();
}



// CusMapCtrl 消息处理程序



int CusMapCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	//内部地图控件创建
	m_hClientDC = ::GetDC(this->GetSafeHwnd());
	m_hMemDC = ::CreateCompatibleDC(m_hClientDC);

	m_hCtrlWnd = this->GetSafeHwnd();

	//创建一个新地图
	Carto::CMapPtr ptrMap = new Carto::CMap();


	ptrMap->SetName("Map--1");

	Framework::IMapCtrl::SetMap(ptrMap);

	//为了能够加载Control库，所以调用一个没有作用的类
	Control::CActivexLoad cLoad;

	return 0;
}

void CusMapCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 COleControl::OnPaint()

	CRect rect;
	GetClientRect(rect);
	Carto::CMapPtr pGeoMap =GetMap();
	if(pGeoMap)
	{

		::BitBlt(GetClientDC(),0,0,rect.Width(),rect.Height(),GetMemDC(),0,0,SRCCOPY);
	}
	else
	{
		//绘制背景
		HBRUSH hbrush = ::CreateSolidBrush( RGB(255,255,255));

		::FillRect(GetClientDC() , &rect , hbrush );

		::DeleteObject( hbrush );
	}

}

void CusMapCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	ControlResize(nType,cx,cy);
}

void CusMapCtrl::AddShpfile(LPCTSTR filename)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	_bstr_t  csDataSourceTmp =filename;

	CString csThemeName =csDataSourceTmp;

	csThemeName = csThemeName.Mid (csThemeName.ReverseFind ('\\') + 1);
	csThemeName =csThemeName.Left(csThemeName.ReverseFind('.'));

	Geodatabase::IWorkspace *pWorkspace =CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(csDataSourceTmp);

	if(!pWorkspace)
	{
		MessageBox(_T("打开数据失败！"),_T("提示"),MB_OK);
		return ;
	}
	Geodatabase::IFeatureClassPtr pFeatureClass =pWorkspace->OpenFeatureClass(csDataSourceTmp);

	if(!pFeatureClass)
	{
		MessageBox(_T("打开数据失败！"),_T("提示"),MB_OK);
		return ;
	}

	Carto::CMapPtr pGeoMap =GetMap();
	if(pGeoMap->AddNewLayer(pFeatureClass))
	{
		Carto::CLayerArray &layers =pGeoMap->GetLayers();
		Carto::ILayerPtr pLayer =layers.GetAt(layers.GetSize()-1);
		//设置图层名称
		pLayer->SetName(std::string(_bstr_t(csThemeName)));
	}


	Refresh();
}

void CusMapCtrl::Refresh(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	UpdateControl(drawAll);
}

void CusMapCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(m_pCurTool)
	{
		m_pCurTool->LButtonDblClkEvent(nFlags,point);
	}
	__super::OnLButtonDblClk(nFlags, point);
}

void CusMapCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_pCurTool)
	{
		m_pCurTool->LButtonDownEvent(nFlags,point);
	}

	__super::OnLButtonDown(nFlags, point);
}

void CusMapCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_pCurTool)
	{
		m_pCurTool->LButtonUpEvent(nFlags,point);
	}

	__super::OnLButtonUp(nFlags, point);
}

void CusMapCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_pCurTool)
	{
		m_pCurTool->MouseMoveEvent(nFlags,point);
	}

	__super::OnMouseMove(nFlags, point);
}

BOOL CusMapCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return __super::OnMouseWheel(nFlags, zDelta, pt);
}

void CusMapCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	if(m_pCurTool)
	{
		m_pCurTool->RButtonDownEvent(nFlags,point);
	}

	__super::OnRButtonDown(nFlags, point);
}

void CusMapCtrl::OnRButtonUp(UINT nFlags, CPoint point)
{
	
	__super::OnRButtonUp(nFlags, point);
}

void CusMapCtrl::OnTimer(UINT_PTR nIDEvent)
{
	

	__super::OnTimer(nIDEvent);
}

usToolType CusMapCtrl::GetCurTool(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	

	return m_Tooltype;
}

void CusMapCtrl::SetCurTool(usToolType newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_Tooltype =newVal;

	m_pCurTool =GetTool(newVal);

	if(m_pCurTool)
	{
		m_pCurTool->Initialize(dynamic_cast<Framework::IUIObject*>(this));
	}

	SetModifiedFlag();
}

Framework::ITool* CusMapCtrl::GetTool(usToolType tooltype)
{
	if(NoneTool==tooltype)
	{
		return NULL;
	}

	Framework::ITool *pTool =NULL;
	switch(tooltype)
	{
	case PanTool:
		pTool =Framework::ITool::CreateTool("MapPan");
		break;
	case ZoomInTool:
		pTool =Framework::ITool::CreateTool("MapZoomin");
		break;
	case ZoomOutTool:
		pTool =Framework::ITool::CreateTool("MapZoomout");
		break;
	default:
		break;

	}

	return pTool;
}