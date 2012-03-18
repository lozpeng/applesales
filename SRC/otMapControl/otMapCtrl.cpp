// otMapCtrl.cpp : CotMapCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "otMapControl.h"
#include "otMapCtrl.h"
#include "otMapPpg.h"
#include "ILayer.h"
#include "Map.h"
#include "IWorkspace.h"
//#include "TmsWorkspaceFactory.h"
#include "ShapefileWorkspaceFactory.h"
#include "RasterWSFactory.h"
#include "IRasterDataset.h"
#include "CursorMgr.h"
#include "DlgAbout.h"
#include "DIB.h"
#include "RelativePath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CotMapCtrl, COleControl)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CotMapCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEWHEEL()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CotMapCtrl, COleControl)
	DISP_FUNCTION_ID(CotMapCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CotMapCtrl, "AddFeatureLayer", dispidAddFeatureLayer, AddFeatureLayer, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CotMapCtrl, "Refresh", dispidRefresh, Refresh, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_EX_ID(CotMapCtrl, "Action", dispidAction, GetAction, SetAction, VT_I2)
	DISP_FUNCTION_ID(CotMapCtrl, "AddTmsFile", dispidAddTmsFile, AddTmsFile, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CotMapCtrl, "AddImageFile", dispidAddImageFile, AddImageFile, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION_ID(CotMapCtrl, "MoveMap", dispidMoveMap, MoveMap, VT_EMPTY, VTS_R8 VTS_R8)
	DISP_PROPERTY_EX_ID(CotMapCtrl, "Map", dispidMap, GetMap, SetNotSupported, VT_UNKNOWN)
	DISP_PROPERTY_EX_ID(CotMapCtrl, "Object", dispidObject, GetObject, SetNotSupported, VT_UNKNOWN)
	DISP_PROPERTY_EX_ID(CotMapCtrl, "ViewExtent", dispidViewExtent, GetViewExtent, SetViewExtent, VT_UNKNOWN)
	DISP_PROPERTY_EX_ID(CotMapCtrl, "FullExtent", dispidFullExtent, GetFullExtent, SetNotSupported, VT_UNKNOWN)
	DISP_FUNCTION_ID(CotMapCtrl, "AddShpFile", dispidAddShpFile, AddShpFile, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CotMapCtrl, "UpdateContent", dispidUpdateContent, UpdateContent, VT_EMPTY, VTS_I2)
	DISP_PROPERTY_EX_ID(CotMapCtrl, "ScreenCanvas", dispidScreenCanvas, GetScreenCanvas, SetNotSupported, VT_UNKNOWN)
	DISP_FUNCTION_ID(CotMapCtrl, "RefreshScreen", dispidRefreshScreen, RefreshScreen, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CotMapCtrl, "LoadGWF", dispidLoadGWF, LoadGWF, VT_EMPTY, VTS_BSTR)
	DISP_PROPERTY_EX_ID(CotMapCtrl, "MouseType", dispidMouseType, GetMouseType, SetMouseType, VT_I2)
	DISP_PROPERTY_EX_ID(CotMapCtrl, "MouseIcon", dispidMouseIcon, GetNotSupported, SetMouseIcon, VT_BSTR)
	DISP_FUNCTION_ID(CotMapCtrl, "MapToPixel", dispidMapToPixel, MapToPixel, VT_EMPTY, VTS_R8 VTS_R8 VTS_PI4 VTS_PI4)
	DISP_FUNCTION_ID(CotMapCtrl, "PixelToMap", dispidPixelToMap, PixelToMap, VT_UNKNOWN, VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(CotMapCtrl, "MoveCenterTo", dispidMoveCenterTo, MoveCenterTo, VT_EMPTY, VTS_UNKNOWN)
	DISP_FUNCTION_ID(CotMapCtrl, "OutputMap", dispidOutputMap, OutputMap, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(CotMapCtrl, "OutputMapToFile", dispidOutputMapToFile, OutputMapToFile, VT_BOOL, VTS_BSTR VTS_I2)
	DISP_FUNCTION_ID(CotMapCtrl, "LoadElementFile", dispidLoadElementFile, LoadElementFile, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CotMapCtrl, "RemoveElement", dispidRemoveElement, RemoveElement, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CotMapCtrl, "SaveElement", dispidSaveElement, SaveElement, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CotMapCtrl, "FlashLayer", dispidFlashLayer, FlashLayer, VT_EMPTY, VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(CotMapCtrl, "StopFlashLayer", dispidStopFlashLayer, StopFlashLayer, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CotMapCtrl, COleControl)
	EVENT_CUSTOM_ID("OnDoubleClick", eventidOnDoubleClick, FireDoubleClick, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8)
	EVENT_CUSTOM_ID("OnMouseDown", eventidOnMouseDown, FireMouseDown, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8)
	EVENT_CUSTOM_ID("OnMouseUp", eventidOnMouseUp, FireMouseUp, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8)
	EVENT_CUSTOM_ID("OnMouseMove", eventidOnMouseMove, FireMouseMove, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CotMapCtrl, 1)
	PROPPAGEID(CotMapPropPage::guid)
END_PROPPAGEIDS(CotMapCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CotMapCtrl, "OTMAPCONTROL.otMapCtrl.1",
	0x875f9c3b, 0x337b, 0x4d2c, 0xa3, 0x25, 0x27, 0x7f, 0x2e, 0x1d, 0x20, 0x68)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CotMapCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID BASED_CODE IID_DotMapControl =
		{ 0x1C60EC25, 0x8C5A, 0x4B28, { 0xAE, 0xF7, 0x1, 0x7C, 0x15, 0x8D, 0x40, 0x17 } };
const IID BASED_CODE IID_DotMapControlEvents =
		{ 0x5E23396E, 0x8367, 0x4E8E, { 0xA9, 0xFF, 0xCB, 0xA2, 0x3B, 0x37, 0x8F, 0xAA } };



// �ؼ�������Ϣ

static const DWORD BASED_CODE _dwotMapControlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CotMapCtrl, IDS_OTMAPCONTROL, _dwotMapControlOleMisc)



// CotMapCtrl::CotMapCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CotMapCtrl ��ϵͳע�����

BOOL CotMapCtrl::CotMapCtrlFactory::UpdateRegistry(BOOL bRegister)
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
			IDS_OTMAPCONTROL,
			IDB_OTMAPCONTROL,
			afxRegApartmentThreading,
			_dwotMapControlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CotMapCtrl::CotMapCtrl - ���캯��

CotMapCtrl::CotMapCtrl()
{
	InitializeIIDs(&IID_DotMapControl, &IID_DotMapControlEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�

	m_pMapInterface =NULL;

	m_hClientDC =m_hMemDC =NULL;

	m_pCurAction =NULL;

	m_ActionType =actionNone;

	m_BgColor =RGB(255,255,255);

	m_lCursorType =cursorNormal;

	m_nBorderSize =1;

	m_bTimer = false;
	m_bMouseWheel = false;

	m_mouseType =otMouseDefault;

	m_CustomCursor =NULL;

	m_FlashLayerId =-1;
}



// CotMapCtrl::~CotMapCtrl - ��������

CotMapCtrl::~CotMapCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
	if(m_pGeomap)
	{

		m_pMapInterface->Release();
	}
	if(m_CustomCursor)
	{
	    DestroyCursor(m_CustomCursor);
	}
}



// CotMapCtrl::OnDraw - ��ͼ����

void CotMapCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;


    
}



// CotMapCtrl::DoPropExchange - �־���֧��

void CotMapCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}



// CotMapCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CotMapCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CotMapCtrl::AboutBox - ���û���ʾ�����ڡ���

void CotMapCtrl::AboutBox()
{
	CDlgAbout dlgAbout;
	dlgAbout.DoModal();
}



// CotMapCtrl ��Ϣ�������

int CotMapCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	//����һ��Ĭ�ϵĵ�ͼ
	m_hClientDC = ::GetDC(GetSafeHwnd());
	m_hMemDC = ::CreateCompatibleDC(m_hClientDC);
	m_pGeomap =new Carto::CMap();
	m_pGeomap->SetName("Map--0");
	CRect rect;
    GetClientRect(rect);
	//rect.DeflateRect(m_nBorderSize,m_nBorderSize);
	m_pGeomap->GetDisplay()->SetDC((long)m_hMemDC,rect.Width(), rect.Height());

	//��ʼ����ĻDisplay
	m_pScreenDisplay.reset(new Display::IDisplay());
	m_pScreenDisplay->SetDC((long)m_hClientDC,m_lSizeX,m_lSizeY);

	//����һ��GeoMap�������
	IOriginDataPtr pData;
	CoCreateInstance(CLSID_GeoMap,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	Carto::CMapPtr *ppMap =new Carto::CMapPtr(m_pGeomap);
	pData->put_OriginData((long)ppMap);
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IGeoMap),(void**)&m_pMapInterface);


	return 0;
}


