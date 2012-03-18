
#ifndef _ACTION_DRAW_BezierCurve_ELEMENT_H
#define _ACTION_DRAW_BezierCurve_ELEMENT_H
#pragma once
#include "iactiondrawelement.h"
#include "BezierCurveElement.h"

class CActionDrawBezierCurveElement :
	public IActionDrawElement
{
public:
	CActionDrawBezierCurveElement(void);
	~CActionDrawBezierCurveElement(void);


public:
	void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
	void LButtonDblClkEvent (UINT nFlags, CPoint point);


private:
	Element::CBezierCurveElementPtr m_pBezier;
	int m_nLastVertixId;
};


#endif