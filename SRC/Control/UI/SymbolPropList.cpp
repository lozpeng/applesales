// SymbolPropList.cpp : 实现文件
//

#include "stdafx.h"
#include "SymbolPropList.h"
#include "SpinButtonCtrlEx.h"
#include "SymbolSelectDlg.h"
#include "SymbolFactory.h"
#include "DashArrayDlg.h"
#include "CharSymbolSelectDlg.h"
#include "IComplexSymbol.h"
#include "IExtSymbol.h"

#define PROP_HAS_LIST	0x0001
#define PROP_HAS_BUTTON	0x0002
#define PROP_HAS_SPIN	0x0004
//////////////////////////////////////////////////////////////////////////
CBCGPFontSelectProp::CBCGPFontSelectProp(const CString& strGroupName, DWORD dwData ,
										 BOOL bIsValueList ):	CBCGPProp (strGroupName, dwData, bIsValueList)
{
	m_dwFlags = PROP_HAS_LIST;
}


CBCGPFontSelectProp::CBCGPFontSelectProp(const CString& strName, const _variant_t& varValue, 
										 LPCTSTR lpszDescr , DWORD dwData ,
										 LPCTSTR lpszEditMask , LPCTSTR lpszEditTemplate ,
										 LPCTSTR lpszValidChars ):	CBCGPProp (strName, varValue, 
										 lpszDescr, dwData,lpszEditMask,lpszEditTemplate,lpszValidChars)
{
	m_dwFlags = PROP_HAS_LIST;
}

CComboBox* CBCGPFontSelectProp::CreateCombo (CWnd* pWndParent, CRect rect)
{
	ASSERT_VALID (this);

	rect.bottom = rect.top + 400;

	CWaitCursor cursor;
	CBCGPFontComboBox* pWndCombo = new CBCGPFontComboBox;
	if (!pWndCombo->Create (WS_CHILD | CBS_NOINTEGRALHEIGHT | CBS_DROPDOWNLIST | WS_VSCROLL, 
		rect, pWndParent, BCGPROPLIST_ID_INPLACE))
	{
		delete pWndCombo;
		return NULL;
	}
	pWndCombo->Setup( TRUETYPE_FONTTYPE | RASTER_FONTTYPE | DEVICE_FONTTYPE );

	pWndCombo->SelectFont ((_bstr_t)m_varValue);

	return pWndCombo;
}

//////////////////////////////////////////////////////////////////////////
CCustomDlgProp::CCustomDlgProp( const CString& strName , const _variant_t& varValue , LPCTSTR lpszDescr , DWORD dwData) :CBCGPProp(strName , varValue , lpszDescr ,dwData)
{

}

void CCustomDlgProp::OnClickButton (CPoint point)
{

}
//////////////////////////////////////////////////////////////////////////
CCharSymbolSelectProp::CCharSymbolSelectProp( CSymbolPropList* propList , const CString& strName , const _variant_t& varValue , LPCTSTR lpszDescr , DWORD dwData ) : CCustomDlgProp(strName , varValue ,lpszDescr , dwData)
{
	m_pPropList = propList;
}

void CCharSymbolSelectProp::OnClickButton (CPoint point)
{
	if ( m_pPropList == NULL)
	{
		return;
	}

	CCharSymbolSelectDlg selDlg;

	selDlg.SetSymbolSelectProp(this);
	selDlg.SetCharMarkSymbol(m_pPropList->m_pSymbol);
	INT_PTR nResponse = selDlg.DoModal();
	if (nResponse == IDOK)
	{
		m_pWndList->OnPropertyChanged (this);
	}
}

int CCharSymbolSelectProp::GetMaxValue()
{
	return m_nMaxValue;
}

int CCharSymbolSelectProp::GetMinValue()
{
	return m_nMinValue;
}

//////////////////////////////////////////////////////////////////////////
CBCGPFilePropEx::CBCGPFilePropEx(const CString& strName, const CString& strFolderName, DWORD dwData , LPCTSTR lpszDescr )
: CBCGPFileProp(strName , strFolderName , dwData , lpszDescr)
{

}
CBCGPFilePropEx::CBCGPFilePropEx(const CString& strName, BOOL bOpenFileDialog, const CString& strFileName, LPCTSTR lpszDefExt ,
								 DWORD dwFlags ,LPCTSTR lpszFilter ,LPCTSTR lpszDescr , DWORD dwData ) : CBCGPFileProp(strName ,
								 bOpenFileDialog , strFileName , lpszDefExt , dwFlags , lpszFilter , lpszDescr , dwData)
{

}
CBCGPFilePropEx::~CBCGPFilePropEx()
{

}

void CBCGPFilePropEx::OnClickButton (CPoint point)
{
	char m_cCurrentPath[512];
	DWORD dwRet = GetCurrentDirectory(512, m_cCurrentPath);
	if(dwRet==0)
	{
		MessageBox(AfxGetApp()->GetMainWnd()->m_hWnd , "得到当前路径错误！" , "错误" , MB_OK);
		return;
	}
	if(dwRet > 512)
	{
		MessageBox(AfxGetApp()->GetMainWnd()->m_hWnd , "当前运行路径过长，请重新安装程序于建议路径！"  , "错误" , MB_OK);
		return;
	}
	CBCGPFileProp::OnClickButton(point);
	SetCurrentDirectory(m_cCurrentPath);
}

//////////////////////////////////////////////////////////////////////////
CBCGPPropEx::CBCGPPropEx(const CString& strGroupName, DWORD dwData ,
						 BOOL bIsValueList ):	CBCGPProp (strGroupName, dwData, bIsValueList)
{

}


CBCGPPropEx::CBCGPPropEx(const CString& strName, const _variant_t& varValue, 
						 LPCTSTR lpszDescr , DWORD dwData ,
						 LPCTSTR lpszEditMask , LPCTSTR lpszEditTemplate ,
						 LPCTSTR lpszValidChars ):	CBCGPProp (strName, varValue, 
						 lpszDescr, dwData,lpszEditMask,lpszEditTemplate,lpszValidChars)
{

}

CBCGPPropEx::~CBCGPPropEx()
{

}

BOOL CBCGPPropEx::OnClickValue (UINT uiMsg, CPoint point)
{
	return CBCGPProp::OnClickValue( uiMsg , point );
}

int CBCGPPropEx::GetMaxValue()
{
	return m_nMaxValue;
}

int CBCGPPropEx::GetMinValue()
{
	return m_nMinValue;
}

void CBCGPPropEx::EnableSpinControl (BOOL bEnable, int nMin , int nMax )
{
	ASSERT_VALID (this);

	switch (m_varValue.vt)
	{
	case VT_INT:
	case VT_UINT:
	case VT_I2:
	case VT_I4:
	case VT_UI2:
	case VT_UI4:
	case VT_R4:
		break;

	default:
		ASSERT (FALSE);
		return;
	}

	m_nMinValue = nMin;
	m_nMaxValue = nMax;

	if (bEnable)
	{
		m_dwFlags |= PROP_HAS_SPIN;
	}
	else
	{
		m_dwFlags &= ~PROP_HAS_SPIN;
	}
}

