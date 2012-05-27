// DialogCreatRoi.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UAVSoft.h"
#include "DialogCreateRoi.h"


// CDialogCreateRoi �Ի���

IMPLEMENT_DYNAMIC(CDialogCreateRoi, CDialog)

CDialogCreateRoi::CDialogCreateRoi(Framework::IMapCtrl* pMapCtrl,CWnd* pParent /*=NULL*/)
	: CDialog(CDialogCreateRoi::IDD, pParent)
{
	m_pMapCtrl = pMapCtrl;
	m_bNewROI = false;
}

CDialogCreateRoi::~CDialogCreateRoi()
{
	std::list<ROI_INFO*>::iterator it;
	for (it=m_lstROI.begin(); it!=m_lstROI.end(); it++)
	{
		ROI_INFO* pRoiInfo = (*it);
		delete pRoiInfo;
		pRoiInfo = NULL;
	}
	m_lstROI.clear();
}

void CDialogCreateRoi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ROI_LIST, m_list);
}


BEGIN_MESSAGE_MAP(CDialogCreateRoi, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADD, &CDialogCreateRoi::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, &CDialogCreateRoi::OnBnClickedBtnDel)
END_MESSAGE_MAP()


// CDialogCreateRoi ��Ϣ�������
void CDialogCreateRoi::RemoveROIElement(Element::IElementPtr pElement)
{

}
void CDialogCreateRoi::AddROIElement(CRgn& rgn, Element::IElementPtr pElement)
{
	ROI_INFO* roiInfo = new ROI_INFO();
	Display::ISymbolPtr pSymbol = pElement->GetSymbol();
	srand(time(NULL));
	pSymbol->SetColor(RGB(rand() % 256,rand() % 256,rand() % 256));
	m_pMapCtrl->UpdateControl(drawElement);
	CString str;
	str.Format("%d",pSymbol->GetColor());
	int n = m_list.GetItemCount();
	m_list.InsertItem(n,str);
	str.Format("���%d",n);
	roiInfo->lColor = pSymbol->GetColor();
	roiInfo->strClassNmae = str;
	rgn.CopyRgn(&roiInfo->rgn);
	m_list.SetItemText(n,1,str);
	m_list.SetItemText(n,2,"1");
	m_lstROI.push_back(roiInfo);
	m_bNewROI = false;
}

void CDialogCreateRoi::OnBnClickedBtnAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_bNewROI)
	{
		m_bNewROI = true;
		Framework::ITool* pTool = NULL;
		m_pMapCtrl->SetCurTool("DrawPolygonElementTool");
		pTool=Framework::ITool::FindTool("DrawPolygonElementTool");
		if(pTool)
		{
			pTool->Initialize(dynamic_cast<Framework::IUIObject*>(m_pMapCtrl));
		}
	}
}

//Framework::ITool* pTool = NULL;
//	m_MapCtrl.SetCurTool("DrawPolygonElementTool");
//
//	pTool=Framework::ITool::FindTool("DrawPolygonElementTool");
//	if(pTool)
//	{
//		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(&m_MapCtrl));
//	}
BOOL CDialogCreateRoi::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	m_list.GetClientRect(rect);
	long lwidth =rect.Width();
	m_list.InsertColumn( 0, "��ɫ", LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM, lwidth*0.2, 0 );
	m_list.InsertColumn( 1, "�����", LVCFMT_LEFT, lwidth*0.4);
	m_list.InsertColumn( 2, "����θ���", LVCFMT_LEFT, lwidth*0.4);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDialogCreateRoi::OnBnClickedBtnDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
