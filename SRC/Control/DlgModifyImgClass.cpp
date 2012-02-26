// DlgModifyImgClass.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "DlgModifyImgClass.h"
#include "IDocument.h"
#include "ILayer.h"
#include "IRasterDataset.h"
#include "IWorkspace.h"
#include "RasterWSFactory.h"

// CDlgModifyImgClass 对话框

IMPLEMENT_DYNAMIC(CDlgModifyImgClass, CDialog)

CDlgModifyImgClass::CDlgModifyImgClass(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgModifyImgClass::IDD, pParent)
	, m_strClassfile(_T(""))
	, m_classname(_T(""))
	, m_classvalue(_T(""))
{

}

CDlgModifyImgClass::~CDlgModifyImgClass()
{
}

void CDlgModifyImgClass::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SELCLS_FILE, m_ComboSelfile);
	DDX_Control(pDX, IDC_COMBO_SELCLS_VALUE, m_ComboSelClass);
	DDX_CBString(pDX, IDC_COMBO_SELCLS_FILE, m_strClassfile);
	DDX_Text(pDX, IDC_EDIT_CLSNAME, m_classname);
	DDX_Control(pDX, IDC_BTN_COLORPICK, m_colorbtn);
	DDX_CBString(pDX, IDC_COMBO_SELCLS_VALUE, m_classvalue);
}


BEGIN_MESSAGE_MAP(CDlgModifyImgClass, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_SELCLS_FILE, &CDlgModifyImgClass::OnCbnSelchangeComboSelclsFile)
	ON_BN_CLICKED(IDC_BT_SELCLASSFILE, &CDlgModifyImgClass::OnBnClickedBtSelclassfile)
	ON_BN_CLICKED(IDOK, &CDlgModifyImgClass::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_SELCLS_VALUE, &CDlgModifyImgClass::OnCbnSelchangeComboSelclsValue)
	ON_BN_CLICKED(IDC_BTN_COLORPICK, &CDlgModifyImgClass::OnBnClickedBtnColorpick)
	ON_EN_CHANGE(IDC_EDIT_CLSNAME, &CDlgModifyImgClass::OnEnChangeEditClsname)
	ON_EN_UPDATE(IDC_EDIT_CLSNAME, &CDlgModifyImgClass::OnEnUpdateEditClsname)
	ON_EN_KILLFOCUS(IDC_EDIT_CLSNAME, &CDlgModifyImgClass::OnEnKillfocusEditClsname)
END_MESSAGE_MAP()


// CDlgModifyImgClass 消息处理程序

void CDlgModifyImgClass::OnCbnSelchangeComboSelclsFile()
{
	
	m_ComboSelfile.GetLBText(m_ComboSelfile.GetCurSel(),m_strClassfile);
	
	loadClassinfo();
    

}

void CDlgModifyImgClass::loadClassinfo()
{
	//将之前的类别信息清除
	m_classinfos.clear();
	m_ComboSelClass.ResetContent();
	m_classname="";
	UpdateData(FALSE);
	Geodatabase::IWorkspace *pSrcWp =CRasterWSFactory::GetInstance()->OpenFromFile(m_strClassfile);
	if(!pSrcWp)
	{
		MessageBox("无法打开分类文件","错误");
		return;
	}
	//打开原文件
	Geodatabase::IRasterDatasetPtr pSrcRS =pSrcWp->OpenRasterDataset(m_strClassfile,false);
	if(!pSrcRS)
	{
		MessageBox("无法打开分类文件","错误");
		return;
	}
	std::map<unsigned char,std::string> infos;
	if(!pSrcRS->GetClassesInfo(infos))
	{
		MessageBox("无法获取分类信息","错误");
		return;
	}

	BYTE red[256],green[256],blue[256];
	pSrcRS->GetChannelPalette(1,red,green,blue);
	std::map<unsigned char,std::string>::iterator iter;
	CString strvalue;
	ImgClassInfo info;
	for(iter=infos.begin();iter!=infos.end();iter++)
	{
		strvalue.Format("%d",(int)iter->first);
		m_ComboSelClass.AddString(strvalue);
		//将类别信息保存下来
		info.value =iter->first;
		info.name =iter->second;
		info.red =red[info.value];
		info.green =green[info.value];
		info.blue =blue[info.value];
		m_classinfos.push_back(info);
	}
}
void CDlgModifyImgClass::OnBnClickedBtSelclassfile()
{
	UpdateData();
	CString strFilter = "Image Files(*.tif)|*.tif|All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, "Image Files(*.tif)", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if(dlg.DoModal() == IDOK)
	{
		m_strClassfile = dlg.GetPathName();
		UpdateData(FALSE);
        loadClassinfo();
	}

	
}

void CDlgModifyImgClass::OnBnClickedOk()
{
	UpdateData();
	if(m_strClassfile!="")
	{
        saveClassinfo();
	}
	OnOK();
}

