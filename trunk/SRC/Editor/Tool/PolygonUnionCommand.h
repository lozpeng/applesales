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
		//初始化
		void Initialize(Framework::IUIObject *pTargetControl);

		void Click();
		//清除
		void Clear(void);


	private:
		//图形
		vector<Geometry*> m_shapes;	
		
		//图形ID
		vector<long> m_shapeIds;
		
		//图层
		vector<Carto::ILayer*> m_players;
	};

}

#endif