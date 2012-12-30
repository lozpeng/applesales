#include <owPlugins/ly_feature_geometry/FeatureGeometryLayer.h>
#include <owScene/DataSourceFactory.h>
#include <owScene/FeatureSource.h>
#include <owScene/TerrainTile.h>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/LineWidth>

using namespace owPlugins;

FeatureGeometryLayer::FeatureGeometryLayer()
{

}

FeatureGeometryLayer::~FeatureGeometryLayer()
{

}

osg::Node* FeatureGeometryLayer::createNode(const TerrainTile* tile, Feature* f)
{
	//
	osg::Geode *_geode= new osg::Geode;

	//
	GeoShapeList shapes = f->getShapes();
	for(int i=0; i<shapes.size(); i++)
	{
		osg::ref_ptr<osg::Geometry> _geometry = new osg::Geometry;
		osg::ref_ptr<osg::Vec3Array> _vertexs = new osg::Vec3Array;
		osg::ref_ptr<osg::Vec3Array> _nomals = new osg::Vec3Array;
		GeoShape shape = shapes[i];

		_geometry->setVertexArray(_vertexs.get());
		_geometry->setNormalArray(_nomals);
		_geometry->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);

		_geode->addDrawable(_geometry.get());

		//顶点颜色
		osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
		colors->push_back(_color);

		_geometry->setColorArray(colors);
		_geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
	
		//构建顶点数组
		double lon,lat,h;
		double dx,dy,dz;
		int l=0;


		const SpatialReference* srs = getSP()->getSrs();
		const SpatialReference* tile_srs = tile->getSP()->getSrs();

		for(int j=0; j<shape.getPartCount(); j++)
		{
			std::vector<osg::Vec3d> ins, outs;
			osg::ref_ptr<osg::DrawElementsUShort> dui = new osg::DrawElementsUShort(osg::DrawElements::LINE_STRIP);

			GeoPointList points= shape.getPart(j);
			ins.insert(ins.end(), points.begin(), points.end());
		
			if(!srs->isEquivalentTo(tile_srs))
			{
				srs->transformPoints(tile_srs, &ins);
			}

			for(int k=0; k<ins.size(); k++)
			{
				lon = osg::DegreesToRadians(ins[k]._v[0]);
				lat = osg::DegreesToRadians(ins[k]._v[1]);
				h = ins[k]._v[2];

				//
				srs->getEllipsoid()->convertLatLongHeightToXYZ(lat, lon, h, ins[k]._v[0], ins[k]._v[1], ins[k]._v[2]);

			}

			if(_on_ground)//生成贴地面的点集
			{
				((TerrainTile*)tile)->genSlicePoints(ins, outs);
				if(outs.size() == 0)
					continue;

				for(int k=0; k<outs.size(); k++)
				{
					//顶点
					Vec3 v(outs[k]._v[0],outs[k]._v[1],outs[k]._v[2]);
					_vertexs->push_back(outs[k]);

					//法线
					v.normalize();
					_nomals->push_back(v);

					//图元
					dui->push_back(l++);
				}
			}
			else
			{
				for(int k=0; k<ins.size(); k++)
				{
					//顶点
					Vec3 v(ins[k]._v[0],ins[k]._v[1],ins[k]._v[2]);
					_vertexs->push_back(outs[k]);

					//法线
					v.normalize();
					_nomals->push_back(v);

					//图元
					dui->push_back(l++);
				}
			}


			//添加图元集
			_geometry->addPrimitiveSet(dui);

		}
	}

	return _geode;
}

void FeatureGeometryLayer::read(const Config& config)
{
	//TODO

	FeatureLayer::read(config);

	_sourcename = config.attr("datasource");

}

void FeatureGeometryLayer::write(Config& config)
{
	//TODO

	FeatureLayer::write(config);
}

void FeatureGeometryLayer::setEnable(bool enable)
{
	//TODO

}

bool FeatureGeometryLayer::getEnable()
{
	//TODO
	return false;
}

bool FeatureGeometryLayer::initialize(ProgressBase* base)
{
	if(!getDataSource())
	{
		if(_sourcename.empty())
			return false;

		DataSource* datasource = DataSourceFactory::Instance().getRegistryDataSource(_sourcename);

		if(!datasource)
			return false;

		setDataSource(datasource);
	}


	FeatureSource* feature_source = dynamic_cast<FeatureSource*>(getDataSource());
	if(!feature_source)
		return false;

	if(!feature_source->Connect(base))
		return false;

	if(!feature_source->bValid())
		return false;

	//
	setSP(feature_source->getSP());

	//
	setValid(true);

	return true;

}

bool FeatureGeometryLayer::unInitialize(ProgressBase* base)
{
	if(getDataSource())
		return getDataSource()->disConnect(base);

	return true;
}