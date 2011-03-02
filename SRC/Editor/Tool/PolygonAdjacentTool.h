#ifndef _ACTION_POLYGON_ADJACENT_H
#define _ACTION_POLYGON_ADJACENT_H

#include "IAction.h"
#include <vector>
using std::vector;

namespace otEditor
{
	//�����ڽӶ���εĹ���
	class CActionPolygonAdjacent : public otFramework::IAction
	{
	public:
		CActionPolygonAdjacent();
		~CActionPolygonAdjacent();

		//
	public:
		//��ʼ��
		void Triger(void);

		//����¼�����
		void LButtonDownEvent (UINT nFlags, CPoint point);
		void LButtonDblClkEvent (UINT nFlags, CPoint point);
		void MouseMoveEvent (UINT nFlags, CPoint point);

	public:
		//���
		void Clear();
		
		//������ʱͼ�� 
		void ActionDraw();

		//�����ڽӶ����
		void AdjacentPolygon();

	private:
		//ͼ��
		vector<Geometry*> m_shapes;	

		//ͼ��ID
		vector<long> m_shapeIds;

		//ͼ��
		vector<otCarto::ILayer*> m_players;

	private:
		//�������������
		vector<CPoint> m_Points;

		bool m_bIsDrawing;
	};

	#endif
}