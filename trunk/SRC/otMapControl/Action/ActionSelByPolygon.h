#ifndef _ACTION_SELECT_BYPOLYGON_H
#define _ACTION_SELECT_BYPOLYGON_H

#include "ISelectFeatureTool.h"
#include "GeometrySketch.h"


class CActionSelByPolygon :public ISelectFeatureTool
{
public:
	CActionSelByPolygon(void);
	~CActionSelByPolygon(void);

public:

	virtual void LButtonDownEvent (UINT nFlags, CPoint point);

	virtual void MouseMoveEvent (UINT nFlags, CPoint point);

	virtual void LButtonDblClkEvent (UINT nFlags, CPoint point);

	virtual void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);

	void ActionDraw();

private:
	Display::CGeometrySketchPtr m_pSketch;

	CPoint m_lastPt;
};



#endif