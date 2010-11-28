#include "stdafx.h"
#include  "IFeatureSelection.h"
#include "IFeatureClass.h"

namespace Geodatabase{

IFeatureSelection::IFeatureSelection(Geodatabase::IFeatureClass *pFeatureClass)
                      : CSelctionSet(pFeatureClass)
{
   
}

IFeatureSelection::~IFeatureSelection()
{

}

const GEOMETRY::geom::Geometry* IFeatureSelection::NextShape()
{
	long id =NextID();

	if(m_pTable==NULL)
	{
		return NULL;
	}
	
	m_pShape =((IFeatureClass*)m_pTable)->GetFeatureShape(id);

	return m_pShape.get();

}




} //namespace Geodatabase
