#include "stdafx.h"
#include "IFeatureCursor.h"
#include "IFeatureClass.h"

namespace Geodatabase{


IFeatureCursor::IFeatureCursor(IFeatureClass *pFeatureClass)
	:ICursor(pFeatureClass)
{

}

IFeatureCursor::~IFeatureCursor()
{

}

IRowPtr IFeatureCursor::NextRow()
{
	return IRowPtr(NextFeature());
}




} //namespace Geodatabase