#ifndef _RasterRGBRender_H_
#define _RasterRGBRender_H_
#pragma once
#include "irasterrender.h"
namespace Carto
{
	class CRasterRGBRender : public IRasterRender
	{
	public:
		CRasterRGBRender(void);
		~CRasterRGBRender(void);
	};
}
#endif //_RasterRGBRender_H_
