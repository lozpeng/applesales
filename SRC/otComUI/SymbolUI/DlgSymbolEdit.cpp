// DlgSymbolEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgSymbolEdit.h"
#include "SymbolFactory.h"
#include "IExtSymbol.h"
#include "IComplexSymbol.h"
#include "IDisplay.h"

// CDlgSymbolEdit 对话框

IMPLEMENT_DYNAMIC(CDlgSymbolEdit, CDialog)

CDlgSymbolEdit::CDlgSymbolEdit(CWnd* pParent /*=NULL*/)
: CDialog(CDlgSymbolEdit::IDD, pParent)
, m_bSolid(FALSE)
{

}

CDlgSymbolEdit::~CDlgSymbolEdit()
{

}

void CDlgSymbolEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADD,m_btAdd);
	DDX_Control(pDX, IDC_DEL,m_btDel);
	DDX_Control(pDX, IDC_MOVEUP,m_btUp);
	DDX_Control(pDX, IDC_MOVEDOWN,m_btDown);
	DDX_Control(pDX, IDC_COPY,m_btCopyBUT);
	DDX_Control(pDX, IDC_PASTE,m_btPaste);
	DDX_Control(pDX, IDC_DISPLAY, m_picture);
	DDX_Control(pDX, IDC_COMBO_SYMTYPE, m_comboSelType);
	DDX_Control(pDX,IDC_CR_LINE,m_btCrLine);
	DDX_Control(pDX,IDC_STR_LINE,m_btSTRLine);
	DDX_Control(pDX,IDC_CROSSLINE,m_btCRossLine);
	DDX_Control(pDX, IDC_COMBOUNITS, m_UnitCombo);
	DDX_Control( pDX,IDC_SYMBOLVIEW,m_editDlgManager.m_ComplexSymbolLayerCL);
	DDX_Control(pDX, IDC_ZOOM, m_cComboBoxZoom);
	//DDX_Control(pDX, IDC_ZOOM, m_cComboBoxZoom);
	DDX_Control(pDX ,IDC_BLOWUP , m_btAddition );
	DDX_Control(pDX ,IDC_REDUCE , m_btSubtration );
	DDX_Control(pDX ,IDC_ZOOMFIX , m_btZoomFix );
}


BEGIN_MESSAGE_MAP(CDlgSymbolEdit, CDialog)
	ON_BN_CLICKED(IDC_ADD, OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BLOWUP, OnBnClickedBlowup)
	ON_BN_CLICKED(IDC_COPY, OnBnClickedCopy)
	ON_BN_CLICKED(IDC_DEL, OnBnClickedDel)
	ON_BN_CLICKED(IDC_MOVEDOWN, OnBnClickedMovedown)
	ON_BN_CLICKED(IDC_MOVEUP, OnBnClickedMoveup)
	ON_BN_CLICKED(IDC_PASTE, OnBnClickedPaste)
	ON_BN_CLICKED(IDC_ZOOMFIX, OnBnClickedZoomfix)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_CHANGED , &CDlgSymbolEdit::OnPropChange )
	ON_MESSAGE(WM_REPAINTLEGEND,OnRepaintLegend)
	ON_MESSAGE(WM_SETSYMBOLSTYLE,OnReSetSymbolTypeCombo)
	ON_MESSAGE(WM_SETSYMBOLUNIT,OnReSetSymbolUnitCombo)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_STR_LINE, &CDlgSymbolEdit::OnBnClickedStrLine)
	ON_BN_CLICKED(IDC_CR_LINE, &CDlgSymbolEdit::OnBnClickedCrLine)
	ON_BN_CLICKED(IDC_CROSSLINE, &CDlgSymbolEdit::OnBnClickedCrossline)
	ON_BN_CLICKED(IDC_REDUCE, &CDlgSymbolEdit::OnBnClickedReduce)
	ON_CBN_SELCHANGE(IDC_ZOOM, &CDlgSymbolEdit::OnCbnSelchangeZoom)
	ON_CBN_SELCHANGE(IDC_COMBOUNITS, &CDlgSymbolEdit::OnCbnSelchangeCombounits)
	ON_BN_CLICKED(IDCANCEL, &CDlgSymbolEdit::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_SYMTYPE, &CDlgSymbolEdit::OnCbnSelchangeComboSymtype)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CDlgSymbolEdit 消息处理程序