void CotMapCtrl::OnSize(UINT nType, int cx, int cy)
{
	COleControl::OnSize(nType, cx, cy);

	m_lSizeX =cx;
	m_lSizeY =cy;


	if(m_pGeomap)
	{
		DIS_BOUND rect;
		rect.left = rect.top = 0;
		rect.right = m_lSizeX;
		rect.bottom = m_lSizeY;


		m_pGeomap->GetDisplay()->CacheBuffer(m_lSizeX,m_lSizeY);

		//���¿��ӷ�Χ�Ĵ�С
	
		m_pGeomap->GetDisplay()->GetDisplayTransformation().SetViewBound(rect);

		m_pGeomap->Draw(drawAll);
		RefreshScreen();

	}
	if(m_pScreenDisplay)
	{
		m_pScreenDisplay->GetDrawDC()->CacheBitmap(cx,cy);
	}
	
}

void CotMapCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� COleControl::OnPaint()
	CRect rect;
	GetClientRect(rect);
	if(m_pGeomap)
	{
		
		::BitBlt(m_hClientDC,0,0,rect.Width(),rect.Height(),m_hMemDC,0,0,SRCCOPY);
	}
	else
	{
		//���Ʊ���
		HBRUSH hbrush = ::CreateSolidBrush( RGB(255,255,255));
		
		::FillRect(m_hClientDC , &rect , hbrush );

		::DeleteObject( hbrush );
	}
    //���Ʊ߿�
	/*dc.Draw3dRect (rect,	::GetSysColor (COLOR_3DSHADOW), 
		::GetSysColor (COLOR_3DSHADOW));*/

}

void CotMapCtrl::AddFeatureLayer(BSTR filename)
{
	/*_bstr_t  csDataSourceTmp =filename;
	
    
	Geodatabase::IWorkspace *pWorkspace =CTmsWorkspaceFactory::GetInstance()->OpenFromFile(csDataSourceTmp);

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

	m_pGeomap->AddNewLayer(pFeatureClass);
	

	Refresh();*/
}

void CotMapCtrl::Refresh()
{
	if(m_pGeomap)
	{
		m_pGeomap->Draw(drawAll);
		RefreshScreen();
		
	}
	//Invalidate(FALSE);

}

