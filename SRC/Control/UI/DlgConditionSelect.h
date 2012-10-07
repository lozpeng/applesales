
#pragma once

#include "Resource.h"
#include "IFeatureClass.h"

class CDlgConditionSelect : public CDialog
{
public:
	CDlgConditionSelect(CWnd* pParent = NULL);   // standard constructor
	CDlgConditionSelect(Geodatabase::IFeatureClass *pFeatureClass);
public:


	BOOL LoadTableFields( ); 


	enum { IDD = IDD_DLG_CONDITIONSELECT };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support



protected:

	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditCondition();
	afx_msg void OnSelchangeListLayername();
	afx_msg void OnSelchangeListFunction();
	afx_msg void OnBnAdd();
	afx_msg void OnBnSub();
	afx_msg void OnBnMul();
	afx_msg void OnBnDiv();
	afx_msg void OnBnLt();
	afx_msg void OnBnGt();
	afx_msg void OnBnEq();
	afx_msg void OnBnExp();
	afx_msg void OnBnLe();
	afx_msg void OnBnGe();
	afx_msg void OnBnNe();
	afx_msg void OnBnAnd();
	afx_msg void OnBnOr();
	afx_msg void OnBnNot();
	afx_msg void OnBnParen();
	afx_msg void OnSelchangeListFieldname();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnStart();
	afx_msg void OnBnContain();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


public:
	CListBox	mg_cFunctionList;

	CEdit	mg_cCondition;
	CString	mg_csCondition;
	CString	mg_csFunction;
	CString	mg_csFieldName;

	CStringArray	mg_cFieldsName;
	CStringArray	mg_cFunction;
	int				mg_iStart, mg_iEnd;
	
	BOOL			mg_bHasSrcTable;	

	BOOL			mg_bTable;	

	Geodatabase::IFeatureClass *m_pFeatureClass;


};


