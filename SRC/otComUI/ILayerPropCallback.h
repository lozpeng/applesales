#pragma once

namespace otComUI
{
class otComUI_DLL ILayerPropCallback
{
public:
	ILayerPropCallback(void);
	virtual ~ILayerPropCallback(void);

public:
	//更新地图控件
	virtual void UpdateMapCtrl();
};

}
