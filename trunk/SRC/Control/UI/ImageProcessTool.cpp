#include "stdafx.h"
#include "ImageProcessTool.h"
#include "DllResource.h"
#include "DlgChangeDetect.h"
namespace Control
{

void CImageProcessTool::ShowImgChangeDetectDlg()
{
     CDllResource hdll;
	 CDlgChangeDetect dlg;
	 dlg.DoModal();
}

}