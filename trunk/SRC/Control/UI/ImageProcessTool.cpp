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

namespace Control
{

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
             AfxMessageBox("ºÏ≤‚≥…π¶");
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
				 //…Ë÷√Õº≤„√˚
				 pLayer->SetName(std::string(csThemeName));

				 Carto::IFeatureLayerPtr pFeatureLayer =pLayer;
				 Carto::CSimpleRenderPtr pRender =pFeatureLayer->GetFeatureRender();

				 //…Ë÷√∑˚∫≈
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
			 AfxMessageBox("ºÏ≤‚ ß∞‹");
		 }
	 }
}

}