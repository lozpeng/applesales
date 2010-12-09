#ifndef IFRAME_ELEMENT_BASE_H
#define IFRAME_ELEMENT_BASE_H
#include "IElement.h"
#include "IFrameProperty.h"
#include "IDisplay.h"
#include "TextSymbol.h"

namespace Element{

class CARTO_DLL IFrameElementBase : public IElement, public IFrameProperty
{
public:
	IFrameElementBase(void);
	IFrameElementBase(const GEOMETRY::geom::Geometry& geometry);
	~IFrameElementBase(void);

	virtual void serialization(SYSTEM::IArchive &ar);

	//virtual IElementPtr Clone()=0;
	virtual BOOL Select(GEOMETRY::geom::Geometry* pSelectGeometry, long lSpatialRelation, CElementCollection& selectedSubElements,double dbTolerance=0.0);


	virtual void SetDrawBorder(BOOL bDrawBorder);
	virtual BOOL GetDrawBorder(); 

	virtual void SetDrawBackground(BOOL bDrawBackground);
	virtual BOOL GetDrawBackground(); 

	virtual void SetDrawShadow(BOOL bDrawShadow);
	virtual BOOL GetDrawShadow(); 
	
	virtual void GetThumbnail(long* bitmapHandle);	


protected:
	virtual void DrawBackground(Display::IDisplayPtr pDisplay);
	virtual void DrawForeground(Display::IDisplayPtr pDisplay);
	
	virtual void DrawDraft( Display::IDisplayPtr pDisplay);
	virtual void DrawPrint(Display::IDisplayPtr pDisplay);
	virtual void DrawOnDrawMode(Display::IDisplayPtr pDisplay);
	virtual void DrawMoveMode(Display::IDisplayPtr pDisplay);

	//图形变化响应函数
	virtual void GeometryChangedEvents();


protected:
	BOOL	m_bDrawBorder;

	BOOL	m_bDrawBackground;

	BOOL	m_bDrawShadow;

	Display::CTextSymbolPtr m_FrameNameSymbol;
};

typedef SYSTEM::CSmartPtr<IFrameElementBase> IFrameElementBasePtr;
}
#endif
