#ifndef _ACTION_EDIT_FEATURE_H_
#define _ACTION_EDIT_FEATURE_H_

#include "IAction.h"
#include <geometry/geom/Geometry.h>

namespace otEditor
{

class  EDITOR_DLL CActionEditFeature : public otFramework::IAction
{
public:
	CActionEditFeature();
	~CActionEditFeature();
public:

	enum Status 
	{
		On_None,
		On_Selection,
		On_ShapeMove,
		On_Vertex,    //鼠标在节点上
		On_Line,      //鼠标在线上
		On_VertexMove,  //节点移动
		On_SelectMoreShape, //选中了多个图形
		On_MoveMoreShape   //移动多个图形
	};
public:
	void Triger();
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);

	void LButtonDblClkEvent (UINT nFlags, CPoint point);

	void RButtonDownEvent (UINT nFlags, CPoint point);

	//插入节点
	void InsertVertex();
	//删除节点
	void DelVertex();
	//移动节点
	void MoveVertex();
	//显示属性
	void ShowAttribute();

private:
	void ClearMoveGeometrys();

	//获取编辑图层中选中的图形
	BOOL GetSelectGeometrys();

	BOOL InstanceEditObject();

	//绘制移动的图形
	void DrawMovedGeometrys();

private:
	//上次要素移动时的点
	CPoint m_lastmovePt;

	//误差
	double m_dTolerance;

	long   m_curPart;

	long   m_curVertexIndex;
	bool   m_bMoved;

	bool   m_bContain;

	//当前节点的坐标
	TT_GEOMETRY::geom::Coordinate m_curVertex;

	//当前在线上的点
	TT_GEOMETRY::geom::Coordinate m_insertPt;

	//移动的图形数组
	std::vector<TT_GEOMETRY::geom::Geometry*> m_moveGeometrys;

	std::vector<long> m_shpIds;
	std::vector<otCarto::ILayer*> m_layers;
};

}


#endif