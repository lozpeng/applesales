#include "StdAfx.h"
#include "PictureElement.h"
#include "EnvelopeTracker.h"
#include "IWorkspace.h"
#include "IRasterDataset.h"


namespace Element{

CPictureElement::CPictureElement():IFrameElementBase()
{
	m_enumElementType = ET_EXT_PICTURE_ELEMENT;

	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_FOUR));

	m_pMap.reset( new Carto::CMap());

	m_bMapDCInited = FALSE;

	m_bProperChanged = TRUE;

	m_eWHRatio = EWHR_FIX_RATIO;

	m_strPicPath = "";
}

CPictureElement::CPictureElement(const GEOMETRY::geom::Geometry& geometry):IFrameElementBase(geometry)
{
	m_enumElementType = ET_EXT_PICTURE_ELEMENT;

	m_pSelectionHandle.reset(new CEnvelopeTracker(*geometry.getEnvelopeInternal(), HT_FOUR));

	m_pMap.reset( new Carto::CMap());

	m_bMapDCInited = FALSE;

	m_bProperChanged = TRUE;

	m_eWHRatio = EWHR_FIX_RATIO;

	m_strPicPath = "";

}

CPictureElement::~CPictureElement(void)
{	

}

void CPictureElement::serialization(SYSTEM::IArchive &ar)
{
	IFrameElementBase::serialization(ar);

	if(ar.IsRead())
	{
		ar & m_strPicPath;

		/*Geodatabase::IWorkspace *pWorkspace =CotIfeWorkspaceFactory::GetInstance()->OpenFromFile(m_strPicPath.c_str());

		if(!pWorkspace)
		{
			MessageBox(NULL,"打开数据失败！","提示",MB_OK);
			return;
		}
		Geodatabase::IRasterDatasetPtr pRaster =pWorkspace->OpenRasterDataset(m_strPicPath.c_str());

		if(!pRaster)
		{
			MessageBox(NULL,"打开数据失败！","提示",MB_OK);
			return;
		}

		Carto::CRasterLayerPtr pLayer;
		pLayer = Carto::ILayer::CreateLayer(pRaster);
		m_pMap->DeleteLayer(0);
		m_pMap->AddLayer(pLayer);*/

		m_bProperChanged = TRUE;
	}
	else
	{
		ar & m_strPicPath;
	}
}


void CPictureElement::SetLayer(Carto::CRasterLayerPtr pRasLayer)
{
	m_pMap->GetLayers().RemoveAll();
	m_pMap->AddLayer(pRasLayer);
}

Carto::CRasterLayerPtr CPictureElement::GetLayer()
{
	return m_pMap->GetLayers().GetAt(0);
}


//////////////////////////////////////////////////////////////////////////

void CPictureElement::DrawNormal(Display::IDisplayPtr pDisplay)
{
	//更新map的display
	UpdateMapDisplay(pDisplay);

	//绘制
	DrawBackground(pDisplay);

	DrawMap(pDisplay);

	DrawForeground(pDisplay);
}

void CPictureElement::UpdateMapDisplay(Display::IDisplayPtr pDisplay)
{
	DIS_RECT pictureSize = *pDisplay->GetDisplayTransformation().TransformToDisplay(m_pGeometry->getEnvelopeInternal());
	if(!m_bMapDCInited)
	{
		HDC hdc = ::CreateCompatibleDC((HDC)pDisplay->GetDrawDC()->GetSafeHdc());
		
		m_pMap->GetDisplay()->SetDC((long)hdc, pictureSize.Width(), pictureSize.Height());

		m_bMapDCInited = TRUE;
	}
	else
	{
		m_pMap->GetDisplay()->GetDrawDC()->CacheBitmap(pictureSize.Width(), pictureSize.Height());
	}
}

void CPictureElement::DrawMap(Display::IDisplayPtr pDisplay)
{
	/*if(m_bProperChanged)
	{*/
		ReDrawMap(pDisplay);
		//m_bProperChanged = FALSE;
	//}

	DIS_RECT *rect = pDisplay->GetDisplayTransformation().TransformToDisplay(m_pGeometry->getEnvelopeInternal());
	BitBlt((HDC)pDisplay->GetDrawDC()->GetSafeHdc(), rect->left, rect->top, 
		rect->Width(), rect->Height(),(HDC)m_pMap->GetDisplay()->GetDrawDC()->GetSafeHdc(), 0,0, SRCCOPY);

}

void CPictureElement::ReDrawMap(Display::IDisplayPtr pDisplay)
{
	DIS_BOUND *rect = pDisplay->GetDisplayTransformation().TransformToDisplayBound(m_pGeometry->getEnvelopeInternal());

	////更新可视范围的大小
	//RECT rct;
	//rct.left = 0;
	//rct.right = rect->right - rect->left;
	//rct.top = 0;
	//rct.bottom = rect->bottom - rect->top;


	m_pMap->GetDisplay()->GetDisplayTransformation().SetViewBound(*rect);

	m_pMap->GetDisplay()->GetDisplayTransformation().FitViewBound(m_pMap->GetExtent());

	//绘制map
	m_pMap->Draw(drawAll);
	m_pMap->GetDisplay()->SetDrawBuffer(drawAll);
	m_pMap->GetDisplay()->DrawBackgroud();
	m_pMap->GetDisplay()->RefreshDisplay(drawAll);

	FreeDisplayObj(rect);
}

void CPictureElement::GeometryChangedEvents()
{
	IFrameElementBase::GeometryChangedEvents();
	m_bProperChanged = TRUE;
}

////属性编辑//////////////////////////////////////////////////////////////////////

void CPictureElement::SetPicturePath(std::string picPath)
{
	std::string oldPath = m_strPicPath;
	m_strPicPath = picPath;
	if(/*oldPath.compare("") == 0 || */oldPath.compare(picPath) == 0 )
		return;

	/*Geodatabase::IWorkspace *pWorkspace =CotIfeWorkspaceFactory::GetInstance()->OpenFromFile(picPath.c_str());

	if(!pWorkspace)
	{
		MessageBox(NULL,"打开数据失败！","提示",MB_OK);
		return;
	}
	Geodatabase::IRasterDatasetPtr pRaster =pWorkspace->OpenRasterDataset(m_strPicPath.c_str());

	if(!pRaster)
	{
		MessageBox(NULL,"打开数据失败！","提示",MB_OK);
		return;
	}

	Carto::CRasterLayerPtr pLayer;
	pLayer = Carto::ILayer::CreateLayer(pRaster);
	m_pMap->DeleteLayer(0);
	m_pMap->AddLayer(pLayer);*/
	
	m_bProperChanged = TRUE;

}

std::string CPictureElement::GetPicturePath()
{
	return m_strPicPath;
}
}
