#ifndef _OWSCENE_MODELSPACE_H
#define _OWSCENE_MODELSPACE_H

#include <owScene/export.h>
#include <owScene/ModelSet.h>
#include <osg/Group>
#include <osg/CopyOp>

namespace owScene
{

	class OWSCENE_EXPORT ModelWorkSpace : public osg::LOD
	{
	public:

		ModelWorkSpace(){}
		ModelWorkSpace(const ModelWorkSpace& fgn, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);
		
		META_Node(owScene,ModelWorkSpace);

	public:

		//
		void read(const Config& config);

		//
		void write(Config& config);

		//
		void AddMoelSet(ModelSet* modelSet) {_root->addChild(modelSet);}

		//
		owUtil::SpatialReference* getSrs(){return _srs.get();}

	protected:
		
		~ModelWorkSpace(){}

	protected:

		//
		std::string _name;

		//
		osg::ref_ptr<SpatialReference> _srs;

		//
		osg::ref_ptr<GeoExtent> _extent;

		//
		double _height;

		//
		double _lodratio;

		//
		osg::ref_ptr<osg::Group> _root;

		//
		std::string _wkt;
	
	};
}

#endif