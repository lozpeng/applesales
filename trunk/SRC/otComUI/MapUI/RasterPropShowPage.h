#pragma once
#include "resource.h"
#include "RasterLayer.h"
#include "RasterRGBRender.h"
#include "afxwin.h"

// CRasterPropShowPage 对话框

class CRasterPropShowPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CRasterPropShowPage)

public:
	CRasterPropShowPage();
	virtual ~CRasterPropShowPage();

// 对话框数据
	enum { IDD = IDD_DLG_RASLAYER_PROPERTY };

	void SetLayer(Carto::CRasterLayerPtr layer);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	void InitLayerInfo();

	void UpdateChannelStaticInfo(long lChannelIndex);

	void UpdateInvalidValue();

	DECLARE_MESSAGE_MAP()

private:
	Carto::CRasterLayerPtr m_pLayer;
	Carto::CRasterRGBRender* m_pRGBRender;

	CString	m_csCellSizeX;
	CString	m_csCellSizeY;
	//统计信息
	float	m_fMax;
	float	m_fMean;
	float	m_fMin;
	float	m_fVar;
	float	m_Entroy;
	float   m_fInvalidValue;

	//无效值设置
	BOOL        m_bUseInvaidVal;
	float       m_fOrigInvaidVal;

	//背景色设置
	BOOL m_buseTrans;
	BYTE m_red;
	BYTE m_green;
	BYTE m_blue;


public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();  
	virtual BOOL OnApply();
	virtual void OnOK();

	CComboBox m_comboBand;
	CString m_csRows;
	CString m_csCols;
	CString m_csChannelCount;
	afx_msg void OnCbnSelchangeComboBands();
	afx_msg void OnBnClickedCheckSet();
	afx_msg void OnBnClickedCheckBackcolortrans();
	afx_msg void OnBnClickedBtnSelcolor();
};
