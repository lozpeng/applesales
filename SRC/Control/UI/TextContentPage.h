#pragma once
#include "resource.h"
#include "ITextElement.h"
// CTExtContentPage 对话框

class CTextContentPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CTextContentPage)

public:
	CTextContentPage();
	virtual ~CTextContentPage();

	void SetElement(Element::IElementPtr pElement);

	BOOL OnInitDialog();

	BOOL OnApply();

// 对话框数据
	enum { IDD = IDD_PAGE_TEXT_CONTENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	Element::IElementPtr m_pElement;
	afx_msg void OnEnChangeEditText();
};
