#pragma once

#include "Resource.h"
#include "IRenderSetting.h"
#include "SymbolPreviewButton.h"
#include "RangeRender.h"
#include "RangeRenderList.h"
#include "GrdintClrComboBox.h"

class CRangeRenderPage : public CDialog ,public IRenderSetting
{
	DECLARE_DYNAMIC(CRangeRenderPage)

public:
	CRangeRenderPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRangeRenderPage();

// 对话框数据
	enum { IDD = IDD_RANGE_RENDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    
	virtual long GetRenderType();

	virtual Carto::IRenderPtr GetRender();

	virtual bool CreateDlg(CWnd *pParent);

	void ShowSymbol(int index);

	//修改选择项
	void ModifySelItem(int index);

	afx_msg void OnBnClickedBtnAutoSetrange();
	afx_msg void OnBnClickedBtnRangeOverview();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboRangeField();
private:

	void Init();

	void InitList();
    
public:
	struct RangeItem
	{
		double min;
		double max;
		Display::ISymbolPtr pSymbol;
		CString strLabel;
	};
public:
	Carto::IRangeRenderPtr m_pRender;
	CGrdintClrComboBox m_ctlColorRamp;
	CComboBox m_ComboFields;
	CString m_renderField;
	CString m_strHeading;

	//预览按钮
	CSymbolPreviewButton m_BtnOverview;

	CRangeRenderList m_list;
	long m_Breaknum; //分段数

	CBCGPColorButton m_BtnStartcolor;
	CBCGPColorButton m_BtnEndcolor;

	//所有的分段记录
	std::vector<RangeItem> m_Classes;

	//当前符号序号
	int m_curIndex;


};
