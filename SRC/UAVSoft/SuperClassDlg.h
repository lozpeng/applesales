#pragma once


// CSuperClassDlg �Ի���

class CSuperClassDlg : public CDialog
{
	DECLARE_DYNAMIC(CSuperClassDlg)

public:
	CSuperClassDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSuperClassDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SUPERCLASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
