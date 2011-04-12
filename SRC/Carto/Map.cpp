#include "stdafx.h"
#include "Map.h"
#include "FeatureLayer.h"
#include "GraphicLayer.h"
#include "IFeatureClass.h"
#include "IRasterDataset.h"
#include "DisplayTransformation.h"
#include "ProjTransform.h"

namespace Carto
{

	static boost::signal<void (ILayerPtr)> gCallbackDeleteLayer;
	static boost::signal<void (ILayerPtr)> gCallbackActiveLayer; 
	static boost::signal<void (CMap*)> gCallbackChangeMapExtent;
	static boost::signal<void (CMap*)> gCallbackChangeMapProj;
	static boost::signal<void (CMap*)> gCallbackChangeMapExtentMode;
	static boost::signal<void (CMap*)> gCallbackMapReDrawed;
	static boost::signal<void (ILayerPtr)> gCallbackLayerColorAdjust;

	CMap::CMap()
	{
		m_pDisplay.reset(new Display::IDisplay()) ;

		m_lID = 0;

		m_unit = SYSTEM::SYS_UNIT_UNKNOWN;
		m_bSetPrj = FALSE;
		//m_activeLayer = NULL;
		//m_pEagleEyeViewPtr = NULL;
		m_pGraphicLayer.reset(new Carto::CGraphicLayer(GEOMETRY::geom::Envelope(0,0,1,1)));


		m_viewEnvelope.init(0,0,0,0);

		m_dbReferenceScale = 0;

		m_ExtentMode = EEM_AUTO;

		m_bFramed = FALSE;

		m_dbFramePageScale = 1;

		//m_pCrossLine = NULL;

		m_lActiveLayerId = -1;

		//CAoiManager* pManager = new CAoiManager();
		//m_pAoiManager.reset(pManager);

		//m_pElementOperStack.reset(new Element::CElementOperationStack(m_pGraphicLayer));
	}

	CMap::~CMap()
	{

	}

	void CMap::serialization(SYSTEM::IArchive &ar)
	{
		SYSTEM::ISerialization::serialization( ar );
		if(ar.IsRead())
		{
			ar & m_strMapName;

			ar & m_strWkt;

			double refScale;
			ar & refScale;
			SetReferenceScale(refScale);

			if(m_strWkt == "")
			{
				m_bSetPrj = FALSE;
				m_unit = SYSTEM::SYS_UNIT_UNKNOWN;
			}
			else
			{
				m_bSetPrj = TRUE;

				//设置投影单位
				/*STPROJCS stProjcs;
				IPE_ParseWkt2ST ( m_strWkt.c_str(), &stProjcs);

				if(stProjcs.bProj)
				m_unit = SYSTEM::UnitConverter::GetUnitByString(stProjcs.unit.name);
				else
				m_unit = SYSTEM::UnitConverter::GetUnitByString(stProjcs.geogcs.unit.name);;	*/	
			}
			m_pDisplay->GetDisplayTransformation().SetUnit(m_unit);

			m_Layers.serialization(ar);
			UpdateMapExtent();

			long id;
			ar & id;
			if(id >= 0 && id < m_Layers.GetSize())
				SetActiveLayer(m_Layers.GetAt(id));
			else if(m_Layers.GetSize()>0)
				SetActiveLayer(m_Layers.GetAt(0));

			//		m_pGraphicLayer = ILayer::CreateLayerFromStream(ar);

			int extMode;
			ar & extMode;
			m_ExtentMode = (MAP_EXTENT_MODE)extMode; 

			double minx, maxx, miny, maxy;

			ar & minx;

			ar & maxx;

			ar & miny;

			ar & maxy;

			m_viewEnvelope.init(minx, maxx, miny, maxy);

		}
		else
		{
			ar & m_strMapName;

			ar & m_strWkt;

			ar & m_dbReferenceScale;

			m_Layers.serialization(ar);

			//long id = m_Layers.FindIndex(m_activeLayer);

			ar & m_lActiveLayerId;

			//m_pGraphicLayer->serialization(ar);

			long extMode = (long)m_ExtentMode;
			ar & extMode; 

			double minx, maxx, miny, maxy;
			minx = m_viewEnvelope.getMinX();
			maxx = m_viewEnvelope.getMaxX();
			miny = m_viewEnvelope.getMinY();
			maxy = m_viewEnvelope.getMaxY();

			ar & minx;;

			ar & maxx;

			ar & miny;

			ar & maxy;
		}
	}

