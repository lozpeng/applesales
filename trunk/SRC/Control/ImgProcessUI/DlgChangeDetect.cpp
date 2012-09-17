// DlgChangeDetect.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "DlgChangeDetect.h"
#include "IDocument.h"
#include "ILayer.h"
// CDlgChangeDetect 对话框

IMPLEMENT_DYNAMIC(CDlgChangeDetect, CDialog)

CDlgChangeDetect::CDlgChangeDetect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChangeDetect::IDD, pParent)
	, m_strResult(_T(""))
	, m_bLoadShp(TRUE)
	, m_dCor(0.4)
	, m_nSize(100)
	, m_dblH1(0.3)
	, m_dblH2(0.8)
	, m_dblP1(0.4)
	, m_dblP2(0.4)
	, m_dblW1(0.4)
	, m_dblW2(1.0)
	, n_strRel2(_T(""))
	, m_strResult3(_T(""))
	, m_strRelMap(_T(""))
	, m_nBlockSize(21)
	, m_strResult2(_T(""))
{

}

CDlgChangeDetect::~CDlgChangeDetect()
{
}

void CDlgChangeDetect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ORIIMG, m_CmbSrc);
	DDX_Control(pDX, IDC_COMBO_DESTIMG, m_CmbDest);
	DDV_MinMaxDouble(pDX, m_dCor, 0.2, 1.0);
	DDX_Text(pDX, IDC_EDIT1, m_nSize);
	DDV_MinMaxInt(pDX, m_nSize, 10, 500);
	DDX_Text(pDX, IDC_EDIT_H1, m_dblH1);
	DDX_Text(pDX, IDC_EDIT_H2, m_dblH2);
	DDX_Text(pDX, IDC_EDIT_P1, m_dblP1);
	DDX_Text(pDX, IDC_EDIT4, m_nBlockSize);
	DDX_Text(pDX, IDC_EDIT_RELSHP2, m_strResult2);
	DDX_Control(pDX, IDC_COMBO_TARGET, m_comboTarget);
}


BEGIN_MESSAGE_MAP(CDlgChangeDetect, CDialog)
	ON_BN_CLICKED(IDC_BTN_SELCHASHP, &CDlgChangeDetect::OnBnClickedBtnSelchashp)
	ON_BN_CLICKED(IDOK, &CDlgChangeDetect::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELCHASHP4, &CDlgChangeDetect::OnBnClickedBtnSelchashp4)
	ON_EN_CHANGE(IDC_EDIT_RELSHP, &CDlgChangeDetect::OnEnChangeEditRelshp)
	ON_CBN_SELCHANGE(IDC_COMBO_DESTIMG, &CDlgChangeDetect::OnCbnSelchangeComboDestimg)
END_MESSAGE_MAP()


// CDlgChangeDetect 消息处理程序

void CDlgChangeDetect::OnBnClickedBtnSelchashp()
{
	UpdateData();
	CFileDialog dlg(false, "*.shp", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"shapefile(*.shp)|*.shp||",this);
	if(dlg.DoModal()==IDOK) 
	{
		m_strResult =dlg.GetPathName();
		UpdateData(FALSE);
	}
	
}

void CDlgChangeDetect::OnBnClickedOk()
{
	UpdateData();
    if(m_strResult2=="")
	{
        MessageBox("请选择检测结果文件");
		return;

	}
	//获得检测文件路径
	Carto::ILayer *pLayer;
	pLayer =(Carto::ILayer*)m_CmbSrc.GetItemData(m_CmbSrc.GetCurSel());
	m_strSrc =pLayer->GetDataObject()->Getname().c_str();

	pLayer =(Carto::ILayer*)m_CmbDest.GetItemData(m_CmbDest.GetCurSel());
	m_strDest =pLayer->GetDataObject()->Getname().c_str();

	pLayer =(Carto::ILayer*)m_comboTarget.GetItemData(m_comboTarget.GetCurSel());
	m_strResult =pLayer->GetDataObject()->Getname().c_str();

	OnOK();
}

BOOL CDlgChangeDetect::OnInitDialog()
{
	CDialog::OnInitDialog();

	Framework::IDocument *pDoc =(Framework::IDocument*)Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppDocument);

	Carto::CMapPtr pMap =pDoc->GetActiveMap();

	Carto::CLayerArray &layers =pMap->GetLayers();

	Carto::ILayerPtr pLayer;
	int index;
	bool bfind =false;
	for(int i=0;i<layers.GetSize();i++)
	{
        pLayer =layers.GetAt(i);
		if(!pLayer)
		{
			continue;
		}
		if(pLayer->GetLayerType()==Carto::RasterLayer)
		{
			index= m_CmbSrc.AddString(pLayer->GetName().c_str());
			m_CmbSrc.SetItemData(index,DWORD_PTR(pLayer.get()));
			index =m_CmbDest.AddString(pLayer->GetName().c_str());
			m_CmbDest.SetItemData(index,DWORD_PTR(pLayer.get()));
			bfind =true;
		}
		else if(pLayer->GetLayerType()==Carto::FeatureLayer)
		{
			index= m_comboTarget.AddString(pLayer->GetName().c_str());
			m_comboTarget.SetItemData(index,DWORD_PTR(pLayer.get()));
			bfind = true;
		}
	}
	if(!bfind)
	{
		return FALSE;
	}
	m_CmbSrc.SetCurSel(0);
    m_CmbDest.SetCurSel(0);
	m_comboTarget.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgChangeDetect::OnBnClickedCheckLoadchange()
{
	
}

void CDlgChangeDetect::OnBnClickedBtnSelchashp2()
{
	UpdateData();
	CFileDialog dlg(false, "*.shp", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"shapefile(*.shp)|*.shp||",this);
	if(dlg.DoModal()==IDOK) 
	{
		n_strRel2 =dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CDlgChangeDetect::OnBnClickedBtnSelchashp3()
{
	UpdateData();
	CFileDialog dlg(false, "*.shp", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"shapefile(*.shp)|*.shp||",this);
	if(dlg.DoModal()==IDOK) 
	{
		m_strResult2 =dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CDlgChangeDetect::OnBnClickedBtnRelmap()
{
	CFileDialog dlg(false, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"影像数据(*.tif;*.img;*.tiff;*.bmp)|*.tif;*.img;*.tiff;*.bmp|All Files(*.*)|*.*||",this);
	if(dlg.DoModal()==IDOK) 
	{

		m_strRelMap =dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CDlgChangeDetect::OnBnClickedBtnSelchashp4()
{
	UpdateData();
	CFileDialog dlg(false, "*.shp", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"shapefile(*.shp)|*.shp||",this);
	if(dlg.DoModal()==IDOK) 
	{
		m_strResult2 =dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CDlgChangeDetect::OnEnChangeEditRelshp()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CDlgChangeDetect::OnCbnSelchangeComboDestimg()
{
	// TODO: 在此添加控件通知处理程序代码
}
