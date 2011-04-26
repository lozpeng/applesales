#include "stdafx.h"
#include "FeatureInfoTool.h"
#include "IMapCtrl.h"
#include "DlgFeatureInfo.h"
#include "SpatialQuery.h"
#include "DllResource.h"
#include <geometry/geom/LinearRing.h>
#include <geometry/geom/Polygon.h>
#include "Editor.h"
extern CEditorApp theApp;

namespace Editor
{
	 int  CFeatureInfoTool::m_SnapTol =3;

	static CFeatureInfoTool gFeatureInfoTool;

	CFeatureInfoTool::CFeatureInfoTool():ITool("FeatureInfoTool")
	{
		m_dlg =NULL;
	}

	CFeatureInfoTool::~CFeatureInfoTool()
	{
		if(m_dlg)
			delete m_dlg;
		m_dlg = NULL;
	}

	//��ʼ��
	void CFeatureInfoTool::Initialize(Framework::IUIObject *pTargetControl)
	{
		ITool::Initialize(pTargetControl);
		//��ʼ�����
		if(cursorNormal == NULL)
			cursorNormal =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_Arrow));
		//��ȡ���ͼ�ؼ�
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return ;

		pMapCtrl->SetCursor(cursorNormal);
	
	}
	void CFeatureInfoTool::LButtonDownEvent(UINT nFlags, CPoint point)
	{

		//��ȡ���ͼ�ؼ�
		Framework::IMapCtrl *pMapCtrl = Framework::IMapCtrl::GetActiveMapCtrl();
		if(!pMapCtrl)
			return;

		//��ȡ�����
		Carto::CMapPtr pMap = pMapCtrl->GetMap();
		if(!pMap)
			return;

		CRectTracker selectBox = CRectTracker(CRect(0,0,0,0),
			CRectTracker::solidLine +
			CRectTracker::resizeOutside );

		selectBox.m_sizeMin = 0;

		bool selected = selectBox.TrackRubberBand(dynamic_cast<CWnd*>(pMapCtrl), point );

		CRect rect = selectBox.m_rect;
		rect.NormalizeRect();

		if( ( rect.BottomRight().x - rect.TopLeft().x ) < 10 &&
			( rect.BottomRight().y - rect.TopLeft().y ) < 10 )
			selected = false;

		GEOMETRY::geom::Envelope envelop;

		//����ѡ��
		if( selected == false )
		{
			//��ѡ
			rect.left =point.x -m_SnapTol;
			rect.right =point.x+m_SnapTol;
			rect.top =point.y -m_SnapTol;
			rect.bottom =point.y+m_SnapTol;
		}


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

			pLayer->Select(&queryfilter,Carto::SELECT_REPLACE);

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
			m_dlg->Create();
			CRect rect;
			m_dlg->GetWindowRect(&rect);
			m_dlg->SetWindowPos(0,400,400,rect.Width(),rect.Height(),0);
			m_dlg->SetMap(pMap.get());
			m_dlg->m_pMapCtrl = pMapCtrl;
			m_dlg->Refresh();

		}
	}



}