	void CMap::serializationEx1(SYSTEM::IArchive &ar)
	{
		SYSTEM::ISerialization::serialization( ar );
		if(ar.IsRead())
		{
			//m_pGraphicLayer = ILayer::CreateLayerFromStream(ar);
		}
		else
		{
			//m_pGraphicLayer->serialization(ar);
		}
	}

	void CMap::serializationEx2(SYSTEM::IArchive &ar)
	{
		SYSTEM::ISerialization::serialization( ar );
		if(ar.IsRead())
		{
			ar & m_strMapName;

			ar & m_strWkt;

			double refScale;
			ar & refScale;
			SetReferenceScale(refScale);

			if(m_strWkt == "")
			{
				m_bSetPrj = FALSE;
				m_unit = SYSTEM::SYS_UNIT_UNKNOWN;
			}
			else
			{
				m_bSetPrj = TRUE;

				//设置投影单位
				/*STPROJCS stProjcs;
				IPE_ParseWkt2ST ( m_strWkt.c_str(), &stProjcs);

				if(stProjcs.bProj)
				m_unit = SYSTEM::UnitConverter::GetUnitByString(stProjcs.unit.name);
				else
				m_unit = SYSTEM::UnitConverter::GetUnitByString(stProjcs.geogcs.unit.name);;	*/	
			}
			m_pDisplay->GetDisplayTransformation().SetUnit(m_unit);

			m_Layers.serialization(ar);
			UpdateMapExtent();

			long id;
			ar & id;
			if(id >= 0 && id < m_Layers.GetSize())
				SetActiveLayer(m_Layers.GetAt(id));
			else if(m_Layers.GetSize()>0)
				SetActiveLayer(m_Layers.GetAt(0));

			int extMode;
			ar & extMode;
			m_ExtentMode = (MAP_EXTENT_MODE)extMode; 

			double minx, maxx, miny, maxy;

			ar & minx;

			ar & maxx;

			ar & miny;

			ar & maxy;

			m_viewEnvelope.init(minx, maxx, miny, maxy);

		}
		else
		{
			ar & m_strMapName;

			ar & m_strWkt;

			ar & m_dbReferenceScale;

			m_Layers.serialization(ar);

			//long id = m_Layers.FindIndex(m_activeLayer);

			ar & m_lActiveLayerId;

			long extMode = (long)m_ExtentMode;
			ar & extMode; 

			double minx, maxx, miny, maxy;
			minx = m_viewEnvelope.getMinX();
			maxx = m_viewEnvelope.getMaxX();
			miny = m_viewEnvelope.getMinY();
			maxy = m_viewEnvelope.getMaxY();

			ar & minx;;

			ar & maxx;

			ar & miny;

			ar & maxy;
		}
	}

	CMapPtr CMap::Clone()
	{
		SYSTEM::CBinArchive ar;

		serialization( ar );


		ar.SetReadState();
		ar.SetPosToBegin();
		Carto::CMapPtr ptrMap( new Carto::CMap() );

		ptrMap->serialization(ar);

		//更新显示	
		DIS_BOUND rect = m_pDisplay->GetDisplayTransformation().GetViewBound();
		ptrMap->GetDisplay()->SetDC(m_pDisplay->GetDrawDC()->GetSafeHdc(),(long)(rect.Width()+0.5), (long)(rect.Height()+0.5));		
		ptrMap->SetViewBound(rect);

		return ptrMap;
	}

	Display::IDisplayPtr CMap::GetDisplay()
	{
		return m_pDisplay;
	}

	Display::IDisplayPtr CMap::SetDisplay(Display::IDisplayPtr pNewDisplay)
	{
		Display::IDisplayPtr pOldDisplay = m_pDisplay;

		m_pDisplay = pNewDisplay;

		return pOldDisplay;
	}

