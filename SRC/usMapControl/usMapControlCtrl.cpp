// usMapControlCtrl.cpp : CusMapCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "usMapControl.h"
#include "usMapControlCtrl.h"
#include "usMapControlPropPage.h"
#include "ShapefileWorkspaceFactory.h"
#include "ShapefileWorkspace.h"
#include "ShapefileFeatureClass.h"
#include "RasterWSFactory.h"
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
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CusMapCtrl, COleControl)
	DISP_FUNCTION_ID(CusMapCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CusMapCtrl, "AddShpfile", dispidAddShpfile, AddShpfile, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CusMapCtrl, "Refresh", dispidRefresh, Refresh, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_EX_ID(CusMapCtrl, "CurTool", dispidCurTool, GetCurTool, SetCurTool, VT_I2)
	DISP_FUNCTION_ID(CusMapCtrl, "AddImagefile", dispidAddImagefile, AddImagefile, VT_EMPTY, VTS_BSTR)
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

	m_bTimer = false;
	m_bMouseWheel = false;
}



// CusMapCtrl::~CusMapCtrl - ��������

CusMapCtrl::~CusMapCtrl()
{
	std::map<usToolType,Framework::ITool*>::iterator iter;
	for(iter =m_allTools.begin();iter!=m_allTools.end();iter++)
	{
		delete iter->second;
		iter->second =NULL;
	}
	m_allTools.clear();
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
	if(!m_pGeoMap)
		return FALSE;
	double dblRatio = 1;
	long lSceenWidth,lSceenHeight;
	GEOMETRY::geom::Coordinate point;
	CRect rect;
	GetClientRect(&rect);
	lSceenWidth = rect.Width();
	lSceenHeight = rect.Height();

	Display::IDisplayPtr pDispaly = m_pGeoMap->GetDisplay();

	if (!m_bTimer)
	{
		m_srcEnvelop = m_pGeoMap->GetViewEnvelope();
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

		m_pGeoMap->GetViewEnvelope().centre(point);

		xmin = point.x - lSceenWidth/2.0*m_dblScale;
		xmax = point.x + lSceenWidth/2.0*m_dblScale;
		ymin = point.y - lSceenHeight/2.0*m_dblScale;
		ymax = point.y + lSceenHeight/2.0*m_dblScale;

		GEOMETRY::geom::Envelope newExt(xmin,xmax,ymin,ymax);

		//�ı��ͼ����ʾ��Χ
		m_pGeoMap->GetDisplay()->GetDisplayTransformation().FitViewBound(newExt);

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

		m_pGeoMap->GetViewEnvelope().centre(point);

		xmin = point.x - lSceenWidth/2.0*m_dblScale;
		xmax = point.x + lSceenWidth/2.0*m_dblScale;
		ymin = point.y - lSceenHeight/2.0*m_dblScale;
		ymax = point.y + lSceenHeight/2.0*m_dblScale;

		GEOMETRY::geom::Envelope newExt(xmin,xmax,ymin,ymax);

		//�ı��ͼ����ʾ��Χ
		m_pGeoMap->GetDisplay()->GetDisplayTransformation().FitViewBound(newExt);


		CRect srcRect,destRect;

		CalSrcRect(m_pGeoMap->GetViewEnvelope(),srcRect);

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
	if(m_bMouseWheel)
	{
		m_bMouseWheel =false;
	}
	else
	{
		if(m_pGeoMap->GetExtentMode() == Carto::EEM_AUTO)
		{
			m_pGeoMap->GetDisplay()->GetDisplayTransformation().ZoomToFixScale(m_dblScale);

			Refresh();			
		}	
		KillTimer(1);	
		m_bTimer = false;
	}

	COleControl::OnTimer(nIDEvent);

	
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
	//�����ڹ��߼��в����Ƿ������ʵ��
	std::map<usToolType,Framework::ITool*>::iterator iter;
	iter =m_allTools.find(tooltype);
	if(iter!=m_allTools.end())
	{
		return iter->second;
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

	if(pTool)
	{
		m_allTools[tooltype] =pTool;
	}

	return pTool;
}
BOOL CusMapCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if(m_cursor)
	{
		::SetCursor(m_cursor);
	}
	else
	{
		//����Ĭ�Ϲ��
		::SetCursor(LoadCursor(NULL,IDC_ARROW));
	}


	return TRUE;
}

void CusMapCtrl::CalSrcRect(GEOMETRY::geom::Envelope extent,CRect &rect)
{
	//���Ŀ�귶Χ��ԭʼ��Χ����ȡ����memDC
	double xmin,xmax,ymin,ymax;
	if(extent.getMaxX()>=m_srcEnvelop.getMaxX() && extent.getMinX()<=m_srcEnvelop.getMinX() && extent.getMaxY()>=m_srcEnvelop.getMaxY() && extent.getMinY()<=m_srcEnvelop.getMinY())
	{
		rect =  m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();
		return;
	}
	else
	{

		GEOMETRY::geom::Coordinate		 cp;
		GEOMETRY::geom::Coordinate	    cPoint, cCp;
		GEOMETRY::geom::Envelope	       cWrdExt;

		rect =  m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();
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

void CusMapCtrl::CalDestRect(GEOMETRY::geom::Envelope srcExtent,GEOMETRY::geom::Envelope destExtent,CRect &rect)
{

	GEOMETRY::geom::Coordinate	  cp;
	GEOMETRY::geom::Coordinate	  cPoint, cCp;
	GEOMETRY::geom::Envelope	     cWrdExt;
	double xmin,xmax,ymin,ymax;

	rect = m_pGeoMap->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();
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
void CusMapCtrl::AddImagefile(LPCTSTR filename)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	_bstr_t csDataSourceTmp=filename;

	CString csThemeName =csDataSourceTmp;

	csThemeName = csThemeName.Mid (csThemeName.ReverseFind ('\\') + 1);
	csThemeName =csThemeName.Left(csThemeName.ReverseFind('.'));



	Geodatabase::IWorkspace *pWorkspace =CRasterWSFactory::GetInstance()->OpenFromFile(csDataSourceTmp);

	if(!pWorkspace)
	{
		MessageBox(_T("������ʧ�ܣ�"),_T("��ʾ"),MB_OK);
		return ;
	}
	Geodatabase::IRasterDatasetPtr pRaster =pWorkspace->OpenRasterDataset(csDataSourceTmp);

	if(!pRaster)
	{
		MessageBox(_T("������ʧ�ܣ�"),_T("��ʾ"),MB_OK);
		return;
	}


	if(m_pGeoMap->AddNewLayer(pRaster))
	{
		Carto::CLayerArray &layers =m_pGeoMap->GetLayers();
		Carto::ILayerPtr pLayer =layers.GetAt(layers.GetSize()-1);
		//����ͼ������
		pLayer->SetName(std::string(_bstr_t(csThemeName)));

	}
	Refresh();
}
