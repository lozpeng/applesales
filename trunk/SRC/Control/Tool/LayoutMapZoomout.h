#ifndef _LAYOUT_MAP_ZOOMOUT_H_
#define _LAYOUT_MAP_ZOOMOUT_H_

#include "ITool.h"
#include "ILayoutCtrl.h"

namespace Control
{

	class CLayoutMapZoomout : public Framework::ITool
	{
	public:
		CLayoutMapZoomout(void);
		virtual ~CLayoutMapZoomout(void);

	public:
		void Initialize(Framework::IUIObject *pTargetControl);
		void LButtonDownEvent (UINT nFlags, CPoint point);

	private:
		HCURSOR m_hCursor;
		Framework::ILayoutCtrl *m_pLayoutCtrl;
	};

}

#endif
