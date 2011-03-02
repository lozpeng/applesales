#ifndef _ACTION_POLYGONXOR_H_
#define _ACTION_POLYGONXOR_H_
#include "IAction.h"
#include <vector>
using std::vector;


namespace otEditor
{

	class CActionPolygonXor: public otFramework::IAction
	{
	public:
		CActionPolygonXor(void);
		virtual ~CActionPolygonXor(void);

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