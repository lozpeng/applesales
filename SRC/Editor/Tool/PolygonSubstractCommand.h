#ifndef _ACTION_POLYGONSUBSTRACT_H_
#define _ACTION_POLYGONSUBSTRACT_H_

#include "IAction.h"
#include <vector>
using std::vector;


namespace otEditor
{

	class CActionPolygonSubstract: public otFramework::IAction
	{
	public:
		CActionPolygonSubstract(void);
		virtual ~CActionPolygonSubstract(void);

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