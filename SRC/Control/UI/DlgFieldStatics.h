#pragma once
#include "afxwin.h"
#include "resource.h"
#include "CommonData.h"
// CDlgFieldStatics 对话框


class CDlgFieldStatics : public CDialog
{
	DECLARE_DYNAMIC(CDlgFieldStatics)

public:
	CDlgFieldStatics(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgFieldStatics();

// 对话框数据
	enum { IDD = IDD_FIELD_STASTIC };

public:
	//初始化计算字段值集合
	void InitFieldsValues( std::vector<LP_CAL_FIELDVALUE> &vecFields );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();

	afx_msg void OnCbnSelchangeCmbSelfield();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnOutput();

protected:
	//统计
	BOOL Statics( const char *szFieldName );

	//输出
	void OutPutResult( const char *szType, 
					long nCount,
					double dMinimum, 
					double dMaxMum,
					double dSum,
					double dMean,
					double dStdDeviation );

	//获得计算的数组
	void GetCalculateValues( const char *szFieldName );

private:
	//数组
	std::vector<LP_CAL_FIELDVALUE> m_vecCalFields;

	//计算的数组
	std::vector<double> m_vecCalValues;
	
	//是否只计算选中的行
	BOOL  m_bOnlyCalSel;

protected:
	CComboBox m_cmbField;
	CString m_szOutputStatics;
	CString m_szField;		
public:
	afx_msg void OnBnClickedChkSel();
};
