#pragma once


// CDlgAbout �Ի���

class CDlgAbout : public CDialog
{
	DECLARE_DYNAMIC(CDlgAbout)

public:
	CDlgAbout(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAbout();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX_OTMAPTREECONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};