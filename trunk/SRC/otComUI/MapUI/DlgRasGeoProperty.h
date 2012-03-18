#pragma once
#include "resource.h"
//#include "projcs.h"
#include "RasterLayer.h"

// CDlgRasGeoProperty 对话框

class CDlgRasGeoProperty : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgRasGeoProperty)

public:
	CDlgRasGeoProperty();   // 标准构造函数
	virtual ~CDlgRasGeoProperty();

public:
	BOOL SetWkt (const char *pszWktIn);
	BOOL GetWkt(char *pszWktOut);
public:
	double	m_dblDRx;
	double	m_dblDRy;
	double	m_dblULx;
	double	m_dblULy;
public:
	CString	m_csProjName;   //名字
	CString	m_csWktDetail;    //投影的详细内容

public:
	void SetLayer(Carto::CRasterLayerPtr pLayer) {m_pLayer = pLayer;};

// 对话框数据
	enum { IDD = IDD_DLG_GEO_COORDINATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

protected:
	CString	m_csCellSizeX;
	CString	m_csCellSizeY;
	CString  mm_csWkt;
//	STPROJCS mm_stProjcs;
	BOOL	 mm_bParseOk;  //是否有投影信息
	void	 DumpProjInfo();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedProjecttion();

private:
	Carto::CRasterLayerPtr m_pLayer;
};
