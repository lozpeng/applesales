// DlgFRField.cpp : 实现文件
//

#include "stdafx.h"
#include "Map.h"
#include "resource.h"
#include "AttributeTable.h"
#include "DlgFRField.h"
#include <algorithm>

//Finder
Finder::Finder()
{
	m_table = NULL;

	posBegin.nRow = -1;
	posBegin.nColumn = -1;
	posEnd.nRow = -1;
	posEnd.nColumn = -1;

	m_iCurIndex = -1;

	m_lpszContent = "";

	m_bIsCap = false;

	m_bIsWholeField = true;
}

Finder::~Finder()
{

}

bool Finder::Inite( Control::CAttributeTable *table, 
				   LIST_POS &posB, 
				   LIST_POS &posE, 
				   const char* szFind, 
				   bool bIsCap,
				   bool bIsWholeField )
{
	m_table = table;
	posBegin.nRow = posB.nRow;
	posBegin.nColumn = posB.nColumn;
	posEnd.nRow = posE.nRow;
	posEnd.nColumn = posE.nColumn;
	m_lpszContent = szFind;
	m_bIsCap = bIsCap;
	m_bIsWholeField = bIsWholeField;

	if ( !Find() )
		return false;

	//m_iCurIndex
	return true;
}

bool Finder::IsEmpty()
{
	if ( m_vecResultPos.size() == 0)
		return true;

	return false;
}

LIST_POS& Finder::NextPos( int iDir )
{
	if( IsEmpty() )
		return LIST_POS( -1, -1 );

	if ( m_iCurIndex == -1)
	{
		switch( iDir )
		{
		case 0:
			m_iCurIndex = 0;
			break;
		case 1:
			m_iCurIndex = 0;
			break;
		case 2:
			m_iCurIndex = m_vecResultPos.size() - 1;
			break;
		default:
			m_iCurIndex = -1;
		}	

	}
	else
	{
		switch( iDir )
		{
		case 0:
			{
				m_iCurIndex = ( ++m_iCurIndex ) % (m_vecResultPos.size());
			}
			break;
		case 1:
			{
				if ( m_iCurIndex >= m_vecResultPos.size() -1 )
					return LIST_POS( -1, -1 );
				else
					m_iCurIndex++;
			}
			break;
		case 2:
			{
				if ( m_iCurIndex <= 0 )
					return LIST_POS( -1, -1 );
				else
					m_iCurIndex--;
			}
			break;
		default:
			return LIST_POS( -1, -1);
		}
	}
	
	return m_vecResultPos[ m_iCurIndex ];
}

bool Finder::Find()
{
	m_vecResultPos.clear();

	if ( m_table == NULL )
		return false;
	
	if ( posBegin.nRow < 0 
		|| posBegin.nColumn < 0 
		|| posEnd.nColumn < 0 
		|| posEnd.nRow < 0 )
		return false;

	//在AttibuteTable中查询匹配项 	
	for ( int i = posBegin.nRow; i <= posEnd.nRow; i++ )
	{
		CBCGPGridRow *pRow = m_table->GetRow( i );
		for( int j = posBegin.nColumn; j <= posEnd.nColumn; j++ )
		{
			CBCGPGridItem *pItem = pRow->GetItem( j );
			CString strLabel = pItem->GetLabel();
			
			//比较字符串	
			std::string szCompareTgt = m_lpszContent;
			std::string szCompareSrc = strLabel.GetBuffer();
			
			if ( !m_bIsCap ) //是否区分大小写 
			{
				std::transform( szCompareTgt.begin(), szCompareTgt.end(), szCompareTgt.begin(), tolower );
				std::transform( szCompareSrc.begin(), szCompareSrc.end(), szCompareSrc.begin(), tolower);
			}

			if ( szCompareTgt == "" && szCompareSrc != "")
				continue;
				
			if ( m_bIsWholeField  && szCompareSrc.compare( szCompareTgt ) == 0 ) //是否全字匹配
				m_vecResultPos.push_back( LIST_POS( i, j ) );
			else if ( !m_bIsWholeField && szCompareTgt != "" && szCompareSrc.find( szCompareTgt ) !=  std::string::npos )
				m_vecResultPos.push_back( LIST_POS( i, j ) );
			else
				continue;
		}
	}

	//查找结果为空
	if ( m_vecResultPos.size() == 0 )
		return false;

	return true;
}

