// DlgFeatureAttriEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgFeatureAttriEdit.h"
#include "FeatureLayer.h"
#include "IWorkspace.h"

// CDlgFeatureAttriEdit 对话框

IMPLEMENT_DYNAMIC(CDlgFeatureAttriEdit, CDialog)

CDlgFeatureAttriEdit::CDlgFeatureAttriEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFeatureAttriEdit::IDD, pParent)
{
    m_hpreTreeItem =NULL;
}

CDlgFeatureAttriEdit::~CDlgFeatureAttriEdit()
{
}

void CDlgFeatureAttriEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FEATURE_PROPLIST, m_propListLoc);
	DDX_Control(pDX, IDC_TREE_SELFEATURES, m_SelFeatureTree);
}


BEGIN_MESSAGE_MAP(CDlgFeatureAttriEdit, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_SELFEATURES, OnSelchangedTreeFeatures)
	ON_NOTIFY(TVN_SELCHANGING, IDC_TREE_SELFEATURES, &CDlgFeatureAttriEdit::OnTvnSelchangingTreeSelfeatures)
	ON_NOTIFY(NM_CLICK, IDC_TREE_SELFEATURES, &CDlgFeatureAttriEdit::OnNMClickTreeSelfeatures)
	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()


// CDlgFeatureAttriEdit 消息处理程序

BOOL CDlgFeatureAttriEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化


	//创建属性列表
    CRect rectPropList;
	m_propListLoc.GetClientRect (&rectPropList);
	m_propListLoc.MapWindowPoints (this, &rectPropList);

	m_PropList.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectPropList, this, (UINT)-1);
	
	m_PropList.EnableHeaderCtrl (TRUE,"属性名","值");

	m_PropList.SetVSDotNetLook ();

	m_PropList.SetShowDragContext ();

	Refresh();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



//树中当前选择要素发生改变
void CDlgFeatureAttriEdit::OnSelchangedTreeFeatures(NMHDR* pNMHDR, LRESULT* pResult) 
{
	

    using namespace Geodatabase;
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	HTREEITEM hCurTreeItem = pNMTreeView->itemNew.hItem;

	if (m_SelFeatureTree.GetChildItem(hCurTreeItem))
	{
		*pResult = 0;
		return;
	}

	if(m_hpreTreeItem==hCurTreeItem)
	{
		*pResult = 0;
		return;
	}
	if(m_hpreTreeItem != NULL)
	{
		if(m_hpreTreeItem!=hCurTreeItem)
		{
			//将之前修改的属性保存
			SavePreAttribute();


		}


	}

   	//清空属性表
	m_PropList.RemoveAll();

	Carto::CFeatureLayer *pLayer = (Carto::CFeatureLayer *)m_SelFeatureTree.GetItemData(hCurTreeItem);
	if (!pLayer)
		return;
	if(!pLayer->GetDataObject())
		return;

	IFeatureClass* pFeatureClass =dynamic_cast<IFeatureClass*>(pLayer->GetDataObject().get());
	IWorkspace *pWorkspace =pFeatureClass->GetWorkspace();

	long lRecNo = atol((LPCTSTR)m_SelFeatureTree.GetItemText(hCurTreeItem));

	CFeaturePtr pFeature =pFeatureClass->GetFeature(lRecNo);

	if(!pFeature)
	{
		return;
	}


	long l = 0;
	CString csName = _T("");
	CString csValue;
	double dValue;
	long   lValue;

	//获取要素属性信息

	CBCGPProp *pProp =NULL;

	long lNumFields = 0;
	long lRecLength = 0;

	long lFieldtype =0;

	lNumFields =pFeatureClass->FieldCount();

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

				//加入到属性表中
				pProp =new CBCGPProp(csName,_variant_t(csValue));

				m_PropList.AddProperty(pProp,FALSE);

			}
			break;
		case Geodatabase::FTYPE_DATE:    //日期型
			{

			}
			break;
		case Geodatabase::FTYPE_DOUBLE:
		case Geodatabase::FTYPE_FLOAT:    //浮点型
			{
				dValue =pFeature->GetValue(l+1).GetAsDouble();

				//加入到属性表中
				pProp =new CBCGPProp(csName,_variant_t(dValue));

				m_PropList.AddProperty(pProp,FALSE);
			}
			break;
		case Geodatabase::FTYPE_BOOL:    //逻辑型
			{

			}
			break;
		case Geodatabase::FTYPE_LONG:    //整型
			{
				lValue =pFeature->GetValue(l+1).m_Var.iVal;

				//加入到属性表中
				pProp =new CBCGPProp(csName,_variant_t(lValue));

				m_PropList.AddProperty(pProp,FALSE);
			}
			break;

		default:
			continue;
			break;
		}



	}
	m_PropList.Invalidate();



	m_hpreTreeItem=hCurTreeItem;


	*pResult = 0;
}


void CDlgFeatureAttriEdit::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
    UpdateData();

	//将属性写入文件
    SavePreAttribute();
    
	CDialog::OnOK();
}

