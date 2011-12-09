#include "stdafx.h"
#include "AreaMeasureTool.h"
#include "Control.h"


extern CControlApp theApp;
namespace Control
{
	static CAreaMeasureTool gAreaMeasureTool;

	CAreaMeasureTool::CAreaMeasureTool() : IDrawElementTool("AreaMeasureTool")
	{
		m_pPolygon.reset();
		m_nLastVertixId = 0;
		m_hCursor =NULL;

		b_CanDelete = false;
		b_InSketch = false;

		m_DelPolygon= NULL;
	}


	CAreaMeasureTool::~CAreaMeasureTool()
	{
		if(m_hHandCursor)
		{
			DeleteObject( m_hHandCursor );
		}
		if(m_hCursor)
		{
			DeleteObject( m_hCursor );
		}
	}

	void CAreaMeasureTool::Initialize(Framework::IUIObject *pTargetControl)
	{
		IDrawElementTool::Initialize(pTargetControl);

		//��ʼ�����
		//if(m_hCursor==NULL)
		{
			m_hCursor =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_Measure) );
			m_hHandCursor=::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_HAND) );
		}


		//��ȡ���ͼ�ؼ�
		m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
		if(!m_pMapCtrl)
			return;

		//���ù������
		m_pMapCtrl->SetCursor(m_hCursor);

	}
	void CAreaMeasureTool::LButtonDownEvent (UINT nFlags, CPoint point)
	{
		IDrawElementTool::LButtonDownEvent (nFlags, point);


		//��ȡ�����
		Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
		if(!pDisplay)
			return;

		if(b_CanDelete)
		{
			if(m_DelPolygon)
				m_pMap->GetGraphicLayer()->RemoveElement(m_DelPolygon);
			b_CanDelete= false;

			m_pMapCtrl->SetCursor(m_hCursor);

			//���»���
			m_pMapCtrl->UpdateControl((DrawContent)(drawAll));
		}
		else
		{

			b_InSketch = true;
			//displaytoGeo
			GEOMETRY::geom::Coordinate coorCur;
			pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(cPtStart.x, cPtStart.y, coorCur);

			if(!m_pPolygon)//����һ������ͼԪ
			{
				m_pPolygon.reset(new Element::CPolygonMeasureElement(coorCur));

				m_pPolygon->SetEditMode(Element::EEM_ONDRAW);

				m_nLastVertixId = 1;
			}
			else //���¾��νǵ�����
			{	
				if(m_nLastVertixId==1)
				{
					m_pPolygon->MoveVertixTo( m_nLastVertixId, coorCur);	
					m_nLastVertixId++;
				}
				else if(m_nLastVertixId==2)
				{
					m_pPolygon->MoveVertixTo( m_nLastVertixId, coorCur);
					m_pPolygon->AddVertix( coorCur);
					m_nLastVertixId++;
				}
				else
				{
					m_pPolygon->AddVertix( coorCur);
					m_nLastVertixId++;
				}
			}
		}
	}

	void CAreaMeasureTool::MouseMoveEvent (UINT nFlags, CPoint point)
	{


		IDrawElementTool::MouseMoveEvent (nFlags, point);

		if(point.x == cPtStart.x || point.y == cPtStart.y)
			return;

		//��ȡ�����
		Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
		if(!pDisplay)
			return;

		//displaytoGeo
		GEOMETRY::geom::Coordinate coorCur;
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(point.x, point.y, coorCur);

		if(b_InSketch)
		{
			if(!m_pPolygon)
				return;

			m_pPolygon->MoveVertixTo( m_nLastVertixId, coorCur);

			//���»���
			pDisplay->SetDrawBuffer(drawEdit);
			pDisplay->DrawBackgroud();
			m_pPolygon->Draw(pDisplay);
			m_pMapCtrl->RefreshScreen();
		}
		else
		{
			//�ҵ����Ա�ɾ�����������

			bool flagSelected= false;
			GEOMETRY::geom::Envelope viewEnvelope = m_pMap->GetViewEnvelope();
			for (size_t i=0;i<m_pMap->GetGraphicLayer()->GetElementCount();i++)
			{
				Element::ELEMENT_TYPE elementType = m_pMap->GetGraphicLayer()->GetElement(i)->GetType();
				if(elementType == Element::ELEMENT_TYPE::ET_MEASURE_POLYGON_ELEMENT)
				{
					GEOMETRY::geom::Envelope eleEnvelope = m_pMap->GetGraphicLayer()->GetElement(i)->GetEnvelope();
					bool bIntersect = eleEnvelope.intersects(viewEnvelope);
					if(bIntersect)
					{
						GEOMETRY::geom::Polygon* pPolygon = (GEOMETRY::geom::Polygon*)m_pMap->GetGraphicLayer()->GetElement(i)->GetGeometry();
						
						const GEOMETRY::geom::CoordinateSequence *pCoors =  pPolygon->getCoordinates();

						if(pCoors->getSize()<3)
							continue;

						GEOMETRY::geom::Coordinate pCentroidPoint;
						pPolygon->getCentroid(pCentroidPoint);

						double dbExpand = pDisplay->GetDisplayTransformation().TransformToGeo(6);
						double dbOffset = pDisplay->GetDisplayTransformation().TransformToGeo(-12);

						GEOMETRY::geom::Envelope textEnvS(pCentroidPoint);
						textEnvS.expandBy(dbExpand);
						textEnvS.translate(dbOffset,-dbOffset);

						bIntersect = textEnvS.intersects(coorCur);
						if(bIntersect)
						{
							flagSelected= true;
							b_CanDelete= true;
							m_DelPolygon = m_pMap->GetGraphicLayer()->GetElement(i);
							//���ù������
							m_pMapCtrl->SetCursor(m_hHandCursor);

							break;
						}

					}
				}
			}

			if(flagSelected==false)
			{
				m_DelPolygon= NULL;
				b_CanDelete= false;
				//���ù������
				m_pMapCtrl->SetCursor(m_hCursor);

			}
		
		}
	}

	void CAreaMeasureTool::LButtonUpEvent (UINT nFlags, CPoint point)
	{
		IDrawElementTool::LButtonUpEvent(nFlags, point);
	}

	void CAreaMeasureTool::LButtonDblClkEvent (UINT nFlags, CPoint point)
	{
		if(!m_pPolygon)
			return;

		m_pPolygon->RemoveVertix(m_nLastVertixId);
		m_nLastVertixId--;

		if (m_nLastVertixId >= 2  )
		{
			m_pMap->GetGraphicLayer()->AddElement(m_pPolygon);
			//m_pMap->GetGraphicLayer()->SelectElement(m_pPolygon);	
		}

		m_pPolygon->bDrawCloseButton = true;
		m_pPolygon.reset();


		//���»���
		m_pMapCtrl->UpdateControl((DrawContent)(drawElement));

		ReleaseCapture();

		b_InSketch = false;
		//IDrawElementTool::LButtonDblClkEvent(nFlags, point);

	}
}