#include "StdAfx.h"
#include "ElementProperSheet.h"
#include "IMapCtrl.h"
//#include "GeoPageLayout.h"

IMPLEMENT_DYNAMIC(CElementProperSheet, CPropertySheet)


BEGIN_MESSAGE_MAP(CElementProperSheet, CPropertySheet)
	ON_BN_CLICKED(ID_APPLY_NOW , &CElementProperSheet::OnApply)
	//ON_BN_CLICKED(IDOK , &CElementProperSheet::OnOK)
END_MESSAGE_MAP()

CElementProperSheet::CElementProperSheet(CString name , CWnd *pWnd): CPropertySheet(name , pWnd)
{
	m_psh.dwFlags &= ~PSH_HASHELP;
	m_pElement = NULL;
}

CElementProperSheet::~CElementProperSheet(void)
{
}

void CElementProperSheet::SetElement(Element::IElementPtr pElement)
{
	m_pElement = pElement;
}

void CElementProperSheet::OnOK()
{
	//调用每个页面的应用函数
	if(m_pElement == NULL)
		return;

	int pagecount =GetPageCount();
	for(int i=0;i<pagecount;i++)
	{
		CPropertyPage* page =GetPage(i);
		page->OnOK();
	}
	//获取活动制图控件
	Framework::IMapCtrl* pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	pMapCtrl->UpdateControl(drawEdit|drawElement);

	CPropertySheet::OnClose();
}

void CElementProperSheet::OnApply()
{
	//调用每个页面的应用函数
	if(m_pElement == NULL)
		return;

	CPropertyPage* pPage = GetActivePage();
	pPage->OnApply();

	//获取活动制图控件
	Framework::IMapCtrl* pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	pMapCtrl->UpdateControl(drawEdit|drawElement);
}
BOOL CElementProperSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	CWnd* pHelp = NULL;
	pHelp = GetDlgItem(ID_APPLY_NOW);

	if (pHelp != NULL)
	{
		CString text = "应用";
		pHelp->SetWindowText(text);
	}
	return bResult;
}

