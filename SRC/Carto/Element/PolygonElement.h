//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/15
// ������  �����󡪡������
//////////////////////////////////////////////////////////////////////


#ifndef CPOLYGON_ELEMENT_H
#define CPOLYGON_ELEMENT_H
#include "IFillShapeElement.h"
namespace Element{

class CARTO_DLL CPolygonElement :
	public IFillShapeElement
{
public:
	CPolygonElement();
	CPolygonElement(const GEOMETRY::geom::Geometry& geometry);
	CPolygonElement(GEOMETRY::geom::Coordinate& coord);
	~CPolygonElement(void);

	virtual void serialization(SYSTEM::IArchive &ar);   

	void AddVertix(GEOMETRY::geom::Coordinate coord);
	void InsertVertix(long lIndex, GEOMETRY::geom::Coordinate coord);
	void RemoveVertix(long lIndex);
	void MoveVertixTo(long lIndex,GEOMETRY::geom::Coordinate coord);

protected:
	Display::IFillSymbolPtr m_pVertixSymbol;

};

typedef SYSTEM::CSmartPtr<CPolygonElement> CPolygonElementPtr;
}
#endif