CSpinButtonCtrl* CBCGPPropEx::CreateSpinControl (CRect rectSpin)
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pWndList);

	CSpinButtonCtrl* pWndSpin = new CSpinButtonCtrlEx(this);

	if (!pWndSpin->Create (
		WS_CHILD | WS_VISIBLE | UDS_ARROWKEYS | UDS_SETBUDDYINT | UDS_NOTHOUSANDS,
		rectSpin, m_pWndList, BCGPROPLIST_ID_INPLACE))
	{
		return NULL;
	}

	pWndSpin->SetBuddy (m_pWndInPlace);

	if (m_nMinValue != 0 || m_nMaxValue != 0)
	{
		pWndSpin->SetRange32 (m_nMinValue , m_nMaxValue);
	}

	return pWndSpin;
}

void CBCGPPropEx::Update()
{
	ASSERT_VALID (m_pWndList);
	m_pWndList->OnPropertyChanged (this);
}

CWnd* CBCGPPropEx::CreateInPlaceEdit (CRect rectEdit, BOOL& bDefaultFormat)
{
	switch (m_varValue.vt)
	{
	case VT_BSTR:
	case VT_R4:
	case VT_R8:
	case VT_UI1:
	case VT_I2:
	case VT_INT:
	case VT_UINT:
	case VT_I4:
	case VT_UI2:
	case VT_UI4:
	case VT_BOOL:
		break;

	default:
		if (!m_bIsValueList)
		{
			return NULL;
		}
	}

	CEdit* pWndEdit = NULL;

	if (!m_strEditMask.IsEmpty () || !m_strEditTempl.IsEmpty () ||
		!m_strValidChars.IsEmpty ())
	{
		CBCGPMaskEdit* pWndEditMask = new CBCGPMaskEdit;

		if (!m_strEditMask.IsEmpty () && !m_strEditTempl.IsEmpty ())
		{
			pWndEditMask->EnableMask (m_strEditMask, m_strEditTempl, _T(' '));
		}

		if (!m_strValidChars.IsEmpty ())
		{
			pWndEditMask->SetValidChars (m_strValidChars);
		}

		pWndEdit = pWndEditMask;
	}
	else
	{
		pWndEdit = new CCustomEdit( this , m_pWndList );
	}

	DWORD dwStyle = WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL;

	if (!m_bEnabled || !m_bAllowEdit)
	{
		dwStyle |= ES_READONLY;
	}

	pWndEdit->Create (dwStyle, rectEdit, m_pWndList, BCGPROPLIST_ID_INPLACE);

	bDefaultFormat = TRUE;
	return pWndEdit;
}

//////////////////////////////////////////////////////////////////////////
CSymbolProp::CSymbolProp(CWnd *pWnd , const CString& strName, _variant_t &value,
						 LPCTSTR lpszDescr, DWORD dwData)
						 :	CBCGPProp (strName, 0, lpszDescr, dwData)
{
	SetSymbol( value );
	m_pParentWnd = pWnd;
	m_varValue = (long)0;

}

void CSymbolProp::OnDrawValue (CDC* pDC, CRect rect)
{
	if( m_pSymbol != NULL  )
	{
		/*if ( IsEnabled() )
		{*/
		Display::IDisplayPtr pDisplay ( new Display::IDisplay());
		pDisplay->SetDC( (long)pDC->GetSafeHdc() , rect.Width() , rect.Height() );
		DIS_RECT rc;
		rc.left = rect.left;
		rc.top = rect.top;
		rc.right = rect.right;
		rc.bottom = rect.bottom;
		pDisplay->DrawLegend( m_pSymbol.get() , &rc , 0 );
		//}
		//else
		//{
		//	Display::IDisplayPtr pDisplay ( new Display::CSimpleDisplay() , false );

		//	/////////////////////////////////////////////////////////////////////////
		//	//RECT rc1;
		//	//rc1.left = rect.left;
		//	//rc1.top = rect.top;
		//	//rc1.right = rect.right;
		//	//rc1.bottom = rect.bottom;
		//	//HBRUSH brush = CreateSolidBrush(RGB(200 , 200 , 200));
		//	//HBRUSH oldBrush = (HBRUSH)SelectObject(pDC->GetSafeHdc() , brush);
		//	//FillRect(pDC->GetSafeHdc() , &rc1 , brush);
		//	//SelectObject(pDC->GetSafeHdc() , oldBrush);
		//	//::DeleteObject(brush);
		//	//////////////////////////////////////////////////////////////////////////
		//	pDisplay->SetDC( (long)pDC->GetSafeHdc() , rect.Width() , rect.Height() );

		//	Display::CDC* pDC = NULL;
		//	pDC = pDisplay->GetDrawDC()->CloneDC();

		//	//////////////////////////////////////////////////////////////////////////
		//	DRECT rc;
		//	rc.minX = rect.left;
		//	rc.minY = rect.top;
		//	rc.maxX = rect.right;
		//	rc.maxY = rect.bottom;
		//	pDisplay->DrawLegend( m_pSymbol , &rc , 0 );
		//	//////////////////////////////////////////////////////////////////////////
		//	DPOINT p;
		//	p.p.x = p.p.y = 0;
		//	pDC->AlphaBlend( pDisplay->GetDrawDC() , p, pDC->GetDCWidth() , pDC->GetDCHeight() , 
		//		p, pDC->GetDCWidth() , pDC->GetDCHeight()  , 128 , 0 );

		//	pDisplay->GetDrawDC()->ReleaseCloneDC( pDC );
		//}
	}
}

void CSymbolProp::OnClickButton (CPoint point)
{
	AfxGetApp()->DoWaitCursor(-1); 
	CDlgSymbolSelect Dlg;

	Dlg.SetSymbol(m_pSymbol);
	if(Dlg.DoModal()==IDOK)
	{
		m_pSymbol = Dlg.GetSymbol();

		if (m_pSymbol->GetType() & COMPLEX_SYMBOL)
		{
			Display::IComplexSymbolPtr complexSymbol = m_pSymbol;
			if (complexSymbol != NULL)
			{
				int index = complexSymbol->GetSize() - 1;
				for ( ; index >= 0 ; --index )
				{
					Display::IExtSymbolPtr pSymbol =  complexSymbol->GetAt(index);
					if ( pSymbol == NULL)
						break;
				}
				if (index >= 0)
				{
					Display::ISymbolPtr aimSymbol  = complexSymbol->GetAt(index);
					bool state = complexSymbol->IsVisible(index);
					complexSymbol->RemoveSymbol(index);
					complexSymbol->Insert(index , aimSymbol , state);
				}
			}
		}
		SYSTEM::CBinArchive ba;
		m_pSymbol->serialization( ba );
		m_symbolData = ba.ExportToVariant();

		Redraw();
		m_pWndList->OnPropertyChanged (this);
	}
	

	//SYSTEM::CStringArchive sa;
	//m_pSymbol->serialization( sa );
	//m_symbolData = sa.ExportToVariant();
}

void CSymbolProp::SetSymbol( _variant_t &vt )
{
	if( vt.vt == VT_BSTR )
	{

		SYSTEM::CStringArchive sa;
		sa.ImportVariant( vt );
		if( sa.GetSize() != 0 )
			m_pSymbol = Display::CSymbolFactory::CreateSymbolFromStream( sa );
	}
	else if( vt.vt == (VT_UI1|VT_ARRAY) )
	{
		SYSTEM::CBinArchive ba;
		ba.ImportVariant( vt );

		if( !ba.IsEOF() )
			m_pSymbol = Display::CSymbolFactory::CreateSymbolFromStream( ba );
	}
	else
		return;

	if( m_pSymbol != NULL )
	{
		SYSTEM::CStringArchive ba;
		m_pSymbol->serialization( ba );
		m_symbolData = ba.ExportToVariant();
	}
}

