//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/15
// 描述：  制图要素——背景框
//////////////////////////////////////////////////////////////////////

#ifndef CSIMPLE_BACKGROUND_H
#define CSIMPLE_BACKGROUND_H
#include "IBackground.h"
#include "IFillSymbol.h"


namespace Element{

class CARTO_DLL CSimpleBackground :
	public IBackground
{
public:
	CSimpleBackground(void);
	~CSimpleBackground(void);
	CSimpleBackground(const GEOMETRY::geom::Geometry& geometry);

	void serialization(SYSTEM::IArchive &ar);

	SYSTEM::CSmartPtr<CSimpleBackground> Clone();

	void Draw(Display::IDisplayPtr pDisplay);
	void SetSymbol(Display::IFillSymbolPtr pFillSymbol);
	Display::IFillSymbolPtr GetSymbol();

protected:
	void InitFillSymbol();


protected:
	Display::IFillSymbolPtr m_pFillSymbol;

};

typedef SYSTEM::CSmartPtr<CSimpleBackground> CSimpleBackgroundPtr;
}
#endif