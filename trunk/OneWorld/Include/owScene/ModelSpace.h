#ifndef _OWSCENE_MODELSPACE_H
#define _OWSCENE_MODELSPACE_H

#include <owScene/export.h>
#include <owScene/ModelLayer.h>
#include <osg/Group>
#include <osg/CopyOp>

namespace owScene
{

	class OWSCENE_EXPORT ModelSpace : public osg::Group
	{
	public:

		ModelSpace(){}
		ModelSpace(const ModelSpace& fgn, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
		
		META_Node(owScene,ModelSpace);

	public:

		//添加模型层
		void AddModelLayer(ModelLayer* layer);

		//获取模型层个数
		int GetLayerCount() {return _layerlist.size();}

		//获取模型层
		ModelLayer* GetLayer(int i) {return _layerlist[i].get();}


	protected:
		
		~ModelSpace(){}

	private:

		ModelLayerList _layerlist;
	
	};
}

#endif