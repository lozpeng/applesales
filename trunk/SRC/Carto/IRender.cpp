#include "stdafx.h"
#include "IRender.h"
#include "ICursor.h"
#include "SimpleRender.h"
//#include "UniqueRender.h"
//#include "RangeRender.h"

namespace Carto
{

IRender::IRender()
{
	m_HighLightColor = RGB(255,0,0);
}

IRender::~IRender() 
{

}

SYSTEM::CSmartPtr<IRender> IRender::CopyNewRender()
{
	Carto::IRenderPtr pRend;
	SYSTEM::CBinArchive ar;

	serialization( ar );
	ar.SetReadState();
	ar.SetPosToBegin();
	pRend = CreateRenderFromStream( ar );

	return pRend;
}


Carto::RENDER_TYPE Carto::IRender::GetRenderType()
{		  
return m_type;
}

void IRender::serialization(SYSTEM::IArchive &ar)
{
	SYSTEM::ISerialization::serialization( ar );

	if(ar.IsRead() )
	{
		int i;
		ar & i;
		//ASSERT( m_type == (Carto::RENDER_TYPE)i );
		m_type == (Carto::RENDER_TYPE)i ;
	}
	else
	{
		int i = m_type;
		ar & (i);
	}
}

void IRender::HighLightDraw(Display::IDisplayPtr pDisplay,  Geodatabase::ICursorPtr pCursor )
{

}

void IRender::HighLightDraw(Display::IDisplayPtr pDisplay, Geodatabase::ISelctionSet* pSelections)
{

}

void IRender::SetHighLightSymbol(Display::ISymbolPtr pSymbol)
{
	m_pHighLightSymbol =pSymbol;
}

SYSTEM::CSmartPtr<IRender>  IRender::CreateRenderFromStream(SYSTEM::IArchive &ar)
{
	int startpos = ar.GetCurrentPos();
	int i;
	ar & i;
	std::string renderName = "";

	IRenderPtr pRender = CreateRender( (RENDER_TYPE)i , renderName);

	ar.GetCurrentPos() = startpos; 

	if (pRender != NULL)
		pRender->serialization( ar );

	return pRender;

}

SYSTEM::CSmartPtr<IRender>  IRender::CreateRender( RENDER_TYPE type , std::string RenderName )
{
	switch(type)
	{
	case SIMPLERENDER:
		return IRenderPtr( new CSimpleRender() );
	case UNIQUERENDER: 
		//return IRenderPtr( new CUniqueRender() );
	case RANGERENDER:
		//return IRenderPtr( new CRangeRender() );
	case MIXSIMPLERENDER:
	case TRIANGLERENDER:
		return NULL;
	default:
		return NULL;
	}
}

void Carto::IRender::SetRenderFeatureType(long type)
{
	m_lFeaturetype = type;
}

long Carto::IRender::GetRenderFeatureType()
{
	return m_lFeaturetype;
}

COLORREF Carto::IRender::GetHighLightColor()
{
	return m_HighLightColor;
}

void IRender::SetHighLightColor(COLORREF color)
{
	m_HighLightColor = color;
}

Carto::CLegendInfoPtr IRender::GetLegendInfo()
{
	return NULL;
}


}