//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/15
// ������  �����󡪡�����
//////////////////////////////////////////////////////////////////////


#ifndef IRECTANGLE_ELEMENT_H
#define IRECTANGLE_ELEMENT_H
#include "IFillShapeElement.h"
namespace Element{

class CARTO_DLL CRectangleElement :
	public IFillShapeElement
{
public:
	CRectangleElement();
	CRectangleElement(const GEOMETRY::geom::Geometry& geometry);
	CRectangleElement(GEOMETRY::geom::Envelope& envelope);
	CRectangleElement(double xMin, double yMin, double xMax, double yMax);
	~CRectangleElement(void);

	virtual void serialization(SYSTEM::IArchive &ar);   

	//IElementPtr Clone();

	void Update(double xStart,double yStart, double xEnd,double yEnd);

};

typedef SYSTEM::CSmartPtr<CRectangleElement> CRectangleElementPtr;
}
#endif
