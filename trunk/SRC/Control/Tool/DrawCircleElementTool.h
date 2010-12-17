#pragma once

#include "IDrawElementTool.h"
#include "CircleElement.h"

namespace Control
{


class  CDrawCircleElementTool : public IDrawElementTool
{

public:
	CDrawCircleElementTool();
	~CDrawCircleElementTool();

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);

private:
	Element::CCircleElementPtr m_pCircle;

};


}