void CotMapCtrl::RefreshScreen()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(m_pGeomap)
	{
		m_pGeomap->GetDisplay()->SetDrawBuffer(drawAll);
		m_pGeomap->GetDisplay()->DrawBackgroud();
		m_pGeomap->GetDisplay()->RefreshDisplay(drawAll);

		CRect rect;
		GetClientRect(rect);
		::BitBlt(m_hClientDC,0,0,rect.Width(),rect.Height(),m_hMemDC,0,0,SRCCOPY);

		//���Ʊ߿�
		/*CDC *pDC =GetDC();
		pDC->Draw3dRect(rect,::GetSysColor (COLOR_3DSHADOW), 
			::GetSysColor (COLOR_3DSHADOW));*/
		//ReleaseDC(pDC);
	}
}
void CotMapCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	double dx,dy;
	m_pGeomap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,dx,dy);

	//���������¼�
	FireMouseDown(1,0,point.x,point.y,dx,dy);

    if(m_pCurAction)
	{
		m_pCurAction->LButtonDownEvent(nFlags,point);
	}
	COleControl::OnLButtonDown(nFlags, point);
}

void CotMapCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	double dx,dy;
	m_pGeomap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,dx,dy);

	//�������̧���¼�
	FireMouseUp(1,0,point.x,point.y,dx,dy);

	if(m_pCurAction)
	{
		m_pCurAction->LButtonUpEvent(nFlags,point);
	}
	COleControl::OnLButtonUp(nFlags, point);
}

void CotMapCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	double dx,dy;
	m_pGeomap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,dx,dy);

	//����˫���¼�
	FireDoubleClick(1,0,point.x,point.y,dx,dy);

	if(m_pCurAction)
	{
		m_pCurAction->LButtonDblClkEvent(nFlags,point);
	}

	COleControl::OnLButtonDblClk(nFlags, point);
}

void CotMapCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(m_pCurAction)
	{
		m_pCurAction->KeyDownEvent(nChar,nRepCnt,nFlags);
	}

	COleControl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CotMapCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
	if(m_pCurAction)
	{
		m_pCurAction->KeyUpEvent(nChar,nRepCnt,nFlags);
	}
	COleControl::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CotMapCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	double dx,dy;
	m_pGeomap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,dx,dy);

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
	FireMouseMove(button,0,point.x,point.y,dx,dy);
	
	if(m_pCurAction)
	{
		m_pCurAction->MouseMoveEvent(nFlags,point);
	}

	COleControl::OnMouseMove(nFlags, point);
}

void CotMapCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	double dx,dy;
	m_pGeomap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,dx,dy);

	//���������¼�
	FireMouseDown(2,0,point.x,point.y,dx,dy);

	if(m_pCurAction)
	{
		m_pCurAction->RButtonDownEvent(nFlags,point);
	}

	COleControl::OnRButtonDown(nFlags, point);
}

void CotMapCtrl::OnRButtonUp(UINT nFlags, CPoint point)
{
	double dx,dy;
	m_pGeomap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,dx,dy);

	//�������̧���¼�
	FireMouseUp(2,0,point.x,point.y,dx,dy);


	COleControl::OnRButtonUp(nFlags, point);
}

