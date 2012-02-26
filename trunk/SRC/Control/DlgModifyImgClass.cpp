// DlgModifyImgClass.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Control.h"
#include "DlgModifyImgClass.h"
#include "IDocument.h"
#include "ILayer.h"
#include "IRasterDataset.h"
#include "IWorkspace.h"
#include "RasterWSFactory.h"

// CDlgModifyImgClass �Ի���

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


// CDlgModifyImgClass ��Ϣ�������

void CDlgModifyImgClass::OnCbnSelchangeComboSelclsFile()
{
	
	m_ComboSelfile.GetLBText(m_ComboSelfile.GetCurSel(),m_strClassfile);
	
	loadClassinfo();
    

}

void CDlgModifyImgClass::loadClassinfo()
{
	//��֮ǰ�������Ϣ���
	m_classinfos.clear();
	m_ComboSelClass.ResetContent();
	m_classname="";
	UpdateData(FALSE);
	Geodatabase::IWorkspace *pSrcWp =CRasterWSFactory::GetInstance()->OpenFromFile(m_strClassfile);
	if(!pSrcWp)
	{
		MessageBox("�޷��򿪷����ļ�","����");
		return;
	}
	//��ԭ�ļ�
	Geodatabase::IRasterDatasetPtr pSrcRS =pSrcWp->OpenRasterDataset(m_strClassfile,false);
	if(!pSrcRS)
	{
		MessageBox("�޷��򿪷����ļ�","����");
		return;
	}
	std::map<unsigned char,std::string> infos;
	if(!pSrcRS->GetClassesInfo(infos))
	{
		MessageBox("�޷���ȡ������Ϣ","����");
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
		//�������Ϣ��������
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
		MessageBox("�޷��򿪷����ļ�","����");
		return;
	}
	//��ԭ�ļ�
	Geodatabase::IRasterDatasetPtr pSrcRS =pSrcWp->OpenRasterDataset(m_strClassfile,false);
	if(!pSrcRS)
	{
		MessageBox("�޷��򿪷����ļ�","����");
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

	//�ж������Ƿ��Ѿ��ڵ�ͼ�У�����ڣ����滻��ԭ��������Դ
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
				//�ж��Ƿ��Ƿ����ļ�
				if(pRaster->Getname()==strfile)
				{
                    pLayer->SetData(pSrcRS);
					break;
				}
			}
			

		}
	}
}

//��ѡ��ֵ��ʱ����������
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
				//�ж��Ƿ��Ƿ����ļ�
				if(pRaster->GetClassesInfo(infos))
				{
					//���ļ�������
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
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgModifyImgClass::OnBnClickedBtnColorpick()
{
	COLORREF color = m_colorbtn.GetColor ();

    //����ɫֵд��
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	
}

void CDlgModifyImgClass::OnEnUpdateEditClsname()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// �������� EM_SETEVENTMASK ��Ϣ���͵��ؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CDlgModifyImgClass::OnEnKillfocusEditClsname()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	//������д��
	for(size_t i=0;i<m_classinfos.size();i++)
	{
		if(m_classinfos[i].value==atoi(m_classvalue))
		{
			m_classinfos[i].name =m_classname;

			break;
		}

	}

}
