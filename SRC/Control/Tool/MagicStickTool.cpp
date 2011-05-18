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

	
	//��ȡ���ͼ�ؼ�
	m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
	if(!m_pMapCtrl)
		return;

	//���ù������
	m_pMapCtrl->SetCursor(m_hCursor);


}

void CMagicStickTool::SetParam(int ntol,Carto::ILayer* pLayer)
{
	gpLayer =pLayer;
	gtol =ntol;

}

void CMagicStickTool::LButtonDownEvent (UINT nFlags, CPoint point)
{
	//��ȡ���ͼ�ؼ�
	if(!m_pMapCtrl)
		return;

	//��ȡ�����
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
	//ħ������ȡ
	GEOMETRY::geom::Polygon *pPolygon =ImageProcess::MagicStick(pRaster.get(),x,y,10);

	if(!pPolygon)
	{
		return;
	}
	//�������ͼԪɾ��
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
			//�жϴ�ͼԪ��ͼ���Ƿ������ȡ��
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
	//�����ɵĶ���������֮ǰ�Ķ�����ཻ���������ϲ�
	for(int i=count-1;i>=0;i--)
	{
		pElement =pLayer->GetElement(i);
		if(!pElement)
		{
			continue;
		}
		if(pElement->GetUserdata()==1)
		{
			//�жϴ�ͼԪ��ͼ���Ƿ������ȡ��
			ppoly =dynamic_cast<GEOMETRY::geom::Polygon*>(pElement->GetGeometry());
			if(ppoly==NULL)
			{
				continue;
			}
			try
			{
				if(ppoly->intersects(pPolygon))
				{
					//ͼ�κϲ�
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

	
	//����һ�������ͼԪ
	Element::CPolygonElement *ppolyElement =new Element::CPolygonElement(*pPolygon);

	delete pPolygon;
	pPolygon =NULL;

	ppolyElement->SetUserdata(1);

	//���÷���
	Display::CSimpleFillSymbolPtr pFillSymbol =ppolyElement->GetSymbol();
	pFillSymbol->SetDrawFill(false);
	pFillSymbol->SetOutLineWidth(1);
	pFillSymbol->SetOutLineColor(RGB(0,255,0));

	pMap->GetGraphicLayer()->AddElement(ppolyElement);

    m_pMapCtrl->UpdateControl(drawElement);

}

}