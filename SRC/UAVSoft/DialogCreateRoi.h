#pragma once

#include "MapControl.h"
#include "IElement.h"
#include "afxcmn.h"
// CDialogCreateRoi 对话框
struct ROI_INFO
{
	COLORREF			lColor;
	CString				strClassNmae;
	std::vector<CRgn*>	rgns;
	/*~ROI_INFO()
	{
		for (int i=0; rgns.size(); i++)
		{
			delete rgns[i];
			rgns[i] = NULL;
		}
		rgns.clear();
	}*/
};

struct ELE_INFO
{
	CString								strClassNmae;
	std::vector<Element::IElementPtr>	elems;
};
class CDialogCreateRoi : public CDialog
{
	DECLARE_DYNAMIC(CDialogCreateRoi)

public:
	CDialogCreateRoi(Framework::IMapCtrl* pMapCtrl,CWnd* pParent=NULL);   // 标准构造函数
	virtual ~CDialogCreateRoi();

// 对话框数据
	enum { IDD = IDD_DLG_CREATE_ROI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAdd();
public:
	void						InitList();
	void						InitCol();
	void						RemoveROIElement(Element::IElementPtr pElement);
	void						AddROIElement(CRgn& rgn, Element::IElementPtr pElement);
	HBITMAP                     CoverBitmap( Display::ISymbolPtr pSymbol );
public:
	bool						m_bNewROI;
protected:
	Framework::IMapCtrl*		m_pMapCtrl;
	bool						m_bMulti;
	COLORREF					m_lCurColor;
	int							m_nCount;
	int							m_nIndex;
public:
	std::vector<ROI_INFO*>		m_lstROI;
	std::vector<ELE_INFO>		m_lstEle;
	std::string					m_strLyrName;
public:
	CListCtrl m_list;
	CImageList m_ImageList;
	int m_cx, m_cy;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnDel();
};
