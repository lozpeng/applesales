// TExtContentPage.cpp : 实现文件
//

#include "stdafx.h"
#include "TextContentPage.h"
#include "ITextElement.h"
#include "MapTitle.h"

// CTExtContentPage 对话框

IMPLEMENT_DYNAMIC(CTextContentPage, CPropertyPage)

CTextContentPage::CTextContentPage()
	: CPropertyPage(CTextContentPage::IDD)
{

}

CTextContentPage::~CTextContentPage()
{
}

void CTextContentPage::SetElement(Element::ITextElementPtr pElement)
{
	m_pElement = pElement;
}

void CTextContentPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CTextContentPage, CPropertyPage)
	ON_EN_CHANGE(IDC_EDIT_TEXT, &CTextContentPage::OnEnChangeEditText)
END_MESSAGE_MAP()


// CTExtContentPage 消息处理程序
// CTExtContentPage 消息处理程序
BOOL CTextContentPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	if (m_pElement == NULL)
		return FALSE;

	if(m_pElement->GetType() & Element::ET_TEXT_ELEMENT)
	{
		Element::ITextElement* pText = dynamic_cast<Element::ITextElement*>(m_pElement.get());
		GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(pText->GetText().c_str());
	}
	else if(m_pElement->GetType() == Element::ET_MAP_TITLE)
	{
		Element::CMapTitle* pText = dynamic_cast<Element::CMapTitle*>(m_pElement.get());
		GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(pText->GetText().c_str());
	}


	return TRUE;
}

BOOL CTextContentPage::OnApply()
{
	if(!IsWindow(m_hWnd))
		return FALSE;

	if (m_pElement == NULL)
		return FALSE;

	UpdateData();

	CString cs;
	GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(cs);

	if(m_pElement->GetType() == Element::ET_SIMPLE_TEXT_ELEMENT)
	{
		Element::ITextElement* pText = dynamic_cast<Element::ITextElement*>(m_pElement.get());
		pText->SetText((LPSTR)(LPCSTR)cs);
	}
	else if(m_pElement->GetType() == Element::ET_MAP_TITLE)
	{
		Element::CMapTitle* pText = dynamic_cast<Element::CMapTitle*>(m_pElement.get());
		pText->SetText((LPSTR)(LPCSTR)cs);
	}

	SetModified(FALSE);

	return TRUE;
}

void CTextContentPage::OnEnChangeEditText()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	SetModified();
}