bool Finder::HasQueryResult()
{
	return ( m_iCurIndex == -1 ? false : true );
}


//Replacer
Replacer::Replacer()
{
	m_finder = NULL;
	m_lpszRelpace = "";
}

Replacer::~Replacer()
{

}
void Replacer::Inite( Finder *finder, const char* lpszReplace )
{
	m_finder = finder;
	m_lpszRelpace = lpszReplace;
}

bool Replacer::Replace()
{
	if ( m_finder->IsEmpty() )
		return false;

	if ( m_finder->m_iCurIndex == - 1)
		return false;
	
	LIST_POS pos = m_finder->m_vecResultPos[ m_finder->m_iCurIndex ];

	CBCGPGridRow *pRow = m_finder->m_table->GetRow( pos.nRow );
	CBCGPGridItem *pItem = pRow->GetItem( pos.nColumn );
	
	_variant_t val = pItem->GetValue();

	if ( m_finder->m_bIsWholeField )
	{
		val.SetString( m_lpszRelpace.c_str() );
		pItem->SetValue( val, TRUE );
	}
	else
	{
		CString strOldLabel = pItem->GetLabel();
		std::string szOldLabel = strOldLabel.GetBuffer();

		std::string::size_type i = szOldLabel.find( m_finder->m_lpszContent );
		if( i != std::string::npos)
		{
			szOldLabel.replace( i, strlen( m_finder->m_lpszContent.c_str() ), m_lpszRelpace, 0, strlen( m_lpszRelpace.c_str() ) );
			i = szOldLabel.find( m_finder->m_lpszContent );
		}

		val.SetString( szOldLabel.c_str() );
		pItem->SetValue( val, TRUE );
	}

	m_finder->m_table->ChangeFeatureFromListItem( pItem, pos.nRow, pos.nColumn );
	
	m_finder->m_vecResultPos.erase( m_finder->m_vecResultPos.begin() + m_finder->m_iCurIndex );
	m_finder->m_iCurIndex--;

	return true;
}

bool Replacer::ReplaceAll()
{
	if ( m_finder->IsEmpty() )
		return false;
	
	for ( int i = 0; i < m_finder->m_vecResultPos.size(); i++ )
	{
		LIST_POS pos = m_finder->m_vecResultPos[i];

		CBCGPGridRow *pRow = m_finder->m_table->GetRow( pos.nRow );
		CBCGPGridItem *pItem = pRow->GetItem( pos.nColumn );

		_variant_t val = pItem->GetValue();
		if ( m_finder->m_bIsWholeField )
		{
			val.SetString( m_lpszRelpace.c_str() );
			pItem->SetValue( val, TRUE );
		}
		else
		{
			CString strOldLabel = pItem->GetLabel();
			std::string szOldLabel = strOldLabel.GetBuffer();

			std::string::size_type i = szOldLabel.find( m_finder->m_lpszContent );
			while ( i != std::string::npos)
			{
				szOldLabel.replace( i, strlen( m_finder->m_lpszContent.c_str() ), m_lpszRelpace, 0, strlen( m_lpszRelpace.c_str() ) );
				i = szOldLabel.find( m_finder->m_lpszContent );
			}

			val.SetString( szOldLabel.c_str() );
			pItem->SetValue( val, TRUE );
		}

		m_finder->m_table->ChangeFeatureFromListItem( pItem, pos.nRow, pos.nColumn );
	}

	m_finder->m_vecResultPos.clear();
	m_finder->m_iCurIndex = -1;

	return true;
}

// CDlgFRField 对话框

//查找和替换列表项


IMPLEMENT_DYNAMIC(CDlgFRField, CDialog)

CDlgFRField::CDlgFRField(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFRField::IDD, pParent)
	,m_strFindContent(_T(""))
	,m_strMatchCondition(_T(""))
	,m_strLastFindContent(_T(""))
	,m_strReplaceContent(_T(""))
	,m_bIsMatchCap(FALSE)
{
	m_bLastMathCap = FALSE;

	m_strLastMathConditon = "";
}

CDlgFRField::~CDlgFRField()
{
}