BOOL CotMapCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if(!m_pGeomap)
		return FALSE;
	double dblRatio = 1;
	long lSceenWidth,lSceenHeight;
	GEOMETRY::geom::Coordinate point;
	CRect rect;
	GetClientRect(&rect);
	lSceenWidth = rect.Width();
	lSceenHeight = rect.Height();

	Display::IDisplayPtr pDispaly = m_pGeomap->GetDisplay();

	if (!m_bTimer)
	{
		m_srcEnvelop = m_pGeomap->GetViewEnvelope();
		SetTimer(1,300,NULL);
		m_dblScale = pDispaly->GetDisplayTransformation().GetScale();

		m_srcScale = m_dblScale;

		m_bTimer = true;
	}

	m_bMouseWheel = true;

	HDC hMemDC = ::CreateCompatibleDC(m_hClientDC);

	HBITMAP hOldBitmap,hBitmap = ::CreateCompatibleBitmap(m_hClientDC,m_lSizeX,m_lSizeY);

	hOldBitmap = (HBITMAP)::SelectObject(hMemDC,hBitmap);

	//���Ʊ���
	HBRUSH hbrush = ::CreateSolidBrush( RGB(255,255,255));

	::FillRect(hMemDC , &rect , hbrush );

	::DeleteObject( hbrush );

	double xmin,xmax,ymin,ymax;

	if (zDelta > 0) //�Ŵ�
	{
		dblRatio = 0.8;

		m_dblScale *= dblRatio;

		m_pGeomap->GetViewEnvelope().centre(point);

		xmin = point.x - lSceenWidth/2.0*m_dblScale;
		xmax = point.x + lSceenWidth/2.0*m_dblScale;
		ymin = point.y - lSceenHeight/2.0*m_dblScale;
		ymax = point.y + lSceenHeight/2.0*m_dblScale;

		GEOMETRY::geom::Envelope newExt(xmin,xmax,ymin,ymax);

		//�ı��ͼ����ʾ��Χ
		m_pGeomap->GetDisplay()->GetDisplayTransformation().FitViewBound(newExt);

		CRect srcRect,destRect;

		CalSrcRect(newExt,srcRect);

		//���Ŀ�귶Χ��ԭʼ��ΧС����Ŀ�����������View�Ŀͻ���
		if(newExt.getMaxX()<=m_srcEnvelop.getMaxX() 
			&& newExt.getMinX()>=m_srcEnvelop.getMinX() 
			&& newExt.getMaxY()<=m_srcEnvelop.getMaxY()
			&& newExt.getMinY()>=m_srcEnvelop.getMinY())
		{
			destRect = rect;
		}
		else
		{
			GEOMETRY::geom::Envelope srcExtent =m_srcEnvelop;
			CalDestRect(srcExtent,newExt,destRect);

		}

		::SetStretchBltMode(hMemDC,MAXSTRETCHBLTMODE);

		::StretchBlt(hMemDC,destRect.left,destRect.top,destRect.Width(),destRect.Height(),(HDC)pDispaly->GetDrawDC()->GetSafeHdc(),srcRect.left,srcRect.top,srcRect.Width(),srcRect.Height(),SRCCOPY);


		//::BitBlt(m_hMemDC,0,0,m_lSizeX,m_lSizeY,hMemDC,0,0,SRCCOPY);
		::BitBlt(m_hClientDC,0,0,m_lSizeX,m_lSizeY,hMemDC,0,0,SRCCOPY);

	}
	else if (zDelta < 0) //��С
	{
		dblRatio = 1.2;

		m_dblScale *= dblRatio;

		m_pGeomap->GetViewEnvelope().centre(point);

		xmin = point.x - lSceenWidth/2.0*m_dblScale;
		xmax = point.x + lSceenWidth/2.0*m_dblScale;
		ymin = point.y - lSceenHeight/2.0*m_dblScale;
		ymax = point.y + lSceenHeight/2.0*m_dblScale;

		GEOMETRY::geom::Envelope newExt(xmin,xmax,ymin,ymax);

		//�ı��ͼ����ʾ��Χ
		m_pGeomap->GetDisplay()->GetDisplayTransformation().FitViewBound(newExt);


		CRect srcRect,destRect;

		CalSrcRect(m_pGeomap->GetViewEnvelope(),srcRect);

		//���Ŀ�귶Χ��ԭʼ��ΧС����Ŀ�����������View�Ŀͻ���
		if(newExt.getMaxX()<=m_srcEnvelop.getMaxX() 
			&& newExt.getMinX()>=m_srcEnvelop.getMinX() 
			&& newExt.getMaxY()<=m_srcEnvelop.getMaxY()
			&&newExt.getMinY()>=m_srcEnvelop.getMinY())
		{
			destRect = rect;
		}
		else
		{
			GEOMETRY::geom::Envelope srcExtent =m_srcEnvelop;
			CalDestRect(srcExtent,newExt,destRect);

		}

		::SetStretchBltMode(hMemDC,MAXSTRETCHBLTMODE);

		::StretchBlt(hMemDC,destRect.left,destRect.top,destRect.Width(),destRect.Height(),(HDC)pDispaly->GetDrawDC()->GetSafeHdc(),srcRect.left,srcRect.top,srcRect.Width(),srcRect.Height(),SRCCOPY);

		
		::BitBlt(m_hClientDC,0,0,m_lSizeX,m_lSizeY,hMemDC,0,0,SRCCOPY);

	}

	::SelectObject(hMemDC,hOldBitmap);
	::DeleteObject(hBitmap);
	::DeleteDC(hMemDC);

	return COleControl::OnMouseWheel(nFlags, zDelta, pt);
}

void CotMapCtrl::CalSrcRect(GEOMETRY::geom::Envelope extent,CRect &rect)
{
	//���Ŀ�귶Χ��ԭʼ��Χ����ȡ����memDC
	double xmin,xmax,ymin,ymax;
	if(extent.getMaxX()>=m_srcEnvelop.getMaxX() && extent.getMinX()<=m_srcEnvelop.getMinX() && extent.getMaxY()>=m_srcEnvelop.getMaxY() && extent.getMinY()<=m_srcEnvelop.getMinY())
	{
		rect =  m_pGeomap->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();
		return;
	}
	else
	{

		GEOMETRY::geom::Coordinate		 cp;
		GEOMETRY::geom::Coordinate	    cPoint, cCp;
		GEOMETRY::geom::Envelope	       cWrdExt;

		rect =  m_pGeomap->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();
		//
		cp.x = rect.CenterPoint().x;
		cp.y = rect.CenterPoint().y;

		cWrdExt = m_srcEnvelop;
		cWrdExt.centre(cCp);

		cPoint.x = extent.getMinX();
		cPoint.y = extent.getMinY();

		cPoint.x -= cCp.x;
		cPoint.y -= cCp.y;
		xmin = cp.x + cPoint.x / (m_srcScale);
		ymax = cp.y - cPoint.y / (m_srcScale);

		cPoint.x = extent.getMaxX();
		cPoint.y = extent.getMaxY();
		cPoint.x -= cCp.x;
		cPoint.y -= cCp.y;
		xmax = cp.x + cPoint.x / (m_srcScale);
		ymin = cp.y - cPoint.y / (m_srcScale);

		rect.left = (long)(xmin+0.5);
		rect.top = (long)(ymin+0.5);
		rect.right = (long)(xmax+0.5);
		rect.bottom = (long)(ymax+0.5);	

	}


}

