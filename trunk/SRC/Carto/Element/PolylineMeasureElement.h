//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2011-11-21
// 描述：  折线量测对象
//////////////////////////////////////////////////////////////////////

#ifndef CPOLYLINEMEASURE_ELEMENT_H
#define CPOLYLINEMEASURE_ELEMENT_H
#include "PolylineElement.h"
namespace Element{

class CARTO_DLL CPolylineMeasureElement :
	public CPolylineElement
{
public:
	CPolylineMeasureElement(void);
	CPolylineMeasureElement(const GEOMETRY::geom::Geometry& geometry);
	CPolylineMeasureElement(GEOMETRY::geom::Coordinate& coord);
	~CPolylineMeasureElement(void);

	void serialization(SYSTEM::IArchive &ar);

	void DrawNormal(Display::IDisplayPtr pDisplay);

	void SetUnitType(SYSTEM::SYS_UNIT_TYPE unitType){m_unitType = unitType;} //设置量测单位

	bool bDrawCloseButton;

private:
	void DrawVertixLabel(Display::IDisplayPtr pDisplay);//显示量测值
	void DrawVertixCircle(Display::IDisplayPtr pDisplay);//显示量测点

	void DrawCloseButton(Display::IDisplayPtr pDisplay);//绘制关闭按钮



	SYSTEM::SYS_UNIT_TYPE  m_unitType;  //量测单位

};

typedef SYSTEM::CSmartPtr<CPolylineMeasureElement> CPolylineMeasureElementPtr;
}
#endif
