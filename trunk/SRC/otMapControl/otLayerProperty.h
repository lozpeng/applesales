

#pragma once

#include "ILayer.h"
// CotLayerProperty 命令目标

class CotLayerProperty : public CCmdTarget
{
	DECLARE_DYNCREATE(CotLayerProperty)

public:
	CotLayerProperty();
	virtual ~CotLayerProperty();

	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CotLayerProperty)

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	
	

	enum 
	{
		dispidShowLayerProperty = 1L
	};

	void ShowLayerProperty(IotLayer* layer,IDispatch *MapControl);

	//从IotLayer接口里获得图层指针
	Carto::ILayerPtr ConvertILayer(IotLayer *layer);


};


