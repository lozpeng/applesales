#pragma once
#include "resource.h"
#include "ITextElement.h"
// CTExtContentPage �Ի���

class CTextContentPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CTextContentPage)

public:
	CTextContentPage();
	virtual ~CTextContentPage();

	void SetElement(Element::IElementPtr pElement);

	BOOL OnInitDialog();

	BOOL OnApply();

// �Ի�������
	enum { IDD = IDD_PAGE_TEXT_CONTENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	Element::IElementPtr m_pElement;
	afx_msg void OnEnChangeEditText();
};
