// DlgCondition.cpp : implementation file
//

#include "stdafx.h"
#include "DlgConditionSelect.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgConditionSelect dialog


CDlgConditionSelect::CDlgConditionSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConditionSelect::IDD, pParent)
{
	
	mg_csCondition = _T("");
	mg_csFunction = _T("");
	mg_csFieldName = _T("");
	
	mg_bTable = FALSE;
	m_pFeatureClass =NULL;
}



CDlgConditionSelect::CDlgConditionSelect(Geodatabase::IFeatureClass *pFeatureClass)
    : CDialog(CDlgConditionSelect::IDD)
{
	mg_csCondition = _T("");
	mg_csFunction = _T("");
	mg_csFieldName = _T("");
	m_pFeatureClass =pFeatureClass;
	mg_bTable = FALSE;
}

void CDlgConditionSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConditionSelect)
	DDX_Control(pDX, IDC_LIST_FUNCTION, mg_cFunctionList);
	DDX_Control(pDX, IDC_EDIT_CONDITION, mg_cCondition);
	DDX_Text(pDX, IDC_EDIT_CONDITION, mg_csCondition);
	DDX_LBString(pDX, IDC_LIST_FUNCTION, mg_csFunction);
	DDX_LBString(pDX, IDC_LIST_FIELDNAME, mg_csFieldName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConditionSelect, CDialog)
	//{{AFX_MSG_MAP(CDlgConditionSelect)
	ON_EN_CHANGE(IDC_EDIT_CONDITION, OnChangeEditCondition)
	ON_LBN_SELCHANGE(IDC_LIST_FUNCTION, OnSelchangeListFunction)
	ON_BN_CLICKED(IDC_BN_ADD, OnBnAdd)
	ON_BN_CLICKED(IDC_BN_SUB, OnBnSub)
	ON_BN_CLICKED(IDC_BN_MUL, OnBnMul)
	ON_BN_CLICKED(IDC_BN_DIV, OnBnDiv)
	ON_BN_CLICKED(IDC_BN_LT, OnBnLt)
	ON_BN_CLICKED(IDC_BN_GT, OnBnGt)
	ON_BN_CLICKED(IDC_BN_EQ, OnBnEq)
	ON_BN_CLICKED(IDC_BN_EXP, OnBnExp)
	ON_BN_CLICKED(IDC_BN_LE, OnBnLe)
	ON_BN_CLICKED(IDC_BN_GE, OnBnGe)
	ON_BN_CLICKED(IDC_BN_NE, OnBnNe)
	ON_BN_CLICKED(IDC_BN_AND, OnBnAnd)
	ON_BN_CLICKED(IDC_BN_OR, OnBnOr)
	ON_BN_CLICKED(IDC_BN_NOT, OnBnNot)
	ON_BN_CLICKED(IDC_BN_PAREN, OnBnParen)
	
	ON_LBN_SELCHANGE(IDC_LIST_FIELDNAME, OnSelchangeListFieldname)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_BN_CONTAIN, OnBnContain)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConditionSelect message handlers



BOOL CDlgConditionSelect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString csTemp;
	long lNumRecs;
	long i;
	CRect rect;

	mg_cFunctionList.GetClientRect( &rect );
	mg_cFunctionList.SetHorizontalExtent( rect.Width( )*3 );

//字符串函数
	mg_cFunction.InsertAt( 0,"ALLTRIM( <CHAR Value> )" );
	mg_cFunction.InsertAt( 1,"CHR( <INTEGER Value> )" );
	mg_cFunction.InsertAt( 2,"LEFT( <CHAR Value> , <Num_Chars> )" );
	mg_cFunction.InsertAt( 3,"TRIM( <CHAR Value> )" );
	mg_cFunction.InsertAt( 4,"LTRIM( <CHAR Value> )" );
	mg_cFunction.InsertAt( 5,"STR( <Numeric> , <Length> , <Decimal> )" );
	mg_cFunction.InsertAt( 6,"SUBSTR( <CHAR Value> , <Start Index> , <NumChars> )" );
	mg_cFunction.InsertAt( 7,"UPPER( <CHAR Value> )" );
	mg_cFunction.InsertAt( 8,"VAL( <CHAR Value> )" );

//时间函数
	mg_cFunction.InsertAt( 9,"TIME(  )" );
	mg_cFunction.InsertAt( 10,"DATE(  )" );
	mg_cFunction.InsertAt( 11,"DAY( <DATE Value> )" );
	mg_cFunction.InsertAt( 12,"DTOC( <DATE Value> )" );
	mg_cFunction.InsertAt( 13,"DTOS( <DATE Value> )" );
	mg_cFunction.InsertAt( 14,"STOD( <CHAR Value> )" );
	mg_cFunction.InsertAt( 15,"CTOD( <\"MM/DD/YY\"> )" );
	mg_cFunction.InsertAt( 16,"YEAR( <DATE Value> )" );
	mg_cFunction.InsertAt( 17,"MONTH( <DATE Value> )" );

//条件表达
	mg_cFunction.InsertAt( 18,"IIF( <Condition> , <TRUE_Result> , <FALSE_Result> )" );

//
	mg_cFunction.InsertAt( 19,"RECCOUNT(  )" );
	mg_cFunction.InsertAt( 20,"RECNO(  )" );


	lNumRecs = mg_cFunction.GetSize();
	CListBox* pLBFunction = (CListBox*)GetDlgItem(IDC_LIST_FUNCTION);
	for (i = 0; i < lNumRecs; i ++)
	{
		csTemp = mg_cFunction.GetAt(i);
		pLBFunction->InsertString(-1, csTemp);
	}

	if( mg_bTable )
	{
		
	}
	else if(m_pFeatureClass)
	{
		CString csTemp;
		CString szTableName;

		csTemp = "条件构造";
		SetWindowText(csTemp);
		csTemp = "表名";
	
		csTemp = "取消";
		GetDlgItem( IDCANCEL )->SetWindowText(csTemp);
		csTemp = "确定";
		GetDlgItem( IDC_START )->SetWindowText(csTemp);

		LoadTableFields( );
	}


	return TRUE;
}

