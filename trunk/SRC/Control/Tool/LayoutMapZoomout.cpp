#include "stdafx.h"
#include "LayoutMapZoomout.h"
#include "IMapCtrl.h"
#include "MapFrame.h"

#include "Control.h"

extern CControlApp theApp;

namespace Control
{

	static CLayoutMapZoomout gActionLayoutMapZoomout;

	CLayoutMapZoomout::CLayoutMapZoomout() : ITool("Layout_Map_ZoomOut")
	{
		m_hCursor = NULL;
	}

	CLayoutMapZoomout::~CLayoutMapZoomout()
	{

	}

	void CLayoutMapZoomout::Initialize(Framework::IUIObject *pTargetControl)
	{
		ITool::Initialize(pTargetControl);

		//初始化光标
		if(m_hCursor==NULL)
		{
			m_hCursor =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_ZOOMOUT) );
		}

		//获取活动地图控件
		m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);
		if(!m_pLayoutCtrl)
			return;

		//设置光标类型
		m_pLayoutCtrl->SetCursor(m_hCursor);


	}

	void CLayoutMapZoomout::LButtonDownEvent (UINT nFlags, CPoint point)
	{
		//获取活动地图控件
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		Carto::CMapPtr pMap = pMapCtrl->GetMap();
		if(!pMap)
			return;

		Framework::ILayoutCtrl *pLayoutCtrl = Framework::ILayoutCtrl::GetActiveLayoutCtrl();
		if(!pLayoutCtrl)
			return;

		Carto::CPageLayoutPtr pPageLayout = pLayoutCtrl->GetPageLayout();
		if(!pPageLayout)
			return;

		Element::CMapFrame* pMapFrame = NULL;
		Element::IElementPtr pElement = pPageLayout->GetGraphicLayer()->Reset();
		while(pElement)
		{
			if(pElement->GetType() != Element::ET_MAP_FRAME_ELEMENT)
			{
				pElement = pPageLayout->GetGraphicLayer()->Next();
				continue;
			}

			Element::CMapFrame* pTmpMapFrm = dynamic_cast<Element::CMapFrame*>(pElement.get());
			if(pTmpMapFrm->GetMap() != pMap)
			{
				pElement = pPageLayout->GetGraphicLayer()->Next();
				continue;
			}

			pMapFrame = pTmpMapFrm;
			break;
		}

		if(!pMapFrame)
			return;

		DIS_RECT* mapFrameBound = NULL;
		CreateDisplayRect(mapFrameBound);
		mapFrameBound = pPageLayout->GetDisplay()->GetDisplayTransformation().TransformToDisplay(pMapFrame->GetGeometry()->getEnvelopeInternal());

		//Selection Box
		CRectTracker selectBox = CRectTracker(CRect(0,0,0,0),
			CRectTracker::solidLine +
			CRectTracker::resizeOutside );

		selectBox.m_sizeMin = 0;
		bool selected = selectBox.TrackRubberBand(dynamic_cast<CWnd*>(pLayoutCtrl), point, FALSE );

		CRect rect = selectBox.m_rect;
		rect.NormalizeRect();
		if( ( rect.BottomRight().x - rect.TopLeft().x ) < 10 &&
			( rect.BottomRight().y - rect.TopLeft().y ) < 10 )
			selected = false;


		if( selected == true )
		{
			GEOMETRY::geom::Envelope envelop;

			pMap->GetDisplay()->GetDisplayTransformation().GetGeoBound(envelop);

			long lWidth = rect.Width();
			long lHeight = rect.Height();

			double rx = envelop.getWidth()/ lWidth;
			double ry = envelop.getHeight()/ lHeight;

			double dbScale = (rx > ry) ? rx : ry;

			pMap->GetDisplay()->GetDisplayTransformation().ZoomToFixScale(dbScale);

			CRect viewRect =pMap->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();

			double dx=(rect.CenterPoint().x - mapFrameBound->left - viewRect.CenterPoint().x)*dbScale;
			double dy=(viewRect.CenterPoint().y - (rect.CenterPoint().y - mapFrameBound->top))*dbScale;

			pMap->GetDisplay()->GetDisplayTransformation().MoveViewBound(dx,dy);

		}
		else
		{
			double geoCenterX, geoCenterY;
			long x,y;
			x = point.x - mapFrameBound->left;
			y = point.y - mapFrameBound->top;
			pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(x,y,geoCenterX, geoCenterY);
			pMap->GetDisplay()->GetDisplayTransformation().SetGeoCenterX(geoCenterX);
			pMap->GetDisplay()->GetDisplayTransformation().SetGeoCenterY(geoCenterY);
			pMap->GetDisplay()->GetDisplayTransformation().ZoomViewPosScale(1.5);	
		}

		GEOMETRY::geom::Envelope viewGeo;
		pMap->GetDisplay()->GetDisplayTransformation().GetGeoBound(viewGeo);
		pMap->SetViewEnvelope(viewGeo);


		FreeDisplayObj(mapFrameBound);
		pLayoutCtrl->UpdateControl();	
	}


} //namespace otMap