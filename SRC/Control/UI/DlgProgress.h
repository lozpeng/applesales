#pragma once
#include "afxcmn.h"
#include "GradientProgressCtrl.h"
#include "resource.h"
// CDlgProgress 对话框

class CDlgProgress : public CDialog
{
	//DECLARE_DYNAMIC(CDlgProgress)

public:
	CDlgProgress(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgProgress();

// 对话框数据
	enum { IDD = IDD_PROGRESS_BAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
   void SetProgressRange(long count,bool bPercent);

   void SetPercent(double percent);

   void UpdateSetp();

public:
	CProgressCtrl m_Progress;
	CString m_strTitle;

	int m_nRange;
	
};
