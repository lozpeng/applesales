#ifndef _ACTION_POLYGONUNION_H_
#define _ACTION_POLYGONUNION_H_

#include "ICommand.h"
#include "ILayer.h"
#include <vector>
using std::vector;


namespace Editor
{

	class CPolygonUnionTool: public Framework::ICommand
	{
	public:
		CPolygonUnionTool(void);
		virtual ~CPolygonUnionTool(void);

	public:
		//��ʼ��
		void Initialize(Framework::IUIObject *pTargetControl);

		void Click();
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