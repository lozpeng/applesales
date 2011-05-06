// DlgFeatureInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Editor.h"
#include "DlgFeatureInfo.h"

#include "IFeatureClass.h"
// CDlgFeatureInfo �Ի���

IMPLEMENT_DYNAMIC(CDlgFeatureInfo, CDialog)

CDlgFeatureInfo::CDlgFeatureInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFeatureInfo::IDD, pParent)
{
   m_pMap =NULL;
   m_pMapCtrl = NULL;
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
	//ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_FEATURES, &CDlgFeatureInfo::OnTvnSelchangedTreeFeatures)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_TREE_FEATURES, &CDlgFeatureInfo::OnNMClickTreeFeatures)
END_MESSAGE_MAP()


// CDlgFeatureInfo ��Ϣ�������

void CDlgFeatureInfo::OnTvnSelchangedTreeFeatures(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
}

BOOL CDlgFeatureInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString csBuf;

	csBuf = "�ֶ���";
	m_FeatureInfo.InsertColumn(0, csBuf, LVCFMT_LEFT, 80);
	csBuf = "ֵ";
	m_FeatureInfo.InsertColumn(1, csBuf, LVCFMT_LEFT, 250);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgFeatureInfo::SetMap(Carto::CMap *pMap)
{
	m_pMap =pMap;
}

void CDlgFeatureInfo::Refresh()
{
	m_Features.DeleteAllItems();
	m_FeatureInfo.DeleteAllItems();
	HTREEITEM hRoot = m_Features.InsertItem("ѡ��Ҫ��");

	if(!m_pMap)
	{
		return;
	}
    m_layers.clear();

	//���ѡ��Ҫ�ص�ͼ��
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
				//û��ѡ��
				continue;
			}
			m_layers.push_back(pFeatureLayer);


			//��ͼ���Ҫ�ؼ��뵽����
			HTREEITEM hLayer = m_Features.InsertItem(pFeatureLayer->GetName().c_str(), hRoot, TVI_LAST);

			pSel->ResetIndex();
			while(!pSel->IsEOF())
			{
				csFeatureNo.Format("%d", pSel->NextID());
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_layers.clear();
	CDialog::OnClose();
}

void CDlgFeatureInfo::OnNMClickTreeFeatures(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	HTREEITEM hCurTreeItem ;//= pNMTreeView->itemNew.hItem;

	//if (m_Features.GetChildItem(hCurTreeItem))
	//{
	//	*pResult = 0;
	//	return;
	//}
	DWORD   dwpos = GetMessagePos();   
	TVHITTESTINFO ht = {0};   

	ht.pt.x = GET_X_LPARAM(dwpos);
	ht.pt.y = GET_Y_LPARAM(dwpos);
	::MapWindowPoints(HWND_DESKTOP,pNMHDR->hwndFrom,&ht.pt,1); //����Ļ����ת���ɿؼ�����

	TreeView_HitTest(pNMHDR->hwndFrom,&ht);   //ȷ�����������һ��

	hCurTreeItem = ht.hItem;

	//�ж��ǲ��Ǹ��ڵ�
	if(m_Features.GetRootItem()==hCurTreeItem)
	{
		*pResult = 0;
		return;
	}

	m_FeatureInfo.DeleteAllItems();

	int iLayer = m_Features.GetItemData(hCurTreeItem);

	long lRecNo = atol((LPCTSTR)m_Features.GetItemText(hCurTreeItem));

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

	//��˸
	GEOMETRY::geom::Geometry *pGeometry = pFeature->GetShape();
	if (m_pMapCtrl)
	{
		m_pMapCtrl->FlashShape(pGeometry,1,300,NULL);
	}

	long lNumFields =pFeatureClass->FieldCount();


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

				csValue.TrimLeft();
				m_FeatureInfo.InsertItem(l, csName);
				m_FeatureInfo.SetItem(l, 1, LVIF_TEXT, csValue, 0, 0, 0, NULL);

			}
			break;
		case Geodatabase::FTYPE_DATE:    //������
			{
				m_FeatureInfo.InsertItem(l, csName);
				m_FeatureInfo.SetItem(l, 1, LVIF_TEXT, "", 0, 0, 0, NULL);
			}
			break;
		case Geodatabase::FTYPE_DOUBLE:
		case Geodatabase::FTYPE_FLOAT:    //������
			{
				dValue =pFeature->GetValue(l+1).GetAsDouble();

				csValue.Format("%.8f",dValue);

				m_FeatureInfo.InsertItem(l, csName);
				m_FeatureInfo.SetItem(l, 1, LVIF_TEXT, csValue, 0, 0, 0, NULL);

			}
			break;
		case Geodatabase::FTYPE_BOOL:    //�߼���
			{

			}
			break;
		case Geodatabase::FTYPE_LONG:    //����
			{
				lValue =pFeature->GetValue(l+1).m_Var.iVal;

				csValue.Format("%d",lValue);

				m_FeatureInfo.InsertItem(l, csName);
				m_FeatureInfo.SetItem(l, 1, LVIF_TEXT, csValue, 0, 0, 0, NULL);
			}
			break;

		default:
			m_FeatureInfo.InsertItem(l, csName);
			m_FeatureInfo.SetItem(l, 1, LVIF_TEXT, "", 0, 0, 0, NULL);
			break;
		}

	}
	*pResult = 0;
}
