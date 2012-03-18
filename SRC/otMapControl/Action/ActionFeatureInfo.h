#ifndef _ACTION_FEATUREINFO_H_
#define _ACTION_FEATUREINFO_H_

#include "IAction.h"

class CDlgFeatureInfo;


class CActionFeatureInfo: public IAction
{
public:
	CActionFeatureInfo(void);
	virtual ~CActionFeatureInfo(void);

public:
	//≥ı ºªØ
	void Init(CotMapCtrl *pMapCtrl,Carto::CMap *pMap);

	void LButtonUpEvent (UINT nFlags, CPoint point);


private:

    CDlgFeatureInfo *m_dlg;
};



#endif