#ifndef _ACTION_EDITDRAWELLIPSE_H_
#define _ACTION_EDITDRAWELLIPSE_H_

#include "IAction.h"
#include "IDisplay.h"
#include <geometry/geom/Geometry.h>

namespace otEditor
{

	class CActionEditDrawEllipse: public otFramework::IAction
	{
	public:
		CActionEditDrawEllipse(void);
		virtual ~CActionEditDrawEllipse(void);

	public:
		//初始化
		void Triger(void);

		void LButtonDownEvent (UINT nFlags, CPoint point);

		void MouseMoveEvent (UINT nFlags, CPoint point);

		void ActionDraw();

	private:
		//向图层中添加椭圆形
		void AddEllipse(CPoint ulPt,CPoint lrPt);

		//分割椭圆形
		void SplitEllipse(TT_GEOMETRY::geom::Geometry *pGeometry);

	private:
		bool m_bStartDraw;//绘制中或绘制结束

		CPoint m_ulPt; //外接矩形的左上角点
		CPoint m_lrPt; //外接矩形右下角点

	};

}

#endif