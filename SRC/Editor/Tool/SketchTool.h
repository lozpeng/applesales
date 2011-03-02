#ifndef _SKETCH_H_TOOL_
#define _SKETCH_H_TOOL_

#include "ITool.h"

namespace Editor
{

class  CSketchTool : public Framework::ITool
{
public:
	CSketchTool();
	~CSketchTool();


public:
	//≥ı ºªØ
		
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
	void LButtonDblClkEvent (UINT nFlags, CPoint point);
	void RButtonDownEvent (UINT nFlags, CPoint point);

private:
	CPoint m_clickPt;
};

}


#endif