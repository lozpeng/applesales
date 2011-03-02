#ifndef _ACTION_POLYGONINTERSECT_H_
#define _ACTION_POLYGONINTERSECT_H_

#include "IAction.h"
#include <vector>
using std::vector;


namespace otEditor
{

	class CActionPolygonIntersect: public otFramework::IAction
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
		vector<otCarto::ILayer*> m_players;
	};

}

#endif