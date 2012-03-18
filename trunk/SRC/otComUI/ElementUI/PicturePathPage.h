#pragma once
#include "PictureElement.h"
#include "resource.h"
// CPicturePathPage 对话框

class CPicturePathPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPicturePathPage)

public:
	CPicturePathPage();
	virtual ~CPicturePathPage();

	void SetElement(Element::CPictureElementPtr pElement);

	BOOL OnInitDialog();

	BOOL OnApply();

// 对话框数据
	enum { IDD = IDD_PAGE_PICTURE_PATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	Element::CPictureElementPtr m_pElement;
	afx_msg void OnBnClickedBtnSetPath();
	afx_msg void OnEnChangeEditPath();
};
