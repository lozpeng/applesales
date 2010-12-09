//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/4/10
// 描述：  制图要素——网格  其它格网的基类
//////////////////////////////////////////////////////////////////////

#ifndef IGRID_H
#define IGRID_H
#include "SimpleBorder.h"
#include "ILineSymbol.h"
#include "TextSymbol.h"
#include "ISelectionTracker.h"

namespace Element{

	class CMapFrame;

	enum MapGridLineStyle
	{
		MGLS_LINE,
		MGLS_MARKER,
		MGLS_NONE
	};

	enum GridType
	{
		GT_GRATICULE_GRID,
		GT_MEASURED_GRID,
		GT_STANDARD_MAPPING_GRID,
		GT_STANDARD_GRATICULE_GRID
	};

	struct stGridLabel
	{
		BOOL bStartValid;

		BOOL bEndValid;

		GEOMETRY::geom::Coordinate geoCoordStart;

		GEOMETRY::geom::Coordinate geoCoordEnd;

		GEOMETRY::geom::Coordinate pageCoordStart;

		GEOMETRY::geom::Coordinate pageCoordEnd;

		stGridLabel(){bStartValid = TRUE;bEndValid = TRUE;};
	};

	static DIS_RECT CalculateTextSize(Display::IDisplayPtr pDisplay, Display::CTextSymbol* pTextSymbol, std::string text)
	{
		DIS_RECT textSize;
		textSize.left = 0; textSize.right = 1;
		textSize.top = 0; textSize.bottom = 1;

		pDisplay->SetSymbol(pTextSymbol);

		pDisplay->Begin();

		textSize = pDisplay->Draw(&textSize, text, TRUE, DT_CALCRECT | DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);

		pDisplay->End();

		return textSize;
	}

	class CARTO_DLL IGrid : public SYSTEM::ISerialization
	{
	public:
		IGrid();
		~IGrid(void);

		virtual void serialization(SYSTEM::IArchive &ar);  

		virtual SYSTEM::CSmartPtr<IGrid> Clone()=0;

		static SYSTEM::CSmartPtr<IGrid> CreateGridFromStream(SYSTEM::IArchive &ar);

		static SYSTEM::CSmartPtr<IGrid> CreateGrid( GridType type);


		void SetRecalcGrid();

		void SetGridActive(BOOL bActive);
		BOOL GetGridActive();

		void SetGridName(std::string name);
		std::string GetGridName();

		void SetGridVisibility(BOOL bVisible);
		BOOL GetGridVisibility();

		void SetGridLineSymbol(Display::ILineSymbolPtr pLineSymbol);
		Display::ILineSymbolPtr GetGridLineSymbol();

		void SetGridMarkerSymbol(Display::IMarkerSymbolPtr pGridMarkerSymbol);
		Display::IMarkerSymbolPtr GetGridMarkerSymbol();

		void SetUseDynamicXYOrigin(BOOL bDyn);
		BOOL GetUseDynamicXYOrigin();

		void SetXOrigin(double XOrg);
		double GetXOrigin();

		void SetYOrigin(double XOrg);
		double GetYOrigin();

		void SetXInterval(double XInter);
		double GetXInterval();

		void SetYInterval(double XInter);
		double GetYInterval();

		void SetBorderVisibility(BOOL bVisible);
		BOOL GetBorderVisibility();

		void SetBorderLineSymbol(Display::ILineSymbolPtr pLineSymbol);
		Display::ILineSymbolPtr GetBorderLineSymbol();

		void SetBorderExpandX(float x);
		float GetBorderExpandX();

		void SetBorderExpandY(float y);
		float GetBorderExpandY();

		void SetLabelVisibility(BOOL bVisible);
		BOOL GetLabelVisibility();

		void SetTickVisibility(BOOL bVisible);
		BOOL GetTickVisibility();

		void SetTickCount(int nCount);
		int GetTickCount();

		void SetTickLength(double dbLen);
		double GetTickLength();

		void SetTickOffset(double dbOffset);
		double GetTickOffset();

		void SetTickLineSymbol(Display::ILineSymbolPtr pLineSym);
		Display::ILineSymbolPtr GetTickLineSymbol();

		void SetSubTickVisibility(BOOL bVisible);
		BOOL GetSubTickVisibility();

		void SetSubTickCount(int nCount);
		int GetSubTickCount();

		void SetSubTickLength(double dbLen);
		double GetSubTickLength();

		void SetSubTickLineSymbol(Display::ILineSymbolPtr pLineSym);
		Display::ILineSymbolPtr GetSubTickLineSymbol();

		void SetTextSymbol(Display::CTextSymbolPtr pTextSym);
		Display::CTextSymbolPtr GetTextSymbol();

		void SetLabelOffset(float fLabelOffset);
		float GetLabelOffset();

		void SetLabelTop(BOOL bLabel);
		BOOL GetLabelTop();

		void SetLabelBottom(BOOL bLabel);
		BOOL GetLabelBottom();

		void SetLabelLeft(BOOL bLabel);
		BOOL GetLabelLeft();

		void SetLabelRight(BOOL bLabel);
		BOOL GetLabelRight();

		void SetVertTopBottom(BOOL bVert);
		BOOL GetVertTopBottom();

