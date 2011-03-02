#ifndef _ACTION_UNGROUP_SHAPE_H
#define _ACTION_UNGROUP_SHAPE_H

#include "IAction.h"
#include "TT_Shape.hxx"
#include <vector>
using std::vector;

namespace otEditor
{
	class CActionUnGroupShape : public otFramework::IAction
	{
	public:
		CActionUnGroupShape();
		~CActionUnGroupShape();

	public:
		//��ʼ��
		void Triger(void);

		//���ͼ��
		void UnGroupShape();

		//���
		void Clear();

	private:
		//ͼ��
		vector<Geometry*> m_shapes;	

		//ͼ��ID
		vector<long> m_shapeIds;

		//ͼ��
		vector<otCarto::ILayer*> m_players;
	};

#endif
}
