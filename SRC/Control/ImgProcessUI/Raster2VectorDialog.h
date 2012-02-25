#pragma once


// CRaster2VectorDialog 对话框

class CRaster2VectorDialog : public CDialog
{
	DECLARE_DYNAMIC(CRaster2VectorDialog)

public:
	CRaster2VectorDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRaster2VectorDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_RASTER2VECTOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonInputfile();
	afx_msg void OnBnClickedButtonOutputfile();
	CString m_strInputFile;
	CString m_strOutputFile;
	int m_classValue;
	afx_msg void OnBnClickedOk2();
	long m_lThres;
};
