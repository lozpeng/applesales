#pragma once


// CFuzzyKMeanDialog �Ի���

class CFuzzyKMeanDialog : public CDialog
{
	DECLARE_DYNAMIC(CFuzzyKMeanDialog)

public:
	CFuzzyKMeanDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFuzzyKMeanDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_FUZZYKMEAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonInputfile();
	afx_msg void OnBnClickedButtonOutputfile();
	afx_msg void OnBnClickedOk();
	CString m_strInputFile;
	CString m_strOutputFile;
	long m_lClassNum;
	long m_lSampleCount;
	long m_lIterCount;
	double m_dblThreold;
};
