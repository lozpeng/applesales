//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2011-11-21
// 描述：  折线量测对象
//////////////////////////////////////////////////////////////////////

#ifndef CPOLYLINEMEASURE_ELEMENT_H
#define CPOLYLINEMEASURE_ELEMENT_H
#include "PolygonElement.h"
namespace Element{

class CARTO_DLL CPolygonMeasureElement :
	public CPolygonElement
{
public:
	CPolygonMeasureElement(void);
	CPolygonMeasureElement(const GEOMETRY::geom::Geometry& geometry);
	CPolygonMeasureElement(GEOMETRY::geom::Coordinate& coord);
	~CPolygonMeasureElement(void);

	void serialization(SYSTEM::IArchive &ar);

	void DrawNormal(Display::IDisplayPtr pDisplay);

	bool bDrawCloseButton;
 
	void DrawOnDrawMode(Display::IDisplayPtr pDisplay);
private:
	void DrawVertixLabel(Display::IDisplayPtr pDisplay);//显示量测值
	void DrawVertixCircle(Display::IDisplayPtr pDisplay);//显示量测点

	void DrawCloseButton(Display::IDisplayPtr pDisplay);//绘制关闭按钮
	

	protected:
	Display::IFillSymbolPtr m_pVertixSymbol;
	SYSTEM::SYS_UNIT_TYPE  m_unitType;  //量测单位
};

typedef SYSTEM::CSmartPtr<CPolygonMeasureElement> CPolygonMeasureElementPtr;
}
#endif
