#ifndef _EDIT_ELEMENT_VERTIX_TOOL_h
#define _EDIT_ELEMENT_VERTIX_TOOL_h

#include "ITool.h"
#include "IElement.h"
#include "IMapCtrl.h"

namespace Control
{

	class  CEditElementVertixTool : public Framework::ITool
	{
	public:
		CEditElementVertixTool();
		~CEditElementVertixTool();

	public:
		void Initialize(Framework::IUIObject *pTargetControl);
		void LButtonDownEvent (UINT nFlags, CPoint point);
		void MouseMoveEvent (UINT nFlags, CPoint point);
		void LButtonUpEvent (UINT nFlags, CPoint point);

	protected:
		void UpdateStartPoint(CPoint pt);
		void UpdateEndPoint(CPoint pt);
		long GetHandleCursor(Element::HIT_HANDLE nHandle);

	private:
		MOVE_STATUS m_nMoveStatus;
		CAN_MOVE_CONTENT m_nCanMoveContent;
		CPoint m_cPtStart,m_cPtEnd;
		GEOMETRY::geom::Coordinate m_startCoord, m_endCoord;

		int m_nBufferDis;

		Element::HIT_TEST_RES m_hitTestRes;
		Element::IElementPtr m_pCurElement;

		Framework::IMapCtrl *m_pMapCtrl;

		HCURSOR cursorNormal;
		HCURSOR cursorSizeAll;
		HCURSOR cursorVertixMove;
		HCURSOR cursorOnVertix;

	};

}


#endif