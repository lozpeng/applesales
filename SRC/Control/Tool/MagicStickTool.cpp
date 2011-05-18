#include "stdafx.h"
#include "MagicStickTool.h"
#include "MagicStick.h"
#include "Control.h"
#include "PolygonElement.h"

extern CControlApp theApp;
static Carto::ILayer* gpLayer =NULL;
static int gtol =20;

namespace Control
{

	

static CMagicStickTool gMagicStickTool;

CMagicStickTool::CMagicStickTool() : Framework::ITool("MagicStickTool")
{
	m_pMapCtrl =NULL;

	m_hCursor =NULL;
}

CMagicStickTool::~CMagicStickTool()
{
	if(m_hCursor)
	{
		DeleteObject( m_hCursor );
	}
}

void CMagicStickTool::Initialize(Framework::IUIObject *pTargetControl)
{
	ITool::Initialize(pTargetControl);

	
	//获取活动地图控件
	m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
	if(!m_pMapCtrl)
		return;

	//设置光标类型
	m_pMapCtrl->SetCursor(m_hCursor);


}

void CMagicStickTool::SetParam(int ntol,Carto::ILayer* pLayer)
{
	gpLayer =pLayer;
	gtol =ntol;

}

void CMagicStickTool::LButtonDownEvent (UINT nFlags, CPoint point)
{
	//获取活动地图控件
	if(!m_pMapCtrl)
		return;

	//获取活动地区
	Carto::CMapPtr pMap = m_pMapCtrl->GetMap();
	if(!pMap)
		return;

	if(gpLayer==NULL)
	{
		return;
	}
	//Carto::ILayerPtr pLayer =pMap->GetLayers().GetAt(0);

	Geodatabase::IRasterDatasetPtr pRaster =gpLayer->GetDataObject();
	if(!pRaster)
	{
		return ;
	}
	double geoCenterX, geoCenterY;
	pMap->GetDisplay()->GetDisplayTransformation().ConvertDisplayToGeo(point.x,point.y,geoCenterX, geoCenterY);
	long x,y;
	pRaster->WorldToPixel(geoCenterX,geoCenterY,&x,&y);
	//魔术棒提取
	GEOMETRY::geom::Polygon *pPolygon =ImageProcess::MagicStick(pRaster.get(),x,y,10);

	if(!pPolygon)
	{
		return;
	}
	//将下面的图元删除
	Carto::CGraphicLayerPtr pLayer =pMap->GetGraphicLayer();
	Element::IElementPtr pElement;
	int count =pLayer->GetElementCount();
	
	GEOMETRY::geom::Coordinate coord;
	coord.x =geoCenterX;
	coord.y =geoCenterY;
    GEOMETRY::geom::Polygon *ppoly =NULL;
	SYSTEM::CSmartPtr<GEOMETRY::geom::Point> pPt =GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPoint(coord);
	for(int i=count-1;i>=0;i--)
	{
		pElement =pLayer->GetElement(i);
		if(!pElement)
		{
			continue;
		}
		if(pElement->GetUserdata()==1)
		{
			//判断此图元的图形是否包含提取点
			ppoly =dynamic_cast<GEOMETRY::geom::Polygon*>(pElement->GetGeometry());
			if(ppoly==NULL)
			{
				continue;
			}
			try
			{
               if(ppoly->contains(pPt.get()))
			   {
				   pLayer->RemoveElement(pElement);
				   break;
			   }
			}
			catch(...)
			{
               
			}
			

            
		}
	}

	std::vector<Element::IElementPtr>  removeList;
	//新生成的多边形如果和之前的多边形相交，则将两个合并
	for(int i=count-1;i>=0;i--)
	{
		pElement =pLayer->GetElement(i);
		if(!pElement)
		{
			continue;
		}
		if(pElement->GetUserdata()==1)
		{
			//判断此图元的图形是否包含提取点
			ppoly =dynamic_cast<GEOMETRY::geom::Polygon*>(pElement->GetGeometry());
			if(ppoly==NULL)
			{
				continue;
			}
			try
			{
				if(ppoly->intersects(pPolygon))
				{
					//图形合并
                    GEOMETRY::geom::Geometry *pResult =pPolygon->Union(ppoly);
					if(pResult==NULL)
					{
						continue;
					}
					delete pPolygon;
					pPolygon =dynamic_cast<GEOMETRY::geom::Polygon*>(pResult);
					if(pPolygon==NULL)
					{
						continue;
					}
					removeList.push_back(pElement);
					
				}
			}
			catch(...)
			{
               int a =10;
			}



		}
	}

	for(int i=0;i<removeList.size();i++)
	{
		pLayer->RemoveElement(removeList[i]);
	}

	
	//构建一个多边形图元
	Element::CPolygonElement *ppolyElement =new Element::CPolygonElement(*pPolygon);

	delete pPolygon;
	pPolygon =NULL;

	ppolyElement->SetUserdata(1);

	//设置符号
	Display::CSimpleFillSymbolPtr pFillSymbol =ppolyElement->GetSymbol();
	pFillSymbol->SetDrawFill(false);
	pFillSymbol->SetOutLineWidth(1);
	pFillSymbol->SetOutLineColor(RGB(0,255,0));

	pMap->GetGraphicLayer()->AddElement(ppolyElement);

    m_pMapCtrl->UpdateControl(drawElement);

}

}