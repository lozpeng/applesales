// usMapControlCtrl.cpp : CusMapCtrl ActiveX �ؼ����ʵ�֡�

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



// ��Ϣӳ��

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



// ����ӳ��

BEGIN_DISPATCH_MAP(CusMapCtrl, COleControl)
	DISP_FUNCTION_ID(CusMapCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CusMapCtrl, "AddShpfile", dispidAddShpfile, AddShpfile, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CusMapCtrl, "Refresh", dispidRefresh, Refresh, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_EX_ID(CusMapCtrl, "CurTool", dispidCurTool, GetCurTool, SetCurTool, VT_I2)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CusMapCtrl, COleControl)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CusMapCtrl, 1)
	PROPPAGEID(CusMapControlPropPage::guid)
END_PROPPAGEIDS(CusMapCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CusMapCtrl, "USMAPCONTROL.usMapControlCtrl.1",
	0xa9e92766, 0xea71, 0x429d, 0xb2, 0x33, 0x80, 0xbc, 0x20, 0xf9, 0xd6, 0x7b)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CusMapCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID BASED_CODE IID_DusMapControl =
		{ 0x68B41220, 0xC2AB, 0x44BE, { 0xAC, 0xB7, 0x9D, 0x72, 0x11, 0x13, 0x5B, 0x56 } };
const IID BASED_CODE IID_DusMapControlEvents =
		{ 0xC1D0682, 0x3FE2, 0x4567, { 0xB4, 0x81, 0x98, 0x2D, 0x6C, 0x49, 0xED, 0x63 } };



// �ؼ�������Ϣ

static const DWORD BASED_CODE _dwusMapControlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CusMapCtrl, IDS_USMAPCONTROL, _dwusMapControlOleMisc)



// CusMapCtrl::CusMapCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CusMapCtrl ��ϵͳע�����

BOOL CusMapCtrl::CusMapCtrlFactory::UpdateRegistry(BOOL bRegister)
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



// CusMapCtrl::CusMapCtrl - ���캯��

CusMapCtrl::CusMapCtrl()
{
	InitializeIIDs(&IID_DusMapControl, &IID_DusMapControlEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
	CreateAss("USMAPCONTROL");

	SetAutoDetroy(true);

	m_bActiveX =true;

	m_pCurTool =NULL;

	m_Tooltype =NoneTool;
}



// CusMapCtrl::~CusMapCtrl - ��������

CusMapCtrl::~CusMapCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
}



// CusMapCtrl::OnDraw - ��ͼ����

void CusMapCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	
}



// CusMapCtrl::DoPropExchange - �־���֧��

void CusMapCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}



// CusMapCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CusMapCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CusMapCtrl::AboutBox - ���û���ʾ�����ڡ���

void CusMapCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_USMAPCONTROL);
	dlgAbout.DoModal();
}



// CusMapCtrl ��Ϣ�������



int CusMapCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	//�ڲ���ͼ�ؼ�����
	m_hClientDC = ::GetDC(this->GetSafeHwnd());
	m_hMemDC = ::CreateCompatibleDC(m_hClientDC);

	m_hCtrlWnd = this->GetSafeHwnd();

	//����һ���µ�ͼ
	Carto::CMapPtr ptrMap = new Carto::CMap();


	ptrMap->SetName("Map--1");

	Framework::IMapCtrl::SetMap(ptrMap);

	//Ϊ���ܹ�����Control�⣬���Ե���һ��û�����õ���
	Control::CActivexLoad cLoad;

	return 0;
}

void CusMapCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� COleControl::OnPaint()

	CRect rect;
	GetClientRect(rect);
	Carto::CMapPtr pGeoMap =GetMap();
	if(pGeoMap)
	{

		::BitBlt(GetClientDC(),0,0,rect.Width(),rect.Height(),GetMemDC(),0,0,SRCCOPY);
	}
	else
	{
		//���Ʊ���
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
		MessageBox(_T("������ʧ�ܣ�"),_T("��ʾ"),MB_OK);
		return ;
	}
	Geodatabase::IFeatureClassPtr pFeatureClass =pWorkspace->OpenFeatureClass(csDataSourceTmp);

	if(!pFeatureClass)
	{
		MessageBox(_T("������ʧ�ܣ�"),_T("��ʾ"),MB_OK);
		return ;
	}

	Carto::CMapPtr pGeoMap =GetMap();
	if(pGeoMap->AddNewLayer(pFeatureClass))
	{
		Carto::CLayerArray &layers =pGeoMap->GetLayers();
		Carto::ILayerPtr pLayer =layers.GetAt(layers.GetSize()-1);
		//����ͼ������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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