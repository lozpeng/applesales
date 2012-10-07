#if !defined(AFX_DLGPRINTIMGSET_H__EBDF1989_2B9E_479A_849F_DC93125E4F47__INCLUDED_)
#define AFX_DLGPRINTIMGSET_H__EBDF1989_2B9E_479A_849F_DC93125E4F47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPrintImgSet.h : header file
#include "resource.h"
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPrintImgSet dialog

class CDlgPrintImgSet : public CDialog
{
// Construction
public:
	CDlgPrintImgSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPrintImgSet)
	enum { IDD = IDD_DLG_PRINTIMGFILE };
	double	m_dblDpi;
	CString	m_strPrintImg;
	CString	m_strWidth;
	CString	m_strHeight;
	//}}AFX_DATA
	CString m_strPrintImgPath;
	double  m_dblSizeX,m_dblSizeY;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrintImgSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPrintImgSet)
	afx_msg void OnButtonPrintimgfile();
	afx_msg void OnChangeEditDpi();
	afx_msg void OnUpdateEditDpi();
	afx_msg void OnKillfocusEditDpi();
	afx_msg void OnBUTTONUpDate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPRINTIMGSET_H__EBDF1989_2B9E_479A_849F_DC93125E4F47__INCLUDED_)