	void CMap::Draw(long content )
	{
		OnBeforeDraw(content);

		BOOL bPrint = m_pDisplay->GetPrinting();

		if(content&drawGeography)
		{
			m_pDisplay->SetDrawBuffer(drawGeography);

			m_pDisplay->DrawBackgroud();

			for (int i=0 ; i<m_Layers.GetSize() ; i++ )
			{
				int cnt = m_Layers.GetSize();
				ILayerPtr pLayer = m_Layers[i];
				m_Layers[i]->Draw( m_pDisplay , drawGeography );
				gCallbackLayerColorAdjust(m_Layers[i]);
			}

			gCallbackMapReDrawed(this);
		}

		if(content&drawGeoSelection)
		{
			m_pDisplay->SetDrawBuffer(drawGeoSelection);

			if(!bPrint)
				m_pDisplay->DrawBackgroud();


			for (int i=0 ; i<m_Layers.GetSize() ; i++ )
			{
				m_Layers[i]->Draw( m_pDisplay , drawGeoSelection );
			}
		}

		if(content&drawElement )
		{
			m_pDisplay->SetDrawBuffer(drawElement);

			if(!bPrint)
				m_pDisplay->DrawBackgroud();


			if(m_pGraphicLayer)
				m_pGraphicLayer->Draw( m_pDisplay,drawElement);

			//绘制AOI要素
			//if (m_pAoiManager)
			//{
			//	for (int i=0;i<m_pAoiManager->m_AOIs.size();i++)
			//	{
			//		if(m_pAoiManager->m_AOIs[i]->m_pGraphicLayer)
			//			m_pAoiManager->m_AOIs[i]->m_pGraphicLayer->Draw( m_pDisplay,drawElement);

			//	}
			//}

		}

		if(content&drawEdit )
		{
			m_pDisplay->SetDrawBuffer(drawEdit);

			if(!bPrint)
				m_pDisplay->DrawBackgroud();


			//绘制编辑空间里的内容
			if(m_pEditor)
			{
				if(m_pEditor->IsEditing())
				{
					m_pEditor->DrawEdit(m_pDisplay);
				}
			}

			if(m_pGraphicLayer)
				m_pGraphicLayer->Draw( m_pDisplay,drawEdit);

			////绘制AOI要素
			//if (m_pAoiManager)
			//{
			//	for (int i=0;i<m_pAoiManager->m_AOIs.size();i++)
			//	{
			//		if(m_pAoiManager->m_AOIs[i]->m_pGraphicLayer)
			//			m_pAoiManager->m_AOIs[i]->m_pGraphicLayer->Draw( m_pDisplay,drawEdit);

			//	}
			//}

		}

		if (content&drawTempObj)
		{
			m_pDisplay->SetDrawBuffer(drawTempObj);

			if(!bPrint)
				m_pDisplay->DrawBackgroud();


			//if (m_pEagleEyeViewPtr && m_pEagleEyeViewPtr->GetEagleDrawStatue()) //绘制鹰眼窗口临时对象
			//{
			//	m_pEagleEyeViewPtr->Draw((long)m_pDisplay->GetDrawDC()->GetSafeHdc(),m_pDisplay);

			//}

			////绘制十字丝临时对象
			//if (m_pCrossLine&&m_pCrossLine->m_bDrawStatue) //绘制鹰眼窗口临时对象
			//{
			//	//m_pEagleEyeViewPtr->Draw((long)m_pDisplay->GetDrawDC()->GetSafeHdc(),m_pDisplay);] 
			//	m_pCrossLine->SetDisplayPtr(m_pDisplay);
			//	m_pCrossLine->Draw((long)m_pDisplay->GetDrawDC()->GetSafeHdc());

			//}
		}

		OnAfterDraw(content);
	}


	void CMap::OnAfterDraw(long content)
	{
		if(!m_bFramed && m_ExtentMode != EEM_FIX_EXTENT)
		{
			m_pDisplay->GetDisplayTransformation().GetGeoBound(m_viewEnvelope);
		}
	}

	void CMap::OnBeforeDraw(long content)
	{

	}

	void CMap::SetID(long id)
	{
		m_lID = id;
	}

	long CMap::GetID()
	{
		return m_lID;
	}