void CDlgFRField::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_CMB_FINDCONTENT, m_strFindContent);
	DDX_Control(pDX, IDC_CMB_FINDCONTENT, m_cmbFindContent);
	DDX_Control(pDX, IDC_CMB_MATCHCONDITION, m_cmbMatchConditon);
	DDX_Control(pDX, IDC_CMB_FINDDIRECTION, m_cmbFindDirection);
	DDX_Control(pDX, IDC_CMB_REPLACECONTENT, m_cmbReplaceContent);
	DDX_Control(pDX, IDC_BTN_REPLACE, m_btnReplace);
	DDX_Control(pDX, IDC_BTN_REPLACEALL, m_btnReplaceAll);
	DDX_CBString(pDX, IDC_CMB_REPLACECONTENT, m_strReplaceContent);
	DDX_CBString(pDX, IDC_CMB_MATCHCONDITION, m_strMatchCondition);
	DDX_Check(pDX, IDC_CHK_MATCHCAPS, m_bIsMatchCap);
	DDX_Control(pDX, IDC_TAB_FIND_REPLACE, m_tabFindReplace);
}


BEGIN_MESSAGE_MAP(CDlgFRField, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_FIND_REPLACE, &CDlgFRField::OnTcnSelchangeTabFindReplace)
	ON_BN_CLICKED(IDC_BTN_NEXT, &CDlgFRField::OnBnClickedBtnNext)
	ON_BN_CLICKED(IDC_BTN_REPLACE, &CDlgFRField::OnBnClickedBtnReplace)
	ON_BN_CLICKED(IDC_BTN_REPLACEALL, &CDlgFRField::OnBnClickedBtnReplaceall)
END_MESSAGE_MAP()


// CDlgFRField 消息处理程序
BOOL CDlgFRField::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化界面设置 
	m_tabFindReplace.InsertItem( 0, _T("查找") );
	m_tabFindReplace.InsertItem( 1, _T("替换") );
	m_tabFindReplace.SetCurSel( 0 );

	m_cmbReplaceContent.ShowWindow( SW_HIDE );
	m_btnReplace.ShowWindow( SW_HIDE );
	m_btnReplaceAll.ShowWindow( SW_HIDE );
	GetDlgItem( IDC_LABLE_REPLACE )->ShowWindow( SW_HIDE );

	m_cmbMatchConditon.AddString( _T("部分匹配") );
	m_cmbMatchConditon.AddString( _T("全字匹配") );
	m_cmbMatchConditon.SetCurSel( 0 );

	m_cmbFindDirection.AddString( _T("全部") );
	m_cmbFindDirection.AddString( _T("向下") );
	m_cmbFindDirection.AddString( _T("向上") );
	m_cmbFindDirection.SetCurSel( 0 );
	
	Control::CAttributeTable *pAttrTable = dynamic_cast<Control::CAttributeTable*>( Framework::IAttributeTable::GetActiveAttributeTable() );
	m_btnReplace.EnableWindow( pAttrTable->IsEditMode() );
	m_btnReplaceAll.EnableWindow( pAttrTable->IsEditMode() );
	m_cmbReplaceContent.EnableWindow( pAttrTable->IsEditMode() );

	UpdateCmbFindContent();

	UpdateCmbReplaceContent();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgFRField::OnTcnSelchangeTabFindReplace(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_tabFindReplace.GetCurSel() == 0)
	{
		m_cmbReplaceContent.ShowWindow( SW_HIDE );
		m_btnReplace.ShowWindow( SW_HIDE );
		m_btnReplaceAll.ShowWindow( SW_HIDE );
		GetDlgItem( IDC_LABLE_REPLACE )->ShowWindow( SW_HIDE );
	}
	else
	{
		m_cmbReplaceContent.ShowWindow( SW_SHOW );
		m_btnReplace.ShowWindow(  SW_SHOW );
		m_btnReplaceAll.ShowWindow(  SW_SHOW );
		GetDlgItem( IDC_LABLE_REPLACE )->ShowWindow( SW_SHOW );
	}

	*pResult = 0;
}
std::vector<CString> CDlgFRField::m_slpszFindcontent;
std::vector<CString> CDlgFRField::m_slpszReplacecontent;

