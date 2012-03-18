#pragma once

#include "IRenderSetting.h"
#include "SymbolPreviewButton.h"
#include "Resource.h"
#include "afxwin.h"
//��ר�������

class CSimpleRenderPage : public CDialog ,public IRenderSetting
{
	DECLARE_DYNAMIC(CSimpleRenderPage)

public:
	CSimpleRenderPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSimpleRenderPage();

// �Ի�������
	enum { IDD = IDD_SIMPLE_RENDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	//Ԥ����ť
	CSymbolPreviewButton m_PreviewBtn;

	Display::ISymbolPtr m_pSymbol;
};
