#include "stdafx.h"
#include "LineMeasureTool.h"
#include "Control.h"


extern CControlApp theApp;
namespace Control
{
	static CLineMeasureTool gLineMeasureTool;

	CLineMeasureTool::CLineMeasureTool() : IDrawElementTool("LineMeasureTool")
	{
		m_pPolyline.reset();
		m_nLastVertixId = 0;
		m_hCursor =NULL;

		b_CanDelete = false;
		b_InSketch = false;

		m_DelPolyline= NULL;
	}


	CLineMeasureTool::~CLineMeasureTool()
	{
		if(m_hCursor)
		{
			DeleteObject( m_hCursor );
		}
		if(m_hHandCursor)
		{
			DeleteObject( m_hHandCursor );
		}
	}

	void CLineMeasureTool::Initialize(Framework::IUIObject *pTargetControl)
	{
		IDrawElementTool::Initialize(pTargetControl);

		//初始化光标
		//if(m_hCursor==NULL)
		{
			m_hCursor =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_Measure) );
			m_hHandCursor=::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_HAND) );
		}


		//获取活动地图控件
		m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
		if(!m_pMapCtrl)
			return;

		//设置光标类型
		m_pMapCtrl->SetCursor(m_hCursor);
	}
	void CLineMeasureTool::LButtonDownEvent (UINT nFlags, CPoint point)
	{
		IDrawElementTool::LButtonDownEvent (nFlags, point);

		//获取活动地区
		Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
		if(!pDisplay)
			return;

		if(b_CanDelete)
		{
			if(m_DelPolyline)
				m_pMap->GetGraphicLayer()->RemoveElement(m_DelPolyline);
			b_CanDelete= false;

			m_pMapCtrl->SetCursor(m_hCursor);
			
			//更新绘制
			m_pMapCtrl->UpdateControl((DrawContent)(drawAll));
		}
		else
		{
			b_InSketch = true;
			//displaytoGeo
			GEOMETRY::geom::Coordinate coorCur;
			pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(cPtStart.x, cPtStart.y, coorCur);

			if(!m_pPolyline)//创建一个矩形图元
			{
				m_pPolyline.reset(new Element::CPolylineMeasureElement(coorCur));

				m_pPolyline->SetEditMode(Element::EEM_ONDRAW);

				m_nLastVertixId = 1;
			}
			else //更新矩形角点坐标
			{	
				if(m_nLastVertixId==1)
				{
					m_pPolyline->MoveVertixTo( m_nLastVertixId, coorCur);
					m_pPolyline->AddVertix( coorCur);
					m_nLastVertixId++;
				}
				else
				{
					m_pPolyline->AddVertix( coorCur);
					m_nLastVertixId++;
				}
			}
		}
	}

	void CLineMeasureTool::MouseMoveEvent (UINT nFlags, CPoint point)
	{

		IDrawElementTool::MouseMoveEvent (nFlags, point);

		if(point.x == cPtStart.x || point.y == cPtStart.y)
			return;


		//获取活动地区
		Display::IDisplayPtr pDisplay = m_pMap->GetDisplay();
		if(!pDisplay)
			return;

		//displaytoGeo
		GEOMETRY::geom::Coordinate coorCur;
		pDisplay->GetDisplayTransformation().ConvertDisplayToGeo(point.x, point.y, coorCur);

		if(b_InSketch)
		{
			if(!m_pPolyline)
				return;

			m_pPolyline->MoveVertixTo( m_nLastVertixId, coorCur);

			//更新绘制
			pDisplay->SetDrawBuffer(drawEdit);
			pDisplay->DrawBackgroud();
			m_pPolyline->Draw(pDisplay);
			m_pMapCtrl->RefreshScreen();
		}
		else
		{

			//找到可以被删除的量测对象

			bool flagSelected= false;
			GEOMETRY::geom::Envelope viewEnvelope = m_pMap->GetViewEnvelope();
			for (size_t i=0;i<m_pMap->GetGraphicLayer()->GetElementCount();i++)
			{
				Element::ELEMENT_TYPE elementType = m_pMap->GetGraphicLayer()->GetElement(i)->GetType();
				if(elementType == Element::ELEMENT_TYPE::ET_MEASURE_POLYLINE_ELEMENT)
				{
					GEOMETRY::geom::Envelope eleEnvelope = m_pMap->GetGraphicLayer()->GetElement(i)->GetEnvelope();
					bool bIntersect = eleEnvelope.intersects(viewEnvelope);
					if(bIntersect)
					{
						GEOMETRY::geom::LineString* pLineString = (GEOMETRY::geom::LineString*)m_pMap->GetGraphicLayer()->GetElement(i)->GetGeometry();
						const GEOMETRY::geom::CoordinateSequence *pCoors = pLineString->getCoordinatesRO();
						GEOMETRY::geom::Coordinate pToPoint;

						double dbExpand = pDisplay->GetDisplayTransformation().TransformToGeo(6);
						double dbOffset = pDisplay->GetDisplayTransformation().TransformToGeo(-12);
						pToPoint = pCoors->getAt(pCoors->getSize()-1);

						GEOMETRY::geom::Envelope textEnvS(pToPoint);
						textEnvS.expandBy(dbExpand);
						textEnvS.translate(dbOffset,-dbOffset);

						bIntersect = textEnvS.intersects(coorCur);
						if(bIntersect)
						{
							flagSelected= true;
							b_CanDelete= true;
							m_DelPolyline = m_pMap->GetGraphicLayer()->GetElement(i);
							//设置光标类型
							m_pMapCtrl->SetCursor(m_hHandCursor);
							
							break;
						}

					}
				}
			}

			if(flagSelected==false)
			{
				m_DelPolyline= NULL;
				b_CanDelete= false;
				//设置光标类型
				m_pMapCtrl->SetCursor(m_hCursor);
				
			}

		}
	}

	void CLineMeasureTool::LButtonUpEvent (UINT nFlags, CPoint point)
	{
		IDrawElementTool::LButtonUpEvent(nFlags, point);
	}

	void CLineMeasureTool::LButtonDblClkEvent (UINT nFlags, CPoint point)
	{
		if(!m_pPolyline)
			return;

		m_pPolyline->RemoveVertix(m_nLastVertixId);
		m_nLastVertixId--;

		if (m_nLastVertixId >= 2  )
		{

			m_pMap->GetGraphicLayer()->AddElement(m_pPolyline);
			//m_pMap->GetGraphicLayer()->SelectElement(m_pPolyline);	
		}

		m_pPolyline->bDrawCloseButton= true;
		m_pPolyline.reset();

		//更新绘制
		m_pMapCtrl->UpdateControl((DrawContent)(drawElement));

		ReleaseCapture();

		b_InSketch = false;
		//IDrawElementTool::LButtonDblClkEvent(nFlags, point);

	}
}