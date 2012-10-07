// DlgFieldStatics.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Map.h"
#include "DlgFieldStatics.h"
#include "AttributeTable.h"
#include <cmath>

// CDlgFieldStatics �Ի���

IMPLEMENT_DYNAMIC(CDlgFieldStatics, CDialog)

CDlgFieldStatics::CDlgFieldStatics(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFieldStatics::IDD, pParent)
	, m_szOutputStatics(_T(""))
	, m_szField(_T(""))
	, m_bOnlyCalSel(TRUE)
{

}

CDlgFieldStatics::~CDlgFieldStatics()
{
}

#define IDC_BTN_OUTPUT                  5006
#define IDC_CHK_SEL                     5004

void CDlgFieldStatics::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_SELFIELD, m_cmbField);
	DDX_Text(pDX, IDC_EDT_OUTPUTRESULT, m_szOutputStatics);
	DDX_Check(pDX, IDC_CHK_SEL, m_bOnlyCalSel);
}

BEGIN_MESSAGE_MAP(CDlgFieldStatics, CDialog)
	ON_CBN_SELCHANGE(IDC_CMB_SELFIELD, &CDlgFieldStatics::OnCbnSelchangeCmbSelfield)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_OUTPUT, &CDlgFieldStatics::OnBnClickedBtnOutput)
	ON_BN_CLICKED(IDC_CHK_SEL, &CDlgFieldStatics::OnBnClickedChkSel)
END_MESSAGE_MAP()


// CDlgFieldStatics ��Ϣ�������

BOOL CDlgFieldStatics::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	for ( int i = 0; i < m_vecCalFields.size(); i++)
		m_cmbField.AddString( m_vecCalFields[i]->szFieldName.c_str() );
	
	m_cmbField.SetCurSel( 0 );
	m_cmbField.GetLBText( m_cmbField.GetCurSel(), m_szField );

	UpdateData( TRUE );
	Statics( m_szField );
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgFieldStatics::OnCbnSelchangeCmbSelfield()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData( TRUE );

	m_cmbField.GetLBText( m_cmbField.GetCurSel(), m_szField );
	Statics( m_szField );
}

void CDlgFieldStatics::InitFieldsValues( std::vector<LP_CAL_FIELDVALUE> &vecFields )
{
	m_vecCalFields.clear();

	for ( int i = 0; i < vecFields.size(); i++)
		m_vecCalFields.push_back( vecFields[i] );

}

void CDlgFieldStatics::OnDestroy()
{
	CDialog::OnDestroy();

	for ( int i = 0; i < m_vecCalFields.size(); i++)
		delete m_vecCalFields[i];

	// TODO: �ڴ˴������Ϣ����������
}

BOOL CDlgFieldStatics::Statics( const char *szFieldName )
{
	if ( m_vecCalFields.size() == 0)
		return FALSE;
	
	CalFieldValue calField;
	int iFiedIndex = -1;
	calField.szFieldName = szFieldName;

	//---�����ֶ�----
	for ( int i = 0; i < m_vecCalFields.size(); i++ )
	{
		if ( *m_vecCalFields[i] == calField )
		{
			iFiedIndex = i;
			break;
		}	
	}

	if ( iFiedIndex == -1 )
		return FALSE;

	//�ֶ�����
	CString szType = m_vecCalFields[iFiedIndex]->szType.c_str();
	
	//��ȡ�����ֵ
	GetCalculateValues( m_vecCalFields[iFiedIndex]->szFieldName.c_str() );

	//-------�������ͳ��ֵ-----------------
	//ֵ������
	long nCount = m_vecCalValues.size();
	
	//
	double dMaximum = 0.0;		//��Сֵ
	double dMinimum = 0.0;		//���ֵ
	if ( nCount > 0)
	{
		dMaximum = m_vecCalValues[0];
		dMinimum = m_vecCalValues[0];
	}
	
	double dSum =0.0;			//��
	double dMean = 0.0;			//ƽ��ֵ 
	double dStdDeviation = 0.0;	//��׼��

	//����͡���Сֵ�� ���ֵ��ƽ��ֵ
	for ( int i = 0; i< nCount; i++)
	{
		double dValue = m_vecCalValues[i];

		if ( dMaximum < dValue )
			dMaximum = dValue;

		if ( dMinimum > dValue )
			dMinimum = dValue;
		
		dSum += dValue;
	}

	if ( nCount >0 )
		dMean = dSum / nCount;
		
	//�����׼��
	double dStdDevSum = 0.0;
	for ( int i = 0; i< nCount; i++)
	{
		double dValue = m_vecCalValues[i];
		dStdDevSum += std::pow( dValue - dMean, 2 );
	}

	if ( nCount > 0)
		dStdDeviation = std::sqrt( dStdDevSum / nCount );

	//-------������-----------------
	OutPutResult( szType, nCount, dMinimum, dMaximum, dSum, dMean, dStdDeviation );

	return TRUE;
}

