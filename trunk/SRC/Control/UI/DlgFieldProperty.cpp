// DlgFieldProperty.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Map.h"

#include "DlgFieldProperty.h"



// CDlgFieldProperty �Ի���

IMPLEMENT_DYNAMIC(CDlgFieldProperty, CDialog)

CDlgFieldProperty::CDlgFieldProperty(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFieldProperty::IDD, pParent)
	, m_bInVisible( false )
	, m_nNumDecimal( 0 )
	, m_strName(_T(""))
	, m_strType(_T(""))
	, m_nLength( 0 )
	, m_nPrecise( 0 )
{

}

CDlgFieldProperty::~CDlgFieldProperty()
{
}

void CDlgFieldProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDT_TYPE, m_strType);
	DDX_Text(pDX, IDC_EDT_LENTH, m_nLength);
	DDX_Text(pDX, IDC_EDT_PREC, m_nPrecise);
	DDX_Text(pDX, IDC_EDT_DEC, m_nNumDecimal);
	DDX_Control(pDX, IDC_EDT_DEC, m_edtDec);
	DDX_Check(pDX, IDC_CHK_INVISIBLE, m_bInVisible );
	DDV_MinMaxLong(pDX, m_nNumDecimal, 0, 16);
}


BEGIN_MESSAGE_MAP(CDlgFieldProperty, CDialog)
END_MESSAGE_MAP()


// CDlgFieldProperty ��Ϣ�������
void CDlgFieldProperty::SetName( const char* szName )
{
	m_strName = szName;
}

void CDlgFieldProperty::SetType( Geodatabase::FIELD_TYPE szType )
{
	switch( szType )
	{
	case Geodatabase::FTYPE_UNKNOWN:
		m_strType = "δ֪����";
		break;
	case Geodatabase::FTYPE_BOOL:
		m_strType = "������";
		break;
	case Geodatabase::FTYPE_STRING:
		m_strType = "�ַ���";
		break;
	case Geodatabase::FTYPE_SHORT:
		m_strType = "������";
		break;
	case Geodatabase::FTYPE_LONG:
		m_strType = "����";
		break;
	case Geodatabase::FTYPE_FLOAT:
		m_strType = "�����ȸ�����";
		break;
	case Geodatabase::FTYPE_DOUBLE:
		m_strType = "������";
		break;
	case Geodatabase::FTYPE_DATE:
		m_strType = "������";
		break;
	case Geodatabase::FTYPE_TIME:
		m_strType = "ʱ����";
		break;
	case Geodatabase::FTYPE_GEOMETRY:
		m_strType = "����ͼ��";
		break;
	case Geodatabase::FTYPE_BLOB:
		m_strType = "������";
		break;
	case Geodatabase::FTYPE_RASTERBLOCK:
		m_strType = "դ������";
		break;
	default:
		m_strType = "δ֪����";
		break;
	}
}

void CDlgFieldProperty::SetLength( long nLength )
{
	m_nLength = nLength;
}

void CDlgFieldProperty::SetPrecision( long nPrecision )
{
	m_nPrecise = nPrecision;
}

void CDlgFieldProperty::SetVisible( bool bVisible )
{
	m_bInVisible = !bVisible;

}

bool CDlgFieldProperty::GetVisible( void )
{
	return(!m_bInVisible);
}

void CDlgFieldProperty::SetDecimalNum( long nNum )
{
	m_nNumDecimal = nNum;

}

long CDlgFieldProperty::GetDecimalNum( void )
{
	return m_nNumDecimal;
}

BOOL CDlgFieldProperty::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if ( m_strType == "������" )
	{
		m_edtDec.EnableWindow( TRUE );
	}
	else
	{
		m_edtDec.EnableWindow( FALSE );
	}

	UpdateData( FALSE );
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
