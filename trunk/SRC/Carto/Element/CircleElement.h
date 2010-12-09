//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/23
// 描述：  标绘对象——圆
//////////////////////////////////////////////////////////////////////

#ifndef ICIRCLE_ELEMENT2_H
#define ICIRCLE_ELEMENT2_H
#include "IFillShapeElement.h"
namespace Element{
class CARTO_DLL CCircleElement :
	public IFillShapeElement
{
public:
	CCircleElement();
	CCircleElement(const GEOMETRY::geom::Geometry& geometry);
    CCircleElement(GEOMETRY::geom::Coordinate& center, double radius);
	~CCircleElement(void);

	virtual void serialization(SYSTEM::IArchive &ar);  

	void Update(GEOMETRY::geom::Coordinate center, double radius);


};
typedef SYSTEM::CSmartPtr<CCircleElement> CCircleElementPtr;
}
#endif;
