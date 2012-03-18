// CommonPropPage.cpp : 实现文件
//

#include "stdafx.h"

#include "CommonPropPage.h"


// CCommonPropPage 对话框

IMPLEMENT_DYNCREATE(CCommonPropPage, CPropertyPage)

CCommonPropPage::CCommonPropPage()
: CPropertyPage(CCommonPropPage::IDD)

{
	m_psp.dwFlags &= ~PSP_HASHELP;
	m_bAllowSetModified = false;
	m_bModified = false;
	m_pLayer = NULL;
}

CCommonPropPage::~CCommonPropPage()
{
}

void CCommonPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LAYERNAME, m_editLayerName);
	DDX_Control(pDX, IDC_LAYERDESCRIB, m_editLayerDescrib);
	DDX_Control(pDX, IDC_LAYERVISIBLE, m_buttonLayerVisible);
	DDX_Control(pDX, IDC_RADIO_NOSCALE, m_buttonRadio1);
	DDX_Control(pDX, IDC_RADIO_SCALE, m_buttonRadio2);
	DDX_Control(pDX, IDC_EDITMAX, m_editMax);
	DDX_Control(pDX, IDC_EDITMIN, m_editMin);
	//DDX_Control(pDX, IDC_EDITDATASOURCE, m_editDataSource);
}


BEGIN_MESSAGE_MAP(CCommonPropPage, CPropertyPage)
	ON_EN_CHANGE(IDC_LAYERNAME, &CCommonPropPage::OnEnChangeLayername)
	ON_EN_CHANGE(IDC_LAYERDESCRIB, &CCommonPropPage::OnEnChangeLayerdescrib)
	ON_BN_CLICKED(IDC_LAYERVISIBLE, &CCommonPropPage::OnBnClickedLayervisible)
	ON_BN_CLICKED(IDC_RADIO_NOSCALE, &CCommonPropPage::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO_SCALE, &CCommonPropPage::OnBnClickedRadio2)
	ON_EN_CHANGE(IDC_EDITMAX, &CCommonPropPage::OnEnChangeLayername)
	ON_EN_CHANGE(IDC_EDITMIN, &CCommonPropPage::OnEnChangeLayerdescrib)
END_MESSAGE_MAP()


// CCommonPropPage 消息处理程序

BOOL CCommonPropPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	if (m_pLayer == NULL)
	{
		return FALSE;
	}

	//处理层名描述
	m_editLayerName.SetWindowText( m_pLayer->GetName().c_str() );
	m_editLayerDescrib.SetWindowText( m_pLayer->GetLayerDesciption().c_str() );

	//处理可见
	m_buttonLayerVisible.SetCheck(m_pLayer->GetVisible());

	//处理范围
	if (m_pLayer->GetEnableScaleRange())
	{
		m_buttonRadio1.SetCheck(0);
		m_buttonRadio2.SetCheck(1);

		m_editMax.EnableWindow(TRUE);
		m_editMin.EnableWindow(TRUE);

		if ( m_pLayer->GetScaleRangeMax() < 1 )
		{
			m_pLayer->SetScaleRangeMax(1);
		}
		if ( m_pLayer->GetScaleRangeMin() < 1)
		{
			m_pLayer->SetScaleRangeMin(1);
		}
		CString scaleValue;
		double intValue = m_pLayer->GetScaleRangeMax();
		scaleValue.Format("%d" , (int)intValue);
		m_editMax.SetWindowText(scaleValue);

		intValue = m_pLayer->GetScaleRangeMin() ;
		scaleValue.Format("%d" , (int)intValue);
		m_editMin.SetWindowText(scaleValue);
	}
	else
	{
		m_buttonRadio1.SetCheck(1);
		m_buttonRadio2.SetCheck(0);

		m_editMax.EnableWindow(FALSE);
		m_editMin.EnableWindow(FALSE);
	}

	//处理数据源
	/*otDataSource::IDataLayerPtr dataLayer = m_pLayer->GetDataSource();
	otDataSource::IDataSourcePtr dataSource = dataLayer->GetDataSource();

	CString allInfo,path,name;
	SYSTEM::CString dataBaseName = dataSource->GetDatabaseName();
	path.Format("路径:%s" , dataBaseName);

	SYSTEM::CString dataName = dataLayer->GetName();
	name.Format("名称:%s" , dataName);

	if (m_pLayer->GetLayerType() == Carto::eFeatureLayer)
	{
		CString featureTypeName;
		Carto::IFeatureLayerPtr featureLayer = m_pLayer;
		FEATURE_TYPE featureType = featureLayer->GetFeatureType();
		if (featureType == OT_FEATURE_POINT)
		{
			featureTypeName.Format("几何体类型:点");
		}
		else if (featureType == OT_FEATURE_LINE)
		{
			featureTypeName.Format("几何体类型:线");
		}
		else if (featureType == OT_FEATURE_POLYGON)
		{
			featureTypeName.Format("几何体类型:面");
		}
		allInfo.Format("%s\r\n%s\r\n%s" , name , path , featureTypeName);
	}
	else if (m_pLayer->GetLayerType() == Carto::eRasterLayer)
	{
		allInfo.Format("%s\r\n%s" , name , path);
	}

	m_editDataSource.SetWindowText(allInfo);*/

	m_bAllowSetModified = true;
	return TRUE;  
	// 异常: OCX 属性页应返回 FALSE
}

