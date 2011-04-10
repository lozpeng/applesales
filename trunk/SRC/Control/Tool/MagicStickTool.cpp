#include "stdafx.h"
#include "MagicStickTool.h"
#include "MagicStick.h"
#include "Control.h"
#include "PolygonElement.h"

extern CControlApp theApp;
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

	//��ʼ�����
	if(m_hCursor==NULL)
	{
		//m_hCursor =::LoadCursor( theApp.m_hInstance , MAKEINTRESOURCE( IDC_ZOOMIN) );
	}


	//��ȡ���ͼ�ؼ�
	m_pMapCtrl = dynamic_cast<Framework::IMapCtrl*>(pTargetControl);
	if(!m_pMapCtrl)
		return;

	//���ù������
	//m_pMapCtrl->SetCursor(m_hCursor);


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

	Carto::ILayerPtr pLayer =pMap->GetLayers().GetAt(0);

	Geodatabase::IRasterDatasetPtr pRaster =pLayer->GetDataObject();
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
	//����һ�������ͼԪ

	Element::CPolygonElement *pElement =new Element::CPolygonElement(*pPolygon);

	//���÷���
	Display::CSimpleFillSymbolPtr pFillSymbol =pElement->GetSymbol();
	pFillSymbol->SetDrawFill(false);
	pFillSymbol->SetOutLineWidth(2);
	pFillSymbol->SetOutLineColor(RGB(0,255,0));

	pMap->GetGraphicLayer()->AddElement(pElement);

    m_pMapCtrl->UpdateControl(drawElement);

}

}