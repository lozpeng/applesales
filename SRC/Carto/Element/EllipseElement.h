//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/23
// ������  �����󡪡���Բ
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
