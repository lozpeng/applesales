#pragma once
// CDlgAttrTableProperty 对话框
#include "Resource.h"

class CDlgAttrTableProperty : public CDialog
{
	DECLARE_DYNAMIC(CDlgAttrTableProperty)

public:
	CDlgAttrTableProperty(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAttrTableProperty();

// 对话框数据
	enum { IDD = IDD_ATTRTABLE_APPEARENCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void SetSelColor( COLORREF colorSel );
	COLORREF GetSelColor();

	void SetTableColor( COLORREF colorFont );
	COLORREF GetTableColor();

	void SetFont( CString szFont );
	CString GetFont();
	
	void SetFontSize( int fontSize );
	int GetFontSize();
	
public:
	CComboBox m_cmbFont;

protected:
	CBCGPColorButton m_btnSelColor;
	CBCGPColorButton m_btnFontColor;
	CComboBox m_cmbFontSize;

	COLORREF m_colorSel;
	COLORREF m_colorTableFont;

	CString m_strFont;
	CString m_strFontSize;

	int m_iFontSize;


public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
