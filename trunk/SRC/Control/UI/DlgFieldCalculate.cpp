// DlgFieldCalculate.cpp : 实现文件
//

#include "stdafx.h"
#include "Map.h"
#include "resource.h"
#include "DlgFieldCalculate.h"
#include "AttributeTable.h"
#include "IWorkspace.h"
#include "Calculator.h"
#include <boost/regex.hpp>

using namespace boost;

// CDlgFieldCalculate 对话框

IMPLEMENT_DYNAMIC(CDlgFieldCalculate, CDialog)

CDlgFieldCalculate::CDlgFieldCalculate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFieldCalculate::IDD, pParent)
	, m_bOnlySel(FALSE)
	, m_szMathExpr(_T(""))
{
	m_iStart = 0;
	m_iEnd = 0;
}

CDlgFieldCalculate::~CDlgFieldCalculate()
{
}

void CDlgFieldCalculate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_FIELD, m_LstFields);
	DDX_Control(pDX, IDC_LST_OPERATE, m_lstFunction);
	DDX_Control(pDX, IDC_EDT_CAL_EXPRESS, m_edtMathExpr);
	DDX_Check(pDX, IDC_CHK_ONLY_SELECTED, m_bOnlySel);
	DDX_Text(pDX, IDC_EDT_CAL_EXPRESS, m_szMathExpr);
	DDX_Radio(pDX, IDC_RADIO_NUMBER, m_iType);
}


BEGIN_MESSAGE_MAP(CDlgFieldCalculate, CDialog)
ON_LBN_DBLCLK(IDC_LST_FIELD, &CDlgFieldCalculate::OnLbnDblclkLstField)
ON_LBN_DBLCLK(IDC_LST_OPERATE, &CDlgFieldCalculate::OnLbnDblclkLstOperate)
ON_BN_CLICKED(IDC_BTN_ADD, &CDlgFieldCalculate::OnBnClickedBtnAdd)
ON_BN_CLICKED(IDC_BTN_SUBSTRACT, &CDlgFieldCalculate::OnBnClickedBtnSubstract)
ON_BN_CLICKED(IDC_BTN_MULTIPLY, &CDlgFieldCalculate::OnBnClickedBtnMultiply)
ON_BN_CLICKED(IDC_BTN_DIVIDE, &CDlgFieldCalculate::OnBnClickedBtnDivide)
ON_BN_CLICKED(IDC_BTN_EQUAL, &CDlgFieldCalculate::OnBnClickedBtnEqual)
ON_BN_CLICKED(IDC_BTN_MI, &CDlgFieldCalculate::OnBnClickedBtnMi)
ON_BN_CLICKED(IDC_RADIO_NUMBER, &CDlgFieldCalculate::OnBnClickedRadioNum)
ON_BN_CLICKED(IDC_RADIO_CHAR, &CDlgFieldCalculate::OnBnClickedRadioChar)
ON_BN_CLICKED(IDC_RADIO_TIME, &CDlgFieldCalculate::OnBnClickedRadioTime)
ON_BN_CLICKED(IDOK, &CDlgFieldCalculate::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgFieldCalculate 消息处理程序

void CDlgFieldCalculate::OnLbnDblclkLstField()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData( TRUE );
	m_edtMathExpr.GetSel( m_iStart, m_iEnd );
	
	int iCurSel = m_LstFields.GetCurSel();
	if( iCurSel < 0 )
		return;

	CString szField;
	m_LstFields.GetText( iCurSel, szField );

	//宽字节处理 
	CStringW szW( m_szMathExpr );
	szW.Insert( m_iStart, CStringW( szField) );
	m_szMathExpr = szW;

	szW = szField;
	long lLen = szW.GetLength();
	szField = szW;
	UpdateData( FALSE );

	m_edtMathExpr.SetFocus();
	m_edtMathExpr.SetSel( m_iStart+lLen, m_iEnd+lLen );
}