LRESULT CDlgSymbolEdit::OnPropChange(WPARAM wParam, LPARAM lParam)
{
	CBCGPProp* pProp = (CBCGPProp* )lParam;

	this->m_wndPropList.UpDataSymbol();

	ShowSymbol();
	return 0;
}

LRESULT CDlgSymbolEdit::OnRepaintLegend(WPARAM wParam, LPARAM lParam)
{
	OnCbnSelchangeZoom();
	return 0;
}

void CDlgSymbolEdit::SetSymbol(Display::ISymbolPtr pSymbol)
{
	m_editDlgManager.SetSymbol( pSymbol );
}

void CDlgSymbolEdit::OnBnClickedAdd()
{
	Display::ISymbolPtr pSymbol=
		((Display::IComplexSymbolPtr)m_editDlgManager.m_pComplexSymbol)
		->GetAt(m_editDlgManager.GetSelect());

	if (pSymbol->GetType() & EXT_SYMBOL)
	{
		Display::IExtSymbolPtr curSymbol = pSymbol;
		Display::IExtSymbolPtr extSymbol = Display::CSymbolFactory::CreateExtSymbol(curSymbol->GetSymbolName());
		if ( extSymbol != NULL )
			((Display::IComplexSymbolPtr)m_editDlgManager.m_pComplexSymbol)->Insert(0, extSymbol ,true);
		else
		{
//			OTEND_NORET0("Error:Can't find Ext symbol to create Ext symbol")
		}
	}
	else
	{
		Display::ISymbolPtr newSymbol = Display::CSymbolFactory::CreateSymbol(pSymbol->GetType());
		((Display::IComplexSymbolPtr)m_editDlgManager.m_pComplexSymbol)
			->Insert(0, newSymbol ,true);
	}

	m_editDlgManager.ReSetSelectIndexToBegin();
	m_editDlgManager.ReSetSymboltoPropList((( Display::IComplexSymbolPtr )m_editDlgManager.m_pComplexSymbol)->GetAt(0));
	m_editDlgManager.SetCopySymbol();
	m_editDlgManager.UpdateComplexSymbolLayerCtrl();
	OnCbnSelchangeZoom();
}

void CDlgSymbolEdit::OnBnClickedBlowup()
{
	int index = m_cComboBoxZoom.GetCurSel();
	if ( index-- > 0 )
	{
		m_cComboBoxZoom.SetCurSel(index);
		UpdateData(TRUE);
		OnCbnSelchangeZoom();
	}
}

void CDlgSymbolEdit::OnBnClickedCopy()
{
	m_editDlgManager.m_pCopySymbol =
		((( Display::IComplexSymbolPtr )m_editDlgManager.m_pComplexSymbol)
		->GetAt(m_editDlgManager.GetSelect()))->Clone();
	m_editDlgManager.m_bVisible =(( Display::IComplexSymbolPtr )m_editDlgManager.m_pComplexSymbol)
		->IsVisible(m_editDlgManager.GetSelect());
}

void CDlgSymbolEdit::OnBnClickedDel()
{
	if ((( Display::IComplexSymbolPtr )m_editDlgManager.m_pComplexSymbol)->GetSize() > 1 )
	{
		int curSelect = m_editDlgManager.GetSelect();

		if( curSelect > 0 )
		{
			(( Display::IComplexSymbolPtr )m_editDlgManager.m_pComplexSymbol)->RemoveSymbol(curSelect--);
			m_editDlgManager.SetSelect(curSelect);
			m_editDlgManager.ReSetSymboltoPropList((( Display::IComplexSymbolPtr )m_editDlgManager.m_pComplexSymbol)->GetAt(curSelect));
			m_editDlgManager.SetCopySymbol();
			m_editDlgManager.UpdateComplexSymbolLayerCtrl();
			OnCbnSelchangeZoom();
		}
		else if( curSelect == 0 )
		{
			(( Display::IComplexSymbolPtr )m_editDlgManager.m_pComplexSymbol)->RemoveSymbol(curSelect);
			m_editDlgManager.SetSelect(curSelect);
			m_editDlgManager.ReSetSymboltoPropList((( Display::IComplexSymbolPtr )m_editDlgManager.m_pComplexSymbol)->GetAt(curSelect));
			m_editDlgManager.SetCopySymbol();
			m_editDlgManager.UpdateComplexSymbolLayerCtrl();
			OnCbnSelchangeZoom();
		}

		//(( Display::IComplexSymbolPtr )m_editDlgManager.m_pComplexSymbol)
		//	->RemoveSymbol(m_editDlgManager.GetSelect());

		//if( m_editDlgManager.GetSelect() > 0 )
		//{
		//	m_editDlgManager.SetSelect(m_editDlgManager.GetSelect()-1);
		//}

		/*m_editDlgManager.ReSetSymboltoPropList((( Display::IComplexSymbolPtr )m_editDlgManager.m_pComplexSymbol)->GetAt(m_editDlgManager.GetSelect()));*/
		/*m_editDlgManager.SetCopySymbol();
		m_editDlgManager.UpdateComplexSymbolLayerCtrl();
		OnCbnSelchangeZoom();*/
	}
}

