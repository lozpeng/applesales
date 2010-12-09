//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/4/14
// 描述：  制图要素  其它要素的基类
//////////////////////////////////////////////////////////////////////


#ifndef IMAP_SURROUND_H
#define IMAP_SURROUND_H
#include "IDisplay.h"
#include "IFrameElementBase.h"
namespace Element{

	class CMapFrame;

class CARTO_DLL IMapSurround: public IFrameElementBase
{
public:
	IMapSurround(void);
	IMapSurround(CMapFrame* pMapFrame);
	IMapSurround(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame);
	virtual ~IMapSurround(void);

	virtual void serialization(SYSTEM::IArchive &ar); 

	virtual IElementPtr Clone();

	void SetMapFrame(CMapFrame* pMapFrame);
	CMapFrame* GetMapFrame();

	long GetMapFrameID(){return m_MapFrameID;};

	virtual void DelayEvent(BOOL bDelay);

	virtual void Refresh();


protected:
	virtual void MapFrameSettedEvent();
	
protected:
	CMapFrame* m_pMapFrame;
	long m_MapFrameID;
};

typedef SYSTEM::CSmartPtr<IMapSurround> IMapSurroundPtr;
}
#endif
