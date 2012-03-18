#ifndef _ACTION_SELECT_BYPOINT_H
#define _ACTION_SELECT_BYPOINT_H

#include "ISelectFeatureTool.h"



class  CActionSelByPoint : public ISelectFeatureTool
{
public:
	CActionSelByPoint();
	~CActionSelByPoint();

public:

	void LButtonDownEvent (UINT nFlags, CPoint point);



};




#endif