void CDlgSymbolEdit::OnBnClickedMovedown()
{
	if( m_editDlgManager.GetSelect() <
		(( Display::IComplexSymbolPtr )m_editDlgManager.m_pComplexSymbol)->GetSize() -1 )
	{
		(( Display::IComplexSymbolPtr )m_editDlgManager.m_pComplexSymbol)
			->ExchangeOrder( m_editDlgManager.GetSelect() , m_editDlgManager.GetSelect() + 1 );
		m_editDlgManager.SetSelect(m_editDlgManager.GetSelect() + 1);
		m_editDlgManager.SetCopySymbol();
		m_editDlgManager.UpdateComplexSymbolLayerCtrl();
		OnCbnSelchangeZoom();
		m_editDlgManager.m_ComplexSymbolLayerCL.Scroll(CSize(0,m_editDlgManager.GetSelect()*50));
	}
}

void CDlgSymbolEdit::OnBnClickedMoveup()
{
	if( m_editDlgManager.GetSelect() > 0 )
	{
		(( Display::IComplexSymbolPtr )m_editDlgManager.m_pComplexSymbol)
			->ExchangeOrder( m_editDlgManager.GetSelect() - 1 , m_editDlgManager.GetSelect() );
		m_editDlgManager.SetSelect(m_editDlgManager.GetSelect() - 1);
		m_editDlgManager.SetCopySymbol();
		m_editDlgManager.UpdateComplexSymbolLayerCtrl();
		OnCbnSelchangeZoom();
		m_editDlgManager.m_ComplexSymbolLayerCL.Scroll(CSize(0,m_editDlgManager.GetSelect()*50));
	}
}

void CDlgSymbolEdit::OnBnClickedPaste()
{
	if( m_editDlgManager.m_pCopySymbol )
	{
		(( Display::IComplexSymbolPtr )m_editDlgManager.m_pComplexSymbol )
			->Insert( m_editDlgManager.GetSelect() , m_editDlgManager.m_pCopySymbol->Clone(),
			m_editDlgManager.m_bVisible );
		m_editDlgManager.ReSetSymboltoPropList((( Display::IComplexSymbolPtr )m_editDlgManager.m_pComplexSymbol)->GetAt(m_editDlgManager.GetSelect()));
		m_editDlgManager.SetCopySymbol();
		m_editDlgManager.UpdateComplexSymbolLayerCtrl();
		OnCbnSelchangeZoom();
	}
}

void CDlgSymbolEdit::OnBnClickedZoomfix()
{
	m_cComboBoxZoom.SetCurSel(2);
	UpdateData(TRUE);
	OnCbnSelchangeZoom();
}

void CDlgSymbolEdit::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

