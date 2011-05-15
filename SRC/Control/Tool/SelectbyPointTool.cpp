#include "stdafx.h"
#include "SelectbyPointTool.h"
#include "Control.h"


extern CControlApp theApp;
namespace Control
{


static CSelectbyPointTool gSelectbyPointTool;

CSelectbyPointTool::CSelectbyPointTool() :ISelectFeatureTool("SelectbyPoint")
{
	

}

CSelectbyPointTool::~CSelectbyPointTool()
{
	
}

void CSelectbyPointTool::Initialize(Framework::IUIObject *pTargetControl)
{
	ITool::Initialize(pTargetControl);




	//��ȡ���ͼ�ؼ�
	m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
	if(!m_pMapCtrl)
		return;

	//���ù������
	m_pMapCtrl->SetCursor(NULL);


}

void CSelectbyPointTool::LButtonDownEvent (UINT nFlags, CPoint point)
{
	//��ȡ���ͼ�ؼ�
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;
	m_pMapCtrl = pMapCtrl;
	//��ȡ�����
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;


	CRectTracker selectBox = CRectTracker(CRect(0,0,0,0),
		CRectTracker::solidLine +
		CRectTracker::resizeOutside );

	selectBox.m_sizeMin = 0;

	bool selected = selectBox.TrackRubberBand(dynamic_cast<CWnd*>(m_pMapCtrl), point, TRUE );

	CRect rect = selectBox.m_rect;
	rect.NormalizeRect();

	if( ( rect.BottomRight().x - rect.TopLeft().x ) < 10 &&
		( rect.BottomRight().y - rect.TopLeft().y ) < 10 )
		selected = false;


	//����ѡ��
	if( selected == true )
	{
		GEOMETRY::geom::Envelope envelop;
		DIS_RECT disrect;
		disrect.left = rect.left;
		disrect.right = rect.right;
		disrect.top = rect.top;
		disrect.bottom = rect.bottom;
		pMap->GetDisplay()->GetDisplayTransformation().TransformToGeo(disrect,&envelop);

		//����һ�����ڲ�ѯ�Ķ����

		Geodatabase::CSpatialQuery queryfilter;




		//����һ���ռ��ѯ����
		GEOMETRY::geom::Geometry *pGeometry =GeometryFactory::getDefaultInstance()->toGeometry(&envelop);
		queryfilter.SetGeometry(pGeometry);
		queryfilter.SetSpatialRel(Geodatabase::SpatialRelIntersects);

		ISelectFeatureTool::Select(&queryfilter);

	}
	else
	{
		//��ѡ
		GEOMETRY::geom::Envelope envelop;
		DIS_RECT rect;
		rect.left =point.x -m_SnapTol;
		rect.right =point.x+m_SnapTol;
		rect.top =point.y -m_SnapTol;
		rect.bottom =point.y+m_SnapTol;

		pMap->GetDisplay()->GetDisplayTransformation().TransformToGeo(rect,&envelop);
		//����һ�����ڲ�ѯ�Ķ����

		Geodatabase::CSpatialQuery queryfilter;


		//����һ���ռ��ѯ����
		GEOMETRY::geom::Geometry *pGeometry =GeometryFactory::getDefaultInstance()->toGeometry(&envelop);
		queryfilter.SetGeometry(pGeometry);
		queryfilter.SetSpatialRel(Geodatabase::SpatialRelIntersects);

		ISelectFeatureTool::Select(&queryfilter);
	}
	
}



}