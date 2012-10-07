#pragma once
#include "afxwin.h"


// CDlgFieldCalculate 对话框

class CDlgFieldCalculate : public CDialog
{
	DECLARE_DYNAMIC(CDlgFieldCalculate)

public:
	CDlgFieldCalculate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgFieldCalculate();

// 对话框数据
	enum { IDD = IDD_FIELD_CALCULATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();

	afx_msg void OnLbnDblclkLstField();
	afx_msg void OnLbnDblclkLstOperate();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnSubstract();
	afx_msg void OnBnClickedBtnMultiply();
	afx_msg void OnBnClickedBtnDivide();
	afx_msg void OnBnClickedBtnEqual();
	afx_msg void OnBnClickedBtnMi();

public:
	void Init( int iFieldIndex, 
		std::vector<long> &vSelFeatures, 
		std::vector<long> &vAllFeatures,
		Geodatabase::IFeatureClassPtr pFeatureClass );
	
private:
	//尾部添加括号
	void AddBackBracket( CString &szAdded );
	//添加操作符
	void AddOprator( LPCTSTR szOp );
	
	//获得字符串
	CString GetMathExpr();
	//把带字段变量的数学表达式解析成数字形式的表达式
	void MathExpreParser( CString &szMathExpr, Geodatabase::CFeaturePtr pFeature );
	//计算
	void Calculate();

	//加载函数列表
	void ReLoadFuntionList();

protected:
	CListBox m_LstFields;
	CListBox m_lstFunction;
	CEdit m_edtMathExpr;
	int m_iType;
	BOOL m_bOnlySel;
	CString m_szMathExpr;

	//操作的FeatureClass
	Geodatabase::IFeatureClassPtr m_pFeatureClass;

private:
	//表达式选择位置 
	int m_iStart;
	int m_iEnd;
	
	//选择集
	std::vector<int> m_vSelFeatureIndex;

	//全部记录索引
	std::vector<int> m_vAllFieldsIndex;

	//计算字段
	int m_iCalFieldIndex;

public:
	afx_msg void OnBnClickedRadioNum();
	afx_msg void OnBnClickedRadioChar();
	afx_msg void OnBnClickedRadioTime();
	afx_msg void OnBnClickedOk();
};
