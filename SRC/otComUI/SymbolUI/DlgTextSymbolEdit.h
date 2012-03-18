#pragma once

#include "resource.h"
#include "SymbolPropList.h"
#include "TextSymbol.h"
#include "TextSymbolPropListManager.h"
// CDlgTextSymbolEdit 对话框 

class CDlgTextSymbolEdit : public CDialog 
{
	DECLARE_DYNAMIC(CDlgTextSymbolEdit)

public:
	CDlgTextSymbolEdit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTextSymbolEdit();

// 对话框数据
	enum { IDD = IDD_TEXT_SYMBOLEDIT_DIALOG };
	
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	void CDlgTextSymbolEdit::SetSymbolUnit(SYSTEM::SYS_UNIT_TYPE symbolUnit);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void LoadConfig(void);
	void SetSymbol(Display::CTextSymbolPtr pSymbol);
	void ShowSymbol(void);


	afx_msg void OnBnClickedBlowup();

	afx_msg void OnBnClickedReduce();

	afx_msg void OnBnClickedZoomfix();

	afx_msg void OnCbnSelchangeZoom();

	afx_msg void OnCbnSelchangeCombounits();

	afx_msg LRESULT OnPropChange(WPARAM wParam, LPARAM lParam);
	
	afx_msg LRESULT OnRepaintLegend(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnReSetSymbolUnitCombo(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedOk();

	afx_msg void OnBnClickedCancel();

	afx_msg void OnDestroy();

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);





public:
	CBCGPButton  m_btAddition, m_btSubtration ,m_btZoomFix;// +、-、1:1按钮

	CComboBox m_comboSelType,m_cComboBoxZoom,m_UnitCombo;

	CStatic m_picture;

	CSymbolPropList	m_wndPropList;

	SYSTEM::SYS_UNIT_TYPE unit;

	int m_UnitComboIndex;
	
	Display::CTextSymbolPtr m_pTextSymbol;

	Display::CTextSymbolPtr m_pCopySymbol;

	CTextSymbolPropListManager m_properlistManager;
};