void CDlgFeatureAttriEdit::OnTvnSelchangingTreeSelfeatures(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码


	*pResult = 0;
}

void CDlgFeatureAttriEdit::OnNMClickTreeSelfeatures(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	*pResult = 0;
}



using namespace Geodatabase;
//设置选择的要素
void CDlgFeatureAttriEdit::SetFeatures(vector<Carto::ILayer*> &allLayers)
{
	 m_allLayers =allLayers;
}

//刷新属性表和要素选择树形控件
void CDlgFeatureAttriEdit::Refresh()
{
	m_SelFeatureTree.DeleteAllItems();
	//清空属性表
	m_PropList.RemoveAll();
	HTREEITEM hRoot = m_SelFeatureTree.InsertItem("要素选择集");
   
	Geodatabase::ISelctionSet *pSelection=NULL;
	Carto::CFeatureLayer *pLayer =NULL;
	long fid = 0;
	BOOL bIsSelected = FALSE;
	CString csFeatureNo = _T("");
	for (long l = 0; l < m_allLayers.size(); l++)
	{

		pLayer =dynamic_cast<Carto::CFeatureLayer*>(m_allLayers[l]);
		if(!pLayer)
		{
			continue;
		}
		pSelection = pLayer->GetSelection().get();

		if (pSelection && pSelection->Count() > 0)
		{
			HTREEITEM hLayer = m_SelFeatureTree.InsertItem(pLayer->GetName().c_str(), hRoot, TVI_LAST);
			
			bIsSelected = FALSE;
			csFeatureNo = _T("");
			pSelection->ResetIndex();
			while(!pSelection->IsEOF())
			{
                 fid =pSelection->NextID();

				 csFeatureNo.Format("%ld", fid);
				 HTREEITEM hFeature = m_SelFeatureTree.InsertItem(csFeatureNo, hLayer, TVI_LAST);
				 m_SelFeatureTree.SetItemData(hFeature, (DWORD)pLayer);

			}
			
		}
	}

	//选中第一个要素
	HTREEITEM hLayer = m_SelFeatureTree.GetChildItem(hRoot);
	if (hLayer)
	{
		HTREEITEM hFeature = m_SelFeatureTree.GetChildItem(hLayer);
		if (hFeature)
			m_SelFeatureTree.SelectItem(hFeature);
	}
}

void CDlgFeatureAttriEdit::SavePreAttribute()
{
	if(m_hpreTreeItem==NULL)
	{
		return;
	}

	Carto::CFeatureLayer *pLayer = (Carto::CFeatureLayer*)m_SelFeatureTree.GetItemData(m_hpreTreeItem);
	if (!pLayer)
		return;
	if(!pLayer->GetDataObject())
		return;

	//得到属性的数目
	int lnum =m_PropList.GetPropertyCount();
	if(lnum<=0)
	{
		return;
	}

	long lRecNo = atol((LPCTSTR)m_SelFeatureTree.GetItemText(m_hpreTreeItem));
    _variant_t value;

	IFeatureClass* pFeatureClass =dynamic_cast<IFeatureClass*>(pLayer->GetDataObject().get());
	IWorkspace *pWorkspace =pFeatureClass->GetWorkspace();

	CFeaturePtr pFeature =pFeatureClass->GetFeature(lRecNo);

	if(!pFeature)
	{
		return;
	}

	long lfieldindex,lFieldtype=0;
	CBCGPProp *pProp =NULL;
	CString csName;
	pWorkspace->StartEditOperation();
	//更新要素的属性
	for(int i=0;i<lnum;i++)
	{
		pProp =m_PropList.GetProperty(i);
		if(pProp==NULL)
		{
			continue;
		}

		//得到属性名
		csName =pProp->GetName();
		//得到属性值
		value =pProp->GetValue();

		//得到字段序号
		lfieldindex = pFeatureClass->FindField(csName);

		lFieldtype =pFeatureClass->GetField(lfieldindex)->GetType();


		switch(lFieldtype)
		{

		case Geodatabase::FTYPE_STRING:    //字符型
			{
				pFeature->GetValue(lfieldindex).SetString((const char*)((_bstr_t)(value)));
			}
			break;
		case Geodatabase::FTYPE_DATE:    //日期型
			{

			}
			break;
		case Geodatabase::FTYPE_DOUBLE:
		case Geodatabase::FTYPE_FLOAT:    //浮点型
			{
				pFeature->GetValue(lfieldindex).SetDouble(double(value));
				
			}
			break;
		case Geodatabase::FTYPE_BOOL:    //逻辑型
			{

			}
			break;
		case Geodatabase::FTYPE_SHORT:    //整型
		case Geodatabase::FTYPE_LONG:    //整型
			{
				pFeature->GetValue(lfieldindex).SetInt((int)(value));
			
			}
			break;

		default:
			continue;
			break;
		}

	}
    
	pFeature->Update();
	pWorkspace->StopEditOperation();


	
}

LRESULT CDlgFeatureAttriEdit::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	UpdateData();

	//将属性写入文件
	SavePreAttribute();
	return 1;
}

