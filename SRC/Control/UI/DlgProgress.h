#pragma once
#include "afxcmn.h"
#include "GradientProgressCtrl.h"
#include "resource.h"
// CDlgProgress �Ի���

class CDlgProgress : public CDialog
{
	//DECLARE_DYNAMIC(CDlgProgress)

public:
	CDlgProgress(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgProgress();

// �Ի�������
	enum { IDD = IDD_PROGRESS_BAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