void CotMapCtrl::CalDestRect(GEOMETRY::geom::Envelope srcExtent,GEOMETRY::geom::Envelope destExtent,CRect &rect)
{

	GEOMETRY::geom::Coordinate	  cp;
	GEOMETRY::geom::Coordinate	  cPoint, cCp;
	GEOMETRY::geom::Envelope	     cWrdExt;
	double xmin,xmax,ymin,ymax;

	rect = m_pGeomap->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();
	//
	cp.x = rect.CenterPoint().x;
	cp.y = rect.CenterPoint().y;

	cWrdExt = destExtent;
	cWrdExt.centre(cCp);

	cPoint.x = srcExtent.getMinX();
	cPoint.y = srcExtent.getMinY();
	cPoint.x -= cCp.x;
	cPoint.y -= cCp.y;

	xmin = cp.x + cPoint.x / (m_dblScale);
	ymax = cp.y - cPoint.y / (m_dblScale);

	cPoint.x = srcExtent.getMaxX();
	cPoint.y = srcExtent.getMaxY();
	cPoint.x -= cCp.x;
	cPoint.y -= cCp.y;
	xmax = cp.x + cPoint.x / (m_dblScale);
	ymin = cp.y - cPoint.y / (m_dblScale);

	rect.left = (long)(xmin+0.5);
	rect.top = (long)(ymin+0.5);
	rect.right = (long)(xmax+0.5);
	rect.bottom = (long)(ymax+0.5);	


}

void CotMapCtrl::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==1)
	{
		//������ϸ�ʱ��Σ������ֻ���,�򽫱����Ϊfalse
		if(m_bMouseWheel)
		{
			m_bMouseWheel =false;
		}
		else
		{
			if(m_pGeomap->GetExtentMode() == Carto::EEM_AUTO)
			{
				m_pGeomap->GetDisplay()->GetDisplayTransformation().ZoomToFixScale(m_dblScale);

				Refresh();			
			}	
			KillTimer(1);	
			m_bTimer = false;
		}
	}
	else if(nIDEvent==2)
	{
		//������˸ͼ���¼�
		Carto::ILayerPtr pLayer=m_pGeomap->GetLayers().GetAt(m_FlashLayerId);
		if(pLayer)
		{
			pLayer->SetVisible(!pLayer->GetVisible());

			UpdateContent(otDrawGeography);
		}


	}
	COleControl::OnTimer(nIDEvent);
}


otActionType CotMapCtrl::GetAction(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
    
	return m_ActionType;
}

void CotMapCtrl::SetAction(otActionType type)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ�������Դ���������
    m_ActionType =type;
	m_pCurAction =IAction::FindAction(type);
	if(m_pCurAction)
	{
		m_pCurAction->Init(this,m_pGeomap.get());
	}
	SetModifiedFlag();
}

void CotMapCtrl::OffsetClient(long offset_x, long offset_y)
{
	if(m_pGeomap)
	{
		RECT rc;
		HBRUSH hbrush = ::CreateSolidBrush( m_BgColor );
		HDC hMemDC = ::CreateCompatibleDC(m_hClientDC);
		HBITMAP hOldBitmap,hBitmap = ::CreateCompatibleBitmap(m_hClientDC, m_lSizeX, m_lSizeY);

		rc.left=rc.top=0;rc.right=m_lSizeX;rc.bottom=m_lSizeY;

		hOldBitmap=(HBITMAP)::SelectObject(hMemDC,hBitmap);
		::FillRect(hMemDC , &rc , hbrush );
		::BitBlt(hMemDC,offset_x,offset_y,m_lSizeX,m_lSizeY,m_hMemDC,0,0,SRCCOPY);
		::BitBlt(m_hMemDC,0,0,m_lSizeX,m_lSizeY,hMemDC,0,0,SRCCOPY);
		::BitBlt(m_hClientDC,0,0,m_lSizeX,m_lSizeY,hMemDC,0,0,SRCCOPY);

		::SelectObject(hMemDC,hOldBitmap);
		::DeleteObject( hbrush );
		::DeleteObject(hBitmap);
		::DeleteDC(hMemDC);

		//���Ʊ߿�
       /* CDC *pDC =GetDC();
		pDC->Draw3dRect(&rc,::GetSysColor (COLOR_3DSHADOW), 
			::GetSysColor (COLOR_3DSHADOW));
		ReleaseDC(pDC);*/
	}
}

BOOL CotMapCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if(m_mouseType==otMouseDefault)
	{
		HCURSOR hCursor=CCursorMgr::GetCursor(m_lCursorType);
		SetCursor(hCursor);
	}
	else if(m_mouseType==otMouseCustom)
	{
       //�����Զ�����
	   if(m_CustomCursor)
	   {
		   SetCursor(m_CustomCursor);
	   }
	   else
	   {
		   //����Զ�����Ϊ�գ���Ĭ������Ϊ��ͷ
		   SetCursor(::LoadCursor(NULL,IDC_ARROW));
	   }
	}
	

	return TRUE;
}

void CotMapCtrl::AddTmsFile(BSTR filename)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//_bstr_t  csDataSourceTmp =filename;

	//CString csThemeName =csDataSourceTmp;

	//csThemeName = csThemeName.Mid (csThemeName.ReverseFind ('\\') + 1);
	//csThemeName =csThemeName.Left(csThemeName.ReverseFind('.'));

	//Geodatabase::IWorkspace *pWorkspace =CTmsWorkspaceFactory::GetInstance()->OpenFromFile(csDataSourceTmp);

	//if(!pWorkspace)
	//{
	//	MessageBox(_T("������ʧ�ܣ�"),_T("��ʾ"),MB_OK);
	//	return ;
	//}
	//Geodatabase::IFeatureClassPtr pFeatureClass =pWorkspace->OpenFeatureClass(csDataSourceTmp);

	//if(!pFeatureClass)
	//{
	//	MessageBox(_T("������ʧ�ܣ�"),_T("��ʾ"),MB_OK);
	//	return ;
	//}

	//if(m_pGeomap->AddNewLayer(pFeatureClass))
	//{
	//	Carto::CLayerArray &layers =m_pGeomap->GetLayers();
	//	Carto::ILayerPtr pLayer =layers.ElementAt(layers.GetSize()-1);
	//	//����ͼ������
	//	pLayer->SetName(std::string(_bstr_t(csThemeName)));
	//}


	//Refresh();
}

