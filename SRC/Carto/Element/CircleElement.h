//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/23
// ������  �����󡪡�Բ
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
