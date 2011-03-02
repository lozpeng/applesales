#ifndef _ACTION_SKETCH_H_
#define _ACTION_SKETCH_H_

#include "IAction.h"

namespace otEditor
{

class  CActionSketch : public otFramework::IAction
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