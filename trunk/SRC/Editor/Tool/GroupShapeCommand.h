#ifndef _ACTION_GROUP_SHAPE_H
#define _ACTION_GROUP_SHAPE_H

#include "ICommand.h"
#include <vector>
using std::vector;
#include "ILayer.h"

namespace Editor
{
	class CActionGroupShape : public Framework::ICommand
	{
	public:
		CActionGroupShape();
		~CActionGroupShape();

	public:
		//��ʼ��
		void Initialize(Framework::IUIObject *pTargetControl);

		void Click();
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
		vector<Carto::ILayer*> m_players;
	};

#endif
}
