//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/3/15
// ������  �����󡪡�����
//////////////////////////////////////////////////////////////////////

#ifndef CSIMPLE_TEXT_ELEMENT_H
#define CSIMPLE_TEXT_ELEMENT_H
#include "ITextElement.h"
namespace Element{
class CARTO_DLL CSimpleTextElement :
	public ITextElement
{
public:
	CSimpleTextElement();
	CSimpleTextElement(const GEOMETRY::geom::Geometry& geometry);
	~CSimpleTextElement(void);

	void serialization(SYSTEM::IArchive &ar);


	void Move(double dx, double dy);


	void DrawNormal(Display::IDisplayPtr pDisplay);

};
typedef SYSTEM::CSmartPtr<CSimpleTextElement> CSimpleTextElementPtr;
}
#endif;
