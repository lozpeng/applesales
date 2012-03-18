#pragma once
#include "ILayerPropCallback.h"


class CMapTreeCallback : public otComUI::ILayerPropCallback
{
public:
	CMapTreeCallback(void);
	virtual ~CMapTreeCallback(void);

public:
	void SetMapCtrl(_DotMapControl *pMapControl) {m_pMapControl =pMapControl;}

	virtual void UpdateMapCtrl();
private:

	_DotMapControl *m_pMapControl; 

};
