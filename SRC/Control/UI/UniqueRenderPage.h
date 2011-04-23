#pragma once

#include "Resource.h"
#include "IRenderSetting.h"
#include "SymbolPreviewButton.h"
#include "UniqueRender.h"
#include "UniqueRenderList.h"



//代表了唯一值列表中的一类符号
struct SymbolClass
{
	bool operator< (const SymbolClass &other)
	{
		return index<other.index;
	}
    CString strLabel; //类的标记
	Display::ISymbolPtr pSymbol; //符号
	CString strCount; //元素的数目
	int index; //在列表中的位置


};


class CUniqueRenderPage : public CDialog,public IRenderSetting
{
	DECLARE_DYNAMIC(CUniqueRenderPage)

public:
	CUniqueRenderPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUniqueRenderPage();

// 对话框数据
	enum { IDD = IDD_UNIQUE_RENDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual long GetRenderType();

	virtual Carto::IRenderPtr GetRender();

	virtual bool CreateDlg(CWnd *pParent);

	virtual BOOL OnInitDialog();

	//修改选择项
	void ModifySelItem(int index);

	//预览显示指定的符号
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

	//初始化符号列表
	void InitList();
	
    //产生一个随机的符号
	Display::ISymbolPtr  AddUniquerSymbol();

	void FillValues(std::vector<CString> &allValues);

public:
	CUniquerRenderSymbolList m_list;
	CSymbolPreviewButton m_BtnOverview;
	CComboBox m_ComboFields;
	CString m_strHeading;
	Carto::IUniqueRenderPtr m_pRender;

	//唯一值渲染的字段
	CString m_renderField;

	//默认符号
	Display::ISymbolPtr m_pDefaultSymbol;
    //默认标记
	CString m_DefaultLabel;

	SYMBOL_TYPE m_nType;
	
	typedef std::map<CString,SymbolClass> SCMAP;

	//保存了分类信息
	SCMAP m_SymbolMap;
    //保存了每类在列表中的序号
	std::vector<CString> m_IndexList;

	//目前显示在预览框中的要素的值
	CString m_curValue;
	
	CBCGPButton m_BtnUp;
	CBCGPButton m_BtnDown;

	CBitmap m_bpUp;
	CBitmap m_bpDown;
	
};
