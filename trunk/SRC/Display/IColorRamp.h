#ifndef _ICOLORRAMP_H_
#define _ICOLORRAMP_H_
#include "ColorDefine.h"
#include "SmartPtr.h"
namespace Display
{

class DISPLAY_DLL IColorRamp
{
public:
	IColorRamp();
	virtual ~IColorRamp();
public:

	virtual RGBColor GetColor(int index)=0;

	int getSize() const {return m_size;}

	void setSize(int size){m_size=size;}
private:
	//ÑÕÉ«ÊýÄ¿
	int m_size;

};

typedef SYSTEM::CSmartPtr<IColorRamp> IColorRampPtr;

}

#endif