VARIANT_BOOL CotMapCtrl::AddImageFile(BSTR filename)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	_bstr_t csDataSourceTmp=filename;

    CString csThemeName =csDataSourceTmp;

	csThemeName = csThemeName.Mid (csThemeName.ReverseFind ('\\') + 1);
	csThemeName =csThemeName.Left(csThemeName.ReverseFind('.'));
	


	Geodatabase::IWorkspace *pWorkspace =CRasterWSFactory::GetInstance()->OpenFromFile(csDataSourceTmp);

	if(!pWorkspace)
	{
		MessageBox(_T("������ʧ�ܣ�"),_T("��ʾ"),MB_OK);
		return VARIANT_FALSE;
	}
	Geodatabase::IRasterDatasetPtr pRaster =pWorkspace->OpenRasterDataset(csDataSourceTmp);

	if(!pRaster)
	{
		MessageBox(_T("������ʧ�ܣ�"),_T("��ʾ"),MB_OK);
		return VARIANT_FALSE;
	}

	
	if(m_pGeomap->AddNewLayer(pRaster))
	{
		Carto::CLayerArray &layers =m_pGeomap->GetLayers();
		Carto::ILayerPtr pLayer =layers.GetAt(layers.GetSize()-1);
		//����ͼ������
		pLayer->SetName(std::string(_bstr_t(csThemeName)));
	
	}
	Refresh();
	return VARIANT_TRUE;
}

void CotMapCtrl::MoveMap(DOUBLE dx, DOUBLE dy)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_pGeomap->GetDisplay()->GetDisplayTransformation().MoveViewBound(dx,dy);
	Refresh();
}





IGeoMap* CotMapCtrl::GetMap(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������

	m_pMapInterface->AddRef();

	return m_pMapInterface;


}

IDispatch* CotMapCtrl::GetObject()
{
   AFX_MANAGE_STATE(AfxGetStaticModuleState());

   return CCmdTarget::GetIDispatch(TRUE);

}

IotEnvelope* CotMapCtrl::GetViewExtent(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	IotEnvelope *pEnvelop;
    CoCreateInstance(CLSID_otEnvelope,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotEnvelope),(void**)&pEnvelop);

    //�õ���ǰ��ͼ�ķ�Χ
	GEOMETRY::geom::Envelope envelope;
	m_pGeomap->GetDisplay()->GetDisplayTransformation().GetGeoBound(envelope);

	pEnvelop->put_MinX(envelope.getMinX());
	pEnvelop->put_MinY(envelope.getMinY());
	pEnvelop->put_MaxX(envelope.getMaxX());
	pEnvelop->put_MaxY(envelope.getMaxY());

	return pEnvelop;
}

void CotMapCtrl::SetViewExtent(IotEnvelope* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	GEOMETRY::geom::Envelope envelope;
	double minx,maxx,miny,maxy;

	pVal->get_MinX(&minx);
	pVal->get_MinY(&miny);
	pVal->get_MaxX(&maxx);
	pVal->get_MaxY(&maxy);

	envelope.init(minx,maxx,miny,maxy);

	m_pGeomap->GetDisplay()->GetDisplayTransformation().FitViewBound(envelope);

	SetModifiedFlag();
}

IotEnvelope* CotMapCtrl::GetFullExtent(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	IotEnvelope *pEnvelop;
	CoCreateInstance(CLSID_otEnvelope,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotEnvelope),(void**)&pEnvelop);

	GEOMETRY::geom::Envelope envelope=m_pGeomap->GetExtent();
	pEnvelop->put_MinX(envelope.getMinX());
	pEnvelop->put_MinY(envelope.getMinY());
	pEnvelop->put_MaxX(envelope.getMaxX());
	pEnvelop->put_MaxY(envelope.getMaxY());


	return pEnvelop;
}

void CotMapCtrl::AddShpFile(LPCTSTR filename)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	_bstr_t  csDataSourceTmp =filename;

	CString csThemeName =csDataSourceTmp;

	csThemeName = csThemeName.Mid (csThemeName.ReverseFind ('\\') + 1);
	csThemeName =csThemeName.Left(csThemeName.ReverseFind('.'));

	Geodatabase::IWorkspace *pWorkspace = CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(csDataSourceTmp);

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

	if(m_pGeomap->AddNewLayer(pFeatureClass))
	{
		Carto::CLayerArray &layers =m_pGeomap->GetLayers();
		Carto::ILayerPtr pLayer =layers.GetAt(layers.GetSize()-1);
		//����ͼ������
		pLayer->SetName(std::string(_bstr_t(csThemeName)));
	}


	Refresh();
}

void CotMapCtrl::UpdateContent(otDrawContent content)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(m_pGeomap)
	{
		m_pGeomap->Draw(content);
		RefreshScreen();

	}
	//Invalidate(FALSE);
}


IotCanvas* CotMapCtrl::GetScreenCanvas(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    //����ǰ��ͼ������ת��������ĻDisplay
    m_pScreenDisplay->GetDisplayTransformation() = m_pGeomap->GetDisplay()->GetDisplayTransformation();

	Display::IDisplayPtr *ppDis =new Display::IDisplayPtr(m_pScreenDisplay);

	IOriginDataPtr pData;
	CoCreateInstance(CLSID_otCanvas,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);
	pData->put_OriginData((long)ppDis);
	pData->put_AutoDestroy(TRUE);
    
	IotCanvas *pCanvas =NULL;

	pData->QueryInterface(__uuidof(IotCanvas),(void**)&pCanvas);

	return pCanvas;
}


