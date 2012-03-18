

#pragma once

#include "ILayer.h"
// CotLayerProperty ����Ŀ��

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

	//��IotLayer�ӿ�����ͼ��ָ��
	Carto::ILayerPtr ConvertILayer(IotLayer *layer);


};


