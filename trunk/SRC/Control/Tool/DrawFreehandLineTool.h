#pragma once
#include "IDrawElementTool.h"
#include "PolylineElement.h"

class CDrawFreehandLineTool :
	public IDrawElementTool
{
public:
	CDrawFreehandLineTool(void);
	~CDrawFreehandLineTool(void);


public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
private:
	Element::CPolylineElementPtr m_pFreehanline;
	int m_nLastVertixId;
};
