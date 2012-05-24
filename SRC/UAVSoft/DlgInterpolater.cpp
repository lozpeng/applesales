// DlgInterpolater.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UAVSoft.h"
#include "DlgInterpolater.h"
#include "InverseDist.h"
#include <string>
#include <fstream>
#include <sstream>
#include "CSpreadSheet.h"
#include "IWorkspace.h"
#include "ShapefileWorkspaceFactory.h"
using namespace std;
// CDlgInterpolater �Ի���

IMPLEMENT_DYNAMIC(CDlgInterpolater, CDialog)

CDlgInterpolater::CDlgInterpolater(CWnd* pParent /*=NULL*/)
: CDialog(CDlgInterpolater::IDD, pParent)
, m_strInputFile(_T(""))
, m_strOutputFile(_T(""))
, m_dbCellSize(0.00002)
, m_dbSearchRadius(0.1)
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
	CString strFilter = "Excel Files(*.xlsx)|*.xlsx|Ascii Files(*.txt)|*.txt|All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, "Data Files(*.xlsx)", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if(dlg.DoModal() == IDOK)
	{
		m_strInputFile = dlg.GetPathName();
	}

	UpdateData(FALSE);
}

void CDlgInterpolater::Excel2Shp(std::string filename,std::vector<double> &dxs, std::vector<double> &dys, 
								 std::vector<double> &dzs)
{
	std::string path =filename;
	//�õ��ļ�·��
	path =path.substr(0,path.rfind('\\'));

	Geodatabase::IWorkspace *pWorkspace =CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(filename.c_str());
	if(!pWorkspace)
	{
		return;
	}

	Geodatabase::FeatureClassDef fdef;
	fdef.hasz =false;

	fdef.lshptype = GEOMETRY::geom::GEOS_POINT;

	const char* szFieldname="SO2";

	Geodatabase::IFeatureClassPtr pFeatureClass = NULL;
	pFeatureClass = pWorkspace->OpenFeatureClass(filename.c_str());
	if(pFeatureClass == NULL)
	{
		Geodatabase::CField *pField =new Geodatabase::CField();
		pField->SetType(Geodatabase::BDT_DOUBLE);
		pField->SetName(szFieldname);
		pField->SetLength(12);
		fdef.FieldsDef.push_back(Geodatabase::CFieldPtr(pField));

		pFeatureClass =pWorkspace->CreateFeatureClass(filename.c_str(),fdef);
	}

	if(!pFeatureClass)
	{
		return;
	}

	//��ʼ�༭
	bool srcState = pWorkspace->IsEditing();
	if(srcState== false)
		pWorkspace->StartEdit();

	pWorkspace->StartEditOperation();

	Geodatabase::CFeaturePtr pFeature;


	GEOMETRY::geom::Geometry* pGeometry =NULL;

	for (size_t i=0;i<dzs.size();i++)
	{

		//����һ���µ�Ҫ��
		pFeature =pFeatureClass->CreateFeature();
		//������
		pGeometry =(Geometry*)GeometryFactory::getDefaultInstance()->createPoint();

		GEOMETRY::geom::Coordinate coord;
		coord.x = dxs[i];
		coord.y = dys[i];
		pGeometry->AddPoint(coord);

		pFeature->SetShape( pGeometry);

		int lfieldindex = pFeatureClass->FindField(szFieldname);

		//�ύҪ��
		pFeatureClass->AddFeature(pFeature.get());

		//pFeature->GetValue(lfieldindex).SetDouble(double(dzs[i]));
		//pFeature->Update();


	}

	pWorkspace->StopEditOperation();
	if(srcState == false)
		pWorkspace->StopEdit(true);
}

#include "MainFrm.h"
#include "UAVSoftDoc.h"
#include "IMapCtrl.h"
void CDlgInterpolater::OnBnClickedOk()
{
	this->UpdateData();

	using namespace std;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_dbSearchRadius<=0||m_dbCellSize<=0||m_strInputFile.GetLength()<1||m_strOutputFile.GetLength()<1)
	{
		MessageBox("��������Ϊ�գ�������!","��ʾ",MB_OK);
		return;
	}

	//��������
	locale oldloc = locale::global(locale(""));

	double x, y, z;
	std::vector<double> dxs,dys,dzs;
	
	CString tempString = PathFindExtension(m_strInputFile);
	tempString.MakeLower();
	if (tempString == ".xls"||tempString == ".xlsx") 
	{
		CSpreadSheet sheet(m_strInputFile,"sheet1");  //�򿪹������еĹ�����sheet1!
		
		CStringArray pArray;
		CString pVal;

		//��ȡ����
		sheet.ReadColumn(pArray,'W'-'A'+1);
		int lCnt = pArray.GetSize();
		for (int k=1;k< lCnt;k++)
		{
			pVal = pArray.GetAt(k);
			x= atof(pVal);

			//excel��ȡ��ĩβ�д��������⣬��ʱx���ж�
			int flag=(int)x;
			if(flag == 0)
			{
				lCnt = k;
				break;
			}

			dxs.push_back(x);
		}
		//��ȡγ��
		sheet.ReadColumn(pArray,'X'-'A'+1);
		for (int k=1;k< lCnt;k++)
		{
			pVal = pArray.GetAt(k);
			y= atof(pVal);
			dys.push_back(y);
		}
		
		//���ݶ�ȡ(��������)
		sheet.ReadColumn(pArray,'G'-'A'+1);
		for (int k=1;k< lCnt;k++)
		{
			pVal = pArray.GetAt(k);
			z= atof(pVal);
			dzs.push_back(z);
		}

	}
	else if (tempString == ".txt") 
	{
		std::string filename= m_strInputFile;

		std::ifstream in(filename.c_str());
		if(!in) {
			::AfxMessageBox(_T("��txt�ļ�ʧ��..."));
			return;
		}

		while(!in.eof()) {
			std::string line;
			getline(in, line);
			istringstream iss(line);
			iss >> x >> y >> z;
			dxs.push_back(x);
			dys.push_back(y);
			dzs.push_back(z);

		}
	}


	//����shp�ļ�
	std::string strShpFile =m_strOutputFile.Left(m_strOutputFile.GetLength()-4);
	strShpFile +=".shp";
	this->Excel2Shp(strShpFile,dxs,dys,dzs);

	//shp���ݼ���

	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CUAVSoftDoc* pDoc = (CUAVSoftDoc*)pMainFrm->GetActiveDocument();
	pDoc->LoadShpFile(strShpFile.c_str());
	pDoc->GetLinkMapCtrl()->UpdateControl(drawAll);

	//���ò�ֵ����
	if(!ImageProcess::CInverseDist::Run(dxs,dys,dzs,m_dbCellSize,m_dbCellSize,m_dbSearchRadius,m_strOutputFile))
	{
		MessageBox("����ʧ��");

	}
	else
	{
		MessageBox("����ɹ�");
	}

	pDoc->LoadImageFile(m_strOutputFile);
	pDoc->GetLinkMapCtrl()->UpdateControl(drawAll);

	locale::global(oldloc);
	OnOK();
}