CString CSymbolProp::FormatProperty ()
{
	if ( m_pWndInPlace != NULL)
	{
		m_pWndInPlace->ShowWindow(SW_HIDE);
	}

	return CBCGPProp::FormatProperty();
}

Display::ISymbolPtr CSymbolProp::GetSymbol()
{
	return m_pSymbol;
}
//////////////////////////////////////////////////////////////////////////
CBCGPColorPropEx::CBCGPColorPropEx(const CString& strName, const COLORREF& color, 
								   CPalette* pPalette , LPCTSTR lpszDescr , DWORD dwData) :
CBCGPColorProp(strName , color ,pPalette , lpszDescr , dwData)
{

}

CBCGPColorPropEx::~CBCGPColorPropEx()
{

}

void CBCGPColorPropEx::OnClickButton (CPoint point)
{
	AfxGetApp()->DoWaitCursor(-1); 
	CBCGPColorProp::OnClickButton(point);
}

void CBCGPColorPropEx::InitColors (IMAGE_COLOR * imagePalette , CArray<COLORREF, COLORREF>& arColors)
{
	if (imagePalette == NULL)
	{
		// Use system palette:
		CPalette *pCPalette = CPalette::FromHandle ((HPALETTE) ::GetStockObject (DEFAULT_PALETTE));
		ASSERT_VALID (pCPalette);

		PALETTEENTRY palEntry;
		for (int i = 0; i < 20; i++)
		{
			pCPalette->GetPaletteEntries (i, 1, &palEntry);
			arColors [i] = RGB (palEntry.peRed, palEntry.peGreen, palEntry.peBlue);
		}
	}
	else
	{
		unsigned long dataCount = imagePalette->ulDataLens;
		arColors.RemoveAll();
		for ( unsigned long i =0 ; i < dataCount ; ++ i )
		{	 
			arColors.Add(imagePalette->ulData[i]);
		}
	}

}
void CBCGPColorPropEx::ReSetPalette(IMAGE_COLOR * imagePalette)
{
	CBCGPColorPropEx::InitColors (imagePalette, m_Colors);
}
//////////////////////////////////////////////////////////////////////////
CDashArrayExProp::CDashArrayExProp(const CString& strName, 
								   Display::CDashArray *dashArray,
								   LPCTSTR lpszDescr, DWORD dwData
								   )
								   :	CBCGPProp (strName, "...", lpszDescr, dwData)

{	
	m_dashArray = NULL;
	if ( dashArray != NULL )
	{
		m_dashArray = dashArray;
	}
}

void CDashArrayExProp::SetDashArray(Display::CDashArray *dashArray)
{
	if ( dashArray != NULL )
	{
		m_dashArray = dashArray;
	}
}

void CDashArrayExProp::SetSymbolType(SYMBOL_TYPE type)
{
	m_enumSymbolType = type;
}

void CDashArrayExProp::OnClickButton (CPoint point)
{

	CDashArrayDlg dlg;
	dlg.SetDashArray(m_dashArray);
	dlg.SetSymbolType(m_enumSymbolType);

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		m_pWndList->OnPropertyChanged (this);
	}
	else if (nResponse == IDCANCEL)
	{
	}
}
CDashArrayExProp::~CDashArrayExProp()
{
}
//////////////////////////////////////////////////////////////////////////
// CSymbolPropList

IMPLEMENT_DYNAMIC(CSymbolPropList, CBCGPPropList)
CSymbolPropList::CSymbolPropList()
{
	m_enumUnit = SYSTEM::SYS_UNIT_MILLIMETER;

	m_propListInterface = NULL;

	m_SymbolType = -1;

	m_bCurrentForce = false;

	m_lWide = 200.000000f;
	m_lWideNegative = -200.000000f;
	m_ulWide = 200.000000f;

	HDC dis = CreateDC( "DISPLAY" , NULL , NULL , NULL );

	m_fPelsToMmRate = (double)::GetDeviceCaps( dis , VERTSIZE )  /  (double)GetDeviceCaps( dis , VERTRES );//毫米与象素比值
	m_fMmToPelsRate = 1 / m_fPelsToMmRate;
	m_fPelsToCmRate = m_fMmToPelsRate * 0.1;
	m_fCmToPelsRate = m_fPelsToMmRate * 10;
	m_fDmToPelsRate = m_fMmToPelsRate * 0.01;
	m_fPelsToDmRate = m_fPelsToMmRate * 100;

	m_fPointToMmRate = 1/2.83464576;
	m_fMmToPointRate = 2.83464576;

	::DeleteDC(dis);
}

CSymbolPropList::~CSymbolPropList()
{
}


BEGIN_MESSAGE_MAP(CSymbolPropList, CBCGPPropList)
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// 初始化属性
void CSymbolPropList::SetUnit( SYSTEM::SYS_UNIT_TYPE newUnit)
{
	m_enumUnit = newUnit;
}

bool CSymbolPropList::InitSymbolPropList(int SymbolType) 
{
	RemoveAll();

	SYSTEM::IConfigItemPtr pSymCfg = GetSymbolConfigItem( SymbolType );
	if ( pSymCfg == NULL )
	{
		//ErrorLog("Not Found Symbol Config Item . type = "<<SymbolType);
		::MessageBox(this->GetParent()->m_hWnd , "XML文件解析失败,请重新安装！" , "错误" , MB_OK);
		return false;
	}

	int Count = pSymCfg->GetChildCount();

	for (int i = 0 ; i < Count ; i++ )
	{
		SYSTEM::IConfigItemPtr pSymItemGroupCfg = pSymCfg->GetChilds(i);
		if (pSymItemGroupCfg == NULL)
		{
			//ErrorLog("Not Found Symbol Config child Item . type = "<<SymbolType);
			::MessageBox(this->GetParent()->m_hWnd,"XML文件解析失败,请重新安装！" ,"错误" , MB_OK);
			return false;
		}
		CBCGPProp* pGroup = new CBCGPProp ( pSymItemGroupCfg->GetProperties("Name") , -1 );
		int iCount = pSymItemGroupCfg->GetChildCount();
		for (int j = 0 ; j < iCount ; j++ )
		{
			SYSTEM::IConfigItemPtr pSymItemCfg = pSymItemGroupCfg->GetChilds(j);
			if (pSymItemCfg == NULL)
			{
				continue;
			}
			CBCGPProp* pItem = GetSymbolItem( pSymItemCfg ) ;
			if (pItem != NULL)
				pGroup->AddSubItem( pItem );
		}
		AddProperty( pGroup , false , false );
	}

	m_SymbolType = SymbolType;
	m_pSymCfg = pSymCfg;
	return true;
}

// 通过类型获得配置节点
SYSTEM::IConfigItemPtr CSymbolPropList::GetSymbolConfigItem(int type)
{
	SYSTEM::XMLConfigurationPtr pConfig = Display::GetSymbolRenderConfig();
	if(pConfig == NULL)
	{
		//ErrorLog("Get symbolrender node failed.");
		return NULL;
	}

	SYSTEM::IConfigItemPtr pCfgDisplay =  pConfig->GetChildByName(DISPLAYNODE);
	if (pCfgDisplay == NULL)
	{
		::MessageBox(this->GetParent()->m_hWnd,"XML文件解析失败,请重新安装！", "错误" , MB_OK);
		return NULL;
	}

	SYSTEM::IConfigItemPtr pCfgSymbolConfig = pCfgDisplay->GetChildByName(SYMBOLCFG);
	if (pCfgSymbolConfig == NULL)
	{
		::MessageBox(this->GetParent()->m_hWnd,"XML文件解析失败,请重新安装！", "错误" , MB_OK);
		return NULL;
	}

	long Count = pCfgSymbolConfig->GetChildCount();
	for(int i = 0 ; i < Count ; i++ )
	{
		SYSTEM::IConfigItemPtr pCfgSymbol =pCfgSymbolConfig->GetChilds(i);
		if (pCfgSymbol == NULL)
		{
			::MessageBox(this->GetParent()->m_hWnd,"XML文件解析失败,请重新安装！" , "错误", MB_OK);
			return NULL;
		}
		int SymType = atoi(pCfgSymbol->GetProperties("SymbolType"));
		if ( type == SymType )
		{
			return pCfgSymbol;
		}
	}

	return NULL;
}

