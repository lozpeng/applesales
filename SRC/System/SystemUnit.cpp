#include "StdAfx.h"
#include "SystemUnit.h"

namespace SYSTEM
{

static double CalcUnitConvertRate( SYS_UNIT_TYPE inUnit, SYS_UNIT_TYPE outUnit);
static double GetRatePointToOther(SYS_UNIT_TYPE outUnit);
static double GetRateMeterToOther(SYS_UNIT_TYPE outUnit);
static double GetRateInchToOther(SYS_UNIT_TYPE outUnit);
static double GetRateFeetToOther(SYS_UNIT_TYPE outUnit);
static double GetRateYardToOther(SYS_UNIT_TYPE outUnit);
static double GetRateMileToOther(SYS_UNIT_TYPE outUnit);
static double GetRateNauticalMileToOther(SYS_UNIT_TYPE outUnit);
static double GetRateRadianToOther(SYS_UNIT_TYPE outUnit);
static double GetRateDegreeToOther(SYS_UNIT_TYPE outUnit);


UnitConverter::UnitConverter(void)
{
}

UnitConverter::~UnitConverter(void)
{
}

double UnitConverter::ConvertUnits(double inVal, SYS_UNIT_TYPE inUnit, SYS_UNIT_TYPE outUnit)
{
	if(inUnit == outUnit || inUnit == SYS_UNIT_UNKNOWN)
		return inVal;
	else
		return inVal*CalcUnitConvertRate(inUnit, outUnit);
}

std::string UnitConverter::GetUnitLabelEN(SYS_UNIT_TYPE unit)
{
	switch(unit)
	{
	case SYS_UNIT_POINT:
		return "Points";
	case SYS_UNIT_MILLIMETER:
		return "Millimeters";
	case SYS_UNIT_CENTIMETER:
		return "Centimeters";
	case SYS_UNIT_DECIMETER:
		return "Decimeters";
	case SYS_UNIT_METER:
		return "Metres";
	case SYS_UNIT_KILOMETER:
		return "Kilometers";
	case SYS_UNIT_INCH:
		return "Inches";
	case SYS_UNIT_FEET:
		return "Feet";
	case SYS_UNIT_YARD:
		return "Yards";
	case SYS_UNIT_MILE:
		return "Miles";
	case SYS_UNIT_NAUTICALMILE:
		return "Nautical Miles";
	case SYS_UNIT_RADIAN:
		return "Radian";
	case SYS_UNIT_DEGREE:
		return "Degrees";
	case SYS_UNIT_UNKNOWN:
		return "未知单位";
	default:
		return "";
	}
}

std::string UnitConverter::GetUnitLabelCHS(SYS_UNIT_TYPE unit)
{
	switch(unit)
	{
	case SYS_UNIT_POINT:
		return "磅";
	case SYS_UNIT_MILLIMETER:
		return "毫米";
	case SYS_UNIT_CENTIMETER:
		return "厘米";
	case SYS_UNIT_DECIMETER:
		return "分米";
	case SYS_UNIT_METER:
		return "米";
	case SYS_UNIT_KILOMETER:
		return "千米";
	case SYS_UNIT_INCH:
		return "英尺";
	case SYS_UNIT_FEET:
		return "英寸";
	case SYS_UNIT_YARD:
		return "码";
	case SYS_UNIT_MILE:
		return "英里";
	case SYS_UNIT_NAUTICALMILE:
		return "海里";
	case SYS_UNIT_RADIAN:
		return "弧度";
	case SYS_UNIT_DEGREE:
		return "度";
	case SYS_UNIT_UNKNOWN:
		return "未知单位";
	default:
		return "";
	}
}

std::string UnitConverter::GetBriefUnitLabel(SYS_UNIT_TYPE unit)
{
	switch(unit)
	{
	case SYS_UNIT_POINT:
		return "pt";
	case SYS_UNIT_MILLIMETER:
		return "mm";
	case SYS_UNIT_CENTIMETER:
		return "cm";
	case SYS_UNIT_DECIMETER:
		return "dm";
	case SYS_UNIT_METER:
		return "m";
	case SYS_UNIT_KILOMETER:
		return "km";
	case SYS_UNIT_INCH:
		return "in";
	case SYS_UNIT_FEET:
		return "feet";
	case SYS_UNIT_YARD:
		return "yd";
	case SYS_UNIT_MILE:
		return "mi";
	case SYS_UNIT_NAUTICALMILE:
		return "nm";
	case SYS_UNIT_RADIAN:
		return "rad";
	case SYS_UNIT_DEGREE:
		return "°";
	case SYS_UNIT_UNKNOWN:
		return "未知单位";
	default:
		return "";
	}
}

SYS_UNIT_TYPE UnitConverter::GetUnitByString(std::string untiLabel)
{
	if(untiLabel.compare("Meter") == 0 || untiLabel.compare("metre") == 0)
		return SYS_UNIT_METER;
	else if(untiLabel.compare("Degree") == 0 || untiLabel.compare("degree") == 0)
		return SYS_UNIT_DEGREE;
	else
		return SYS_UNIT_UNKNOWN;
}

//////////////////////////////////////////////////////////////////////////
static double CalcUnitConvertRate( SYS_UNIT_TYPE inUnit, SYS_UNIT_TYPE outUnit)
{
	switch(inUnit)
	{
	case SYS_UNIT_POINT:
		{
			return GetRatePointToOther(outUnit);
		}
	case SYS_UNIT_MILLIMETER:
		{
			return 0.001*GetRateMeterToOther(outUnit);
		}
		break;
	case SYS_UNIT_CENTIMETER:
		{
			return 0.01*GetRateMeterToOther(outUnit);
		}
		break;
	case SYS_UNIT_DECIMETER:
		return 0.1*GetRateMeterToOther(outUnit);;
	case SYS_UNIT_METER:
		return GetRateMeterToOther(outUnit);
	case SYS_UNIT_KILOMETER:
		return 1000*GetRateMeterToOther(outUnit);
	case SYS_UNIT_INCH:
		return GetRateInchToOther(outUnit);
	case SYS_UNIT_FEET:
		return GetRateFeetToOther(outUnit);
	case SYS_UNIT_YARD:
		return GetRateYardToOther(outUnit);
	case SYS_UNIT_MILE:
		return GetRateMileToOther(outUnit);
	case SYS_UNIT_NAUTICALMILE:
		return GetRateNauticalMileToOther(outUnit);
	case SYS_UNIT_RADIAN:
		return GetRateRadianToOther(outUnit);
	case SYS_UNIT_DEGREE:
		return GetRateDegreeToOther(outUnit);
	case SYS_UNIT_UNKNOWN:
		return GetRateMeterToOther(outUnit);;
	default:
		return 1;
	}
}


static double GetRateMeterToOther(SYS_UNIT_TYPE outUnit)
{
	switch(outUnit)
	{
	case SYS_UNIT_POINT:
		return 2834.64576;
	case SYS_UNIT_MILLIMETER:
		return 1000;
	case SYS_UNIT_CENTIMETER:
		return 100;
	case SYS_UNIT_DECIMETER:
		return 10;
	case SYS_UNIT_METER:
		return 1;
	case SYS_UNIT_KILOMETER:
		return 0.001;
	case SYS_UNIT_INCH:
		return 39.37008;
	case SYS_UNIT_FEET:
		return 3.28084;
	case SYS_UNIT_YARD:
		return 1.09361;
	case SYS_UNIT_MILE:
		return 0.00062;
	case SYS_UNIT_NAUTICALMILE:
		return 0.00054;
	case SYS_UNIT_RADIAN:
		return 1/GetRateRadianToOther(SYS_UNIT_METER);
	case SYS_UNIT_DEGREE:
		return 1/GetRateDegreeToOther(SYS_UNIT_METER); 
	case SYS_UNIT_UNKNOWN:
		return 1;
	default:
		return 1;
	}
}
static double GetRateInchToOther(SYS_UNIT_TYPE outUnit)
{
	switch(outUnit)
	{
	
	case SYS_UNIT_MILLIMETER:
		return 25.4;
	case SYS_UNIT_CENTIMETER:
		return 2.54;
	case SYS_UNIT_DECIMETER:
		return 0.254;
	case SYS_UNIT_UNKNOWN: 
	case SYS_UNIT_METER:
		return 0.0254;
	case SYS_UNIT_KILOMETER:
		return 0.0000254;
	case SYS_UNIT_POINT:
		return 72;
	case SYS_UNIT_INCH:
		return 1;
	case SYS_UNIT_FEET:
		return 0.0833333;
	case SYS_UNIT_YARD:
		return 0.0277778;
	case SYS_UNIT_MILE:
		return 0.0000158;
	case SYS_UNIT_NAUTICALMILE:
		return 0.0000137;
	case SYS_UNIT_RADIAN:
		return 0.0254/GetRateRadianToOther(SYS_UNIT_METER);
	case SYS_UNIT_DEGREE:
		return 0.0254/GetRateDegreeToOther(SYS_UNIT_METER); 
	default:
		return 1;
	}
}
static double GetRateFeetToOther(SYS_UNIT_TYPE outUnit)
{
	switch(outUnit)
	{
	case SYS_UNIT_MILLIMETER:
		return 304.8;
	case SYS_UNIT_CENTIMETER:
		return 30.48;
	case SYS_UNIT_DECIMETER:
		return 3.048;
	case SYS_UNIT_UNKNOWN: 
	case SYS_UNIT_METER:
		return 0.3048;
	case SYS_UNIT_KILOMETER:
		return 0.0003048;
	case SYS_UNIT_POINT:
		return 864;
	case SYS_UNIT_INCH:
		return 12;
	case SYS_UNIT_FEET:
		return 1;
	case SYS_UNIT_YARD:
		return 0.3333333;
	case SYS_UNIT_MILE:
		return 0.0001894;
	case SYS_UNIT_NAUTICALMILE:
		return 0.0001646;
	case SYS_UNIT_RADIAN:
		return 0.3048/GetRateRadianToOther(SYS_UNIT_METER);
	case SYS_UNIT_DEGREE:
		return 0.3048/GetRateDegreeToOther(SYS_UNIT_METER); 
	default:
		return 1;
	}
}

static double GetRateYardToOther(SYS_UNIT_TYPE outUnit)
{
	switch(outUnit)
	{
	case SYS_UNIT_MILLIMETER:
		return 914.4;
	case SYS_UNIT_CENTIMETER:
		return 91.44;
	case SYS_UNIT_DECIMETER:
		return 9.144;
	case SYS_UNIT_UNKNOWN: 
	case SYS_UNIT_METER:
		return 0.9144;
	case SYS_UNIT_KILOMETER:
		return 0.0009144;
	case SYS_UNIT_POINT:
		return 2592;
	case SYS_UNIT_INCH:
		return 36;
	case SYS_UNIT_FEET:
		return 3;
	case SYS_UNIT_YARD:
		return 1;
	case SYS_UNIT_MILE:
		return 0.0005682;
	case SYS_UNIT_NAUTICALMILE:
		return 0.0004937;
	case SYS_UNIT_RADIAN:
		return 0.9144/GetRateRadianToOther(SYS_UNIT_METER);
	case SYS_UNIT_DEGREE:
		return 0.9144/GetRateDegreeToOther(SYS_UNIT_METER); 
	default:
		return 1;
	}
}

static double GetRateMileToOther(SYS_UNIT_TYPE outUnit)
{
	switch(outUnit)
	{
	case SYS_UNIT_MILLIMETER:
		return 1609344;
	case SYS_UNIT_CENTIMETER:
		return 160934.4;
	case SYS_UNIT_DECIMETER:
		return 16093.44;
	case SYS_UNIT_UNKNOWN: 
	case SYS_UNIT_METER:
		return 1609.344;
	case SYS_UNIT_KILOMETER:
		return 1.609344;
	case SYS_UNIT_POINT:
		return 4561920;
	case SYS_UNIT_INCH:
		return 63360;
	case SYS_UNIT_FEET:
		return 5280;
	case SYS_UNIT_YARD:
		return 1760;
	case SYS_UNIT_MILE:
		return 1;
	case SYS_UNIT_NAUTICALMILE:
		return 0.8689762;
	case SYS_UNIT_RADIAN:
		return 1609.344/GetRateRadianToOther(SYS_UNIT_METER);
	case SYS_UNIT_DEGREE:
		return 1609.344/GetRateDegreeToOther(SYS_UNIT_METER); 
	default:
		return 1;
	}
}

static double GetRateNauticalMileToOther(SYS_UNIT_TYPE outUnit)
{
	switch(outUnit)
	{
	case SYS_UNIT_MILLIMETER:
		return 1852000;
	case SYS_UNIT_CENTIMETER:
		return 185200;
	case SYS_UNIT_DECIMETER:
		return 18520;
	case SYS_UNIT_UNKNOWN: 
	case SYS_UNIT_METER:
		return 1852;
	case SYS_UNIT_KILOMETER:
		return 1.852;
	case SYS_UNIT_POINT:
		return 145826.771652;
	case SYS_UNIT_INCH:
		return 2025.3718285;
	case SYS_UNIT_FEET:
		return 6076.1154856;
	case SYS_UNIT_YARD:
		return 2025.3718285;
	case SYS_UNIT_MILE:
		return 1.1507794;
	case SYS_UNIT_NAUTICALMILE:
		return 1;
	case SYS_UNIT_RADIAN:
		return 1852/GetRateRadianToOther(SYS_UNIT_METER);
	case SYS_UNIT_DEGREE:
		return 1852/GetRateDegreeToOther(SYS_UNIT_METER); 
	default:
		return 1;
	}
}

static double GetRatePointToOther(SYS_UNIT_TYPE outUnit)
{
	switch(outUnit)
	{
	case SYS_UNIT_POINT:
		return 1;
	case SYS_UNIT_MILLIMETER:
		return 0.352778;
	case SYS_UNIT_CENTIMETER:
		return 0.0352778;
	case SYS_UNIT_DECIMETER:
		return 0.00352778;
	case SYS_UNIT_UNKNOWN: 
	case SYS_UNIT_METER:
		return 0.000352778;
	case SYS_UNIT_KILOMETER:
		return 0.000000352778;
	case SYS_UNIT_INCH:
		return 0.01384;
	case SYS_UNIT_FEET:
		return 0.00115333;
	case SYS_UNIT_YARD:
		return 0.000384444;
	case SYS_UNIT_MILE:
		return 0.000000218441;
	case SYS_UNIT_NAUTICALMILE:
		return 0.0000001905;
	case SYS_UNIT_RADIAN:
		return 0.000352778/GetRateRadianToOther(SYS_UNIT_METER);
	case SYS_UNIT_DEGREE:
		return 0.000352778/GetRateDegreeToOther(SYS_UNIT_METER); 
	default:
		return 1;
	}
}

static double GetRateRadianToOther(SYS_UNIT_TYPE outUnit)
{
	switch(outUnit)
	{
	case SYS_UNIT_POINT:
		return 111319.5*59.8422596*GetRateMeterToOther(SYS_UNIT_POINT);
	case SYS_UNIT_MILLIMETER:
		return 111319.5*59.8422596*GetRateMeterToOther(SYS_UNIT_MILLIMETER);
	case SYS_UNIT_CENTIMETER:
		return 111319.5*59.8422596*GetRateMeterToOther(SYS_UNIT_CENTIMETER);
	case SYS_UNIT_DECIMETER:
		return 111319.5*59.8422596*GetRateMeterToOther(SYS_UNIT_DECIMETER);
	case SYS_UNIT_UNKNOWN: 
	case SYS_UNIT_METER:
		return 111319.5*59.8422596;
	case SYS_UNIT_KILOMETER:
		return 111319.5*59.8422596*GetRateMeterToOther(SYS_UNIT_KILOMETER);
	case SYS_UNIT_INCH:
		return 111319.5*59.8422596*GetRateMeterToOther(SYS_UNIT_INCH);
	case SYS_UNIT_FEET:
		return 111319.5*59.8422596*GetRateMeterToOther(SYS_UNIT_FEET);
	case SYS_UNIT_YARD:
		return 111319.5*59.8422596*GetRateMeterToOther(SYS_UNIT_YARD);
	case SYS_UNIT_MILE:
		return 111319.5*59.8422596*GetRateMeterToOther(SYS_UNIT_MILE);
	case SYS_UNIT_NAUTICALMILE:
		return 111319.5*59.8422596*GetRateMeterToOther(SYS_UNIT_NAUTICALMILE);
	case SYS_UNIT_RADIAN:
		return 1;
	case SYS_UNIT_DEGREE:
		return  59.8422596;
	default:
		return 1;
	}
	return 59.8422596;
}

static double GetRateDegreeToOther(SYS_UNIT_TYPE outUnit)
{
	switch(outUnit)
	{
	case SYS_UNIT_POINT:
		return 111319.5*GetRateMeterToOther(SYS_UNIT_POINT);
	case SYS_UNIT_MILLIMETER:
		return 111319.5*GetRateMeterToOther(SYS_UNIT_MILLIMETER);
	case SYS_UNIT_CENTIMETER:
		return 111319.5*GetRateMeterToOther(SYS_UNIT_CENTIMETER);
	case SYS_UNIT_DECIMETER:
		return 111319.5*GetRateMeterToOther(SYS_UNIT_DECIMETER);
	case SYS_UNIT_UNKNOWN: 
	case SYS_UNIT_METER:
		return 111319.5;
	case SYS_UNIT_KILOMETER:
		return 111319.5*GetRateMeterToOther(SYS_UNIT_KILOMETER);
	case SYS_UNIT_INCH:
		return 111319.5*GetRateMeterToOther(SYS_UNIT_INCH);
	case SYS_UNIT_FEET:
		return 111319.5*GetRateMeterToOther(SYS_UNIT_FEET);
	case SYS_UNIT_YARD:
		return 111319.5*GetRateMeterToOther(SYS_UNIT_YARD);
	case SYS_UNIT_MILE:
		return 111319.5*GetRateMeterToOther(SYS_UNIT_MILE);
	case SYS_UNIT_NAUTICALMILE:
		return 111319.5*GetRateMeterToOther(SYS_UNIT_NAUTICALMILE);
	case SYS_UNIT_RADIAN:
		return 0.0174533;
	case SYS_UNIT_DEGREE:
		return 1;
	default:
		return 1;
	}
}
}
