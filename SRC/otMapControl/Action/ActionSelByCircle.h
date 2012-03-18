#ifndef _ACTION_SELECT_BYCIRCLE_H
#define _ACTION_SELECT_BYCIRCLE_H

#include "ISelectFeatureTool.h"
#include "IDisplay.h"
#include <geometry/geom/Geometry.h>



class CActionSelByCircle :public ISelectFeatureTool
{
public:
	CActionSelByCircle(void);
	~CActionSelByCircle(void);

	virtual void LButtonDownEvent (UINT nFlags, CPoint point);

	virtual void MouseMoveEvent (UINT nFlags, CPoint point);

	virtual void LButtonUpEvent (UINT nFlags, CPoint point);

	virtual void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);

	void ActionDraw();

private:
	//�Ƿ�ʼ����
	bool m_bStartDraw;			

	//Բ�ĺ��յ�
	CPoint m_centralPt;
	CPoint m_endPt;
};



#endif