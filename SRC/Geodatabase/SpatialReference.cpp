#include "stdafx.h"
#include "SpatialReference.h"
#include "ogr_spatialref.h"
#include "cpl_conv.h"

namespace Geodatabase{

CSpatialReference::CSpatialReference()
{
   m_Handle =new OGRSpatialReference();
}

CSpatialReference::CSpatialReference(const char *wkt)
{
	m_Handle =new OGRSpatialReference(wkt);
}

CSpatialReference::CSpatialReference(const Geodatabase::CSpatialReference &other)
{
    m_Handle = NULL;

	if( other.m_Handle)
	{
		OGRSpatialReference* psrIn = (OGRSpatialReference*)other.m_Handle;
		m_Handle = new OGRSpatialReference( *psrIn );
	}
}

CSpatialReference& CSpatialReference::operator =(const CSpatialReference& other)
{
	Clear();
	if( other.m_Handle)
	{
		OGRSpatialReference* psrIn = (OGRSpatialReference*)other.m_Handle;
		m_Handle = new OGRSpatialReference( *psrIn );
	}

	return *this;

}

CSpatialReference::~CSpatialReference()
{
    Clear();
}

void CSpatialReference::Clear()
{
	if( m_Handle )
	{
		OGRSpatialReference* psr = (OGRSpatialReference*)m_Handle;
		//psr->Release();
		m_Handle = NULL;
	}
}

CSpatialReference* CSpatialReference::Clone() const
{
	return new CSpatialReference(*this);
}

bool CSpatialReference::ImportFromWkt(const char *wkt)
{
	if(!m_Handle)
	{
		return false;
	}

	OGRSpatialReference* psr = (OGRSpatialReference*)m_Handle;

	char * cc[2];
	cc[0] =(char*)wkt;
	cc[1] =NULL;

	if(OGRERR_NONE!=psr->importFromWkt(cc))
	{
		return false;
	}

	return true;

}


std::string CSpatialReference::ExportToWkt() const
{
	if(!m_Handle)
	{
		return "";
	}

	OGRSpatialReference* psr = (OGRSpatialReference*)m_Handle;

	char *pszWKT = NULL;
	psr->exportToWkt(&pszWKT);

	std::string wkt =pszWKT;

	CPLFree( pszWKT );

	return wkt;

}

bool CSpatialReference::ImportFromESRI(const char *wkt)
{
	if(!m_Handle)
	{
		return false;
	}

	OGRSpatialReference* psr = (OGRSpatialReference*)m_Handle;

	char * cc[2];
	cc[0] =(char*)wkt;
	cc[1] =NULL;

	if(OGRERR_NONE!=psr->importFromESRI(cc))
	{
		return false;
	}

	return true;
}


bool CSpatialReference::IsGeographic() const
{
	if(!m_Handle)
	{
		return false;
	}
    OGRSpatialReference* psr = (OGRSpatialReference*)m_Handle;

	return psr->IsGeographic();
}

bool CSpatialReference::IsProjected() const
{
	if(!m_Handle)
	{
		return false;
	}
	OGRSpatialReference* psr = (OGRSpatialReference*)m_Handle;

	return psr->IsProjected();
}

bool CSpatialReference::IsSame(const Geodatabase::CSpatialReference *pOther) const
{
	if(m_Handle ==NULL || pOther->m_Handle==NULL)
	{
		return false;
	}
    OGRSpatialReference* psr = (OGRSpatialReference*)m_Handle;

	return psr->IsSame((OGRSpatialReference*)pOther->m_Handle);
}

std::string CSpatialReference::GetGeogName() const
{
	if(!m_Handle)
	{
		return "";
	}

	OGRSpatialReference* psr = (OGRSpatialReference*)m_Handle;

	//查找GEOGCS节点
	OGR_SRSNode *pNode =psr->GetAttrNode("GEOGCS");

	if(!pNode)
	{
		return "";
	}

	return pNode->GetChild(0)->GetValue();


}

std::string CSpatialReference::GetProjName() const
{
	if(!m_Handle)
	{
		return "";
	}

	OGRSpatialReference* psr = (OGRSpatialReference*)m_Handle;

	//查找GEOGCS节点
	OGR_SRSNode *pNode =psr->GetAttrNode("PROJCS");

	if(!pNode)
	{
		return "";
	}

	return pNode->GetChild(0)->GetValue();
}

void* CSpatialReference::GetHandle() const
{
	return m_Handle;
}

SYSTEM::SYS_UNIT_TYPE CSpatialReference::GetLinearUnits() const
{
	if(!m_Handle)
	{
		return SYSTEM::SYS_UNIT_UNKNOWN;
	}
	char *strUnit =NULL;
	((OGRSpatialReference*)m_Handle)->GetLinearUnits(&strUnit);

	return SYSTEM::UnitConverter::GetUnitByString(strUnit);

}

SYSTEM::SYS_UNIT_TYPE CSpatialReference::GetAngularUnits() const
{
	if(!m_Handle)
	{
		return SYSTEM::SYS_UNIT_UNKNOWN;
	}
	char *strUnit =NULL;
	((OGRSpatialReference*)m_Handle)->GetAngularUnits(&strUnit);

	return SYSTEM::UnitConverter::GetUnitByString(strUnit);

}


}//namespace Geodatabase

