#pragma once
#include "afxdlgs.h"
# include "workflowWizardInclude.h"
#include "stdafx.h"
class CBCGPButton;
class WSEXT_CLASS CMyPropertySheet :
	public CPropertySheet
{
	DECLARE_DYNCREATE(CMyPropertySheet)
public:
	CMyPropertySheet(void);
	
	CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);	
	CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual BOOL OnInitDialog();


protected:
	//下一步
	virtual int DoNext();
	//上一步
	virtual int DoPrev();
	//跳过
	virtual int DoSkip();
	//更新按钮状态
	virtual int UpdateCustomButtons(bool isFirst, bool isLast);

public:
	~CMyPropertySheet(void);
private:
	CBCGPButton* nextButton;
	CBCGPButton* prevButton;
	CBCGPButton* cancelButton;
	CBCGPButton* helpButton;
protected:
	DECLARE_MESSAGE_MAP()
private:	
  afx_msg void OnBnClickedNext();
  afx_msg void OnBnClickedPrev();
  afx_msg void OnBnClickedCancel();
};
