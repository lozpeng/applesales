// UAVSoftDoc.h : interface of the CUAVSoftDoc class
//


#pragma once


class CUAVSoftDoc : public CDocument
{
protected: // create from serialization only
	CUAVSoftDoc();
	DECLARE_DYNCREATE(CUAVSoftDoc)

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
	virtual ~CUAVSoftDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


