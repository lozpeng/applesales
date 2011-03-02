#ifndef _ACTION_EDITDRAWRECT_H_
#define _ACTION_EDITDRAWRECT_H_

#include "IAction.h"
#include "IDisplay.h"
#include <geometry/geom/Geometry.h>

namespace otEditor
{

class CActionEditDrawRect: public otFramework::IAction
{
public:
	CActionEditDrawRect(void);
	virtual ~CActionEditDrawRect(void);

public:
	//初始化
	void Triger(void);

	void LButtonDownEvent (UINT nFlags, CPoint point);

	void MouseMoveEvent (UINT nFlags, CPoint point);

	void ActionDraw();

private:
	//向图层中添加矩形
	void AddRect(CPoint ulPt,CPoint lrPt);

private:
	bool m_bStartDraw;//绘制中或绘制结束

	CPoint m_ulPt; //矩形的左上角点
	CPoint m_lrPt; //矩形右下角点

};

}

#endif