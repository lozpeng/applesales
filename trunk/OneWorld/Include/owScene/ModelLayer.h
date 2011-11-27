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

	class OWSCENE_EXPORT ModelLayer : public osg::Referenced
	{
	public:
		ModelLayer();

	public:

		//
		void read(const Config& config);

		//
		void write(Config& config);

		//
		osg::Node* GetRoot() {return _root.get(); }

		//
		std::string getName()const {return _name;};
		void setName(const std::string& name){_name = name;};

	protected:

		virtual ~ModelLayer(){}
	protected:
		//
		osg::ref_ptr<osg::Group> _root;

		//
		std::string _name;
		std::string _url;

		//
		std::string _wkt;
		osg::ref_ptr<SpatialReference> _srs;

		//
		osg::ref_ptr<GeoExtent> _extent;
		double _height;
		double _lodratio;
	};


	typedef std::vector<osg::ref_ptr<ModelLayer>> ModelLayerList;
}

#endif