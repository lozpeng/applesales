//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2011-11-21
// ������  �����������
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

	void SetUnitType(SYSTEM::SYS_UNIT_TYPE unitType){m_unitType = unitType;} //�������ⵥλ

	bool bDrawCloseButton;

private:
	void DrawVertixLabel(Display::IDisplayPtr pDisplay);//��ʾ����ֵ
	void DrawVertixCircle(Display::IDisplayPtr pDisplay);//��ʾ�����

	void DrawCloseButton(Display::IDisplayPtr pDisplay);//���ƹرհ�ť



	SYSTEM::SYS_UNIT_TYPE  m_unitType;  //���ⵥλ

};

typedef SYSTEM::CSmartPtr<CPolylineMeasureElement> CPolylineMeasureElementPtr;
}
#endif
