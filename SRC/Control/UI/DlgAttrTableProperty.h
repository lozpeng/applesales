#pragma once
// CDlgAttrTableProperty �Ի���
#include "Resource.h"

class CDlgAttrTableProperty : public CDialog
{
	DECLARE_DYNAMIC(CDlgAttrTableProperty)

public:
	CDlgAttrTableProperty(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAttrTableProperty();

// �Ի�������
	enum { IDD = IDD_ATTRTABLE_APPEARENCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