	std::string CMap::GetName()
	{
		return m_strMapName;
	}

	void CMap::SetName(std::string Name)
	{
		m_strMapName = Name;
	}

	BOOL CMap::AddNewLayer(Geodatabase::IGeodataObjectPtr pDataObject)
	{
		if(!pDataObject)
			return FALSE;

		Carto::ILayerPtr pLayer;
		pLayer = Carto::ILayer::CreateLayer(pDataObject);
		if(!pLayer)
			return FALSE;
		AddLayer(pLayer);

		return TRUE;	
	}

	BOOL CMap::AddLayer(ILayerPtr pLayer)
	{
		UpdateMapProjection(pLayer);

		m_Layers.Add(pLayer);

		UpdateMapExtent();

		SetActiveLayer(pLayer);

		GEOMETRY::geom::Envelope env = pLayer->GetEnvelope();

		m_pDisplay->GetDisplayTransformation().FitViewBound(env);

		m_pDisplay->GetDisplayTransformation().GetGeoBound(m_viewEnvelope);

		gCallbackActiveLayer(pLayer);

		return TRUE;
	}

	BOOL CMap::DeleteLayer(int iIndex)
	{
		//
		if(iIndex >= m_Layers.GetSize() || iIndex < 0)
			return false;

		ILayerPtr ptrLayer = m_Layers.GetAt(iIndex);
		LAYER_TYPE iLayerType = ptrLayer->GetLayerType();
		//if (iLayerType == eFeatureLayer)
		//{
		//	IFeatureLayerPtr pFeatureLayer = (IFeatureLayerPtr)ptrLayer;
		//	long iFeatureType = pFeatureLayer->GetFeatureType();
		//	switch(iFeatureType)
		//	{
		//	case GEOMETRY::geom::GEOS_POINT:
		//	case GEOMETRY::geom::GEOS_MULTIPOINT:
		//		{				
		//			//m_lPointLayerCount--;
		//		}
		//		break;
		//	case GEOMETRY::geom::GEOS_LINESTRING:
		//	case GEOMETRY::geom::GEOS_MULTILINESTRING:
		//		{
		//			//m_lLineLayerCount--;
		//		}
		//		break;
		//	case GEOMETRY::geom::GEOS_POLYGON:
		//	case GEOMETRY::geom::GEOS_MULTIPOLYGON:
		//		{
		//			//m_lPolygonLayerCount--;
		//		}
		//		break;
		//	case GEOMETRY::geom::GEOS_GEOMETRYCOLLECTION:
		//		{
		//			//m_lGeometryCount--;
		//		}
		//		break;
		//	default:	//FEATURE_UNKNOWN
		//		break;
		//	}

		//}

		//更新激活图层
		if(m_lActiveLayerId == iIndex)
		{
			m_Layers.RemoveAt(iIndex);
			m_lActiveLayerId = m_Layers.GetSize()-1;
		}	
		else
		{
			ILayerPtr pLayer = GetActiveLayer();
			m_Layers.RemoveAt(iIndex);
			SetActiveLayer(pLayer);
		}

		//

		gCallbackDeleteLayer(ptrLayer);

		UpdateMapExtent();

		return TRUE;
	}

	//删除图层的回调
	BOOL CMap::DeleteLayer(ILayerPtr ptrLayer)
	{
		long index = m_Layers.FindIndex(ptrLayer);
		if (index < 0)
		{
			return FALSE;
		}
		return DeleteLayer(index);
	}

	void CMap::MoveLayerUp(ILayerPtr ptrLayer)
	{
		long lIndex = m_Layers.FindIndex(ptrLayer);
		if (lIndex < 1)
		{
			return;
		}

		std::swap(m_Layers[lIndex], m_Layers[lIndex-1]);
		UpdateMapExtent();
	}	

	void CMap::MoveLayerDown(ILayerPtr ptrLayer)
	{
		long lIndex = m_Layers.FindIndex(ptrLayer);
		long lCount = m_Layers.GetSize();
		if (lIndex > lCount - 1 )
		{
			return;
		}

		std::swap(m_Layers[lIndex], m_Layers[lIndex + 1]);
		UpdateMapExtent();
	}

