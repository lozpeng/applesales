// LayerBasepropPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Control.h"
#include "LayerBasepropPage.h"
#include "IFeatureClass.h"


// CLayerBasepropPage �Ի���

IMPLEMENT_DYNAMIC(CLayerBasepropPage, CPropertyPage)

CLayerBasepropPage::CLayerBasepropPage()
	: CPropertyPage(CLayerBasepropPage::IDD)
	, m_layername(_T(""))
	, m_strSource(_T(""))
	, m_top(0)
	, m_left(0)
	, m_right(0)
	, m_bottom(0)
{
    m_psp.dwFlags &= ~PSP_HASHELP;
	m_player =NULL;
}

CLayerBasepropPage::~CLayerBasepropPage()
{
}

void CLayerBasepropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LAYERNAME, m_layername);
	DDX_Text(pDX, IDC_EDIT_DATAPATH, m_strSource);
	DDX_Text(pDX, IDC_EXTENT_TOP, m_top);
	DDX_Text(pDX, IDC_EXTENT_LEFT, m_left);
	DDX_Text(pDX, IDC_EXTENT_RIGHT, m_right);
	DDX_Text(pDX, IDC_EXTENT_BOTTOM, m_bottom);
}


BEGIN_MESSAGE_MAP(CLayerBasepropPage, CPropertyPage)
END_MESSAGE_MAP()


// CLayerBasepropPage ��Ϣ�������
void CLayerBasepropPage::SetLayer(Carto::ILayer *player)
{
	m_player =player;
}
BOOL CLayerBasepropPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	if (m_player == NULL)
	{
		return FALSE;
	}

	//����ͼ����
	m_layername =m_player->GetName().c_str();

	GetDataSource();

	//���õ���Χ
	GEOMETRY::geom::Envelope extent=  m_player->GetEnvelope();
	m_top =extent.getMaxY();
	m_left =extent.getMinX();
	m_right =extent.getMaxX();
	m_bottom =extent.getMinY();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CLayerBasepropPage::GetDataSource()
{
	Geodatabase::IGeodataObjectPtr dataLayer =m_player->GetDataObject();

	if(!dataLayer)
	{
		return;
	}
	Geodatabase::GEODATATYPE type =dataLayer->GetType();

	CString strInfo;

	switch(type)
	{
	case Geodatabase::GDT_FEATURECLASS:
		{
			std::string path =dataLayer->Getname();

			strInfo.Format("%s%s\r\n\r\n","·��: ",path.c_str());

			CString strType="����������: ";

			//��ü���������
			Geodatabase::IFeatureClassPtr pFeatureClass =dataLayer;
			if(pFeatureClass)
			{
				long shpType =pFeatureClass->ShapeType();

				switch(shpType)
				{
				case GEOMETRY::geom::GEOS_POINT:
					strType+="��";
					break;
				case GEOMETRY::geom::GEOS_MULTIPOINT:
					strType+="����";
					break;
				case GEOMETRY::geom::GEOS_LINESTRING:
				case GEOMETRY::geom::GEOS_LINEARRING:
					strType+="��";
					break;
				case GEOMETRY::geom::GEOS_MULTILINESTRING:
					strType+="����";
					break;
				case GEOMETRY::geom::GEOS_POLYGON:
				case GEOMETRY::geom::GEOS_MULTIPOLYGON:
					strType+="�����";
					break;
				case GEOMETRY::geom::GEOS_GEOMETRYCOLLECTION:
					strType+="ͼ�μ���";
					break;
				default:
					strType+="δ֪����";
					break;

				}

				strInfo+=strType;
			}



			break;
		}
	case Geodatabase::GDT_RASTERDATASET:
		{
			std::string path =dataLayer->Getname();

			strInfo.Format("%s%s\r\n\n","·��: ",path.c_str());

			break;
		}
	default:
		break;
	}

	m_strSource =strInfo;
}