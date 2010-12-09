//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/23
// 描述：  标绘对象——贝塞尔曲线
//////////////////////////////////////////////////////////////////////

#ifndef CBEZIER_CURVE_ELEMENT_H
#define CBEZIER_CURVE_ELEMENT_H
#include "IElement.h"
namespace Element{

class CARTO_DLL CBezierCurveElement :
	public IElement
{
public:
	CBezierCurveElement(void);
	CBezierCurveElement(const GEOMETRY::geom::Geometry& geometry);
	CBezierCurveElement(GEOMETRY::geom::Coordinate& coord);
	~CBezierCurveElement(void);

	void serialization(SYSTEM::IArchive &ar);


	void DrawNormal(Display::IDisplayPtr pDisplay);

	void AddVertix(GEOMETRY::geom::Coordinate coord);
	void InsertVertix(long lIndex, GEOMETRY::geom::Coordinate coord);
	void RemoveVertix(long lIndex);
	void MoveVertixTo(long lIndex,GEOMETRY::geom::Coordinate coord);
};

typedef SYSTEM::CSmartPtr<CBezierCurveElement> CBezierCurveElementPtr;
}
#endif
