// DlgFeatureInfo.cpp : 实现文件
//
 
#include "stdafx.h"
#include "DlgFeatureInfo.h"
#include "IFeatureClass.h"
#include "../resource.h"

// CDlgFeatureInfo 对话框

IMPLEMENT_DYNAMIC(CDlgFeatureInfo, CDialog)

CDlgFeatureInfo::CDlgFeatureInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFeatureInfo::IDD, pParent)
{
   m_pMap =NULL;
}

CDlgFeatureInfo::~CDlgFeatureInfo()
{
}

void CDlgFeatureInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_FEATURES, m_Features);
	DDX_Control(pDX, IDC_LIST_FEATURE_INFO, m_FeatureInfo);
}


BEGIN_MESSAGE_MAP(CDlgFeatureInfo, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_FEATURES, &CDlgFeatureInfo::OnTvnSelchangedTreeFeatures)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgFeatureInfo 消息处理程序

void CDlgFeatureInfo::OnTvnSelchangedTreeFeatures(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	HTREEITEM hCurTreeItem = pNMTreeView->itemNew.hItem;

	if (m_Features.GetChildItem(hCurTreeItem))
	{
		*pResult = 0;
		return;
	}

	//判断是不是根节点
	if(m_Features.GetRootItem()==hCurTreeItem)
	{
		*pResult = 0;
		return;
	}

	m_FeatureInfo.DeleteAllItems();
	
	int iLayer = m_Features.GetItemData(hCurTreeItem);
	
	long lRecNo = _wtol((LPCTSTR)m_Features.GetItemText(hCurTreeItem));

	Carto::IFeatureLayerPtr pLayer =m_layers[iLayer];

	long l = 0;
	CString csName;
	CString csValue;

	long lFieldtype =0;

	double dValue;
	long lValue;

	Geodatabase::IFeatureClassPtr pFeatureClass=pLayer->GetDataObject();

	Geodatabase::CFeaturePtr pFeature =pFeatureClass->GetFeature(lRecNo);

	if(!pFeature)
	{
		*pResult = 0;
		return;
	}


	long lNumFields =pFeatureClass->FieldCount();


	for ( l = 0; l < lNumFields; l++)
	{

		//得到字段名
		csName =pFeatureClass->GetField(l+1)->GetName().c_str();
		//得到字段类型
		lFieldtype =pFeatureClass->GetField(l+1)->GetType();

		switch(lFieldtype)
		{

		case Geodatabase::FTYPE_STRING:    //字符型
			{
				csValue =pFeature->GetValue(l+1).GetasString().c_str();

				csValue.TrimLeft();
				m_FeatureInfo.InsertItem(l, csName);
				m_FeatureInfo.SetItem(l, 1, LVIF_TEXT, csValue, 0, 0, 0, NULL);

			}
			break;
		case Geodatabase::FTYPE_DATE:    //日期型
			{
				m_FeatureInfo.InsertItem(l, csName);
				m_FeatureInfo.SetItem(l, 1, LVIF_TEXT, _T(""), 0, 0, 0, NULL);
			}
			break;
		case Geodatabase::FTYPE_DOUBLE:
		case Geodatabase::FTYPE_FLOAT:    //浮点型
			{
				dValue =pFeature->GetValue(l+1).GetAsDouble();

				csValue.Format(_T("%.8f"),dValue);

				m_FeatureInfo.InsertItem(l, csName);
				m_FeatureInfo.SetItem(l, 1, LVIF_TEXT, csValue, 0, 0, 0, NULL);

			}
			break;
		case Geodatabase::FTYPE_BOOL:    //逻辑型
			{
                
			}
			break;
		case Geodatabase::FTYPE_LONG:    //整型
			{
				lValue =pFeature->GetValue(l+1).m_Var.iVal;

				csValue.Format(_T("%d"),lValue);

				m_FeatureInfo.InsertItem(l, csName);
				m_FeatureInfo.SetItem(l, 1, LVIF_TEXT, csValue, 0, 0, 0, NULL);
			}
			break;

		default:
			m_FeatureInfo.InsertItem(l, csName);
			m_FeatureInfo.SetItem(l, 1, LVIF_TEXT, _T(""), 0, 0, 0, NULL);
			break;
		}

	}

	*pResult = 0;
}

BOOL CDlgFeatureInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString csBuf;

	csBuf = "字段名";
	m_FeatureInfo.InsertColumn(0, csBuf, LVCFMT_LEFT, 80);
	csBuf = "值";
	m_FeatureInfo.InsertColumn(1, csBuf, LVCFMT_LEFT, 200);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgFeatureInfo::SetMap(Carto::CMap *pMap)
{
	m_pMap =pMap;
}

void CDlgFeatureInfo::Refresh()
{
	m_Features.DeleteAllItems();
	m_FeatureInfo.DeleteAllItems();
	HTREEITEM hRoot = m_Features.InsertItem(_T("选择要素"));

	if(!m_pMap)
	{
		return;
	}
    m_layers.clear();

	//获得选中要素的图层
	Carto::CLayerArray &layers =m_pMap->GetLayers();

	Carto::ILayerPtr pLayer;
	Carto::IFeatureLayerPtr pFeatureLayer;
	Geodatabase::ISelctionSetPtr pSel;
	long lRecCount = 0;
	CString csFeatureNo;

	for(int i=0;i<layers.GetSize();i++)
	{
		pLayer =layers.GetAt(i);
		if(pLayer->GetLayerType()==Carto::FeatureLayer)
		{
			pFeatureLayer =pLayer;
			pSel =pFeatureLayer->GetSelection();
			if(!pSel)
			{
				continue;
			}
			if(pSel->Count()==0)
			{
				//没有选中
				continue;
			}
			m_layers.push_back(pFeatureLayer);


			//将图层和要素加入到树中
			HTREEITEM hLayer = m_Features.InsertItem(CString(pFeatureLayer->GetName().c_str()), hRoot, TVI_LAST);

			pSel->ResetIndex();
			while(!pSel->IsEOF())
			{
				csFeatureNo.Format(_T("%d"), pSel->NextID());
				HTREEITEM hFeature = m_Features.InsertItem(csFeatureNo, hLayer, TVI_LAST);
				m_Features.SetItemData(hFeature, m_layers.size()-1);
			}
			


		}
	}

	
	HTREEITEM hLayer = m_Features.GetChildItem(hRoot);
	if (hLayer)
	{
		HTREEITEM hFeature = m_Features.GetChildItem(hLayer);
		if (hFeature)
			m_Features.SelectItem(hFeature);
	}
}

BOOL CDlgFeatureInfo::Create()
{
	return CDialog::Create(CDlgFeatureInfo::IDD);
}
void CDlgFeatureInfo::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_layers.clear();
	CDialog::OnClose();
}
