#pragma once
#include "afxwin.h"
#include <map>

// CDlgInterpolater �Ի���

class CDlgInterpolater : public CDialog
{
	DECLARE_DYNAMIC(CDlgInterpolater)

public:
	CDlgInterpolater(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInterpolater();

// �Ի�������
	enum { IDD = IDD_DIG_Interpolater };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	//�����ֵ�����ش�����Ϣ
	CString Process();

private:
	CComboBox m_comboGas;
	//������к������Ƶ�map
	std::map<CString,short> m_gascolmap;
	CString m_gasName;
};
