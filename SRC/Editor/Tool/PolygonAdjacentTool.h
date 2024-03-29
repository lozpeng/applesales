#ifndef _ACTION_POLYGON_ADJACENT_H
#define _ACTION_POLYGON_ADJACENT_H

#include "ITool.h"
#include "ILayer.h"

#include <vector>
using std::vector;

namespace Editor
{
	//生成邻接多边形的工具
	class CActionPolygonAdjacent : public Framework::ITool
	{
	public:
		CActionPolygonAdjacent();
		~CActionPolygonAdjacent();

		//
	public:
		//初始化
		void Initialize(Framework::IUIObject *pTargetControl);

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
		vector<Carto::ILayer*> m_players;

	private:
		//鼠标点击保存数组
		vector<CPoint> m_Points;

		bool m_bIsDrawing;
	};

	#endif
}