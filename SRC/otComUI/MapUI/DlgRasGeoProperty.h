#pragma once
#include "resource.h"
//#include "projcs.h"
#include "RasterLayer.h"

// CDlgRasGeoProperty �Ի���

class CDlgRasGeoProperty : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgRasGeoProperty)

public:
	CDlgRasGeoProperty();   // ��׼���캯��
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
	CString	m_csProjName;   //����
	CString	m_csWktDetail;    //ͶӰ����ϸ����

public:
	void SetLayer(Carto::CRasterLayerPtr pLayer) {m_pLayer = pLayer;};

// �Ի�������
	enum { IDD = IDD_DLG_GEO_COORDINATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

protected:
	CString	m_csCellSizeX;
	CString	m_csCellSizeY;
	CString  mm_csWkt;
//	STPROJCS mm_stProjcs;
	BOOL	 mm_bParseOk;  //�Ƿ���ͶӰ��Ϣ
	void	 DumpProjInfo();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedProjecttion();

private:
	Carto::CRasterLayerPtr m_pLayer;
};
