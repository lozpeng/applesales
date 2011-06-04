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

	 //创建一个默认画笔
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


	//获取活动地图控件
	m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
	if(!m_pMapCtrl)
		return;

	//设置光标类型
	m_pMapCtrl->SetCursor(m_hCursor);


}


void CEdgeTrackTool::LButtonDownEvent (UINT nFlags, CPoint point)
{

	//获取活动地图控件
	if(!m_pMapCtrl)
		return;

	//获取活动地区
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
		//确定目标图层数据
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
			//如果点选的点在图像范围内，则就是此图像
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
	case 0:		//初始点
		m_cEdge.SetSeedPoint(coord);
		mp_lSeedPointCount=-1;
		mp_lSeedPointCount++;
		//记录下种子点
		m_seedPoints.push_back(coord);
		m_lPointNum++;
		break;
	case 1:    //重新设置种子点
		m_cEdge.SetCurPoint(coord);
		//得到种子点到此点的路径
		m_cEdge.GetOptimalPath(&mp_lPixelTempCount,&m_pTempPathPoint);

        //将上段路径保留
		
		GEOMETRY::geom::Coordinate pt;
		for(long i=mp_lPixelTempCount-1;i>=0;i--)
		{
			m_pDataset->PixelToWorld(m_pTempPathPoint[i].x,m_pTempPathPoint[i].y,&pt.x,&pt.y);
			m_pSketch->AddPoint(pt);
		}
		mp_lPixelTempCount=-1;

		m_cEdge.SetSeedPoint(coord);
		//m_pSketch->AddPoint(coord);
		//记录下种子点
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
	//获取活动地图控件
	if(!m_pMapCtrl)
		return;

	//获取活动地区
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

			//如果这条路径长度大于截断路径，则记录下来此段路径
			if(mp_lPixelTempCount > mg_lSeedBreakCount + mg_lSeedBreakCount * 0.3)
			{
				for(long i=0;i<mg_lSeedBreakCount;i++)
				{
					m_pDataset->PixelToWorld(m_pTempPathPoint[mp_lPixelTempCount-i-1].x,m_pTempPathPoint[mp_lPixelTempCount-i-1].y,&pt.x,&pt.y);
					m_pSketch->AddPoint(pt);
				}
				low =mg_lSeedBreakCount-1;
				
				m_cEdge.SetSeedPoint(pt);
				//记录下种子点
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

	//获取活动地区
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

		//设置符号
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

	//构造一个线对象 
	CreateDisplayLine(pline,num);
	for(i=0;i<num;i++)
	{
		pline->ps[i] =pts[i];
	}

	LINE_STYLE ls;				//设置画笔
	memset( &ls , 0 , sizeof(ls) );
	ls.eStyle = SOLID;
	ls.lColor = RGB(0,255,0);
	ls.lWidth = 1;

	DISPLAY_HANDLE hPen = pDC->CreatePen(ls);

	DISPLAY_HANDLE pOld =pDC->SelectObject(hPen);

	//先画线
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
			//绘制随鼠标变化的线
			INT_POINT*	pPoints = NULL;

			pPoints = new INT_POINT[lNumPoints];
			INT_POINT pt;

			//将线的种子点加入
			pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(m_seedPoints.back().x,m_seedPoints.back().y,pt.x,pt.y);
			pPoints[0] = pt;
			//构造一个线
			for( int j = 1;j < lNumPoints;j++ )
			{
				
				pDisplay->GetDisplayTransformation().ConvertGeoToDisplay(m_tempPoints[j-1].x,m_tempPoints[j-1].y,pt.x,pt.y);
				pPoints[j] = pt;	

			}


			DrawEditPolyline(pDisplay,pPoints,lNumPoints);

			delete []pPoints;

		}

		//绘制种子点
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

	//获取活动地区
	Carto::CMapPtr pMap = m_pMapCtrl->GetMap();
	if(!pMap)
		return;

	//注册扩展绘制
	if(!pMap->IsDrawInlist(this))
	{
       pMap->AddOtherDraw(this);
	}
	//初始化
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

	//释放内存
	m_cEdge.ReleaseMemory();


}

}