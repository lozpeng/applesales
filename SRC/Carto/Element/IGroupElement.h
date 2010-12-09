//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/4/13
// 描述：  标绘对象组
//////////////////////////////////////////////////////////////////////

#ifndef ICIRCLE_ELEMENT_H
#define ICIRCLE_ELEMENT_H
#include "IGraphicElement.h"

namespace Element{

class CARTO_DLL IGroupElement :
	public IGraphicElement
{
public:
	IGroupElement(void);
	~IGroupElement(void);
};


typedef SYSTEM::CSmartPtr<IGroupElement> IGroupElementPtr;
}
#endif