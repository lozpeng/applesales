#pragma once
#include "Map.h"
#include "IMapCtrl.h"
#include "RasterRGBRender.h"
#include "Resource.h"


// CEnhanceSld 对话框

namespace Framework
{
	class IMapCtrl;
}
class CEnhanceSld : public CDialog
{
	DECLARE_DYNAMIC(CEnhanceSld)

public:
	CEnhanceSld(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEnhanceSld();
	BOOL OnInitDialog();
	void SetGeoMap(Carto::CMapPtr *pGeoMap,Display::IDisplayPtr pdisplay,Framework::IMapCtrl *pMap){m_pGeoMap=pGeoMap;m_pdisplay=pdisplay;m_pMap=pMap;};
	void SetGeoMapDCs(CDC *pDC1, CDC *pDC2, CRect drawRect,HDC pdc){m_pDC1 = pDC1; m_pDC2 = pDC2;m_drawRect = drawRect;m_pdc=pdc;};

// 对话框数据
	enum { IDD = IDD_SWIPE_SHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRadioLr();
	afx_msg void OnBnClickedRadioUd();
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
private:
	CSliderCtrl m_sldCtrl;
	CStatic m_staticPos;
	CButton m_rdLR;
	CRect m_drawRect;
	CString m_enhanceName;

	int m_sldPos;
	CDC *m_pDC1, *m_pDC2;
	HDC m_pdc;
	HDC m_hdc1;
    HDC m_hdc2;
	HDC m_hClientDC;


	Carto::CMapPtr* m_pGeoMap;
	Display::IDisplayPtr m_pdisplay;
	Framework::IMapCtrl *m_pMap;



};
