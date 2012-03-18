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
	CRangeRenderPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRangeRenderPage();

// �Ի�������
	enum { IDD = IDD_RANGE_RENDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    
	virtual long GetRenderType();

	virtual Carto::IRenderPtr GetRender();

	virtual bool CreateDlg(CWnd *pParent);

	void ShowSymbol(int index);

	//�޸�ѡ����
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

	//Ԥ����ť
	CSymbolPreviewButton m_BtnOverview;

	CRangeRenderList m_list;
	long m_Breaknum; //�ֶ���

	CBCGPColorButton m_BtnStartcolor;
	CBCGPColorButton m_BtnEndcolor;

	//���еķֶμ�¼
	std::vector<RangeItem> m_Classes;

	//��ǰ�������
	int m_curIndex;


};
