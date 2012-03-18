#include "StdAfx.h"
#include "ElementProperSheet.h"
//#include "ILayoutCtrl.h"
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

	m_pMap =NULL;
	m_pCallBack =NULL;
}

CElementProperSheet::~CElementProperSheet(void)
{
}

void CElementProperSheet::SetElement(Element::IElementPtr pElement,Carto::CMap* pMap,otComUI::ILayerPropCallback *pCallBack)
{
	m_pElement = pElement;

	m_pMap =pMap;
	m_pCallBack =pCallBack;

}

void CElementProperSheet::OnOK()
{
	//调用每个页面的应用函数
	//if(m_pElement == NULL)
	//	return;

	//int pagecount =GetPageCount();
	//for(int i=0;i<pagecount;i++)
	//{
	//	CPropertyPage* page =GetPage(i);
	//	page->OnOK();
	//}
	////获取活动制图控件
	//if(m_pCallBack)
	//{
	//	m_pCallBack->UpdateMapCtrl();
	//}


	
}

void CElementProperSheet::OnApply()
{
	//调用每个页面的应用函数
	if(m_pElement == NULL)
		return;

	CPropertyPage* pPage = GetActivePage();
	pPage->OnApply();

	//获取活动制图控件
	if(m_pCallBack)
	{
		m_pCallBack->UpdateMapCtrl();
	}
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

