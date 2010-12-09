//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/4/10
// 描述：  制图要素——单线  
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