void CDlgFRField::OnBnClickedBtnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData( TRUE );

	Control::CAttributeTable *pAttrTable = dynamic_cast<Control::CAttributeTable*>( Framework::IAttributeTable::GetActiveAttributeTable() );
	if ( m_strFindContent != m_strLastFindContent
		|| m_strMatchCondition != m_strLastMathConditon
		|| m_bIsMatchCap != m_bLastMathCap 
		|| !m_Finder.HasQueryResult() )
	{
		bool bIsWholeField = ( m_cmbMatchConditon.GetCurSel() == 0 ? false : true ); 
		
		m_Finder.Inite( pAttrTable, LIST_POS(0,0), LIST_POS(pAttrTable->GetRecordCount() - 1, pAttrTable->GetColumnCount() -1), m_strFindContent, m_bIsMatchCap, bIsWholeField );
	}
	
	LIST_POS pos = m_Finder.NextPos( m_cmbFindDirection.GetCurSel() );
	if ( pos.nColumn == -1 || pos.nRow == -1 )
	{
		CString szMsg;
		szMsg.Format(_T("没有找到%s!"), m_strFindContent);
		AfxMessageBox( szMsg );
	}
	else
	{
		pAttrTable->SetCurSel( CBCGPGridItemID( pos.nRow, pos.nColumn) );
		
		//调整垂直滚动条的位置
		CScrollBar *pScrollBar = pAttrTable->GetScrollBarCtrl( SB_VERT );
		int iMin, iMax;	
		pScrollBar->GetScrollRange( &iMin, &iMax );
		int nPosVer = iMin + ( iMax - iMin ) *  pos.nRow / pAttrTable->GetRecordCount();
		pScrollBar->SetScrollPos( nPosVer );
		::SendMessage( pAttrTable->CBCGPGridCtrl::m_hWnd, WM_VSCROLL, MAKEWPARAM(SB_THUMBPOSITION, 0), 0 );
	}

	//缓存查找过的字符串	
	if( std::find( m_slpszFindcontent.begin(), m_slpszFindcontent.end(), m_strFindContent ) == m_slpszFindcontent.end() )
	{
		if ( m_slpszFindcontent.size() >= 10  )
			m_slpszFindcontent.erase( m_slpszFindcontent.begin() );

		m_slpszFindcontent.push_back( CString(m_strFindContent) );

		UpdateCmbFindContent();
	}
	
	m_strLastFindContent = m_strFindContent;
	m_strLastMathConditon = m_strMatchCondition;
	m_bLastMathCap = m_bIsMatchCap;
	UpdateData( FALSE );
}

