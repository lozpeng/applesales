//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/23
// 描述：  标绘对象——椭圆
//////////////////////////////////////////////////////////////////////

#ifndef CELLPSE_ELEMENT_H
#define CELLPSE_ELEMENT_H
#include "IFillShapeElement.h"
namespace Element{
class CARTO_DLL CEllipseElement :
	public IFillShapeElement
{
public:
	CEllipseElement();
	CEllipseElement(const GEOMETRY::geom::Geometry& geometry);
	CEllipseElement(GEOMETRY::geom::Envelope env);
	~CEllipseElement(void);

	virtual void serialization(SYSTEM::IArchive &ar); 

//	IElementPtr Clone();

	void Update(GEOMETRY::geom::Envelope& env);

protected:



};
typedef SYSTEM::CSmartPtr<CEllipseElement> CEllipseElementPtr;
}
#endif;
