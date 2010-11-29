#include "stdafx.h"
#include "IRender.h"
#include "ICursor.h"
//#include "SimpleRender.h"
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

	if (i == CUSTOMRENDER)
	{
		ar & renderName;
	}

	IRenderPtr pRender = CreateRender( (RENDER_TYPE)i , renderName);

	ar.GetCurrentPos() = startpos; 

	if (pRender != NULL)
		pRender->serialization( ar );

	return pRender;

}

SYSTEM::CSmartPtr<IRender>  IRender::CreateRender( RENDER_TYPE type , std::string RenderName )
{
	//switch(type)
	//{
	//case OT_SIMPLERENDER:
	//	return IRenderPtr( new CSimpleRender() );
	//case OT_UNIQUERENDER: 
	//	return IRenderPtr( new CUniqueRender() );
	//case OT_RANGERENDER:
	//	return IRenderPtr( new CRangeRender() );
	//case OT_MIXSIMPLERENDER:
	//case OT_TRIANGLERENDER:
	//case OT_CUSTOMRENDER:
	//	return NULL;
	//default:
		return NULL;
	//}
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

/////////////////////////////////////////////////////////////////////////////////
// IExtRender

const std::string& Carto::IExtRender::GetExtRenderName()
{
	return m_extRenderName;
}

const std::string& Carto::IExtRender::GetExtRenderDescription()
{
	return m_extRenderDescription;
}

void Carto::IExtRender::SetProperties( const char* PropertyName , const _variant_t& PropertyValue)
{

}
_variant_t Carto::IExtRender::GetProperties(const char* PropertyName)
{
	return NULL;
}

Carto::IRenderPtr Carto::IExtRender::CopyNewRender()
{
	Carto::IExtRenderPtr pRend;
	SYSTEM::CBinArchive ar;

	serialization( ar );
	ar.SetReadState();
	ar.SetPosToBegin();
	pRend = CreateRenderFromStream( ar );

	return pRend;
}

void Carto::IExtRender::serialization(SYSTEM::IArchive &ar)
{
	Carto::IRender::serialization(ar);

	ar & m_extRenderName;
	ar & m_extRenderDescription;
	ar & m_pageName;
}

Carto::IExtRender::IExtRender()
{
	m_type = CUSTOMRENDER;
}

Display::ISymbolPtr Carto::IExtRender::CreateSymbolFromInSideSymbolName()
{
	return NULL;
}

void Carto::IExtRender::SetPageName(std::string pageName)
{
	m_pageName = pageName;
}

std::string Carto::IExtRender::GetPageName()
{
	return m_pageName;
}
}