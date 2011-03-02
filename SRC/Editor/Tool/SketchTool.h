#ifndef _ACTION_SKETCH_H_
#define _ACTION_SKETCH_H_

#include "ITool.h"

namespace Editor
{

class  CActionSketch : public Framework::ITool
{
public:
	CActionSketch();
	~CActionSketch();


public:
	void Triger();
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