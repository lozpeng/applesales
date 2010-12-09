//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/4/10
// 描述：  制图要素——制图页
//////////////////////////////////////////////////////////////////////
#ifndef _CARTO_ELEMENT_PAGE_H
#define _CARTO_ELEMENT_PAGE_H
#include "IFrameProperty.h"
#include "IDisplay.h"
#include "PageGrid.h"

namespace Element{

class CARTO_DLL CPage : public IFrameProperty, public SYSTEM::ISerialization
{
public:
	CPage(void);
	CPage(int nPrintPageNumX, int nPagePrintNumY, double dbOnePrintPageWidth, double dbOnePrintPageHeight);
	~CPage(void);

	virtual void serialization(SYSTEM::IArchive& ar);

	SYSTEM::CSmartPtr<CPage> Clone();

	void SetPageEnvelope(GEOMETRY::geom::Envelope& PageEnvelope);	
	const GEOMETRY::geom::Envelope& GetPageEnvelope();
	
	const GEOMETRY::geom::Envelope& GetPageMarginEnvelope();

	void Draw( Display::IDisplayPtr pDisplay , bool bPrint = false);

	/**
	* 获得地图的单位
	* @return 地图的单位
	*/
	void SetUnit(SYSTEM::SYS_UNIT_TYPE unit);
	SYSTEM::SYS_UNIT_TYPE GetUnit(){return m_unit;};

	void SetDrawPageGrid(BOOL bDraw);
	BOOL GetDrawPageGrid();

	void SetPageGridIntervalX(double x);
	double GetPageGridIntervalX();

	void SetPageGridIntervalY(double y);
	double GetPageGridIntervalY();

	void SetDrawPageDiv(BOOL bDraw);
	BOOL GetDrawPageDiv();

	void SetPrintPageNumX(int nNum);
	int GetPrintPageNumX();

	void SetPrintPageNumY(int nNum);
	int GetPrintPageNumY();

	/*void SetOnePrintPageWidth(double dbWidth);
	double GetOnePrintPageWidth();*/

	/*void SetOnePrintPageHeight(double dbHeight);
	double GetOnePrintPageHeight();*/


	CPageGridPtr GetGrid();

	PAGE_INFO GetPageInfo(){return m_pageInfo;}

	void SetPageInfo(PAGE_INFO pageInfo);


protected:
	void PageSizeChangedEvents();
	void Init( );

protected:
	//纸张的单位
	SYSTEM::SYS_UNIT_TYPE m_unit;
	//Page的尺寸
	int				m_nPrintPageNumX;
	int				m_nPrintPageNumY;

	double			m_dbOnePrintPageWidth;//mm
	double			m_dbOnePrintPageHeight;//mm

	GEOMETRY::geom::Envelope m_PageEnvelope;

	//Page可打印的尺寸
	GEOMETRY::geom::Envelope m_PrintableEnvelope;
	//Page外扩空白的尺寸
	GEOMETRY::geom::Envelope m_MarginEnvelope;
	//纸张与视图区域的边界距离
	double m_dbMargin;
	//纸张方向：0为横(landscape()宽>=高)，1为竖（portrait:宽<高）
	BOOL m_bOrientation;
	//打印区域是否可见
	BOOL m_bPrintAreaVisible;

	//绘制图形
	GEOMETRY::geom::Geometry* m_pGeometry;

	//纸张网格
	CPageGridPtr	m_pPageGrid;

	//分页线
	BOOL			m_bDrawPageDiv;

	PAGE_INFO		m_pageInfo;	
};

typedef SYSTEM::CSmartPtr<CPage> CPagePtr;
}
#endif

