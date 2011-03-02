#ifndef _ACTION_EDITDRAWRECT_H_
#define _ACTION_EDITDRAWRECT_H_

#include "IAction.h"
#include "IDisplay.h"
#include <geometry/geom/Geometry.h>

namespace otEditor
{

class CActionEditDrawRect: public otFramework::IAction
{
public:
	CActionEditDrawRect(void);
	virtual ~CActionEditDrawRect(void);

public:
	//��ʼ��
	void Triger(void);

	void LButtonDownEvent (UINT nFlags, CPoint point);

	void MouseMoveEvent (UINT nFlags, CPoint point);

	void ActionDraw();

private:
	//��ͼ������Ӿ���
	void AddRect(CPoint ulPt,CPoint lrPt);

private:
	bool m_bStartDraw;//�����л���ƽ���

	CPoint m_ulPt; //���ε����Ͻǵ�
	CPoint m_lrPt; //�������½ǵ�

};

}

#endif