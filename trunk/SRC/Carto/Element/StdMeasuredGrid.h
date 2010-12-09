//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/3/15
// 描述：  制图要素——标准制图公里网  
//////////////////////////////////////////////////////////////////////


#ifndef CGROUND_COORD_STDMAPGRID_H
#define CGROUND_COORD_STDMAPGRID_H

#include "IMapGrid.h"

namespace Element{



class CARTO_DLL CStdMeasuredGrid :public IMapGrid
{
public:
	CStdMeasuredGrid ();
	CStdMeasuredGrid (CMapFrame* pMapFrame);
	~CStdMeasuredGrid (void);

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

	//计算投影带号
	std::string CaculateProjStrapNode();

public:
	bool GetProjStrapCodeVisible( void );
	void SetProjStrapCodeVisible( bool bVisible );

	bool GetHundredKmVisible( void );
	void SetHundredKmVisible( bool bVisible );

	bool GetKmVisible( void );
	void SetKmVisible( bool bVisible );

	Display::CTextSymbolPtr GetHundredLabelSymbol( void );
	void SetHundredLabelSymbol( Display::CTextSymbolPtr pTextSymbol );

	Display::CTextSymbolPtr GetProjLabelSymbol( void );
	void SetProjLabelSymbol( Display::CTextSymbolPtr pTextSymbol );

private:
	//标示是否绘制图幅所在投影带的编号
	bool m_bIsDrawProjStrapCode;

	//标示是否绘制百公里数
	bool m_bIsDrawHundredKm;
	
	//标示是否绘制个十公里数
	bool m_bIsDrawKm;
	
	//百公里数字的符号
	Display::CTextSymbolPtr m_pHundredLabelSymbol;

	//图幅所在投影带的编号
	Display::CTextSymbolPtr m_pProjStrapLabelSymbol;
	
	//百公里数字集合
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecVerHundredKmLabels;
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecHorHundredKmLabels;
	
	//百公里以下公里数字集合	
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecVerKmLabels;
	std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecHorKmLabels;
};

typedef SYSTEM::CSmartPtr<CStdMeasuredGrid > CStdMeasuredGridPtr;
}
#endif
