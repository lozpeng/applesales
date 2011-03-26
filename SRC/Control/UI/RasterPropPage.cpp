// RasterPropPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Control.h"
#include "RasterPropPage.h"
#include "IRasterDataset.h"

// CRasterPropPage �Ի���

IMPLEMENT_DYNAMIC(CRasterPropPage, CPropertyPage)

CRasterPropPage::CRasterPropPage()
	: CPropertyPage(CRasterPropPage::IDD)
{
    m_player =NULL;
}

CRasterPropPage::~CRasterPropPage()
{
}

void CRasterPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RASTERLOC, m_wndPropListLocation);
}


BEGIN_MESSAGE_MAP(CRasterPropPage, CPropertyPage)
END_MESSAGE_MAP()


// CRasterPropPage ��Ϣ�������

BOOL CRasterPropPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	if(!m_player)
	{
		return FALSE;
	}
	Geodatabase::IRasterDatasetPtr pRaster =m_player->GetDataObject();

	CRect rectPropList;
	m_wndPropListLocation.GetClientRect (&rectPropList);
	m_wndPropListLocation.MapWindowPoints (this, &rectPropList);

	m_wndPropList.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectPropList, this, (UINT)-1);

	m_wndPropList.EnableHeaderCtrl (TRUE,"����","ֵ");
	//m_wndPropList.EnableDesciptionArea ();
	m_wndPropList.SetVSDotNetLook (TRUE);
	//m_wndPropList.MarkModifiedProperties (m_bMarkChanged);

	//m_wndPropList.SetAlphabeticMode (!m_bPropListCategorized);
	//m_wndPropList.SetShowDragContext (m_bShowDragContext);

	CBCGPProp* pGroup1 = new CBCGPProp (_T("��������"));


	CBCGPProp* pProp;

	// ͼ���С
	long lwidth,lheight;
	pRaster->GetSize(&lwidth,&lheight);

	CBCGPProp* pSize = new CBCGPProp (_T("ͼ���С"), 0, TRUE);

	pProp = new CBCGPProp (_T("��"), (_variant_t) lwidth);
	pProp->AllowEdit (FALSE);
	pSize->AddSubItem (pProp);
	pProp = new CBCGPProp (_T("��"), (_variant_t) lheight);
	pProp->AllowEdit (FALSE);
	pSize->AddSubItem (pProp);

	pGroup1->AddSubItem(pSize);

	//������
	long lband =pRaster->GetBandCount();
	
	pProp =new CBCGPProp (_T("������"), (_variant_t) lband);
	pProp->AllowEdit (FALSE);
	pGroup1->AddSubItem(pProp);

    //���ش�С
    double dx,dy;
	pRaster->GetCellSize(&dx,&dy);
	CBCGPProp* pCellSize = new CBCGPProp (_T("���ش�С"), 0, TRUE);

	pProp = new CBCGPProp (_T("X"), (_variant_t) dx);
	pProp->AllowEdit (FALSE);
	pCellSize->AddSubItem (pProp);
	pProp = new CBCGPProp (_T("Y"), (_variant_t) dy);
	pProp->AllowEdit (FALSE);
	pCellSize->AddSubItem (pProp);

	pGroup1->AddSubItem(pCellSize);

	//��������
	Geodatabase::BANDDATATYPE datatype= pRaster->GetBandDataType(1);
	CString strType;
	switch(datatype)
	{
	case Geodatabase::BDT_BYTE:
		{
			strType ="�޷���8λ";
			break;
		}
	case Geodatabase::BDT_SHORT:
		{
			strType ="16λ����";
			break;
		}
	case Geodatabase::BDT_USHORT:
		{
			strType ="�޷���16λ����";
			break;
		}
	case Geodatabase::BDT_LONG:
		{
			strType ="32λ����";
			break;
		}
	case Geodatabase::BDT_FLOAT:
		{
			strType ="32λ������";
			break;
		}
	case Geodatabase::BDT_DOUBLE:
		{
			strType ="64λ������";
			break;
		}
	default:
		strType ="δ֪";
		break;
	}
	pProp =new CBCGPProp (_T("��������"), (_variant_t) strType);
	pProp->AllowEdit (FALSE);
	pGroup1->AddSubItem(pProp);

	m_wndPropList.AddProperty (pGroup1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CRasterPropPage::SetLayer(Carto::ILayer* player)
{
	m_player =player;
}