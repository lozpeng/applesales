// RasterPropShowPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RasterPropShowPage.h"
#include "IRasterDataset.h"


// CRasterPropShowPage �Ի���

IMPLEMENT_DYNAMIC(CRasterPropShowPage, CPropertyPage)

CRasterPropShowPage::CRasterPropShowPage()
	: CPropertyPage(CRasterPropShowPage::IDD)
{
	m_psp.dwFlags &= ~PSP_HASHELP;

	m_pLayer = NULL;

	m_pRGBRender = NULL;

	m_csRows = _T("");
	m_csCols = _T("");
	m_csChannelCount = _T("");

	m_fMax = 0.0f;
	m_fMean = 0.0f;
	m_fMin = 0.0f;
	m_fVar = 0.0f;
	m_Entroy = 0.0f;

	//
	m_buseTrans = TRUE;
	m_red = 0;
	m_green = 0;
	m_blue = 0;

}

CRasterPropShowPage::~CRasterPropShowPage()
{
}

void CRasterPropShowPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_BANDS, m_comboBand);
	DDX_Text(pDX, IDC_ROWS, m_csRows);
	DDX_Text(pDX, IDC_COM_SCOL, m_csCols);
	DDX_Text(pDX, IDC_CHANNELCOUNT, m_csChannelCount);
	DDX_Text(pDX, IDC_EDIT_MAX, m_fMax);
	DDX_Text(pDX, IDC_EDIT_MEAN, m_fMean);
	DDX_Text(pDX, IDC_EDIT_MIN, m_fMin);
	DDX_Text(pDX, IDC_EDIT_VAR, m_fVar);
	DDX_Text(pDX, IDC_EDIT_Entroy, m_Entroy);
	DDX_Text(pDX,IDC_EDIT_INVALIDVAL,m_fInvalidValue);
	DDX_Check(pDX, IDC_CHECK_BACKCOLORTRANS, m_buseTrans);
	DDX_Text(pDX, IDC_EDIT_R, m_red);
	DDX_Text(pDX, IDC_EDIT_G, m_green);
	DDX_Text(pDX, IDC_EDIT_B, m_blue);
	DDX_Text(pDX,IDC_X_CELL,m_csCellSizeX);
	DDX_Text(pDX,IDC_Y_CELL,m_csCellSizeY);
}


BEGIN_MESSAGE_MAP(CRasterPropShowPage, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO_BANDS, &CRasterPropShowPage::OnCbnSelchangeComboBands)
	ON_BN_CLICKED(IDC_CHECK_SET, &CRasterPropShowPage::OnBnClickedCheckSet)
	ON_BN_CLICKED(IDC_CHECK_BACKCOLORTRANS, &CRasterPropShowPage::OnBnClickedCheckBackcolortrans)
	ON_BN_CLICKED(IDC_BTN_SELCOLOR, &CRasterPropShowPage::OnBnClickedBtnSelcolor)
END_MESSAGE_MAP()


// CRasterPropShowPage ��Ϣ�������
BOOL CRasterPropShowPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	if (!m_pLayer || !m_pRGBRender)
	{
		return FALSE;
	}

	//����ɫ
	//��ȡͼ���͸��ɫ��״̬
	/*m_buseTrans = m_pRGBRender->GetTransStatue();

	if (m_buseTrans)
	{
		COLORREF curcolor = m_pRGBRender->GetTransColor();

		m_red =GetRValue(curcolor);
		m_green =GetGValue(curcolor);
		m_blue =GetBValue(curcolor);
	}*/



	InitLayerInfo();

	UpdateChannelStaticInfo(1);

	return TRUE;
}

void CRasterPropShowPage::SetLayer(Carto::CRasterLayerPtr layer)
{
	m_pLayer = layer;

	Carto::IRasterRenderPtr pRender = m_pLayer->GetRender();
	if(!pRender)
		return;

	m_pRGBRender = dynamic_cast<Carto::CRasterRGBRender*>(pRender.get());
	if(!m_pRGBRender)
		return;
}

