//////////////////////////////////////////////////////////////////////
// 版权(c) 2010-2020, 天地智绘
// 作者：  hhzhao
// 时间：  2009/11/25
// 描述：  标绘工具——选择工具
//////////////////////////////////////////////////////////////////////

#ifndef _Select_Elements_Tool_h
#define _Select_Elements_Tool_h


#include "RectSelectTracker.h"
#include "IElement.h"
#include "ITool.h"
#include "IMapCtrl.h"
//#include "ILayerPropCallback.h"
//
//
//class CElementPropCallback : public ComUI::ILayerPropCallback
//{
//public:
//	CElementPropCallback(void){};
//	virtual ~CElementPropCallback(void){};
//
//public:
//	void SetMapCtrl(CMapCtrl *pMapControl) {m_pMapControl =pMapControl;}
//
//	virtual void UpdateMapCtrl();
//private:
//
//	CMapCtrl *m_pMapControl; 
//
//};

namespace Control
{
	class  CSelectElementsTool : public Framework::ITool
	{
	public:
		CSelectElementsTool();
		~CSelectElementsTool();

	public:
		virtual void Initialize(Framework::IUIObject *pTargetControl);

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

		Framework::IMapCtrl *m_pMapCtrl;
		Carto::CMapPtr m_pMap;
	};

}


#endif