// DlgSetChangeSymbol.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "DlgSetChangeSymbol.h"
#include "ImageProcessTool.h"
#include "ISymbolListCtrl.h"
using namespace Control;

IMPLEMENT_DYNAMIC(CDlgSetChangeSymbol, CDialog)

CDlgSetChangeSymbol::CDlgSetChangeSymbol(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetChangeSymbol::IDD, pParent)
{

}

CDlgSetChangeSymbol::~CDlgSetChangeSymbol()
{
}

void CDlgSetChangeSymbol::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_SHOWSYMBOL, m_SymbolBtn);
}


BEGIN_MESSAGE_MAP(CDlgSetChangeSymbol, CDialog)
	ON_BN_CLICKED(IDC_BTN_CHASYMBOL, &CDlgSetChangeSymbol::OnBnClickedBtnChasymbol)
	ON_BN_CLICKED(IDOK, &CDlgSetChangeSymbol::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSetChangeSymbol 消息处理程序

BOOL CDlgSetChangeSymbol::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(!CImageProcessTool::m_pChangeSymbol)
	{
		CImageProcessTool::InitSymbol();
	}
	m_pSymbol = CImageProcessTool::m_pChangeSymbol->Clone();
	m_SymbolBtn.SetSymbol(m_pSymbol.get());

    
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgSetChangeSymbol::OnBnClickedBtnChasymbol()
{
	Framework::ISymbolListCtrl *pCtrl =dynamic_cast<Framework::ISymbolListCtrl*>(Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppSymbolLstCtrl));
	if(pCtrl)
	{
		m_pSymbol =pCtrl->SelectSymbol(m_pSymbol);
	}
	m_SymbolBtn.SetSymbol(m_pSymbol.get());
}

void CDlgSetChangeSymbol::OnBnClickedOk()
{
	if(m_pSymbol)
	{
		CImageProcessTool::m_pChangeSymbol =m_pSymbol;
	}
	OnOK();
}
