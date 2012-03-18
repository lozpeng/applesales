// otMapFrame.cpp : CotMapFrame 的实现

#include "stdafx.h"
#include "otMapFrame.h"


// CotMapFrame
CotMapFrame::CotMapFrame()
{

	//构造一个新的圆形图元
	m_pMapFrameElement =NULL;

	m_ppElement =NULL;

	m_bAutoDestroy =false;
}

CotMapFrame::~CotMapFrame()
{

	if(m_ppElement && m_bAutoDestroy)
	{
		delete m_ppElement;
	}
}

bool CotMapFrame::CheckPointer()
{
	if(!m_ppElement)
	{
		return false;
	}
	if(!(*m_ppElement))
	{
		return false;
	}
	return true;
}


STDMETHODIMP CotMapFrame::get_Map(IGeoMap** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	Carto::CMapPtr pMap =m_pMapFrameElement->GetMap();
	if(!pMap)
	{
		*pVal =NULL;
		return S_OK;
	}

	IOriginDataPtr pData;
	CoCreateInstance(CLSID_GeoMap,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

	Carto::CMapPtr *ppMap =new Carto::CMapPtr(pMap);
	pData->put_OriginData((long)ppMap);
	pData->put_AutoDestroy(TRUE);

	pData->QueryInterface(__uuidof(IGeoMap),(void**)pVal);


	return S_OK;
}

STDMETHODIMP CotMapFrame::put_Map(IGeoMap* newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	if(newVal)
	{
        IOriginDataPtr pData;
		newVal->QueryInterface(__uuidof(IOriginData),(void**)&pData);

		long ldata;
		pData->get_OriginData(&ldata);

		Carto::CMapPtr pMap=*((Carto::CMapPtr*)ldata);

		m_pMapFrameElement->SetMap(pMap);

	}

	return S_OK;
}

/*****************************************************************************
* 实现IOriginData接口
******************************************************************************/
STDMETHODIMP CotMapFrame::get_OriginData(long * pVal)
{

	*pVal =(long)m_ppElement;
	return S_OK;
}

STDMETHODIMP CotMapFrame::put_OriginData(long  pVal)
{

	if(m_ppElement && m_bAutoDestroy)
	{
		delete m_ppElement;
		m_pMapFrameElement =NULL;
	}

	Element::IElementPtr *ppEle =(Element::IElementPtr*)pVal;

	//将IElement指针转换成相应图元的指针
	m_pMapFrameElement =dynamic_cast<Element::CMapFrame*>(ppEle->get());

	if(!m_pMapFrameElement)
	{
		m_ppElement =NULL;
	}
	else
	{
		m_ppElement =ppEle;
	}

	return S_OK;
}

STDMETHODIMP CotMapFrame::get_AutoDestroy(long * pVal)
{

	if(m_bAutoDestroy)
	{
		*pVal =TRUE;
	}
	else
	{
		*pVal =FALSE;
	}
	return S_OK;
}

STDMETHODIMP CotMapFrame::put_AutoDestroy(long  pVal)
{

	if(pVal)
	{
		m_bAutoDestroy =true;
	}
	else
	{
		m_bAutoDestroy =false;
	}
	return S_OK;
}

/*****************************************************************************
* 实现IElement接口
******************************************************************************/

STDMETHODIMP CotMapFrame::get_Geometry(IotGeometry** pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	GEOMETRY::geom::Geometry *pg=m_pMapFrameElement->GetGeometry();
	if(!pg)
	{
		*pVal =NULL;
		return S_OK;
	}
	pg =pg->clone();

	IotGeoConvertPtr pCon;

	CoCreateInstance(CLSID_otGeoConvert,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotGeoConvert),(void**)&pCon);

	pCon->ConvertGeo(long(pg),VARIANT_TRUE,pVal);

	return S_OK;
}

STDMETHODIMP CotMapFrame::put_Geometry(IotGeometry*  newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}
	if(!newVal)
	{
		return E_FAIL;
	}
	IotGeoConvertPtr pCon;

	CoCreateInstance(CLSID_otGeoConvert,NULL,CLSCTX_INPROC_SERVER,__uuidof(IotGeoConvert),(void**)&pCon);

	long ldata;
	pCon->ConvertIGeo(newVal,&ldata);

	m_pMapFrameElement->SetGeometry(*((GEOMETRY::geom::Geometry*)ldata));


	return S_OK;
}


STDMETHODIMP CotMapFrame::get_Name(BSTR * pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	_bstr_t str =m_pMapFrameElement->GetName().c_str();

	*pVal =SysAllocString(str);
	return S_OK;
}


STDMETHODIMP CotMapFrame::put_Name(BSTR newVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	_bstr_t str =newVal;

	m_pMapFrameElement->SetName(std::string(str));

	return S_OK;
}

STDMETHODIMP CotMapFrame::get_Type( ElementType * pVal)
{
	if(!CheckPointer())
	{
		return E_FAIL;
	}

	*pVal =(ElementType)m_pMapFrameElement->GetType();
	return S_OK;
}
STDMETHODIMP CotMapFrame::Create(IGeoMap* map, IotEnvelope* envelope)
{
	
	if(m_ppElement && m_bAutoDestroy)
	{
		delete m_ppElement;
		m_ppElement =NULL;
	}

	if((!map) || (!envelope))
	{
		return E_FAIL;
	}
	
	IOriginDataPtr pData;
	map->QueryInterface(__uuidof(IOriginData),(void**)&pData);

	long ldata;
	pData->get_OriginData(&ldata);

	Carto::CMapPtr pMap=*((Carto::CMapPtr*)ldata);

	GEOMETRY::geom::Envelope extent;
	double xmin,xmax,ymin,ymax;

	envelope->get_MinX(&xmin);
	envelope->get_MaxX(&xmax);

	envelope->get_MinY(&ymin);
	envelope->get_MaxY(&ymax);

	extent.init(xmin,xmax,ymin,ymax);

	GEOMETRY::geom::Geometry* pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&extent);
	m_pMapFrameElement = new Element::CMapFrame(*pGeometry, pMap);
	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(pGeometry);

	m_ppElement =new Element::IElementPtr(m_pMapFrameElement);

	m_bAutoDestroy =true;

	return S_OK;
}
