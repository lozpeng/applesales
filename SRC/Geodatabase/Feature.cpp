#include "stdafx.h"
#include "Feature.h"
#include "IFeatureClass.h"
#include <Geometry/geom/GeometryFactory.h>
#include <Geometry/geom/Geometry.h>

namespace Geodatabase{


CFeature::CFeature(IFeatureClass *pFeatureClass,long oid)
	:IRow(pFeatureClass,oid)
{
	m_pGeometry =NULL;
}

CFeature::CFeature(const Geodatabase::CFeature &other):IRow(other)
{
	m_pGeometry =other.GetShapeClone();
}

CFeature::~CFeature()
{
	if(m_pGeometry)
	{
		delete m_pGeometry;
	}
}

void CFeature::Update()
{
	if(m_pTable)
	{
		IFeatureClass *pFeatureClass =dynamic_cast<IFeatureClass*>(m_pTable);

		if(pFeatureClass)
		{
			pFeatureClass->UpdateFeature(this);
		}
	}
}

void CFeature::Delete()
{
	if(m_pTable)
	{
		IFeatureClass *pFeatureClass =dynamic_cast<IFeatureClass*>(m_pTable);

		if(pFeatureClass)
		{
			pFeatureClass->DeleteFeature(m_oid);
		}
	}
}

GEOMETRY::geom::Geometry* CFeature::GetShapeClone() const
{
	if(m_pGeometry)
	{
		return m_pGeometry->clone();
	}

	return NULL;
}

void CFeature::SetEmpty()
{
	if(m_pGeometry)
	{
		delete m_pGeometry;
		m_pGeometry =NULL;
	}
	for(size_t i=0;i<m_values.size();i++)
	{
		m_values[i].clear();
	}
}

void CFeature::SetShape(GEOMETRY::geom::Geometry *pGeometry)
{
	if(m_pGeometry)
	{
		delete m_pGeometry;
		m_pGeometry =NULL;
	}
	m_pGeometry =pGeometry;
}

CFeature* CFeature::Clone()
{
	return new CFeature(*this);
}


} //namespace Geodatabase