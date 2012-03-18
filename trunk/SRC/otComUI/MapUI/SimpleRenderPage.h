#pragma once

#include "IRenderSetting.h"
#include "SymbolPreviewButton.h"
#include "Resource.h"
#include "afxwin.h"
//简单专题的设置

class CSimpleRenderPage : public CDialog ,public IRenderSetting
{
	DECLARE_DYNAMIC(CSimpleRenderPage)

public:
	CSimpleRenderPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSimpleRenderPage();

// 对话框数据
	enum { IDD = IDD_SIMPLE_RENDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	virtual long GetRenderType();
    
	virtual Carto::IRenderPtr GetRender();

	bool CreateDlg(CWnd *pParent);

	void Init();


public:
	
	afx_msg void OnBnClickedSrSymbolset();
	virtual BOOL OnInitDialog();

private:
	//预览按钮
	CSymbolPreviewButton m_PreviewBtn;

	Display::ISymbolPtr m_pSymbol;
};
