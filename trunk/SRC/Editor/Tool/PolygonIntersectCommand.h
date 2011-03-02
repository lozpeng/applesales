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
		//初始化
		void Triger(void);

		//清除
		void Clear(void);


	private:
		//图形
		vector<Geometry*> m_shapes;	

		//图形ID
		vector<long> m_shapeIds;

		//图层
		vector<otCarto::ILayer*> m_players;
	};

}

#endif