BOOL CDlgSymbolEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	add_Pic.LoadBitmap(IDB_ADD);
	del_Pic.LoadBitmap(IDB_DEL);
	up_Pic.LoadBitmap(IDB_UP);
	down_Pic.LoadBitmap(IDB_DOWN);
	copyBUT_Pic.LoadBitmap(IDB_COPY);
	paste_Pic.LoadBitmap(IDB_PASTE);

	m_btAdd.SetBitmap( add_Pic );
	m_btAdd.SetTooltip("根据当前选取符号类型添加新符号");
	m_btDel.SetBitmap( del_Pic );
	m_btDel.SetTooltip("删除当前选取符号");
	m_btUp.SetBitmap( up_Pic );
	m_btUp.SetTooltip("将当前选取符号向上移动");
	m_btDown.SetBitmap( down_Pic );
	m_btDown.SetTooltip("将当前选取符号向下移动");
	m_btCopyBUT.SetBitmap( copyBUT_Pic );
	m_btCopyBUT.SetTooltip("复制当前选取符号");
	m_btPaste.SetBitmap( paste_Pic );
	m_btPaste.SetTooltip("在当前选取符号的上方粘贴复制的符号");

	m_btAddition.SetTooltip("放大");
	m_btSubtration.SetTooltip("缩小");
	m_btZoomFix.SetTooltip("1:1比例");

	m_UnitCombo.SetCurSel( 0 );
	m_UnitComboIndex = 0;

	m_btCRossLine.SetCheck( 1 );
	m_btSTRLine.SetCheck( 1 );
	if( m_editDlgManager.m_nType==MARKER_SYMBOL )
	{
		m_bDraw = TRUE;
		m_btCRossLine.ShowWindow( SW_SHOW );
	}
	else if( m_editDlgManager.m_nType==LINE_SYMBOL )
	{
		m_bDraw = FALSE;
		m_bSolid = TRUE;
		m_btSTRLine.ShowWindow(SW_SHOW);
		m_btCrLine.ShowWindow(SW_SHOW);
	}
	else
	{
		m_bDraw=FALSE;
		m_bSolid=FALSE;
	}
	m_cComboBoxZoom.SetCurSel(2);
	m_editDlgManager.InitComplexSymbolLayerCtrl();
	ShowSymbol();
	LoadConfig();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgSymbolEdit::ShowSymbol(void)
{

	Display::IDisplayPtr pSDisplay( new Display::IDisplay());
	CClientDC dc(this);

	CRect rc;
	GetDlgItem(IDC_SYMBOLVIEW)->GetClientRect(&rc);
	//设置内存CDC
	CDC MemDC;
	//创建相容的bitmap和dc
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap( &dc , rc.Width() , 110 );
	MemDC.CreateCompatibleDC(&dc);
	CBitmap *  oldbitmap = (CBitmap*)MemDC.SelectObject(&bitmap);
	pSDisplay->SetDC( (long)MemDC.GetSafeHdc() , rc.Width() , 110 );

	DIS_RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = rc.Width();
	rect.bottom= 110;

	rc.top = rc.left = 0;
	rc.right = rc.Width();
	rc.bottom = 110;

	MemDC.FillSolidRect( &rc , RGB(255,255,255) );
	if(m_bDraw)
	{
		CPen pen( PS_DOT , 1 , RGB( 0 , 0 , 0 ) );
		CPen *oldpen = (CPen*)MemDC.SelectObject(&pen);
		POINT po;
		po.x = rc.Width() / 2;
		po.y = 0;

		MemDC.MoveTo(po);
		po.x = rc.Width() / 2;
		po.y = 110;
		MemDC.LineTo(po);
		po.x = 0;
		po.y = 55;

		MemDC.MoveTo(po);
		po.x = rc.Width();
		po.y = 55;
		MemDC.LineTo(po);
		MemDC.SelectObject(oldpen);
	}

	if( m_bSolid )
		pSDisplay->DrawLegend( m_editDlgManager.m_pSymbolCopy.get() , &rect , 0 );
	else
		pSDisplay->DrawLegend( m_editDlgManager.m_pSymbolCopy.get() , &rect , 1 );

	MemDC.SelectObject(oldbitmap);
	MemDC.DeleteDC();

	HBITMAP bp = m_picture.SetBitmap((HBITMAP)bitmap.Detach());
	DeleteObject(bp);

}

void CDlgSymbolEdit::OnDestroy()
{
	HBITMAP bp = m_picture.SetBitmap(NULL);
	DeleteObject(bp);

	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

LRESULT CDlgSymbolEdit::OnReSetSymbolTypeCombo(WPARAM wParam, LPARAM lParam)
{
	SetSymbolType((SYMBOL_TYPE)wParam);
	return 0;
}

LRESULT CDlgSymbolEdit::OnReSetSymbolUnitCombo(WPARAM wParam, LPARAM lParam)
{
	SetSymbolUnit((SYSTEM::SYS_UNIT_TYPE)wParam);
	return 0;
}

void CDlgSymbolEdit::SetSymbolType(SYMBOL_TYPE type)
{

	if (m_currentSymbolType == type)
	{
		return;
	}

	for ( int i = 0 ; i < m_symbolTypeOfCreate.GetSize() ; ++i)
	{
		if (type == m_symbolTypeOfCreate.GetAt(i))
		{
			m_comboSelType.SetCurSel(i);
		}
	}

	m_currentSymbolType = type;
}

void CDlgSymbolEdit::SetSymbolUnit(SYSTEM::SYS_UNIT_TYPE symbolUnit)
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

void CDlgSymbolEdit::LoadConfig(void)
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
		if( atoi(pSymConfig->GetChilds(i)->GetProperties("SymbolType")) == (int)m_editDlgManager.GetSymbol()->GetType() )
		{
			pSymConfigItem = pSymConfig->GetChilds(i);
			break;
		}
	}

	if( pSymConfigItem == NULL )
		return;
