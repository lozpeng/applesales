// DlgSymbolEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgTextSymbolEdit.h"
#include "SymbolFactory.h"
#include "IExtSymbol.h"
#include "IDisplay.h"

 
// CDlgTextSymbolEdit 对话框

IMPLEMENT_DYNAMIC(CDlgTextSymbolEdit, CDialog)

CDlgTextSymbolEdit::CDlgTextSymbolEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTextSymbolEdit::IDD, pParent)
{
	
}

CDlgTextSymbolEdit::~CDlgTextSymbolEdit()
{
	
}

void CDlgTextSymbolEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_DISPLAY, m_picture);
	DDX_Control(pDX, IDC_COMBO_SYMTYPE, m_comboSelType);
	DDX_Control(pDX, IDC_COMBOUNITS, m_UnitCombo);
	DDX_Control(pDX, IDC_ZOOM, m_cComboBoxZoom);
	DDX_Control(pDX ,IDC_BLOWUP , m_btAddition );
	DDX_Control(pDX ,IDC_REDUCE , m_btSubtration );
	DDX_Control(pDX ,IDC_ZOOMFIX , m_btZoomFix );
}


BEGIN_MESSAGE_MAP(CDlgTextSymbolEdit, CDialog)
	
	ON_BN_CLICKED(IDC_ZOOMFIX, OnBnClickedZoomfix)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_MESSAGE(WM_REPAINTLEGEND,OnRepaintLegend)
	ON_MESSAGE(WM_SETSYMBOLUNIT,OnReSetSymbolUnitCombo)
	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_CHANGED , &CDlgTextSymbolEdit::OnPropChange )
	ON_WM_DESTROY()

	ON_BN_CLICKED(IDC_BLOWUP, OnBnClickedBlowup)
	ON_BN_CLICKED(IDC_REDUCE, &CDlgTextSymbolEdit::OnBnClickedReduce)
	ON_CBN_SELCHANGE(IDC_ZOOM, &CDlgTextSymbolEdit::OnCbnSelchangeZoom)
	ON_CBN_SELCHANGE(IDC_COMBOUNITS, &CDlgTextSymbolEdit::OnCbnSelchangeCombounits)
	ON_BN_CLICKED(IDCANCEL, &CDlgTextSymbolEdit::OnBnClickedCancel)

	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CDlgTextSymbolEdit 消息处理程序




void CDlgTextSymbolEdit::SetSymbol(Display::CTextSymbolPtr pSymbol)
{
	m_pTextSymbol =  pSymbol ;

	m_pCopySymbol = m_pTextSymbol->Clone();
}

BOOL CDlgTextSymbolEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_btAddition.SetTooltip("放大");
	m_btSubtration.SetTooltip("缩小");
	m_btZoomFix.SetTooltip("1:1比例");

	m_UnitCombo.SetCurSel( 0 );
	m_UnitComboIndex = 0;

	m_cComboBoxZoom.SetCurSel(2);
	ShowSymbol();
	LoadConfig();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void CDlgTextSymbolEdit::OnBnClickedZoomfix()
{
	m_cComboBoxZoom.SetCurSel(2);
	UpdateData(TRUE);
	OnCbnSelchangeZoom();
}
	
void CDlgTextSymbolEdit::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

LRESULT CDlgTextSymbolEdit::OnPropChange(WPARAM wParam, LPARAM lParam)
{
	CBCGPProp* pProp = (CBCGPProp* )lParam;

	this->m_wndPropList.UpDataSymbol();

	m_pCopySymbol = m_pTextSymbol->Clone();

	ShowSymbol();
	return 0;
}

LRESULT CDlgTextSymbolEdit::OnRepaintLegend(WPARAM wParam, LPARAM lParam)
{
	OnCbnSelchangeZoom();
	return 0;
}

