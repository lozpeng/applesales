#include "StdAfx.h"
#include "InterfaceConvert.h"

CInterfaceConvert::CInterfaceConvert(void)
{
}

CInterfaceConvert::~CInterfaceConvert(void)
{
}

otSymbolUnit CInterfaceConvert::ConvertSymbolUnit(SYSTEM::SYS_UNIT_TYPE unit)
{
	switch(unit)
	{
	case SYSTEM::SYS_UNIT_MILLIMETER:
		return otMILLIMETER;
	case SYSTEM::SYS_UNIT_POINT:
		return otPOINTS;
	case SYSTEM::SYS_UNIT_CENTIMETER:
		return otCENTIMETER;
	case SYSTEM::SYS_UNIT_DECIMETER:
		return otDECIMETER;
	}

	return otPOINTS;

}

SYSTEM::SYS_UNIT_TYPE CInterfaceConvert::ConvertSymbolUnit(otSymbolUnit unit)
{
	switch(unit)
	{
	case  otMILLIMETER:
		return SYSTEM::SYS_UNIT_MILLIMETER;
	case otPOINTS:
		return SYSTEM::SYS_UNIT_POINT;
	case otCENTIMETER:
		return SYSTEM::SYS_UNIT_CENTIMETER;
	case otDECIMETER:
		return SYSTEM::SYS_UNIT_DECIMETER;
	}

	return SYSTEM::SYS_UNIT_MILLIMETER;
}

Display::ISymbolPtr CInterfaceConvert::ConvertISymbol(IotSymbol *pSymbol)
{
   if(!pSymbol)
   {
	   return NULL;
   }
   IOriginDataPtr pData;
   pSymbol->QueryInterface(__uuidof(IOriginData),(void**)&pData);
   
   long lval;
   pData->get_OriginData(&lval);

   return *((Display::ISymbolPtr*)lval);
}

void CInterfaceConvert::ConvertSymbol(Display::ISymbolPtr pSymbol,IotSymbol **retSymbol,bool bown)
{
    if(!pSymbol)
	{
		*retSymbol =NULL;
		return;
	}
	Display::ISymbolPtr *ppSymbol =new Display::ISymbolPtr(pSymbol);

	SYMBOL_TYPE type =pSymbol->GetType();
	IOriginDataPtr pData;
	

	switch(type)
	{
	case SIMPLE_MARKER_SYMBOL:
		{

			CoCreateInstance(CLSID_otSimpleMarkerSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case CHAR_MARKER_SYMBOL:
		{
			CoCreateInstance(CLSID_otCharMarkerSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case ARROW_MARKER_SYMBOL:
		{
			CoCreateInstance(CLSID_otArrowMarkerSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case PIC_MARKER_SYMBOL:
		{
			CoCreateInstance(CLSID_otPicMarkerSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case SIMPLE_LINE_SYMBOL:
		{
			CoCreateInstance(CLSID_otSimpleLineSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case ADV_LINE_SYMBOL:
		{
			CoCreateInstance(CLSID_otAdvLineSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case HASH_LINE_SYMBOL:
		{
			CoCreateInstance(CLSID_otHashLineSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case MARKER_LINE_SYMBOL:
		{
			CoCreateInstance(CLSID_otMarkerLineSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case SIMPLE_FILL_SYMBOL:
		{
			CoCreateInstance(CLSID_otSimpleFillSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case LINE_FILL_SYMBOL:
		{
			CoCreateInstance(CLSID_otLineFillSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case MARKER_FILL_SYMBOL:
		{
			CoCreateInstance(CLSID_otMarkerFillSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case PIC_FILL_SYMBOL:
		{
			CoCreateInstance(CLSID_otPicFillSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case GRADIENT_FILL_SYMBOL:
		{
			CoCreateInstance(CLSID_otGradientFillSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case COMPLEX_MARKER_SYMBOL:
		{
			CoCreateInstance(CLSID_otComplexMarkerSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case COMPLEX_LINE_SYMBOL:
		{
			CoCreateInstance(CLSID_otComplexLineSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case COMPLEX_FILL_SYMBOL:
		{
			CoCreateInstance(CLSID_otComplexFillSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case TEXT_SYMBOL:
		{
			CoCreateInstance(CLSID_otTextSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}


	default:
		*retSymbol =NULL;
		break;
	}
}

void CInterfaceConvert::ConvertSymbol(Display::ISymbolPtr *ppSymbol, IotSymbol **retSymbol, bool bown )
{
	SYMBOL_TYPE type =(*ppSymbol)->GetType();
	IOriginDataPtr pData;


	switch(type)
	{
	case SIMPLE_MARKER_SYMBOL:
		{

			CoCreateInstance(CLSID_otSimpleMarkerSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case CHAR_MARKER_SYMBOL:
		{
			CoCreateInstance(CLSID_otCharMarkerSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case ARROW_MARKER_SYMBOL:
		{
			CoCreateInstance(CLSID_otArrowMarkerSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case PIC_MARKER_SYMBOL:
		{
			CoCreateInstance(CLSID_otPicMarkerSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case SIMPLE_LINE_SYMBOL:
		{
			CoCreateInstance(CLSID_otSimpleLineSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case ADV_LINE_SYMBOL:
		{
			CoCreateInstance(CLSID_otAdvLineSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case HASH_LINE_SYMBOL:
		{
			CoCreateInstance(CLSID_otHashLineSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case MARKER_LINE_SYMBOL:
		{
			CoCreateInstance(CLSID_otMarkerLineSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case SIMPLE_FILL_SYMBOL:
		{
			CoCreateInstance(CLSID_otSimpleFillSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case LINE_FILL_SYMBOL:
		{
			CoCreateInstance(CLSID_otLineFillSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case MARKER_FILL_SYMBOL:
		{
			CoCreateInstance(CLSID_otMarkerFillSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case PIC_FILL_SYMBOL:
		{
			CoCreateInstance(CLSID_otPicFillSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case GRADIENT_FILL_SYMBOL:
		{
			CoCreateInstance(CLSID_otGradientFillSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case COMPLEX_MARKER_SYMBOL:
		{
			CoCreateInstance(CLSID_otComplexMarkerSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case COMPLEX_LINE_SYMBOL:
		{
			CoCreateInstance(CLSID_otComplexLineSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case COMPLEX_FILL_SYMBOL:
		{
			CoCreateInstance(CLSID_otComplexFillSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}
	case TEXT_SYMBOL:
		{
			CoCreateInstance(CLSID_otTextSymbol,NULL,CLSCTX_INPROC_SERVER,__uuidof(IOriginData),(void**)&pData);

			pData->put_OriginData(long(ppSymbol));
			pData->put_AutoDestroy(bown?TRUE:FALSE);

			pData->QueryInterface(__uuidof(IotSymbol),(void**)retSymbol);
			break;
		}


	default:
		*retSymbol =NULL;
		break;
	}
}