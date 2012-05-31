#include "stdafx.h"
#include "LayoutZoomOutTool.h"
#include "Control.h"

extern CControlApp theApp;

static CLayoutZoomoutTool glayoutZoomoutTool;




CLayoutZoomoutTool::CLayoutZoomoutTool() : Framework::ITool("LayoutZoomOutTool")
{
	m_hCursor = NULL;
}

CLayoutZoomoutTool::~CLayoutZoomoutTool()
{
	if(m_hCursor)
	{
		DeleteObject( m_hCursor );
	}
}

void CLayoutZoomoutTool::Initialize(Framework::IUIObject *pTargetControl)
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

void CLayoutZoomoutTool::LButtonDownEvent (UINT nFlags, CPoint point)
{
	if(!m_pLayoutCtrl)
		return;


	if(!m_pLayoutCtrl->GetPageLayout())
		return;


	//Selection Box
	CRectTracker selectBox = CRectTracker(CRect(0,0,0,0),
		CRectTracker::solidLine +
		CRectTracker::resizeOutside );

	selectBox.m_sizeMin = 0;

	bool selected = selectBox.TrackRubberBand(dynamic_cast<CWnd*>(m_pLayoutCtrl), point, FALSE );

	CRect rect = selectBox.m_rect;
	rect.NormalizeRect();

	if( ( rect.BottomRight().x - rect.TopLeft().x ) < 10 &&
		( rect.BottomRight().y - rect.TopLeft().y ) < 10 )
		selected = false;

	
	if( selected == true )
	{
		GEOMETRY::geom::Envelope envelop;
		m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().GetGeoBound(envelop);

		long lWidth = rect.Width();
		long lHeight = rect.Height();

		double rx = envelop.getWidth()/ lWidth;
		double ry = envelop.getHeight()/ lHeight;

		double dbScale = (rx > ry) ? rx : ry;

		m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().ZoomToFixScale(dbScale);

		CRect viewRect =m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().GetViewBound().GetRect();

		double dx=(rect.CenterPoint().x-viewRect.CenterPoint().x)*dbScale;
		double dy=(viewRect.CenterPoint().y-rect.CenterPoint().y)*dbScale;

		m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().MoveViewBound(dx,dy);

	}
	else
	{
		double geoCenterX, geoCenterY;
		m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,geoCenterX, geoCenterY);
		m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().SetGeoCenterX(geoCenterX);
		m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().SetGeoCenterY(geoCenterY);
		m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().ZoomViewPosScale(1.5);
	}
	m_pLayoutCtrl->UpdateControl(drawAll);

	
}

