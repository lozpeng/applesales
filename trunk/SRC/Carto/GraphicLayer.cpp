#include "stdafx.h"
#include "GraphicLayer.h"
#include "MapFrame.h"
#include "IMapSurround.h"
#include "ShapefileWorkspaceFactory.h"
#include "ShapefileWorkspace.h"
#include "ShapefileFeatureClass.h"
using namespace Element;

namespace Carto
{

	static boost::signal<void (Element::IElementPtr pElement)> gCallbackDeleteElement;

	// 标识唯一的MapFrame号
	static long g_lMapFrameID = 0;

	CGraphicLayer::CGraphicLayer()
	{
		m_layerType = GraphicLayer;
	}

	CGraphicLayer::CGraphicLayer(const GEOMETRY::geom::Envelope &envelope)
	{
		m_layerType = GraphicLayer;
		m_envelope = envelope;
	}

	CGraphicLayer::~CGraphicLayer()
	{
	}

	void CGraphicLayer::serialization(SYSTEM::IArchive &ar)
	{
		ILayer::serialization( ar );

		CGraphicsContainer::serialization( ar );

		if(ar.IsRead())
			SetMapFrame();

	}

	void CGraphicLayer::SetMapFrame()
	{
		long lSize = m_vecElements.size();
		for(int i=0; i<lSize; i++)
		{
			Element::IElementPtr pElement = m_vecElements[i];
			
			if(pElement == NULL)
				continue;

			if(pElement->GetType() & Element::ET_MAP_SURROUND_ELEMENT)
			{
				Element::IMapSurround* pSurround = dynamic_cast<Element::IMapSurround*>(pElement.get());
				long mapFrameId = pSurround->GetMapFrameID();
				for(int j=0; j<lSize; j++)
				{
					Element::IElementPtr pElement2 = m_vecElements[j];
					if(pElement2 == NULL)
						continue;
					if(pElement2->GetType() == Element::ET_MAP_FRAME_ELEMENT)
					{
						Element::CMapFrame* pFrm = dynamic_cast<Element::CMapFrame*>(pElement2.get());
						if(pFrm->GetMapFrameID() == mapFrameId)
							pSurround->SetMapFrame(pFrm);
					}
				}
			}
		}
	}
	void CGraphicLayer::Draw(Display::IDisplayPtr pDisplay, DRAW_CONTENT content)
	{
		if (pDisplay == NULL)	
			return;

		//可见性
		if (!m_bVisible)
		{
			return;
		}

		//显示比例尺范围
		if (m_bScaleRange)
		{
			double scaleValue = pDisplay->GetDisplayTransformation().GetScale();

			if (scaleValue < m_dScaleMin)
				return;

			if (scaleValue > m_dScaleMax)
				return;
		}
		if(content == drawElement)
		{
			// 图层绘制	
			Element::IElementPtr pElement = Reset();
			while(pElement)
			{
				Element::ELEMENT_EDIT_MODE editMode = pElement->GetEditMode();
				pElement->SetEditMode(Element::EEM_NO_EDIT);
				pElement->Draw(pDisplay);
				pElement->SetEditMode(editMode);
				pElement = Next();
			}
		}
		else if(content == drawEdit)
		{
			Element::IElementPtr pElement = NULL;
			for(int i=0; i<GetSelectedElementCount(); i++)
			{
				pElement = GetSelectedElement(i);
				pElement->Draw(pDisplay);
			}
		}

		//
		ILayer::Draw(pDisplay, content);
	}

	GEOMETRY::geom::Envelope CGraphicLayer::GetEnvelope()
	{
		return m_envelope;
	}

	void CGraphicLayer::ClearSelectionSet()
	{

	}

	void CGraphicLayer::Select(Geodatabase::CSimpleQuery* query, SELECT_OPTION selectOption)
	{
		Geodatabase::CSpatialQuery *pSpatialQuery =dynamic_cast<Geodatabase::CSpatialQuery*>(query);
		if(pSpatialQuery)
		{
			SpatialSelect(pSpatialQuery,selectOption);
		}
		else
		{
			return;
		}
	}

