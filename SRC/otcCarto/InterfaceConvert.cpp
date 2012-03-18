#include "StdAfx.h"
#include "InterfaceConvert.h"
#include "FeatureLayer.h"
#include "RasterLayer.h"
#include "SimpleRender.h"

CInterfaceConvert::CInterfaceConvert(void)
{
}

CInterfaceConvert::~CInterfaceConvert(void)
{
}


Element::IElementPtr CInterfaceConvert::ConvertIElement(IElement *pElement)
{
	if(!pElement)
	{
		return NULL;
	}
	IOriginDataPtr pData;
	pElement->QueryInterface(__uuidof(IOriginData),(void**)&pData);

	long lval;
	pData->get_OriginData(&lval);

	return *((Element::IElementPtr*)lval);
}

void CInterfaceConvert::ConvertElement(Element::IElementPtr pElement, IElement **retElement, bool bown )
{
	if(!pElement)
	{
		*retElement =NULL;

		return;
	}
	Element::IElementPtr *ppE =new Element::IElementPtr(pElement);

	Element::ELEMENT_TYPE type =pElement->GetType();
	IOriginDataPtr pData;


	switch(type)
	{
	case Element::ET_SIMPLE_POINT_ELEMENT:
		{

			CoCreateInstance(CLSID_otMarkerElement,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppE));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IElement),(void**)retElement);
			break;
		}
	case Element::ET_POLYLINE_ELEMENT:
		{

			CoCreateInstance(CLSID_otPolylineElement,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppE));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IElement),(void**)retElement);
			break;
		}
	case Element::ET_FILL_POLYGON_ELEMENT:
		{

			CoCreateInstance(CLSID_otPolygonElement,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppE));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IElement),(void**)retElement);
			break;
		}
	case Element::ET_FILL_RECTANGLE_ELEMENT:
		{

			CoCreateInstance(CLSID_otRectElement,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppE));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IElement),(void**)retElement);
			break;
		}
	case Element::ET_SIMPLE_TEXT_ELEMENT:
		{

			CoCreateInstance(CLSID_otTextElement,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppE));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IElement),(void**)retElement);
			break;
		}
	case Element::ET_FILL_CIRCLE_ELEMENT:
		{

			CoCreateInstance(CLSID_otCircleElement,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppE));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IElement),(void**)retElement);
			break;
		}
	case Element::ET_FILL_ELLIPSE_ELEMENT:
		{

			CoCreateInstance(CLSID_otEllipseElement,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppE));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IElement),(void**)retElement);
			break;
		}
	case Element::ET_CURVE_ELEMENT:
		{

			CoCreateInstance(CLSID_otBezierCurveElement,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppE));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IElement),(void**)retElement);
			break;
		}
	case Element::ET_BEZIERCURVE_ELEMENT:
	{

			CoCreateInstance(CLSID_otBezierCurveElement,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppE));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IElement),(void**)retElement);
			break;
	}
	case Element::ET_CALLOUT_TEXT_ELEMENT:
		{
			CoCreateInstance(CLSID_otCalloutTextElement,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppE));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IElement),(void**)retElement);
			break;
		}
	case Element::ET_MAP_FRAME_ELEMENT:
		{
			CoCreateInstance(CLSID_otMapFrame,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppE));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IElement),(void**)retElement);
			break;
		}
	default:
		*retElement =NULL;
		break;
	}

}

Carto::ILayerPtr CInterfaceConvert::ConvertILayer(IotLayer *layer)
{
	if(!layer)
	{
		return NULL;
	}
	IOriginDataPtr pData;
	layer->QueryInterface(__uuidof(IOriginData),(void**)&pData);
	long ldata;
	pData->get_OriginData(&ldata);

	otLayerType type;
	layer->get_LayerType(&type);

	Carto::ILayerPtr retLayer;

	switch(type)
	{
	case OT_FeatureLayer:
		{
			retLayer =*((Carto::IFeatureLayerPtr*)ldata);
			break;
		}
	case OT_RasterLayer:
		{
			retLayer =*((Carto::CRasterLayerPtr*)ldata);
			break;
		}
	case OT_GraphicLayer:
		{
			
			retLayer =*((Carto::CGraphicLayerPtr*)ldata);
			break;
		}
	default:
		break;
	}

	return retLayer;

}

void CInterfaceConvert::ConvertLayer(Carto::ILayerPtr pLayer, IotLayer **retLayer, bool bown )
{
	if(!pLayer)
	{
		*retLayer =NULL;

		return;
	}
	Carto::LAYER_TYPE type =pLayer->GetLayerType();

	IOriginDataPtr pData;


	switch(type)
	{
	case Carto::FeatureLayer:
		{

			CoCreateInstance(CLSID_otFeatureLayer,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			Carto::IFeatureLayerPtr *ppLayer =new Carto::IFeatureLayerPtr(pLayer);
			pData->put_OriginData(long(ppLayer));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotLayer),(void**)retLayer);
			break;
		}
	case Carto::RasterLayer:
		{

			CoCreateInstance(CLSID_otRasterLayer,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			Carto::CRasterLayerPtr *ppLayer =new Carto::CRasterLayerPtr(pLayer);
			pData->put_OriginData(long(ppLayer));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotLayer),(void**)retLayer);
			break;
		}
	case Carto::GraphicLayer:
		{

			CoCreateInstance(CLSID_otGraphicLayer,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			Carto::CGraphicLayerPtr *ppLayer =new Carto::CGraphicLayerPtr(pLayer);
			pData->put_OriginData(long(ppLayer));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotLayer),(void**)retLayer);
			break;
		}
	default:
		*retLayer =NULL;
		break;
	}
}

void CInterfaceConvert::ConvertFeatureRender(Carto::IRenderPtr pRender, IotFeatureRender **retRender, bool bown)
{
	if(!pRender)
	{
		*retRender =NULL;

		return;
	}
	Carto::RENDER_TYPE type =pRender->GetRenderType();

	IOriginDataPtr pData;


	switch(type)
	{
	case Carto::SIMPLERENDER:
		{
			CoCreateInstance(CLSID_otSimpleRender,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			Carto::CSimpleRenderPtr *ppRender=new Carto::CSimpleRenderPtr(pRender);
			pData->put_OriginData(long(ppRender));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotFeatureRender),(void**)retRender);
		}
	default:
		*retRender =NULL;
		break;
	}

}

Carto::IRenderPtr CInterfaceConvert::ConvertIFeatureRender(IotFeatureRender *render)
{
	if(!render)
	{
		return NULL;
	}
	IOriginDataPtr pData;
	render->QueryInterface(__uuidof(IOriginData),(void**)&pData);
	long ldata;
	pData->get_OriginData(&ldata);

	otFeatureRenderType type;
	render->get_RenderType(&type);

	Carto::IRenderPtr retRender;

	switch(type)
	{
	case OTSIMPLERENDER:
		{
			retRender =*((Carto::CSimpleRenderPtr*)ldata);
			break;
		}
	default:
		break;
	}

	return retRender;
}