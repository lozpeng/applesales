#pragma once
#include "afxwin.h"
#include <map>

// CDlgInterpolater 对话框

class CDlgInterpolater : public CDialog
{
	DECLARE_DYNAMIC(CDlgInterpolater)

public:
	CDlgInterpolater(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgInterpolater();

// 对话框数据
	enum { IDD = IDD_DIG_Interpolater };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOutputfile();
	CString m_strInputFile;
	CString m_strOutputFile;
	afx_msg void OnBnClickedButtonInputfile();
	double m_dbCellSize;
	double m_dbSearchRadius;
	afx_msg void OnBnClickedOk();

	void Excel2Shp(std::string filename,std::vector<double> &dxs, std::vector<double> &dys, 
		std::vector<double> &dzs);

private:
	//处理插值，返回错误信息
	CString Process();

private:
	CComboBox m_comboGas;
	//气体的列号与名称的map
	std::map<CString,short> m_gascolmap;
	CString m_gasName;
};
