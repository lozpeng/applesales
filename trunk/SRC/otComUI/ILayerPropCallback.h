#pragma once

namespace otComUI
{
class otComUI_DLL ILayerPropCallback
{
public:
	ILayerPropCallback(void);
	virtual ~ILayerPropCallback(void);

public:
	//���µ�ͼ�ؼ�
	virtual void UpdateMapCtrl();
};

}