	void CGraphicLayer::AddElement(Element::IElementPtr pElement)
	{
		/*if(pElement->GetType() & Element::ET_MAP_SURROUND_ELEMENT )
		{
		Element::IMapSurround* pMapSurround = dynamic_cast<Element::IMapSurround*>(pElement.get());
		if(pMapSurround->GetMapFrame())
		pMapSurround->GetMapFrame()->AddMapSurroundElement(pElement);
		}
		else
		{
		if(FindElement(pElement)>-1)
		return ;

		m_vecElements.push_back(pElement);
		}*/

		if(FindElement(pElement)>-1)
			return ;

		if(pElement->GetType() == Element::ET_MAP_FRAME_ELEMENT )
		{
			Element::CMapFrame* pMapFrame = dynamic_cast<Element::CMapFrame*>(pElement.get());
			pMapFrame->SetMapFrameID(g_lMapFrameID);
			g_lMapFrameID++;
		}

		if(FindElement(pElement)>-1)
			return ;

		m_vecElements.push_back(pElement);


		ContainerChangedEvent(pElement);
	}

	void CGraphicLayer::RemoveElement(Element::IElementPtr pElement)
	{
		/*if(pElement->GetType() & Element::ET_MAP_SURROUND_ELEMENT )
		{
		Element::IMapSurround* pMapSurround = dynamic_cast<Element::IMapSurround*>(pElement.get());
		if(pMapSurround->GetMapFrame())
		pMapSurround->GetMapFrame()->RemoveMapSurroundElement(pElement);
		}
		else
		{*/
		std::vector<Element::IElementPtr>::iterator iter = m_vecElements.begin();
		for( ;iter!=m_vecElements.end(); iter++)
		{
			if(*iter == pElement)
			{
				m_vecElements.erase(iter);
				break;
			}
		}
		/*}*/

		//ContainerChangedEvent(pElement);

		gCallbackDeleteElement(pElement);
	}

	void CGraphicLayer::BringForward(Element::IElementPtr pElement)
	{
		/*if(pElement->GetType() & Element::ET_MAP_SURROUND_ELEMENT )
		{
		Element::IMapSurround* pMapSurround = dynamic_cast<Element::IMapSurround*>(pElement.get());
		if(pMapSurround->GetMapFrame())
		pMapSurround->GetMapFrame()->GetMapSurroundContainer()->BringForward(pElement);
		}
		else
		{*/
		std::vector<Element::IElementPtr>::iterator iter = m_vecElements.begin();
		for( ;iter!=m_vecElements.end(); iter++)
		{
			if(*iter == pElement)
				break;
		}

		if(iter != m_vecElements.begin())
		{
			Element::IElementPtr pCur = *iter;
			Element::IElementPtr pFront = *(iter-1);
			*iter = pFront;
			*(iter-1) = pCur;
		}
		/*}*/

	}

	void CGraphicLayer::SendBackward(Element::IElementPtr pElement)
	{
		/*if(pElement->GetType() & Element::ET_MAP_SURROUND_ELEMENT )
		{
		Element::IMapSurround* pMapSurround = dynamic_cast<Element::IMapSurround*>(pElement.get());
		if(pMapSurround->GetMapFrame())
		pMapSurround->GetMapFrame()->GetMapSurroundContainer()->SendBackward(pElement);
		}
		else
		{*/
		std::vector<Element::IElementPtr>::iterator iter = m_vecElements.begin();
		for( ;iter!=m_vecElements.end(); iter++)
		{
			if(*iter == pElement)
				break;
		}

		if(iter != m_vecElements.end())
		{
			Element::IElementPtr pCur = *iter;
			Element::IElementPtr pBack = *(iter+1);
			*iter = pBack;
			*(iter+1) = pCur;
		}
		/*}*/

	}

	void CGraphicLayer::BringToFront(Element::IElementPtr pElement)
	{
		/*if(pElement->GetType() & Element::ET_MAP_SURROUND_ELEMENT )
		{
		Element::IMapSurround* pMapSurround = dynamic_cast<Element::IMapSurround*>(pElement.get());
		if(pMapSurround->GetMapFrame())
		pMapSurround->GetMapFrame()->GetMapSurroundContainer()->BringToFront(pElement);
		}
		else
		{*/
		std::vector<Element::IElementPtr>::iterator iter = m_vecElements.begin();
		for( ;iter!=m_vecElements.end(); iter++)
		{
			if(*iter == pElement)
				break;
		}

		if(iter != m_vecElements.begin())
		{
			Element::IElementPtr pCur = *iter;
			for( ;iter != m_vecElements.begin();iter--)
				*iter = *(iter-1);
			*iter = pCur;
		}
		/*}*/
	}

