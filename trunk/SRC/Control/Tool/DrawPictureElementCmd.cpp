#include "stdafx.h"
#include "DrawPictureElementCmd.h"
#include "PictureElement.h"
#include "IWorkspace.h"
#include "IRasterDataset.h"
#include "RasterWSFactory.h"


namespace Control
{

	static CDrawPictureElementCmd gDrawPictureElementCmd;

	CDrawPictureElementCmd::CDrawPictureElementCmd() : ICommand("DrawPictureElementCmd")
	{
	}

	CDrawPictureElementCmd::~CDrawPictureElementCmd()
	{

	}
	void CDrawPictureElementCmd::Initialize(Framework::IUIObject *pTargetControl)
	{
		ICommand::Initialize(pTargetControl);

		//��ȡ���ͼ�ؼ�
		m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
	}
	void CDrawPictureElementCmd::Click()
	{
		ICommand::Click();

		CString csFilter =	"BMP(*.bmp)|*.bmp|TIFF(*.tif)|*.tif|TIFF(*.tiff)|*.tiff|JPEG(*.jpg)|*.jpg||";
		CString csFileName(_T("*.BMP"));
		CFileDialog dlg(TRUE, "BMP", csFileName, OFN_HIDEREADONLY, csFilter);

		if( IDOK == dlg.DoModal() )
		{	
			CString csPath = dlg.GetPathName();

			CString csDataSourceTmp=csPath;

			CString csThemeName = csPath.Mid (csPath.ReverseFind ('\\') + 1);
			csThemeName =csThemeName.Left(csThemeName.ReverseFind('.'));


			Geodatabase::IWorkspace *pWorkspace =CRasterWSFactory::GetInstance()->OpenFromFile(csDataSourceTmp);

			if(!pWorkspace)
			{
				MessageBox(NULL,"������ʧ�ܣ�","��ʾ",MB_OK);
				return;
			}
			Geodatabase::IRasterDatasetPtr pRaster =pWorkspace->OpenRasterDataset(csDataSourceTmp);

			if(!pRaster)
			{
				MessageBox(NULL,"������ʧ�ܣ�","��ʾ",MB_OK);
				return;
			}

			Carto::CRasterLayerPtr pLayer;
			pLayer = Carto::ILayer::CreateLayer(pRaster);
			pLayer->SetName(std::string(csThemeName));

			//��ȡ���ͼ�ؼ�

			if(!m_pMapCtrl)
				return;

			Carto::CMapPtr pMap = m_pMapCtrl->GetMap();

			long picWidth, picHeight;	
			pRaster->GetSize(&picWidth, &picHeight);

			RECT viewBound = pMap->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();
			DIS_RECT picBound;
			picBound.left = ((double)viewBound.left+(double)viewBound.right)/2.0 - (double)picWidth/2.0;
			picBound.right = picBound.left + picWidth;
			picBound.top = ((double)viewBound.top+(double)viewBound.bottom)/2.0 - (double)picHeight/2.0;
			picBound.bottom = picBound.top + picHeight;

			GEOMETRY::geom::Envelope picExtent;
			GEOMETRY::geom::Geometry *pGeoPic = NULL;
			Element::CPictureElementPtr pPictureElement = NULL;

			pMap->GetDisplay()->GetDisplayTransformation().TransformToGeo(picBound, &picExtent);
			pGeoPic = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&picExtent);	
			pPictureElement.reset(new Element::CPictureElement(*pGeoPic));
			pPictureElement->SetLayer(pLayer);
			pPictureElement->SetPicturePath((LPSTR)(LPCSTR)csDataSourceTmp);
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeoPic);

			pMap->GetGraphicLayer()->UnselectAllElements();
			pMap->GetGraphicLayer()->AddElement(pPictureElement);
			pMap->GetGraphicLayer()->SelectElement(pPictureElement);

			//������˶�ջ
			//pMap->GetElementOperationStack()->AddOperation(Element::OPT_ADD, pPictureElement);

			m_pMapCtrl->UpdateControl(drawElement | drawEdit);


			//����m_pMapCtrlΪѡ��ͼԪ
			m_pMapCtrl->SetCurTool("SelectElementsTool");

		}


	}


}