void CRasterPropShowPage::InitLayerInfo()
{

	Geodatabase::IGeodataObjectPtr pDataObject = m_pLayer->GetDataObject();

	Geodatabase::IRasterDataset *pRasterObj = dynamic_cast<Geodatabase::IRasterDataset*>(pDataObject.get());

	if(!pRasterObj)
		return;

	long lWidth,lHeight;
	pRasterObj->GetSize(&lWidth,&lHeight);
	double dblCellSizeX, dblCellSizeY;
	pRasterObj->GetCellSize(&dblCellSizeX,&dblCellSizeY);
	m_csCellSizeX.Format("%.6f",dblCellSizeX);
	m_csCellSizeY.Format("%.6f",dblCellSizeY);

	long lBandCount;
	lBandCount = pRasterObj->GetBandCount();

	m_csRows.Format("%ld", lHeight);
	m_csCols.Format("%ld", lWidth);
	m_csChannelCount.Format("%ld", lBandCount);

	CButton* pCheck =(CButton*)GetDlgItem(IDC_CHECK_SET);

	//if(!pRasterObj->GetInvalidVal(&m_fInvalidValue))
	//{		
	//	pCheck->SetCheck(BST_UNCHECKED);
	//	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_INVALIDVAL);
	//	pEdit->EnableWindow(false);
	//	m_fInvalidValue = -9999.0;
	//	m_bUseInvaidVal = false;
	//}	
	//else
	//{
	//	pCheck->SetCheck(BST_CHECKED);
	//	m_bUseInvaidVal = true;
	//	m_fOrigInvaidVal = m_fInvalidValue;
	//}

	std::string strChannelDesc;

	std::string strText;

	//Geodatabase::BANDDATATYPE bandType;

	//for (long lChannelIndex = 1; lChannelIndex <= lBandCount; lChannelIndex ++)
	//{

	//	bandType = pRasterObj->GetBandDataType(lChannelIndex);

	//	strChannelDesc =pRasterObj->GetChannelDesc(lChannelIndex);

	//	strText = boost::str(boost::format("%ld - [") % lChannelIndex);

	//	switch(bandType){
	//		case Geodatabase::BDT_BYTE:  //�ֽ�
	//		strText += "8u]";
	//		break;
	//		case Geodatabase::BDT_USHORT:  //�޷���short
	//		strText += "16u]";
	//		break; //short
	//		case Geodatabase::BDT_SHORT:
	//		strText += "16s]";
	//		break;
	//		case Geodatabase::BDT_ULONG:  //�޷���long
	//		strText += "32u]";
	//		break;
	//		case Geodatabase::BDT_LONG:  //long
	//		strText += "32s]";
	//		break;
	//		case Geodatabase::BDT_FLOAT: //float
	//		strText += "32f]";
	//		break;
	//		case Geodatabase::BDT_DOUBLE: //double
	//		strText += "64d]";
	//		break;
	//	}


	//	if (0 == strChannelDesc.length())
	//	{
	//		strText += ": δ֪��λ";
	//	}
	//	else
	//	{
	//		strText += ": ";
	//		//strText += strChannelDesc;
	//	}
	//	m_comboBand.AddString(strText.c_str());
	//}
	m_comboBand.SetCurSel(0);
}

void CRasterPropShowPage::UpdateInvalidValue()
{
	UpdateData(TRUE);

	Geodatabase::IGeodataObjectPtr pDataObject = m_pLayer->GetDataObject();


	Geodatabase::IRasterDataset *pRasterObj = dynamic_cast<Geodatabase::IRasterDataset*>(pDataObject.get());

	if(!pRasterObj)
		return;

	CButton* pCheck =(CButton*)GetDlgItem(IDC_CHECK_SET);		

	//if(BST_CHECKED == pCheck->GetCheck())//����������Чֵ��
	//{			
	//	if (m_bUseInvaidVal)//ԭ��������Чֵ
	//	{
	//		if (abs(m_fInvalidValue - m_fOrigInvaidVal) < 0.0001)//��Чֵ����û�иı�
	//		{
	//			m_pRGBRender->m_bInvalidSetChange = false;
	//		}
	//		else//��Чֵ���øı���
	//		{
	//			m_pRGBRender->m_bInvalidSetChange = true;
	//			pRasterObj->SetInvalidVal(m_fInvalidValue);
	//		}
	//	}
	//	else//ԭ��û��������Чֵ
	//	{
	//		m_pRGBRender->m_bInvalidSetChange = true;
	//		pRasterObj->SetInvalidVal(m_fInvalidValue);
	//	}

	//}
	//else//����û��������Чֵ��
	//{
	//	pRasterObj->CancelInvalidVal();
	//	if (m_bUseInvaidVal)//ԭ��������Чֵ
	//		m_pRGBRender->m_bInvalidSetChange = true;
	//	else
	//		m_pRGBRender->m_bInvalidSetChange = false;

	//}

}

void CRasterPropShowPage::OnCancel()
{
	CPropertyPage::OnCancel();
}

BOOL CRasterPropShowPage::OnApply()
{
	return CPropertyPage::OnApply();
}

void CRasterPropShowPage::OnOK()
{
	UpdateInvalidValue();

	/*if (m_buseTrans)
	{
		m_pRGBRender->SetTransColor(RGB(m_red,m_green,m_blue));
	}*/


	CPropertyPage::OnOK();
}

void CRasterPropShowPage::OnCbnSelchangeComboBands()
{
	UpdateChannelStaticInfo(m_comboBand.GetCurSel()+1);
}

void CRasterPropShowPage::OnBnClickedCheckSet()
{
	CButton* pCheck =(CButton*)GetDlgItem(IDC_CHECK_SET);

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_INVALIDVAL);

	if(BST_UNCHECKED == pCheck->GetCheck())
	{
		pEdit->EnableWindow(false);		                              
	}
	else
		pEdit->EnableWindow(true);

	UpdateChannelStaticInfo(m_comboBand.GetCurSel()+1);
}

void CRasterPropShowPage::UpdateChannelStaticInfo(long lChannelIndex)
{
	/*if(NULL != m_pLayer)
	{
		float pHist[256];

		Geodatabase::IDataObjectPtr pDataObject = m_pLayer->GetDataObject();

		Geodatabase::IRasterDataset *pRasterObj = dynamic_cast<Geodatabase::IRasterDataset*>(pDataObject.get());

		if(!pRasterObj)
			return;

		pRasterObj->GetChannelStatisInfo(lChannelIndex,pHist,&m_fMax,&m_fMin,&m_fMean,&m_fVar);
		pRasterObj->GetChannelEntroy(lChannelIndex,&m_Entroy);
		UpdateData(FALSE);
	}*/
}

void CRasterPropShowPage::OnBnClickedCheckBackcolortrans()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CRasterPropShowPage::OnBnClickedBtnSelcolor()
{
	UpdateData();
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		COLORREF curcolor = dlg.GetColor();

		m_red =GetRValue(curcolor);
		m_green =GetGValue(curcolor);
		m_blue =GetBValue(curcolor);

		UpdateData(FALSE);

	}
}
