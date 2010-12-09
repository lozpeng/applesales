//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/15
// 描述：  制图要素——标准制图经纬网  
//////////////////////////////////////////////////////////////////////

#ifndef CGROUND_COORD_STDGRATICULEGRID_H
#define CGROUND_COORD_STDGRATICULEGRID_H

#include "IMapGrid.h"
#include "GraticuleGrid.h"

namespace Element{
	

class CARTO_DLL CStdGraticuleGrid :public IMapGrid
{
public:
	CStdGraticuleGrid ();

	CStdGraticuleGrid (CMapFrame* pMapFrame);

	~CStdGraticuleGrid (void);

	virtual void serialization(SYSTEM::IArchive &ar); 

	void Draw(Display::IDisplayPtr pDisplay);

	IGridPtr Clone();

protected:
	void DrawGrid(Display::IDisplayPtr pDisplay);

	void DrawTick(Display::IDisplayPtr pDisplay);

	void DrawSubTick(Display::IDisplayPtr pDisplay);

	void DrawLabel(Display::IDisplayPtr pDisplay);

	void DrawBorder(Display::IDisplayPtr pDisplay);
	
	
	void CalcGridLines(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, std::string strMapProj, std::string strLLProj, double XOrigin, double YOrigin, 
		double dXDistanceToBorder, double dYDistanceToBorder, GEOMETRY::geom::Geometry*& pLines);
	
	void CalcGridMarkers(GEOMETRY::geom::Envelope& envGeo, GEOMETRY::geom::Envelope& envPage, std::string strMapProj, std::string strLLProj, double XOrigin, double YOrigin, 
		double dXDistanceToBorder, double dYDistanceToBorder, GEOMETRY::geom::Geometry*& pMarkers);
	
	void CalLabels(Display::IDisplayPtr pDisplay, 
		std::vector<stGridLabel>& vecVerticalLabel, 
		std::vector<stGridLabel>& vecHorizontalLabel, 
		Display::CTextSymbol* pVerticalTextSym,
		Display::CTextSymbol* pHorizontalTextSym, 
		double tickSpacePage,
		double labelOffset);

	void DrawNormal(Display::IDisplayPtr pDisplay);

	void RegulateOrigin(BOOL bDynamicXYOrg, double& XOrigin, double& YOrigin, double& XInterval, double& YInterval, GEOMETRY::geom::Envelope& Env);

	//计算投影带号
	std::string CaculateProjStrapNode();

	// 转化经纬度到度\分\秒
	void TransformToGraticuleText(double graticule, std::vector<std::string> &vecDMS );

public:
	void SetGridLabelContent(int enumGridLabelContent);

	int  GetGridLabelContent();

	void SetXDistancetoBorder( long xDistance );
	long GetXDistancetoBorder( void );

	void SetYDistancetoBorder( long yDistance );
	long GetYDistancetoBorder( void );

private:
	GridLabelContent m_gridLabelContent;	

	//网格距离边界的距离
	long m_lXDistanceToBorder;
	long m_lYDistanceToBorder;
		
	//垂直方向的经度
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecVerDegreeLabels;
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecVerMinuteLabels;
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecVerSecondLabels;
	
	//水平方向的纬度	
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecHorDegreeLabels;
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecHorMinuteLabels;
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecHorSecondLabels;
};

typedef SYSTEM::CSmartPtr<CStdGraticuleGrid > CStdGraticuleGridPtr;
}
#endif
