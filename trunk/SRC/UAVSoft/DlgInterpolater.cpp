// DlgInterpolater.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UAVSoft.h"
#include "DlgInterpolater.h"
#include "InverseDist.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
// CDlgInterpolater �Ի���

IMPLEMENT_DYNAMIC(CDlgInterpolater, CDialog)

CDlgInterpolater::CDlgInterpolater(CWnd* pParent /*=NULL*/)
: CDialog(CDlgInterpolater::IDD, pParent)
, m_strInputFile(_T(""))
, m_strOutputFile(_T(""))
, m_dbCellSize(0.5)
, m_dbSearchRadius(100)
{

}

CDlgInterpolater::~CDlgInterpolater()
{
}

void CDlgInterpolater::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUTFILE, m_strInputFile);
	DDX_Text(pDX, IDC_EDIT_OUTPUTFILE, m_strOutputFile);
	DDX_Text(pDX, IDC_EDIT_CELLSIZE, m_dbCellSize);
	DDX_Text(pDX, IDC_EDIT_SEARCHRADIUS, m_dbSearchRadius);
}


BEGIN_MESSAGE_MAP(CDlgInterpolater, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUTFILE, &CDlgInterpolater::OnBnClickedButtonOutputfile)
	ON_BN_CLICKED(IDC_BUTTON_INPUTFILE, &CDlgInterpolater::OnBnClickedButtonInputfile)
	ON_BN_CLICKED(IDOK, &CDlgInterpolater::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgInterpolater ��Ϣ�������

void CDlgInterpolater::OnBnClickedButtonOutputfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString strFilter = "Image Files(*.tif)|*.tif|All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, "Image Files(*.tif)", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if(dlg.DoModal() == IDOK)
	{
		m_strOutputFile = dlg.GetPathName();
	}
	UpdateData(FALSE);
}

void CDlgInterpolater::OnBnClickedButtonInputfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFilter = "Ascii Files(*.txt)|*.txt|All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, "Ascii Files(*.txt)", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if(dlg.DoModal() == IDOK)
	{
		m_strInputFile = dlg.GetPathName();
	}

	UpdateData(FALSE);
}

void CDlgInterpolater::OnBnClickedOk()
{
	using namespace std;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_dbSearchRadius<=0||m_dbCellSize<=0||m_strInputFile.GetLength()<1||m_strOutputFile.GetLength()<1)
	{
		MessageBox("��������Ϊ�գ�������!","��ʾ",MB_OK);
		return;
	}

	std::string filename= m_strInputFile;

	//��������
	locale oldloc = locale::global(locale(""));
	std::ifstream in(filename.c_str());
	if(!in) {
		::AfxMessageBox(_T("��txt�ļ�ʧ��..."));
		return;
	}

	double x, y, z;
    std::vector<double> dxs,dys,dzs;
	//m_vecPoints.clear();
	while(!in.eof()) {
		std::string line;
		getline(in, line);
		istringstream iss(line);
		iss >> x >> y >> z;
		//m_vecPoints.push_back(Point3D(x, y, z));
		dxs.push_back(x);
		dys.push_back(y);
		dzs.push_back(z);

	}
	
	
	//���ò�ֵ����
	if(!ImageProcess::CInverseDist::Run(dxs,dys,dzs,m_dbCellSize,m_dbCellSize,m_dbSearchRadius,m_strOutputFile))
	{
        MessageBox("����ʧ��");
		
	}
	else
	{
		MessageBox("����ɹ�");
	}


	locale::global(oldloc);
	OnOK();
}
