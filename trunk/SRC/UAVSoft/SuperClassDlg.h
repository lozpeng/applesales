#pragma once


// CSuperClassDlg 对话框

class CSuperClassDlg : public CDialog
{
	DECLARE_DYNAMIC(CSuperClassDlg)

public:
	CSuperClassDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSuperClassDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SUPERCLASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
