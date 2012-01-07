#pragma once
#include "ISymbol.h"
#include "afxwin.h"
#include "SymbolPreviewButton.h"
// CDlgSetChangeSymbol 对话框

class CDlgSetChangeSymbol : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetChangeSymbol)

public:
	CDlgSetChangeSymbol(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSetChangeSymbol();

// 对话框数据
	enum { IDD = IDD_SET_CHANSYMBOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnChasymbol();
	afx_msg void OnBnClickedOk();

private:
	Display::ISymbolPtr m_pSymbol;

public:
	CSymbolPreviewButton m_SymbolBtn;
};
