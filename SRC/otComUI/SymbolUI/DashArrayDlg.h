#pragma once
#include "DashArrayPropListEx.h"
#include "DashArray.h"
#include "resource.h"
// 破折号数组对话框
class CSymbolEditDlg;
class CDashArrayDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDashArrayDlg)

public:
	CDashArrayDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDashArrayDlg();
	void SetDashArray(Display::CDashArray *dashArray);
	void SetSymbolType(SYMBOL_TYPE type);
	
	void InitList();
	
private:
	void Update();
// 对话框数据
	enum { IDD = IDD_DASHARRAYDLG };
public:
	CDashArrayPropListEx m_wndPropList;					//破折号数组属性列表控件
	CStatic	m_wndPropListLocation;						
	//CtoDashArray m_dashArray;							//用于储存破折号数据的数组
private:
	Display::CDashArray *m_pDashArray;
	Display::CDashArray *m_pDashArrayCopy;
	SYMBOL_TYPE m_enumSymbolType;
	CString m_staticUnit;
	//ItoSymbolPtr m_pSymbol;								//传入的符号
	//ItoConfigItemPtr m_pChild;							//传入的节点
	//CSymbolEditDlg * m_pParentDlg;						//传入的符对话框对象的指针
	

	//CBCGPProp* m_pPropGroup;								//属性列表的项（类似树结点）
	int m_iIndex;										//破折号数组个数
	//CPoint m_cPoint;									//得到对话框位置时用于存储
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedButtonadd();
public:
	afx_msg void OnBnClickedButtonrmv();
public:
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);


	afx_msg void OnBnClickedCancel();
};
