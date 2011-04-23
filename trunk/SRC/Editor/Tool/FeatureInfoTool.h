#ifndef _ACTION_FEATUREINFO_H_
#define _ACTION_FEATUREINFO_H_

#include "ITool.h"

class CDlgFeatureInfo;

namespace Editor
{

class CFeatureInfoTool: public Framework::ITool
{
public:
	CFeatureInfoTool(void);
	virtual ~CFeatureInfoTool(void);

public:
	//≥ı ºªØ
	void Initialize(Framework::IUIObject *pTargetControl);

	void LButtonDownEvent (UINT nFlags, CPoint point);


private:

	HCURSOR cursorNormal;
    CDlgFeatureInfo *m_dlg;
	static int  m_SnapTol;
};

}

#endif