#ifndef _OWSCENE_MODELLAYER_H
#define _OWSCENE_MODELLAYER_H

#include <owScene/export.h>
#include <owUtil/config.h>
#include <osg/PagedLOD>
#include <owUtil/SpatialReference.h>
#include <owUtil/GeoExtent.h>

using namespace owUtil;

namespace owScene
{

	class OWSCENE_EXPORT ModelSet : public osg::PagedLOD
	{
	public:
		ModelSet() {}
		ModelSet(const ModelSet& fgn, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

		META_Node(owScene,ModelSet);

	public:

		//
		void read(const Config& config);

		//
		void write(Config& config);

		//
		std::string getName()const {return _name;};
		void setName(const std::string& name){_name = name;};


		//
		owUtil::SpatialReference* getSrs(){return _srs.get();}
		void ModelSet::setSrs(owUtil::SpatialReference* srs) {_srs = srs;}


	protected:

		virtual ~ModelSet(){}

	protected:

		//
		std::string _name;

		//
		std::string _url;

		//
		osg::ref_ptr<SpatialReference> _srs;

		//
		osg::ref_ptr<GeoExtent> _extent;

		//
		double _height;

		//
		double _lodratio;

	};

}

#endif