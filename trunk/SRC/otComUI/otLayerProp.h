#pragma once
#include "IlayerPropCallback.h"
#include "ILayer.h"
namespace otComUI
{

class otComUI_DLL CotLayerProp
{
public:
	CotLayerProp(void);
	~CotLayerProp(void);
public:
	//œ‘ æÕº≤„µƒ Ù–‘
	static int ShowLayerProp(Carto::ILayerPtr pLayer,ILayerPropCallback *pCallback);

};

}
