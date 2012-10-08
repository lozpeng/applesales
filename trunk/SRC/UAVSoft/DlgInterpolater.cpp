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
, m_gasName(_T(""))
{
	m_gascolmap["��������"]='F'-'A'+1;
	m_gascolmap["��������"]='I'-'A'+1;
	m_gascolmap["һ������"]='L'-'A'+1;
	m_gascolmap["����"]='O'-'A'+1;
	m_gascolmap["һ����̼"]='R'-'A'+1;
	m_gascolmap["����"]='U'-'A'+1;


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
	DDX_Control(pDX, IDC_GAS_TYPE, m_comboGas);
	DDX_CBString(pDX, IDC_GAS_TYPE, m_gasName);
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
		pField->SetType(Geodatabase::FTYPE_DOUBLE);
		pField->SetName(szFieldname);
		pField->SetLength(12);
		pField->SetPrecision(5);
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

	for (size_t i=0;i<dxs.size();i++)
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

		pFeature->GetValue(lfieldindex).SetDouble(dzs[i]);
		//�ύҪ��
		pFeatureClass->AddFeature(pFeature.get());

	}

	pWorkspace->StopEditOperation();
	if(srcState == false)
		pWorkspace->StopEdit(true);
}

#include "MainFrm.h"
#include "UAVSoftDoc.h"
#include "IMapCtrl.h"
#include "ProgressBar.h"

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
	if(CB_ERR==m_comboGas.GetCurSel())
	{
		MessageBox("��ѡ��һ����������!","��ʾ",MB_OK);
		return;
	}

	CString error = Process();
	if(!error.IsEmpty())
	{
       MessageBox(error);
	}
	OnOK();
}

CString CDlgInterpolater::Process()
{
	//��������
	locale oldloc = locale::global(locale(""));

	double x, y, z;
	std::vector<double> dxs,dys,dzs,dzdata;

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

		std::map<CString,short>::iterator iter = m_gascolmap.find(m_gasName);
		if(iter==m_gascolmap.end())
		{
			return "û���ҵ���������";
		}

		int nStartFlag = iter->second;
		sheet.ReadColumn(pArray,nStartFlag);
		for (int k=1;k< lCnt;k++)
		{
			pVal = pArray.GetAt(k);
			z= atof(pVal);
			dzdata.push_back(z);
		}
		

		////���ݶ�ȡ(��������)
		//int nStartFlag = 'F'-'A'+1;
		//sheet.ReadColumn(pArray,nStartFlag);
		//for (int k=1;k< lCnt;k++)
		//{
		//	pVal = pArray.GetAt(k);
		//	z= atof(pVal);
		//	dzso2.push_back(z);
		//}

		//nStartFlag+=6;
		//sheet.ReadColumn(pArray,nStartFlag);
		//for (int k=1;k< lCnt;k++)
		//{
		//	pVal = pArray.GetAt(k);
		//	z= atof(pVal);
		//	dzno.push_back(z);
		//}

		//nStartFlag+=3;
		//sheet.ReadColumn(pArray,nStartFlag);
		//for (int k=1;k< lCnt;k++)
		//{
		//	pVal = pArray.GetAt(k);
		//	z= atof(pVal);
		//	dzh2s.push_back(z);
		//}
		//nStartFlag+=3;
		//sheet.ReadColumn(pArray,nStartFlag);
		//for (int k=1;k< lCnt;k++)
		//{
		//	pVal = pArray.GetAt(k);
		//	z= atof(pVal);
		//	dzco.push_back(z);
		//}

	}
	else if (tempString == ".txt") 
	{
		std::string filename= m_strInputFile;

		std::ifstream in(filename.c_str());
		if(!in) {
			//::AfxMessageBox(_T("��txt�ļ�ʧ��..."));
			return "��txt�ļ�ʧ��...";
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
	this->Excel2Shp(strShpFile,dxs,dys,dzdata);


	CMainFrame* pMainFrm = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	CUAVSoftDoc* pDoc = (CUAVSoftDoc*)pMainFrm->GetActiveDocument();

	CString retFile=m_strOutputFile;
	int extFlag = m_strOutputFile.Find(".tif",0);
	//retFile.Insert(extFlag,"_so2");

	Control::CProgressBar progress;
	const char* szProName="�������ݲ�ֵ�У���ȴ�...";
	//���ò�ֵ����
	if(!ImageProcess::CInverseDist::Run(dxs,dys,dzdata,m_dbCellSize,m_dbCellSize,m_dbSearchRadius,retFile,&progress,szProName))
	{
		MessageBox("����ʧ��");

	}
	pDoc->LoadImageFile(retFile);



	//szProName="NO���ݲ�ֵ�У���ȴ�...";
	//retFile=m_strOutputFile;
	//retFile.Insert(extFlag,"_no");
	////���ò�ֵ����
	//if(!ImageProcess::CInverseDist::Run(dxs,dys,dzno,m_dbCellSize,m_dbCellSize,m_dbSearchRadius,retFile,&progress,szProName))
	//{
	//	MessageBox("����ʧ��");

	//}
	//pDoc->LoadImageFile(retFile);


	////
	//szProName="H2S���ݲ�ֵ�У���ȴ�...";
	//retFile=m_strOutputFile;
	//retFile.Insert(extFlag,"_h2s");
	////���ò�ֵ����
	//if(!ImageProcess::CInverseDist::Run(dxs,dys,dzh2s,m_dbCellSize,m_dbCellSize,m_dbSearchRadius,retFile,&progress,szProName))
	//{
	//	MessageBox("����ʧ��");

	//}

	//pDoc->LoadImageFile(retFile);

	////
	//szProName="CO���ݲ�ֵ�У���ȴ�...";
	//retFile=m_strOutputFile;
	//retFile.Insert(extFlag,"_co");
	////���ò�ֵ����
	//if(!ImageProcess::CInverseDist::Run(dxs,dys,dzco,m_dbCellSize,m_dbCellSize,m_dbSearchRadius,retFile,&progress,szProName))
	//{
	//	MessageBox("����ʧ��");

	//}
	//else
	//{
	//	MessageBox("����ɹ�");
	//}
	//pDoc->LoadImageFile(retFile);



	////����shp�ļ�
	//std::string strShpFile =m_strOutputFile.Left(m_strOutputFile.GetLength()-4);
	//strShpFile +=".shp";
	//this->Excel2Shp(strShpFile,dxs,dys,dzs);

	//shp���ݼ���

	pDoc->LoadShpFile(strShpFile.c_str());
	pDoc->GetLinkMapCtrl()->UpdateControl(drawAll);

	pDoc->GetLinkMapCtrl()->UpdateControl(drawAll);

	locale::global(oldloc);
	return "";
}
