//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/4/10
// ������  ��ͼҪ�ء�������  
//////////////////////////////////////////////////////////////////////

#ifndef CNEAT_LINE_H
#define CNEAT_LINE_H

#include "IMapSurround.h"
namespace Element{
class CNeatLine :
	public IMapSurround
{
public:
	CNeatLine();
	CNeatLine(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame);
	~CNeatLine(void);

	void DrawNormal(Display::IDisplayPtr pDisplay);

	virtual void serialization(SYSTEM::IArchive &ar); 
};

typedef SYSTEM::CSmartPtr<CNeatLine>CNeatLinePtr;

}

#endif