//		OTFALSERETURN_NOVAL("Error:Can't find the node of the symbol from XML file")

		//
		//m_comboSelType.
		SYSTEM::SYS_UNIT_TYPE curType = (SYSTEM::SYS_UNIT_TYPE)(m_editDlgManager.GetSymbol()->GetType() & 0x3F0);
	for( int i = 0 ; i < pSymConfig->GetChildCount() ; i++ )
	{
		SYSTEM::SYS_UNIT_TYPE sType = (SYSTEM::SYS_UNIT_TYPE)atoi( pSymConfig->GetChilds(i)->GetProperties("SymbolType") );
		if( sType & curType )
		{
			m_comboSelType.AddString( pSymConfig->GetChilds(i)->GetProperties("Name") );
			m_symbolTypeOfCreate.Add(sType);

			if( sType == m_editDlgManager.GetSymbol()->GetType() )
			{
				m_comboSelType.SetCurSel( m_comboSelType.GetCount() - 1 );
				m_currentSymbolType = sType;
			}
		}
	}

	CRect rectPropList;
	GetDlgItem(IDC_PROPLIST)->GetClientRect (&rectPropList);
	GetDlgItem(IDC_PROPLIST)->MapWindowPoints (this, &rectPropList);

	//更新单位下拉列表与符号单位一致
	SetSymbolUnit( m_editDlgManager.GetSymbol()->GetUnit());
	//

	m_wndPropList.InitWindow( rectPropList , this , -1 );
	m_wndPropList.SetSymbolPropListInterface( &m_editDlgManager );	//需要在初始设置符号前，装入接口管理类
	m_wndPropList.InitSymbolPropList( m_editDlgManager.GetSymbol()->GetType() );
	m_wndPropList.SetSymbol( m_editDlgManager.GetSymbol() );
}

Display::ISymbolPtr CDlgSymbolEdit::EditSymbol(Display::ISymbolPtr pSymbol)
{
	SetSymbol( pSymbol );
	INT_PTR result = this->DoModal();

	if ( result == IDOK ) 
	{
		Display::IComplexSymbolPtr complexSymbol = m_editDlgManager.m_pComplexSymbol;
		int size = complexSymbol->GetSize();
		if ( size > 1 )
		{
			return complexSymbol;
		}

		return complexSymbol->GetAt(0);
	} 
	else
	{
		return m_editDlgManager.m_pStandbyCopySymbol;
	}

	return 0;
}
void CDlgSymbolEdit::OnBnClickedStrLine()
{
	m_bSolid = TRUE;
	OnCbnSelchangeZoom();
}

void CDlgSymbolEdit::OnBnClickedCrLine()
{
	m_bSolid = FALSE ;
	OnCbnSelchangeZoom();
}

void CDlgSymbolEdit::OnBnClickedCrossline()
{
	if( m_btCRossLine.GetCheck()==0 )
	{
		m_bDraw = FALSE;
		ShowSymbol();
	}
	else if( m_btCRossLine.GetCheck()==1 )
	{
		m_bDraw = TRUE;
		OnCbnSelchangeZoom();
	}
}

void CDlgSymbolEdit::OnBnClickedReduce()
{
	int index=m_cComboBoxZoom.GetCurSel()+1;

	if(index<=3)
	{
		m_cComboBoxZoom.SetCurSel(index);
		UpdateData(TRUE);
		OnCbnSelchangeZoom();
	}
}

