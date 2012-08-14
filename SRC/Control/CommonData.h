//
//公共数据类型 
//
#pragma  once

typedef struct CalFieldValue
{
	CalFieldValue()
	{
		iIndex = -1;
		szFieldName = "";
		szType == "";
	}

	//重载==操作符
	bool operator==( const CalFieldValue &e ) const
	{
		return e.szFieldName == szFieldName;
	}

	int iIndex;					//索引
	std::string szFieldName;	//名称
	std::string szType;			//类型
}CAL_FIELDVALUE,  *LP_CAL_FIELDVALUE;

typedef struct FieldDisplayFormat
{
	FieldDisplayFormat()
	{
		szFieldName = "";
		szFormat = "";
		nTypeField = 0;
	}

	bool operator==( const FieldDisplayFormat &e ) const
	{
		return e.szFieldName == szFieldName;
	}

	std::string szFieldName;
	long nTypeField;
	std::string szFormat;		//格式化字符串
}FIELD_DISPLAY_FORMAT;

enum ROWTYPE
{
	FEAUTE_INDEX,
	TABLEROW_INDEX
};