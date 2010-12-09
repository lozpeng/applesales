#ifndef ITEXT_ELEMENT_H
#define ITEXT_ELEMENT_H
#include "IElement.h"
#include "TextSymbol.h"

namespace Element{
class CARTO_DLL ITextElement :
	public IElement
{
public:
	ITextElement();
	ITextElement(const GEOMETRY::geom::Geometry& geometry);
	~ITextElement(void);

	void serialization(SYSTEM::IArchive &ar);

	void SetScaleWithMap(BOOL bScaleWithMap);
	void SetText(std::string text){m_text = text;}; 
	std::string GetText(){return m_text;};

	void SetDrawBg(BOOL bDraw);
	BOOL GetDrawBg();

	void SetFillSymbol(Display::CSimpleFillSymbolPtr pFillSymbol);
	Display::CSimpleFillSymbolPtr GetFillSymbol();

	void ChangeGeometryEnvelopTo(GEOMETRY::geom::Envelope& newEnvelope);

	virtual void GeometryChangedEvents();



protected:
	BOOL	m_bScaleWithMap;
	std::string m_text;
	BOOL m_bDrawBg;
	Display::CSimpleFillSymbolPtr m_pFillSymbol;
	GEOMETRY::geom::Coordinate m_coordOrg;//文字0度时envelope的左下角坐标

};
typedef SYSTEM::CSmartPtr<ITextElement> ITextElementPtr;
}
#endif;
