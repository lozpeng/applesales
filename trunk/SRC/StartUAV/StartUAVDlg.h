// StartUAVDlg.h : 头文件
//

#pragma once

#include "PicContainer.h"
#include "ButtonContainer.h"
// CStartUAVDlg 对话框
class CStartUAVDlg : public CDialog
{
// 构造
public:
	CStartUAVDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_STARTUAV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	void InitXML();

	CString GetExePath();

	void CreateButtons();
public:
	CStatic m_picLoc;
	CPicContainer m_BgContainer;
	

	CString m_strAppName;

	CToolTipCtrl m_ToolTip;

	std::vector<stProduct> m_ButtonInfo;
	std::vector<CTransButton*>  m_buttons;
	std::vector<stButIDandName> m_ButtonIDandName;

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
