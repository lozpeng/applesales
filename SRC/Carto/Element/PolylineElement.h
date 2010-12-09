//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/15
// 描述：  标绘对象——折线
//////////////////////////////////////////////////////////////////////

#ifndef CPOLYLINE_ELEMENT_H
#define CPOLYLINE_ELEMENT_H
#include "IElement.h"
namespace Element{

class CARTO_DLL CPolylineElement :
	public IElement
{
public:
	CPolylineElement(void);
	CPolylineElement(const GEOMETRY::geom::Geometry& geometry);
	CPolylineElement(GEOMETRY::geom::Coordinate& coord);
	~CPolylineElement(void);

	void serialization(SYSTEM::IArchive &ar);

	void DrawNormal(Display::IDisplayPtr pDisplay);

	void AddVertix(GEOMETRY::geom::Coordinate coord);
	void InsertVertix(long lIndex, GEOMETRY::geom::Coordinate coord);
	void RemoveVertix(long lIndex);
	void MoveVertixTo(long lIndex,GEOMETRY::geom::Coordinate coord);
};

typedef SYSTEM::CSmartPtr<CPolylineElement> CPolylineElementPtr;
}
#endif
