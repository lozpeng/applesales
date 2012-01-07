// DistillStep1.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "DistillStep1.h"
#include "TreePropSheetEx.h"
#include "DistillStep2.h"


// CDistillStep1 对话框

IMPLEMENT_DYNAMIC(CDistillStep1, CResizablePage)

CDistillStep1::CDistillStep1(CWnd* pParent /*=NULL*/)
	: CResizablePage(CDistillStep1::IDD)
{
	//m_psp.dwFlags &= (~PSP_HASHELP);
	m_psp.dwFlags |= PSP_USEHICON;
	HICON hIconTab = AfxGetApp()->LoadIcon(IDI_STEP1);
	m_psp.hIcon = hIconTab;
	m_pMapControl = NULL;
	m_mapIndexLyrs.clear();
}

CDistillStep1::~CDistillStep1()
{
}

void CDistillStep1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_RS_LYR, m_ctlComboLyr);
}


BEGIN_MESSAGE_MAP(CDistillStep1, CResizablePage)
	ON_BN_CLICKED(IDC_BUTTON_POLYGON, &CDistillStep1::OnBnClickedButtonPolygon)
END_MESSAGE_MAP()


// CDistillStep1 消息处理程序

void CDistillStep1::OnBnClickedButtonPolygon()
{
	// TODO: 在此添加控件通知处理程序代码
	Framework::ITool* pTool = NULL;
	m_pMapControl->SetCurTool("DiTillTool");
	pTool=Framework::ITool::FindTool("DiTillTool");
	//设置目标图层和阈值
	if(pTool)
	{
		pTool->Initialize(dynamic_cast<Framework::IUIObject*>(m_pMapControl));
	}
}

BOOL CDistillStep1::OnInitDialog()
{
	__super::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (NULL != m_pMapControl)
	{
		Carto::CMapPtr pMap = m_pMapControl->GetMap();
		Carto::ILayerPtr pActiveLyr = pMap->GetActiveLayer();
		Carto::CLayerArray lyrArray = pMap->GetLayers();
		Carto::ILayerPtr pLyr = NULL;
		int iIndex = 0;
		int iSelIndex = -1;
		for (int i=0; i<lyrArray.GetSize(); i++)
		{
			pLyr = lyrArray.GetAt(i);
			if (pLyr->GetLayerType() == Carto::RasterLayer)
			{
				m_mapIndexLyrs[iIndex++] = pLyr;
				m_ctlComboLyr.AddString(pLyr->GetName().c_str());
				if (pActiveLyr == pLyr)
				{
					iSelIndex = iIndex - 1;
				}
			}
		}
		if (m_ctlComboLyr.GetCount() > 0)
		{
			if (iSelIndex > -1)
			{
				m_ctlComboLyr.SetCurSel(iSelIndex);
			}
			else
			{
				m_ctlComboLyr.SetCurSel(0);
			}
		}
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
int CDistillStep1::DoWork()
{
	int iSelIndex = m_ctlComboLyr.GetCurSel();
	if (-1 != iSelIndex)
	{
		TreePropSheet::CTreePropSheetEx* pParentSheet = (TreePropSheet::CTreePropSheetEx*)GetParent();
		int iIndex = pParentSheet->GetActiveIndex();
		if ( iIndex < pParentSheet->GetPageCount() - 1)
		{
			CDistillStep2* pDistillDlg2 = (CDistillStep2*)pParentSheet->GetPage(iIndex + 1);
			pDistillDlg2->SetTargetLyr(m_mapIndexLyrs[iSelIndex]);
		}	
	}
	return 0;
}