	void CGraphicLayer::SendToBack(Element::IElementPtr pElement)
	{
		/*if(pElement->GetType() & Element::ET_MAP_SURROUND_ELEMENT )
		{
		Element::IMapSurround* pMapSurround = dynamic_cast<Element::IMapSurround*>(pElement.get());
		if(pMapSurround->GetMapFrame())
		pMapSurround->GetMapFrame()->GetMapSurroundContainer()->SendToBack(pElement);
		}
		else
		{*/
		std::vector<Element::IElementPtr>::iterator iter = m_vecElements.begin();
		for( ;iter!=m_vecElements.end(); iter++)
		{
			if(*iter == pElement)
				break;
		}

		if(iter+1 != m_vecElements.end())
		{
			Element::IElementPtr pCur = *iter;
			for( ;(iter+1) != m_vecElements.end();iter++)
				*iter = *(iter+1);
			*iter = pCur;
		}
		/*}*/
	}

	void CGraphicLayer::BringForward(Element::CElementCollection pElements)
	{
		CGraphicsContainer::BringForward(pElements);

	}

	void CGraphicLayer::SendBackward(Element::CElementCollection pElements)
	{
		CGraphicsContainer::SendBackward(pElements);
	}

	void CGraphicLayer::BringToFront(Element::CElementCollection pElements)
	{
		CGraphicsContainer::BringToFront(pElements);

	}

	void CGraphicLayer::SendToBack(Element::CElementCollection pElements)
	{
		CGraphicsContainer::SendToBack(pElements);

	}

	//////////////////////////////////////////////////////////////////////////

