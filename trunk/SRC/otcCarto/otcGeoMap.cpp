// otCMap.cpp : GeoMap 的实现

#include "stdafx.h"
#include "otcGeoMap.h"
#include "InterfaceConvert.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>
// GeoMap

GeoMap::GeoMap()
{
	//构造一个默认的地图对象
	m_ppMap=new Carto::CMapPtr(new Carto::CMap());
	m_bAutoDestroy =TRUE;

	//注册回调
	boost::function<void (Element::IElementPtr pElement)> funms = boost::bind(&GeoMap::OnElementDeleted,this,_1);

	m_ConnectionDeleteElement = Carto::CGraphicLayer::RegisterDeleteElement(funms);
}

GeoMap::~GeoMap()
{
   m_ConnectionDeleteElement.disconnect();

   if(m_ppMap && m_bAutoDestroy)
   {
	   delete m_ppMap;
	   m_ppMap =NULL;
   }
}

bool GeoMap::CheckPointer()
{
	if(!m_ppMap)
	{
		return false;
	}
	if(!(*m_ppMap))
	{

		return false;
	}
	return true;
}

STDMETHODIMP GeoMap::get_OriginData(long * pVal)
{
	
    *pVal =(long)m_ppMap;
	return S_OK;
}

STDMETHODIMP GeoMap::put_OriginData(long  pVal)
{

    if(m_ppMap && m_bAutoDestroy)
	{
		delete m_ppMap;
	}
	m_ppMap =(Carto::CMapPtr*)(pVal);
	return S_OK;
}

STDMETHODIMP GeoMap::get_AutoDestroy(long * pVal)
{

    *pVal =m_bAutoDestroy;
	return S_OK;
}

STDMETHODIMP GeoMap::put_AutoDestroy(long  pVal)
{

    m_bAutoDestroy =pVal;
	return S_OK;
}

STDMETHODIMP GeoMap::LayerCount(LONG* Count)
{
	if(CheckPointer())
	{
		Carto::CLayerArray &layers =(*m_ppMap)->GetLayers();
		*Count =layers.GetSize();
	}
	else
	{
		*Count =0;
	}
    
	return S_OK;
}

STDMETHODIMP GeoMap::get_MapUnit(otUnits* pVal)
{
	
    if(!CheckPointer())
	{
		*pVal =OT_UNIT_UNKNOWN;
		return E_FAIL;
	}

	*pVal =(otUnits)(*m_ppMap)->GetUnit();
	return S_OK;
}

STDMETHODIMP GeoMap::get_GraphicLayer(IotGraphicLayer** pVal)
{
	
	if(!CheckPointer())
	{
		*pVal =NULL;
		return E_FAIL;
	}
	Carto::CGraphicLayerPtr pLayer =(*m_ppMap)->GetGraphicLayer();
	if(!pLayer)
	{
		*pVal =NULL;
		return E_FAIL;
	}
	Carto::CGraphicLayerPtr *ppF =new Carto::CGraphicLayerPtr(pLayer);

	IOriginDataPtr pData;

	CoCreateInstance(CLSID_otGraphicLayer,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	pData->put_OriginData((long)ppF);
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IotGraphicLayer),(void**)pVal);

	return S_OK;
}

STDMETHODIMP GeoMap::get_Name(BSTR* pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	_bstr_t str=(*m_ppMap)->GetName().c_str();

	*pVal =SysAllocString(str);


	return S_OK;
}

STDMETHODIMP GeoMap::put_Name(BSTR newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	_bstr_t str =newVal;

	(*m_ppMap)->SetName(std::string(str));

	return S_OK;
}

//添加图层
STDMETHODIMP GeoMap::AddLayer(IotLayer* layer)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	if(!layer)
	{
		return E_FAIL;
	}

	Carto::ILayerPtr pLayer =CInterfaceConvert::ConvertILayer(layer);

	(*m_ppMap)->AddLayer(pLayer);


	return S_OK;
}



STDMETHODIMP GeoMap::GetLayer(LONG index, IotLayer** retLayer)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Carto::CLayerArray &layers =(*m_ppMap)->GetLayers();

	//判断序号是否正确
    if(index<0 || index>=layers.GetSize())
	{
		return E_FAIL;
	}

	Carto::ILayerPtr player =layers.GetAt(index);

	CInterfaceConvert::ConvertLayer(player,retLayer);


	return S_OK;
}


STDMETHODIMP GeoMap::RemoveLayers(void)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	(*m_ppMap)->Clear();

	return S_OK;
}

STDMETHODIMP GeoMap::DeleteLayer(LONG index)
{
	
    if(!CheckPointer())
	{
		return E_FAIL;
	}
	(*m_ppMap)->DeleteLayer(index);

	return S_OK;
}

STDMETHODIMP GeoMap::FindLayer(IotLayer* layer, LONG* index)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	Carto::ILayerPtr pLayer =CInterfaceConvert::ConvertILayer(layer);
	if(!pLayer)
	{
		return E_FAIL;
	}

	*index =(*m_ppMap)->GetLayers().FindIndex(pLayer);
	return S_OK;
}

STDMETHODIMP GeoMap::MoveLayer(IotLayer* layer, LONG ToIndex)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	Carto::ILayerPtr pLayer =CInterfaceConvert::ConvertILayer(layer);
	if(!pLayer)
	{
		return E_FAIL;
	}
	Carto::CLayerArray &layers =(*m_ppMap)->GetLayers();

	layers.ChangeOrder(layers.FindIndex(pLayer),ToIndex);
    
	return S_OK;
}

STDMETHODIMP GeoMap::get_SpatialReference(IotSpatialReference** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	//获得投影信息
	std::string wkt =(*m_ppMap)->GetMapProjection();

	if(wkt.empty())
	{
		*pVal =NULL;
	}
	else
	{
		CoCreateInstance(CLSID_otSpatialReference,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotSpatialReference),(void**)pVal);

		_bstr_t str =wkt.c_str();
		VARIANT_BOOL suc;
		(*pVal)->ImportFromESRI(str,&suc);

		//判断是否解析投影成功
		if(suc ==VARIANT_FALSE)
		{
			(*pVal)->Release();
			*pVal =NULL;
		}
	}

	return S_OK;
}

STDMETHODIMP GeoMap::put_SpatialReference(IotSpatialReference* newVal)
{
	// TODO: 在此添加实现代码

	return S_OK;
}

void GeoMap::OnElementDeleted(Element::IElementPtr pElement)
{
   IElement *pEle =NULL;
   CInterfaceConvert::ConvertElement(pElement,&pEle);

   Fire_ElementDeleted(pEle);
}

STDMETHODIMP GeoMap::ZoomActualSize(void)
{
	// TODO: 在此添加实现代码
	(*m_ppMap)->GetDisplay()->GetDisplayTransformation().SetScale(1);
	return S_OK;
}

STDMETHODIMP GeoMap::ZoomFullExtent(void)
{
	// TODO: 在此添加实现代码
	(*m_ppMap)->GetDisplay()->GetDisplayTransformation().FitViewBound((*m_ppMap)->GetExtent());
	return S_OK;
}
