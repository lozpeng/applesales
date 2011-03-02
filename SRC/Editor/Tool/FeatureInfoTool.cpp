#include "stdafx.h"
#include "ActionFeatureInfo.h"
#include "IMapCtrl.h"
#include "DlgFeatureInfo.h"
#include "SpatialQuery.h"
#include "EditorRes.h"
#include <geometry/geom/LinearRing.h>
#include <geometry/geom/Polygon.h>


namespace otEditor
{
static CActionFeatureInfo gActionFeatureInfo;

CActionFeatureInfo::CActionFeatureInfo():IAction("ActionFeatureInfo")
{
    RegisterAction("ActionFeatureInfo", this);

	m_dlg =NULL;
}

CActionFeatureInfo::~CActionFeatureInfo()
{
	if(m_dlg)
		delete m_dlg;
	m_dlg = NULL;
}

void CActionFeatureInfo::Triger()
{
	//��ȡ���ͼ�ؼ�
	otFramework::IMapCtrl *pMapCtrl = otFramework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//���ù������
	pMapCtrl->SetCursorType(cursorNormal);
}

void CActionFeatureInfo::LButtonUpEvent(UINT nFlags, CPoint point)
{

	//��ȡ���ͼ�ؼ�
	otFramework::IMapCtrl *pMapCtrl = otFramework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//��ȡ�����
	otCarto::CGeoMapPtr pMap = pMapCtrl->GetActiveMap();
	if(!pMap)
		return;


	TT_GEOMETRY::geom::Envelope envelop;
	DIS_RECT rect;
	rect.left =point.x -3;
	rect.right =point.x+3;
	rect.top =point.y -3;
	rect.bottom =point.y+3;

	pMap->GetDisplay()->GetDisplayTransformation().TransformToGeo(rect,&envelop);
	//����һ�����ڲ�ѯ�Ķ����

	GeodataModel::CSpatialQuery queryfilter;


	//����һ���ռ��ѯ����
	TT_GEOMETRY::geom::Geometry *pGeometry =GeometryFactory::getDefaultInstance()->toGeometry(&envelop);
	queryfilter.SetGeometry(pGeometry);
	queryfilter.SetSpatialRel(GeodataModel::SpatialRelIntersects);


	otCarto::CLayerArray &layers =pMap->GetLayers();

	otCarto::ILayerPtr pLayer;
	long FeatureLayernum=0;
	for(int i=0;i<layers.GetSize();i++)
	{
		pLayer =layers.GetAt(i);
		if(!pLayer->GetVisible())
		{
			continue;
		}
		if(pLayer->GetLayerType()!=otCarto::eFeatureLayer)
		{
			continue;
		}

		pLayer->Select(&queryfilter,otCarto::TSELECT_REPLACE);

		FeatureLayernum++;


	}

	if(FeatureLayernum==0)
	{
		return;
	}
	pMapCtrl->UpdateControl(drawGeoSelection);

    CDllResource hdll;
	if( NULL != m_dlg )
	{
		if( !IsWindow( m_dlg->m_hWnd ) )
		{
			m_dlg->Create( );			
		}
		m_dlg->SetMap(pMap.get());
		m_dlg->Refresh();
		m_dlg->ShowWindow(SW_SHOW);
	}
	else
	{
		m_dlg = new CDlgFeatureInfo;
		if( NULL == m_dlg )
			return;
		m_dlg->Create( );
		m_dlg->SetMap(pMap.get());
		m_dlg->Refresh();

	}
}



}