#ifndef _LAYOUT_MAP_ZOOMIN_H_
#define _LAYOUT_MAP_ZOOMIN_H_

#include "ITool.h"
#include "ILayoutCtrl.h"

namespace Control
{

class CLayoutMapZoomin : public Framework::ITool
{
public:
	CLayoutMapZoomin(void);
	virtual ~CLayoutMapZoomin(void);

public:
	void Initialize(Framework::IUIObject *pTargetControl);
	void LButtonDownEvent (UINT nFlags, CPoint point);

private:
	HCURSOR m_hCursor;
	Framework::ILayoutCtrl *m_pLayoutCtrl;
};

}

#endif
