#include "stdafx.h"
#include "IGeodataObject.h"

namespace Geodatabase
{

IGeodataObject::IGeodataObject(IWorkspace* workspace)
{
	m_pWorkspace = workspace;
	m_objType = GDT_UNKNOWN_TYPE;
}

IGeodataObject::~IGeodataObject()
{

}

GEODATATYPE IGeodataObject::GetType() const
{
	return m_objType;
}

std::string IGeodataObject::Getname() const
{
	return m_name;
}

IWorkspace* IGeodataObject::GetWorkspace() const
{
	return m_pWorkspace;
}

bool IGeodataObject::GetExtent(GEOMETRY::geom::Envelope *pEnvelop) const
{
	*pEnvelop = m_Envelop;

	return true;
}

void IGeodataObject::serialization(SYSTEM::IArchive &ar)
{
    
}

}