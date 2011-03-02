#ifndef _ACTION_UNGROUP_SHAPE_H
#define _ACTION_UNGROUP_SHAPE_H

#include "IAction.h"
#include "TT_Shape.hxx"
#include <vector>
using std::vector;

namespace otEditor
{
	class CActionUnGroupShape : public otFramework::IAction
	{
	public:
		CActionUnGroupShape();
		~CActionUnGroupShape();

	public:
		//初始化
		void Triger(void);

		//组合图形
		void UnGroupShape();

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
