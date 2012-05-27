#include "StdAfx.h"
#include "HSLColorRamp.h"

namespace Display
{

HSLColorRamp::HSLColorRamp()
{

}

HSLColorRamp::~HSLColorRamp()
{

}

RGBColor HSLColorRamp::GetColor(int index)
{
	int nSize=getSize();
	if(index<0 || index>nSize)
	{
		return RGBColor();
	}
	double seg=(m_endColor.Light-m_startColor.Light)/((double)nSize);

	RGBColor rgbcolor;
	HSLColor hslcolor=m_startColor;
	hslcolor.Light+=(int)seg*index;
	hslcolor.toRGBColor(&rgbcolor);
	return rgbcolor;





}







}
