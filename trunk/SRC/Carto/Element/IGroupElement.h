//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/4/13
// ������  ��������
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