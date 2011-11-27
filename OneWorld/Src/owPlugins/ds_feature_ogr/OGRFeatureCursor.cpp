#include <owPlugins/ds_feature_ogr/OGRFeatureCursor.h>
#include <owPlugins/ds_feature_ogr/OGRFeature.h>

using namespace owPlugins;

OGRFeatureCursor::OGRFeatureCursor()
{
	_pos = -1;
}

OGRFeatureCursor::~OGRFeatureCursor()
{

}

void OGRFeatureCursor::reset()
{
	_pos = 0;
}

bool OGRFeatureCursor::hasNext()
{
	if(_pos>=_features.size())
		return false;
	else
		return true;
}

Feature* OGRFeatureCursor::next()
{
	OGRFeature* ogr_feature = _features[_pos++];
	
	OGRGSFeature* ogr_gs_feature = new OGRGSFeature(ogr_feature);

	return ogr_gs_feature;
}