#ifndef _ACTION_EDITDRAWELLIPSE_H_
#define _ACTION_EDITDRAWELLIPSE_H_

#include "IAction.h"
#include "IDisplay.h"
#include <geometry/geom/Geometry.h>

namespace otEditor
{

	class CActionEditDrawEllipse: public otFramework::IAction
	{
	public:
		CActionEditDrawEllipse(void);
		virtual ~CActionEditDrawEllipse(void);

	public:
		//��ʼ��
		void Triger(void);

		void LButtonDownEvent (UINT nFlags, CPoint point);

		void MouseMoveEvent (UINT nFlags, CPoint point);

		void ActionDraw();

	private:
		//��ͼ���������Բ��
		void AddEllipse(CPoint ulPt,CPoint lrPt);

		//�ָ���Բ��
		void SplitEllipse(TT_GEOMETRY::geom::Geometry *pGeometry);

	private:
		bool m_bStartDraw;//�����л���ƽ���

		CPoint m_ulPt; //��Ӿ��ε����Ͻǵ�
		CPoint m_lrPt; //��Ӿ������½ǵ�

	};

}

#endif