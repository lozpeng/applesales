// TDAppDoc.h : interface of the CTDAppDoc class
//


#pragma once

#include "IDocument.h"

class CTDAppDoc : public CDocument,public Framework::IDocument
{
protected: // create from serialization only
	CTDAppDoc();
	DECLARE_DYNCREATE(CTDAppDoc)

// Attributes
public:

	afx_msg void OnOpenProject();
	afx_msg void OnNewProject();
	afx_msg void OnSaveProject();

	void CreateNewProject();

	void ClearProject();

	void SaveProject();

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CTDAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:
	CString m_prjPath;
};


