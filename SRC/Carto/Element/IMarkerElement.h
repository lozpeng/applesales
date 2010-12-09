#ifndef IMARKER_ELEMENT_H
#define IMARKER_ELEMENT_H

#include "IGraphicElement.h"
#include "IMarkerSymbol.h"

namespace Element{
class CARTO_DLL IMarkerElement :
	public IGraphicElement
{
public:
	IMarkerElement(void);
	IMarkerElement(const GEOMETRY::geom::Geometry& geometry);
	~IMarkerElement(void);

	void serialization(SYSTEM::IArchive &ar);

	virtual GEOMETRY::geom::Envelope GetEnvelope();

	virtual void MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord);

	virtual BOOL Select(GEOMETRY::geom::Geometry* pSelectGeometry, long lSpatialRelation, CElementCollection& selectedSubElements,double dbTolerance=0.0);

	void GeometryChangedEvents();

protected:
	
	virtual void DrawOnDrawMode(Display::IDisplayPtr pDisplay);

	virtual void DrawMoveMode(Display::IDisplayPtr pDisplay);

	virtual void ChangeGeometryEnvelopTo(GEOMETRY::geom::Envelope& newEnvelope);


protected:
	BOOL m_bGeometryChanged;

};

typedef SYSTEM::CSmartPtr<IMarkerElement> IMarkerElementPtr;
}

#endif
