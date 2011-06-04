#include "stdafx.h"
#include "EdgeTrackTool.h"
#include "ILayer.h"
#include "PolylineElement.h"
namespace Control
{
static CEdgeTrackTool gCEdgeTrackTool;

CEdgeTrackTool::CEdgeTrackTool() : Framework::ITool("EdgeTrackTool")
{
	m_pMapCtrl =NULL;

	m_hCursor =NULL;

	Display::CSimpleLineSymbolPtr pLineSymbol =new Display::CSimpleLineSymbol;
	pLineSymbol->SetLineColor(RGB(0,255,0));
	pLineSymbol->SetLineWidth(1.5);
	
	m_pSymbol =pLineSymbol;

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
		BeginTrack();
		
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
		for(long i=mp_lPixelTempCount-1;i>=0;i--)
		{
			m_pDataset->PixelToWorld(m_pTempPathPoint[i].x,m_pTempPathPoint[i].y,&pt.x,&pt.y);
			m_pSketch->AddPoint(pt);
		}
		mp_lPixelTempCount=-1;

		m_cEdge.SetSeedPoint(coord);
		//m_pSketch->AddPoint(coord);
		//��¼�����ӵ�
		m_seedPoints.push_back(coord);
		mp_lSeedPointCount++;

		m_tempPoints.clear();
		m_pMapCtrl->UpdateControl(drawTempObj);
	    
		break;
	}
	


}

void CEdgeTrackTool::MouseMoveEvent(UINT nFlags, CPoint point)
{
	if(!m_pDataset)
	{
		return;
	}
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

			long low =0;

			//�������·�����ȴ��ڽض�·�������¼�����˶�·��
			if(mp_lPixelTempCount > mg_lSeedBreakCount + mg_lSeedBreakCount * 0.3)
			{
				for(long i=0;i<mg_lSeedBreakCount;i++)
				{
					m_pDataset->PixelToWorld(m_pTempPathPoint[mp_lPixelTempCount-i-1].x,m_pTempPathPoint[mp_lPixelTempCount-i-1].y,&pt.x,&pt.y);
					m_pSketch->AddPoint(pt);
				}
				low =mg_lSeedBreakCount-1;
				
				m_cEdge.SetSeedPoint(pt);
				//��¼�����ӵ�
				m_seedPoints.push_back(pt);
				mp_lSeedPointCount++;

				mp_lSeedPointCount++;
			}

			m_tempPoints.clear();
			//ASSERT(mp_lPixelTempCount<=500);
			for(;low<mp_lPixelTempCount;low++)
			{
				m_pDataset->PixelToWorld(m_pTempPathPoint[mp_lPixelTempCount-low-1].x,m_pTempPathPoint[mp_lPixelTempCount-low-1].y,&pt.x,&pt.y);
				m_tempPoints.push_back(pt);
				
			}

			mg_mouseLocation = coord;
			
			m_pMapCtrl->UpdateControl(drawTempObj);
			
		
	}

}

void CEdgeTrackTool::LButtonDblClkEvent(UINT nFlags, CPoint point)
{
	if(!m_pMapCtrl)
		return;

	//��ȡ�����
	Carto::CMapPtr pMap = m_pMapCtrl->GetMap();
	if(!pMap)
		return;

	if(!m_pDataset)
	{
		return;
	}
    
	if(!m_pSketch->IsEmpty())
	{
		Element::CPolylineElement *ppolyElement =new Element::CPolylineElement(*m_pSketch->GetGeometry());

		//���÷���
		Display::CSimpleLineSymbolPtr pLineSymbol =ppolyElement->GetSymbol();
		pLineSymbol->SetLineColor(RGB(0,255,0));
		pLineSymbol->SetLineWidth(2.0);

		pMap->GetGraphicLayer()->AddElement(ppolyElement);
	}
	

	EndTrack();

	m_pMapCtrl->UpdateControl(drawAll);
}

