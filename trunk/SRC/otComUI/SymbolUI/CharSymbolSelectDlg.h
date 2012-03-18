#pragma once
#include "bcgpdialog.h"
#include "Resource.h"
#include "CharSymbolSelectListBox.h"
#include "SymbolPropList.h"
const long NUMSYMBOLPERROW = 8;
const long FONTSYMBOLNUMS  = 65535;

class CCharSymbolSelectDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CCharSymbolSelectDlg)
public:
	CCharSymbolSelectDlg(CWnd* pParent = NULL);
	virtual ~CCharSymbolSelectDlg(void);

	void SetCharMarkSymbol(Display::CCharMarkerSymbolPtr pCharMarkSymbol);
	void SetSymbolSelectProp(CCharSymbolSelectProp* pSymbolSelectProp);

	enum { IDD = IDD_CHARSELECTDLG };

	DECLARE_MESSAGE_MAP()
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö
private:
	CCharSymbolSelectListBox m_ctrlCharSymbolListBox;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
private:
	Display::CCharMarkerSymbolPtr m_pCharMarkSymbol;
	CCharSymbolSelectProp *m_pSymbolSelectProp;
};
