#include <owPlugins/ly_feature_label/FeatureLableLayer.h>
#include <osgText/Text>
#include <owScene/DataSourceFactory.h>
#include <owScene/FeatureSource.h>
#include <owScene/TerrainTile.h>
#include <Windows.h>

using namespace owPlugins;

FeatureLabelLayer::FeatureLabelLayer() : _font_size(10), _font_name("fonts/SIMLI.TTF"), _size_mode(OBJECT_SIZE)
{

}

FeatureLabelLayer::~FeatureLabelLayer()
{

}


osg::Node* FeatureLabelLayer::createNode(const TerrainTile* tile, Feature* f)
{
	//
	osg::MatrixTransform* mt = new osg::MatrixTransform;
	osg::Geode* _geode= new osg::Geode;

	//
	GeoShapeList shapes = f->getShapes();
	GeoPointList points = shapes[0].getPart(0);
	double lon,lat,h;
	osg::Vec3d start, end, pos;

	const SpatialReference* srs = getSP()->getSrs();
	const SpatialReference* tile_srs = tile->getSP()->getSrs();

	std::vector<osg::Vec3d> ins;
	ins.insert(ins.begin(), points.begin(), points.end());

	if(!srs->isEquivalentTo(tile_srs))
	{
		srs->transformPoints(tile_srs, &ins);
	}

	//
	lon = osg::DegreesToRadians(ins[0]._v[0]);
	lat = osg::DegreesToRadians(ins[0]._v[1]);
	h = ins[0]._v[2];

	srs->getEllipsoid()->convertLatLongHeightToXYZ(lat, lon, h+10000000.0,start._v[0], start._v[1], start._v[2]);
	srs->getEllipsoid()->convertLatLongHeightToXYZ(lat, lon, h-10000000.0,end._v[0], end._v[1], end._v[2]);
	tile->genIntersectPoint(start, end, pos);

	mt->setMatrix(osg::Matrix::translate(pos));

	//
	osgText::Text* text = new osgText::Text;

	std::string name= f->getAttribute(_key).asString();
	wchar_t wtext[1024] = {0};
	int charcount = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (char*)(name.c_str()), name.length(), wtext, 1024);

	text->setFont(_font_name); 
	text->setCharacterSize(_font_size);

	if (_size_mode == OBJECT_SIZE)
	{
		text->setCharacterSizeMode(osgText::Text::OBJECT_COORDS_WITH_MAXIMUM_SCREEN_SIZE_CAPPED_BY_FONT_HEIGHT);
	}
	else
	{
		text->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);
	}

	text->setPosition(Vec3(0.0,0.0,0.0));
	text->setAlignment(osgText::TextBase::LEFT_BOTTOM);
	text->setAxisAlignment(osgText::Text::SCREEN);
	text->setText(wtext);
	text->setName(name.c_str());
	text->setColor(_color);

	_geode->addDrawable(text);

	mt->addChild(_geode);

	return mt;
}

void FeatureLabelLayer::read(const Config& config)
{
	//TODO

	FeatureLayer::read(config);

	_sourcename = config.value("datasource");
	_key = config.value("key");
	_font_size = config.value<int>("font_size",10);

}

void FeatureLabelLayer::write(Config& config)
{
	//TODO

	FeatureLayer::write(config);
}

void FeatureLabelLayer::setEnable(bool enable)
{
	//TODO

}

bool FeatureLabelLayer::getEnable()
{
	//TODO
	return false;
}

bool FeatureLabelLayer::initialize(ProgressBase* base)
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

bool FeatureLabelLayer::unInitialize(ProgressBase* base)
{
	if(getDataSource())
		return getDataSource()->disConnect(base);

	return true;
}