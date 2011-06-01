// DlgFeatureAttriEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgFeatureAttriEdit.h"
#include "FeatureLayer.h"
#include "IWorkspace.h"

// CDlgFeatureAttriEdit �Ի���

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


// CDlgFeatureAttriEdit ��Ϣ�������

BOOL CDlgFeatureAttriEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��


	//���������б�
    CRect rectPropList;
	m_propListLoc.GetClientRect (&rectPropList);
	m_propListLoc.MapWindowPoints (this, &rectPropList);

	m_PropList.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectPropList, this, (UINT)-1);
	
	m_PropList.EnableHeaderCtrl (TRUE,"������","ֵ");

	m_PropList.SetVSDotNetLook ();

	m_PropList.SetShowDragContext ();

	Refresh();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}



//���е�ǰѡ��Ҫ�ط����ı�
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
			//��֮ǰ�޸ĵ����Ա���
			SavePreAttribute();


		}


	}

   	//������Ա�
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

	//��ȡҪ��������Ϣ

	CBCGPProp *pProp =NULL;

	long lNumFields = 0;
	long lRecLength = 0;

	long lFieldtype =0;

	lNumFields =pFeatureClass->FieldCount();

	for ( l = 0; l < lNumFields; l++)
	{

		//�õ��ֶ���
		csName =pFeatureClass->GetField(l+1)->GetName().c_str();
        //�õ��ֶ�����
		lFieldtype =pFeatureClass->GetField(l+1)->GetType();
			
		switch(lFieldtype)
		{

		case Geodatabase::FTYPE_STRING:    //�ַ���
			{
				csValue =pFeature->GetValue(l+1).GetasString().c_str();

				//���뵽���Ա���
				pProp =new CBCGPProp(csName,_variant_t(csValue));

				m_PropList.AddProperty(pProp,FALSE);

			}
			break;
		case Geodatabase::FTYPE_DATE:    //������
			{

			}
			break;
		case Geodatabase::FTYPE_DOUBLE:
		case Geodatabase::FTYPE_FLOAT:    //������
			{
				dValue =pFeature->GetValue(l+1).GetAsDouble();

				//���뵽���Ա���
				pProp =new CBCGPProp(csName,_variant_t(dValue));

				m_PropList.AddProperty(pProp,FALSE);
			}
			break;
		case Geodatabase::FTYPE_BOOL:    //�߼���
			{

			}
			break;
		case Geodatabase::FTYPE_LONG:    //����
			{
				lValue =pFeature->GetValue(l+1).m_Var.iVal;

				//���뵽���Ա���
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
	// TODO: �ڴ����ר�ô����/����û���
    UpdateData();

	//������д���ļ�
    SavePreAttribute();
    
	CDialog::OnOK();
}

void CDlgFeatureAttriEdit::OnTvnSelchangingTreeSelfeatures(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	*pResult = 0;
}

void CDlgFeatureAttriEdit::OnNMClickTreeSelfeatures(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	*pResult = 0;
}



using namespace Geodatabase;
//����ѡ���Ҫ��
void CDlgFeatureAttriEdit::SetFeatures(vector<Carto::ILayer*> &allLayers)
{
	 m_allLayers =allLayers;
}

//ˢ�����Ա��Ҫ��ѡ�����οؼ�
void CDlgFeatureAttriEdit::Refresh()
{
	m_SelFeatureTree.DeleteAllItems();
	//������Ա�
	m_PropList.RemoveAll();
	HTREEITEM hRoot = m_SelFeatureTree.InsertItem("Ҫ��ѡ��");
   
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

	//ѡ�е�һ��Ҫ��
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

	//�õ����Ե���Ŀ
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
	//����Ҫ�ص�����
	for(int i=0;i<lnum;i++)
	{
		pProp =m_PropList.GetProperty(i);
		if(pProp==NULL)
		{
			continue;
		}

		//�õ�������
		csName =pProp->GetName();
		//�õ�����ֵ
		value =pProp->GetValue();

		//�õ��ֶ����
		lfieldindex = pFeatureClass->FindField(csName);

		lFieldtype =pFeatureClass->GetField(lfieldindex)->GetType();


		switch(lFieldtype)
		{

		case Geodatabase::FTYPE_STRING:    //�ַ���
			{
				pFeature->GetValue(lfieldindex).SetString((const char*)((_bstr_t)(value)));
			}
			break;
		case Geodatabase::FTYPE_DATE:    //������
			{

			}
			break;
		case Geodatabase::FTYPE_DOUBLE:
		case Geodatabase::FTYPE_FLOAT:    //������
			{
				pFeature->GetValue(lfieldindex).SetDouble(double(value));
				
			}
			break;
		case Geodatabase::FTYPE_BOOL:    //�߼���
			{

			}
			break;
		case Geodatabase::FTYPE_SHORT:    //����
		case Geodatabase::FTYPE_LONG:    //����
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

	//������д���ļ�
	SavePreAttribute();
	return 1;
}