void CDlgFieldCalculate::OnLbnDblclkLstOperate()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData( TRUE );
	m_edtMathExpr.GetSel( m_iStart, m_iEnd );

	int iCurSel = m_lstFunction.GetCurSel();
	if( iCurSel < 0 )
		return;

	CString szFunction;
	m_lstFunction.GetText( iCurSel, szFunction );
	AddBackBracket( szFunction );

	//宽字节处理 
	CStringW szW( m_szMathExpr );
	szW.Insert( m_iStart, CStringW( szFunction ) );
	m_szMathExpr = szW;

	szW = szFunction;
	long lLen = szW.GetLength();
	szFunction = szW;
	UpdateData( FALSE );

	m_edtMathExpr.SetFocus();
	m_edtMathExpr.SetSel( m_iStart + lLen - 2, m_iEnd + lLen - 2 );
}

void CDlgFieldCalculate::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	AddOprator( _T(" + "));
}

void CDlgFieldCalculate::OnBnClickedBtnSubstract()
{
	// TODO: 在此添加控件通知处理程序代码
	AddOprator( _T(" - "));
}

void CDlgFieldCalculate::OnBnClickedBtnMultiply()
{
	// TODO: 在此添加控件通知处理程序代码
	AddOprator( _T(" * "));
}

void CDlgFieldCalculate::OnBnClickedBtnDivide()
{
	// TODO: 在此添加控件通知处理程序代码
	AddOprator( _T(" / "));
}

void CDlgFieldCalculate::OnBnClickedBtnEqual()
{
	// TODO: 在此添加控件通知处理程序代码
	AddOprator( _T(" = "));
}

void CDlgFieldCalculate::OnBnClickedBtnMi()
{
	// TODO: 在此添加控件通知处理程序代码
	AddOprator( _T(" ^ "));
}

CString CDlgFieldCalculate::GetMathExpr()
{
	return m_szMathExpr;
}

BOOL CDlgFieldCalculate::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化字段列表 
	Geodatabase::CFieldPtr pField;
	for(int i=1; i<= m_pFeatureClass->FieldCount(); i++)
	{
		pField = m_pFeatureClass->GetField(i);

		m_LstFields.AddString(pField->GetName().c_str());
	}
	
	//初始化类型
	m_iType = 0;

	//字段名称
	pField = m_pFeatureClass->GetField( m_iCalFieldIndex );
	CString szFieldName = pField->GetName().c_str();
	szFieldName.AppendFormat( _T(" = "));
	GetDlgItem( IDC_CALFIELDNAME )->SetWindowText( szFieldName );
	//初始化函数列表
	ReLoadFuntionList();

	UpdateData( FALSE );
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgFieldCalculate::ReLoadFuntionList()
{
	m_lstFunction.ResetContent();

	switch( m_iType )
	{
	case 0:
		m_lstFunction.AddString( _T("Sin"));
		m_lstFunction.AddString( _T("Cos"));
		m_lstFunction.AddString( _T("Tan"));
		m_lstFunction.AddString( _T("Sqrt"));
		m_lstFunction.AddString( _T("Log10"));
		m_lstFunction.AddString( _T("Log"));
		m_lstFunction.AddString( _T("Cot"));
		m_lstFunction.AddString( _T("Fabs"));
		m_lstFunction.AddString( _T("Floor"));
		m_lstFunction.AddString( _T("Asin"));
		m_lstFunction.AddString( _T("Acos"));
		m_lstFunction.AddString( _T("Atan"));
		m_lstFunction.AddString( _T("sinh"));
		m_lstFunction.AddString( _T("cosh"));
		m_lstFunction.AddString( _T("tanh"));
		m_lstFunction.AddString( _T("exp"));
		m_lstFunction.AddString( _T("sqrt"));
		break;
	case 1:
		m_lstFunction.AddString( _T( "Alltrim" ) );
		m_lstFunction.AddString( _T( "Chr" ) );
		m_lstFunction.AddString( _T( "Left" ) );
		m_lstFunction.AddString( _T( "Trim" ) );
		m_lstFunction.AddString( _T( "Ltrim" ) );
		m_lstFunction.AddString( _T( "Str" ) );
		m_lstFunction.AddString( _T( "Substr" ) );
		m_lstFunction.AddString( _T( "Upper" ) );
		m_lstFunction.AddString( _T( "Val" ) );
		break;
	case 2:
		m_lstFunction.AddString( _T( "Time" ) );
		m_lstFunction.AddString( _T( "Date" ) );
		m_lstFunction.AddString( _T( "Day" ) );
		m_lstFunction.AddString( _T( "Dtoc" ) );
		m_lstFunction.AddString( _T( "Dtos" ) );
		m_lstFunction.AddString( _T( "Stod" ) );
		m_lstFunction.AddString( _T( "Ctod" ) );
		m_lstFunction.AddString( _T( "Year" ) );
		m_lstFunction.AddString( _T( "Month" ) );
		break;
	default:
		break;
	}
}

