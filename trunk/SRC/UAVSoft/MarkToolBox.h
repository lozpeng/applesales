// ToolBox.h: interface for the CToolBoxBar class.
//

#if !defined(AFX_TOOLBOX_H__F9C28947_2C41_47AD_9BAB_E2516CEEC6E0__INCLUDED_)
#define AFX_TOOLBOX_H__F9C28947_2C41_47AD_9BAB_E2516CEEC6E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CToolBoxBar : public CBCGPToolBox
{
// Construction
public:
	CToolBoxBar();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBoxBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolBoxBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolBoxBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CMarkToolBoxBarEx : public CBCGPToolBoxEx
{
// Construction
public:
	CMarkToolBoxBarEx();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBoxBarEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMarkToolBoxBarEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolBoxBarEx)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_TOOLBOX_H__F9C28947_2C41_47AD_9BAB_E2516CEEC6E0__INCLUDED_)
