#include "stdafx.h"
#include "LabelRender.h"
#include "ICursor.h"
#include "IFeatureCursor.h"
#include "Feature.h"
#include "IFeatureClass.h"
//#include "SymbolFactory.h"

namespace Carto
{

CLabelRender::CLabelRender()
{
    m_pSymbol = NULL;
    m_strRenderField = "";
	m_bIsZoom = FALSE;
}

CLabelRender::~CLabelRender()
{

}

void CLabelRender::serialization(SYSTEM::IArchive &ar)
{
	SYSTEM::ISerialization::serialization( ar );
	if( ar.IsRead() )
	{
		//m_pSymbol = Display::CSymbolFactory::CreateSymbolFromStream( ar );		
	}
	else
	{
		m_pSymbol->serialization( ar );
	}

	ar & m_strRenderField;

	ar & m_bIsZoom;
}

void CLabelRender::Draw( Display::IDisplayPtr pDisplay, Geodatabase::ICursorPtr pCursor )
{
	Geodatabase::IFeatureCursorPtr pFeatureCursor = pCursor;
	Geodatabase::IFeatureClass *pFeatureClass = dynamic_cast<Geodatabase::IFeatureClass *>( pFeatureCursor->GetTable() );
	
	if( m_strRenderField == "" 
		|| pDisplay == NULL
		|| pCursor == NULL
		|| m_pSymbol == NULL )
		return;
			
	long lRenderFieldIndex = pFeatureClass->FindField( m_strRenderField.c_str() );
	Geodatabase::CFeaturePtr pFeature;
	
	pDisplay->SetSymbol( m_pSymbol.get() );

	while(!pFeatureCursor->IsEOF())
	{
		pFeature =pFeatureCursor->NextFeature();

		std::string strFldValue = pFeature->GetValue( lRenderFieldIndex ).GetasString();

		GEOMETRY::geom::Geometry *pGeometry = pFeature->GetShape();
		Coordinate centrlord;
		pGeometry->getCentroid( centrlord );

		//label的位置不能覆盖点符号
		if ( pGeometry->getGeometryTypeId() ==  GEOMETRY::geom::GEOS_POINT )
		{
			double foffset;
			pDisplay->GetDisplayTransformation().ConvertDisplayToGeo( 12, foffset );
			centrlord.y = centrlord.y + foffset;
		}

		GEOMETRY::geom::Envelope env( centrlord.x, centrlord.x, centrlord.y, centrlord.y );

		DIS_RECT rect = GetTextSize( pDisplay, m_pSymbol, strFldValue, env );
		pDisplay->GetDisplayTransformation().TransformToGeo( rect, &env );

		pDisplay->SetSymbol( m_pSymbol.get() );
		pDisplay->Begin();
		pDisplay->Draw( &env, strFldValue, m_bIsZoom,  DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP );
		pDisplay->End();
	}
}

std::string CLabelRender::GetRendFieldstr()
{
	return m_strRenderField;
}

void CLabelRender::SetRendFieldstr( std::string strRenderField )  
{
	m_strRenderField = strRenderField;
}

Display::CTextSymbolPtr CLabelRender::GetSymbol()
{
	return m_pSymbol;
}

void CLabelRender::SetSymbol( Display::CTextSymbolPtr pSymbol )
{
	m_pSymbol = pSymbol;
}

DIS_RECT CLabelRender::GetTextSize(Display::IDisplayPtr pDisplay, Display::CTextSymbolPtr pTextSymbol, std::string text, GEOMETRY::geom::Envelope env )
{
	DIS_RECT textSize;

	pDisplay->SetSymbol( pTextSymbol.get() );

	pDisplay->Begin();
	textSize = pDisplay->Draw(&env, text, TRUE, DT_CALCRECT | DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);
	pDisplay->End();

	long loffsetX = textSize.Width() / 2;
	long loffsetY = 0  - (textSize.Height() /2);

	textSize.top += loffsetY;
	textSize.bottom += loffsetY;
	textSize.left += loffsetX;
	textSize.right += loffsetX;
	return textSize;
}

BOOL CLabelRender::GetIsZoom( void )
{
	return m_bIsZoom;
}

void CLabelRender::SetIsZoom( BOOL bIsZoom )
{
	m_bIsZoom = bIsZoom;
}

std::string CLabelRender::GetRendFieldsStr()
{
	return m_strRenderField;
}

}
