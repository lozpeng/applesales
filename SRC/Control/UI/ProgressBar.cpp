#include "StdAfx.h"
#include "ProgressBar.h"
#include "DllResource.h"
#include "DlgProgress.h"

namespace Control
{

CProgressBar::CProgressBar(void)
{
    m_pBar =NULL;
}

CProgressBar::~CProgressBar(void)
{
   if(m_pBar)
   {
	   delete (CDlgProgress*)m_pBar;
   }
}

bool CProgressBar::Create(const char *title, SYSTEM::IProgress::ProgressMode mode, long ltotal)
{
    CDllResource hdll;
    CDlgProgress *pBar =new CDlgProgress();
	BOOL bSuc =pBar->Create(IDD_PROGRESS_BAR,CWnd::GetDesktopWindow());
    
	if(mode==SYSTEM::IProgress::Percent)
	{
		pBar->SetProgressRange(100,true);
	}
	else
	{
		pBar->SetProgressRange(ltotal,false);
	}
	
	pBar->ShowWindow(SW_SHOW);
	m_pBar =pBar;
	return bSuc;

}

void CProgressBar::Close()
{
	if(m_pBar)
	{
        CDlgProgress *pBar =(CDlgProgress*)m_pBar;
		delete pBar;
		m_pBar =NULL;
	}
}

static void HandleMessages(void)
{
	MSG msg;

	while (PeekMessage(&msg,        /* message structure            */
		(HWND)NULL,   /* handle of window receiving the message */
		(UINT)0,      /* lowest message to examine          */
		(UINT)0,      /* highest message to examine      */
		PM_REMOVE))
	{
		TranslateMessage(&msg);    /* Translates virtual key codes       */
		DispatchMessage(&msg);     /* Dispatches message to window       */
	}
}

void CProgressBar::UpdateProgress(const char *message)
{
	if(m_pBar)
	{
		CDlgProgress *pBar =(CDlgProgress*)m_pBar;
		pBar->UpdateSetp();
		HandleMessages();
	}
}


void CProgressBar::UpdateProgress(const char *message, double percent)
{
	if(m_pBar)
	{
		CDlgProgress *pBar =(CDlgProgress*)m_pBar;
		pBar->SetPercent(percent);
	}
}






}
