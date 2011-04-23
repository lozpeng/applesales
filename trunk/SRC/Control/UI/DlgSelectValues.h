#pragma once

#include "Resource.h"
#include <vector>
// CDlgSelectValues �Ի���

class CDlgSelectValues : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelectValues)

public:
	CDlgSelectValues(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSelectValues();

// �Ի�������
	enum { IDD = IDD_ADD_CLASSES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
