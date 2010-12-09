//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/23
// ������  �����󡪡�����������
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
