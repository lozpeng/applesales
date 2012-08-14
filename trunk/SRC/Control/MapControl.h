#ifndef _MAPCONTROL_H_
#define _MAPCONTROL_H_

#include "IMapCtrl.h"

using namespace Framework;

typedef enum TimeControlType
{
	FLASH_TYPE ,
	MOUSE_TYPE 
}TIME_CONTROL_TYPE;

namespace Control
{

	class CONTROL_DLL CMapControl : public CWnd, public Framework::IMapCtrl
	{

		DECLARE_DYNAMIC(CMapControl)

	public:
		CMapControl();
		virtual ~CMapControl();


	protected:
		DECLARE_MESSAGE_MAP()

	public:
		virtual BOOL CreateControl( std::string Name, void *pParent , long nID );

	public:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point); 
		afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		afx_msg void OnPaint();
		afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
		afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

		void OnTimer(UINT_PTR nIDEvent);

		afx_msg LRESULT OnFlash(WPARAM wParam, LPARAM lParam);


	private:
		//计算要贴的图在memDC上的位置
		void CalSrcRect(GEOMETRY::geom::Envelope extent,CRect &rect);
		//计算贴图在view中的位置
		void CalDestRect(GEOMETRY::geom::Envelope srcExtent,GEOMETRY::geom::Envelope destExtent,CRect &rect);

		void FlashLine(long);
		void FlashShape1(long);
	private:
		double m_dblScale;
		bool m_bTimer;
		GEOMETRY::geom::Envelope m_srcEnvelop; //记录内存DC的地理范围
		double   m_srcScale;
		bool m_bMouseWheel;

		//OnTimer响应的类型
		TIME_CONTROL_TYPE m_TimeType;
		//闪烁的图形
		GEOMETRY::geom::Geometry *m_pGeo;

	public:
		virtual BOOL PreTranslateMessage(MSG* pMsg);

		IStatusInfo* GetStatusInfo();

		std::string CMapControl::GetExtractInfo();
	};
}

#endif