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
#include "DlgSetChangeSymbol.h"
#include "FuzzyKMeanDialog.h"
//流程向导相关
#include "TreePropSheetEx.h"
#include "DistillStep1.h"
#include "DistillStep2.h"
#include "Raster2VectorDialog.h"
#include "TreePropSheetEx.h"
#include "Control.h"
#include "DlgModifyImgClass.h"
#include "DlgTargetClip.h"
#include "ImageClip.h"

namespace Control
{
	std::vector<TreePropSheet::CTreePropSheetEx*> CImageProcessTool::m_manageSheet;
	std::vector<CResizablePage*>  CImageProcessTool::m_manageSheetPage;

	Display::IFillSymbolPtr CImageProcessTool::m_pChangeSymbol;


	void CImageProcessTool::InitSymbol()
	{
		if(!m_pChangeSymbol)
		{
			//设置符号
			Display::CSimpleFillSymbol *pSymbol =new Display::CSimpleFillSymbol();
			pSymbol->SetDrawFill(false);
			pSymbol->SetOutLineWidth(1.5);
			pSymbol->SetOutLineColor(RGB(255,0,0));

			m_pChangeSymbol =pSymbol;
		}
	}
	
	void CImageProcessTool::ShowImgChangeDetectDlg()
	{
		CDllResource hdll;
		if(!m_pChangeSymbol)
		{
			//设置符号
			Display::CSimpleFillSymbol *pSymbol =new Display::CSimpleFillSymbol();
			pSymbol->SetDrawFill(false);
			pSymbol->SetOutLineWidth(1.5);
			pSymbol->SetOutLineColor(RGB(255,0,0));

			m_pChangeSymbol =pSymbol;
		}
		CDlgChangeDetect dlg;
		if(dlg.DoModal()==IDOK)
		{
			CProgressBar progress;
			ImageProcess::ImgChangeDetect detect;

			////
			//bool bsuc = ImageProcess::RelativeMap(dlg.m_strSrc,dlg.m_strDest,dlg.m_strRelMap,10,&progress);
			////
			// bsuc =detect.RelativeDetect(dlg.m_strSrc,dlg.m_strDest,dlg.m_strResult,dlg.m_nSize,dlg.m_dblH1,dlg.m_dblH2,&progress);

			////
			//bsuc =detect.RelativeDetect(dlg.m_strSrc,dlg.m_strDest,dlg.n_strRel2,dlg.m_nSize,dlg.m_dblP1,dlg.m_dblP2,&progress);

			////
			//bsuc =detect.RelativeDetect(dlg.m_strSrc,dlg.m_strDest,dlg.m_strResult3,dlg.m_nSize,dlg.m_dblW1,dlg.m_dblW2,&progress);

			bool bsuc = detect.TargetDetect(dlg.m_strSrc, dlg.m_strDest, dlg.m_strResult, dlg.m_nSize, dlg.m_dblH1,dlg.m_dblH2, dlg.m_dblP1, &progress);

			 if(bsuc)
			 {
				 AfxMessageBox("检测成功");

			 }
				else
			 {
				 AfxMessageBox("检测失败");
			 }
		}
	}

	void CImageProcessTool::ShowChangeSymbolDlg()
	{
        CDllResource hdll;
		CDlgSetChangeSymbol dlg;
		dlg.DoModal();
        
	}

	void CImageProcessTool::ShowFuzzyKMeanDlg()
	{
		CDllResource hdll;
		CFuzzyKMeanDialog dlg;
		dlg.DoModal();
	}

	void CImageProcessTool::ShowClassVectorDlg()
	{
		CDllResource hdll;
		CRaster2VectorDialog dlg;
		dlg.DoModal();
	}

	void CImageProcessTool::ShowTargetClipDlg()
	{
		CDllResource hdll;
		CDlgTargetClip dlg;
		dlg.DoModal();
	}

	void CImageProcessTool::ShowDistillWaterSheet(Control::CMapControl* mapControl, CWnd* pParent)
	{
		CDllResource hdll;
		TreePropSheet::CTreePropSheetEx* pFlowSheet = new TreePropSheet::CTreePropSheetEx("水华信息提取");
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

	void CImageProcessTool::ModifyImgClasses()
	{
		CDllResource hdll;
		CDlgModifyImgClass dlg;
		dlg.DoModal();
	}
}