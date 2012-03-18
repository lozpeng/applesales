#pragma once
#include "PictureElement.h"
#include "resource.h"
// CPicturePathPage �Ի���

class CPicturePathPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPicturePathPage)

public:
	CPicturePathPage();
	virtual ~CPicturePathPage();

	void SetElement(Element::CPictureElementPtr pElement);

	BOOL OnInitDialog();

	BOOL OnApply();

// �Ի�������
	enum { IDD = IDD_PAGE_PICTURE_PATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	Element::CPictureElementPtr m_pElement;
	afx_msg void OnBnClickedBtnSetPath();
	afx_msg void OnEnChangeEditPath();
};
