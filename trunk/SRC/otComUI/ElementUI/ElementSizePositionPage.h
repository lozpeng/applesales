#pragma once
#include "Resource.h"
#include "SystemUnit.h"
#include "IElement.h"

// CDlgElementSizePosition 对话框

class CElementSizePositionPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CElementSizePositionPage)

public:
	CElementSizePositionPage();   // 标准构造函数
	virtual ~CElementSizePositionPage();

public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	enum { IDD = IDD_PAGE_ELEMENT_SIZE_POS };

	DECLARE_MESSAGE_MAP()

public:

	BOOL OnInitDialog();

	BOOL SetCtrls();

	void SetLayoutUnit(SYSTEM::SYS_UNIT_TYPE unit);

	void SetElement(Element::IElementPtr pElement);


	void SetModified(BOOL bChanged = TRUE );

	virtual BOOL OnApply();


private:
	GEOMETRY::geom::Coordinate GetAnchorPos(GEOMETRY::geom::Envelope& env);

	GEOMETRY::geom::Envelope CalcEnvelope(double fPosX, double fPosY, double fWidth, double fHeight);


protected:

	SYSTEM::SYS_UNIT_TYPE m_unit;
	std::string m_unitText;
	Element::IElementPtr m_pElement;
	GEOMETRY::geom::Envelope m_envlope;
	Element::ELEMENT_ANCHOR_POS m_AnchorPos;
	float m_WHRatio;

private:
	CButton m_chkAnchor;

	double	m_EditPosX;
	double	m_EditPosY;
	double	m_EditWidth;
	double	m_EditHeight;
	CEdit	m_EditName;
	int		m_radioAnchor;
	BOOL	m_bChkWHRatioMode;
	BOOL	m_bModified;
public:
	afx_msg void OnEnChangeEditPosX();
	afx_msg void OnEnChangeEditPosY();
	afx_msg void OnBnClickedRadioLeftTop();
	afx_msg void OnBnClickedRadioCenterTop();
	afx_msg void OnBnClickedRadioRightTop();
	afx_msg void OnBnClickedRadioLeftCenter();
	afx_msg void OnBnClickedRadioCenterCenter();
	afx_msg void OnBnClickedRadioRightCenter();
	afx_msg void OnBnClickedRadioLeftBottom();
	afx_msg void OnBnClickedRadioCenterBottom();
	afx_msg void OnBnClickedRadioRightBottom();
	afx_msg void OnEnChangeEditWidth();
	afx_msg void OnEnChangeEditHeight();
	afx_msg void OnEnChangeEditName();
	afx_msg void OnBnClickedChkWhRatio();
	afx_msg void OnEnKillfocusEditWidth();
	afx_msg void OnEnKillfocusEditHeight();
};
