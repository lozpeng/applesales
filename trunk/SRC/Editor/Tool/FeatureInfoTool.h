#ifndef _ACTION_FEATUREINFO_H_
#define _ACTION_FEATUREINFO_H_

#include "IAction.h"

class CDlgFeatureInfo;

namespace otEditor
{

class CActionFeatureInfo: public otFramework::IAction
{
public:
	CActionFeatureInfo(void);
	virtual ~CActionFeatureInfo(void);

public:
	//≥ı ºªØ
	void Triger(void);

	void LButtonUpEvent (UINT nFlags, CPoint point);


private:

    CDlgFeatureInfo *m_dlg;
};

}

#endif