static void DrawEditPolyline(Display::IDisplayPtr &pDisplay,INT_POINT *pts,long num)
{
	Display::CDC *pDC =pDisplay->GetDrawDC();

	int i;
	DIS_LINE *pline;

	//����һ���߶��� 
	CreateDisplayLine(pline,num);
	for(i=0;i<num;i++)
	{
		pline->ps[i] =pts[i];
	}

	LINE_STYLE ls;				//���û���
	memset( &ls , 0 , sizeof(ls) );
	ls.eStyle = SOLID;
	ls.lColor = RGB(0,255,0);
	ls.lWidth = 1;

	DISPLAY_HANDLE hPen = pDC->CreatePen(ls);

	DISPLAY_HANDLE pOld =pDC->SelectObject(hPen);

	//�Ȼ���
	pDC->DrawPolyLines(*pline);

	pDC->SelectObject(pOld);
	pDC->RemoveHandle(hPen);

	FreeDisplayObj(pline);

	
}

void CEdgeTrackTool::Draw(Display::IDisplayPtr pDisplay)
{
	if(m_pSketch)
	{
		if(!m_pSketch->IsEmpty())
		{
           m_pSketch->Draw(pDisplay);
		}
		if(m_tempPoints.size()>1)
		{
			long lNumPoints =m_tempPoints.size()+1;
			//���������仯����
			INT_POINT*	pPoints = NULL;

			pPoints = new INT_POINT[lNumPoints];
			INT_POINT pt;

			//���ߵ����ӵ����
			pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(m_seedPoints.back().x,m_seedPoints.back().y,pt.x,pt.y);
			pPoints[0] = pt;
			//����һ����
			for( int j = 1;j < lNumPoints;j++ )
			{
				
				pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(m_tempPoints[j-1].x,m_tempPoints[j-1].y,pt.x,pt.y);
				pPoints[j] = pt;	

			}


			DrawEditPolyline(pDisplay,pPoints,lNumPoints);

			delete []pPoints;

		}

		//�������ӵ�
		if(!m_seedPoints.empty())
		{
			Display::CDC *pDC =pDisplay->GetDrawDC();
			BRUSH_STYLE bs;
			bs.lColor = RGB(255,0,0);
			bs.Style = SOLID_BRUSH;
			DISPLAY_HANDLE pnewBrush =pDC->CreateBrush(bs);
	
			int nSize =5;
			DIS_RECT rect;

			DISPLAY_HANDLE pOld =pDC->SelectObject(pnewBrush);

            INT_POINT pt;

			for( int i = 0;i < m_seedPoints.size();i++ )
			{
				pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(m_seedPoints[i].x,m_seedPoints[i].y,pt.x,pt.y);
				
				rect.left = pt.x - nSize;
				rect.right = pt.x + nSize;
				rect.top = pt.y - nSize;
				rect.bottom = pt.y + nSize;
				pDC->Circle(rect);

			}
	

			pDC->SelectObject(pOld);
			pDC->RemoveHandle(pnewBrush);
			
		}
		
	}
}

void CEdgeTrackTool::BeginTrack()
{
	if(!m_pMapCtrl)
		return;

	//��ȡ�����
	Carto::CMapPtr pMap = m_pMapCtrl->GetMap();
	if(!pMap)
		return;

	//ע����չ����
	if(!pMap->IsDrawInlist(this))
	{
       pMap->AddOtherDraw(this);
	}
	//��ʼ��
	m_lPointNum =0;

	long lwidth,lheight;
	m_pDataset->GetSize(&lwidth,&lheight);
	RECT rect;
	rect.left =1;
	rect.top =1;
	rect.bottom =lheight;
	rect.right =lwidth;
	GEOMETRY::geom::Envelope extent;
	m_pDataset->GetExtent(&extent);

	m_cEdge.InitRasData(m_pDataset.get(),1,extent,rect);
}

void CEdgeTrackTool::EndTrack()
{
	Carto::CMapPtr pMap = m_pMapCtrl->GetMap();
	pMap->RemoveOtherDraw(this);
    m_pDataset.reset();

	m_pSketch->SetEmpty();

	m_seedPoints.clear();

	m_tempPoints.clear();

	m_lPointNum=0;

	mp_lSeedPointCount=-1;

	//�ͷ��ڴ�
	m_cEdge.ReleaseMemory();


}

}