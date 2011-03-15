#include "stdafx.h"
#include "GraphicLayer.h"
#include "MapFrame.h"
#include "IMapSurround.h"
#include "ShapefileWorkspaceFactory.h"
#include "ShapefileWorkspace.h"
#include "ShapefileFeatureClass.h"

namespace Carto
{

	static boost::signal<void (Element::IElementPtr pElement)> gCallbackDeleteElement;

	// ��ʶΨһ��MapFrame��
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
			if(pElement->GetType() & Element::ET_MAP_SURROUND_ELEMENT)
			{
				Element::IMapSurround* pSurround = dynamic_cast<Element::IMapSurround*>(pElement.get());
				long mapFrameId = pSurround->GetMapFrameID();
				for(int j=0; j<lSize; j++)
				{
					Element::IElementPtr pElement2 = m_vecElements[j];
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
		if (pDisplay == NULL)	////��ά2007.10.23���
			return;

		//�ɼ���
		if (!m_bVisible)
		{
			return;
		}

		//��ʾ�����߷�Χ
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
			// ͼ�����	
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


		ContainerChangedEvent();
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

		ContainerChangedEvent();

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

		//������滻����ѡ�񼯣������ѡ��
		if(selectOption == SELECT_REPLACE)
		{
			UnselectAllElements();
		}

		//ѡ��
		GEOMETRY::geom::Geometry *pSelbox = pQueryGeo->getEnvelope();
		if(pSelbox->getGeometryTypeId() == GEOMETRY::geom::GEOS_POINT)//��ѡ��ѡ��һ������
		{
			Element::IElementPtr pElement = Reset(FALSE);
			while(pElement)
			{
				Element::CElementCollection selectedSubElements;
				double dbTolerance = 0.001;//hhzhao ��ʱע�͵� query->GetTolerance();

				BOOL bSelfElemSelected = pElement->Select(pQueryGeo, lSpatialRelation, selectedSubElements,dbTolerance);
				if(selectedSubElements.Count())//pElement�ĸ���element��ѡ��
				{
					SelectElements(selectedSubElements);
					break;
				}
				else if(bSelfElemSelected)//pElement�Լ���ѡ��
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
		else//������������з��������ľ�ѡ��
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

	void CGraphicLayer::SaveElementAsShp(std::string filename,bool bSlected)
	{
		std::string path =filename;
		//�õ��ļ�·��
		path =path.substr(0,path.rfind('\\'));

		Geodatabase::IWorkspace *pWorkspace =CShapefileWorkspaceFactory::GetInstance()->OpenFromFile(filename.c_str());
		if(!pWorkspace)
		{
			return;
		}

		Geodatabase::FeatureClassDef fdef;
		fdef.hasz =false;
		fdef.lshptype =GEOMETRY::geom::GEOS_POLYGON;
	

		Geodatabase::CField *pField =new Geodatabase::CField();
		pField->SetType(Geodatabase::FTYPE_LONG);
		pField->SetName("UserID");
		pField->SetLength(12);
		fdef.FieldsDef.push_back(Geodatabase::CFieldPtr(pField));

		Geodatabase::IFeatureClassPtr pFeatureClass =pWorkspace->CreateFeatureClass(filename.c_str(),fdef);

		if(!pFeatureClass)
		{
			return;
		}

		//��ʼ�༭
		pWorkspace->StartEdit();
		pWorkspace->StartEditOperation();
		
		Geodatabase::CFeaturePtr pFeature;

		for (size_t i=0;i<GetElementCount();i++)
		{
			//����һ���µ�Ҫ��
			pFeature =pFeatureClass->CreateFeature();
			pFeature->SetShape( this->GetElement(i)->GetGeometry()->clone());
			
			//�ύҪ��
			//pFeatureClass->AddFeature(pFeature.get());
			pFeature->Update();
		}

		pWorkspace->StopEditOperation();
		pWorkspace->StopEdit(true);
	}


}