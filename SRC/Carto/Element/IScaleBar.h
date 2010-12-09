//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/4/14
// 描述：  制图要素——比例尺
//////////////////////////////////////////////////////////////////////


#ifndef ISCALE_BAR_H
#define ISCALE_BAR_H
#include "IMapSurround.h"
#include "TextSymbol.h"
#include "DisRectSet.h"

#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>
typedef boost::signals::connection  connection_t;


namespace Element{

class CARTO_DLL IScaleBar :public IMapSurround
{
public:
	IScaleBar();
	IScaleBar(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame);
	~IScaleBar(void);

	void MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord);

	virtual void serialization(SYSTEM::IArchive &ar); 

	static SYSTEM::CSmartPtr<IScaleBar> CreateScaleBarFromStream(SYSTEM::IArchive &ar);

	static SYSTEM::CSmartPtr<IScaleBar> CreateScaleBar(ELEMENT_TYPE type);

	void UnitChanged(SYSTEM::SYS_UNIT_TYPE newUnit);

	//bar
	void SetTextSymbol(Display::CTextSymbolPtr pTextSymbol);
	Display::CTextSymbolPtr GetTextSymbol();

	void SetForeSymbol(Display::ISymbolPtr pBarSymbol);
	Display::ISymbolPtr GetForeSymbol();

	void SetBackSymbol(Display::ISymbolPtr pBarSymbol);
	Display::ISymbolPtr GetBackSymbol();

	void SetDivisionLen(double len);
	double GetDivisionLen();

	void SetDivisionNum(int num);
	int GetDivisionNum();

	void SetSubDivisionNum(int num);
	int GetSubDivisionNum();

	void SetDrawDivisionBeforZero(BOOL isDraw);
	BOOL GetDrawDivisionBeforZero();

	//mark
	void SetDivMarkHeight(double markHeight);
	double GetDivMarkHeight();

	void SetSubDivMarkHeight(double markHeight);
	double GetSubDivMarkHeight();

	void SetMarkPos(MarkPosition pos);
	MarkPosition GetMarkPos();

	void SetMarkFreq(LabelFrequency freq);
	LabelFrequency GetMarkFreq();

	void SetMarkLineSymbol(Display::ILineSymbolPtr pLineSymbol);
	Display::ILineSymbolPtr GetMarkLineSymbol();

	//num label
	void SetNumGap(double gap);
	double GetNumGap();

	void SetNumFreq(LabelFrequency freq);
	LabelFrequency GetNumFreq();

	void SetNumPos(NumPosition pos);
	NumPosition GetNumPos();


	void SetNumTextSymbol(Display::CTextSymbolPtr pSymbol);
	Display::CTextSymbolPtr GetNumTextSymbol();

	//unit
	void SetUnit(SYSTEM::SYS_UNIT_TYPE unit);
	SYSTEM::SYS_UNIT_TYPE	GetUnit();

	void SetUnitGap(double gap);
	double GetUnitGap();

	void SetUnitPos(UnitPosition pos);
	UnitPosition GetUnitPos();

	void SetUnitTextSymbol(Display::CTextSymbolPtr pSymbol);
	Display::CTextSymbolPtr GetUnitTextSymbol();

	
protected:
	void DrawNormal(Display::IDisplayPtr pDisplay);

protected:
	virtual void DrawBar(Display::IDisplayPtr pDisplay, DIS_RECT rect)=0;

	virtual void DrawMark(Display::IDisplayPtr pDisplay, DIS_RECT rect);

	virtual void DrawUnitLabel(Display::IDisplayPtr pDisplay, DIS_RECT rect);

	virtual void DrawNumLabel(Display::IDisplayPtr pDisplay, DIS_RECT rect);

protected:
	void RecalcGeometry(Display::IDisplayPtr pDisplay);

	void CalculateScalebarRectSet(Display::IDisplayPtr pDisplay, CDisRectSet* pScaleBarRectSet);
	
	DIS_RECT CalcUnitSize(Display::IDisplayPtr pDisplay);

	DIS_RECT CalcBarSize(Display::IDisplayPtr pDisplay);

