#pragma once

#include "resource.h"
#include "SymbolPropList.h"
#include "EditDlgManageControl.h"
// CDlgSymbolEdit 对话框

class CDlgSymbolEdit : public CDialog 
{
	DECLARE_DYNAMIC(CDlgSymbolEdit)

public:
	CDlgSymbolEdit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSymbolEdit();

// 对话框数据
	enum { IDD = IDD_SYMBOLEDIT_DIALOG };
	CBitmap add_Pic;
	CBitmap del_Pic;
	CBitmap up_Pic;
	CBitmap down_Pic;
	CBitmap copyBUT_Pic;
	CBitmap paste_Pic;
	CBCGPButton m_btAdd,m_btDel,m_btUp,m_btDown,m_btCopyBUT,m_btPaste;
	CButton m_btCRossLine,m_btSTRLine,m_btCrLine;		
	CBCGPButton  m_btAddition, m_btSubtration ,m_btZoomFix;// +、-、1:1按钮
	
	BOOL  m_bReBuild;
	BOOL m_bDraw,m_bSolid;					//是否绘制，是直线或折线
protected:
	int m_UnitComboIndex;
	int m_currentSymbolType;				//当前符号类型，为给变更符号用的下拉列表判断是否创建时使用
	CString currentPath;
	CComboBox m_comboSelType,m_cComboBoxZoom,m_UnitCombo;
	SYSTEM::CArray<int> m_symbolTypeOfCreate;					//根据当前符号类型，判断出的可用的同类符号的类型存储
	CSymbolPropList	m_wndPropList;
	/*Display::ISymbolPtr m_pSymbol;*/
	CEditDlgManageControl m_editDlgManager;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void SetSymbolType(SYMBOL_TYPE type);
	void CDlgSymbolEdit::SetSymbolUnit(SYSTEM::SYS_UNIT_TYPE symbolUnit);
	DECLARE_MESSAGE_MAP()
public:
	void SetSymbol(Display::ISymbolPtr pSymbol);
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedBlowup();
	afx_msg void OnBnClickedCopy();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedMovedown();
	afx_msg void OnBnClickedMoveup();
	afx_msg void OnBnClickedPaste();
	afx_msg void OnBnClickedZoomfix();
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnPropChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRepaintLegend(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReSetSymbolTypeCombo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReSetSymbolUnitCombo(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDialog();
	CStatic m_picture;
	void ShowSymbol(void);

	afx_msg void OnDestroy();
	void LoadConfig(void);
	SYSTEM::SYS_UNIT_TYPE unit;
	
public:
	virtual Display::ISymbolPtr EditSymbol(Display::ISymbolPtr pSymbol);// 实现父类纯虚函数
public:
	afx_msg void OnBnClickedStrLine();
public:
	afx_msg void OnBnClickedCrLine();
public:
	afx_msg void OnBnClickedCrossline();
public:
	afx_msg void OnBnClickedReduce();
public:
	afx_msg void OnCbnSelchangeZoom();
	afx_msg void OnCbnSelchangeCombounits();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnSelchangeComboSymtype();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
