#ifndef _Action_Draw_Rectangle_Element_h
#define _Action_Draw_Rectangle_Element_h

#include "IActionDrawElement.h"
#include "RectangleElement.h"


class CActionDrawRectangleElement : public IActionDrawElement
{
public:
	CActionDrawRectangleElement();
	~CActionDrawRectangleElement();

public:
	void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);


private:
	Element::CRectangleElementPtr m_pRectangle;
};




#endif