void CDlgTextSymbolEdit::ShowSymbol(void)
{
	Display::IDisplayPtr pSDisplay( new Display::IDisplay());
	CClientDC dc(this);

	CRect rc;
	GetDlgItem(IDC_STATIC_PREVIEW)->GetClientRect(&rc);
	long bmpWidth = rc.Width()*0.8;
	long bmpHeight = rc.Height()*0.8;
	//设置内存CDC
	CDC MemDC;
	//创建相容的bitmap和dc
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap( &dc , bmpWidth , bmpHeight );
	MemDC.CreateCompatibleDC(&dc);
	CBitmap *  oldbitmap = (CBitmap*)MemDC.SelectObject(&bitmap);
	pSDisplay->SetDC( (long)MemDC.GetSafeHdc() , bmpWidth , bmpHeight );

	DIS_RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = bmpWidth;
	rect.bottom= bmpHeight;

	rc.top = rc.left = 0;
	rc.right = bmpWidth;
	rc.bottom = bmpHeight;

	MemDC.FillSolidRect( &rc , RGB(255,255,255) );
	
	CPen pen( PS_DOT , 1 , RGB( 0 , 0 , 0 ) );
	CPen *oldpen = (CPen*)MemDC.SelectObject(&pen);
	POINT po;
	po.x = bmpWidth / 2;
	po.y = 0;

	MemDC.MoveTo(po);
	po.x = bmpWidth / 2;
	po.y = bmpHeight;
	MemDC.LineTo(po);
	po.x = 0;
	po.y = bmpHeight/2;

	MemDC.MoveTo(po);
	po.x = bmpWidth;
	po.y = bmpHeight/2;
	MemDC.LineTo(po);
	MemDC.SelectObject(oldpen);
	
	pSDisplay->DrawLegend( m_pCopySymbol.get() , &rect , 1 );

	MemDC.SelectObject(oldbitmap);
	MemDC.DeleteDC();

	HBITMAP bp = m_picture.SetBitmap((HBITMAP)bitmap.Detach());
	DeleteObject(bp);

}


LRESULT CDlgTextSymbolEdit::OnReSetSymbolUnitCombo(WPARAM wParam, LPARAM lParam)
{
	SetSymbolUnit((SYSTEM::SYS_UNIT_TYPE)wParam);
	return 0;
}



void CDlgTextSymbolEdit::SetSymbolUnit(SYSTEM::SYS_UNIT_TYPE symbolUnit)
{
	if ( symbolUnit == SYSTEM::SYS_UNIT_PIXEL )
	{
		m_UnitCombo.SetCurSel( 0 );
		m_UnitComboIndex = 0;
	}
	else if ( symbolUnit == SYSTEM::SYS_UNIT_MILLIMETER )
	{
		m_UnitCombo.SetCurSel( 1 );
		m_UnitComboIndex = 1;
	}
	else if ( symbolUnit == SYSTEM::SYS_UNIT_CENTIMETER )
	{
		m_UnitCombo.SetCurSel( 2 );
		m_UnitComboIndex = 2;
	}
	else if ( symbolUnit == SYSTEM::SYS_UNIT_DECIMETER )
	{
		m_UnitCombo.SetCurSel( 3 );
		m_UnitComboIndex = 3;
	}
	else if ( symbolUnit == SYSTEM::SYS_UNIT_POINT )
	{
		m_UnitCombo.SetCurSel( 4 );
		m_UnitComboIndex = 4;
	}
}

