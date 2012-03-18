#pragma once

#include "otcCarto.h"
#include "IElement.h"
#include "IRender.h"
#include "ILayer.h"

class CInterfaceConvert
{
public:
	CInterfaceConvert(void);
	~CInterfaceConvert(void);
public:

	
	static Element::IElementPtr ConvertIElement(IElement *pElement);

	static void ConvertElement(Element::IElementPtr pElement,IElement **retElement,bool bown =true);

	static Carto::ILayerPtr ConvertILayer(IotLayer *layer);

	static void ConvertLayer(Carto::ILayerPtr pLayer,IotLayer **retLayer,bool bown =true);

	static void ConvertFeatureRender(Carto::IRenderPtr pRender,IotFeatureRender **retRender,bool bown =true);

	static Carto::IRenderPtr ConvertIFeatureRender(IotFeatureRender *render);
};
