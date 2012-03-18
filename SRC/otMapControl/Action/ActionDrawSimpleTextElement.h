#ifndef _ACTION_DRAW_SIMPLE_TEXT_ELEMENT_H
#define _ACTION_DRAW_SIMPLE_TEXT_ELEMENT_H

#include "IActionDrawElement.h"
#include "SimpleTextElement.h"


class  CActionDrawSimpleTextElement : public IActionDrawElement
{
public:
	CActionDrawSimpleTextElement();
	~CActionDrawSimpleTextElement();

public:
	void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);

private:
	Element::CSimpleTextElementPtr m_pText;
};




#endif