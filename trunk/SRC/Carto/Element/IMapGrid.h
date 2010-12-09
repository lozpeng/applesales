//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/4/10
// 描述：  制图要素——地图网格  其它格网的基类
//////////////////////////////////////////////////////////////////////

#ifndef IMAP_GRID_H
#define IMAP_GRID_H

#include "IGrid.h"

namespace Element{

class CMapFrame;
class CARTO_DLL IMapGrid :public IGrid
{
public:
	IMapGrid();
	IMapGrid(CMapFrame* pMapFrame);
	~IMapGrid(void);

	virtual void serialization(SYSTEM::IArchive &ar)=0;  


	CMapFrame* GetMapFrame();
	void SetMapFrame(CMapFrame* mapFrame);

protected:
	CMapFrame* m_pMapFrame;

};

typedef SYSTEM::CSmartPtr<IMapGrid> IMapGridPtr;
}
#endif