	void CMap::MoveLayerToTop(ILayerPtr ptrLayer)
	{
		long lIndex = m_Layers.FindIndex(ptrLayer);
		if (lIndex < 1)
		{
			return;
		}

		m_Layers.RemoveAt(lIndex);
		m_Layers.InsertAt(0, ptrLayer);
		UpdateMapExtent();
	}

	void CMap::MoveLayerToBottom(ILayerPtr ptrLayer)
	{
		long lIndex = m_Layers.FindIndex(ptrLayer);
		long lCount = m_Layers.GetSize();
		if (lIndex > lCount - 1)
		{
			return;
		}

		m_Layers.RemoveAt(lIndex);
		m_Layers.InsertAt(lCount - 1, ptrLayer);
		UpdateMapExtent();
	}

	void CMap::Clear()
	{
		m_Envelope.setToNull();
		m_Layers.RemoveAll();
	}

	BOOL CMap::UpdateMapProjection(ILayerPtr pLayer)
	{
		Geodatabase::IGeodataObjectPtr pDataObject = pLayer->GetDataObject();
		
		if(pDataObject == NULL)
			return FALSE;

		std::string tempWkt = "";

		switch ( pDataObject->GetType() )
		{
		case Geodatabase::GDT_FEATURECLASS:
			{
				Geodatabase::IFeatureClass *pFeatureObj = dynamic_cast<Geodatabase::IFeatureClass*>(pDataObject.get());
				tempWkt = pFeatureObj->GetWkt();
			}
			break;
		case Geodatabase::GDT_RASTERDATASET:
			{
				Geodatabase::IRasterDataset *pRasterObj = dynamic_cast<Geodatabase::IRasterDataset*>(pDataObject.get());
				tempWkt = pRasterObj->GetProjection();

			}
			break;
		default:
			return FALSE;
		}
		if (tempWkt.length() != 0)
		{
			std::string oldWkt = m_strWkt;

			Geodatabase::CSpatialReferencePtr pSRTemp =new Geodatabase::CSpatialReference();
			pSRTemp->ImportFromESRI(tempWkt.c_str());

			if (m_bSetPrj) //此处动态投影
			{

				Geodatabase::CSpatialReferencePtr pSRmap =new Geodatabase::CSpatialReference();
				pSRmap->ImportFromESRI(m_strWkt.c_str());

				//判断投影是否相同
				if(!pSRmap->IsSame(pSRTemp.get()))
				{
					CAffineTransformPtr pAffine = pLayer->GetAffineTransPtr();

					GEOMETRY::geom::Envelope dataEnvelop = pLayer->GetEnvelope();

					pAffine->DynaProject(tempWkt,m_strWkt,dataEnvelop);
				}
			}
			else
			{
				m_strWkt = tempWkt;
				m_bSetPrj = TRUE;

				//设置投影单位
				Geodatabase::CSpatialReferencePtr pSRmap =new Geodatabase::CSpatialReference();
				pSRmap->ImportFromESRI(m_strWkt.c_str());

				if(pSRmap->IsProjected())
					m_unit = pSRmap->GetLinearUnits();
				else
					m_unit = pSRmap->GetAngularUnits();

				m_pDisplay->GetDisplayTransformation().SetUnit(m_unit);
			}

			if(m_strWkt.compare(oldWkt) != 0)
				gCallbackChangeMapProj(this);




		}	

		return TRUE;
	}

	std::string CMap::GetMapProjection()
	{
		return m_strWkt;
	}

	inline void CMap::UpdateMapExtent()
	{
		m_Envelope.setToNull();
		for (int i = 0 ; i < m_Layers.GetSize() ; i++ )
		{
			ILayerPtr ptrLayer = m_Layers[i];

			//新建的文件矢量图层的范围为0，不计算到地图范围里去
			GEOMETRY::geom::Envelope env = ptrLayer->GetEnvelope();
			const double dblTalerance = 0.0000001;
			if (fabs(env.getHeight() - 0.0) < dblTalerance && fabs(env.getWidth() - 0.0) < dblTalerance)
			{
				break;
			}
			m_Envelope.expandToInclude( &env );
			gCallbackChangeMapExtent(this);		
		}
	}

