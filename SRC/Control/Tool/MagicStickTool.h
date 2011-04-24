#ifndef _MagicStickTool_H
#define _MagicStickTool_H

#include "ITool.h"
#include "IMapCtrl.h"

namespace Control
{

class CONTROL_DLL CMagicStickTool: public Framework::ITool
{
public:
	CMagicStickTool();
	~CMagicStickTool();

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);

	static void SetParam(int ntol,Carto::ILayer* pLayer);

private:
	HCURSOR m_hCursor;

	Framework::IMapCtrl *m_pMapCtrl;


};

}


#endif