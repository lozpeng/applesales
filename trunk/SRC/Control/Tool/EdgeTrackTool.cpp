#include "stdafx.h"
#include "EdgeTrackTool.h"
#include "ILayer.h"
namespace Control
{
static CEdgeTrackTool gCEdgeTrackTool;

CEdgeTrackTool::CEdgeTrackTool() : Framework::ITool("EdgeTrackTool")
{
	m_pMapCtrl =NULL;

	m_hCursor =NULL;

	Display::CSimpleFillSymbolPtr pFillSymbol =new Display::CSimpleFillSymbol;
	pFillSymbol->SetDrawFill(false);
	pFillSymbol->SetOutLineWidth(1);
	pFillSymbol->SetOutLineColor(RGB(0,255,0));
	m_pSymbol =pFillSymbol;

	m_lPointNum =0;

	 mg_lSeedBreakCount=20;

	 m_pTempPathPoint=new POINT[500];

	 //����һ��Ĭ�ϻ���
	 m_pSketch =new Display::CGeometrySketch((int)GEOMETRY::geom::GEOS_LINESTRING,false,false);
	 m_pSketch->m_lineSymbol =m_pSymbol;

}

CEdgeTrackTool::~CEdgeTrackTool()
{
	if(m_hCursor)
	{
		DeleteObject( m_hCursor );
	}
	if(m_pTempPathPoint)
	{
		delete []m_pTempPathPoint;
	}
}

void CEdgeTrackTool::Initialize(Framework::IUIObject *pTargetControl)
{
	ITool::Initialize(pTargetControl);


	//��ȡ���ͼ�ؼ�
	m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
	if(!m_pMapCtrl)
		return;

	//���ù������
	m_pMapCtrl->SetCursor(m_hCursor);


}


void CEdgeTrackTool::LButtonDownEvent (UINT nFlags, CPoint point)
{

	//��ȡ���ͼ�ؼ�
	if(!m_pMapCtrl)
		return;

	//��ȡ�����
	Carto::CMapPtr pMap = m_pMapCtrl->GetMap();
	if(!pMap)
		return;

	GEOMETRY::geom::Coordinate coord;
	pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo
		(point.x,point.y,coord.x, coord.y);

    if(!m_pDataset)
	{
		m_seedPoints.clear();

		Carto::CLayerArray &layers =pMap->GetLayers();
		int count =layers.GetSize();
		Carto::ILayerPtr pLayer;
		Geodatabase::IRasterDatasetPtr pDataset;
		GEOMETRY::geom::Envelope extent;
		//ȷ��Ŀ��ͼ������
        for(int i=count-1;i>=0;i--)
		{
            pLayer =layers.GetAt(i);
			if(pLayer->GetLayerType()!=Carto::RasterLayer)
			{
				continue;
			}
			if(!pLayer->GetVisible())
			{
				continue;
			}
			pDataset =pLayer->GetDataObject();
			if(!pDataset)
			{
				continue;
			}
			//�����ѡ�ĵ���ͼ��Χ�ڣ�����Ǵ�ͼ��
			pDataset->GetExtent(&extent);
			if(extent.contains(coord))
			{
				m_pDataset =pDataset;
				break;
			}



		}
		if(!m_pDataset)
		{
			return;
		}
		//��ʼ��
		m_lPointNum =0;
	}

	switch(m_lPointNum)
	{
	case 0:		//��ʼ��
		m_cEdge.SetSeedPoint(coord);
		mp_lSeedPointCount=-1;
		mp_lSeedPointCount++;
		//��¼�����ӵ�
		m_seedPoints.push_back(coord);
		m_lPointNum++;
		break;
	case 1:    //�����������ӵ�
		m_cEdge.SetCurPoint(coord);
		//�õ����ӵ㵽�˵��·��
		m_cEdge.GetOptimalPath(&mp_lPixelTempCount,&m_pTempPathPoint);

        //���϶�·������
		
		GEOMETRY::geom::Coordinate pt;
		for(long i=0;i<mp_lPixelTempCount;i++)
		{
			m_pDataset->PixelToWorld(m_pTempPathPoint[i].x,m_pTempPathPoint[i].y,&pt.x,&pt.y);
			m_pSketch->AddPoint(pt);
		}
		mp_lPixelTempCount=-1;

		m_cEdge.SetSeedPoint(coord);
		m_pSketch->AddPoint(coord);
		//��¼�����ӵ�
		m_seedPoints.push_back(coord);
		mp_lSeedPointCount++;

		m_pMapCtrl->UpdateControl(drawTempObj);
	    
		break;
	}
	


}

void CEdgeTrackTool::MouseMoveEvent(UINT nFlags, CPoint point)
{
	//��ȡ���ͼ�ؼ�
	if(!m_pMapCtrl)
		return;

	//��ȡ�����
	Carto::CMapPtr pMap = m_pMapCtrl->GetMap();
	if(!pMap)
		return;

	GEOMETRY::geom::Coordinate coord;
	pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo
		(point.x,point.y,coord.x, coord.y);

	if( m_lPointNum !=0 )
	{
		

	
		    GEOMETRY::geom::Coordinate pt;
			m_cEdge.SetCurPoint( coord );
			m_cEdge.GetOptimalPath( &mp_lPixelTempCount, &m_pTempPathPoint);

			//�������·�����ȴ��ڽض�·�������¼�����˶�·��
			if(mp_lPixelTempCount > mg_lSeedBreakCount + mg_lSeedBreakCount * 0.3)
			{
				for(long i=0;i<mg_lSeedBreakCount;i++)
				{
					m_pDataset->PixelToWorld(m_pTempPathPoint[i].x,m_pTempPathPoint[i].y,&pt.x,&pt.y);
					m_pSketch->AddPoint(pt);
				}
				
				m_cEdge.SetSeedPoint(pt);
				//��¼�����ӵ�
				m_seedPoints.push_back(pt);
				mp_lSeedPointCount++;

				mp_lSeedPointCount++;
			}

			mg_mouseLocation = coord;
			
			m_pMapCtrl->UpdateControl(drawTempObj);
			
		
	}

}

void CEdgeTrackTool::LButtonDblClkEvent(UINT nFlags, CPoint point)
{

}

void CEdgeTrackTool::Draw(Display::IDisplayPtr pDisplay)
{
	if(m_pSketch)
	{
		if(!m_pSketch->IsEmpty())
		{
           m_pSketch->Draw(pDisplay);
		}
		
	}
}


}