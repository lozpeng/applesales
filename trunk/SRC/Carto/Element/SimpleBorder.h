//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/15
// 描述：  制图要素——边框
//////////////////////////////////////////////////////////////////////

#ifndef CSIMPLE_BORDER_H
#define CSIMPLE_BORDER_H
#include "IBorder.h"
#include "SimpleFillSymbol.h"


namespace Element{

class CARTO_DLL CSimpleBorder :
	public IBorder
{
public:
	CSimpleBorder(void);
	//构造函数 pGeometry形状，内部释放
	CSimpleBorder(const GEOMETRY::geom::Geometry& geometry);
	~CSimpleBorder(void);

	void serialization(SYSTEM::IArchive &ar);

	SYSTEM::CSmartPtr<CSimpleBorder> Clone();

	void SetSymbol(Display::ILineSymbolPtr pLineSymbol);
	Display::ILineSymbolPtr GetSymbol();

	void Draw(Display::IDisplayPtr pDisplay);

protected:
	void InitFillSymbol();

protected:
	Display::CSimpleFillSymbolPtr m_pFillSymbol;

};

typedef SYSTEM::CSmartPtr<CSimpleBorder> CSimpleBorderPtr;
}
#endif