void CotMapCtrl::LoadGWF(LPCTSTR filename)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
	//�򿪹����ļ�
	CFile file;
	if(!file.Open(filename,CFile::modeRead))
	{
        return;
	}

	//�ر�֮ǰ��map
	if(m_pGeomap)
	{
		m_pGeomap.reset();
	}
    CString PrjPath =filename;
	CString basePath =PrjPath.Left(PrjPath.ReverseFind(_T('\\'))+1);

	_bstr_t strPath =basePath;
	//���òο�·��
	SYSTEM::CRelativePath::SetBasePath(strPath);

	CArchive ar(&file,CArchive::load);

	unsigned long Size;
	ar >> Size;

	BYTE * pStart = new BYTE[Size];

	ar.Read( pStart , Size );

	SYSTEM::CBinArchive bin( pStart , Size );

	bin.SetReadState();

	serialization(bin,SERIEALIZE_MAP);

	ar.Close ();
	file.Close ();

	//��ȡͼԪ
	CString strELFPath = filename;
	int iResult = strELFPath.Replace( _T("GWF"), _T("ELF"));

	if ( iResult == 1 && _waccess( strELFPath, 0) == 0 )
	{
		CFile fileElF(strELFPath,CFile::modeRead);
		CArchive arELF(&fileElF,CArchive::load);

		
		arELF >> Size;

		BYTE * pbuffer = new BYTE[Size];

		arELF.Read( pbuffer , Size );

		SYSTEM::CBinArchive ebin( pbuffer , Size );

		ebin.SetReadState();

		serialization(ebin,SERIEALIZE_MAPELEMENT);

		arELF.Close ();
		fileElF.Close ();

		
	}

	//�ı�IGeoMap�ӿ�
	IOriginDataPtr pData;
	
	m_pMapInterface->QueryInterface(__uuidof(IOriginData),(void**)&pData);

	Carto::CMapPtr *ppMap =new Carto::CMapPtr(m_pGeomap);
	pData->put_OriginData((long)ppMap);
	pData->put_AutoDestroy(TRUE);




	delete[] pStart;
}


/************************************************************************************
* MapControl���¼�
*
*************************************************************************************/

void CotMapCtrl::FireDoubleClick(LONG button, LONG flag, LONG X, LONG Y, DOUBLE MapX, DOUBLE MapY)
{
	FireEvent(eventidOnDoubleClick, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8), button, flag, X, Y, MapX, MapY);
}

void CotMapCtrl::FireMouseDown(LONG button, LONG flag, LONG x, LONG y, DOUBLE mapX, DOUBLE mapY)
{
	FireEvent(eventidOnMouseDown, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8), button, flag, x, y, mapX, mapY);
}

void CotMapCtrl::FireMouseUp(LONG button, LONG flag, LONG x, LONG y, DOUBLE mapX, DOUBLE mapY)
{
	FireEvent(eventidOnMouseUp, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8), button, flag, x, y, mapX, mapY);
}

void CotMapCtrl::FireMouseMove(LONG button, LONG flag, LONG x, LONG y, DOUBLE mapX, DOUBLE mapY)
{
	FireEvent(eventidOnMouseMove, EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8), button, flag, x, y, mapX, mapY);
}


void CotMapCtrl::serialization(SYSTEM::IArchive &ar,SERIEALIZE_TYPE sType)
{
	if(!ar.IsRead())
	{
		return;
	}

	if ( sType == SERIEALIZE_MAP )
	{
		//�õ���ǰMap��ID
		long lMapID;
		ar & lMapID;

		long lMapCount;
		ar & lMapCount;

		Carto::CMap *pMap =NULL;
		Display::VIEW_POSITION pos;
		BOOL bIsCurMap = FALSE;
		for (long l = 0; l < 1; l++)
		{
			pMap = new Carto::CMap();

			//
			pMap->serializationEx2(ar);

			//������ʾ
			DIS_BOUND rect;
			rect.left = rect.top = 0;
			rect.right =m_lSizeX;
			rect.bottom = m_lSizeY;
			pMap->GetDisplay()->SetDC((long)m_hMemDC,m_lSizeX,m_lSizeY);		
			pMap->SetViewBound(rect);

			BOOL isCurMap;
			ar & isCurMap;

		}

		m_pGeomap =pMap;
	}
	else if ( sType == SERIEALIZE_MAPELEMENT )
	{
		long lMapCount;
		ar & lMapCount;

		
		
		m_pGeomap->serializationEx1(ar);
		

	}
		

	Refresh();
	
}

otMouseType CotMapCtrl::GetMouseType(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return m_mouseType;

	
}

void CotMapCtrl::SetMouseType(otMouseType newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_mouseType =newVal;

	SetModifiedFlag();
}

void CotMapCtrl::SetMouseIcon(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//�����Զ������ļ�
	m_CustomCursor =(HCURSOR)LoadImage(NULL,newVal,IMAGE_CURSOR,0,0,LR_LOADFROMFILE);

	SetModifiedFlag();
}

void CotMapCtrl::MapToPixel(DOUBLE mapX, DOUBLE mapY, LONG* X, LONG* Y)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(m_pGeomap)
	{
		long lx,ly;
		m_pGeomap->GetDisplay()->GetDisplayTransformation().ConvertGeoToDisplay(mapX,mapY,lx,ly);
		*X =lx;
		*Y =ly;
	}
}


IotPoint* CotMapCtrl::PixelToMap(LONG x, LONG y)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(m_pGeomap)
	{
		double dx,dy;
		m_pGeomap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(x,y,dx,dy);

		IotPoint *pPt =NULL;
	    CoCreateInstance(CLSID_otPoint,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotPoint),(void**)&pPt);
		pPt->put_X(dx);
		pPt->put_Y(dy);

		return pPt;

	}

	return NULL;
}

