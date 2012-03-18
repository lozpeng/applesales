// TExtContentPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TextContentPage.h"
#include "ITextElement.h"
#include "MapTitle.h"

// CTExtContentPage �Ի���

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


// CTExtContentPage ��Ϣ�������
// CTExtContentPage ��Ϣ�������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetModified();
}
