//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/4/10
// 描述：  制图要素——公里格网
//////////////////////////////////////////////////////////////////////

#ifndef CGROUND_COORD_GRID_H
#define CGROUND_COORD_GRID_H

#include "IMapGrid.h"

namespace Element{



class CARTO_DLL CMeasuredGrid :public IMapGrid
{
public:
	CMeasuredGrid();
	CMeasuredGrid(CMapFrame* pMapFrame);
	~CMeasuredGrid(void);

	virtual void serialization(SYSTEM::IArchive &ar); 

	void Draw(Display::IDisplayPtr pDisplay);

	IGridPtr Clone();

protected:
	void DrawGrid(Display::IDisplayPtr pDisplay);
	void DrawTick(Display::IDisplayPtr pDisplay);
	void DrawSubTick(Display::IDisplayPtr pDisplay);
	void DrawLabel(Display::IDisplayPtr pDisplay);
	void DrawBorder(Display::IDisplayPtr pDisplay);
	
	
	void CalcGridLines(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, double XOrigin, double YOrigin, 
		double XInterval, double YInterval, GEOMETRY::geom::Geometry*& pLines);
	void CalcGridMarkers(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, double XOrigin, double YOrigin, 
		double XInterval, double YInterval, GEOMETRY::geom::Geometry*& pMarkers);
	void CalLabels(Display::IDisplayPtr pDisplay, std::vector<stGridLabel>& vecVerticalLabel, std::vector<stGridLabel>& vecHorizontalLabel, 
		std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>>& vecVerLabels, std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>>& vecHorLabels,
		double labelOffset, Display::CTextSymbol* pVerticalTextSym,
		Display::CTextSymbol* pHorizontalTextSym, double tickSpacePage);

	void DrawNormal(Display::IDisplayPtr pDisplay);

	void RegulateOrigin(BOOL bDynamicXYOrg, double& XOrigin, double& YOrigin, double& XInterval, double& YInterval, GEOMETRY::geom::Envelope& Env);

};

typedef SYSTEM::CSmartPtr<CMeasuredGrid> CMeasuredGridPtr;
}
#endif
