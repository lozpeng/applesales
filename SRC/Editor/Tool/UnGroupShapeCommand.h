#ifndef _ACTION_UNGROUP_SHAPE_H
#define _ACTION_UNGROUP_SHAPE_H

#include "ICommand.h"
#include "Ilayer.h"
#include <vector>
using std::vector;

namespace Editor
{
	class CActionUnGroupShape : public Framework::ICommand
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
		vector<Carto::ILayer*> m_players;
	};


}
#endif