	Carto::CLayerArray& CMap::GetLayers()
	{
		return m_Layers;
	}

	void CMap::SetActiveLayer(ILayerPtr ptrLayer)
	{
		long index = m_Layers.FindIndex(ptrLayer);
		if (index < 0)
		{
			return;
		}
		else
		{
			m_lActiveLayerId = index;
			// m_activeLayer = ptrLayer;
		}	
	}

	ILayerPtr CMap::GetActiveLayer()
	{
		if(m_lActiveLayerId>=0 && m_lActiveLayerId<m_Layers.GetSize())
			return m_Layers.GetAt(m_lActiveLayerId);
		else
			return NULL;
		//return m_activeLayer;
	}

	CGraphicLayerPtr CMap::GetGraphicLayer()
	{
		return m_pGraphicLayer;
	}

	void CMap::ResetGraphicLayer()
	{
		m_pGraphicLayer.reset(new Carto::CGraphicLayer(m_Envelope));
	}

	boost::signals::connection  CMap::RegisterDeleteLayer(boost::function<void (ILayerPtr)> fun)
	{
		return gCallbackDeleteLayer.connect(fun);
	}

	boost::signals::connection CMap::RegisterActiveLayer(boost::function<void (ILayerPtr)> fun)
	{
		return gCallbackActiveLayer.connect(fun);
	}

	boost::signals::connection CMap::RegisterLayerColorAdjust(boost::function<void (ILayerPtr)> fun)
	{
		return gCallbackLayerColorAdjust.connect(fun);
	}


	boost::signals::connection CMap::RegisterChangeMapExtent(boost::function<void (CMap*)> fun)
	{
		return gCallbackChangeMapExtent.connect(fun);
	}

	boost::signals::connection CMap::RegisterChangeMapExtentMode(boost::function<void (CMap*)> fun)
	{
		return gCallbackChangeMapExtentMode.connect(fun);
	}

	boost::signals::connection CMap::RegisterChangeMapProj(boost::function<void (CMap*)> fun)
	{
		return gCallbackChangeMapProj.connect(fun);
	}

	boost::signals::connection CMap::RegisterMapReDrawed(boost::function<void (CMap*)> fun)
	{
		return gCallbackMapReDrawed.connect(fun);
	}
	/////view/////////////////////////////////////////////////////////////////////
	void CMap::SetFramePageScale(double pageScale,double maptoPageScale)
	{
		m_dbFramePageScale = pageScale;
		m_dbMapToPageScale = maptoPageScale;
	}
	void CMap::SetViewBound(DIS_BOUND bound)
	{
		long lWidth = (long)(bound.Width()+0.5);
		long lHeight = (long)(bound.Height()+0.5);
		m_pDisplay->CacheBuffer(lWidth, lHeight);

		if(m_ExtentMode == EEM_FIX_SCALE)//固定比例尺，随图框调整范围
		{ 	
			//保持比例不变，更新显示地理范围	
			double mapScale, scale;
			mapScale = m_pDisplay->GetDisplayTransformation().GetMapScale();
			scale = m_pDisplay->GetDisplayTransformation().GetScale();

			double dbScale = scale*(m_dbMapFixScale*m_dbFramePageScale)/mapScale;                                 
			m_pDisplay->GetDisplayTransformation().GetGeoBound(m_viewEnvelope);
			m_viewEnvelope.init(m_viewEnvelope.getMinX(), m_viewEnvelope.getMinX()+dbScale*bound.Width(),
				m_viewEnvelope.getMinY(), m_viewEnvelope.getMinY()+dbScale*bound.Height());
		}


		m_pDisplay->GetDisplayTransformation().SetViewBound(bound);	
		m_pDisplay->GetDisplayTransformation().FitViewBound(m_viewEnvelope);

		if(m_ExtentMode == EEM_AUTO)
			m_pDisplay->GetDisplayTransformation().GetGeoBound(m_viewEnvelope);

		gCallbackChangeMapExtent(this);
	}

