// CntrItem.h : interface of the CTDAppCntrItem class
//

#pragma once

class CTDAppDoc;
class CTDAppView;

class CTDAppCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CTDAppCntrItem)

// Constructors
public:
	CTDAppCntrItem(CTDAppDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer

// Attributes
public:
	CTDAppDoc* GetDocument()
		{ return reinterpret_cast<CTDAppDoc*>(COleClientItem::GetDocument()); }
	CTDAppView* GetActiveView()
		{ return reinterpret_cast<CTDAppView*>(COleClientItem::GetActiveView()); }

	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);

	virtual BOOL OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow);

// Implementation
public:
	~CTDAppCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

