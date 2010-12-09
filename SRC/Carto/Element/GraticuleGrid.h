#ifndef CGEO_COORD_GRID_H
#define CGEO_COORD_GRID_H

#include "IMapGrid.h"

namespace Element{

	enum GridLabelContent
	{
		GLC_D_M_S, 
		GLC_D_M, 
		GLC_D
	};

class CARTO_DLL CGraticuleGrid :public IMapGrid
{
public:
	CGraticuleGrid();
	CGraticuleGrid(CMapFrame* pMapFrame);
	~CGraticuleGrid(void);

	virtual void serialization(SYSTEM::IArchive &ar); 

	void SetGridLabelContent(int enumGridLabelContent);
	int  GetGridLabelContent();
	

	void Draw(Display::IDisplayPtr pDisplay);

	IGridPtr Clone();

	CMapFrame* GetMapFrame();

protected:
	void DrawGrid(Display::IDisplayPtr pDisplay);
	void DrawTick(Display::IDisplayPtr pDisplay);
	void DrawSubTick(Display::IDisplayPtr pDisplay);
	void DrawLabel(Display::IDisplayPtr pDisplay);
	void DrawBorder(Display::IDisplayPtr pDisplay);


	void RegulateOrigin(BOOL bDynamicXYOrg, double& XOrigin, double& YOrigin, double& XInterval, double& YInterval, GEOMETRY::geom::Envelope& Env);

	void CalcGridLines(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, std::string strMapProj, std::string strLLProj, double XOrigin, 
		double YOrigin, double XInterval, double YInterval, GEOMETRY::geom::Geometry*& pLines);

	void CalcGridMarkers(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, std::string strMapProj, std::string strLLProj, double XOrigin, 
		double YOrigin, double XInterval, double YInterval, GEOMETRY::geom::Geometry*& pMarkers);

	void CalLabels(Display::IDisplayPtr pDisplay, std::vector<stGridLabel>& vecVerticalLabel, std::vector<stGridLabel>& vecHorizontalLabel, 
		std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>>& vecVerLabels, std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>>& vecHorLabels,
		double labelOffset, Display::CTextSymbol* pVerticalTextSym,
		Display::CTextSymbol* pHorizontalTextSym, GridLabelContent gridLabelContent, double tickSpacePage);

protected:
	GridLabelContent m_gridLabelContent;	


};

typedef SYSTEM::CSmartPtr<CGraticuleGrid> CGraticuleGridPtr;
}
#endif
