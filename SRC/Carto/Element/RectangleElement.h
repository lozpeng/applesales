//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/15
// 描述：  标绘对象——矩形
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
