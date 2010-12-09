#include "StdAfx.h"
#include "CalloutTextElement.h"
#include "CalloutTracker.h"
namespace Element{

CCalloutTextElement::CCalloutTextElement():ITextElement()
{
	m_enumElementType = ET_CALLOUT_TEXT_ELEMENT;

	m_pGeometry = NULL;

	m_bDrawBg = TRUE;

	m_pFillSymbol->SetFillColor(RGB(255,255,210));
	m_pFillSymbol->SetOutLineColor(RGB(0,0,0));
	
	m_pSelectionHandle.reset(new CCalloutTracker);
}

CCalloutTextElement::CCalloutTextElement(GEOMETRY::geom::Envelope& env): ITextElement()
{
	m_enumElementType = ET_CALLOUT_TEXT_ELEMENT;

	m_pGeometry = NULL;

	m_bDrawBg = TRUE;

	m_TextEnv = env;
	env.centre(m_Point);

	m_coordOrg.x = env.getMinX();
	m_coordOrg.y = env.getMinY();

	m_pFillSymbol->SetFillColor(RGB(255,255,210));
	m_pFillSymbol->SetOutLineColor(RGB(0,0,0));

	m_pSelectionHandle.reset(new CCalloutTracker);
}

CCalloutTextElement::~CCalloutTextElement(void)
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}
}

void CCalloutTextElement::serialization(SYSTEM::IArchive &ar)
{
	ITextElement::serialization(ar);
	if(ar.IsRead())
	{
		double minx, maxx, miny, maxy;
		ar & minx;
		ar & maxx;
		ar & miny;
		ar & maxy;
		m_TextEnv.init(minx, maxx, miny, maxy);

		double x, y;
		ar & x;
		ar & y;
		m_Point.x = x;
		m_Point.y = y;
	}
	else
	{
		double minx, maxx, miny, maxy;
		minx = m_TextEnv.getMinX();
		maxx = m_TextEnv.getMaxX();
		miny = m_TextEnv.getMinY();
		maxy = m_TextEnv.getMaxY();

		ar & minx;
		ar & maxx;
		ar & miny;
		ar & maxy;

		double x, y;
		x = m_Point.x;
		y = m_Point.y;
		ar & x;
		ar & y;
		
	}
}



void CCalloutTextElement::DrawNormal(Display::IDisplayPtr pDisplay)
{
	UpdateGeometry(pDisplay);

	if(!m_pGeometry)
		return;

	//绘制背景
	if(m_bDrawBg)
	{
		pDisplay->SetSymbol( m_pFillSymbol.get() );

		pDisplay->Begin();

		pDisplay->Draw( m_pGeometry );

		pDisplay->End();
	}
	
	//绘制文字
	GEOMETRY::geom::Envelope env(m_coordOrg.x,m_coordOrg.x,m_coordOrg.y,m_coordOrg.y);

	pDisplay->SetSymbol( m_pSymbol.get() );
	pDisplay->Begin();
	pDisplay->Draw( &env, m_text , m_bScaleWithMap);
	pDisplay->End();
}

GEOMETRY::geom::Geometry* CCalloutTextElement::GetGeometry()
{
	return m_pGeometry;
}

void CCalloutTextElement::SetGeometry(GEOMETRY::geom::Geometry* pGeometry)
{
	m_pGeometry = pGeometry;
}

void CCalloutTextElement::GeometryChangedEvents()
{
	m_pSelectionHandle->SetGeometry(*m_pGeometry);

	CCalloutTracker* tracker = dynamic_cast<CCalloutTracker*>(m_pSelectionHandle.get());
	tracker->SetHandle(m_Point);
}

void CCalloutTextElement::Move(double x, double y)
{
	m_TextEnv.init(m_TextEnv.getMinX()+x, m_TextEnv.getMaxX()+x, m_TextEnv.getMinY()+y, m_TextEnv.getMaxY()+y);

	m_coordOrg.x += x;
	m_coordOrg.y += y;

	UnionPointAndRect();

	CCalloutTextElement::GeometryChangedEvents();
}

void CCalloutTextElement::MoveHandleTo(HIT_HANDLE nHandle,GEOMETRY::geom::Coordinate coord)
{
	if(!m_pSelectionHandle)
		return;

	m_pSelectionHandle->MoveHandleTo(nHandle, coord);

	m_Point = coord;
}

