// GeoscapeProDoc.h : interface of the CGeoscapeProDoc class
//


#pragma once


class CGeoscapeProDoc : public CDocument
{
protected: // create from serialization only
	CGeoscapeProDoc();
	DECLARE_DYNCREATE(CGeoscapeProDoc)

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
	virtual ~CGeoscapeProDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


