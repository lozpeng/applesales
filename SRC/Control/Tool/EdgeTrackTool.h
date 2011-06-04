#ifndef _EDGETRACKTool_H
#define _EDGETRACKTool_H

#include "ITool.h"
#include "IMapCtrl.h"
#include "EdgeTracking.h"
#include "IRasterDataset.h"
#include "IOtherdDraw.h"
#include "GeometrySketch.h"

namespace Control
{

class CONTROL_DLL CEdgeTrackTool: public Framework::ITool,public Carto::IOtherDraw
{
public:
	CEdgeTrackTool();
	~CEdgeTrackTool();

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);

	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonDblClkEvent (UINT nFlags, CPoint point);

	virtual void Draw(Display::IDisplayPtr pDisplay);


private:
	HCURSOR m_hCursor;

	Framework::IMapCtrl *m_pMapCtrl;

	CEdgeTracking          m_cEdge;

	Geodatabase::IRasterDatasetPtr m_pDataset;

	SYSTEM::CSmartPtr<GEOMETRY::geom::Geometry> m_pGeometry; 
	Display::ISymbolPtr m_pSymbol;

	long m_lPointNum;

	long   mp_lSeedPointCount;

	long    mg_lSeedBreakCount;

	POINT                  *m_pTempPathPoint;   //临时的路径

	long    mp_lPixelTempCount;

	//当前鼠标点坐标
	GEOMETRY::geom::Coordinate mg_mouseLocation;

	std::vector<GEOMETRY::geom::Coordinate> m_seedPoints;

	//画笔
	Display::CGeometrySketchPtr m_pSketch;
};

}


#endif