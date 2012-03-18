// DlgRasGeoProperty.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgRasGeoProperty.h"
#include "IRasterDataset.h"
//#include "TI_Project.h"

//static BOOL DumpProjcs(STPROJCS* pstProjcs, CString &csDump, BOOL bDumpProj = TRUE)
//{
//	csDump = _T("");
//	CString csTemp;
//
//	if((1 == pstProjcs->bProj) && (bDumpProj))
//	{
//		csTemp.Format("Name: %s\r\n",pstProjcs->name);
//
//		csDump = csTemp;
//		csDump += "Alias: \r\n";
//		csDump += "Abbreviation: \r\n";
//		csDump += "Remarks: \r\n";
//
//		csTemp.Format("Projection: %s\r\n", pstProjcs->project.name);
//		csDump += csTemp;
//
//		csTemp.Format("Linear Unit: %s(%lf)\r\n\r\n", pstProjcs->unit.name, pstProjcs->unit.value);
//		csDump += csTemp;
//
//		csDump += "Geographic Coordinate System: \r\n\r\n";
//	}
//
//	double Semiminor = 0.0, ToWGS = 0.0;
//
//	csTemp.Format("Name: %s\r\n",pstProjcs->geogcs.name);
//	csDump += csTemp;
//	csDump += "Alias: \r\n";
//	csDump += "Abbreviation: \r\n";
//	csDump += "Remarks: \r\n";
//	csDump += "Angular Unit: ";
//
//	csTemp.Format("%s",pstProjcs->geogcs.unit.name);
//	csDump += csTemp + " (";
//
//	csTemp.Format("%.16f",pstProjcs->geogcs.unit.value);
//	csDump += csTemp + ")\r\n  Prime Meridian: ";
//
//	csTemp.Format("%s",pstProjcs->geogcs.primem.name);
//	csDump += csTemp + ": ";
//	csTemp.Format("%f",pstProjcs->geogcs.primem.value);
//	csDump += csTemp + "\r\n  Datum: ";
//	csTemp.Format("%s",pstProjcs->geogcs.datum.name);
//	csDump += csTemp + "\r\n    Spheroid: ";
//	csTemp.Format("%s",pstProjcs->geogcs.datum.spheroid.name);
//	csDump += csTemp + "\r\n      Semimajor Axis: ";
//	csTemp.Format("%.12f",pstProjcs->geogcs.datum.spheroid.semimajor);
//	if(pstProjcs->geogcs.datum.spheroid.InEcc == 0)
//		return FALSE;
//	Semiminor = pstProjcs->geogcs.datum.spheroid.semimajor *
//		pow((pstProjcs->geogcs.datum.spheroid.InEcc - 1)/ pstProjcs->geogcs.datum.spheroid.InEcc,0.5);
//	csDump += csTemp + "\r\n      Semiminor Axis: ";
//	csTemp.Format("%.12f",Semiminor);
//	csDump += csTemp + "\r\n      Inverse Flattening: ";
//	csTemp.Format("%f",pstProjcs->geogcs.datum.spheroid.InEcc);
//	csDump += csTemp;
//	int j;
//	for(j=0; j<7; j++)
//	{
//		ToWGS += pstProjcs->geogcs.datum.ToWGS84[j];
//	}
//	if(fabs(ToWGS) > 0.0000001)
//	{			
//		csDump += "\r\n      ToWGS84: ";
//		for(j=0; j<6; j++)
//		{
//			csTemp.Format("%.3f",pstProjcs->geogcs.datum.ToWGS84[j]);
//			csDump += csTemp + ", ";
//		}
//		csTemp.Format("%.3f",pstProjcs->geogcs.datum.ToWGS84[6]);
//		csDump += csTemp;
//	}
//	return TRUE;
//}



// CDlgRasGeoProperty 对话框

IMPLEMENT_DYNAMIC(CDlgRasGeoProperty, CPropertyPage)

CDlgRasGeoProperty::CDlgRasGeoProperty()
	: CPropertyPage(CDlgRasGeoProperty::IDD)
{
	m_csCellSizeX = _T("");
	m_csCellSizeY = _T("");
	m_csProjName = _T("");
	m_csWktDetail = _T("");
	mm_csWkt = _T("");
	m_dblDRx = 0.0;
	m_dblDRy = 0.0;
	m_dblULx = 0.0;
	m_dblULy = 0.0;
	m_pLayer = NULL;
	mm_bParseOk=FALSE;

}

CDlgRasGeoProperty::~CDlgRasGeoProperty()
{
}

