#pragma once


// CRaster2VectorDialog �Ի���

class CRaster2VectorDialog : public CDialog
{
	DECLARE_DYNAMIC(CRaster2VectorDialog)

public:
	CRaster2VectorDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRaster2VectorDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_RASTER2VECTOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
