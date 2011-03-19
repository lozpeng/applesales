#ifndef _GEOMETRY_SKETCH_H
#define _GEOMETRY_SKETCH_H

#include "IDisplay.h"
#include <geometry/geom/Geometry.h>

namespace Display
{
/*********************************************************************
*画笔用来创建一个几何图形，可以动态的添加点，并且可以将图形绘制到Display
* 通常在矢量编辑，或者要临时绘制一个图形时使用 
*
*********************************************************************/
class DISPLAY_DLL CGeometrySketch
{
public:

	CGeometrySketch(int GeometryType,bool bhasZ =false,bool bhasM=false);

	virtual ~CGeometrySketch(void);

public:
	GEOMETRY::geom::Geometry* GetGeometry() const {return m_pGeometry;}

	void Draw(IDisplayPtr pDisplay);

	//替换掉当前图形,并更新画笔信息
	void ReplaceGeometry(GEOMETRY::geom::Geometry* pGeometry,long &curPart,bool &bpartFinish);


	int GetGeometryType() const;

	bool IsMultiPart() const;

	int GetCurPartIndex() const {return m_icurPart;}

	void FinishPart();

	void AddPoint(GEOMETRY::geom::Coordinate &coord);

	//将画笔对象清空，一般在结束当前图形的情况下调用
	void SetEmpty();

	bool IsEmpty() const;

	bool  IsRightGeometry() const;

	bool  IsCurPartFinish() const{return m_bCurPartFinish;}

	GEOMETRY::geom::Coordinate GetlastPoint() const;

	//得到当前Part的第一个点
	GEOMETRY::geom::Coordinate GetCurPartFirstPt() const;

	void MouseMove(GEOMETRY::geom::Coordinate &coord);

private:
	void InitSymbol();
public:
	GEOMETRY::geom::Geometry *m_pGeometry;

	//当前鼠标点的坐标
	GEOMETRY::geom::Coordinate m_MousePt;

	//当前部分序号，多边形、多点、多线、多面的类型有多个Part组成
	int m_icurPart;

	bool        m_bCurPartFinish;

	bool        m_bMultiPart;

	//鼠标是否移动
	bool        m_bMouseMove;

	ISymbolPtr  m_ptSymbol;
	ISymbolPtr  m_lineSymbol;
};

typedef SYSTEM::CSmartPtr<CGeometrySketch> CGeometrySketchPtr;

}

#endif