#include "stdafx.h"
#include "FeatureInfoTool.h"
#include "IMapCtrl.h"
//#include "DlgFeatureInfo.h"
#include "SpatialQuery.h"
//#include "EditorRes.h"
#include <geometry/geom/LinearRing.h>
#include <geometry/geom/Polygon.h>


namespace Editor
{
static CActionFeatureInfo gActionFeatureInfo;

CActionFeatureInfo::CActionFeatureInfo():ITool("ActionFeatureInfo")
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
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//���ù������
	pMapCtrl->SetCursorType(cursorNormal);
}

void CActionFeatureInfo::LButtonUpEvent(UINT nFlags, CPoint point)
{

	//��ȡ���ͼ�ؼ�
	Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
	if(!pMapCtrl)
		return;

	//��ȡ�����
	Carto::CMapPtr pMap = pMapCtrl->GetMap();
	if(!pMap)
		return;


	GEOMETRY::geom::Envelope envelop;
	DIS_RECT rect;
	rect.left =point.x -3;
	rect.right =point.x+3;
	rect.top =point.y -3;
	rect.bottom =point.y+3;

	pMap->GetDisplay()->GetDisplayTransformation().TransformToGeo(rect,&envelop);
	//����һ�����ڲ�ѯ�Ķ����

	Geodatabase::CSpatialQuery queryfilter;


	//����һ���ռ��ѯ����
	GEOMETRY::geom::Geometry *pGeometry =GeometryFactory::getDefaultInstance()->toGeometry(&envelop);
	queryfilter.SetGeometry(pGeometry);
	queryfilter.SetSpatialRel(Geodatabase::SpatialRelIntersects);


	Carto::CLayerArray &layers =pMap->GetLayers();

	Carto::ILayerPtr pLayer;
	long FeatureLayernum=0;
	for(int i=0;i<layers.GetSize();i++)
	{
		pLayer =layers.GetAt(i);
		if(!pLayer->GetVisible())
		{
			continue;
		}
		if(pLayer->GetLayerType()!=Carto::FeatureLayer)
		{
			continue;
		}

		pLayer->Select(&queryfilter,Carto::TSELECT_REPLACE);

		FeatureLayernum++;


	}

	if(FeatureLayernum==0)
	{
		return;
	}
	pMapCtrl->UpdateControl(drawGeoSelection);

   // CDllResource hdll;
	if( NULL != m_dlg )
	{
	/*	if( !IsWindow( m_dlg->m_hWnd ) )
		{
			m_dlg->Create( );			
		}
		m_dlg->SetMap(pMap.get());
		m_dlg->Refresh();
		m_dlg->ShowWindow(SW_SHOW);*/
	}
	else
	{
		//m_dlg = new CDlgFeatureInfo;
		//if( NULL == m_dlg )
		//	return;
		//m_dlg->Create( );
		//m_dlg->SetMap(pMap.get());
		//m_dlg->Refresh();

	}
}



}