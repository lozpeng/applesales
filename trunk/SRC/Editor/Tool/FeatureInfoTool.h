#ifndef _ACTION_FEATUREINFO_H_
#define _ACTION_FEATUREINFO_H_

#include "ITool.h"

class CDlgFeatureInfo;

namespace Editor
{

class CActionFeatureInfo: public Framework::ITool
{
public:
	CActionFeatureInfo(void);
	virtual ~CActionFeatureInfo(void);

public:
	//��ʼ��
	void Triger(void);

	void LButtonUpEvent (UINT nFlags, CPoint point);


private:

    CDlgFeatureInfo *m_dlg;
};

}

#endif