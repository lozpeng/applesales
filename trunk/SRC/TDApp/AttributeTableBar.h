#pragma once

#include "AttributeTable.h"
/*------------------------------------------------*/
//通知父窗口选择数目发生改变
#define WM_UPDATESELECTNUM WM_USER+100
#define WM_MESSAGE_FLASH WM_USER+101


/*------------------------------------------------*/

class CAttriToolBar : public CBCGPToolBar
{
public:	
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)	
	{		
		CBCGPToolBar::OnUpdateCmdUI ((CFrameWnd*) GetOwner (), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList () const		{	return FALSE;	}
};

class CAttributeTableBar: public CBCGPDockingControlBar
{
public:
	CAttributeTableBar(void);
	virtual ~CAttributeTableBar(void);
	
	void SetTableEdit( bool bEdit = true );

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	
	afx_msg void OnUpdateTableEdit(CCmdUI* pCmdUI);

	afx_msg void OnTableQuery();
	afx_msg void OnUpdateTableQuery(CCmdUI* pCmdUI);
	
	afx_msg void OnFindReplace();
	afx_msg void OnUpdateFindReplace(CCmdUI* pCmndUI);

	afx_msg void OnSelectAll();
	afx_msg void OnUpdateSelectAll(CCmdUI* pCmndUI);

	afx_msg void OnSelectNone();
	afx_msg void OnUpdateSelectNone(CCmdUI* pCmndUI);

	afx_msg void OnAddField();
	afx_msg void OnUpdateAddField(CCmdUI* pCmndUI);

	afx_msg void OnStartEdit();
	afx_msg void OnUpdateStartEdit(CCmdUI* pCmndUI);

	afx_msg void OnStopSaveEdit();
	afx_msg void OnUpdateStopSaveEdit(CCmdUI* pCmndUI);

	afx_msg void OnShowFields();

	afx_msg void OnOutputTable();
	
	afx_msg void OnPrintTable();
	
	afx_msg void OnSetAprearence();

	afx_msg LRESULT OnUpdateSelNum(WPARAM wParam, LPARAM lParam);

public:

	Control::CAttributeTable *GetTable() {return &m_table;}
public:

	Control::CAttributeTable m_table;

	CAttriToolBar m_OperToolbar;


};
