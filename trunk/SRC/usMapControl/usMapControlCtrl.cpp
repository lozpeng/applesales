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
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CusMapCtrl, COleControl)
	DISP_FUNCTION_ID(CusMapCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CusMapCtrl, "AddShpfile", dispidAddShpfile, AddShpfile, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CusMapCtrl, "Refresh", dispidRefresh, Refresh, VT_EMPTY, VTS_NONE)
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
	m_MapControl.CreateAss("USMAPCONTROL");

	m_MapControl.SetAutoDetroy(true);
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
	m_MapControl.Create(this);

	return 0;
}

void CusMapCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� COleControl::OnPaint()

	CRect rect;
	GetClientRect(rect);
	Carto::CMapPtr pGeoMap =m_MapControl.GetMap();
	if(pGeoMap)
	{

		::BitBlt(m_MapControl.GetClientDC(),0,0,rect.Width(),rect.Height(),m_MapControl.GetMemDC(),0,0,SRCCOPY);
	}
	else
	{
		//���Ʊ���
		HBRUSH hbrush = ::CreateSolidBrush( RGB(255,255,255));

		::FillRect(m_MapControl.GetClientDC() , &rect , hbrush );

		::DeleteObject( hbrush );
	}

}

void CusMapCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	m_MapControl.ControlResize(nType,cx,cy);
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

	Carto::CMapPtr pGeoMap =m_MapControl.GetMap();
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

	m_MapControl.UpdateControl(drawAll);
}
