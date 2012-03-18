#ifndef _ACTION_DRAW_POLYGON_ELEMENT_h
#define _ACTION_DRAW_POLYGON_ELEMENT_h

#include "IActionDrawElement.h"
#include "PolygonElement.h"


class  CActionDrawPolygonElement : public IActionDrawElement
{
public:
	CActionDrawPolygonElement();
	~CActionDrawPolygonElement();

public:
	void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);

	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
	void LButtonDblClkEvent (UINT nFlags, CPoint point);


private:
	Element::CPolygonElementPtr m_pPolygon;
	int m_nLastVertixId;
};




#endif