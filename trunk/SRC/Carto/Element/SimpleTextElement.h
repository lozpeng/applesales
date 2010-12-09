//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/15
// 描述：  标绘对象——文字
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
