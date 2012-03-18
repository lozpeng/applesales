// PicturePathPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PicturePathPage.h"



// CPicturePathPage 对话框

IMPLEMENT_DYNAMIC(CPicturePathPage, CPropertyPage)

CPicturePathPage::CPicturePathPage()
	: CPropertyPage(CPicturePathPage::IDD)
{

}

CPicturePathPage::~CPicturePathPage()
{
}

void CPicturePathPage::SetElement(Element::CPictureElementPtr pElement)
{
	m_pElement = pElement;
}


void CPicturePathPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPicturePathPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_SET_PATH, &CPicturePathPage::OnBnClickedBtnSetPath)
	ON_EN_CHANGE(IDC_EDIT_PATH, &CPicturePathPage::OnEnChangeEditPath)
END_MESSAGE_MAP()


// CPicturePathPage 消息处理程序
BOOL CPicturePathPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	if (m_pElement == NULL)
		return FALSE;

	GetDlgItem(IDC_EDIT_PATH)->SetWindowText(m_pElement->GetPicturePath().c_str());

	return TRUE;
}

BOOL CPicturePathPage::OnApply()
{
	if(!IsWindow(m_hWnd))
		return FALSE;

	if (m_pElement == NULL)
		return FALSE;

	UpdateData();

	CString cs;
	GetDlgItem(IDC_EDIT_PATH)->GetWindowText(cs);

	m_pElement->SetPicturePath((LPSTR)(LPCSTR)cs);

	SetModified(FALSE);

	return TRUE;
}
void CPicturePathPage::OnBnClickedBtnSetPath()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csFilter =	"BMP(*.bmp)|*.bmp|TIFF(*.tif)|*.tif|TIFF(*.tiff)|*.tiff|JPEG(*.jpg)|*.jpg||";
	CString csFileName(_T("*.BMP"));
	CFileDialog dlg(TRUE, "BMP", csFileName, OFN_HIDEREADONLY, csFilter);

	if( IDOK == dlg.DoModal() )
	{	
		CString csPath = dlg.GetPathName();

		GetDlgItem(IDC_EDIT_PATH)->SetWindowText(csPath);
	}
}

void CPicturePathPage::OnEnChangeEditPath()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	SetModified();
}
