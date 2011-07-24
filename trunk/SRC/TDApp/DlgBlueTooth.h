#pragma once

#include "BlueTooth.h"

// CDlgBlueTooth �Ի���

class CDlgBlueTooth : public CDialog
{
	DECLARE_DYNAMIC(CDlgBlueTooth)

public:
	CDlgBlueTooth(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBlueTooth();

// �Ի�������
	enum { IDD = IDD_BLUETOOTH_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