void CDlgModifyImgClass::saveClassinfo()
{
	Geodatabase::IWorkspace *pSrcWp =CRasterWSFactory::GetInstance()->OpenFromFile(m_strClassfile);
	if(!pSrcWp)
	{
		MessageBox("无法打开分类文件","错误");
		return;
	}
	//打开原文件
	Geodatabase::IRasterDatasetPtr pSrcRS =pSrcWp->OpenRasterDataset(m_strClassfile,false);
	if(!pSrcRS)
	{
		MessageBox("无法打开分类文件","错误");
		return;
	}
	std::map<unsigned char,std::string> infos;
	
	BYTE red[256],green[256],blue[256];
	pSrcRS->GetChannelPalette(1,red,green,blue);
	for(size_t i=0;i<m_classinfos.size();i++)
	{
		red[m_classinfos[i].value] =m_classinfos[i].red;
		green[m_classinfos[i].value] =m_classinfos[i].green;
		blue[m_classinfos[i].value] =m_classinfos[i].blue;

		infos[m_classinfos[i].value] =m_classinfos[i].name;
	}
	pSrcRS->SetChannelPalette(1,red,green,blue);
	pSrcRS->SetClassesInfo(infos);

	//判断数据是否已经在地图中，如果在，则替换掉原来的数据源
	Framework::IDocument *pDoc =(Framework::IDocument*)Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppDocument);

	Carto::CMapPtr pMap =pDoc->GetActiveMap();

	Carto::CLayerArray &layers =pMap->GetLayers();

	Carto::ILayerPtr pLayer;
	
	Geodatabase::IRasterDatasetPtr pRaster;
	std::string strfile=m_strClassfile;
	for(int i=0;i<layers.GetSize();i++)
	{
		pLayer =layers.GetAt(i);
		if(!pLayer)
		{
			continue;
		}
		if(pLayer->GetLayerType()==Carto::RasterLayer)
		{
			pRaster =pLayer->GetDataObject();
			if(pRaster)
			{
				//判断是否是分类文件
				if(pRaster->Getname()==strfile)
				{
                    pLayer->SetData(pSrcRS);
					break;
				}
			}
			

		}
	}
}

//当选择值的时候发生的事情
void CDlgModifyImgClass::OnCbnSelchangeComboSelclsValue()
{
	UpdateData();
	for(size_t i=0;i<m_classinfos.size();i++)
	{
		if(m_classinfos[i].value==atoi(m_classvalue))
		{
			m_classname=m_classinfos[i].name.c_str();
            m_colorbtn.SetColor(RGB(m_classinfos[i].red,m_classinfos[i].green,m_classinfos[i].blue));
			break;
		}

	}
	UpdateData(FALSE);

}

BOOL CDlgModifyImgClass::OnInitDialog()
{
	CDialog::OnInitDialog();

	Framework::IDocument *pDoc =(Framework::IDocument*)Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppDocument);

	Carto::CMapPtr pMap =pDoc->GetActiveMap();

	Carto::CLayerArray &layers =pMap->GetLayers();

	Carto::ILayerPtr pLayer;
	
	bool bfind =false;
	Geodatabase::IRasterDatasetPtr pRaster;
	std::map<unsigned char,std::string> infos;
	for(int i=0;i<layers.GetSize();i++)
	{
		pLayer =layers.GetAt(i);
		if(!pLayer)
		{
			continue;
		}
		if(pLayer->GetLayerType()==Carto::RasterLayer)
		{
            pRaster =pLayer->GetDataObject();
			if(pRaster)
			{
				//判断是否是分类文件
				if(pRaster->GetClassesInfo(infos))
				{
					//将文件名加入
                    m_ComboSelfile.AddString(pRaster->Getname().c_str());
					bfind =true;
				}
			}
			/*index= m_ComboSelfile.AddString(pLayer->GetName().c_str());
			m_CmbSrc.SetItemData(index,DWORD_PTR(pLayer.get()));
			index =m_CmbDest.AddString(pLayer->GetName().c_str());
			m_CmbDest.SetItemData(index,DWORD_PTR(pLayer.get()));*/
			
		}
	}
	/*if(bfind)
	{

	}*/
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgModifyImgClass::OnBnClickedBtnColorpick()
{
	COLORREF color = m_colorbtn.GetColor ();

    //将颜色值写入
    for(size_t i=0;i<m_classinfos.size();i++)
	{
        if(m_classinfos[i].value==atoi(m_classvalue))
		{
			m_classinfos[i].red =GetRValue (color);
			m_classinfos[i].green =GetGValue (color);
			m_classinfos[i].blue =GetBValue (color);
			break;
		}

	}
	
		
		
}

void CDlgModifyImgClass::OnEnChangeEditClsname()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	
}

void CDlgModifyImgClass::OnEnUpdateEditClsname()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数，将 EM_SETEVENTMASK 消息发送到控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CDlgModifyImgClass::OnEnKillfocusEditClsname()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	//将名称写入
	for(size_t i=0;i<m_classinfos.size();i++)
	{
		if(m_classinfos[i].value==atoi(m_classvalue))
		{
			m_classinfos[i].name =m_classname;

			break;
		}

	}

}
