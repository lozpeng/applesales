#ifndef _ACTION_POLYGONUNION_H_
#define _ACTION_POLYGONUNION_H_

#include "IAction.h"
#include <vector>
using std::vector;


namespace otEditor
{

	class CActionPolygonUnion: public otFramework::IAction
	{
	public:
		CActionPolygonUnion(void);
		virtual ~CActionPolygonUnion(void);

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