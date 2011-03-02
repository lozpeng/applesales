#ifndef _ACTION_EDITDRAWCIRCLE_H_
#define _ACTION_EDITDRAWCIRCLE_H_

#include "ITool.h"
#include "IDisplay.h"
#include <geometry/geom/Geometry.h>

namespace Editor
{

	class CEditDrawCircleTool: public Framework::ITool
	{
	public:
		CEditDrawCircleTool(void);
		virtual ~CEditDrawCircleTool(void);

	public:
		//初始化
		
		void Initialize(Framework::IUIObject *pTargetControl);

		void LButtonDownEvent (UINT nFlags, CPoint point);

		void MouseMoveEvent (UINT nFlags, CPoint point);

		void ActionDraw();

		void SplitCircle(GEOMETRY::geom::Geometry *pGeometry);

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