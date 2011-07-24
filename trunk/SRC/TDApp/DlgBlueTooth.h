#pragma once

#include "BlueTooth.h"

// CDlgBlueTooth 对话框

class CDlgBlueTooth : public CDialog
{
	DECLARE_DYNAMIC(CDlgBlueTooth)

public:
	CDlgBlueTooth(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgBlueTooth();

// 对话框数据
	enum { IDD = IDD_BLUETOOTH_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSelsfile();
	afx_msg void OnBnClickedTestConnect();
	afx_msg void OnBnClickedOk();
public:
	CString m_BluetoothName;
	CString m_strFile;

	BlueToothComm::CBlueTooth m_bluetooth;
	
};
