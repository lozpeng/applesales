#include "stdafx.h"
#include "Map.h"
#include "DlgAttrTableProperty.h"
#include "AttributeTable.h"

//------------------------------------------------------------
//---------------�ص����� ö��ϵͳ���� -----------------------
//------------------------------------------------------------
int CALLBACK EnumFontFamilyProc1(
								ENUMLOGFONTEX *lpelfe,    // logical-font data
								NEWTEXTMETRICEX *lpntme,  // physical-font data
								DWORD FontType,           // type of font
								LPARAM lParam             // application-defined data
								)
{
	CDlgAttrTableProperty *pWnd = (CDlgAttrTableProperty *)lParam;
	if ( pWnd->m_cmbFont.FindString( 0, lpelfe->elfLogFont.lfFaceName ) < 0)
	{
		pWnd->m_cmbFont.AddString( lpelfe->elfLogFont.lfFaceName );
	}
	return 1;
}

// CDlgAttrTableProperty �Ի���

IMPLEMENT_DYNAMIC(CDlgAttrTableProperty, CDialog)

CDlgAttrTableProperty::CDlgAttrTableProperty(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAttrTableProperty::IDD, pParent)
	, m_strFont(_T(""))
	, m_iFontSize(8)
{
	m_btnSelColor.EnableOtherButton(_T("������ɫ"));
	m_btnFontColor.EnableOtherButton(_T("������ɫ"));
}

CDlgAttrTableProperty::~CDlgAttrTableProperty()
{
}

void CDlgAttrTableProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_CMB_FONT, m_strFont);
	DDX_CBString(pDX, IDC_CMB_FONTSIZE, m_strFontSize );
	DDX_Control( pDX, IDC_BTN_SELCOLOR,  m_btnSelColor );
	DDX_Control( pDX, IDC_BTN_FONTCOLOR, m_btnFontColor );
	DDX_Control( pDX, IDC_CMB_FONT, m_cmbFont );
	DDX_Control( pDX, IDC_CMB_FONTSIZE, m_cmbFontSize );
}


BEGIN_MESSAGE_MAP(CDlgAttrTableProperty, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgAttrTableProperty::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgAttrTableProperty ��Ϣ�������

BOOL CDlgAttrTableProperty::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	UpdateData( TRUE );

	//��ʼ�������б�
	LOGFONT lf;
	lf.lfCharSet = DEFAULT_CHARSET;
	strcpy(lf.lfFaceName, "");
	
	Control::CAttributeTable *pAttrTable = dynamic_cast<Control::CAttributeTable*>( Framework::IAttributeTable::GetActiveAttributeTable() );
	CClientDC dc((CWnd*)pAttrTable);
	::EnumFontFamiliesEx( (HDC)dc, &lf, (FONTENUMPROC)EnumFontFamilyProc1, (LPARAM)this, 0);
//	m_cmbFont.SetCurSel( 0 );

	//��ʼ�������С�б�
	for ( int i = 5; i <= 11; i++ )
	{
		CString szFontSize;
		szFontSize.Format( "%d", i );
		m_cmbFontSize.AddString( _T(szFontSize) );
	}
	for ( int i = 12; i <= 28; i += 2 )
	{
		CString szFontSize;
		szFontSize.Format( "%d", i );
		m_cmbFontSize.AddString( _T(szFontSize) );
	}
	m_cmbFontSize.AddString(_T("36"));
	m_cmbFontSize.AddString(_T("48"));
	m_cmbFontSize.AddString(_T("72"));
//	m_cmbFontSize.SetCurSel( 3 );

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgAttrTableProperty::SetSelColor( COLORREF colorSel )
{
	m_colorSel = colorSel;
	m_btnSelColor.SetColor( m_colorSel );
}

COLORREF CDlgAttrTableProperty::GetSelColor()
{
	m_colorSel = m_btnSelColor.GetColor();
	return m_colorSel;
}

void CDlgAttrTableProperty::SetTableColor( COLORREF colorFont )
{
	m_btnFontColor.SetColor( colorFont );
	m_colorTableFont = colorFont;
}

COLORREF CDlgAttrTableProperty::GetTableColor()
{
	m_colorTableFont = m_btnFontColor.GetColor();
	return m_colorTableFont;
}

void CDlgAttrTableProperty::SetFont( CString szFont )
{
	m_strFont = szFont;
}

CString CDlgAttrTableProperty::GetFont()
{
	return m_strFont;
}

void CDlgAttrTableProperty::SetFontSize( int fontSize )
{	
	m_iFontSize = fontSize;
	m_strFontSize.Format("%d", fontSize );
}

int CDlgAttrTableProperty::GetFontSize()
{
	return m_iFontSize;
}

void CDlgAttrTableProperty::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData( TRUE );

	m_iFontSize = atoi( m_strFontSize );
	
	OnOK();
}
