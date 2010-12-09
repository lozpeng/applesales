#include "StdAfx.h"
#include "IBackground.h"
#include "SimpleBackground.h"

namespace Element{
IBackground::IBackground(void)
{
	m_fXGap = 0;
	m_fYGap = 0;

	m_pDrawGeometry = NULL;
	m_pGeometry = NULL;
}

IBackground::~IBackground(void)
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

IBackground::IBackground(const GEOMETRY::geom::Geometry& geometry)
{
	m_pGeometry = geometry.clone();
	m_pDrawGeometry = geometry.clone();
	
	m_fXGap = 0;
	m_fYGap = 0;

	UpdateDrawGeometry();
}

void IBackground::serialization(SYSTEM::IArchive &ar)
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

IBackgroundPtr IBackground::CreateBackgroundFromStream(SYSTEM::IArchive &ar)
{
	unsigned long lPos = ar.GetCurrentPos();

	int type;
	ar & type;

	ar.GetCurrentPos() = lPos;

	IBackgroundPtr pBackground = CreateBackground((Background_Type)type);

	if (pBackground != NULL)
		pBackground->serialization(ar);

	return pBackground;

}

IBackgroundPtr  IBackground::CreateBackground(Background_Type type)
{
	switch(type)
	{
	case BT_SIMPLE_BG:
		return CSimpleBackgroundPtr(new CSimpleBackground());
	default:
		return NULL;
	}
}

void IBackground::SetGeometry(const GEOMETRY::geom::Geometry& geometry)
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}
	m_pGeometry = geometry.clone();

	UpdateDrawGeometry();
}

const GEOMETRY::geom::Geometry* IBackground::GetGeometry()
{
	return m_pGeometry;
}
const GEOMETRY::geom::Geometry* IBackground::GetDrawGeometry()
{
	return m_pDrawGeometry;
}
void IBackground::GetGap(float &fXGap, float &fYGap)
{
	fXGap = m_fXGap;
	fYGap = m_fYGap;
}

void IBackground::SetGap(float fXGap, float fYGap)
{
	m_fXGap = fXGap;
	m_fYGap = fYGap;

	if(!m_pGeometry)
		return;

	UpdateDrawGeometry();
}

void IBackground::UpdateDrawGeometry()
{
	if(m_pDrawGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pDrawGeometry);
		m_pDrawGeometry = NULL;
	}

	GEOMETRY::geom::Envelope envelope = *m_pGeometry->getEnvelopeInternal();
	envelope.expandBy(m_fXGap, m_fYGap);
	m_pDrawGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&envelope);
}
}