	void CGraphicLayer::SpatialSelect(Geodatabase::CSpatialQuery* query, SELECT_OPTION selectOption)
	{
		GEOMETRY::geom::Geometry* pQueryGeo = query->GetGeometry();
		long lSpatialRelation =query->GetSpatialRel();

		//如果是替换已有选择集，先清空选择集
		if(selectOption == SELECT_REPLACE)
		{
			UnselectAllElements();
		}

		//选择
		GEOMETRY::geom::Geometry *pSelbox = pQueryGeo->getEnvelope();
		if(pSelbox->getGeometryTypeId() == GEOMETRY::geom::GEOS_POINT)//点选：选中一个即可
		{
			Element::IElementPtr pElement = Reset(FALSE);
			while(pElement)
			{
				Element::CElementCollection selectedSubElements;
				double dbTolerance = 0.001;//hhzhao 暂时注释掉 query->GetTolerance();

				BOOL bSelfElemSelected = pElement->Select(pQueryGeo, lSpatialRelation, selectedSubElements,dbTolerance);
				if(selectedSubElements.Count())//pElement的附属element被选中
				{
					SelectElements(selectedSubElements);
					break;
				}
				else if(bSelfElemSelected)//pElement自己被选中
				{
					SelectElement(pElement);
					break;
				}			
				else
				{
					pElement = Pre();
				}
			}
		}
		else//其他情况：所有符合条件的均选中
		{
			Element::IElementPtr pElement = Reset(FALSE);
			while(pElement)
			{
				Element::CElementCollection selectedSubElements;
				BOOL bSelfElemSelected = pElement->Select(pQueryGeo, lSpatialRelation, selectedSubElements);
				if(bSelfElemSelected)
				{
					SelectElement(pElement);
				}

				if(selectedSubElements.Count())
				{
					SelectElements(selectedSubElements);
				}

				pElement = Pre();
			}
		}

		if(pSelbox)
		{
			GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pSelbox);
			pSelbox = NULL;
		}
	}


	boost::signals::connection CGraphicLayer::RegisterDeleteElement(boost::function<void (Element::IElementPtr pElement)> fun)
	{
		return gCallbackDeleteElement.connect(fun);
	}

	void CGraphicLayer::SaveElementAsShp(std::string filename,bool bSlected,long drawingType)
	{
		std::string path =filename;
		//得到文件路径
		path =path.substr(0,path.rfind('\\'));

		Geodatabase::IWorkspace *pWorkspace =CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(filename.c_str());
		if(!pWorkspace)
		{
			return;
		}

		Element::ELEMENT_TYPE elementType;

		Geodatabase::FeatureClassDef fdef;
		fdef.hasz =false;

		if (drawingType == 2)
		{
			fdef.lshptype = GEOMETRY::geom::GEOS_POINT;
		}
		else if (drawingType ==1)
		{
			fdef.lshptype = GEOMETRY::geom::GEOS_LINESTRING;
		}
		else
		{
			fdef.lshptype = GEOMETRY::geom::GEOS_POLYGON;
		}

		Geodatabase::IFeatureClassPtr pFeatureClass = NULL;
		pFeatureClass = pWorkspace->OpenFeatureClass(filename.c_str());
		if(pFeatureClass == NULL)
		{
			Geodatabase::CField *pField =new Geodatabase::CField();
			pField->SetType(Geodatabase::FTYPE_LONG);
			pField->SetName("UserID");
			pField->SetLength(12);
			fdef.FieldsDef.push_back(Geodatabase::CFieldPtr(pField));

			pFeatureClass =pWorkspace->CreateFeatureClass(filename.c_str(),fdef);
		}

		if(!pFeatureClass)
		{
			return;
		}

		//开始编辑
		bool srcState = pWorkspace->IsEditing();
		if(srcState== false)
			pWorkspace->StartEdit();

		pWorkspace->StartEditOperation();

		Geodatabase::CFeaturePtr pFeature;

		if (bSlected)
		{
			for (size_t i=0;i<this->GetSelectedElementCount();i++)
			{
				elementType = this->GetSelectedElement(i)->GetType();
				if (drawingType == 2)
				{
					if (elementType!=ELEMENT_TYPE::ET_POINTELEMENT&&elementType!=ELEMENT_TYPE::ET_SIMPLE_POINT_ELEMENT)
					{
						continue;
					}
				}
				else if (drawingType ==1)
				{
					if (elementType!=ELEMENT_TYPE::ET_LINEELEMENT&&elementType!=ELEMENT_TYPE::ET_POLYLINE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_CURVE_ELEMENT&&
						elementType!=ELEMENT_TYPE::ET_BEZIERCURVE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_MEASURE_POLYLINE_ELEMENT)
					{
						continue;
					}
				}
				else
				{
					if (elementType!=ELEMENT_TYPE::ET_FILLELEMENT&&elementType!=ET_FILL_RECTANGLE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_FILL_POLYGON_ELEMENT&&elementType!=ELEMENT_TYPE::ET_FILL_CIRCLE_ELEMENT&&
						elementType!=ELEMENT_TYPE::ET_FILL_ELLIPSE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_MEASURE_POLYGON_ELEMENT)
					{
						continue;
					}
				}
				//产生一个新的要素
				pFeature =pFeatureClass->CreateFeature();
				pFeature->SetShape( this->GetSelectedElement(i)->GetGeometry()->clone());

				//提交要素
				pFeatureClass->AddFeature(pFeature.get());
				//remove
				this->RemoveElement(this->GetSelectedElement(i));
			}
		}
		else
		{
			for (size_t i=0;i<GetElementCount();i++)
			{
				elementType = this->GetElement(i)->GetType();
				if (drawingType == 2)
				{
					if (elementType!=ELEMENT_TYPE::ET_POINTELEMENT&&elementType!=ELEMENT_TYPE::ET_SIMPLE_POINT_ELEMENT)
					{
						continue;
					}
				}
				else if (drawingType ==1)
				{
					if (elementType!=ELEMENT_TYPE::ET_LINEELEMENT&&elementType!=ELEMENT_TYPE::ET_POLYLINE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_CURVE_ELEMENT&&
						elementType!=ELEMENT_TYPE::ET_BEZIERCURVE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_MEASURE_POLYLINE_ELEMENT)
					{
						continue;
					}
				}
				else
				{
					if (elementType!=ELEMENT_TYPE::ET_FILLELEMENT&&elementType!=ELEMENT_TYPE::ET_FILL_RECTANGLE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_FILL_POLYGON_ELEMENT&&elementType!=ELEMENT_TYPE::ET_FILL_CIRCLE_ELEMENT&&
						elementType!=ELEMENT_TYPE::ET_FILL_ELLIPSE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_MEASURE_POLYGON_ELEMENT)
					{
						continue;
					}
				}
				//产生一个新的要素
				pFeature =pFeatureClass->CreateFeature();
				pFeature->SetShape( this->GetElement(i)->GetGeometry()->clone());

				//提交要素
				pFeatureClass->AddFeature(pFeature.get());


			}
			UnselectAllElements();
			//remove
			this->RemoveAllElements();
		}


		pWorkspace->StopEditOperation();
		if(srcState == false)
			pWorkspace->StopEdit(true);
	}

	void CGraphicLayer::SaveElementAsShp(Geodatabase::IFeatureClassPtr pFeatureClass,bool bSlected,long drawingType)
	{

		if(!pFeatureClass)
		{
			return;
		}
		Element::ELEMENT_TYPE elementType;

		Geodatabase::CFeaturePtr pFeature;

		if (bSlected)
		{
			for (size_t i=0;i<this->GetSelectedElementCount();i++)
			{
				elementType = this->GetSelectedElement(i)->GetType();
				if (drawingType == 2)
				{
					if (elementType!=ELEMENT_TYPE::ET_POINTELEMENT&&elementType!=ELEMENT_TYPE::ET_SIMPLE_POINT_ELEMENT)
					{
						continue;
					}
				}
				else if (drawingType ==1)
				{
					if (elementType!=ELEMENT_TYPE::ET_LINEELEMENT&&elementType!=ELEMENT_TYPE::ET_POLYLINE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_CURVE_ELEMENT&&
						elementType!=ELEMENT_TYPE::ET_BEZIERCURVE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_MEASURE_POLYLINE_ELEMENT)
					{
						continue;
					}
				}
				else
				{
					if (elementType!=ELEMENT_TYPE::ET_FILLELEMENT&&elementType!=ET_FILL_RECTANGLE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_FILL_POLYGON_ELEMENT&&
						elementType!=ELEMENT_TYPE::ET_FILL_CIRCLE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_FILL_ELLIPSE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_MEASURE_POLYGON_ELEMENT)
					{
						continue;
					}
				}
				//产生一个新的要素
				pFeature =pFeatureClass->CreateFeature();
				pFeature->SetShape( this->GetSelectedElement(i)->GetGeometry()->clone());

				//提交要素
				pFeatureClass->AddFeature(pFeature.get());

			}


			//remove
			for (size_t i=0;i<this->GetSelectedElementCount();i++)
			{
				this->RemoveElement(this->GetSelectedElement(i));
			}
			UnselectAllElements();
		}
		else
		{
			for (size_t i=0;i<GetElementCount();i++)
			{
				elementType = this->GetElement(i)->GetType();
				if (drawingType == 2)
				{
					if (elementType!=ELEMENT_TYPE::ET_POINTELEMENT&&elementType!=ELEMENT_TYPE::ET_SIMPLE_POINT_ELEMENT)
					{
						continue;
					}
				}
				else if (drawingType ==1)
				{
					if (elementType!=ELEMENT_TYPE::ET_LINEELEMENT&&elementType!=ELEMENT_TYPE::ET_POLYLINE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_CURVE_ELEMENT&&
						elementType!=ELEMENT_TYPE::ET_BEZIERCURVE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_MEASURE_POLYLINE_ELEMENT)
					{
						continue;
					}
				}
				else
				{
					if (elementType!=ELEMENT_TYPE::ET_FILLELEMENT&&elementType!=ELEMENT_TYPE::ET_FILL_RECTANGLE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_FILL_POLYGON_ELEMENT&&
						elementType!=ELEMENT_TYPE::ET_FILL_CIRCLE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_FILL_ELLIPSE_ELEMENT&&elementType!=ELEMENT_TYPE::ET_MEASURE_POLYGON_ELEMENT)
					{
						continue;
					}
				}
				//产生一个新的要素
				pFeature =pFeatureClass->CreateFeature();
				pFeature->SetShape( this->GetElement(i)->GetGeometry()->clone());

				//提交要素
				pFeatureClass->AddFeature(pFeature.get());

			}
			UnselectAllElements();
			//remove
			this->RemoveAllElements();
		}

	}
	//增量导出、导入
	const std::string node_Incremental ="incremental";
	const std::string node_CaptureTime ="CaptureTime";
	const std::string node_PolygonFeature ="PolygonFeature";
	const std::string node_LineFeature ="LineFeature";
	const std::string node_PointFeature ="PointFeature";
	const std::string node_FlagAdd ="Add";
	const std::string node_FlagDelete ="Delete";
	const std::string node_FlagAttribute ="Attribute";
	const std::string node_FlagModify ="Modify";
	const std::string node_coordinate = "coordinate";
	const std::string node_FeatID = "FeatID";

	SYSTEM::XMLConfigurationPtr ipIncremenalFile = NULL;


	void CGraphicLayer::IncrementalExport(std::string incrementalFile,std::string tagertLayerName_P,std::string tagertLayerName_L,std::string tagertLayerName_A,bool bExportAll)
	{

		SYSTEM::CXMLConfiguration::Initialize();
		try
		{
			if(ipIncremenalFile == NULL)
				ipIncremenalFile = new SYSTEM::CXMLConfiguration;
			bool bFlagOpen = ipIncremenalFile->Open(incrementalFile);
			if (!bFlagOpen||ipIncremenalFile->GetName() != node_Incremental)
				ipIncremenalFile->Create(incrementalFile,"UTF-8",node_Incremental);

			//增加时间节点
			SYSTEM::IConfigItemPtr ipCurTimeNode = ipIncremenalFile->GetChildByName(node_CaptureTime.c_str());
			if (ipCurTimeNode == NULL)
			{
				ipCurTimeNode = ipIncremenalFile->AddChildNode(node_CaptureTime.c_str());
			}
			time_t t = time(0);    
			char szCurTime[64];    
			strftime( szCurTime, sizeof(szCurTime), "%Y-%m-%d %X",localtime(&t));    
			ipCurTimeNode->SetValue(szCurTime);
			char destBuf[1024];
			std::string layerName = "polygonlayer";
			Element::ELEMENT_TYPE elementType;
			

			//
			
			std::vector<Element::IElementPtr>  removeList;
			std::string strFeatureType = node_PolygonFeature;
			if(bExportAll)
			{
				for (size_t i=0;i<GetElementCount();i++)
				{
					elementType = this->GetElement(i)->GetType();

					if (elementType==ELEMENT_TYPE::ET_POINTELEMENT||elementType==ELEMENT_TYPE::ET_SIMPLE_POINT_ELEMENT)
					{
						if(tagertLayerName_P.empty()||tagertLayerName_P.length()<1)
							continue;
						strFeatureType = node_PointFeature;
						layerName = tagertLayerName_P;

					}
					else if (elementType==ET_LINEELEMENT||elementType==ET_POLYLINE_ELEMENT||elementType==ET_CURVE_ELEMENT||elementType==ET_BEZIERCURVE_ELEMENT)
					{
						if(tagertLayerName_L.empty()||tagertLayerName_L.length()<1)
							continue;
						strFeatureType = node_LineFeature;
						layerName = tagertLayerName_L;

					}

					else if (elementType==ET_FILLELEMENT||elementType==ET_FILL_RECTANGLE_ELEMENT||elementType==ET_FILL_POLYGON_ELEMENT
						||elementType==ET_FILL_CIRCLE_ELEMENT||elementType==ET_FILL_ELLIPSE_ELEMENT)
					{
						if(tagertLayerName_A.empty()||tagertLayerName_A.length()<1)
							continue;
						strFeatureType = node_PolygonFeature;
						layerName = tagertLayerName_A;
					}

					//类型
					SYSTEM::IConfigItemPtr ipFeatureTypeNode = ipIncremenalFile->GetChildByName(strFeatureType.c_str());
					if (ipFeatureTypeNode == NULL)
					{
						ipFeatureTypeNode = ipIncremenalFile->AddChildNode(strFeatureType.c_str());
					}

					//名称
					SYSTEM::IConfigItemPtr ipFeatureNameNode = ipFeatureTypeNode->GetChildByName(layerName.c_str());
					if (ipFeatureNameNode == NULL)
					{
						ipFeatureNameNode = ipFeatureTypeNode->AddChildNode(layerName.c_str());
					}

					SYSTEM::IConfigItemPtr ipFlagAddNode  = ipFeatureNameNode->AddChildNode(node_FlagAdd.c_str());

					//坐标值
					SYSTEM::IConfigItemPtr   ipCoorNode= ipFlagAddNode->AddChildNode(node_coordinate.c_str());
					GEOMETRY::geom::Geometry* pgeometry = this->GetElement(i)->GetGeometry()->clone();
					CoordinateSequence* pCoordinateSequence = pgeometry->getCoordinates();
					std::string strCoordinate;

					for (int k = 0;k<pCoordinateSequence->getSize();k++)
					{
						double dx = pCoordinateSequence->getX(k);
						double dy = pCoordinateSequence->getY(k);
						gcvt(dx,10,destBuf);
						strCoordinate.append(destBuf);
						strCoordinate.append(",");
						gcvt(dy,10,destBuf);
						strCoordinate.append(destBuf);
						if(k<pCoordinateSequence->getSize()-1)
							strCoordinate.append(" ");
					}
					ipCoorNode->SetValue(strCoordinate.c_str());
					//
					removeList.push_back(GetElement(i));
					
				}

				//remove
				for(int j = 0;j< removeList.size();j++)
				{
					this->RemoveElement(removeList[j]);
				}
				UnselectAllElements();

			}
			else
			{

				for (size_t i=0;i<this->GetSelectedElementCount();i++)
				{
					elementType = this->GetSelectedElement(i)->GetType();

					if (elementType==ELEMENT_TYPE::ET_POINTELEMENT||elementType==ELEMENT_TYPE::ET_SIMPLE_POINT_ELEMENT)
					{
						if(tagertLayerName_P.empty()||tagertLayerName_P.length()<1)
							continue;
						strFeatureType = node_PointFeature;
						layerName = tagertLayerName_P;

					}
					else if (elementType==ET_LINEELEMENT||elementType==ET_POLYLINE_ELEMENT||elementType==ET_CURVE_ELEMENT||elementType==ET_BEZIERCURVE_ELEMENT)
					{
						if(tagertLayerName_L.empty()||tagertLayerName_L.length()<1)
							continue;
						strFeatureType = node_LineFeature;
						layerName = tagertLayerName_L;

					}

					else if (elementType==ET_FILLELEMENT||elementType==ET_FILL_RECTANGLE_ELEMENT||elementType==ET_FILL_POLYGON_ELEMENT
						||elementType==ET_FILL_CIRCLE_ELEMENT||elementType==ET_FILL_ELLIPSE_ELEMENT)
					{
						if(tagertLayerName_A.empty()||tagertLayerName_A.length()<1)
							continue;
						strFeatureType = node_PolygonFeature;
						layerName = tagertLayerName_A;
					}

					//类型
					SYSTEM::IConfigItemPtr ipFeatureTypeNode = ipIncremenalFile->GetChildByName(strFeatureType.c_str());
					if (ipFeatureTypeNode == NULL)
					{
						ipFeatureTypeNode = ipIncremenalFile->AddChildNode(strFeatureType.c_str());
					}

					//名称
					SYSTEM::IConfigItemPtr ipFeatureNameNode = ipFeatureTypeNode->GetChildByName(layerName.c_str());
					if (ipFeatureNameNode == NULL)
					{
						ipFeatureNameNode = ipFeatureTypeNode->AddChildNode(layerName.c_str());
					}

					SYSTEM::IConfigItemPtr ipFlagAddNode  = ipFeatureNameNode->AddChildNode(node_FlagAdd.c_str());

					//坐标值
					SYSTEM::IConfigItemPtr   ipCoorNode= ipFlagAddNode->AddChildNode(node_coordinate.c_str());
					GEOMETRY::geom::Geometry* pgeometry = this->GetSelectedElement(i)->GetGeometry()->clone();
					CoordinateSequence* pCoordinateSequence = pgeometry->getCoordinates();
					std::string strCoordinate;

					for (int k = 0;k<pCoordinateSequence->getSize();k++)
					{
						double dx = pCoordinateSequence->getX(k);
						double dy = pCoordinateSequence->getY(k);
						gcvt(dx,10,destBuf);
						strCoordinate.append(destBuf);
						strCoordinate.append(",");
						gcvt(dy,10,destBuf);
						strCoordinate.append(destBuf);
						if(k<pCoordinateSequence->getSize()-1)
							strCoordinate.append(" ");
					}
					ipCoorNode->SetValue(strCoordinate.c_str());

					removeList.push_back(GetSelectedElement(i));
				}

				//remove
								//remove
				for(int j = 0;j< removeList.size();j++)
				{
					this->RemoveElement(removeList[j]);
				}
				UnselectAllElements();
			}

			ipIncremenalFile->Save();
		}
		catch(...)
		{
			return ;
		}

	}

}