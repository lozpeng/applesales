#ifndef _ACTION_EDITDRAWCIRCLE_H_
#define _ACTION_EDITDRAWCIRCLE_H_

#include "IAction.h"
#include "IDisplay.h"
#include <geometry/geom/Geometry.h>

namespace otEditor
{

	class CActionEditDrawCircle: public otFramework::IAction
	{
	public:
		CActionEditDrawCircle(void);
		virtual ~CActionEditDrawCircle(void);

	public:
		//��ʼ��
		void Triger(void);

		void LButtonDownEvent (UINT nFlags, CPoint point);

		void MouseMoveEvent (UINT nFlags, CPoint point);

		void ActionDraw();

		void SplitCircle(TT_GEOMETRY::geom::Geometry *pGeometry);

	private:
		//��ͼ������Ӿ���
		void AddCircle(void);

	private:
		bool m_bStartDraw;//�����л���ƽ���


		//Բ�ĺ��յ�
		CPoint m_centralPt;
		CPoint m_endPt;

	};

}

#endif