#include "StdAfx.h"
#include "IGraphicElement.h"

namespace Element{


IGraphicElement::IGraphicElement(void)
{

}
IGraphicElement::IGraphicElement(const GEOMETRY::geom::Geometry& geometry):IElement(geometry)
{
}

IGraphicElement::~IGraphicElement(void)
{
}

//Ҫɾ��
void IGraphicElement::DrawDraftMode( Display::IDisplayPtr pDisplay , bool bPrint)
{

}
}
