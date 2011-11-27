#ifndef _OWSCENE_MODELOBJECT_H
#define _OWSCENE_MODELOBJECT_H

#include <owScene/export.h>
#include <owUtil/SpatialReference.h>
#include <owUtil/config.h>
#include <osg/Group>
#include <osg/CopyOp>

using namespace owUtil;

namespace owScene
{

	//模型位置定义
	struct ModelPos
	{
		osg::Vec3d _anchor;
		osg::Vec3d _off;
		osg::Vec3d _rot;
		osg::Vec3d _scale;
	};

	//模型参数定义
	struct ModelParam
	{
		//模型名称
		std::string _name;

		//模型位置
		ModelPos _pos;

		//模型路径
		std::string _path;

		//模型半径
		double _radius;

		//lod
		double _lodratio;
	};


	class OWSCENE_EXPORT ModelObject : public osg::Group
	{
	public:

		ModelObject(){}
		ModelObject(const ModelObject& fgn, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

		META_Node(owScene,ModelObject);

	public:
		//
		void read(const Config& config);

		//
		void SetSrs(SpatialReference* srs) {  _srs = srs; }

		//
		void SetPath(std::string path) {  _path = path; }

	protected:

		~ModelObject(){}

		void CreateModel();

	private:

		//
		ModelParam _modelParam;

		osg::ref_ptr<SpatialReference> _srs;

		std::string _path;

	};
}

#endif