void CDlgFRField::OnBnClickedBtnReplace()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData( TRUE );
	
	Control::CAttributeTable *pAttrTable = dynamic_cast<Control::CAttributeTable*>( Framework::IAttributeTable::GetActiveAttributeTable() );
	
	if ( m_strFindContent != m_strLastFindContent
		|| m_strMatchCondition != m_strLastMathConditon
		|| m_bIsMatchCap != m_bLastMathCap 
		|| !m_Finder.HasQueryResult() )
	{
		bool bIsWholeField = ( m_cmbMatchConditon.GetCurSel() == 0 ? false : true ); 
		m_Finder.Inite( pAttrTable, LIST_POS(0,0), LIST_POS(pAttrTable->GetRecordCount() - 1, pAttrTable->GetColumnCount() -1), m_strFindContent, m_bIsMatchCap, bIsWholeField );

		LIST_POS pos = m_Finder.NextPos( m_cmbFindDirection.GetCurSel() );
		if ( pos.nColumn == -1 || pos.nRow == -1 )
		{
			CString szMsg;
			szMsg.Format(_T("没有找到%s!"), m_strFindContent);
			AfxMessageBox( szMsg );
		}
		else
		{
			pAttrTable->SetCurSel( CBCGPGridItemID( pos.nRow, pos.nColumn) );
			
			//调整垂直滚动条的位置
			CScrollBar *pScrollBar = pAttrTable->GetScrollBarCtrl( SB_VERT );
			int iMin, iMax;	
			pScrollBar->GetScrollRange( &iMin, &iMax );
			int nPosVer = iMin + ( iMax - iMin ) *  pos.nRow / pAttrTable->GetRecordCount();
			pScrollBar->SetScrollPos( nPosVer );
			::SendMessage( pAttrTable->CBCGPGridCtrl::m_hWnd, WM_VSCROLL, MAKEWPARAM(SB_THUMBPOSITION, 0), 0 );

			m_Replacer.Inite( &m_Finder, m_strReplaceContent );
			m_Replacer.Replace();
		}
	}
	else
	{
		m_Replacer.Inite( &m_Finder, m_strReplaceContent );
		bool bDoReplace = m_Replacer.Replace();

		LIST_POS pos = m_Finder.NextPos( m_cmbFindDirection.GetCurSel() );
		if ( bDoReplace && ( pos.nColumn == -1 || pos.nRow == -1 ) )
		{
			CString szMsg;
			szMsg.Format(_T("没有找到%s!"), m_strFindContent);
			AfxMessageBox( szMsg );
		}
		else
		{
			pAttrTable->SetCurSel( CBCGPGridItemID( pos.nRow, pos.nColumn) );
			
			//调整垂直滚动条的位置
			CScrollBar *pScrollBar = pAttrTable->GetScrollBarCtrl( SB_VERT );
			int iMin, iMax;	
			pScrollBar->GetScrollRange( &iMin, &iMax );
			int nPosVer = iMin + ( iMax - iMin ) *  pos.nRow / pAttrTable->GetRecordCount();
			pScrollBar->SetScrollPos( nPosVer );
			::SendMessage( pAttrTable->CBCGPGridCtrl::m_hWnd, WM_VSCROLL, MAKEWPARAM(SB_THUMBPOSITION, 0), 0 );
		}
	}

	//缓存查找过的字符串	
	if( std::find( m_slpszReplacecontent.begin(), m_slpszReplacecontent.end(), m_strReplaceContent ) == m_slpszReplacecontent.end() )
	{
		if ( m_slpszReplacecontent.size() >= 10  )
			m_slpszReplacecontent.erase( m_slpszReplacecontent.begin() );

		m_slpszReplacecontent.push_back( CString(m_strReplaceContent) );
		
		UpdateCmbReplaceContent();
	}
	
	UpdateData( FALSE );
}

void CDlgFRField::OnBnClickedBtnReplaceall()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData( TRUE );

	Control::CAttributeTable *pAttrTable = dynamic_cast<Control::CAttributeTable*>( Framework::IAttributeTable::GetActiveAttributeTable() );

	if ( m_strFindContent != m_strLastFindContent
		|| m_strMatchCondition != m_strLastMathConditon
		|| m_bIsMatchCap != m_bLastMathCap 
		|| !m_Finder.HasQueryResult() )
	{
		bool bIsWholeField = ( m_cmbMatchConditon.GetCurSel() == 0 ? false : true ); 
			
		m_Finder.Inite( pAttrTable, LIST_POS(0,0), LIST_POS(pAttrTable->GetRecordCount() - 1, pAttrTable->GetColumnCount() -1), m_strFindContent, m_bIsMatchCap, bIsWholeField );
	}
	
	if ( !m_Finder.IsEmpty() )
	{
		m_Replacer.Inite( &m_Finder, m_strReplaceContent );
		m_Replacer.ReplaceAll();
	}
	else
	{
		CString szMsg;
		szMsg.Format(_T("没有找到%s!"), m_strFindContent);
		AfxMessageBox( szMsg );
	}

	//缓存查找过的字符串	
	if( std::find( m_slpszReplacecontent.begin(), m_slpszReplacecontent.end(), m_strReplaceContent ) == m_slpszReplacecontent.end() )
	{
		if ( m_slpszReplacecontent.size() >= 10  )
			m_slpszReplacecontent.erase( m_slpszReplacecontent.begin() );

		m_slpszReplacecontent.push_back( CString(m_strReplaceContent) );

		UpdateCmbReplaceContent();
	}
	
	UpdateData( FALSE );
}

void CDlgFRField::UpdateCmbFindContent()
{
	m_cmbFindContent.ResetContent();
	for ( int i = 0; i < m_slpszFindcontent.size(); i++ )
		m_cmbFindContent.AddString( _T( m_slpszFindcontent[i] ) );
}

void CDlgFRField::UpdateCmbReplaceContent()
{
	m_cmbReplaceContent.ResetContent();
	for ( int i = 0; i < m_slpszReplacecontent.size(); i++ )
		m_cmbReplaceContent.AddString( _T( m_slpszReplacecontent[i] ) );	
}

