#pragma once
#include "afxwin.h"
#include "ButtonInfo.h"

class CPicContainer :
	public CWnd
{
	DECLARE_DYNAMIC(CPicContainer)
public:
	CPicContainer(void);
	~CPicContainer(void);


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	void SetImage(CString path);

	void SetDesc(CString text) {m_text =text;}

	void AddButtonInfo(stProduct &info) {m_ButtonInfo.push_back(info);}

private:
    HBITMAP LoadBMP(CString bmpPath);
public:
	//±³¾°Í¼Æ¬Â·¾¶
	CString m_ImagePath;
	//ÃèÊöÎÄ×Ö
	CString m_text;

	CBitmap *m_pBitmap;

	std::vector<stProduct> m_ButtonInfo;
	std::vector<CButton*>  m_buttons;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
