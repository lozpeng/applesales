
#ifndef _LAYOUTCONTROL_H_
#define _LAYOUTCONTROL_H_

#include  "ILayoutCtrl.h"
#include "Map.h"

namespace Control
{

	class CONTROL_DLL CLayoutControl :public CWnd, public Framework::ILayoutCtrl
	{

		DECLARE_DYNAMIC(CLayoutControl)

	public:
		CLayoutControl(void);
		~CLayoutControl(void);

	protected:
		DECLARE_MESSAGE_MAP()
		//

	public:
		virtual BOOL CreateControl( std::string Name, void *pParent , long nID );

	public:

		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnPaint();
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
		afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
		afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
		afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

		void LoadTemplate(Carto::CMapPtr map, BSTR templatefile);

	};

}
#endif