		void SetVertLeftRight(BOOL bVert);
		BOOL GetVertLeftRight();

		void SetMapGridLineStyle(int nStyle);
		int GetMapGridLineStyle();

		GridType GetGridType();

	public:
		virtual void Draw(Display::IDisplayPtr pDisplay);


	protected:
		void CalTickLines(Display::IDisplayPtr pDisplay, std::vector<stGridLabel>& vecVerticalLabel, std::vector<stGridLabel>& vecHorizontalLabel,
			GEOMETRY::geom::Geometry*& pTickLines, double tickOffset, double tickLength);

		void CalSubTickLines();


	protected:
		//整个网格是否可见
		BOOL				m_bActive;
		
		/*
		//Grid
		*/
		//网格类型
		GridType			m_GridType;
		//网格名称
		std::string			m_strGridName;
		//网格线/星是否可见
		BOOL				m_bGridVisibility;
		//网格属性是否变动
		BOOL				m_bGridDirty;
		//网格绘制类型：线/星
		MapGridLineStyle			m_gridLineStyle;
		//网格线符号
		Display::ILineSymbolPtr		m_pGridLineSymbol;//line
		//网格线图形集multiline
		GEOMETRY::geom::Geometry*	m_pLines; 	
		//网格星符号
		Display::IMarkerSymbolPtr		m_pGridMarkerSymbol; //Marker
		//网格星图形集multipoint
		GEOMETRY::geom::Geometry*	m_pMarkers;

		/*
		//Axis
		*/
		//是否使用地图原点作为坐标起始点
		BOOL				m_bDynamicXYOrg;
		//用户设置的起始点坐标(单位根据网格类型而定，经纬度网格坐标为经纬度，地图网格坐标与地图坐标单位相同)
		double				m_XOrigin;
		double				m_YOrigin;
		//实际起始点的坐标
		double				m_ActualXOrigin;
		double				m_ActualYOrigin;
		//网格间隙
		double				m_XInterval;
		double				m_YInterval;

		/*
		//Border
		*/	
		//边框是否可见
		BOOL				m_bBorderVisibility;
		//边框属性是否更改
		BOOL				m_bBorderDirty;
		//边框外扩
		double				m_borderExpandX;//mm
		double				m_borderExpandY;//mm
		double				m_borderExpandXPage;//Page unit
		double				m_borderExpandYPage;//Page unit
		//边框绘制符号
		Display::ILineSymbolPtr		m_pBorderLineSymbol;
		//边框范围（单位：纸张单位）
		GEOMETRY::geom::Envelope		m_envBorder;
		//边框图形
		GEOMETRY::geom::Geometry*	m_pBorderLine;

		/*
		//Label
		*/	
		//标注是否可见
		BOOL				m_bLabelVisibility;
		//标注是否变动
		BOOL				m_bLabelDirty;
		//标注的偏移距离
		double				m_labelOffset;//mm
		//是否绘制上端标注
		BOOL				m_bLabelTop;
		//是否绘制下端标注
		BOOL				m_bLabelBottom;
		//是否绘制左侧标注	
		BOOL				m_bLabelLeft;
		//是否绘制右侧标注
		BOOL				m_bLabelRight;
		//上下端标注文字是否垂直绘制
		BOOL				m_bVertTopBottom;
		//左右侧标注文字是否垂直绘制
		BOOL				m_bVertLeftRight;
		//文字绘制符号
		Display::CTextSymbolPtr		m_pTextSym;
		//上下端文字位置及绘制内容集合
		std::vector<stGridLabel>		m_vecVerticalLabel;
		//左右侧文字位置及绘制内容集合
		std::vector<stGridLabel>		m_vecHorizontalLabel;
		//上下端文字集合
		std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecVerLabels;
		//左右侧文字集合	
		std::vector<std::pair<GEOMETRY::geom::Envelope, std::string>> m_vecHorLabels;

		/*
		//Tick
		*/	
		//刻度是否可见
		BOOL				m_bTickVisibility;
		//刻度设置是否改变
		BOOL				m_bTickDirty;
		//刻度数目
		int					m_tickCount;
		//刻度长度
		double				m_tickLength;//mm
		//刻度长度
		double				m_tickLengthPage;//page unit
		//刻度偏移
		double				m_tickOffset;//mm
		//刻度偏移
		double				m_tickOffsetPage;//page unit
		//刻度绘制符号
		Display::ILineSymbolPtr		m_pTickLineSymbol;
		//刻度现集合multiline
		GEOMETRY::geom::Geometry* m_pTickLines;

		/*
		//sub Tick
		*/
		//分刻度是否可见
		BOOL				m_bSubTickVisibility;
		//刻度设置是否改变
		BOOL				m_bSubTickDirty;
		//分刻度数目
		int					m_subTickCount;
		//分刻度长度
		double				m_subTickLength;//mm
		//分刻度长度
		double				m_subTickLengthPage;//page unit
		//分刻度线符号
		Display::ILineSymbolPtr		m_pSubTickLineSymbol;
		//刻度现集合multiline
		GEOMETRY::geom::Geometry* m_pSubTickLines;
	};

	typedef SYSTEM::CSmartPtr<IGrid> IGridPtr;
}
#endif