#define PROPNAME m_pSymCfgItems.Add(pItemCfg)
// 通过一个配置节点，创建一个属性配置项
CBCGPProp* CSymbolPropList::GetSymbolItem(SYSTEM::IConfigItemPtr pItemCfg)
{
	if(stricmp( pItemCfg->GetProperties("Type") , "long" ) == 0)
	{

		float Value = atoi(pItemCfg->GetProperties("DefaultValue"));
		float wide = 32767.000000;
		/*if( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL)
			;
		else */if( m_enumUnit == SYSTEM::SYS_UNIT_CENTIMETER )
		{
			wide = 1155.000000;
		}
		else if( m_enumUnit == SYSTEM::SYS_UNIT_MILLIMETER )
		{
			wide = 11559.000000;
		}
		else if( m_enumUnit == SYSTEM::SYS_UNIT_DECIMETER )
		{
			wide = 115.000000;
		}
		else if( m_enumUnit == SYSTEM::SYS_UNIT_POINT )
		{
			wide = 32765.000000;
		}

		const char *p = NULL;
		float value1 = 0;

		p = pItemCfg->GetProperties("MinValue");
		if( p != NULL ) 
		{
			value1 = atoi(p);
		}

		if ( wide < Value)
		{
			Value = wide;
		}
		else if( Value < -wide )
		{
			Value = - wide;
		}

		if (p != NULL)
		{
			if (Value < value1)
			{
				Value = value1;
			}
		}

		CBCGPPropEx* pItem = 0;
		/*if( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL )
		{
		pItem = new CBCGPPropEx ( 
		CString(pItemCfg->GetProperties("Name")) , 
		(long)Value , 
		CString(pItemCfg->GetProperties("Desc") ) , PROPNAME );

		pItem->EnableSpinControl( TRUE , (long)-wide , (long)wide );
		}
		else
		{*/
		pItem = new CBCGPPropEx ( 
			CString(pItemCfg->GetProperties("Name")) , 
			Value , 
			CString(pItemCfg->GetProperties("Desc") ) , PROPNAME );

		if( p != NULL ) 
		{
			pItem->EnableSpinControl( TRUE , value1 , wide );
			m_lWideNegative = value1;
		}
		else
		{
			pItem->EnableSpinControl( TRUE , -wide , wide );
			m_lWideNegative = -wide;
		}

		//	}

		m_lWide = wide;

		return pItem;
	}
	else if( stricmp(pItemCfg->GetProperties("Type") , "size") == 0 ||
		stricmp(pItemCfg->GetProperties("Type") , "unsigned long") == 0)
	{
		const char * name = pItemCfg->GetProperties("Name");
		const char *p = pItemCfg->GetProperties("DefaultValue");
		float Value = 0;
		if( p != NULL ) Value = atoi(p);
		p = pItemCfg->GetProperties("MaxValue");
		float wide = 500.000000;
		if( p != NULL ) wide = atoi(p);
		/*if( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL )
			;
		else */if( m_enumUnit==SYSTEM::SYS_UNIT_CENTIMETER )  
		{
			wide  = ((unsigned long)(wide * m_fPelsToCmRate + 0.5)) * 1.000000f;
		}
		else if(m_enumUnit==SYSTEM::SYS_UNIT_MILLIMETER)
		{
			wide  = ((unsigned long)(wide * m_fPelsToMmRate + 0.5)) * 1.000000f;
		}
		else if( m_enumUnit == SYSTEM::SYS_UNIT_DECIMETER )
		{
			wide = ((unsigned long)(wide * m_fPelsToDmRate + 0.5)) * 1.000000f;
		}
		else if( m_enumUnit == SYSTEM::SYS_UNIT_POINT )
		{
			wide = ((unsigned long)(wide * m_fPelsToMmRate * m_fMmToPointRate + 0.5)) * 1.000000f;
		}

		if ( wide < Value )
		{
			Value = wide;
		}
		else if ( Value < 0.000001f)
		{
			Value = 0.000001f;
		}


		CBCGPPropEx* pItem;
		/*if ( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL )
		{
		pItem = new CBCGPPropEx ( CString(pItemCfg->GetProperties("Name")) , 
		(unsigned long)Value ,  CString(pItemCfg->GetProperties("Desc") ) , PROPNAME );
		pItem->EnableSpinControl( TRUE , 0 , wide );
		} 
		else
		{*/
		pItem = new CBCGPPropEx ( CString(pItemCfg->GetProperties("Name")) , 
			Value ,  CString(pItemCfg->GetProperties("Desc") ) , PROPNAME );
		pItem->EnableSpinControl( TRUE , 0.000001f , wide );
		//	}

		m_ulWide = wide;

		return pItem;
	}
	else if ( stricmp(pItemCfg->GetProperties("Type") , "rate") == 0 )
	{
		const char *p = NULL;
		p =	pItemCfg->GetProperties("DefaultValue");
		float defaultValue = 0;
		if ( p != NULL)
		{
			defaultValue = atoi(p);
			p = NULL;
		}

		p =	pItemCfg->GetProperties("MinVaue");
		float minValue = -10;
		if ( p != NULL)
		{
			minValue = atoi(p);
			p = NULL;
		}

		p =	pItemCfg->GetProperties("MaxValue");
		float maxValue = 10;
		if ( p != NULL)
		{
			maxValue = atoi(p);
			p = NULL;
		}

		CBCGPPropEx* pItem = new CBCGPPropEx ( CString(pItemCfg->GetProperties("Name")) , 
			defaultValue , CString(pItemCfg->GetProperties("Desc") ) , PROPNAME );

		pItem->EnableSpinControl (TRUE, minValue , maxValue );
		return pItem;
	}
	else if( stricmp(pItemCfg->GetProperties("Type") , "group") == 0 )
	{
		CBCGPProp* pItem = new CBCGPProp ( CString(pItemCfg->GetProperties("Name")) , -1 , TRUE );
		int iCount = pItemCfg->GetChildCount();
		for(int i = 0 ; i < iCount ; i++ )
		{
			pItem->AddSubItem( GetSymbolItem(pItemCfg->GetChilds(i)));
		}
		pItem->Expand();
		pItem->AllowEdit(FALSE);
		return pItem;
	}
	else if(stricmp(pItemCfg->GetProperties("Type") , "angle") == 0 )
	{				
		float angle=0.0;
		const char *p = pItemCfg->GetProperties("DefaultValue");
		if( p != NULL )
			angle = (float)atof(p);

		angle = angle*180/3.1415926535;
		CBCGPPropEx* pItem = new CBCGPPropEx ( CString(pItemCfg->GetProperties("Name")) , 
			angle , CString(pItemCfg->GetProperties("Desc") ) , PROPNAME );

		pItem->EnableSpinControl (TRUE, -360.000000 , 360.000000);
		m_angleWide = 360.000000;
		return pItem;
	}	
	else if(stricmp(pItemCfg->GetProperties("Type") , "bool") == 0 || stricmp(pItemCfg->GetProperties("Type") , "bAlpha") == 0)
	{
		bool bRes = false;
		const char *p = pItemCfg->GetProperties("DefaultValue");
		if( p != NULL )
			bRes = (bool)atoi(p);
		CBCGPProp* pItem = new CBCGPProp ( CString(pItemCfg->GetProperties("Name")) , 
			bRes , CString(pItemCfg->GetProperties("Desc") ) , PROPNAME );

		return pItem;
	}		
	else if( stricmp(pItemCfg->GetProperties("Type"),"PicPath") == 0 )
	{
		static TCHAR BASED_CODE szFilter[] = "Picture Files (*.bmp,*.jpg,*.png,*.gif)|*.bmp;*.jpg;*.png;*.gif|";
		CBCGPProp* pItem = new CBCGPFilePropEx ( CString(pItemCfg->GetProperties("Name")) , 
			TRUE, NULL , NULL , OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT , szFilter, 
			CString(pItemCfg->GetProperties("Desc")) , PROPNAME );
		pItem->SetValue(_variant_t(pItemCfg->GetProperties("DefaultValue")));
		pItem->AllowEdit (FALSE);
		return pItem;
	}
	else if(stricmp(pItemCfg->GetProperties("Type") , "enum") == 0 )
	{
		CBCGPProp* pItem = new CBCGPProp ( CString(pItemCfg->GetProperties("Name")) , 
			_variant_t(pItemCfg->GetProperties("DefaultValue")) , 
			CString(pItemCfg->GetProperties("Desc") ) , PROPNAME );

		int iCount = pItemCfg->GetChildCount();
		for(int i = 0 ; i < iCount ; i++)
		{
			pItem->AddOption( pItemCfg->GetChilds(i)->GetProperties("name"));
		}

		pItem->AllowEdit (FALSE);
		return pItem;
	}
	else if(stricmp(pItemCfg->GetProperties("Type") , "CharType") == 0 )
	{
		CBCGPProp* pItem = new CBCGPFontSelectProp ( CString(pItemCfg->GetProperties("Name")) , 
			_variant_t(pItemCfg->GetProperties("DefaultValue")) , 
			CString(pItemCfg->GetProperties("Desc") ) , PROPNAME );

		pItem->AllowEdit (FALSE);
		return pItem;
		////列举字体名
		//HDC hDC;	
		//hDC = ::GetWindowDC(NULL);	
		//LOGFONT lf;	
		//ZeroMemory(&lf,sizeof(lf));

		////SYMBOL_CHARSET; //OEM_CHARSET; //GB2312_CHARSET; //DEFAULT_CHARSET;
		////获取不同字符集的字体集合
		//lf.lfCharSet = ANSI_CHARSET; //西方
		//if (!EnumFontFamiliesEx(
		//	hDC,	// handle to device context
		//	&lf,	// pointer to logical font information
		//	(FONTENUMPROC)EnumFamScreenCallBackEx,	// pointer to callback function
		//	(LPARAM) this,	// application-supplied data
		//	(DWORD) 0))
		//	return FALSE;

		//lf.lfCharSet = SYMBOL_CHARSET; //符号
		//if (!EnumFontFamiliesEx(
		//	hDC,	// handle to device context
		//	&lf,	// pointer to logical font information
		//	(FONTENUMPROC)EnumFamScreenCallBackEx,	// pointer to callback function
		//	(LPARAM) this,	// application-supplied data
		//	(DWORD) 0))
		//	return FALSE;

		/*::ReleaseDC(NULL,hDC);*/
	}
	else if(stricmp(pItemCfg->GetProperties("Type") , "color") == 0 )
	{
		const char *p = pItemCfg->GetProperties("DefaultValue");
		COLORREF Val = 0;
		if( p != NULL ) Val = (COLORREF)atoi(p);
		CBCGPColorPropEx* pColorProp = new CBCGPColorPropEx ( CString(pItemCfg->GetProperties("Name")) , 
			Val , NULL ,  CString(pItemCfg->GetProperties("Desc") ) , PROPNAME );

		pColorProp->EnableOtherButton ("调色板...   ");
		pColorProp->AllowEdit (FALSE);
		return pColorProp;
	}
	else if( stricmp( pItemCfg->GetProperties("Type") , "symbol" ) == 0 )
	{
		CSymbolProp* pItem = new CSymbolProp (this, CString(pItemCfg->GetProperties("Name")) , 
			_variant_t(pItemCfg->GetProperties("DefaultValue")) , 
			CString(pItemCfg->GetProperties("Desc") ) , PROPNAME );
		pItem->AllowEdit(FALSE);
		return pItem;
	}
	else if( stricmp( pItemCfg->GetProperties("Type") , "DashArray" ) == 0 )
	{
		CDashArrayExProp *pItem = new CDashArrayExProp( CString(pItemCfg->GetProperties("Name")) , NULL ,
			CString(pItemCfg->GetProperties("Desc") ), PROPNAME);
		return pItem;
	}
	else if( stricmp( pItemCfg->GetProperties("Type") , "CharMap" ) == 0 )
	{
		const char *p = pItemCfg->GetProperties("DefaultValue");
		int Value = 1;
		if( p != NULL )
			Value = atoi(p);
		if (Value < 1)
		{
			Value = 1;
		}

		if (Value > 65535)
		{
			Value = 65535;
		}

		CCharSymbolSelectProp *pItem = new CCharSymbolSelectProp( this , CString(pItemCfg->GetProperties("Name")) , 
			(unsigned long)Value ,
			CString(pItemCfg->GetProperties("Desc") ) , PROPNAME );
		pItem->EnableSpinControl(FALSE , 1, 65535);
		return pItem;
	}
	else 
	{
		CBCGPProp* pItem = new CBCGPProp ( CString(pItemCfg->GetProperties("Name")) , 
			_variant_t(pItemCfg->GetProperties("DefaultValue")) , 
			CString(pItemCfg->GetProperties("Desc") ) , PROPNAME );

		return pItem;
	}
	return NULL;
}

