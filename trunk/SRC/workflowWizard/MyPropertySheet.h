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
	//��һ��
	virtual int DoNext();
	//��һ��
	virtual int DoPrev();
	//����
	virtual int DoSkip();
	//���°�ť״̬
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
