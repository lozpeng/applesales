#ifndef CPARAGRAPH_TEXT_ELEMENT_H
#define CPARAGRAPH_TEXT_ELEMENT_H
#include "ITextElement.h"
#include "IFrameProperty.h"

namespace Element{
class CARTO_DLL CParagraphTextElement :public ITextElement, public IFrameProperty
{
public:
	CParagraphTextElement();
	CParagraphTextElement(const GEOMETRY::geom::Geometry& geometry);
	~CParagraphTextElement(void);

	void DrawNormal(Display::IDisplayPtr pDisplay);

};
typedef SYSTEM::CSmartPtr<CParagraphTextElement> CParagraphTextElementPtr;
}
#endif;
