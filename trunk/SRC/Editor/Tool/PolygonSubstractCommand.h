#ifndef _ACTION_POLYGONSUBSTRACT_H_
#define _ACTION_POLYGONSUBSTRACT_H_

#include "ICommand.h"
#include <vector>
using std::vector;


namespace Editor
{

	class CActionPolygonSubstract: public Framework::ICommand
	{
	public:
		CActionPolygonSubstract(void);
		virtual ~CActionPolygonSubstract(void);

	public:
		//��ʼ��
		void Initialize(Framework::IUIObject *pTargetControl);
		void Click(void);

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