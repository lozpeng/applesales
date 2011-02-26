#include "stdafx.h"
#include "dlgprogress.h"


//IMPLEMENT_DYNCREATE(CDlgProgress, CDialog)

CDlgProgress::CDlgProgress(CWnd* pParent /*=NULL*/)
: CDialog(CDlgProgress::IDD, pParent)
{
   m_nRange =0;
}

CDlgProgress::~CDlgProgress()
{

}

void CDlgProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCTestProgressBarDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
}

BEGIN_MESSAGE_MAP(CDlgProgress, CDialog)
	

END_MESSAGE_MAP()

void CDlgProgress::SetProgressRange(long count, bool bPercent)
{
	
    m_nRange =count;
	m_Progress.SetRange(0,m_nRange);
	if(!bPercent)
	{
		m_Progress.SetStep(1);
	}
	
}

void CDlgProgress::SetPercent(double percent)
{
    int pos =m_nRange*percent;

	m_Progress.SetPos(pos);
}

void CDlgProgress::UpdateSetp()
{
	m_Progress.StepIt();
}