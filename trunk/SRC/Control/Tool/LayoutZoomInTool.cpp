#include "stdafx.h"
#include "LayoutZoominTool.h"
#include "Control.h"

extern CControlApp theApp;

static CLayoutZoominTool glayoutZoominTool;

CLayoutZoominTool::CLayoutZoominTool() : Framework::ITool("LayoutZoomInTool")
{
	m_hCursor = NULL;
}

CLayoutZoominTool::~CLayoutZoominTool()
{
	if(m_hCursor)
	{
		DeleteObject( m_hCursor );
	}
}


void CLayoutZoominTool::Initialize(Framework::IUIObject *pTargetControl)
{
	ITool::Initialize(pTargetControl);

	//初始化光标
	if(m_hCursor==NULL)
	{
		m_hCursor =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_ZOOMIN) );
	}


	//获取活动地图控件
	m_pLayoutCtrl = dynamic_cast<Framework::ILayoutCtrl*>(pTargetControl);
	if(!m_pLayoutCtrl)
		return;

	//设置光标类型
	m_pLayoutCtrl->SetCursor(m_hCursor);


}

void CLayoutZoominTool::LButtonDownEvent (UINT nFlags, CPoint point)
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
		DIS_RECT disrect;
		disrect.left = rect.left;
		disrect.right = rect.right;
		disrect.top = rect.top;
		disrect.bottom = rect.bottom;

		m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().TransformToGeo(disrect,&envelop);
		m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().FitViewBound(envelop,true);

	}
	else
	{
		double geoCenterX, geoCenterY;
		m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,geoCenterX, geoCenterY);
		m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().SetGeoCenterX(geoCenterX);
		m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().SetGeoCenterY(geoCenterY);
		m_pLayoutCtrl->GetPageLayout()->GetDisplay()->GetDisplayTransformation().ZoomViewPosScale(0.667);
	}
	m_pLayoutCtrl->UpdateControl(drawAll);;

	
}