	DIS_RECT CalcMarkSize(Display::IDisplayPtr pDisplay, DIS_RECT barRect);

	DIS_RECT CalcNumSize(Display::IDisplayPtr pDisplay, DIS_RECT barRect);

	void NormalizeRect(Display::IDisplayPtr pDisplay, DIS_RECT& rect);

	void TransferNumToDisplay(double number, char* cNum);

	DIS_RECT CalculateTextSize(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol,  std::string str);

	void AddBarRect(Display::IDisplayPtr pDisplay, CDisRectSet* pScaleBarRectSet, DIS_RECT barRect);

	void AddMarkRect(Display::IDisplayPtr pDisplay, CDisRectSet* pScaleBarRectSet, DIS_RECT markRect);

	void AddNumRect(Display::IDisplayPtr pDisplay, CDisRectSet* pScaleBarRectSet, DIS_RECT numRect);

	void AddUnitRect(Display::IDisplayPtr pDisplay, CDisRectSet* pScaleBarRectSet, DIS_RECT unitRect);

	void DrawText(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol, std::string text, DIS_RECT rect, unsigned int dwDTFormat);

	void ConvertMillimeterToPixel(Display::IDisplayPtr pDisplay);


protected:

	connection_t m_ConnectionMapFrameProperChanged;

	void CallbackMapFrameProperChangedFun(CMapFrame* pMapFram);

protected:
	//GEOMETRY::geom::Envelope m_env;  //legend的名义地理范围，用于legend的拖框缩放，
	//每当legend由于内部内容、字体等变化造成真实范围变化时，更新

	BOOL						m_contentChanged;	//标志内容是否改变

	double						m_mapScale;			//地图比例尺
	
	//bar
	Display::CTextSymbolPtr	m_pTextSymbol;		//比例尺字体
	Display::ISymbolPtr		m_pForeSymbol;		//比例尺前景色
	Display::ISymbolPtr		m_pBackSymbol;		//比例尺背景色
	double						m_BarHeight;		//比例尺的高度(单位：mm)
	long						m_BarHeightPixel;	//比例尺的高度(单位：Pixel)
	double						m_DivisionLen;		//主分段的长度
	int							m_DivisionNum;		//主分段的数目
	int							m_SubDivisionNum;	//子分段的数目
	BOOL						m_DrawDivBeforZero;	//设置是否在0值前绘制一个分段

	//mark
	double						m_DivisionMarkHeight;//主分段刻度高度(单位：mm)
	long						m_DivisionMarkHeightPixel;//主分段刻度高度(单位：pixel)
	double						m_SubDivisionMarkHeight;//子分段刻度高度(单位：mm)
	long						m_SubDivisionMarkHeightPixel;//子分段刻度高度(单位：Pixel)
	MarkPosition				m_MarkPos;			//刻度的位置
	LabelFrequency				m_MarkFreq;			//刻度绘制的规则
	Display::ILineSymbolPtr	m_pMarkLineSymbol;		//刻度的线符号

	//num label
	Display::CTextSymbolPtr	m_NumTextSymbol;	//数字标注的字体
	double						m_NumLabelGap;		//数字标注与比例尺的距离(单位：mm)
	long						m_NumLabelGapPixel;	//数字标注与比例尺的距离(单位：Pixel)
	LabelFrequency				m_NumLabelFreq;		//数字标注绘制的规则
	NumPosition					m_NumLabelPos;		//数字标注相对于比例尺的位置

	//unit label
	Display::CTextSymbolPtr	m_UnitTextSymbol;	//单位标注的字体
	SYSTEM::SYS_UNIT_TYPE		m_Unit;				//单位
	double						m_UnitLabelGap;		//单位标注与比例尺的距离(单位：mm)
	long						m_UnitLabelGapPixel;//单位标注与比例尺的距离(单位：Pixel)
	UnitPosition				m_UnitLabelPos;		//单位标注相对比例尺的方位

	
};
typedef SYSTEM::CSmartPtr<IScaleBar> IScaleBarPtr;
}
#endif