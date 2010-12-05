#ifndef _SYSTEM_UNIT_CONVERTER_H
#define _SYSTEM_UNIT_CONVERTER_H

#include <string>

namespace SYSTEM
{

	enum SYS_UNIT_TYPE
	{
		SYS_UNIT_PIXEL,			//��Ļ����
		SYS_UNIT_MILLIMETER,	//����
		SYS_UNIT_CENTIMETER,	//����
		SYS_UNIT_DECIMETER,		//����
		SYS_UNIT_METER,			//��		
		SYS_UNIT_KILOMETER,		//����
		SYS_UNIT_POINT,			//��1/72Ӣ��
		SYS_UNIT_INCH,			//Ӣ��
		SYS_UNIT_FEET,			//Ӣ��
		SYS_UNIT_YARD,			//��
		SYS_UNIT_MILE,			//Ӣ��
		SYS_UNIT_NAUTICALMILE,	//����
		SYS_UNIT_RADIAN,		//����
		SYS_UNIT_DEGREE,		//��
		SYS_UNIT_UNKNOWN		//δ֪��λ
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
