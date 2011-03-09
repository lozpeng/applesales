#ifndef _ACTION_GROUP_SHAPE_H
#define _ACTION_GROUP_SHAPE_H

#include "ICommand.h"
#include <vector>
using std::vector;
#include "ILayer.h"

namespace Editor
{
	class CActionGroupShape : public Framework::ICommand
	{
	public:
		CActionGroupShape();
		~CActionGroupShape();

	public:
		//初始化
		void Initialize(Framework::IUIObject *pTargetControl);

		void Click();
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
		vector<Carto::ILayer*> m_players;
	};

#endif
}
