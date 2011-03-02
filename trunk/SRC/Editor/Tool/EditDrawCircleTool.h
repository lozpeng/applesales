#ifndef _ACTION_EDITDRAWCIRCLE_H_
#define _ACTION_EDITDRAWCIRCLE_H_

#include "ITool.h"
#include "IDisplay.h"
#include <geometry/geom/Geometry.h>

namespace Editor
{

	class CActionEditDrawCircle: public Framework::ITool
	{
	public:
		CActionEditDrawCircle(void);
		virtual ~CActionEditDrawCircle(void);

	public:
		//��ʼ��
		
		void Initialize(Framework::IUIObject *pTargetControl);

		void LButtonDownEvent (UINT nFlags, CPoint point);

		void MouseMoveEvent (UINT nFlags, CPoint point);

		void ActionDraw();

		void SplitCircle(GEOMETRY::geom::Geometry *pGeometry);

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