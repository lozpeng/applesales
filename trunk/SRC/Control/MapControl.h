#ifndef _MAPCONTROL_H_
#define _MAPCONTROL_H_

#include "IMapCtrl.h"



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
	virtual void SetCursor();

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



private:
	//计算要贴的图在memDC上的位置
	void CalSrcRect(GEOMETRY::geom::Envelope extent,CRect &rect);
	//计算贴图在view中的位置
	void CalDestRect(GEOMETRY::geom::Envelope srcExtent,GEOMETRY::geom::Envelope destExtent,CRect &rect);

private:
	double m_dblScale;
	bool m_bTimer;
	GEOMETRY::geom::Envelope m_srcEnvelop; //记录内存DC的地理范围
	double   m_srcScale;
	bool m_bMouseWheel;



};
}

#endif