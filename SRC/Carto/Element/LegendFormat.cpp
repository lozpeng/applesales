#include "StdAfx.h"
#include "LegendFormat.h"

namespace Element{
CLegendFormat::CLegendFormat(void)
{
}

CLegendFormat::~CLegendFormat(void)
{
}

void CLegendFormat::serialization(SYSTEM::IArchive &ar)
{
	SYSTEM::ISerialization::serialization( ar );
}
}