#pragma once
#include "Resource.h"
#include "ILayer.h"
#include "IMapCtrl.h"

namespace Framework
{
	class IMapCtrl;
}
class CTransparentDLG : public CDialog
{
	DECLARE_DYNAMIC(CTransparentDLG)

	enum Type{EHC_TRANS, EHC_ALTERNATE};

public:
	CTransparentDLG(Type nameType = EHC_TRANS, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTransparentDLG();
	BOOL OnInitDialog();

	void SetLayer(Carto::ILayerPtr pLayer) {m_pLayer = pLayer;};

	void SetMapCtrl(Framework::IMapCtrl* pMapCtrl ) {m_pMapCtrl = pMapCtrl;};

// 对话框数据
	enum { IDD = IDD_TRANSPARENT_ENHANCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	CSliderCtrl m_sldCtrl;
	CStatic m_staticPos;
	int m_sldPos;

	Carto::ILayerPtr m_pLayer;

	Framework::IMapCtrl* m_pMapCtrl;

	Type m_enumType;

	bool bShow;
};