void CDlgSymbolEdit::OnCbnSelchangeZoom()
{
	int nSize=m_cComboBoxZoom.GetCurSel();
	m_editDlgManager.m_pSymbolCopy = m_editDlgManager.m_pComplexSymbol->Clone();
	switch(nSize)
	{
	case 0:
		m_editDlgManager.m_pSymbolCopy->Zoom(4.0f);

		break;
	case 1:
		m_editDlgManager.m_pSymbolCopy->Zoom(2.0f);

		break;
	case 2:
		m_editDlgManager.m_pSymbolCopy->Zoom(1.0f);

		break;
	case 3:
		m_editDlgManager.m_pSymbolCopy->Zoom(0.5f);

		break;
	}

	ShowSymbol();
}

void CDlgSymbolEdit::OnCbnSelchangeCombounits()
{
	// TODO: 在此添加控件通知处理程序代码
	int selectIndex = m_UnitCombo.GetCurSel();
	if ( selectIndex == m_UnitComboIndex )
	{
		return;
	}

	m_UnitComboIndex = selectIndex;

	Display::ISymbolPtr symbol = (( Display::IComplexSymbolPtr )(m_editDlgManager.m_pComplexSymbol))->GetAt(m_editDlgManager.GetSelect());
	if (selectIndex == 0)
	{

		symbol->SetUnit(SYSTEM::SYS_UNIT_PIXEL);
	}
	else if (selectIndex == 1)
	{
		symbol->SetUnit(SYSTEM::SYS_UNIT_MILLIMETER);
	}
	else if (selectIndex == 2)
	{
		symbol->SetUnit(SYSTEM::SYS_UNIT_CENTIMETER);
	}
	else if (selectIndex == 3)
	{
		symbol->SetUnit(SYSTEM::SYS_UNIT_DECIMETER);
	}
	else if (selectIndex == 4)
	{
		symbol->SetUnit(SYSTEM::SYS_UNIT_POINT);
	}

	m_wndPropList.InitSymbolPropList( symbol->GetType() );
	m_wndPropList.SetSymbol( symbol );
}

void CDlgSymbolEdit::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CDlgSymbolEdit::OnCbnSelchangeComboSymtype()
{
	int selectIndex = m_comboSelType.GetCurSel();
	int aimOfSymbolType = m_symbolTypeOfCreate.GetAt(selectIndex);
	if ( aimOfSymbolType == m_currentSymbolType )
	{
		return;
	}
	Display::ISymbolPtr aimOfSymbol;
	if (aimOfSymbolType & EXT_SYMBOL)
	{
		CString extSymbolName;
		m_comboSelType.GetWindowText(extSymbolName);
		CString extSymbolNameNew = extSymbolName;
		Display::IExtSymbolPtr extSymbol = Display::CSymbolFactory::CreateExtSymbol(std::string(extSymbolNameNew));
		aimOfSymbol = extSymbol;
	}
	else
		aimOfSymbol = Display::CSymbolFactory::CreateSymbol((SYMBOL_TYPE)aimOfSymbolType);

	if (aimOfSymbol == NULL)
	{
		::MessageBox(this->m_hWnd , "创建失败!请检查符号文件,或重新安装" , "错误" , MB_OK);
		return;
	}
	int unitIndex = m_UnitCombo.GetCurSel();

	if ( unitIndex == 0)
	{
		aimOfSymbol->SetUnit(SYSTEM::SYS_UNIT_PIXEL);
	}
	else if (unitIndex == 1)
	{
		aimOfSymbol->SetUnit(SYSTEM::SYS_UNIT_MILLIMETER);
	}
	else if (unitIndex == 2)
	{
		aimOfSymbol->SetUnit(SYSTEM::SYS_UNIT_CENTIMETER);
	}
	else if (unitIndex == 3)
	{
		aimOfSymbol->SetUnit(SYSTEM::SYS_UNIT_DECIMETER);
	}
	else if (unitIndex == 4)
	{
		aimOfSymbol->SetUnit(SYSTEM::SYS_UNIT_POINT);
	}

	m_editDlgManager.SetSymbol(aimOfSymbol);

	m_editDlgManager.OnSymbolPropChanged( aimOfSymbol , this );

	m_editDlgManager.ReSetSymboltoPropList(aimOfSymbol);

	m_currentSymbolType = aimOfSymbolType;
}
void CDlgSymbolEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	__super::OnMouseMove(nFlags, point);

	if( m_wndPropList.m_bCurrentForce )
	{
		this->SetFocus();
		m_wndPropList.m_bCurrentForce = false;
	}
}
