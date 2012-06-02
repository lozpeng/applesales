// DialogCreatRoi.cpp : 实现文件
//

#include "stdafx.h"
#include "UAVSoft.h"
#include "DialogCreateRoi.h"


// CDialogCreateRoi 对话框

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


// CDialogCreateRoi 消息处理程序
void CDialogCreateRoi::RemoveROIElement(Element::IElementPtr pElement)
{

}
HBITMAP CDialogCreateRoi::CoverBitmap( Display::ISymbolPtr pSymbol )
{
	Display::IDisplay SimpleDisplay;
	CDC * dc=GetDC();
	CDC MemDC;//创建相容的bitmap和dc
	HBITMAP hbitmap = CreateCompatibleBitmap( dc->GetSafeHdc(), m_cx, m_cy );
	HBITMAP hBitmapTemp;
	MemDC.CreateCompatibleDC( dc );
	hBitmapTemp=( HBITMAP )SelectObject( MemDC, hbitmap );

	RECT rc1;
	rc1.top = rc1.left = 0;
	rc1.right = m_cx;
	rc1.bottom = m_cy;
	CBrush brush( RGB(255,254,253) );
	MemDC.FillRect( &rc1, &brush );

	SimpleDisplay.SetBgColor( RGB(255,255,255) );
	SimpleDisplay.SetDC( (long)MemDC.GetSafeHdc(), rc1.right, rc1.bottom );
	DIS_RECT rc;
	rc.left = rc.top = 0;
	rc.right = m_cx;
	rc.bottom= m_cy;
	HRGN hr = 0;
	SimpleDisplay.DrawLegend( pSymbol.get(), &rc, 0 );
	hbitmap=(HBITMAP)SelectObject(MemDC.m_hDC,hBitmapTemp);
	MemDC.DeleteDC();
	return hbitmap;
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

	CBitmap bitmap;
	bitmap.Attach(CoverBitmap(pSymbol));
	int Index = m_ImageList.Add(&bitmap, RGB(255, 255, 255));
	bitmap.DeleteObject();

	LV_ITEM lvi;

	lvi.mask = /*LVIF_TEXT |*/ LVIF_IMAGE /*| LVIF_STATE*/;
	lvi.iItem = n;
	lvi.iSubItem = 0;
	lvi.iImage = Index;

	//m_list.InsertItem(n, "", Index);
	m_list.InsertItem( &lvi );

	str.Format("类别%d",n);
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
	// TODO: 在此添加控件通知处理程序代码
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

	// TODO:  在此添加额外的初始化

	CRect rect;
	m_list.GetClientRect(rect);
	long lwidth =rect.Width();
	m_list.SetExtendedStyle(m_list.GetExStyle() | LVS_EX_GRIDLINES);
	m_list.InsertColumn( 0, "颜色", LVCFMT_CENTER | LVCF_IMAGE/* | LVCF_SUBITEM*/, lwidth*0.2, 0 );
	m_list.InsertColumn( 1, "类别名", LVCFMT_LEFT, lwidth*0.4);
	m_list.InsertColumn( 2, "多边形个数", LVCFMT_LEFT, lwidth*0.4);

	m_cx = lwidth*0.2;
	m_cy = 25;
	m_ImageList.Create(m_cx, m_cy, ILC_COLOR24 | ILC_MASK, 4,  20);

	m_list.SetImageList(&m_ImageList, TVSIL_STATE);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDialogCreateRoi::OnBnClickedBtnDel()
{
	// TODO: 在此添加控件通知处理程序代码
}
