#pragma once

#include "Resource.h"
#include "IRenderSetting.h"
#include "SymbolPreviewButton.h"
#include "UniqueRender.h"
#include "UniqueRenderList.h"



//������Ψһֵ�б��е�һ�����
struct SymbolClass
{
	bool operator< (const SymbolClass &other)
	{
		return index<other.index;
	}
    CString strLabel; //��ı��
	Display::ISymbolPtr pSymbol; //����
	CString strCount; //Ԫ�ص���Ŀ
	int index; //���б��е�λ��


};


class CUniqueRenderPage : public CDialog,public IRenderSetting
{
	DECLARE_DYNAMIC(CUniqueRenderPage)

public:
	CUniqueRenderPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUniqueRenderPage();

// �Ի�������
	enum { IDD = IDD_UNIQUE_RENDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual long GetRenderType();

	virtual Carto::IRenderPtr GetRender();

	virtual bool CreateDlg(CWnd *pParent);

	virtual BOOL OnInitDialog();

	//�޸�ѡ����
	void ModifySelItem(int index);

	//Ԥ����ʾָ���ķ���
	void ShowSymbol(CString &value);

	afx_msg void OnCbnSelchangeComboUniqueField();

	afx_msg void OnBnClickedUniAddall();
	afx_msg void OnBnClickedUniAdd();
	afx_msg void OnBnClickedUniRemove();
	afx_msg void OnBnClickedUniRemoveall();
	afx_msg void OnBnClickedBtnUniSymbolset();
	afx_msg void OnBnClickedBtnUniOverview();
	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnDown();
	afx_msg void OnDestroy();

private:
	void Init();

	//��ʼ�������б�
	void InitList();
	
    //����һ������ķ���
	Display::ISymbolPtr  AddUniquerSymbol();

	void FillValues(std::vector<CString> &allValues);

public:
	CUniquerRenderSymbolList m_list;
	CSymbolPreviewButton m_BtnOverview;
	CComboBox m_ComboFields;
	CString m_strHeading;
	Carto::IUniqueRenderPtr m_pRender;

	//Ψһֵ��Ⱦ���ֶ�
	CString m_renderField;

	//Ĭ�Ϸ���
	Display::ISymbolPtr m_pDefaultSymbol;
    //Ĭ�ϱ��
	CString m_DefaultLabel;

	SYMBOL_TYPE m_nType;
	
	typedef std::map<CString,SymbolClass> SCMAP;

	//�����˷�����Ϣ
	SCMAP m_SymbolMap;
    //������ÿ�����б��е����
	std::vector<CString> m_IndexList;

	//Ŀǰ��ʾ��Ԥ�����е�Ҫ�ص�ֵ
	CString m_curValue;
	
	CBCGPButton m_BtnUp;
	CBCGPButton m_BtnDown;

	CBitmap m_bpUp;
	CBitmap m_bpDown;
	
};
