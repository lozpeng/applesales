//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2011-11-21
// ������  �����������
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
	void DrawVertixLabel(Display::IDisplayPtr pDisplay);//��ʾ����ֵ
	void DrawVertixCircle(Display::IDisplayPtr pDisplay);//��ʾ�����

	void DrawCloseButton(Display::IDisplayPtr pDisplay);//���ƹرհ�ť
	

	protected:
	Display::IFillSymbolPtr m_pVertixSymbol;
	SYSTEM::SYS_UNIT_TYPE  m_unitType;  //���ⵥλ
};

typedef SYSTEM::CSmartPtr<CPolygonMeasureElement> CPolygonMeasureElementPtr;
}
#endif
