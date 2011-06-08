// DistillStep2.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "DistillStep2.h"
#include "GeoObjectExtract.h"
#include "IMapCtrl.h"

// CDistillStep2 对话框

IMPLEMENT_DYNAMIC(CDistillStep2, CResizablePage)

CDistillStep2::CDistillStep2(CWnd* pParent /*=NULL*/)
: CResizablePage(CDistillStep2::IDD)
, m_dTol(0.2)
, m_nMinArea(10)
{
	//m_psp.dwFlags &= (~PSP_HASHELP);
	m_psp.dwFlags |= PSP_USEHICON;
	HICON hIconTab = AfxGetApp()->LoadIcon(IDI_STEP2);
	m_psp.hIcon = hIconTab;
	m_pTargetLyr = NULL;
}

CDistillStep2::~CDistillStep2()
{
}

void CDistillStep2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TOLL, m_dTol);
	DDV_MinMaxDouble(pDX, m_dTol, 0, 1);
	DDX_Text(pDX, IDC_EDIT_MINAREA, m_nMinArea);
	DDV_MinMaxInt(pDX, m_nMinArea, 1, 100000000);
}


BEGIN_MESSAGE_MAP(CDistillStep2, CResizablePage)
END_MESSAGE_MAP()


// CDistillStep2 消息处理程序


int CDistillStep2::DoWork()
{
	UpdateData();
	if(m_nMinArea<1)
	{
        MessageBox("阈值不能小于1","提示",MB_OK);
		return 1;
	}
    if(!m_pTargetLyr)
	{
		MessageBox("请选择目标层","提示",MB_OK);
		return 1;
	}

	Carto::CMapPtr pMap =Framework::IMapCtrl::GetActiveMapCtrl()->GetMap();

	if(!pMap)
	{
		return 1;
	}

	Carto::CGraphicLayerPtr pLayer =pMap->GetGraphicLayer();
	Element::IElementPtr pElement;
	int count =pLayer->GetElementCount();
	if(count<=0)
	{
		return 1;
	}
	std::vector<GEOMETRY::geom::Polygon*> samples;
	for(int i=count-1;i>=0;i--)
	{
		pElement =pLayer->GetElement(i);
		if(!pElement)
		{
			continue;
		}
		if(pElement->GetUserdata()==2)
		{
			samples.push_back(dynamic_cast<GEOMETRY::geom::Polygon*>(pElement->GetGeometry()));
			
		
		}
	}


	ImageProcess::WaterExtract(m_pTargetLyr->GetDataObject()->Getname().c_str(),"aaa",samples);

    return 0;

}

void CDistillStep2::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
    
	__super::OnOK();
}
