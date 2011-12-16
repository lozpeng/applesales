// StartUAVDlg.h : ͷ�ļ�
//

#pragma once

#include "PicContainer.h"
#include "ButtonContainer.h"
// CStartUAVDlg �Ի���
class CStartUAVDlg : public CDialog
{
// ����
public:
	CStartUAVDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_STARTUAV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