// 设置一个符号
bool CSymbolPropList::SetSymbol(Display::ISymbolPtr pSymbol)
{
	if( pSymbol == NULL )
	{
		pSymbol = Display::CSymbolFactory::CreateSymbol((SYMBOL_TYPE)m_SymbolType);
	}
	if( pSymbol->GetType() != m_SymbolType )
	{
		return false;
	}

	m_enumUnit = pSymbol->GetUnit();
	for (int i = 0 ; i < GetPropertyCount() ; i++ )
	{
		SetSymbolValueToPropList( pSymbol , GetProperty(i) );
	}

	m_pSymbol = pSymbol;
	AdjustLayout();
	UpdateData();
	return true;
}


// 更新符号的相应参数
bool CSymbolPropList::UpDataSymbol()
{
	UpdateData(FALSE);
	if( m_pSymbol == NULL )
	{
		m_pSymbol = Display::CSymbolFactory::CreateSymbol((SYMBOL_TYPE)m_SymbolType);
	}
	for (int i = 0 ; i < GetPropertyCount() ; i++ )
	{
		SetPropListToSymbolValue( GetProperty(i) );
	}

	return true;
}

// 替代Create函数，进行创建和初始化工作
bool CSymbolPropList::InitWindow(CRect& rectPropList, CWnd* pWnd, UINT nID)
{
	Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectPropList, pWnd, nID );

	EnableHeaderCtrl ( TRUE , "属性"  ,  " 值 " );
	EnableDesciptionArea ();
	SetVSDotNetLook (TRUE);

	SetAlphabeticMode (FALSE);
	SetShowDragContext (TRUE);

	SetBoolLabels("是","否");
	return true;
}