void CDlgRasGeoProperty::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	/*DDX_Text(pDX,IDC_X_DISTING,m_csCellSizeX);
	DDX_Text(pDX,IDC_Y_DISTING,m_csCellSizeY);*/
	DDX_Text(pDX,IDC_RIGHTBUTTON_X,m_dblDRx);
	DDX_Text(pDX,IDC_RIGHTBUTTON_Y,m_dblDRy);
	DDX_Text(pDX,IDC_LEFTTOP_X,m_dblULx);
	DDX_Text(pDX,IDC_LEFTTOP_Y,m_dblULy);
	//DDX_Text(pDX,IDC_EDIT_NAME, m_csProjName);
	DDX_Text(pDX,IDC_SHOWPROJECT_INF, m_csWktDetail);
}


BEGIN_MESSAGE_MAP(CDlgRasGeoProperty, CPropertyPage)
	ON_BN_CLICKED(IDC_PROJECTTION, &CDlgRasGeoProperty::OnBnClickedProjecttion)
END_MESSAGE_MAP()


// CDlgRasGeoProperty 消息处理程序

void CDlgRasGeoProperty::OnBnClickedProjecttion()
{
	/*if (NULL == m_pLayer)
		return;	

	Geodatabase::IDataObjectPtr pDataObject = m_pLayer->GetDataObject();


	Geodatabase::IRasterDataset *pRasterObj = dynamic_cast<Geodatabase::IRasterDataset*>(pDataObject.get());

	if(!pRasterObj)
		return;


	char *pszWktOut = new char[2048];
	memset(pszWktOut, 0, 2048);

	std::string  strWktIn;
	strWktIn = pRasterObj->GetProjection();

   if(strWktIn.length() == 0)
   {
	   delete[] pszWktOut;
	   MessageBox("该影像没有投影信息！");
	   return;
   }


	if (IPE_GUISelectWKT(strWktIn.c_str(), pszWktOut) && pRasterObj->IsWritable())
	   pRasterObj->SetProjection(pszWktOut);

	delete[] pszWktOut;*/
}

BOOL CDlgRasGeoProperty::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	if (NULL == m_pLayer)
		return FALSE;	

	Geodatabase::IGeodataObjectPtr pDataObject = m_pLayer->GetDataObject();


	Geodatabase::IRasterDataset *pRasterObj = dynamic_cast<Geodatabase::IRasterDataset*>(pDataObject.get());

	if(!pRasterObj)
		return FALSE;

	double dblCellSizeX, dblCellSizeY;

	std::string  strWktIn;
	strWktIn = pRasterObj->GetProjection();

	pRasterObj->GetCellSize(&dblCellSizeX,&dblCellSizeY);

	m_csCellSizeX.Format("%.6f",dblCellSizeX);
	m_csCellSizeY.Format("%.6f",dblCellSizeY);

	GEOMETRY::geom::Envelope envelop;

	pRasterObj->GetExtent(&envelop);

	m_dblDRx = envelop.getMaxX();
	m_dblDRy = envelop.getMinY();
	m_dblULx = envelop.getMinX();
	m_dblULy = envelop.getMaxY();

	mm_bParseOk=TRUE;

	SetWkt(strWktIn.c_str());

	//DumpProjInfo();

	UpdateData(FALSE);


	return TRUE;

}

void CDlgRasGeoProperty::DumpProjInfo()
{
	/*if (mm_bParseOk)
	{
		if (mm_stProjcs.bProj)
		{
			m_csProjName.Format("%s", mm_stProjcs.name);
			DumpProjcs(&mm_stProjcs, m_csWktDetail, TRUE);
		}
		else
		{
			m_csProjName.Format("%s", mm_stProjcs.geogcs.name);
			DumpProjcs(&mm_stProjcs, m_csWktDetail, FALSE);
		}
	}
	else
	{
		m_csProjName = _T("无信息");
		mm_csWkt = _T("无信息");
		m_csWktDetail = _T("无信息");
	}*/
	UpdateData(FALSE);
}

BOOL CDlgRasGeoProperty::SetWkt(const char *pszWktIn)
{
	/*if (NULL == pszWktIn)
	{
		mm_bParseOk = FALSE;
		return FALSE;
	}
	if (IPE_ParseWkt2ST ( pszWktIn, &mm_stProjcs))
	{
		mm_bParseOk = TRUE; 
		mm_csWkt.Format("%s", pszWktIn);
	}
	else
	{
		mm_bParseOk = FALSE;
	}*/
	return FALSE;
}

BOOL CDlgRasGeoProperty::GetWkt(char *pszWktOut)
{
	if (!mm_bParseOk)
	{
		strcpy(pszWktOut, "No Projection");
		return FALSE;
	}
	strcpy(pszWktOut, (LPCTSTR)mm_csWkt);
	return TRUE;
}