void CDlgFieldCalculate::AddBackBracket( CString &szAdded )
{
	CString szBracket;
	szBracket.Format("\040%s\040%s","(",")");
	szAdded = szAdded + szBracket;
}

void CDlgFieldCalculate::AddOprator( LPCTSTR szOp )
{
	UpdateData( TRUE );
	m_edtMathExpr.GetSel( m_iStart, m_iEnd );
	
	//宽字节处理 
	CStringW szW( m_szMathExpr );
	szW.Insert( m_iStart, CStringW( szOp ) );
	m_szMathExpr = szW;

	szW = szOp;
	long lLen = szW.GetLength();
	
	UpdateData( FALSE );

	m_edtMathExpr.SetFocus();
	m_edtMathExpr.SetSel( m_iStart + lLen, m_iEnd + lLen );
}

void CDlgFieldCalculate::Init( int iFieldIndex, 
							  std::vector<long> &vSelFeatures, 
							  std::vector<long> &vAllFeatures,
							  Geodatabase::IFeatureClassPtr pFeatureClass )
{
	m_iCalFieldIndex = iFieldIndex;

	m_vSelFeatureIndex.clear();
	for ( long i = 0; i < vSelFeatures.size(); i++ )
	{
		m_vSelFeatureIndex.push_back( vSelFeatures[i] );
	}

	m_vAllFieldsIndex.clear();
	for ( long i = 0; i < vAllFeatures.size(); i++ )
	{
		m_vAllFieldsIndex.push_back( vAllFeatures[i] );
	}

	m_pFeatureClass = pFeatureClass;
}

void CDlgFieldCalculate::OnBnClickedRadioNum()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iType = 0;
	ReLoadFuntionList();
}

void CDlgFieldCalculate::OnBnClickedRadioChar()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iType = 1;
	ReLoadFuntionList();
}

void CDlgFieldCalculate::OnBnClickedRadioTime()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iType = 2;
	ReLoadFuntionList();
}

void CDlgFieldCalculate::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData( TRUE );
	
	//正则表达式 验证表达式正确
	cmatch what;

	if ( m_pFeatureClass == NULL )
		return;
	if ( m_iType == 0)
	{
		Calculate();
	}
	//else if ( m_iType == 1 )
	//{
	//	regex express("^[a-zA-Z]+([.])");
	//	if ( regex_match( m_szMathExpr, what, express ) )
	//	{
	//		
	//	}
	//	else
	//	{
	//		MessageBox( _T("表达式错误!"), _T("提示"), IDOK );
	//	}
	//}
	/*else if ( m_iType == 2)
	{
		regex express("^[a-zA-Z]+([.])");
		if ( regex_match( m_szMathExpr, what, express ) )
		{

		}
		else
		{
			MessageBox( _T("表达式错误!"), _T("提示"), IDOK );
		}
	}*/

	OnOK();
}

//********************************************************//
//***************计算数学表达式 调用MahExpr**************************//
//数值替换字符串
void CDlgFieldCalculate::MathExpreParser( CString &szMathExpr, Geodatabase::CFeaturePtr pFeature )
{
	for ( int i = 1; i <= pFeature->FieldCount(); i++ )
	{
		Geodatabase::CFieldPtr pField = pFeature->GetField( i );
		CString szFieldName = pField->GetName().c_str();
		
		if ( szMathExpr.Find( szFieldName, 0 ) )
			continue;

		double dValue = pFeature->GetValue( i ).GetAsDouble();
		CString szValueReplace;
		szValueReplace.Format("%lf", dValue);
		
		szMathExpr.Replace( szFieldName, szValueReplace );
	}
}

