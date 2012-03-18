#pragma once
#include "iactiondrawelement.h"
#include "PolylineElement.h"

class CActionDrawFreehandLine :
	public IActionDrawElement
{
public:
	CActionDrawFreehandLine(void);
	~CActionDrawFreehandLine(void);


public:
	void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
private:
	Element::CPolylineElementPtr m_pFreehanline;
	int m_nLastVertixId;
};
