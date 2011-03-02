#ifndef _ACTION_POLYGONSUBSTRACT_H_
#define _ACTION_POLYGONSUBSTRACT_H_

#include "IAction.h"
#include <vector>
using std::vector;


namespace Editor
{

	class CActionPolygonSubstract: public Framework::IAction
	{
	public:
		CActionPolygonSubstract(void);
		virtual ~CActionPolygonSubstract(void);

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