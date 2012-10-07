// D:\TitanImage7\Src\UIBase\otMap\MapUI\DlgAddField.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Map.h"
#include "resource.h"
#include "DlgAddField.h"



// CDlgAddField �Ի���

IMPLEMENT_DYNAMIC(CDlgAddField, CDialog)

CDlgAddField::CDlgAddField(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddField::IDD, pParent)
	, m_nLength(0)
	, m_nPrecision(0)
{
	m_strName = "";
	m_fieldType = Geodatabase::FTYPE_UNKNOWN;
}

CDlgAddField::~CDlgAddField()
{
}

void CDlgAddField::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text( pDX, IDC_EDT_NAME, m_strName );
	DDX_Control(pDX, IDC_CMB_TYPE, m_cmbType);
	DDX_Text(pDX, IDC_EDT_LENGTH, m_nLength);
	DDX_Text(pDX, IDC_EDT_PRECISION, m_nPrecision);
	DDV_MinMaxLong(pDX, m_nPrecision, 0, 32);
}


BEGIN_MESSAGE_MAP(CDlgAddField, CDialog)
	
	ON_EN_CHANGE(IDC_EDT_NAME, &CDlgAddField::OnEnChangeEdtName)
	ON_CBN_SELCHANGE(IDC_CMB_TYPE, &CDlgAddField::OnCbnSelchangeCmbType)
END_MESSAGE_MAP()


// CDlgAddField ��Ϣ�������
BOOL CDlgAddField::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	InitFieldTypes();

	GetDlgItem( IDOK)->EnableWindow( FALSE );
	

	return TRUE;
}

void CDlgAddField::InitFieldTypes()
{
	m_cmbType.AddString( _T("������") ); 
	m_cmbType.AddString( _T("����") );
	m_cmbType.AddString( _T("������") );
	m_cmbType.AddString( _T("�ַ���") );
	m_cmbType.AddString( _T("������") );
	//m_cmbType.AddString( _T("Geometry") );
	//m_cmbType.AddString( _T("������") );
	//m_cmbType.AddString( _T("Clob") );
	//m_cmbType.AddString( _T("RasterBlock") );
	m_cmbType.SetCurSel( 3 );

	OnCbnSelchangeCmbType();
}
void CDlgAddField::OnEnChangeEdtName()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData( TRUE );

	if( m_strName != "")
		GetDlgItem( IDOK)->EnableWindow( TRUE );
}

void CDlgAddField::OnCbnSelchangeCmbType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData( TRUE );

	switch( m_cmbType.GetCurSel() )
	{
	case 0:
		{
			m_fieldType = Geodatabase::FTYPE_BOOL;
			GetDlgItem( IDC_EDT_LENGTH )->EnableWindow( TRUE );
			GetDlgItem( IDC_EDT_PRECISION )->EnableWindow( FALSE );
			m_nLength =1;
			m_nPrecision=0;
		}
		break;
	case 1:
		{
			m_fieldType = Geodatabase::FTYPE_LONG;
			GetDlgItem( IDC_EDT_LENGTH )->EnableWindow( TRUE );
			GetDlgItem( IDC_EDT_PRECISION )->EnableWindow( FALSE );
			m_nLength =10;
			m_nPrecision=0;
		}
		break;
	case 2:
		{
			m_fieldType = Geodatabase::FTYPE_DOUBLE;
			GetDlgItem( IDC_EDT_LENGTH )->EnableWindow( TRUE );
			GetDlgItem( IDC_EDT_PRECISION )->EnableWindow( TRUE );
			m_nLength =16;
            m_nPrecision=6;
		}
		break;
	case 3:
		{
			m_fieldType = Geodatabase::FTYPE_STRING;
			GetDlgItem( IDC_EDT_LENGTH )->EnableWindow( TRUE );
			GetDlgItem( IDC_EDT_PRECISION )->EnableWindow( FALSE );
			m_nPrecision=0;
			m_nLength =32;
			
		}
		break;
	case 4:
		{
			m_fieldType = Geodatabase::FTYPE_DATE;
			GetDlgItem( IDC_EDT_LENGTH )->EnableWindow( TRUE );
			GetDlgItem( IDC_EDT_PRECISION )->EnableWindow( FALSE );
			m_nPrecision=0;
			m_nLength =8;
		}
		break;
	/*case 5:
		{
			m_fieldType = GeodataModel::FTYPE_BLOB;
			GetDlgItem( IDC_EDT_LENGTH )->EnableWindow( TRUE );
			GetDlgItem( IDC_EDT_PRECISION )->EnableWindow( FALSE );
			m_nPrecision=0;
		}
		break;*/
	default:
		{
			m_fieldType = Geodatabase::FTYPE_UNKNOWN;
			GetDlgItem( IDC_EDT_LENGTH )->EnableWindow( FALSE );
			GetDlgItem( IDC_EDT_PRECISION )->EnableWindow( FALSE );

		}
		
	}
	UpdateData(FALSE);
}
