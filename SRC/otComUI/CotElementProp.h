#pragma once

#include "IElement.h"
#include "IlayerPropCallback.h"
#include "Map.h"

namespace otComUI
{

class otComUI_DLL CElementProp
{
public:
	CElementProp(void);
	~CElementProp(void);
public:
	//œ‘ æÕº≤„µƒ Ù–‘
	static int ShowElementProp(Element::IElementPtr pElement,Carto::CMap* pMap,ILayerPropCallback *pCallback);
};

}