void CSymbolPropList::SetSymbolValueToPropList(Display::ISymbolPtr pSymbol, CBCGPProp* pGroup)
{
	ASSERT( pGroup->GetData() == -1 );

	for (int i = 0 ; i < pGroup->GetSubItemsCount() ; i++ )
	{
		if( pGroup->GetSubItem(i)->GetData() == -1 )
			SetSymbolValueToPropList( pSymbol , pGroup->GetSubItem(i) ); // 更新下个层次的内容
		else
		{
			CBCGPProp *pProp = NULL;
			pProp =	pGroup->GetSubItem(i);
			if ( pProp == NULL )
			{
				continue;
			}

			int index = pProp->GetData();
			CString PropName = m_pSymCfgItems[index]->GetProperties("PropName");
			_variant_t vt = pSymbol->GetProperties((char*)(LPCTSTR)PropName);

			if( ((vt.vt == VT_I4 )||(vt.vt == VT_INT)) && pGroup->GetSubItem(i)->GetOptionCount() != 0 )
			{
				CBCGPProp *tmpProp = pGroup->GetSubItem(i);
				if ( tmpProp == NULL )
				{
					continue;
				}

				int enumCount = m_pSymCfgItems[index]->GetChildCount();
				int j = 0;
				for ( ; j < enumCount ; ++j )
				{
					SYSTEM::IConfigItemPtr item = m_pSymCfgItems[index]->GetChilds(j);
					if (item == NULL)
					{
						::MessageBox(this->m_hWnd , "解析XML文件错误" , "错误" , MB_OK);
						return;
					}
					int intValue = atoi(item->GetProperties("enumvalue"));
					if ( intValue == vt.lVal )
					{
						break;
					}
				}

				vt = tmpProp->GetOption(j);
			}

			if( vt.vt != (VT_UI1|VT_ARRAY) )
				vt.ChangeType( pGroup->GetSubItem(i)->GetValue().vt );
			//换算单位
			if( stricmp( m_pSymCfgItems[index]->GetProperties("Type") , "long" ) == 0)
			{
				/*if( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL )
				vt = (long)(float)vt;
				else 
				vt = (float)vt;*/

				/*if( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL )
				{
				if ( (long)m_lWide < (long)vt )
				{			
				vt = (long)m_lWide;
				}
				else if( (long)vt < (long)-m_lWide )
				{

				vt = (long)-m_lWide;
				}
				}
				else
				{*/
				if ( m_lWide < (float)vt)
				{			
					vt = (float)m_lWide;
				}
				else if( (float)vt < m_lWideNegative)
				{
					vt = (float)m_lWideNegative;
				}		
				//	}

			}
			else if( stricmp(m_pSymCfgItems[index]->GetProperties("Type") , "size" ) == 0 ||
				stricmp(m_pSymCfgItems[index]->GetProperties("Type") , "unsigned long") == 0 )
			{

				/*if( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL )
				vt = (unsigned long)(float)vt;
				else 
				vt =  (float)vt ;

				if( m_enumUnit == SYSTEM::SYS_UNIT_PIXEL )
				{
				if ( (long)m_ulWide < vt.lVal)
				{
				vt = (unsigned long)m_ulWide;
				}
				else if( vt.lVal < 0)
				{
				vt = (unsigned long)0;
				}
				}
				else
				{*/
				if ( m_ulWide < (float)vt)
				{
					vt = (float)m_ulWide;
				}
				else if( (float)vt < 0.000001f )
				{
					vt = 0.000001f;
				}
				//	}
			}
			else if( stricmp( (char*)m_pSymCfgItems[index]->GetProperties("Type") , "angle" ) == 0 )
			{
				vt = (float)((float)vt * 180 / 3.1415926535 );
			}

			// 更新值
			if( stricmp( (char*)m_pSymCfgItems[index]->GetProperties("Type") , "color" ) == 0 )
			{
				CBCGPColorPropEx *pProp = (CBCGPColorPropEx*)pGroup->GetSubItem(i);
				pProp->Enable(TRUE);
				CString EnablePropName = m_pSymCfgItems[index]->GetProperties("PaletteData");
				if( EnablePropName.GetLength() != 0 )
				{
					_variant_t vt = pSymbol->GetProperties((char*)(LPCTSTR)EnablePropName);
					IMAGE_COLOR *data = (IMAGE_COLOR*)(long)vt;

					if (data == NULL)
					{
						/*pProp->Enable(FALSE);*/
						pProp->ReSetPalette(NULL);
					}
					else
					{
						pProp->ReSetPalette(data);
					}
					delete data;
				}	

				CString extPropName = m_pSymCfgItems[index]->GetProperties("ExtProp");
				if( extPropName.GetLength() != 0 )
				{					
					_variant_t vt = pSymbol->GetProperties((char*)(LPCTSTR)extPropName);
					CString disibleCondition = m_pSymCfgItems[index]->GetProperties("DisableCondition");

					char *token;
					char seps[]   = ",";

					token = strtok( ((char*)(LPCTSTR)disibleCondition ) , seps );

					while( token != NULL )
					{ 
						if (atoi(token) == (int)vt)
						{
							pProp->Enable(FALSE);
							break;
						}
						token = strtok( NULL , seps );
					}

				}

				pProp->SetColor( vt.lVal & 0x00ffffff );
			}
			else if( stricmp( (char*)m_pSymCfgItems[index]->GetProperties("Type") , "symbol" ) == 0 )
			{
				CSymbolProp *pProp = (CSymbolProp*)pGroup->GetSubItem(i);
				pProp->SetSymbol( vt );
			}
			else if( stricmp( (char*)m_pSymCfgItems[index]->GetProperties("Type") , "DashArray" ) == 0 )
			{
				CDashArrayExProp *pItem = NULL;
				pItem = dynamic_cast<CDashArrayExProp*>(pProp);
				if ( pItem == NULL )
				{
					continue;
				}
				Display::CDashArray *pDashArray = NULL;
				pDashArray = (Display::CDashArray*)(long)vt;
				if ( pDashArray == NULL )
				{
					continue;
				}
				pItem->SetDashArray(pDashArray);
				pItem->SetSymbolType(pSymbol->GetType());
			}
			else if( stricmp( (char*)m_pSymCfgItems[index]->GetProperties("Type") , "bool" ) == 0 )
			{
				CString extPropName = m_pSymCfgItems[index]->GetProperties("ExtProp");
				pProp->Enable(TRUE);
				if( extPropName.GetLength() != 0 )
				{					
					_variant_t vt = pSymbol->GetProperties((char*)(LPCTSTR)extPropName);
					CString disibleCondition = m_pSymCfgItems[index]->GetProperties("DisableCondition");

					char *token;
					char seps[]   = ",";

					token = strtok( ((char*)(LPCTSTR)disibleCondition ) , seps );

					while( token != NULL )
					{ 
						if (atoi(token) == (int)vt)
						{
							pProp->Enable(FALSE);
							break;
						}
						token = strtok( NULL , seps );
					}

				}

				pProp->SetValue( vt );
			}
			else if( stricmp( (char*)m_pSymCfgItems[index]->GetProperties("Type") , "bAlpha" ) == 0 )
			{
				pProp->SetValue( (bool)CheckNoColor(pSymbol->GetColor()) );
			}
			else
			{
				pProp->SetValue( vt );
			}
			// 检查属性可用状态
			CString EnablePropName = m_pSymCfgItems[index]->GetProperties("EnablePropName");
			if( EnablePropName.GetLength() != 0 )
			{
				_variant_t vt = pSymbol->GetProperties((char*)(LPCTSTR)EnablePropName);
				vt.ChangeType(VT_BOOL);
				pGroup->GetSubItem(i)->Enable( vt.bVal );

			}	
		}
	}
}

