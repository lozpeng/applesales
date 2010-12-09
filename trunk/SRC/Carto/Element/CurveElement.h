#ifndef CCURVE_ELEMENT_H
#define CCURVE_ELEMENT_H
#include "IElement.h"
namespace Element{
class CARTO_DLL CCurveElement :
	public IElement
{
public:
	CCurveElement();
	CCurveElement(const GEOMETRY::geom::Geometry& geometry);
	~CCurveElement(void);

	void serialization(SYSTEM::IArchive &ar);

//	IElementPtr Clone();

	void DrawNormal(Display::IDisplayPtr pDisplay);

protected:



};
typedef SYSTEM::CSmartPtr<CCurveElement> CCurveElementPtr;
}
#endif;