void CCalloutTextElement::MovePoint(double x, double y)
{
	m_Point.x = m_Point.x + x;
	m_Point.y = m_Point.x + y;

	UnionPointAndRect();

	CCalloutTextElement::GeometryChangedEvents();
}

void CCalloutTextElement::UpdateGeometry(Display::IDisplayPtr pDisplay)
{
	UpdateTextEnv(pDisplay);

	UnionPointAndRect();

	CCalloutTextElement::GeometryChangedEvents();
}

void CCalloutTextElement::UpdateTextEnv(Display::IDisplayPtr pDisplay)
{
	DIS_RECT textRect;
	GEOMETRY::geom::Envelope env(m_coordOrg.x,m_coordOrg.x,m_coordOrg.y,m_coordOrg.y);

	//计算title大小
	pDisplay->SetSymbol(m_pSymbol.get());
	pDisplay->Begin();
	textRect = pDisplay->Draw(&env, m_text, m_bScaleWithMap, DT_CALCRECT | DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_BOTTOM);
	pDisplay->End();

	pDisplay->GetDisplayTransformation().TransformToGeo(textRect, &env);

	m_TextEnv = env;
}

void CCalloutTextElement::UnionPointAndRect()
{
	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}

	double expX, expY;
	GEOMETRY::geom::Envelope env;
	expX = m_TextEnv.getWidth()/3;
	expY = m_TextEnv.getHeight()/3;
	env = m_TextEnv;
	env.expandBy(expX, expY);

	if(env.covers(m_Point))
	{
		m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&env);
	}
	else
	{
		/*
				-------------------------------------
                        |         |         |
                   B    |    C    |    D    |   E
				        |         |         |
		                ---------------------
						|                   |
				--------         TEXT        --------		
						|                   |
						---------------------
                        |         |         |
                   A    |    H    |    G    |   F
				        |         |         |
			   --------------------------------------
		*/

		GEOMETRY::geom::Coordinate center;
		env.centre(center);

		double spaceY = env.getHeight()/6;
		double spaceX = env.getWidth()/6;

		GEOMETRY::geom::CoordinateSequence* pCoords = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->getCoordinateSequenceFactory()->create(NULL);

		if(m_Point.x <= env.getMinX() && m_Point.y <= center.y)//A
		{
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY() + spaceY));
			pCoords->add(m_Point);
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),center.y - spaceY));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));		
		}
		else if(m_Point.x <= env.getMinX() && m_Point.y > center.y)//B
		{
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),center.y + spaceY));
			pCoords->add(m_Point);
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMaxY() - spaceY));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));		
		}		
		else if(m_Point.x > env.getMinX() && m_Point.x <= center.x && m_Point.y > env.getMaxY())//C
		{
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX()+spaceX,env.getMaxY()));
			pCoords->add(m_Point);	
			pCoords->add(GEOMETRY::geom::Coordinate(center.x -spaceX ,env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));
		}
		else if(m_Point.x <= env.getMaxX() && m_Point.x > center.x && m_Point.y > env.getMaxY())//D
		{
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(center.x+spaceX,env.getMaxY()));
			pCoords->add(m_Point);	
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX() -spaceX ,env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));
		}
		else if(m_Point.x > env.getMaxX() && m_Point.y > center.y)//E
		{
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMaxY() - spaceY));
			pCoords->add(m_Point);	
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX() ,center.y + spaceY));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));
		}
		else if(m_Point.x > env.getMaxX() && m_Point.y <= center.y)//F
		{
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),center.y - spaceY));
			pCoords->add(m_Point);	
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX() ,env.getMinY() + spaceY));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));
		}
		else if(m_Point.x <= env.getMaxX() && m_Point.x > center.x && m_Point.y <= env.getMinY())//G
		{
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX()-spaceX,env.getMinY()));
			pCoords->add(m_Point);	
			pCoords->add(GEOMETRY::geom::Coordinate(center.x+spaceX,env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));
		}
		else if(m_Point.x > env.getMinX() && m_Point.x <= center.x && m_Point.y <= env.getMinY())//H
		{
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMaxY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMaxX(),env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(center.x-spaceX,env.getMinY()));
			pCoords->add(m_Point);	
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX()+spaceX,env.getMinY()));
			pCoords->add(GEOMETRY::geom::Coordinate(env.getMinX(),env.getMinY()));
		}

		GEOMETRY::geom::LinearRing* pRing = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createLinearRing(*pCoords);
		m_pGeometry = 	GEOMETRY::geom::GeometryFactory::getDefaultInstance()->createPolygon(pRing, NULL);
}
}

}
