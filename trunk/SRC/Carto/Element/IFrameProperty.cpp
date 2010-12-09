#include "StdAfx.h"
#include "IFrameProperty.h"
#include "SimpleBackground.h"
#include "SimpleBorder.h"
#include "SimpleShadow.h"
namespace Element{

IFrameProperty::IFrameProperty()
{
	m_pBackground = NULL;
	m_pBorder = NULL;
	m_pShadow = NULL;
}

IFrameProperty::IFrameProperty(const GEOMETRY::geom::Geometry& geometry)
{
	m_pBackground.reset(new CSimpleBackground(geometry));

	m_pBorder.reset(new CSimpleBorder(geometry));

	m_pShadow.reset(new CSimpleShadow(geometry));
}

IFrameProperty::~IFrameProperty(void)
{
}
//////////////////////////////////////////////////////////////////////////
void IFrameProperty::serialization(SYSTEM::IArchive &ar)
{
	SYSTEM::ISerialization::serialization( ar );

	if(ar.IsRead())
	{
		m_pBackground.reset(new CSimpleBackground);
		m_pBackground->serialization(ar);

		m_pBorder.reset(new CSimpleBorder);
		m_pBorder->serialization(ar);

		m_pShadow.reset(new CSimpleShadow);
		m_pShadow->serialization(ar);
	}
	else
	{
		m_pBackground->serialization(ar);

		m_pBorder->serialization(ar);

		m_pShadow->serialization(ar);
	}
	
}

CSimpleBackgroundPtr IFrameProperty::GetBackground()
{
	return m_pBackground;
}
void IFrameProperty::SetBackground(CSimpleBackgroundPtr pBackground)
{
	m_pBackground = pBackground;
}
CSimpleBorderPtr IFrameProperty::GetBorder()
{
	return m_pBorder;
}
void IFrameProperty::SetBorder(CSimpleBorderPtr pBorder)
{
	m_pBorder = pBorder;
}

CSimpleShadowPtr IFrameProperty::GetShadow()
{
	return m_pShadow;
}
void IFrameProperty::SetShadow(CSimpleShadowPtr pShadow)
{
	m_pShadow= pShadow;
}
}