#ifndef CSIMPLE_SHADOW_H
#define CSIMPLE_SHADOW_H
#include "IShadow.h"
#include "IFillSymbol.h"


namespace Element{

class CARTO_DLL CSimpleShadow :
	public IShadow
{
public:
	CSimpleShadow(void);
	~CSimpleShadow(void);
	CSimpleShadow(const GEOMETRY::geom::Geometry& geometry);

	void serialization(SYSTEM::IArchive &ar);

	SYSTEM::CSmartPtr<CSimpleShadow> Clone();

	void Draw(Display::IDisplayPtr pDisplay);
	void SetSymbol(Display::IFillSymbolPtr pFillSymbol);
	Display::IFillSymbolPtr GetSymbol();

protected:
	void InitFillSymbol();


protected:
	Display::IFillSymbolPtr m_pFillSymbol;

};

typedef SYSTEM::CSmartPtr<CSimpleShadow> CSimpleShadowPtr;
}
#endif