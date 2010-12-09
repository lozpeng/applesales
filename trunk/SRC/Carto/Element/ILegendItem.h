//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/4/10
// 描述：  制图要素——图例项
//////////////////////////////////////////////////////////////////////


#ifndef ILEGEND_ITEM_H
#define ILEGEND_ITEM_H

#include "TextSymbol.h"
#include "ElementDefine.h"
#include "ISelectionTracker.h"
#include "ISerialization.h"

namespace Element{

	enum Legend_Item_Type
	{
		LIT_HORIZONTAL,
		LIT_VERTICAL
	};
	
class CARTO_DLL ILegendItem : public SYSTEM::ISerialization
{
public:
	ILegendItem();
	ILegendItem(Carto::ILayerPtr	pLayer);
	~ILegendItem(void);

	virtual void serialization(SYSTEM::IArchive &ar); 

	static SYSTEM::CSmartPtr<ILegendItem> CreateLegendItemFromStream(SYSTEM::IArchive &ar);

	static SYSTEM::CSmartPtr<ILegendItem> CreateLegendItem(Legend_Item_Type type);


	virtual void Draw(Display::IDisplayPtr pDisplay, DIS_RECT& rect);

	virtual SYSTEM::CSmartPtr<ILegendItem> Clone()=0;

	void SetLayer(Carto::ILayerPtr pLayer);

	Carto::ILayerPtr GetLayer(){return m_pLayer;};

	void SetLayerID(long lID);

	long GetLayerID();

	 void SetLayerNameSymbol(Display::CTextSymbolPtr pTextSymbol);
	 Display::CTextSymbolPtr GetLayerNameSymbol();

	 void SetHeadingSymbol(Display::CTextSymbolPtr pTextSymbol);
	 Display::CTextSymbolPtr GetHeadingSymbol();

	 void SetLabelSymbol(Display::CTextSymbolPtr pTextSymbol);
	 Display::CTextSymbolPtr GetLabelSymbol();

	 void SetDescSymbol(Display::CTextSymbolPtr pTextSymbol);
	 Display::CTextSymbolPtr GetDescSymbol();


	 BOOL GetStartCol(){return m_bStartCol;};
	 void SetStartCol(BOOL bStartCol){m_bStartCol = bStartCol;};

	 int GetColCount(){return  m_nColumns;};
	 void SetColCount(int nColCount){m_nColumns = nColCount;};

	void SetReadDirection(BOOL bRightToLeft);
	BOOL GetReadDirection();

	void SetPatchWidth(float fWidth);
	float GetPatchWidth();

	void SetPatchHeight(float fHeight);
	float GetPatchHeight();

	void SetPatchMarkerSymbolStyle(MarkerSymbolLegendStyle markerStyle);
	MarkerSymbolLegendStyle GetPatchMarkerSymbolStyle();

	void SetPatchLineSymbolStyle(LineSymbolLegendStyle lineStyle);
	LineSymbolLegendStyle GetPatchLineSymbolStyle();

	void SetPatchAreaSymbolStyle(FillSymbolLegendStyle areaStyle);
	FillSymbolLegendStyle GetPatchAreaSymbolStyle();

	void SetLayerNameAndGroup(float fSpace);
	float GetLayerNameAndGroup();

	void SetHeadingAndClasses(float fSpace);
	float GetHeadingAndClasses();

	void SetClassesSpace(float fSpace);
	float GetClassesSpace();

	void SetPatchAndOther(float fSpace);
	float GetPatchAndOther();

	void SetLabelAndOther(float fSpace);
	float GetLabelAndOther();

protected:
	virtual void ConvertPointToDisplay(Display::IDisplayPtr pDisplay);	

	virtual DIS_RECT GetPatchSize();

	virtual DIS_RECT GetTextSize(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol, std::string text);


	virtual void DrawText(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol, DIS_RECT& rect, std::string text, unsigned int dwDTFormat);

protected:

	Legend_Item_Type m_type;

	Carto::ILayerPtr	m_pLayer;	//与item相关的layer

	BOOL			m_bRightToLeft;	//
	BOOL			m_bStartCol;	//是否为Legend中一列的起始图例项

	BOOL			m_bCanDisplay;	//是否可视
	int				m_nColumns;		//item的列数
	int				m_nHeight;		//item的高度（mm）
	int				m_nWidth;		//item的宽度（mm）
	long			m_lHeightPixel;	//pixel
	long			m_lWidthPixel;	//pixel

	int				m_LayerNameAndGroup;	//layer name和其他的距离（mm）
	int				m_HeadingAndClasses;	//Head和各类别图例的距离（mm）
	int				m_ClassesSpaces;			//各类别之间的距离（mm）
	int				m_PatchAndOther;		//符号与其他（标注/描述/layer name）距离（mm）
	int				m_LabelAndOther;		//标注和其他的距离（mm）
	long			m_LayerNameAndGroupPixel;//pixel	
	long			m_HeadingAndClassesPixel;//pixel
	long			m_ClassesSpacesPixel;			//pixel
	long			m_PatchAndOtherPixel;	//pixel
	long			m_LabelAndOtherPixel;	//pixel	


	LegendItemStyle	m_itemStyle;	//item的显示风格

	BOOL			m_bShowHeading;
	BOOL			m_bShowLayerName;
	BOOL			m_bShowLabels;
	BOOL			m_bShowDescriptions;
	
	Display::CTextSymbolPtr	m_pLayerNameSymbol;
	Display::CTextSymbolPtr	m_pHeadingSymbol;	
	Display::CTextSymbolPtr	m_pLabelSymbol;
	Display::CTextSymbolPtr	m_pDescriptionSymbol;

	int				m_patchWidth;
	int				m_patchHeight;
	long			m_patchWidthPixel;
	long			m_patchHeightPixel;
	LineSymbolLegendStyle	m_patchLineStyle;
	FillSymbolLegendStyle	m_patchAreaStyle;
	MarkerSymbolLegendStyle	m_patchMarkerStyle;

	//Display::IMarkerSymbolPtr	m_patchMarkerSymbol;


protected:
	long	m_LayerID;//只在序列化加载时临时保存图层序号时使用


};

typedef SYSTEM::CSmartPtr<ILegendItem> ILegendItemPtr;
}
#endif
