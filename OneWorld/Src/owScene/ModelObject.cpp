#include <owScene/ModelObject.h>
#include <osg/Matrixd>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>

using namespace owScene;

std::string MatrixToString(const osg::Matrix& matrix)
{
	std::ostringstream os;

	os<<matrix(0,0)<<" "<<matrix(0,1)<<" "<<matrix(0,2)<<" "<<matrix(0,3)<<" "<<
		matrix(1,0)<<" "<<matrix(1,1)<<" "<<matrix(1,2)<<" "<<matrix(1,3)<<" "<<
		matrix(2,0)<<" "<<matrix(2,1)<<" "<<matrix(2,2)<<" "<<matrix(2,3)<<" "<<
		matrix(3,0)<<" "<<matrix(3,1)<<" "<<matrix(3,2)<<" "<<matrix(3,3);
	return os.str();
}


osg::Matrixd getLocalMatrix(ModelPos pos)
{
	osg::Quat rota(pos._rot.x(), osg::Vec3(1.0, 0.0, 0.0), pos._rot.y(), osg::Vec3(0.0, 1.0, 0.0),pos._rot.z(), osg::Vec3(0.0, 0.0, 1.0));

	osg::Matrixd mt = osg::Matrixd::scale(pos._scale)*osg::Matrixd::rotate(rota);

	return mt;
}

ModelObject::ModelObject(const ModelObject& fn,const osg::CopyOp& copyop/*=CopyOp::SHALLOW_COPY*/)
: Group(fn,copyop)
{

}

void ModelObject::read(const Config& config)
{
		ModelPos pos;
		std::string anchor,off,rot,scale;

		_modelParam._name = config.value("name");
		_modelParam._radius = config.value<float>("radius",1.0e+10);
		_modelParam._lodratio = config.value<float>("lodratio", 30.0);
		_modelParam._path = config.value("path");

		anchor = config.value("anchor");
		sscanf(anchor.c_str(),"%lf,%lf,%lf", &(pos._anchor._v[0]), &(pos._anchor._v[1]), &(pos._anchor._v[2]));

		off = config.value("off");
		sscanf(off.c_str(),"%lf,%lf,%lf", &(pos._off._v[0]), &(pos._off._v[1]), &(pos._off._v[2]));

		rot = config.value("rot");
		sscanf(rot.c_str(),"%lf,%lf,%lf", &(pos._rot._v[0]), &(pos._rot._v[1]), &(pos._rot._v[2]));

		scale = config.value("scale");
		sscanf(scale.c_str(),"%lf,%lf,%lf", &(pos._scale._v[0]), &(pos._scale._v[1]), &(pos._scale._v[2]));

		_modelParam._pos = pos;

		CreateModel();
}

void ModelObject::CreateModel()
{
	//
	osg::ref_ptr<SpatialReference> _srs84 = SpatialReference::create("wgs84");
	osg::Vec3d off = _modelParam._pos._anchor + _modelParam._pos._off;
	osg::Matrixd tm,lm;
	double lon,lat,h;

	if(!_srs->isEquivalentTo(_srs84))
	{
		_srs->transform(off._v[0],off._v[1],_srs84, lon, lat);
		lon = osg::DegreesToRadians(lon);
		lat = osg::DegreesToRadians(lat);
		h = off._v[2];
	}
	else
	{

		lon = osg::DegreesToRadians(off._v[0]);
		lat = osg::DegreesToRadians(off._v[1]);
		h = off._v[2];
	}

	_srs->getEllipsoid()->computeLocalToWorldTransformFromLatLongHeight(lat,lon,h,tm);
	lm = getLocalMatrix(_modelParam._pos);

	//
	osg::MatrixTransform* trans = new osg::MatrixTransform(tm*lm);
	trans->setName(_modelParam._name);

	//

#if 0
	osg::PagedLOD* pglod = new osg::PagedLOD;
	std::string filepath = _path+_modelParam._path;

	pglod->setFileName(0,filepath);
	pglod->setRange(0,0,_modelParam._radius*_modelParam._lodratio);
	trans->addChild(pglod);

#else
	osg::LOD* lod = new osg::LOD;
	std::string filepath = _path+_modelParam._path;

	osg::Node* model = osgDB::readNodeFile(filepath);
	lod->addChild(model, 0, _modelParam._radius*_modelParam._lodratio);
	trans->addChild(lod);

#endif

	 addChild(trans);

}