void CSymbolPropList::SetPropListToSymbolValue(CBCGPProp* pGroup) const
{

	if ( pGroup == NULL )
	{
		return;
	}

	int index = 0;
	index = pGroup->GetData();
	if ( index == -1)	//新加
	{
		for ( int i = 0 ; i < pGroup->GetSubItemsCount() ; i++ )
		{
			SetPropListToSymbolValue( pGroup->GetSubItem(i) );
		}

		return;
	}

	CString PropName = m_pSymCfgItems[index]->GetProperties("PropName");
	_variant_t vt = pGroup->GetValue();


	//换算单位
	if( stricmp( m_pSymCfgItems[index]->GetProperties("Type") , "long" ) == 0)
	{		
		if ( ((CBCGPPropEx*)pGroup)->GetMaxValue() < (float)vt)
		{			
			pGroup->SetValue((float)((CBCGPPropEx*)pGroup)->GetMaxValue());
			vt = (float)((CBCGPPropEx*)pGroup)->GetMaxValue();

		}
		else if( (float)vt < ((CBCGPPropEx*)pGroup)->GetMinValue() )
		{
			pGroup->SetValue((float)((CBCGPPropEx*)pGroup)->GetMinValue());
			vt = (float)((CBCGPPropEx*)pGroup)->GetMinValue();
		}	
	}
	else if( stricmp(m_pSymCfgItems[index]->GetProperties("Type") , "size" ) == 0 ||
		stricmp(m_pSymCfgItems[index]->GetProperties("Type") , "unsigned long" ) == 0 )
	{
		if ( ((CBCGPPropEx*)pGroup)->GetMaxValue() < (float)vt)
		{
			pGroup->SetValue((float)((CBCGPPropEx*)pGroup)->GetMaxValue());
			vt = (float)((CBCGPPropEx*)pGroup)->GetMaxValue();
		}
		else if ( (float)vt < 0.000001f )
		{
			pGroup->SetValue( 0.000001f);
			vt = 0.000001f;
		}

		/*m_pSymbol->SetProperties( (char*)(LPCTSTR)PropName , vt );

		for (int i = 0 ; i < GetPropertyCount() ; i++ )
		{
		const_cast< CSymbolPropList * >( this )->SetSymbolValueToPropList( m_pSymbol ,  GetProperty(i) );
		}

		const_cast< CSymbolPropList * >( this )->AdjustLayout();

		if ( m_propListInterface != NULL )
		m_propListInterface->OnSymbolPropChanged(m_pSymbol,this->GetParent());
		return;*/
	}
	else if ( stricmp(m_pSymCfgItems[index]->GetProperties("Type") , "angle" ) == 0 )
	{
		if( (float)vt > ((CBCGPPropEx*)pGroup)->GetMaxValue() )
		{
			pGroup->SetValue((float)((CBCGPPropEx*)pGroup)->GetMaxValue());
			vt = (float)((CBCGPPropEx*)pGroup)->GetMaxValue();
		}
		else if( (float)vt < ((CBCGPPropEx*)pGroup)->GetMinValue() )
		{
			pGroup->SetValue((float)((CBCGPPropEx*)pGroup)->GetMinValue());
			vt = (float)((CBCGPPropEx*)pGroup)->GetMinValue();
		}

		vt = (float)((float)vt * 3.1415926535 / 180);
	}
	else if ( stricmp(m_pSymCfgItems[index]->GetProperties("Type") , "rate" ) == 0 )
	{
		if( (float)vt > ((CBCGPPropEx*)pGroup)->GetMaxValue() )
		{
			pGroup->SetValue((float)((CBCGPPropEx*)pGroup)->GetMaxValue());
			vt = (float)((CBCGPPropEx*)pGroup)->GetMaxValue();
		}
		else if( (float)vt < ((CBCGPPropEx*)pGroup)->GetMinValue() )
		{
			pGroup->SetValue((float)((CBCGPPropEx*)pGroup)->GetMinValue());
			vt = (float)((CBCGPPropEx*)pGroup)->GetMinValue();
		}
	}
	else if ( stricmp(m_pSymCfgItems[index]->GetProperties("Type") , "bool" ) == 0 )
	{
		m_pSymbol->SetProperties( (char*)(LPCTSTR)PropName , vt );

		for (int i = 0 ; i < GetPropertyCount() ; i++ )
		{
			const_cast< CSymbolPropList * >( this )->SetSymbolValueToPropList( m_pSymbol ,  GetProperty(i) );
		}

		const_cast< CSymbolPropList * >( this )->AdjustLayout();

		if ( m_propListInterface != NULL )
			m_propListInterface->OnSymbolPropChanged(m_pSymbol,this->GetParent());
		return;
	}
	else if ( stricmp(m_pSymCfgItems[index]->GetProperties("Type") , "bAlpha" ) == 0 )
	{
		if ((bool)vt)	//透明
		{
			m_pSymbol->SetProperties( (char*)(LPCTSTR)PropName , (unsigned long)SetNoColor );
		}
		else			//符号不透明
		{
			m_pSymbol->SetProperties( (char*)(LPCTSTR)PropName , (unsigned long)SetHasColor );
		}
		/*m_pSymbol->SetProperties( (char*)(LPCTSTR)PropName , vt );*/

		for (int i = 0 ; i < GetPropertyCount() ; i++ )
		{
			const_cast< CSymbolPropList * >( this )->SetSymbolValueToPropList( m_pSymbol ,  GetProperty(i) );
		}

		const_cast< CSymbolPropList * >( this )->AdjustLayout();

		if ( m_propListInterface != NULL )
			m_propListInterface->OnSymbolPropChanged(m_pSymbol,this->GetParent());
		return;
	}
	else if ( stricmp(m_pSymCfgItems[index]->GetProperties("Type") , "DashArray" ) == 0 )
	{
		//更新响应到外界
		if ( m_propListInterface !=  NULL )
			m_propListInterface->OnSymbolPropChanged(m_pSymbol,this->GetParent());
		return;
	}
	else if( stricmp( m_pSymCfgItems[index]->GetProperties("Type") , "PicPath" ) == 0 )
	{
		m_pSymbol->SetProperties( (char*)(LPCTSTR)PropName , vt );

		_variant_t vtRetPath =  m_pSymbol->GetProperties( (char*)(LPCTSTR)PropName );

		if (strlen((_bstr_t)vtRetPath) == 0)
		{
			::MessageBox(this->m_hWnd  , "加载文件失败或文件不存在,请重新选择文件！" , "错误" , MB_OK);
		}

		for (int i = 0 ; i < GetPropertyCount() ; i++ )
		{
			const_cast< CSymbolPropList * >( this )->SetSymbolValueToPropList( m_pSymbol ,  GetProperty(i) );
		}

		const_cast< CSymbolPropList * >( this )->AdjustLayout();

		if ( m_propListInterface != NULL )
			m_propListInterface->OnSymbolPropChanged(m_pSymbol,this->GetParent());
		return;
	}
	else if( stricmp( m_pSymCfgItems[index]->GetProperties("Type") , "symbol" ) == 0 )
	{
		CSymbolProp * symbolProp = NULL;
		symbolProp = (CSymbolProp*)pGroup;
		if (symbolProp == NULL)
		{
			return;
		}
		Display::ISymbolPtr newSymbol;
		if( symbolProp->m_symbolData.vt == VT_BSTR )
		{
			SYSTEM::CStringArchive ar;
			ar.ImportVariant( symbolProp->m_symbolData);
			ar.SetReadState();
			newSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);			
		}
		else
		{
			SYSTEM::CBinArchive ar;
			ar.ImportVariant( symbolProp->m_symbolData);
			ar.SetReadState();
			newSymbol = Display::CSymbolFactory::CreateSymbolFromStream(ar);
		}
		if (newSymbol == NULL)
		{
			::MessageBox(this->m_hWnd , "创建符号失败!请检查符号文件!"  ,  "错误" ,  MB_OK);
			goto REFRESH;
		}

		if (newSymbol->GetType() & EXT_SYMBOL)
		{
			::MessageBox(this->m_hWnd , "不能将扩展符号加入标准符号内！\n如要使用可以加入到复合符号再选入。"  ,  "错误" ,  MB_OK);
			goto REFRESH;
		}

		m_pSymbol->SetProperties( (char*)(LPCTSTR)PropName , symbolProp->m_symbolData );

REFRESH:
		CString PropName = m_pSymCfgItems[index]->GetProperties("ExtProp");
		if( PropName.GetLength() != 0 )
		{
			if (stricmp("ReFresh" , (char*)(LPCTSTR)PropName) == 0)
			{
				for (int i = 0 ; i < GetPropertyCount() ; i++ )
				{
					const_cast< CSymbolPropList * >( this )->SetSymbolValueToPropList( m_pSymbol ,  GetProperty(i) );
				}

				const_cast< CSymbolPropList * >( this )->AdjustLayout();
			}
		}

		if ( m_propListInterface != NULL )
			m_propListInterface->OnSymbolPropChanged(m_pSymbol,this->GetParent());
		return;
	}
	else if( stricmp( m_pSymCfgItems[index]->GetProperties("Type") , "color" ) == 0 )
	{
		m_pSymbol->SetProperties( (char*)(LPCTSTR)PropName , (unsigned long)vt & 0x00ffffff);

		CString PropName = m_pSymCfgItems[index]->GetProperties("ExtProp");
		if( PropName.GetLength() != 0 )
		{
			if (stricmp("ReFresh" , (char*)(LPCTSTR)PropName) == 0)
			{
				for (int i = 0 ; i < GetPropertyCount() ; i++ )
				{
					const_cast< CSymbolPropList * >( this )->SetSymbolValueToPropList( m_pSymbol ,  GetProperty(i) );
				}

				const_cast< CSymbolPropList * >( this )->AdjustLayout();
			}
		}

		if ( m_propListInterface != NULL )
			m_propListInterface->OnSymbolPropChanged(m_pSymbol,this->GetParent());
		return;
	}
	else if( ((vt.vt == VT_BSTR) || (vt.vt == VT_INT)) && pGroup->GetOptionCount() != 0 )
	{
		SYSTEM::IConfigItemPtr pSymItemCfg = m_pSymCfgItems[index];
		if (pSymItemCfg == NULL)
		{
			//	const_cast< CSymbolPropList * >( this )->AfxMessageBox(this->m_hWnd , "解析XML文件失败" , "错误" , OT_MESSAGEBOX_TYPE_OK);
			return;
		}
		for (int i = 0 ; i < pSymItemCfg->GetChildCount() ; i++ )
		{
			if( stricmp( pSymItemCfg->GetChilds(i)->GetProperties("name") , (char*)(_bstr_t)vt ) == 0 )
			{
				vt = atoi( pSymItemCfg->GetChilds(i)->GetProperties("enumvalue") );
				break;
			}
		}
	}
	else if( stricmp( m_pSymCfgItems[index]->GetProperties("Type") , "CharMap" ) == 0 )
	{
		if ((unsigned long)vt < ((CCharSymbolSelectProp*)pGroup)->GetMinValue())
		{
			vt = (unsigned long)((CCharSymbolSelectProp*)pGroup)->GetMinValue();
		}
		if ((unsigned long)vt > ((CCharSymbolSelectProp*)pGroup)->GetMaxValue())
		{
			vt = (unsigned long)((CCharSymbolSelectProp*)pGroup)->GetMaxValue();
		}
		m_pSymbol->SetProperties( (char*)(LPCTSTR)PropName , vt );

		for (int i = 0 ; i < GetPropertyCount() ; i++ )
		{
			const_cast< CSymbolPropList * >( this )->SetSymbolValueToPropList( m_pSymbol ,  GetProperty(i) );
		}

		const_cast< CSymbolPropList * >( this )->AdjustLayout();
		//更新响应到外界
		if ( m_propListInterface != NULL )
			m_propListInterface->OnSymbolPropChanged(m_pSymbol,this->GetParent());
		return;
	}

	// 更新值
	m_pSymbol->SetProperties( (char*)(LPCTSTR)PropName , vt );

	// 检查属性可用状态
	CString EnablePropName = m_pSymCfgItems[index]->GetProperties("EnablePropName");
	if( EnablePropName.GetLength() != 0 )
	{
		_variant_t vt = m_pSymbol->GetProperties((char*)(LPCTSTR)EnablePropName);
		vt.ChangeType(VT_BOOL);
		pGroup->Enable( vt.bVal );

	}

	//更新响应到外界
	if ( m_propListInterface != NULL )
		m_propListInterface->OnSymbolPropChanged(m_pSymbol,this->GetParent());
}


