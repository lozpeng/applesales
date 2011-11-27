#include <owPlugins/ds_feature_ogr/OGRFeatureSource.h>
#include <owPlugins/ds_feature_ogr/OGRFeatureCursor.h>
#include "ogrsf_frmts.h"

using namespace owPlugins;



OGRFeatureSource::OGRFeatureSource()
{
	_poDS = NULL;

	_poLayer = NULL;
}

OGRFeatureSource::~OGRFeatureSource()
{

}

bool OGRFeatureSource::Connect(owUtil::ProgressBase* p/*=NULL*/)
{
	if(_poDS)
		return true;

	//ogr驱动注册
	OGRRegisterAll();

	//获取数据集和数据图层
	_poDS = OGRSFDriverRegistrar::Open(_url.c_str(), FALSE);
	if(!_poDS)
		return false;

	_poLayer = _poDS->GetLayer(0);

	if(!_poLayer)
		return false;

	//投影信息
	char *wkt_prj;
	OGREnvelope ogr_ext;
	OGRSpatialReference* ogr_sp_ref;

	ogr_sp_ref = _poLayer->GetSpatialRef();
	ogr_sp_ref->exportToWkt(&wkt_prj);
	_poLayer->GetExtent(&ogr_ext);

	osg::ref_ptr<GeoExtent> geo_ext = new GeoExtent(ogr_ext.MinX, ogr_ext.MinY, ogr_ext.MaxX, ogr_ext.MaxY);
	osg::ref_ptr<SpatialReference> srs = SpatialReference::create(wkt_prj);
	osg::ref_ptr<SpatialProperty> sp = new SpatialProperty(geo_ext.get(),srs.get());
	CPLFree(wkt_prj);

	//
	setSP(sp);

	//生成属性表方案
	genAttributeSchemaList();

	//设置数据源有效
	setValid(true);

	return true;
}

bool OGRFeatureSource::disConnect(owUtil::ProgressBase* p/*=NULL*/)
{
	setValid(false);

	OGRSFDriverRegistrar::GetRegistrar()->ReleaseDataSource(_poDS);

	_poDS = NULL;
	_poLayer = NULL;

	return true;
}

void OGRFeatureSource::read(const Config& config)
{
	FeatureSource::read(config);
	_url = config.value("url");

}

void OGRFeatureSource::write(Config& config) const
{

}

FeatureCursor* OGRFeatureSource::createFeatureCursor()
{
	return NULL;
}

FeatureCursor* OGRFeatureSource::createFeatureCursor(const std::string& exp)
{
	return NULL;
}

FeatureCursor* OGRFeatureSource::createFeatureCursor(const SpatialProperty& sp)
{

	osg::ref_ptr<OGRFeatureCursor> feature_cursor = new OGRFeatureCursor;

	_poLayer->SetAttributeFilter(NULL);
	_poLayer->SetSpatialFilterRect(sp.getGeoExtent()->xMin(),sp.getGeoExtent()->yMin(),sp.getGeoExtent()->xMax(),sp.getGeoExtent()->yMax());
	_poLayer->ResetReading();

	OGRFeature *pFeature =NULL;

	while(true)
	{
		pFeature =_poLayer->GetNextFeature();
		if(!pFeature)
		{
			break;
		}
		feature_cursor->GetFeatures().push_back(pFeature);
	}
	feature_cursor->reset();

	if(feature_cursor->GetFeatures().size() == 0)
		return NULL;

	return feature_cursor.release();
}


Feature* OGRFeatureSource::createFeature(FeatureOID id)
{
	return NULL;
}

unsigned int OGRFeatureSource::getFeaturesCount() const
{
	if(_poLayer == NULL)
		return 0;

	return _poLayer->GetFeatureCount();
}

const AttributeSchemaList& OGRFeatureSource::getAttributeSchemaList() const
{
	return _attrbuteschemalist;
}

void OGRFeatureSource::genAttributeSchemaList()
{
	long count = _poLayer->GetLayerDefn()->GetFieldCount();

	for(int i=0; i<count; i++)
	{
		std::string attr_name;
		Attribute::Type attr_type;

		OGRFieldDefn *pFieldDef =_poLayer->GetLayerDefn()->GetFieldDefn(i);


		//获得字段名称
		attr_name = pFieldDef->GetNameRef();

		//获得字段类型
		OGRFieldType ftype =pFieldDef->GetType();
		switch(ftype)
		{


		case OFTInteger:
			{
				attr_type = Attribute::TYPE_INT;
				break;
			}
		case OFTReal:
			{
				attr_type = Attribute::TYPE_DOUBLE;
				break;
			}

		case OFTString:
			{
				attr_type =Attribute::TYPE_STRING;
				break;

			}
		case OFTDate :
		case OFTTime:
		case OFTDateTime:
		case OFTBinary:
			{
				attr_type = Attribute::TYPE_STRING;
				break;
			}
		default:
			{
				attr_type = Attribute::TYPE_UNSPECIFIED;
				break;
			}

		}

		//
		AttributeSchema attr_schema(attr_name, attr_type);

		//
		_attrbuteschemalist.push_back(attr_schema);
	}
}