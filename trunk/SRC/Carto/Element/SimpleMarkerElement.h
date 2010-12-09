//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/15
// 描述：  标绘对象——点
//////////////////////////////////////////////////////////////////////

#ifndef CSIMPLE_MARKER_ELEMENT_H
#define CSIMPLE_MARKER_ELEMENT_H
#include "IMarkerElement.h"

namespace Element{


class CARTO_DLL CSimpleMarkerElement :
	public IMarkerElement
{
public:
	CSimpleMarkerElement(void);
	CSimpleMarkerElement(const GEOMETRY::geom::Geometry& geometry);
	~CSimpleMarkerElement(void);

	void serialization(SYSTEM::IArchive &ar);

	GEOMETRY::geom::Envelope GetEnvelope();


protected:
	void DrawNormal(Display::IDisplayPtr pDisplay);

};
typedef SYSTEM::CSmartPtr<CSimpleMarkerElement> CSimpleMarkerElementPtr;
}
#endif