void CSymbolPropList::OnPropertyChanged (CBCGPProp* pProp) const
{
	SetPropListToSymbolValue(pProp);
}

void CSymbolPropList::SetSymbolPropListInterface( ISymbolPropListInterface * propListInterface)
{
	if ( propListInterface != NULL )
	{
		m_propListInterface = propListInterface;
		m_propListInterface->SetPropList(this);
	}
}


//////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CCustomEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()
CCustomEdit::CCustomEdit( CBCGPProp *prop , CBCGPPropList *propList )
{
	m_pPropList = propList;
	m_pProp = prop;
}
void CCustomEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if ( nChar == 46)
	{
		CString value;
		this->GetWindowText(value);
		if (value.Find('.') != -1)
		{
			return;
		}
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		return;
	}

	if ( nChar == 48)
	{
		CString value;
		this->GetWindowText(value);
		if (value.Compare("") == 0)
		{
			this->SetSel(0 , -1);
			CEdit::OnChar(nChar, nRepCnt, nFlags);
			return;
		}
	}

	SetCapture();
	CEdit::OnChar(nChar, nRepCnt, nFlags);

	if ( (m_pProp != NULL) && (m_pPropList != NULL) )
	{
		m_pProp->OnUpdateValue();
	}

	ReleaseCapture();
}

//////////////////////////////////////////////////////////////////////////


void CSymbolPropList::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bCurrentForce = true;
	__super::OnMouseMove(nFlags, point);
}