	void CMap::SetDrawBound(DIS_BOUND bound, BOOL bSetBack)
	{
		if(!bSetBack)
		{
			long lWidth = (long)(bound.Width()+0.5);
			long lHeight = (long)(bound.Height()+0.5);
			m_pDisplay->CacheBuffer(lWidth, lHeight);

			GEOMETRY::geom::Envelope env;

			DIS_BOUND orgBound = m_pDisplay->GetDisplayTransformation().GetViewBound();
			double left,right,top,bottom;
			left = m_viewEnvelope.getMinX() + bound.left*m_viewEnvelope.getWidth()/orgBound.Width();
			right = m_viewEnvelope.getMinX() + bound.right*m_viewEnvelope.getWidth()/orgBound.Width();
			top = m_viewEnvelope.getMaxY() - bound.top*m_viewEnvelope.getHeight()/orgBound.Height();
			bottom = m_viewEnvelope.getMaxY() - bound.bottom*m_viewEnvelope.getHeight()/orgBound.Height();

			m_pDisplay->GetDisplayTransformation().SetGeoCenterX((left + right)/2);
			m_pDisplay->GetDisplayTransformation().SetGeoCenterY((top + bottom)/2);
		}
		else
		{
			GEOMETRY::geom::Coordinate center;
			m_viewEnvelope.centre(center);
			m_pDisplay->GetDisplayTransformation().SetGeoCenterX(center.x);
			m_pDisplay->GetDisplayTransformation().SetGeoCenterY(center.y);
		}



		DIS_BOUND dcBound;
		dcBound.left = 0;
		dcBound.right = bound.Width();
		dcBound.top = 0;
		dcBound.bottom = bound.Height();

		m_pDisplay->GetDisplayTransformation().SetViewBound(dcBound);	
	}

	DIS_BOUND CMap::GetViewBound()
	{
		return m_pDisplay->GetDisplayTransformation().GetViewBound();
	}

	MAP_EXTENT_MODE CMap::GetExtentMode()
	{
		return m_ExtentMode;
	}

	GEOMETRY::geom::Envelope CMap::GetViewEnvelope()
	{
		return m_viewEnvelope;
	}

	void CMap::SetReferenceScale(double refScale)
	{
		m_dbReferenceScale = refScale;
		m_pDisplay->GetDisplayTransformation().SetReferenceScale(m_dbReferenceScale);
	}
	double CMap::GetReferenceScale()
	{
		m_dbReferenceScale = m_pDisplay->GetDisplayTransformation().GetReferenceScale();
		return m_dbReferenceScale;
	}

	void CMap::SetFramed(BOOL bFramed)
	{
		m_bFramed = bFramed;
	}

	void CMap::SelectFeature(ILayer* ipLayer,Geodatabase::CFeaturePtr pFeature)
	{
		if (ipLayer == NULL || pFeature== NULL)
		 return;
		if (ipLayer->GetLayerType()!=FeatureLayer)
			return;
		long lFeatureID = -1;
		Geodatabase::IRowPtr pRow = pFeature;
		lFeatureID = pRow->GetId();
		CFeatureLayer* pFeatureLayer = (CFeatureLayer*)ipLayer;
		
		pFeatureLayer->Select(NULL,SELECT_ADD);
		Geodatabase::ISelctionSet* pFSelection = pFeatureLayer->GetSelection().get();
		if(pFSelection&&lFeatureID >0)
			pFSelection->Add(lFeatureID);

	}
	void CMap::ClearSelection()
	{
		for (int i = 0 ; i < m_Layers.GetSize() ; i++ )
		{
			ILayerPtr pLayer = m_Layers[i];
			if (pLayer->GetLayerType()!=FeatureLayer)
				continue;
			IFeatureLayerPtr pFeatureLayer = pLayer;
			pFeatureLayer->ClearSelectionSet();
		}
	}

	long CMap::SelectionCount()
	{
		long lCnt = 0;
		for (int i = 0 ; i < m_Layers.GetSize() ; i++ )
		{
			ILayerPtr pLayer = m_Layers[i];
			if (pLayer->GetLayerType()!=FeatureLayer)
				continue;
			IFeatureLayerPtr pFeatureLayer = pLayer;
			lCnt += pFeatureLayer->GetSelection()->Count();
		}
		return lCnt;
	}

}