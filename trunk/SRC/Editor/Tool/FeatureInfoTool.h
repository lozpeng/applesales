#ifndef _ACTION_FEATUREINFO_H_
#define _ACTION_FEATUREINFO_H_

#include "ITool.h"

//class CDlgFeatureInfo;

namespace Editor
{

class CActionFeatureInfo: public Framework::ITool
{
public:
	CActionFeatureInfo(void);
	virtual ~CActionFeatureInfo(void);

public:
	//≥ı ºªØ
	void Initialize(Framework::IUIObject *pTargetControl);

	void LButtonUpEvent (UINT nFlags, CPoint point);


private:

    CDlgFeatureInfo *m_dlg;
};

}

#endif