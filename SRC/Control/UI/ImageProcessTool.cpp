#include "stdafx.h"
#include "ImageProcessTool.h"
#include "DllResource.h"
#include "DlgChangeDetect.h"
#include "ImgChangeDetect.h"
#include "IDocument.h"
namespace Control
{

void CImageProcessTool::ShowImgChangeDetectDlg()
{
     CDllResource hdll;
	 CDlgChangeDetect dlg;
	 if(dlg.DoModal()==IDOK)
	 {
		 ImageProcess::ImgChangeDetect detect;
		 bool bsuc =detect.RelativeDetect(dlg.m_strSrc,dlg.m_strDest,dlg.m_strResult,dlg.m_nSize,dlg.m_dCor);
		 if(bsuc)
		 {
             AfxMessageBox("ºÏ≤‚≥…π¶");
			 if(dlg.m_bLoadShp)
			 {
                 Framework::IDocument *pDoc =(Framework::IDocument*)Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppDocument);
				 pDoc->LoadShpFile(dlg.m_strResult);
			 }
		 }
		 else
		 {
			 AfxMessageBox("ºÏ≤‚ ß∞‹");
		 }
	 }
}

}