void CDlgFieldCalculate::Calculate()
{
	//数学表达式计算器
	Calculator mathCalculator;

	Geodatabase::IWorkspace *pWorkspace = m_pFeatureClass->GetWorkspace();
	bool bEdit =false;
	//矢量正在进行编辑
	if(pWorkspace->IsEditing())
	{
		bEdit =true;
	}
	else
	{
		pWorkspace->StartEdit();
	}
	
	if ( m_bOnlySel )
	{
		for ( int i = 0; i < m_vSelFeatureIndex.size(); i++ )
		{
			Geodatabase::CFeaturePtr pFeature = m_pFeatureClass->GetFeature( m_vSelFeatureIndex[i] );
			
			if(!pFeature)
			{
				if(!bEdit)
					pWorkspace->StopEdit(false);
			
				return;
			}

			//用数字替换字段变量
			CString szMathExpr = GetMathExpr();
			MathExpreParser( szMathExpr, pFeature );

			//计算数学表达式
			if ( !mathCalculator.Input( (LPSTR)(LPCTSTR)szMathExpr ) )
			{
				MessageBox( _T("表达式错误!"), _T("提示"), MB_OK );
				return;
			}
			
			if( !mathCalculator.Compute() )
			{
				MessageBox( _T("表达式错误!"), _T("提示"), MB_OK );
				return;
			}

			double dResult = mathCalculator.GetResult();

			Geodatabase::FieldValue pFiedValue = pFeature->GetValue( m_iCalFieldIndex );
			switch( pFiedValue.vtype )
			{
			case Geodatabase::FieldValue::VT_INT:
				pFeature->GetValue( m_iCalFieldIndex ).m_Var.iVal = (int)dResult;
				break;
			case Geodatabase::FieldValue::VT_SHORT:
				pFeature->GetValue( m_iCalFieldIndex ).m_Var.sVal = (short)dResult;
				break;
			case Geodatabase::FieldValue::VT_FLOAT:
				pFeature->GetValue( m_iCalFieldIndex ).m_Var.sVal = (float)dResult;
				break;
			case Geodatabase::FieldValue::VT_DOUBLE:
				pFeature->GetValue( m_iCalFieldIndex ).m_Var.sVal = (double)dResult;
				break;
			default:
				continue;
				break;
			}
				
			pFeature->Update();
		}
	}
	else
	{
		for ( int i = 0; i < m_vAllFieldsIndex.size(); i++)
		{
			Geodatabase::CFeaturePtr pFeature = m_pFeatureClass->GetFeature( m_vAllFieldsIndex[i] );
			
			if(!pFeature)
			{
				if(!bEdit)
				{
					pWorkspace->StopEdit(false);
				}
				return;
			}

			//用数字替换字段变量
			CString szMathExpr = GetMathExpr();
			MathExpreParser( szMathExpr, pFeature );

			//计算数学表达式
			if ( !mathCalculator.Input( (LPSTR)(LPCTSTR)szMathExpr ) )
			{
				MessageBox( _T("表达式错误!"), _T("提示"), MB_OK );
				return;
			}

			if( !mathCalculator.Compute() )
			{
				MessageBox( _T("表达式错误!"), _T("提示"), MB_OK );
				return;
			}

			double dResult = mathCalculator.GetResult();

			Geodatabase::FieldValue pFiedValue = pFeature->GetValue( m_iCalFieldIndex );
			switch( pFiedValue.vtype )
			{
			case Geodatabase::FieldValue::VT_INT:
				pFeature->GetValue( m_iCalFieldIndex ).m_Var.iVal = (int)dResult;
				break;
			case Geodatabase::FieldValue::VT_SHORT:
				pFeature->GetValue( m_iCalFieldIndex ).m_Var.sVal = (short)dResult;
				break;
			case Geodatabase::FieldValue::VT_FLOAT:
				pFeature->GetValue( m_iCalFieldIndex ).m_Var.fVal = (float)dResult;
				break;
			case Geodatabase::FieldValue::VT_DOUBLE:
				pFeature->GetValue( m_iCalFieldIndex ).m_Var.dVal = (double)dResult;
				break;
			default:
				continue;
				break;
			}
				
			pFeature->Update();
		}
	}
	
	if(!bEdit)
	{
		pWorkspace->StopEdit(true);
	}
}
//********************************************************//

