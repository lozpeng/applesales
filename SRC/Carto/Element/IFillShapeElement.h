#ifndef IFILL_SHAPE_ELEMENT_H
#define IFILL_SHAPE_ELEMENT_H
#include "IGraphicElement.h"
#include "ISymbol.h"

namespace Element{

class CARTO_DLL IFillShapeElement :
	public IGraphicElement
{
public:
	IFillShapeElement(void);
	IFillShapeElement(const GEOMETRY::geom::Geometry& geometry);
	virtual~IFillShapeElement(void);

	virtual void DrawNormal(Display::IDisplayPtr pDisplay);

	/**
	* 功能描述：序列化操作
	* @param SYSTEM::IArchive &ar 档案文件流
	* @return  void
	*/
	virtual void serialization(SYSTEM::IArchive &ar);   

	
protected:
	void InitFillShape();

	virtual void DrawOnDrawMode(Display::IDisplayPtr pDisplay);

	virtual void DrawMoveMode(Display::IDisplayPtr pDisplay);

protected:
	Display::IFillSymbolPtr m_pFillDraftSymbol;
	Display::IFillSymbolPtr m_pOnDrawSymbol;
	Display::IFillSymbolPtr m_pMoveSymbol;

};

}
#endif;
