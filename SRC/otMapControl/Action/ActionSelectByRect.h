#ifndef _ACTION_SELECT_BYRECT_H
#define _ACTION_SELECT_BYRECT_H

#include "ISelectFeatureTool.h"



class  CActionSelByRect : public ISelectFeatureTool
{
public:
	CActionSelByRect();
	~CActionSelByRect();

public:
	
	void LButtonDownEvent (UINT nFlags, CPoint point);


	
};




#endif