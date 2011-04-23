#pragma once

#include "Resource.h"
#include <vector>
// CDlgSelectValues 对话框

class CDlgSelectValues : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelectValues)

public:
	CDlgSelectValues(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSelectValues();

// 对话框数据
	enum { IDD = IDD_ADD_CLASSES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedAddselect();
	afx_msg void OnBnClickedAddallValue();
	afx_msg void OnBnClickedRemoveSelect();
	afx_msg void OnBnClickedRemoveallValue();
	afx_msg void OnLbnDblclkListAllvalues();
	afx_msg void OnLbnDblclkListSelectvalue();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

public:
	CListBox m_listAllValues;
	CListBox m_listSelect;

	std::vector<CString> m_allValues;
	std::vector<CString> m_values;


	

};
