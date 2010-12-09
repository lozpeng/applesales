//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/4/10
// 描述：  制图要素——制图页网格线  
//////////////////////////////////////////////////////////////////////

#ifndef CPAGE_GRID_H
#define CPAGE_GRID_H

#include "IGrid.h"
#include "ISelectionTracker.h"

namespace Element{

class CARTO_DLL CPageGrid : public SYSTEM::ISerialization
{
public:
	CPageGrid();
	~CPageGrid(void);

	virtual void serialization(SYSTEM::IArchive &ar); 

	void SetGridVisibility(BOOL bVisible);
	BOOL GetGridVisibility();

	void SetXOrigin(double XOrg);
	double GetXOrigin();

	void SetYOrigin(double XOrg);
	double GetYOrigin();

	void SetXInterval(double XInter);
	double GetXInterval();

	void SetYInterval(double XInter);
	double GetYInterval();

	void SetEnvelope(GEOMETRY::geom::Envelope GridEnvelope);

	void Draw(Display::IDisplayPtr pDisplay);

protected:
	void DrawGrid(Display::IDisplayPtr pDisplay);

	void CalcGridLines(GEOMETRY::geom::Envelope GridEnvelope, double XInterval, double YInterval, GEOMETRY::geom::Geometry*&	pLines);

protected:
	BOOL				m_bGridDirty;
	BOOL				m_bGridVisibility;
	//网格间隙
	double				m_XInterval;
	double				m_YInterval;

	//网格范围
	GEOMETRY::geom::Envelope		m_GridEnvelope;

	//网格线符号
	Display::ILineSymbolPtr		m_pGridLineSymbol;//line

	//网格线图形集multiline
	GEOMETRY::geom::Geometry*	m_pLines; 	
};

typedef SYSTEM::CSmartPtr<CPageGrid> CPageGridPtr;
}
#endif