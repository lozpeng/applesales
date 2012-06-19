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
	std::vector<ROI_INFO*>::iterator it;
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
	if (!m_bMulti)
	{
		ROI_INFO* ri = new ROI_INFO();
		m_lstROI.push_back(ri);
		ELE_INFO eleInfo;
		Display::ISymbolPtr pSymbol = pElement->GetSymbol();
		srand(time(NULL));
		m_lCurColor = RGB(rand() % 256,rand() % 256,rand() % 256);
		pSymbol->SetColor(m_lCurColor);
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
		int nCount = m_lstROI.size();
		ROI_INFO* roiInfo =m_lstROI[nCount-1];
		roiInfo->lColor = pSymbol->GetColor();
		roiInfo->strClassNmae = str;
		eleInfo.strClassNmae = str;
		eleInfo.elems.push_back(pElement);
		m_lstEle.push_back(eleInfo);
		CRgn* pRgn = new CRgn();
		rgn.CopyRgn(pRgn);
		roiInfo->rgns.push_back(pRgn);
		m_list.SetItemText(n,1,str);
		m_list.SetItemText(n,2,"1");
		m_nIndex = n;
		m_nCount = 1;
	}
	else
	{
		Display::ISymbolPtr pSymbol = pElement->GetSymbol();
		pSymbol->SetColor(m_lCurColor);
		m_pMapCtrl->UpdateControl(drawElement);
		int nCount = m_lstROI.size();
		ROI_INFO* roiInfo =m_lstROI[nCount-1];
		m_lstEle[nCount-1].elems.push_back(pElement);
		CRgn* pRgn = new CRgn();
		rgn.CopyRgn(pRgn);
		roiInfo->rgns.push_back(pRgn);
		m_nCount++;
		CString str;
		str.Format("%d",m_nCount);
		m_list.SetItemText(m_nIndex,2,str.GetBuffer());
	}
	m_bMulti = true;
	//m_bNewROI = false;
}

void CDialogCreateRoi::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	//if (!m_bNewROI)
	//{
		m_bNewROI = true;
		m_bMulti = false;
		m_nCount = 0;
		Framework::ITool* pTool = NULL;
		m_pMapCtrl->SetCurTool("DrawPolygonElementTool");
		pTool=Framework::ITool::FindTool("DrawPolygonElementTool");
		if(pTool)
		{
			pTool->Initialize(dynamic_cast<Framework::IUIObject*>(m_pMapCtrl));
		}
	//}
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
    m_list.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_list.InsertColumn( 0, "颜色", LVCFMT_CENTER | LVCF_IMAGE/* | LVCF_SUBITEM*/, lwidth*0.2, 0 );
	m_list.InsertColumn( 1, "类别名", LVCFMT_LEFT, lwidth*0.4);
	m_list.InsertColumn( 2, "多边形个数", LVCFMT_LEFT, lwidth*0.4);

	m_cx = lwidth*0.2 - 5;
	m_cy = 25;
	m_ImageList.Create(m_cx, m_cy, ILC_COLOR24 | ILC_MASK, 4,  20);

	m_list.SetImageList(&m_ImageList, LVSIL_SMALL);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDialogCreateRoi::OnBnClickedBtnDel()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int nItem = m_list.GetNextSelectedItem(pos);
	if (nItem < 0)
		return;
	CString strText = m_list.GetItemText(nItem,1);
	int nCount = m_lstROI.size();
	std::vector<ELE_INFO>::iterator eleIt;
	eleIt = m_lstEle.begin();
	std::vector<ROI_INFO*>::iterator roiIt;
	roiIt = m_lstROI.begin();
	for (int i=0; i<nCount; i++)
	{
		if (m_lstROI[i]->strClassNmae == strText)
		{
			m_list.DeleteItem(nItem);
			int nSize = m_lstEle[i].elems.size();
			for (int j=0; j<nSize; j++)
			{
				m_pMapCtrl->GetMap()->GetGraphicLayer()->RemoveElement(m_lstEle[i].elems[j]);
			}
			m_lstEle.erase(eleIt);
			m_lstROI.erase(roiIt);
			m_pMapCtrl->UpdateControl(drawElement);
			return;
		}
		eleIt++;
		roiIt++;
	}
}
