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