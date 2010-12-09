//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/4/10
// 描述：  制图要素——地图网格集
//////////////////////////////////////////////////////////////////////

#ifndef CMAP_GRIDS_H
#define CMAP_GRIDS_H
#include "IMapGrid.h"
#include "ISerialization.h"

namespace Element{

	class CARTO_DLL CMapGrids : public SYSTEM::ISerialization
	{
	public:
		CMapGrids(void);
		~CMapGrids(void);

		void serialization(SYSTEM::IArchive &ar);

		void AddMapGrid (IMapGridPtr pMapGird);
		void DeleteMapGrid (IMapGridPtr pMapGird);
		void DeleteMapGridByIndex (int nIndex);
		void ClearMapGrids();

		void SetMapGrid(int nIndex, IMapGridPtr pMapGird);
		IMapGridPtr GetMapGrid(int nIndex);
		int GetGridCount();


	protected:
		std::vector<IMapGridPtr> m_vecMapGrids;
	};

}
#endif
