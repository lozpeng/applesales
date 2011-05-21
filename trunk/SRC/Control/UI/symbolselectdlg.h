#pragma once

#include "SymbolList.h"
#include "SymbolPreviewButton.h"
#include "SymbollibLoader.h"
#include "resource.h"


// CDlgSymbolSelect 对话框

class CDlgSymbolSelect : public CDialog 
{
	DECLARE_DYNAMIC(CDlgSymbolSelect)

public:


	CDlgSymbolSelect(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSymbolSelect();

	// 对话框数据
	enum { IDD = IDD_SYMBOLSEL_DLG };

protected:
	
	void UpdateAddSymbolMenu();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSymbolEdit();
public:
	afx_msg void OnBnClickedAddSymbollib();
public:
	afx_msg void OnOpenSymbolLibMenuItems(UINT nID);
	afx_msg void OnBnClickedBtnOverview();
	afx_msg void OnSymbolMenuItems(UINT nID);
	afx_msg void OnAddSymbolMenuItems(UINT nID);
	afx_msg void OnSymbolMenuItemsUI(CCmdUI *pCmdUI);


	

public:

	void SetSymbol(Display::ISymbolPtr pSymbol);

	Display::ISymbolPtr GetSymbol() {return m_pSymbol;}

	afx_msg void OnBnClickedOk();

	virtual BOOL OnInitDialog();

	afx_msg void OnBnKillfocusBtnOverview();

	bool InstallSymbol(char * pStrName = NULL);

	afx_msg void OnBnClickedSavesymbol();

	afx_msg void OnLvnItemchangedListSymbol(NMHDR *pNOTDR, LRESULT *pResult);

	afx_msg void OnEnChangeSymname();

	afx_msg void OnBnClickedSymbolfind();

protected:
	void InitData(void);

public:

	afx_msg LRESULT OnReFindEdit(WPARAM wParam, LPARAM lParam);


	afx_msg void OnEnChangeSymkey();

	afx_msg void OnBnClickedSymbolresetting();	
	afx_msg void OnBnClickedCheckNoneSymbol();

private:
	CButton m_btFind;
	CSymbolList m_SymList;
	CSymbolPreviewButton m_SymButton;
	CMenu * m_SymbolLibMenu, *m_SymAddMenu;
	CImageList	m_cSymbolImageList;
	vector<CSymbolLibLoader*> SymLibs;
	Display::ISymbolPtr m_pSymbol;
    Display::ISymbolPtr m_pcopySymbol;
	int m_nSelect;
	BOOL m_bRun;

	CString m_SymKeyString;
	int m_nMenuID;
	char m_cPath[512];	
	CString m_SymbolName;
	CButton m_btOk;
	bool m_bFind;
	CString m_strSymFile;
public:
	afx_msg void OnNMClickListSymbol(NMHDR *pNMHDR, LRESULT *pResult);
};

