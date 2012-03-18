#pragma once

#include "Resource.h"

#include "ISymbol.h"
#include "SymbolPreviewButton.h"

class CDlgModifyUniClass : public CDialog
{
	DECLARE_DYNAMIC(CDlgModifyUniClass)

public:
	CDlgModifyUniClass(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgModifyUniClass();

// �Ի�������
	enum { IDD = IDD_MODIFY_UNIQUE_CLASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnUniov();
	virtual BOOL OnInitDialog();

	void Init(CString value,CString label,Display::ISymbolPtr pSymbol);
public:
	bool    m_bUniqueRender;

	CString m_strValue;
	CString m_strLabel;

	Display::ISymbolPtr m_pSymbol;
	
	CSymbolPreviewButton m_btn;
};
