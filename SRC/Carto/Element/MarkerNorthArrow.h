//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/4/15
// ������  ��ͼҪ�ء���ָ���� 
//////////////////////////////////////////////////////////////////////


#ifndef CMARKER_NORTH_ARROW_H
#define CMARKER_NORTH_ARROW_H
#include "IMapSurround.h"
//#include "ArrowMarkerSymbol.h"
#include "IMarkerElement.h"

namespace Element{


class CARTO_DLL CMarkerNorthArrow :
	public IMapSurround
{
public:
	CMarkerNorthArrow();
	CMarkerNorthArrow(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame);
	~CMarkerNorthArrow(void);

	virtual void serialization(SYSTEM::IArchive &ar); 

	GEOMETRY::geom::Envelope GetEnvelope();

	void GeometryChangedEvents();

protected:
	void DrawOnDrawMode(Display::IDisplayPtr pDisplay);

	void DrawMoveMode(Display::IDisplayPtr pDisplay);

	void ChangeGeometryEnvelopTo(GEOMETRY::geom::Envelope& newEnvelope);

	void DrawNormal(Display::IDisplayPtr pDisplay);

protected:
	BOOL m_bGeometryChanged;


};
typedef SYSTEM::CSmartPtr<CMarkerNorthArrow> CMarkerNorthArrowPtr;
}
#endif