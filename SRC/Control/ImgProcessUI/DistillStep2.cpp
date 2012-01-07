// DistillStep2.cpp : 实现文件
//

#include "stdafx.h"
#include "Control.h"
#include "DistillStep2.h"
#include "GeoObjectExtract.h"
#include "IMapCtrl.h"
#include "IDocument.h"
#include "FeatureLayer.h"
#include "SimpleRender.h"
#include "IMapCtrl.h"
#include "ShapefileWorkspaceFactory.h"
#include "IWorkspace.h"
#include "ProgressBar.h"

// CDistillStep2 对话框

IMPLEMENT_DYNAMIC(CDistillStep2, CResizablePage)

CDistillStep2::CDistillStep2(CWnd* pParent /*=NULL*/)
: CResizablePage(CDistillStep2::IDD)
, m_dTol(0.2)
, m_nMinArea(100)
, m_shpfile(_T(""))
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
	DDV_MinMaxInt(pDX, m_nMinArea, 20, 100000000);
	DDX_Text(pDX, IDC_EDIT_EXWATERSHP, m_shpfile);
}


BEGIN_MESSAGE_MAP(CDistillStep2, CResizablePage)
	ON_BN_CLICKED(IDC_BTN_SELEXSHP, &CDistillStep2::OnBnClickedBtnSelexshp)
END_MESSAGE_MAP()


// CDistillStep2 消息处理程序


int CDistillStep2::DoWork()
{
	UpdateData();
	if(m_nMinArea<20)
	{
        MessageBox("阈值不能小于20","提示",MB_OK);
		return 1;
	}
    if(!m_pTargetLyr)
	{
		MessageBox("请选择目标层","提示",MB_OK);
		return 1;
	}
	if(m_shpfile=="")
	{
		MessageBox("请选择结果路径","提示",MB_OK);
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

	Control::CProgressBar progress;

	bool bret =ImageProcess::WaterExtract(m_pTargetLyr->GetDataObject()->Getname().c_str(),m_shpfile,samples,m_nMinArea,&progress);

	//将样本删除
	for(int i=count-1;i>=0;i--)
	{
		pElement =pLayer->GetElement(i);
		if(!pElement)
		{
			continue;
		}
		if(pElement->GetUserdata()==2)
		{
			pLayer->RemoveElement(pElement);


		}
	}
	if(bret)
	{
        MessageBox("提取成功","提示",MB_OK);
		Framework::IDocument *pDoc =(Framework::IDocument*)Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppDocument);
		
		CString csDataSourceTmp=m_shpfile;

		CString csThemeName = csDataSourceTmp.Mid (csDataSourceTmp.ReverseFind ('\\') + 1);
		csThemeName =csThemeName.Left(csThemeName.ReverseFind('.'));

		Geodatabase::IWorkspace* ipWorkspace = CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(m_shpfile);
		Geodatabase::IFeatureClassPtr ipFeatureCls = ipWorkspace->OpenFeatureClass(m_shpfile);


		Carto::ILayerPtr pLayer = Carto::ILayerPtr(new Carto::CFeatureLayer());
		pLayer = Carto::ILayer::CreateLayer(ipFeatureCls);
		//设置图层名
		pLayer->SetName(std::string(csThemeName));

		//Carto::IFeatureLayerPtr pFeatureLayer =pLayer;
		//Carto::CSimpleRenderPtr pRender =pFeatureLayer->GetFeatureRender();

		////设置符号
		//Display::CSimpleFillSymbolPtr pFillSymbol =pRender->GetSymbol();
		//pFillSymbol->SetDrawFill(false);
		//pFillSymbol->SetOutLineWidth(1.5);
		//pFillSymbol->SetOutLineColor(RGB(255,0,0));

		pDoc->GetActiveMap()->AddLayer(pLayer);

		pDoc->GetLinkMapTree()->AddLayer(pLayer);
        
		Framework::IMapCtrl::GetActiveMapCtrl()->UpdateControl(drawAll);

	}
	else
	{
		progress.Close();
		MessageBox("提取失败","提示",MB_OK);
	}
    return 0;

}

void CDistillStep2::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
    
	__super::OnOK();
}

void CDistillStep2::OnBnClickedBtnSelexshp()
{
	UpdateData();
	CFileDialog dlg(false, "*.shp", "",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"shapefile(*.shp)|*.shp||",this);
	if(dlg.DoModal()==IDOK) 
	{
		m_shpfile =dlg.GetPathName();
		UpdateData(FALSE);
	}
}
