#pragma once

#include "MapControl.h"
#include "IElement.h"
#include "afxcmn.h"
// CDialogCreateRoi �Ի���
struct ROI_INFO
{
	COLORREF	lColor;
	CString		strClassNmae;
	CRgn		rgn;
};
class CDialogCreateRoi : public CDialog
{
	DECLARE_DYNAMIC(CDialogCreateRoi)

public:
	CDialogCreateRoi(Framework::IMapCtrl* pMapCtrl,CWnd* pParent=NULL);   // ��׼���캯��
	virtual ~CDialogCreateRoi();

// �Ի�������
	enum { IDD = IDD_DLG_CREATE_ROI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAdd();
public:
	void						InitList();
	void						InitCol();
	void						RemoveROIElement(Element::IElementPtr pElement);
	void						AddROIElement(CRgn& rgn, Element::IElementPtr pElement);
public:
	bool						m_bNewROI;
protected:
	Framework::IMapCtrl*		m_pMapCtrl;
public:
	std::list<ROI_INFO*>		m_lstROI;
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnDel();
};
