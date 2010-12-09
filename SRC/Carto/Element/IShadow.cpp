#include "StdAfx.h"
#include "IShadow.h"
#include "SimpleShadow.h"

namespace Element{
IShadow::IShadow(void)
{
	m_pDrawGeometry = NULL;
	m_pGeometry = NULL;

	m_fXGap = 0;
	m_fYGap = 0;

}

IShadow::IShadow(const GEOMETRY::geom::Geometry& geometry)
{
	m_pGeometry = geometry.clone();
	m_pDrawGeometry = geometry.clone();;

	m_fXGap = 0;
	m_fYGap = 0;

	UpdateDrawGeometry();
}

IShadow::~IShadow(void)
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry =NULL;
	}
	if(m_pDrawGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pDrawGeometry);
		m_pDrawGeometry =NULL;
	}
}

void IShadow::serialization(SYSTEM::IArchive &ar)
{
	SYSTEM::ISerialization::serialization( ar );

	ar & m_fXGap;
	ar & m_fYGap;

	if(ar.IsRead())
	{
		GEOMETRY::io::WKTReader GeoReader;
		std::string strGeo;

		ar & strGeo;
		m_pGeometry = GeoReader.read(strGeo);

		ar & strGeo;
		m_pDrawGeometry = GeoReader.read(strGeo);
	}
	else
	{
		GEOMETRY::io::WKTWriter GeoWriter;
		std::string strGeo= GeoWriter.write(m_pGeometry); 
		ar & strGeo;

		strGeo= GeoWriter.write(m_pDrawGeometry); 
		ar & strGeo;
	}
}

IShadowPtr IShadow::CreateShadowFromStream(SYSTEM::IArchive &ar)
{
	unsigned long lPos = ar.GetCurrentPos();

	int type;
	ar & type;

	ar.GetCurrentPos() = lPos;

	IShadowPtr pShadow = CreateShadow((Shadow_Type)type);

	if (pShadow != NULL)
		pShadow->serialization(ar);

	return pShadow;

}

IShadowPtr  IShadow::CreateShadow(Shadow_Type type)
{
	switch(type)
	{
	case ST_SIMPLE_SHADOW:
		return CSimpleShadowPtr(new CSimpleShadow());
	default:
		return NULL;
	}
}

void IShadow::SetGeometry(const GEOMETRY::geom::Geometry& geometry)
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}
	m_pGeometry = geometry.clone();

	UpdateDrawGeometry();
}

const GEOMETRY::geom::Geometry* IShadow::GetGeometry()
{
	return m_pGeometry;
}


void IShadow::GetGap(float &fXGap, float &fYGap)
{
	fXGap = m_fXGap;
	fYGap = m_fYGap;
}

void IShadow::SetGap(float fXGap, float fYGap)
{
	m_fXGap = fXGap;
	m_fYGap = fYGap;

	if(!m_pGeometry)
		return;

	UpdateDrawGeometry();
}

void IShadow::UpdateDrawGeometry()
{
	/*if(abs(m_fXGap) < 0.000001 && abs(m_fYGap) < 0.000001)
		return;*/

	if(m_pDrawGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pDrawGeometry);
		m_pDrawGeometry = NULL;
	}

	GEOMETRY::geom::Geometry* m_pMoveGeometry = m_pGeometry->clone();
	m_pMoveGeometry->Move(m_fXGap, m_fYGap);
	m_pDrawGeometry = m_pMoveGeometry->difference(m_pGeometry);
	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pMoveGeometry);
}

}
