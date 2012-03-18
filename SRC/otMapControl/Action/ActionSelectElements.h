#ifndef _Action_Select_Elements_h
#define _Action_Select_Elements_h

#include "IAction.h"
#include "RectSelectTracker.h"
#include "IElement.h"

#include "ILayerPropCallback.h"


class CElementPropCallback : public otComUI::ILayerPropCallback
{
public:
	CElementPropCallback(void){};
	virtual ~CElementPropCallback(void){};

public:
	void SetMapCtrl(CotMapCtrl *pMapControl) {m_pMapControl =pMapControl;}

	virtual void UpdateMapCtrl();
private:

	CotMapCtrl *m_pMapControl; 

};

enum MOVE_STATUS
{
	NO_MOVING,
	SELECTTRAKER_DRAWING,
	ELEMENT_MOVING, 
	HANDLE_MOVING,
	VERTIX_MOVING
};

enum CAN_MOVE_CONTENT
{
	CMC_CANMOVE_NONE,
	CMC_CANMOVE_ELEMENT, 
	CMC_CANMOVE_HANDLE,
	CMC_CANMOVE_VERTIX
};

class  CActionSelectElements : public IAction
{
public:
	CActionSelectElements();
	~CActionSelectElements();

public:
	virtual void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);

	void LButtonDownEvent (UINT nFlags, CPoint point);
	void MouseMoveEvent (UINT nFlags, CPoint point);
	void LButtonUpEvent (UINT nFlags, CPoint point);
	void KeyDownEvent (UINT nChar, UINT nRepCnt, UINT nFlags);
	void LButtonDblClkEvent (UINT nFlags, CPoint point);


protected:
	void UpdateStartPoint(CPoint pt);
	void UpdateEndPoint(CPoint pt);
	long GetHandleCursor(Element::HIT_HANDLE nHandle);

	void OnEditElementProp();

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

};




#endif