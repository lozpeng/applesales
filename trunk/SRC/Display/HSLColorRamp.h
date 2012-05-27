#ifndef _HSLCOLORRAMP_H_
#define _HSLCOLORRAMP_H_
#include "IColorRamp.h"

namespace Display
{

class DISPLAY_DLL HSLColorRamp:public IColorRamp
{
public:
	HSLColorRamp();
	virtual ~HSLColorRamp();
public:


	virtual RGBColor GetColor(int index);
    

	void setStartColor(HSLColor color){m_startColor=color;}

	HSLColor getStartColor() const{return m_startColor;}

	void setEndColor(HSLColor color){m_endColor=color;}

	HSLColor getEndColor() const{return m_endColor;}


private:

	HSLColor m_startColor;
	HSLColor m_endColor;

};

typedef SYSTEM::CSmartPtr<HSLColorRamp> HSLColorRampPtr;

}

#endif