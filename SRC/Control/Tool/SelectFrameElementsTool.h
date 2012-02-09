
//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  leo
// 时间：  2010.12.20
// 描述：  制图要素选择工具
//////////////////////////////////////////////////////////////////////

#ifndef _Select_Elements_TOOL_h
#define _Select_Elements_TOOL_h

#include "RectSelectTracker.h"
#include "IElement.h"

#include "ITool.h"
#include "ILayoutCtrl.h"

class  CSelectFrameElementsTool : public Framework::ITool
{
public:
	CSelectFrameElementsTool();
	~CSelectFrameElementsTool();

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
	void LButtonDblClkEvent (UINT nFlags, CPoint point);
	void RButtonDownEvent (UINT nFlags, CPoint point);
	void KeyDownEvent (UINT nChar, UINT nRepCnt, UINT nFlags);

	void OnEditElementProp();


protected:
	void UpdateStartPoint(CPoint pt);
	void UpdateEndPoint(CPoint pt);
	HCURSOR GetHandleCursor(Element::HIT_HANDLE nHandle);


private:
	MOVE_STATUS m_nMoveStatus;
	CAN_MOVE_CONTENT m_nCanMoveContent;
	CPoint m_cPtStart,m_cPtEnd;
	GEOMETRY::geom::Coordinate m_startCoord, m_endCoord;
	Element::CRectSelectTracker m_selectBox;

	int m_nBufferDis;
	double m_dbBufferDis;

	Element::HIT_HANDLE m_nCurHandle;
	Element::IElementPtr m_pCurElement;
private:
	Framework::ILayoutCtrl *m_pLayoutCtrl;

	HCURSOR cursorNormal;
	HCURSOR cursorSizeAll;
	HCURSOR cursorRightTop;
	HCURSOR cursorTopBottom;
	HCURSOR cursorleftTop;
	HCURSOR cursorLeftRight;
};




#endif