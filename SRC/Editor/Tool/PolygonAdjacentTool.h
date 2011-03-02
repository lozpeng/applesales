#ifndef _ACTION_POLYGON_ADJACENT_H
#define _ACTION_POLYGON_ADJACENT_H

#include "IAction.h"
#include <vector>
using std::vector;

namespace otEditor
{
	//生成邻接多边形的工具
	class CActionPolygonAdjacent : public otFramework::IAction
	{
	public:
		CActionPolygonAdjacent();
		~CActionPolygonAdjacent();

		//
	public:
		//初始化
		void Triger(void);

		//鼠标事件处理
		void LButtonDownEvent (UINT nFlags, CPoint point);
		void LButtonDblClkEvent (UINT nFlags, CPoint point);
		void MouseMoveEvent (UINT nFlags, CPoint point);

	public:
		//清除
		void Clear();
		
		//绘制临时图形 
		void ActionDraw();

		//生成邻接多边形
		void AdjacentPolygon();

	private:
		//图形
		vector<Geometry*> m_shapes;	

		//图形ID
		vector<long> m_shapeIds;

		//图层
		vector<otCarto::ILayer*> m_players;

	private:
		//鼠标点击保存数组
		vector<CPoint> m_Points;

		bool m_bIsDrawing;
	};

	#endif
}