void CDlgConditionSelect::OnChangeEditCondition() 
{
}

void CDlgConditionSelect::OnSelchangeListFieldname()
{
	long lLen;

	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);
	
	//宽字节处理 
	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart,CStringW(mg_csFieldName) );
	mg_csCondition = szW;
	
	szW = mg_csFieldName;
	lLen = szW.GetLength();
	mg_csFieldName = szW;

	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel( mg_iStart+lLen, mg_iEnd+lLen );
}

void CDlgConditionSelect::OnSelchangeListFunction() 
{
	long lLen;
	long lStart = 0,lEnd = 0;
	CString csTemp;

	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);
	
	csTemp = mg_csFunction;

	while( ( lStart = csTemp.Find( '<',0 ) ) >= 0 )
	{
		lEnd = csTemp.Find( '>',lStart );
		csTemp.Delete( lStart,lEnd-lStart+1 );
	}
	
	//宽字节处理
	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart, CStringW(csTemp) );
	mg_csCondition = szW;
	
	szW = csTemp;
	lLen = szW.GetLength();
	csTemp = szW;

	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+lLen-2, mg_iEnd+lLen-2);
}

void CDlgConditionSelect::OnBnAdd() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);
	
	//用宽字节进行处理
	CStringW szWCondition( mg_csCondition );
	szWCondition.Insert(mg_iStart, L" + ");
	mg_csCondition = szWCondition;

	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+3, mg_iEnd+3);
}

void CDlgConditionSelect::OnBnSub() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);
	
	//用宽字节进行处理
	CStringW szWCondition( mg_csCondition );
	szWCondition.Insert(mg_iStart, L" - ");
	mg_csCondition = szWCondition;

	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+3, mg_iEnd+3);
}

void CDlgConditionSelect::OnBnMul() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);

	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart, L" * " );
	mg_csCondition = szW;

	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+3, mg_iEnd+3);
}

void CDlgConditionSelect::OnBnDiv() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);
	
	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart, L" * " );
	mg_csCondition = szW;


	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+3, mg_iEnd+3);
}

void CDlgConditionSelect::OnBnLt() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);
	
	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart, L" < " );
	mg_csCondition = szW;

	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+3, mg_iEnd+3);
}

void CDlgConditionSelect::OnBnGt() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);

	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart, L" > " );
	mg_csCondition = szW;

	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+3, mg_iEnd+3);
}

void CDlgConditionSelect::OnBnEq() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);

	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart, L" = " );
	mg_csCondition = szW;

	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+3, mg_iEnd+3);
}

void CDlgConditionSelect::OnBnExp() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);

	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart, L" ^ " );
	mg_csCondition = szW;

	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+3, mg_iEnd+3);
}

void CDlgConditionSelect::OnBnLe() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);

	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart, L" <= " );
	mg_csCondition = szW;

	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+4, mg_iEnd+4);
}

void CDlgConditionSelect::OnBnGe() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);

	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart, L" >= " );
	mg_csCondition = szW;

	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+4, mg_iEnd+4);
}

void CDlgConditionSelect::OnBnNe() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);

	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart, L" <> " );
	mg_csCondition = szW;

	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+4, mg_iEnd+4);
}

void CDlgConditionSelect::OnBnContain() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);

	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart, L" $ " );
	mg_csCondition = szW;

	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+3, mg_iEnd+3);	
}

void CDlgConditionSelect::OnBnAnd() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);

	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart, L" .And. " );
	mg_csCondition = szW;

	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+7, mg_iEnd+7);
}

void CDlgConditionSelect::OnBnOr() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);

	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart, L" .OR. " );
	mg_csCondition = szW;


	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+6, mg_iEnd+6);
}

void CDlgConditionSelect::OnBnNot() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);

	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart, L" .NOT " );
	mg_csCondition = szW;


	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+7, mg_iEnd+7);
}

void CDlgConditionSelect::OnBnParen() 
{
	UpdateData();
	mg_cCondition.GetSel(mg_iStart, mg_iEnd);

	CStringW szW( mg_csCondition );
	szW.Insert( mg_iStart, L"()" );
	mg_csCondition = szW;


	UpdateData(FALSE);
	mg_cCondition.SetFocus();
	mg_cCondition.SetSel(mg_iStart+2, mg_iEnd+2);
}

BOOL CDlgConditionSelect::LoadTableFields( )
{
	if(!m_pFeatureClass)
	{
		return FALSE;
	}

	long lNumFields =m_pFeatureClass->FieldCount();
	long i;
	CString pszFieldName;


	CListBox* pLBField = (CListBox*)GetDlgItem(IDC_LIST_FIELDNAME);
	pLBField->ResetContent( );

	Geodatabase::CFieldPtr pField;
	for( i = 1;i <= lNumFields;i++ )
	{
		pField =m_pFeatureClass->GetField(i);


		if(!pField)
		{
			continue;
		}
		pszFieldName =pField->GetName().c_str();
		pLBField->InsertString( -1,pszFieldName );
	}
	return TRUE;
}





void CDlgConditionSelect::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgConditionSelect::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CDlgConditionSelect::OnStart() 
{
	UpdateData( TRUE );	

	CDialog::OnOK();

}



