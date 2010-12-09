#include "StdAfx.h"
#include "MapTitle.h"
#include "TextSymbol.h"
#include "EnvelopeTracker.h"

namespace Element{
CMapTitle::CMapTitle()
{
	m_enumElementType = ET_MAP_TITLE;

	m_pSelectionHandle.reset(new CEnvelopeTracker(GEOMETRY::geom::Envelope(0,0,0,0), HT_NONE));

	m_bCanSetWHRMode = FALSE;

}

CMapTitle::CMapTitle(const GEOMETRY::geom::Geometry& geometry, CMapFrame* pMapFrame)
			:IMapSurround(geometry, pMapFrame)
{
	m_enumElementType = ET_MAP_TITLE;

	m_strTitle = "地图名";
	Display::CTextSymbol* pSymbol = new Display::CTextSymbol;
	pSymbol->SetTextSize(28);
	m_pSymbol.reset(pSymbol);
	m_pSelectionHandle.reset(new CEnvelopeTracker(GetEnvelope(), HT_NONE));

	m_bCanSetWHRMode = FALSE;

	m_coordOrg.x = geometry.getEnvelopeInternal()->getMinX();
	m_coordOrg.y = geometry.getEnvelopeInternal()->getMinY();


}

CMapTitle::~CMapTitle(void)
{
}

void CMapTitle::serialization(SYSTEM::IArchive &ar)
{
	IMapSurround::serialization( ar );

	ar & m_strTitle;

	ar & m_coordOrg.x;

	ar & m_coordOrg.y;
}

void CMapTitle::Move(double dx, double dy)
{
	if(!m_pGeometry)
		return;

	m_pGeometry->Move(dx,dy);

	m_coordOrg.x += dx;
	m_coordOrg.y += dy;

	IFrameElementBase::GeometryChangedEvents();
}

void CMapTitle::DrawNormal(Display::IDisplayPtr pDisplay)
{
	//计算envelope，并更新geometry
	DIS_RECT textSize;
	GEOMETRY::geom::Envelope env(m_coordOrg.x,m_coordOrg.x,m_coordOrg.y,m_coordOrg.y);
	pDisplay->SetSymbol(m_pSymbol.get());
	pDisplay->Begin();
	textSize = pDisplay->Draw(&env, m_strTitle, TRUE);
	pDisplay->End();

	GEOMETRY::geom::Envelope envelope;
	pDisplay->GetDisplayTransformation().TransformToGeo(textSize, &envelope);

	if(m_pGeometry)
	{
		GEOMETRY::geom::GeometryFactory::getDefaultInstance()->destroyGeometry(m_pGeometry);
		m_pGeometry = NULL;
	}
	m_pGeometry = GEOMETRY::geom::GeometryFactory::getDefaultInstance()->toGeometry(&envelope);

	IFrameElementBase::GeometryChangedEvents();

	//绘制
	DrawBackground(pDisplay);

	pDisplay->SetSymbol(m_pSymbol.get());
	pDisplay->Begin();
	textSize = pDisplay->Draw(&env, m_strTitle, TRUE);
	pDisplay->End();

	DrawForeground(pDisplay);
}

void CMapTitle::ChangeGeometryEnvelopTo(GEOMETRY::geom::Envelope& newEnvelope)
{
	GEOMETRY::geom::Envelope oldEnv = *m_pGeometry->getEnvelopeInternal();
	double scaleX, scaleY;
	scaleX = newEnvelope.getWidth()/oldEnv.getWidth();
	scaleY = newEnvelope.getHeight()/oldEnv.getHeight();

	m_coordOrg.x = newEnvelope.getMinX() + (m_coordOrg.x - oldEnv.getMinX())*scaleX;
	m_coordOrg.y = newEnvelope.getMinY() + (m_coordOrg.y - oldEnv.getMinY())*scaleY;

	Display::CTextSymbol* pTextSym = dynamic_cast<Display::CTextSymbol*>(m_pSymbol.get());
	pTextSym->SetTextSize(pTextSym->GetTextSize()*scaleY);

	IElement::ChangeGeometryEnvelopTo(newEnvelope);
}
}