void CotMapCtrl::MoveCenterTo(IotPoint* point)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
	double dx,dy;
	point->get_X(&dx);
	point->get_Y(&dy);

	m_pGeomap->GetDisplay()->GetDisplayTransformation().SetGeoCenterX(dx);
	m_pGeomap->GetDisplay()->GetDisplayTransformation().SetGeoCenterY(dy);

	Refresh();
	
}

void CotMapCtrl::OutputMap(LONG hDC)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

    if(!m_pGeomap)
	{
		return;
	}
	if(m_lSizeX==0 || m_lSizeY==0)
	{
		return;
	}
	//���»���
	Refresh();

	//��ͼ
	::BitBlt((HDC)hDC,0,0,m_lSizeX,m_lSizeY,m_hMemDC,0,0,SRCCOPY);
	
}

VARIANT_BOOL CotMapCtrl::OutputMapToFile(LPCTSTR filename, otOutputFileType filetype)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(!m_pGeomap)
	{
		return VARIANT_FALSE;
	}
	if(m_lSizeX==0 || m_lSizeY==0)
	{
		return VARIANT_FALSE;
	}
    HDC hTempDC =::CreateCompatibleDC(m_hClientDC);  

    CBitmap drawbmp;
	drawbmp.CreateCompatibleBitmap(GetDC(),m_lSizeX,m_lSizeY);

	HBITMAP hOldBitmap=(HBITMAP)::SelectObject(hTempDC,drawbmp);

    //���»���
	Refresh();

    //��ͼ
	::BitBlt(hTempDC,0,0,m_lSizeX,m_lSizeY,m_hMemDC,0,0,SRCCOPY);

	::SelectObject(hTempDC,hOldBitmap);
    ::DeleteDC(hTempDC);

	Display::CDIB dib;
	if(!dib.CreateFromBitmap(drawbmp))
	{
		return VARIANT_FALSE;
	}

    _bstr_t str =filename;
	std::string path =str;

	path =path.substr(0,path.rfind('\\'));

	Geodatabase::IWorkspace *pWorkspace = CRasterWSFactory::GetInstance()->OpenFolder(path.c_str());

	if(!pWorkspace)
	{
		return VARIANT_FALSE;
	}

	Geodatabase::RasFileInfo  fileinfo;
	fileinfo.lWidth =dib.GetWidth();
	fileinfo.lHeight =dib.GetHeight();
	fileinfo.lChannelNum = 3;								//ͼ���ͨ����
	fileinfo.lDataType = 0;							//��������

	//�����ļ�
	if(!pWorkspace->CreateRasterDataset(str,&fileinfo))
	{
        return VARIANT_FALSE;
	}

	//���ļ�
	Geodatabase::IRasterDatasetPtr pRaster =pWorkspace->OpenRasterDataset(str,false);

	if(!pRaster)
	{
		return VARIANT_FALSE;
	}
    
	//д������
	unsigned char *buffer =new unsigned char[dib.GetWidth()*dib.GetHeight()];
    
	for(int i=2;i<=4;i++)
	{
       dib.GetImgDataBW(i,1,1,dib.GetWidth(),dib.GetHeight(),buffer);
	   pRaster->DataWriteBand(i-1,1,1,dib.GetWidth(),dib.GetHeight(),buffer);
	}

	delete []buffer;
    
	return VARIANT_TRUE;
}

void CotMapCtrl::LoadElementFile(LPCTSTR filename)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	// TODO: �ڴ���ӵ��ȴ���������
	CFile file;
	if(!file.Open(filename,CFile::modeRead))
		return;
	
	CArchive ar(&file,CArchive::load);
	
	unsigned long Size;
	ar >> Size;

	BYTE * pStart = new BYTE[Size];
	ar.Read( pStart , Size );

	SYSTEM::CBinArchive bin( pStart , Size );
	bin.SetReadState();
	
	long nMapCount;
	bin & nMapCount;

	for ( long i = 0; i < nMapCount; ++i )
	{
		m_pGeomap->serializationEx1( bin );
		break;
	}

	ar.Close ();
	file.Close ();
}

void CotMapCtrl::RemoveElement(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	m_pGeomap->GetGraphicLayer()->RemoveAllElements();
}

void CotMapCtrl::SaveElement(LPCTSTR filename)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	CFile file;
	if(!file.Open(filename, CFile::modeCreate|CFile::modeWrite ))
		return;

	CArchive ar(&file,CArchive::store);
	
	SYSTEM::CBinArchive bin;
	bin.SetWriteState();
	
	long nMapCount = 1;
	bin & nMapCount;

	for (long i = 0; i < nMapCount; i++)
	{
		m_pGeomap->serializationEx1(bin);
	}

	ar << bin.GetSize();
	ar.Write( bin.GetData() , bin.GetSize() );

	ar.Close ();
	file.Close ();	
}

void CotMapCtrl::FlashLayer(LONG layerId, LONG millisecond)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	if(!m_pGeomap)
	{
		return ;
	}
	KillTimer(2);
	int count =m_pGeomap->GetLayers().GetSize();
	if(layerId<0||layerId>=count)
	{
		return;
	}

	m_FlashLayerId =layerId;

	this->SetTimer(2,millisecond,NULL);
}

void CotMapCtrl::StopFlashLayer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	KillTimer(2);

	//����˸ͼ����Ϊ�ɼ�
	m_pGeomap->GetLayers().GetAt(m_FlashLayerId)->SetVisible(true);

	UpdateContent(otDrawGeography);
	m_FlashLayerId =-1;
}


