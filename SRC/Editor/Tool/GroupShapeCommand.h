#ifndef _ACTION_GROUP_SHAPE_H
#define _ACTION_GROUP_SHAPE_H

#include "IAction.h"
#include <vector>
using std::vector;


namespace otEditor
{
	class CActionGroupShape : public otFramework::IAction
	{
	public:
		CActionGroupShape();
		~CActionGroupShape();

	public:
		//初始化
		void Triger(void);

		//组合图形
		void GroupShape();
		
		//清除
		void Clear();

	private:
		//图形
		vector<Geometry*> m_shapes;	

		//图形ID
		vector<long> m_shapeIds;

		//图层
		vector<otCarto::ILayer*> m_players;
	};

#endif
}
