// PicturePathPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PicturePathPage.h"



// CPicturePathPage �Ի���

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


// CPicturePathPage ��Ϣ�������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetModified();
}
