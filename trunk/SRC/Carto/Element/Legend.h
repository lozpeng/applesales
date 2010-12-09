//////////////////////////////////////////////////////////////////////
// ��Ȩ(c) 2010-2020, ����ǻ�
// ���ߣ�  hhzhao
// ʱ�䣺  2009/4/14
// ������  ��ͼҪ�ء���ͼ��
//////////////////////////////////////////////////////////////////////


#ifndef ILEGEND_H
#define ILEGEND_H
#include "IMapSurround.h"
#include "LegendFormat.h"
#include "ILegendItem.h"
#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>

typedef boost::signals::connection  connection_t;

namespace Carto{
	class CMap;
}

namespace Element{

class CARTO_DLL CLegend :public IMapSurround
{
public:
	CLegend();
	CLegend(const GEOMETRY::geom::Geometry& geometry,CMapFrame* pMapFrame);
	~CLegend(void);

	virtual void serialization(SYSTEM::IArchive &ar);   

	void DelayEvent(BOOL bDelay);
	void FitToEnvelope(Display::IDisplayPtr pDisplay, GEOMETRY::geom::Envelope *pEnvelope, BOOL bSizeChanged);
	void GetEnvelope(Display::IDisplayPtr pDisplay, GEOMETRY::geom::Envelope *pEnvelope);
	void Refresh();

	//////////////////////////////////////////////////////////////////////////
	void AddItem(ILegendItemPtr pLegendItem);
	void ClearItem();
	void InsertItem(long lIndex, ILegendItemPtr pLegendItem);
	void RemoveIntem(long lIndex);
	ILegendItemPtr GetItem(long lIndex);
	int GetItemCount();

	//////////////////////////////////////////////////////////////////////////
	void SetReadDirection(BOOL bRightToLeft);
	BOOL GetReadDirection();

	void SetDrawTitle(BOOL bDrawTitle);
	BOOL GetDrawTitle();

	void SetTitleSymbol(Display::CTextSymbolPtr titleSymbol);
	Display::CTextSymbolPtr GetTitleSymbol();

	void SetTitlePos(TITLE_DRAW_STYLE titlePos);
	TITLE_DRAW_STYLE GetTitlePos();

	void SetColumnSpace(float fSpace);
	float GetColumnSpace();

	void SetTitleItemSpace(float fSpace);
	float GetTitleItemSpace();

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

	void SetAllTextSymbol(Display::CTextSymbolPtr pTextSymbol);
	Display::CTextSymbolPtr GetAllTextSymbol();

	void SetLayerNameSymbol(Display::CTextSymbolPtr pTextSymbol);
	Display::CTextSymbolPtr GetLayerNameSymbol();

	void SetHeadingSymbol(Display::CTextSymbolPtr pTextSymbol);
	Display::CTextSymbolPtr GetHeadingSymbol();

	void SetLabelSymbol(Display::CTextSymbolPtr pTextSymbol);
	Display::CTextSymbolPtr GetLabelSymbol();

	void SetDescSymbol(Display::CTextSymbolPtr pTextSymbol);
	Display::CTextSymbolPtr GetDescSymbol();

	//ֻ�����л�����ʱ����itemʱʹ��
	void MapSettedEvent();

	void MapFrameSettedEvent();

	//////////////////////////////////////////////////////////////////////////
	connection_t m_ConnectionMapFrameMapSetted;

	connection_t m_ConnectionMapFrameProperChanged;

	connection_t m_ConnectionMapLayerDeleted;



protected:
	virtual void DrawNormal(Display::IDisplayPtr pDisplay);

	virtual void DrawLegendTitle(Display::IDisplayPtr pDisplay, DIS_RECT& rect);

	void RecalcGeometry(Display::IDisplayPtr pDisplay);

	DIS_RECT GetTitleSize(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol);

	void CallbackMapFrameMapSettedFun(CMapFrame* pMapFram);

	void CallbackMapFrameProperChangedFun(CMapFrame* pMapFram);

	void CallbackMapLayerDeleted(Carto::ILayerPtr pLayer);

protected:

	//read direction
	BOOL m_bRightToLeft;

	//default set
	BOOL m_bAutoAdd;
	BOOL m_bAutoReorder;
	BOOL m_bAutoVisilility;

	//items and arrangement
	CLegendFormat m_legendFormat;
	std::vector<ILegendItemPtr> m_vecLegendItems;

	//title
	BOOL m_bDrawTitle;
	std::string m_strLegendTitle;
	Display::CTextSymbolPtr m_pTitleSymbol;
	TITLE_DRAW_STYLE m_titlePos;

	//legend space
	double m_TitleToItems;//mm
	double m_ColumnSpace;//mm

	//changed event
	BOOL m_contentChanged;

	//////////////////////////////////////////////////////////////////////////

	//item specify
	float m_patchWidth;
	float m_patchHeight;
	LineSymbolLegendStyle	m_patchLineStyle;
	FillSymbolLegendStyle	m_patchAreaStyle;
	MarkerSymbolLegendStyle	m_patchMarkerStyle;

	float m_LayerNameAndGroup;	//layer name�������ľ��루mm��
	float m_HeadingAndClasses;	//Head�͸����ͼ���ľ��루mm��
	float m_ClassesSpaces;			//�����֮��ľ��루mm��
	float m_PatchAndOther;		//��������������ע/����/layer name�����루mm��
	float m_LabelAndOther;		//��ע�������ľ��루mm��

	Display::CTextSymbolPtr	m_pAllTextSymbol;
	Display::CTextSymbolPtr	m_pLayerNameSymbol;
	Display::CTextSymbolPtr	m_pHeadingSymbol;	
	Display::CTextSymbolPtr	m_pLabelSymbol;
	Display::CTextSymbolPtr	m_pDescriptionSymbol;

//	GEOMETRY::geom::Envelope m_env;  //legend���������Χ������legend���Ͽ����ţ�
	                                    //ÿ��legend�����ڲ����ݡ�����ȱ仯�����ʵ��Χ�仯ʱ������
};

typedef SYSTEM::CSmartPtr<CLegend> CLegendPtr;
}
#endif
