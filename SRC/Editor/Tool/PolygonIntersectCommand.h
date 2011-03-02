#ifndef _ACTION_POLYGONINTERSECT_H_
#define _ACTION_POLYGONINTERSECT_H_

#include "ICommand.h"
#include <vector>
using std::vector;


namespace Editor
{

	class CActionPolygonIntersect: public Framework::ICommand
	{
	public:
		CActionPolygonIntersect(void);
		virtual ~CActionPolygonIntersect(void);

	public:
		//��ʼ��
		void Triger(void);

		//���
		void Clear(void);


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