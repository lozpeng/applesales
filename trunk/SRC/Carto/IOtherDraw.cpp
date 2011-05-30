#include "stdafx.h"
#include "IOtherdDraw.h"

namespace Carto
{


IOtherDraw::IOtherDraw()
{

}

IOtherDraw::~IOtherDraw()
{

}

std::string IOtherDraw::GetName()
{
	return m_name;
}

void IOtherDraw::SetName(const char *strName)
{
	m_name =strName;
}

}