void CDlgFieldStatics::OutPutResult( const char *szType, 
				  long nCount, double dMinimum, 
				  double dMaxMum,
				  double dSum,
				  double dMean,
				  double dStdDeviation )
{
	CString szOutPut = "";
	CString szFormat = "";

	szOutPut += "ֵ������ ";
	szFormat.Format( "%d", nCount );
	szOutPut += szFormat;
	szOutPut += "\r\n";
	
	CString szCompare( szType );
	if ( szCompare == "FLOAT" || szCompare == "DOUBLE" )
	{
		szOutPut += "��Сֵ�� ";
		szFormat.Format( "%.6f", dMinimum );
		szOutPut += szFormat;
		szOutPut += "\r\n";

		szOutPut += "���ֵ�� ";
		szFormat.Format( "%.6f", dMaxMum );
		szOutPut += szFormat;
		szOutPut += "\r\n";

		szOutPut += "        ";
		szFormat.Format( "�ͣ� %.6f", dSum );
		szOutPut += szFormat;
		szOutPut += "\r\n";

		szOutPut += "ƽ��ֵ�� ";
		szFormat.Format( "%.6f", dMean );
		szOutPut += szFormat;
		szOutPut += "\r\n";

		szOutPut += "��׼� ";
		szFormat.Format( "%.6f", dStdDeviation );
		szOutPut += szFormat;
		szOutPut += "\r\n";
	}
	else if( szCompare == "SHORT" || szCompare == "LONG" )
	{
		szOutPut += "��Сֵ�� ";
		szFormat.Format( "%d", (long)dMinimum );
		szOutPut += szFormat;
		szOutPut += "\r\n";

		szOutPut += "���ֵ�� ";
		szFormat.Format( "%d", (long)dMaxMum );
		szOutPut += szFormat;
		szOutPut += "\r\n";

		szOutPut += "        ";
		szFormat.Format( "�ͣ� %d", (long)dSum );
		szOutPut += szFormat;
		szOutPut += "\r\n";

		szOutPut += "ƽ��ֵ�� ";
		szFormat.Format( "%d", (long)dMean );
		szOutPut += szFormat;
		szOutPut += "\r\n";

		szOutPut += "��׼� ";
		szFormat.Format( "%.6f", dStdDeviation );
		szOutPut += szFormat;
		szOutPut += "\r\n";
	}

	m_szOutputStatics = szOutPut;
	UpdateData( FALSE );
}

void   CDlgFieldStatics::GetCalculateValues( const char *  szFieldName )
{
	m_vecCalValues.clear();

	Control::CAttributeTable *pAttrTable = dynamic_cast<Control::CAttributeTable*>( Framework::IAttributeTable::GetActiveAttributeTable() );
	Geodatabase::IFeatureClassPtr pFeatureClass = pAttrTable->GetFeatureClass();
	long nFieldIndex = pFeatureClass->FindField( szFieldName );

	Geodatabase::CSimpleQuery indexquery;
	indexquery.AddField(szFieldName);
	//����ִ��һ�β�ѯ��������Ҫ��ʾ��Ҫ�ص�ID�����
	Geodatabase::IRowPtr pRow;
	Geodatabase::ICursorPtr pCursor =pFeatureClass->Query(&indexquery);
	if(!pCursor)
		return;
	
	if ( m_bOnlyCalSel )
	{
		std::vector<long> vCalRows;
		pAttrTable->GetSelectRows( vCalRows, FEAUTE_INDEX );
		
		long nCalNum = 0;
		while(!pCursor->IsEOF())
		{
			++nCalNum;

			pRow =pCursor->NextRow();
			if ( std::find( vCalRows.begin(), vCalRows.end(), pRow->GetId() ) != vCalRows.end() )
				m_vecCalValues.push_back( pRow->GetValue( 0 ).GetAsDouble() );
						
			if ( nCalNum >= vCalRows.size() )
				break;
		}
	}
	else 
	{
		while(!pCursor->IsEOF())
		{
			pRow =pCursor->NextRow();
			
			m_vecCalValues.push_back( pRow->GetValue( nFieldIndex ).GetAsDouble() );
		}
	}
}

void CDlgFieldStatics::OnBnClickedBtnOutput()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString csFilter = "TXT (*.txt)|*.txt|";
	CFileDialog dlgSave(FALSE, "TXT", "ͳ��������", OFN_HIDEREADONLY, csFilter);

	if( IDOK == dlgSave.DoModal())
	{
		CString csSavePath = dlgSave.GetPathName();	
		CFile file( csSavePath, CFile::modeWrite |  CFile::modeCreate);
		
		file.Write( m_szOutputStatics, strlen( m_szOutputStatics ) );
		
		file.Close();
	}

	
}

void CDlgFieldStatics::OnBnClickedChkSel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData( TRUE );

	m_cmbField.GetLBText( m_cmbField.GetCurSel(), m_szField );
	Statics( m_szField );
}
