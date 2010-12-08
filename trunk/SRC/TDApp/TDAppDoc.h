// TDAppDoc.h : interface of the CTDAppDoc class
//


#pragma once

#include "IDocument.h"

class CTDAppDoc : public COleDocument,public Framework::IDocument
{
protected: // create from serialization only
	CTDAppDoc();
	DECLARE_DYNCREATE(CTDAppDoc)

// Attributes
public:

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
};


