// DlgFtrDectect.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "DlgFtrDectect.h"
#include "IDocument.h"
#include "ILayer.h"

// CDlgFtrDectect 对话框

IMPLEMENT_DYNAMIC(CDlgFtrDectect, CDialog)

CDlgFtrDectect::CDlgFtrDectect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFtrDectect::IDD, pParent)
	, m_strInImg(_T(""))
	, m_strInImg2(_T(""))
	, m_strTargetFile(_T(""))
	, m_strResultFile(_T(""))
	, m_targetSize(100)
	, m_blockSize(32)
	, m_P3(0.4)
	, m_H3(0.5)
	, m_H4(0.8)
	, m_c1(FALSE)
{

}

CDlgFtrDectect::~CDlgFtrDectect()
{
}

void CDlgFtrDectect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TARGETFILE2, m_strResultFile);
	DDX_Control(pDX, IDC_COMBO1, m_comboTexOri);
	DDX_Text(pDX, IDC_EDIT1, m_targetSize);
	DDX_Text(pDX, IDC_EDIT4, m_blockSize);
	//DDX_Text(pDX, IDC_EDIT_P3, m_P3);
	DDX_Text(pDX, IDC_EDIT_H3, m_H3);
	DDX_Text(pDX, IDC_EDIT_H4, m_H4);
	DDX_Check(pDX, IDC_CHECK1, m_c1);
	DDX_Control(pDX, IDC_COMBO_ORIIMG, m_CmbSrc);
	DDX_Control(pDX, IDC_COMBO_DESTIMG, m_CmbDest);
	DDX_Control(pDX, IDC_COMBO_TARGET2, m_comboTarget);
}


BEGIN_MESSAGE_MAP(CDlgFtrDectect, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_INIMG, &CDlgFtrDectect::OnBnClickedButtonInimg)
	ON_BN_CLICKED(IDC_BUTTON_INIMG2, &CDlgFtrDectect::OnBnClickedButtonInimg2)
	ON_BN_CLICKED(IDC_BUTTON_TARGETFILE, &CDlgFtrDectect::OnBnClickedButtonTargetfile)
	ON_BN_CLICKED(IDC_BUTTON_TARGETFILE2, &CDlgFtrDectect::OnBnClickedButtonTargetfile2)
	ON_BN_CLICKED(IDCANCEL, &CDlgFtrDectect::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDlgFtrDectect::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgFtrDectect 消息处理程序

void CDlgFtrDectect::OnBnClickedButtonInimg()
{
	CFileDialog dlg(true, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"影像数据(*.tif;*.img;*.tiff;*.bmp)|*.tif;*.img;*.tiff;*.bmp|All Files(*.*)|*.*||",this);
	if(dlg.DoModal()==IDOK) 
	{

		m_strInImg =dlg.GetPathName();
		UpdateData(FALSE);
	}

}

void CDlgFtrDectect::OnBnClickedButtonInimg2()
{
	CFileDialog dlg(true, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"影像数据(*.tif;*.img;*.tiff;*.bmp)|*.tif;*.img;*.tiff;*.bmp|All Files(*.*)|*.*||",this);
	if(dlg.DoModal()==IDOK) 
	{

		m_strInImg2 =dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CDlgFtrDectect::OnBnClickedButtonTargetfile()
{
	CFileDialog dlg(true, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"shapefile(*.shp)|*.shp|All file(*.*)|*.*|",this);

	if(dlg.DoModal()==IDOK) 
	{
		m_strTargetFile =dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CDlgFtrDectect::OnBnClickedButtonTargetfile2()
{
	CFileDialog dlg(false, "*.*", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"shapefile(*.shp)|*.shp|All file(*.*)|*.*|",this);

	if(dlg.DoModal()==IDOK) 
	{
		m_strResultFile =dlg.GetPathName();
		UpdateData(FALSE);
	}
}

BOOL CDlgFtrDectect::OnInitDialog()
{
	CDialog::OnInitDialog();

	//
	m_comboTexOri.AddString("0");
	m_comboTexOri.AddString("45");
	m_comboTexOri.AddString("90");
	m_comboTexOri.AddString("135");

	//
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

void CDlgFtrDectect::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CDlgFtrDectect::OnBnClickedOk()
{
	//获得检测文件路径
	Carto::ILayer *pLayer;
	pLayer =(Carto::ILayer*)m_CmbSrc.GetItemData(m_CmbSrc.GetCurSel());
	m_strInImg =pLayer->GetDataObject()->Getname().c_str();

	pLayer =(Carto::ILayer*)m_CmbDest.GetItemData(m_CmbDest.GetCurSel());
	m_strInImg2 =pLayer->GetDataObject()->Getname().c_str();

	pLayer =(Carto::ILayer*)m_comboTarget.GetItemData(m_comboTarget.GetCurSel());
	m_strTargetFile =pLayer->GetDataObject()->Getname().c_str();


	OnOK();
}