void CCommonPropPage::SetLayer(Carto::ILayer* layer)
{
	m_pLayer = layer;
}
void CCommonPropPage::OnEnChangeLayername()
{
	if ( !m_bAllowSetModified )
	{
		return;
	}
	SetModified(TRUE);
}

BOOL CCommonPropPage::OnApply()
{
	if (!m_bModified)
	{
		return TRUE;
	}
	if (!ValidateCheck())
	{
		return FALSE;
	}

	SetValuesToLayer();
	m_bModified = false;
	return CPropertyPage::OnApply();
}

void CCommonPropPage::OnCancel()
{

	CPropertyPage::OnCancel();
}

void CCommonPropPage::OnOK()
{
	//if (!ValidateCheck())
	//{
	//	return;
	//}
	//SetValuesToLayer();
	CPropertyPage::OnOK();
}

void CCommonPropPage::OnEnChangeLayerdescrib()
{
	if ( !m_bAllowSetModified )
	{
		return;
	}
	SetModified(TRUE);
}

void CCommonPropPage::OnBnClickedLayervisible()
{
	if ( !m_bAllowSetModified )
	{
		return;
	}
	SetModified(TRUE);
}

void CCommonPropPage::SetValuesToLayer()
{
	CString tmpString;
	m_editLayerName.GetWindowText(tmpString);
	
	m_pLayer->SetName(std::string(tmpString));

	m_editLayerDescrib.GetWindowText(tmpString);
	
	m_pLayer->SetLayerDescription(std::string(tmpString));

	m_pLayer->SetVisible(m_buttonLayerVisible.GetCheck());

	m_pLayer->SetEnableScaleRange(m_buttonRadio2.GetCheck());

	if (m_pLayer->GetEnableScaleRange())
	{
		CString valueRange;
		m_editMin.GetWindowText(valueRange);
		m_pLayer->SetScaleRangeMin(atof(valueRange));

		m_editMax.GetWindowText(valueRange);
		m_pLayer->SetScaleRangeMax( atof(valueRange));
	}
	
}

BOOL CCommonPropPage::OnSetActive()
{
	return CPropertyPage::OnSetActive();
}
void CCommonPropPage::OnBnClickedRadio1()
{
	if ( !m_bAllowSetModified )
	{
		return;
	}
	SetModified(TRUE);
	m_editMax.EnableWindow(FALSE);
	m_editMin.EnableWindow(FALSE);
}

void CCommonPropPage::OnBnClickedRadio2()
{
	if ( !m_bAllowSetModified )
	{
		return;
	}
	SetModified(TRUE);
	m_editMax.EnableWindow(TRUE);
	m_editMin.EnableWindow(TRUE);

	if ( m_pLayer->GetScaleRangeMax() < 1 )
	{
		m_pLayer->SetScaleRangeMax(1);
	}
	if ( m_pLayer->GetScaleRangeMin() < 1)
	{
		m_pLayer->SetScaleRangeMin(1);
	}
	CString scaleValue;
	double intValue = m_pLayer->GetScaleRangeMax();
	scaleValue.Format("%d" , (int)intValue);
	m_editMax.SetWindowText(scaleValue);

	intValue =  m_pLayer->GetScaleRangeMin();
	scaleValue.Format("%d" , (int)intValue);
	m_editMin.SetWindowText(scaleValue);
}

BOOL CCommonPropPage::ValidateCheck()
{
	if (m_buttonRadio2.GetCheck())
	{
		CString valueRange;
		m_editMin.GetWindowText(valueRange);
		double doubleValue = atof(valueRange);

		if (doubleValue < 1.000000)
		{
			::MessageBox(this->GetParent()->m_hWnd , "范围参数不能小于1" , "警告" , MB_OK);
			
			m_editMin.SetFocus();
			m_editMin.SetSel( 0 , -1 );
			return FALSE;
		}

		m_editMax.GetWindowText(valueRange);
		doubleValue = atof(valueRange);

		if (doubleValue < 1.000000)
		{
			::MessageBox(this->GetParent()->m_hWnd , "范围参数不能小于0" , "警告" , MB_OK);
			
			m_editMax.SetFocus();
			m_editMax.SetSel( 0 , -1 );
			return FALSE;
		}
	}

	return TRUE;
}

void CCommonPropPage::SetModified(BOOL bChanged)
{
	CPropertyPage::SetModified(bChanged);
	m_bModified = bChanged;
}
BOOL CCommonPropPage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_KEYDOWN)
	{
		if ( pMsg->hwnd == GetDlgItem(IDC_EDITMIN)->m_hWnd )
		{
			if ( GetKeyState(VK_CONTROL) < 0 ||::GetKeyState(VK_SHIFT) < 0)
			{
				return TRUE;
			}
		}

		if ( pMsg->hwnd == GetDlgItem(IDC_EDITMAX)->m_hWnd )
		{
			if ( GetKeyState(VK_CONTROL) < 0 ||::GetKeyState(VK_SHIFT) < 0)
			{
				return TRUE;
			}
		}
	}

	return CPropertyPage::PreTranslateMessage(pMsg);
}

void CCommonPropPage::OnChangeScaleMax()
{
	SetModified(TRUE);
}
void CCommonPropPage::OnChangeScaleMin()
{
	SetModified(TRUE);
}