void CDlgTextSymbolEdit::LoadConfig(void)
{
	SYSTEM::CXMLConfiguration::Initialize();

	SYSTEM::XMLConfigurationPtr pRoot = Display::GetSymbolRenderConfig();
	if(pRoot == NULL)
	{
//		ErrorLog("Get symbolrender node failed.");
		return;
	}

	SYSTEM::IConfigItemPtr pDisplayItem = pRoot->GetChildByName(DISPLAYNODE);
	if( pDisplayItem == NULL )
		return;

	SYSTEM::IConfigItemPtr pSymConfig = pDisplayItem->GetChildByName(SYMBOLCFG);
	SYSTEM::IConfigItemPtr pSymConfigItem;

	for( int i = 0 ; i < pSymConfig->GetChildCount() ; i++ )
	{
		if( atoi(pSymConfig->GetChilds(i)->GetProperties("SymbolType")) == (int)m_pTextSymbol->GetType() )
		{
			pSymConfigItem = pSymConfig->GetChilds(i);
			break;
		}
	}

	if( pSymConfigItem == NULL )
		return;
	//	OTFALSERETURN_NOVAL("Error:Can't find the node of the symbol from XML file");

	//设置符号类型
	m_comboSelType.AddString( pSymConfigItem->GetProperties("Name") );
	m_comboSelType.SetCurSel( 0);

	
	//符号单位
	SetSymbolUnit( m_pTextSymbol->GetUnit());


	CRect rectPropList;
	GetDlgItem(IDC_PROPLIST)->GetClientRect (&rectPropList);
	GetDlgItem(IDC_PROPLIST)->MapWindowPoints (this, &rectPropList);
	m_wndPropList.InitWindow( rectPropList , this , -1 );
	m_wndPropList.SetSymbolPropListInterface( &m_properlistManager );	//需要在初始设置符号前，装入接口管理类
	m_wndPropList.InitSymbolPropList( m_pTextSymbol->GetType() );
	m_wndPropList.SetSymbol( m_pTextSymbol );
}

void CDlgTextSymbolEdit::OnBnClickedBlowup()
{
	int index = m_cComboBoxZoom.GetCurSel();
	if ( index-- > 0 )
	{
		m_cComboBoxZoom.SetCurSel(index);
		UpdateData(TRUE);
		OnCbnSelchangeZoom();
	}
}

void CDlgTextSymbolEdit::OnBnClickedReduce()
{
	int index=m_cComboBoxZoom.GetCurSel()+1;

	if(index<=3)
	{
		m_cComboBoxZoom.SetCurSel(index);
		UpdateData(TRUE);
		OnCbnSelchangeZoom();
	}
}

void CDlgTextSymbolEdit::OnCbnSelchangeZoom()
{
	m_pCopySymbol = m_pTextSymbol->Clone();

	int nSize=m_cComboBoxZoom.GetCurSel();
	switch(nSize)
	{
	case 0:
		m_pCopySymbol->Zoom(4.0f);

		break;
	case 1:
		m_pCopySymbol->Zoom(2.0f);

		break;
	case 2:
		m_pCopySymbol->Zoom(1.0f);

		break;
	case 3:
		m_pCopySymbol->Zoom(0.5f);

		break;
	}

	ShowSymbol();
}

void CDlgTextSymbolEdit::OnCbnSelchangeCombounits()
{
	// TODO: 在此添加控件通知处理程序代码
	int selectIndex = m_UnitCombo.GetCurSel();
	if ( selectIndex == m_UnitComboIndex )
	{
		return;
	}

	m_UnitComboIndex = selectIndex;

	if (selectIndex == 0)
	{

		m_pTextSymbol->SetUnit(SYSTEM::SYS_UNIT_PIXEL);
	}
	else if (selectIndex == 1)
	{
		m_pTextSymbol->SetUnit(SYSTEM::SYS_UNIT_MILLIMETER);
	}
	else if (selectIndex == 2)
	{
		m_pTextSymbol->SetUnit(SYSTEM::SYS_UNIT_CENTIMETER);
	}
	else if (selectIndex == 3)
	{
		m_pTextSymbol->SetUnit(SYSTEM::SYS_UNIT_DECIMETER);
	}
	else if (selectIndex == 4)
	{
		m_pTextSymbol->SetUnit(SYSTEM::SYS_UNIT_POINT);
	}

	m_pCopySymbol = m_pTextSymbol->Clone();

	m_wndPropList.InitSymbolPropList( m_pTextSymbol->GetType() );
	m_wndPropList.SetSymbol( m_pTextSymbol );
}

void CDlgTextSymbolEdit::OnDestroy()
{
	HBITMAP bp = m_picture.SetBitmap(NULL);
	DeleteObject(bp);

	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

void CDlgTextSymbolEdit::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CDlgTextSymbolEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	__super::OnMouseMove(nFlags, point);

	if( m_wndPropList.m_bCurrentForce )
	{
		this->SetFocus();
		m_wndPropList.m_bCurrentForce = false;
	}
}

