#ifndef _ACTION_EDITDRAWCIRCLE_H_
#define _ACTION_EDITDRAWCIRCLE_H_

#include "IAction.h"
#include "IDisplay.h"
#include <geometry/geom/Geometry.h>

namespace otEditor
{

	class CActionEditDrawCircle: public otFramework::IAction
	{
	public:
		CActionEditDrawCircle(void);
		virtual ~CActionEditDrawCircle(void);

	public:
		//初始化
		void Triger(void);

		void LButtonDownEvent (UINT nFlags, CPoint point);

		void MouseMoveEvent (UINT nFlags, CPoint point);

		void ActionDraw();

		void SplitCircle(TT_GEOMETRY::geom::Geometry *pGeometry);

	private:
		//向图层中添加矩形
		void AddCircle(void);

	private:
		bool m_bStartDraw;//绘制中或绘制结束


		//圆心和终点
		CPoint m_centralPt;
		CPoint m_endPt;

	};

}

#endif