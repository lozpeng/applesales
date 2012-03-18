#ifndef _ACTION_DRAW_POLYLINE_ELEMENT_H
#define _ACTION_DRAW_POLYLINE_ELEMENT_H

#include "IActionDrawElement.h"
#include "PolylineElement.h"


class CActionDrawPolylineElement : public IActionDrawElement
{
public:
	CActionDrawPolylineElement();
	~CActionDrawPolylineElement();

public:
	void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);

	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
	void LButtonDblClkEvent (UINT nFlags, CPoint point);


private:
	Element::CPolylineElementPtr m_pPolyline;
	int m_nLastVertixId;
};



#endif