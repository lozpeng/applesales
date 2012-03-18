// MapBasicProperPage.cpp : 实现文件
//

#include "stdafx.h"
#include "MapBasicProperPage.h"
#include "CustomScaleDlg.h"

// CMapBasicProperPage 对话框

IMPLEMENT_DYNAMIC(CMapBasicProperPage, CPropertyPage)

CMapBasicProperPage::CMapBasicProperPage()
	: CPropertyPage(CMapBasicProperPage::IDD)
{
	m_dbRefScale = 0;
}

CMapBasicProperPage::~CMapBasicProperPage()
{
}

void CMapBasicProperPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_REF_SCALE, m_cmbRefScale);
}


BEGIN_MESSAGE_MAP(CMapBasicProperPage, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO_REF_SCALE, &CMapBasicProperPage::OnCbnSelchangeComboRefScale)
END_MESSAGE_MAP()

void CMapBasicProperPage::SetMap(Carto::CMapPtr pMap)
{
	m_pMap = pMap;
}

// CMapBasicProperPage 消息处理程序
BOOL CMapBasicProperPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	
	if(!m_pMap)
		return FALSE;

	if(m_pMap->GetReferenceScale()!=0)
	{
		m_dbRefScale = m_customScale = m_pMap->GetReferenceScale();
		
	}
	else
	{	
		m_customScale = m_pMap->GetDisplay()->GetDisplayTransformation().GetMapScale();
	}

	m_cmbRefScale.AddString("无参考比例");
	CString csScale;
	csScale.Format("1:%ld",(long)(m_customScale+0.5));
	m_cmbRefScale.AddString(csScale);

	m_cmbRefScale.AddString("1:1000");
	m_cmbRefScale.AddString("1:10,000");
	m_cmbRefScale.AddString("1:25,000");
	m_cmbRefScale.AddString("1:50,000");
	m_cmbRefScale.AddString("1:100,000");
	m_cmbRefScale.AddString("1:250,000");
	m_cmbRefScale.AddString("1:500,000");
	m_cmbRefScale.AddString("1:1,000,000");
	m_cmbRefScale.AddString("1:25,000,000");
	m_cmbRefScale.AddString("1:50,000,000");
	m_cmbRefScale.AddString("1:100,000,000");
	m_cmbRefScale.AddString("用户自定义比例尺");

	if(m_dbRefScale != 0)
		m_cmbRefScale.SetCurSel(1);
	else
		m_cmbRefScale.SetCurSel(0);

	
	UpdateData(FALSE);

	return TRUE;
}

BOOL  CMapBasicProperPage::OnApply()
{
	if(!IsWindow(m_hWnd))
		return -1;

	UpdateData();

	m_pMap->SetReferenceScale(m_dbRefScale);

	CPropertyPage::OnApply();
}
void CMapBasicProperPage::OnCbnSelchangeComboRefScale()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(m_cmbRefScale.GetCurSel())
	{
	case 0:
		m_dbRefScale = 0;
		break;
	case 1:
		m_dbRefScale = m_customScale;
		break;
	case 2:
		m_dbRefScale = 1000;
		break;
	case 3:
		m_dbRefScale = 10000;
		break;
	case 4:
		m_dbRefScale = 25000;
		break;
	case 5:
		m_dbRefScale = 50000;
		break;
	case 6:
		m_dbRefScale = 100000;
		break;
	case 7:
		m_dbRefScale = 250000;
		break;
	case 8:
		m_dbRefScale = 500000;
		break;
	case 9:
		m_dbRefScale = 1000000;
		break;
	case 10:
		m_dbRefScale = 2500000;
		break;
	case 11:
		m_dbRefScale = 5000000;
		break;
	case 12:
		m_dbRefScale = 10000000;
		break;
	case 13:
		{
			CCustomScaleDlg dlg;
			if(dlg.DoModal() == IDOK)
			{
				m_dbRefScale = m_customScale = dlg.m_dbScale;
				switch((long)m_dbRefScale)
				{
				case 1000:
					m_cmbRefScale.SetCurSel(1);
					break;
				case 10000:
					m_cmbRefScale.SetCurSel(2);
					break;
				case 25000:
					m_cmbRefScale.SetCurSel(3);
					break;
				case 50000:
					m_cmbRefScale.SetCurSel(4);
					break;
				case 100000:
					m_cmbRefScale.SetCurSel(5);
					break;
				case 250000:
					m_cmbRefScale.SetCurSel(6);
					break;
				case 500000:
					m_cmbRefScale.SetCurSel(7);
					break;
				case 1000000:
					m_cmbRefScale.SetCurSel(8);
					break;
				case 2500000:
					m_cmbRefScale.SetCurSel(9);
					break;
				case 5000000:
					m_cmbRefScale.SetCurSel(10);
					break;
				case 10000000:
					m_cmbRefScale.SetCurSel(11);
					break;
				default:
					m_cmbRefScale.DeleteString(1);
					m_cmbRefScale.InsertString(1,(LPCSTR)dlg.m_csScale);
					m_cmbRefScale.SetCurSel(1);
				}
			
			}
		}
		break;
	}
}
