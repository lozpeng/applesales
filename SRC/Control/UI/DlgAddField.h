#pragma once
#include "afxwin.h"
#include "Field.h"


// CDlgAddField 对话框

class CDlgAddField : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddField)

public:
	CDlgAddField(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAddField();

// 对话框数据
	enum { IDD = IDD_ADD_FIELD };

public:
	CString GetFieldName(){ return m_strName; }

	Geodatabase::FIELD_TYPE GetFieldType(){ return m_fieldType; }

	long GetLength() { return m_nLength; }

	long GetPrecision() { return m_nPrecision; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	//初始化类型列表
	void InitFieldTypes();
	
	virtual BOOL OnInitDialog();
	
	afx_msg void OnEnChangeEdtName();
	afx_msg void OnCbnSelchangeCmbType();
	
private:
	//控件 变量 
	CString m_strName;
	CComboBox m_cmbType;
	long m_nLength;
	long m_nPrecision;

	//字段类型
	Geodatabase::FIELD_TYPE m_fieldType;
};
