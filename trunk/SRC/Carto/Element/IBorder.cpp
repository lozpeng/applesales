#include "StdAfx.h"
#include "IBorder.h"
#include "SimpleBorder.h"


namespace Element{
IBorder::IBorder(void)
{
	m_fXGap = 0;
	m_fYGap = 0;

	m_pDrawGeometry = NULL;
	m_pGeometry = NULL;
}

IBorder::~IBorder(void)
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

IBorder::IBorder(const GEOMETRY::geom::Geometry& geometry)
{
	m_pGeometry = geometry.clone();
	m_pDrawGeometry = geometry.clone();

	m_fXGap = 0;
	m_fYGap = 0;

	UpdateDrawGeometry();
}

void IBorder::serialization(SYSTEM::IArchive &ar)
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

		double minx, maxx, miny, maxy;

		ar & minx;

		ar & maxx;

		ar & miny;

		ar & maxy;

		m_Envelope.init(minx, maxx, miny, maxy);
	}
	else
	{
		GEOMETRY::io::WKTWriter GeoWriter;
		std::string strGeo= GeoWriter.write(m_pGeometry); 
		ar & strGeo;

		strGeo= GeoWriter.write(m_pDrawGeometry); 
		ar & strGeo;

		double minx, maxx, miny, maxy;
		minx = m_Envelope.getMinX();
		maxx = m_Envelope.getMaxX();
		miny = m_Envelope.getMinY();
		maxy = m_Envelope.getMaxY();

		ar & minx;;

		ar & maxx;

		ar & miny;

		ar & maxy;
	}
}

IBorderPtr IBorder::CreateBorderFromStream(SYSTEM::IArchive &ar)
{
	unsigned long lPos = ar.GetCurrentPos();

	int type;
	ar & type;

	ar.GetCurrentPos() = lPos;

	IBorderPtr pBorder = CreateBorder((Border_Type)type);

	if (pBorder != NULL)
		pBorder->serialization(ar);

	return pBorder;

}

IBorderPtr  IBorder::CreateBorder(Border_Type type)
{
	switch(type)
	{
	case ST_SIMPLE_BORDER:
		return CSimpleBorderPtr(new CSimpleBorder());
	default:
		return NULL;
	}
}

void IBorder::SetGeometry(const GEOMETRY::geom::Geometry& geometry)
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}
	m_pGeometry = geometry.clone();

	UpdateDrawGeometry();
}

const GEOMETRY::geom::Geometry* IBorder::GetGeometry()
{
	return m_pGeometry;
}
const GEOMETRY::geom::Geometry* IBorder::GetDrawGeometry()
{
	return m_pDrawGeometry;
}
void IBorder::SetEnvelope(GEOMETRY::geom::Envelope& envelope)
{
	m_Envelope = envelope;
}

const GEOMETRY::geom::Envelope& IBorder::GetEnvelope()
{
	return m_Envelope;
}

void IBorder::GetGap(float &fXGap, float &fYGap)
{
	fXGap = m_fXGap;
	fYGap = m_fYGap;
}

void IBorder::SetGap(float fXGap, float fYGap)
{
	m_fXGap = fXGap;
	m_fYGap = fYGap;

	if(!m_pGeometry)
		return;

	//目前geos不支持X或Y方向单独变动	
	
	UpdateDrawGeometry();
}



void IBorder::UpdateDrawGeometry()
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
