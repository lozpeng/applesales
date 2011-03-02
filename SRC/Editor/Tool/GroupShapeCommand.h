#ifndef _ACTION_GROUP_SHAPE_H
#define _ACTION_GROUP_SHAPE_H

#include "IAction.h"
#include <vector>
using std::vector;


namespace otEditor
{
	class CActionGroupShape : public otFramework::IAction
	{
	public:
		CActionGroupShape();
		~CActionGroupShape();

	public:
		//��ʼ��
		void Triger(void);

		//���ͼ��
		void GroupShape();
		
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
