#ifndef _SYSTEM_UNIT_CONVERTER_H
#define _SYSTEM_UNIT_CONVERTER_H

#include <string>

namespace SYSTEM
{

	enum SYS_UNIT_TYPE
	{
		SYS_UNIT_PIXEL,			//屏幕像素
		SYS_UNIT_MILLIMETER,	//毫米
		SYS_UNIT_CENTIMETER,	//厘米
		SYS_UNIT_DECIMETER,		//分米
		SYS_UNIT_METER,			//米		
		SYS_UNIT_KILOMETER,		//公里
		SYS_UNIT_POINT,			//磅1/72英寸
		SYS_UNIT_INCH,			//英寸
		SYS_UNIT_FEET,			//英尺
		SYS_UNIT_YARD,			//码
		SYS_UNIT_MILE,			//英里
		SYS_UNIT_NAUTICALMILE,	//海里
		SYS_UNIT_RADIAN,		//弧度
		SYS_UNIT_DEGREE,		//度
		SYS_UNIT_UNKNOWN		//未知单位
	};

class SYSTEM_DLL UnitConverter
{
public:
	UnitConverter();
	~UnitConverter() ;

	static double ConvertUnits(double inVal, SYS_UNIT_TYPE inUnit, SYS_UNIT_TYPE outUnit);
	static std::string GetUnitLabelEN(SYS_UNIT_TYPE unit);
	static std::string GetBriefUnitLabel(SYS_UNIT_TYPE unit);
	static std::string GetUnitLabelCHS(SYS_UNIT_TYPE unit);
	static SYS_UNIT_TYPE GetUnitByString(std::string untiLabel);
};

}
#endif
