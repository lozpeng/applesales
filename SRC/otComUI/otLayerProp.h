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
	//��ʾͼ�������
	static int ShowLayerProp(Carto::ILayerPtr pLayer,ILayerPropCallback *pCallback);

};

}
