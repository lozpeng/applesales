#include "stdafx.h"
#include "ImageProcessTool.h"
#include "DllResource.h"
#include "DlgChangeDetect.h"
#include "ImgChangeDetect.h"
#include "IDocument.h"
#include "FeatureLayer.h"
#include "SimpleRender.h"
#include "IMapCtrl.h"
#include "ShapefileWorkspaceFactory.h"
#include "IWorkspace.h"
#include "ProgressBar.h"

//���������
#include "TreePropSheetEx.h"
#include "DistillStep1.h"
#include "DistillStep2.h"
#include "TreePropSheetEx.h"
#include "Control.h"
namespace Control
{
	std::vector<TreePropSheet::CTreePropSheetEx*> CImageProcessTool::m_manageSheet;
	std::vector<CResizablePage*>  CImageProcessTool::m_manageSheetPage;
	void CImageProcessTool::ShowImgChangeDetectDlg()
	{
		CDllResource hdll;
		CDlgChangeDetect dlg;
		if(dlg.DoModal()==IDOK)
		{
			CProgressBar progress;
			ImageProcess::ImgChangeDetect detect;
			bool bsuc =detect.RelativeDetect(dlg.m_strSrc,dlg.m_strDest,dlg.m_strResult,dlg.m_nSize,dlg.m_dCor,&progress);
			if(bsuc)
		 {
			 AfxMessageBox("���ɹ�");
			 if(dlg.m_bLoadShp)
			 {
				 Framework::IDocument *pDoc =(Framework::IDocument*)Framework::IUIObject::GetUIObjectByName(Framework::CommonUIName::AppDocument);
				 //pDoc->LoadShpFile(dlg.m_strResult);

				 CString csDataSourceTmp=dlg.m_strResult;

				 CString csThemeName = csDataSourceTmp.Mid (csDataSourceTmp.ReverseFind ('\\') + 1);
				 csThemeName =csThemeName.Left(csThemeName.ReverseFind('.'));

				 Geodatabase::IWorkspace* ipWorkspace = CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(dlg.m_strResult);
				 Geodatabase::IFeatureClassPtr ipFeatureCls = ipWorkspace->OpenFeatureClass(dlg.m_strResult);


				 Carto::ILayerPtr pLayer = Carto::ILayerPtr(new Carto::CFeatureLayer());
				 pLayer = Carto::ILayer::CreateLayer(ipFeatureCls);
				 //����ͼ����
				 pLayer->SetName(std::string(csThemeName));

				 Carto::IFeatureLayerPtr pFeatureLayer =pLayer;
				 Carto::CSimpleRenderPtr pRender =pFeatureLayer->GetFeatureRender();

				 //���÷���
				 Display::CSimpleFillSymbolPtr pFillSymbol =pRender->GetSymbol();
				 pFillSymbol->SetDrawFill(false);
				 pFillSymbol->SetOutLineWidth(1.5);
				 pFillSymbol->SetOutLineColor(RGB(255,0,0));

				 pDoc->GetActiveMap()->AddLayer(pLayer);

				 pDoc->GetLinkMapTree()->AddLayer(pLayer);
			 }
		 }
			else
		 {
			 AfxMessageBox("���ʧ��");
		 }
		}
	}
	void CImageProcessTool::ShowDistillWaterSheet(Control::CMapControl* mapControl, CWnd* pParent)
	{
		CDllResource hdll;
		TreePropSheet::CTreePropSheetEx* pFlowSheet = new TreePropSheet::CTreePropSheetEx("ˮ����Ϣ��ȡ");
		pFlowSheet->SetTreeViewMode( TRUE, TRUE, TRUE);
		pFlowSheet->SetIsResizable( true );
		pFlowSheet->SetTreeWidth( 150 );  
		pFlowSheet->SetPaneMinimumSizes( 150, 180 );
		pFlowSheet->SetMinSize( CSize( 500, 400 ) );	
		pFlowSheet->SetAutoExpandTree(true);

		CDistillStep1* pStep1 = new CDistillStep1();
		pStep1->SetMapControl(mapControl);
		CDistillStep2* pStep2 = new CDistillStep2();
		pFlowSheet->AddPage(pStep1);
		pFlowSheet->AddPage(pStep2);

		pFlowSheet->Create(pParent, /*WS_POPUP|*/WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_VISIBLE, 0 );
		pFlowSheet->Invalidate( TRUE );

		m_manageSheet.push_back(pFlowSheet);

		m_manageSheetPage.push_back(pStep1);
		m_manageSheetPage.push_back(pStep2);
	}
	void CImageProcessTool::ReleaseSheets()
	{
		for(int i=0; i<(int)m_manageSheet.size(); i++)
		{
			if(NULL != m_manageSheet[i])
			{
				if(m_manageSheet[i]->m_hWnd)
				{
					m_manageSheet[i]->EnableWindow();
					m_manageSheet[i]->DestroyWindow();
				}
				delete m_manageSheet[i];
				m_manageSheet[i] = NULL;
			}
		}
		m_manageSheet.clear();

		for(int i=0; i<(int)m_manageSheetPage.size(); i++)
		{
			if(NULL != m_manageSheetPage[i])
			{
				delete m_manageSheetPage[i];
				m_manageSheetPage[i] = NULL;
			}
		}
		m_manageSheetPage.clear();
	}
}